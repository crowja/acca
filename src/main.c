/**
 *  @file main.c
 *  @version 0.0-alpha
 *  @date %TODAY%
 *  @copyright %COPYRIGHT%
 *  @brief FIXME
 *  @details FIXME
 */

#include <stdlib.h>
#include <stdio.h>                               /* FIXME */
#include <string.h>                              /* FIXME */
#include "main.h"
#include "options.h"
#include "linereader.h"
#include "tokenset.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

#ifdef  _EXTEND
#undef  _EXTEND
#endif
#define _EXTEND       1024

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)
#ifndef PACKAGE_VERSION
#define PACKAGE_VERSION dev
#endif
#define PACKAGE_VERSION_STR STR(PACKAGE_VERSION)

static struct tokenset *xlabels;
static struct tokenset *ylabels;
static unsigned *xids = NULL;               /* sample i has xlabel id xid[i] */
static unsigned *yids = NULL;               /* sample i has ylabel id yid[i] */
static unsigned xysamp = 0;                 /* total number of raw samples */
static unsigned xysize = 0;                 /* current allocated size for both xids and yids */

static int
read_input(char *fname)
{
   struct linereader *r;
   char       *str;                         /* malloced and freed by linereader */
   char       *xword = NULL, *yword = NULL;
   char       *wtmp1, *wtmp2;
   size_t      wsize = 0;
   unsigned   *itmp1, *itmp2;

   r = linereader_new();
   if (!_IS_NULL(fname) && linereader_init(r, fname)) {
      fprintf(stderr, "[FATAL ERROR] Cannot open input file \"%s\"\n", fname);
      linereader_free(r);
      return 1;
   }

   while (NULL != (str = (char *) linereader_next(r))) {
      if (strlen(str) > wsize) {
         wtmp1 = (char *) realloc(xword, sizeof(char) * (wsize + _EXTEND));
         wtmp2 = (char *) realloc(yword, sizeof(char) * (wsize + _EXTEND));
         if (_IS_NULL(wtmp1) || _IS_NULL(wtmp2)) {
            fprintf(stderr,
                    "[FATAL ERROR] Cannot allocate adequate read buffers for input.\n");
            _FREE(xids);
            _FREE(yids);
            _FREE(xword);
            _FREE(yword);
            linereader_free(r);
            return 1;
         }

         xword = wtmp1;
         yword = wtmp2;
         wsize += _EXTEND;
      }

      if (xysize == xysamp) {
         itmp1 = (unsigned *) realloc(xids, sizeof(unsigned) * (xysize + _EXTEND));
         itmp2 = (unsigned *) realloc(yids, sizeof(unsigned) * (xysize + _EXTEND));
         if (_IS_NULL(itmp1) || _IS_NULL(itmp2)) {
            fprintf(stderr,
                    "[FATAL ERROR] Cannot allocate adequate memory for input data.\n");
            _FREE(xids);
            _FREE(yids);
            _FREE(xword);
            _FREE(yword);
            linereader_free(r);
            return 1;
         }

         xids = itmp1;
         yids = itmp2;
         xysize += _EXTEND;
      }

      sscanf(str, "%s %s", xword, yword);
      if ('#' == xword[0])                       /* we'll skip comment lines */
         continue;
      /* do something with xword and yword */
      xids[xysamp] = tokenset_add(xlabels, xword);
      yids[xysamp] = tokenset_add(ylabels, yword);
#if 0
      printf("Just assigned %d and %d to sample %d\n", xids[xysamp], yids[xysamp],
             xysamp);
#endif
#if 0
      printf("In read_input() just read \"%s\" and \"%s\"\n", xword, yword);
#endif
      xysamp += 1;

   }

   printf("Tokenset x count %d, tokenset y count %d\n", tokenset_count(xlabels),
          tokenset_count(ylabels));

   _FREE(xword);
   _FREE(yword);
   linereader_free(r);

   return 0;
}

static int
set_scores(struct options *o, unsigned r, unsigned c)
{
   unsigned    i, j, k;
   double     *table = NULL;
   double     *rowsums = NULL;
   double     *colsums = NULL;
   double      allsums = 0;
   double      prior = 0;
   double      tol = 0.0;
   const char *xlabel, *ylabel;

   /* Compute the count table, the row sums, the col sums */

   table = (double *) realloc(table, sizeof(double) * r * c);
   rowsums = (double *) realloc(rowsums, sizeof(double) * r);
   colsums = (double *) realloc(colsums, sizeof(double) * c);

   /* FIXME ought to check for success on the allocations above */

   for (i = 0; i < r; i++)
      for (j = 0; j < c; j++)
         table[i * c + j] = prior;

   for (i = 0; i < r; i++)
      rowsums[i] = prior * c;

   for (j = 0; j < c; j++)
      colsums[j] = prior * r;

   allsums = prior * r * c;

   for (k = 0; k < xysamp; k++) {
      i = xids[k];
      j = yids[k];
      table[i * c + j] += 1;
      rowsums[i] += 1;
      colsums[j] += 1;
      allsums += 1;
   }

#if 0
   printf("%f\t%f\t|%f\n", table[0 * c + 0], table[0 * c + 1], rowsums[0]);
   printf("%f\t%f\t|%f\n", table[1 * c + 0], table[1 * c + 1], rowsums[1]);
   printf("- - - - - - - - - - - - - - - - - - - - - - \n");
   printf("------------ %f\t%f\t|%f\n", colsums[0], colsums[1], allsums);
#endif

   for (i = 0; i < r; i++) {

      if (rowsums[i] < tol * allsums + 10)
         continue;

      xlabel = tokenset_get_by_id(xlabels, i);

      for (j = 0; j < c; j++) {
         double      p1, p2;

         ylabel = tokenset_get_by_id(ylabels, j);

         if (colsums[j] < tol * allsums + 10)
            continue;

         /* Assertion 1:  x[i] =>  y[j], ~y[j] => ~x[i] */
         p1 = table[i * c + j] / rowsums[i];
         p2 =
          (allsums - rowsums[i] - colsums[j] + table[i * c + j]) / (allsums - colsums[j]);
         if (p1 * p2 > 0.8)
            printf("%f %f [%f %f] x:%s => y:%s\n", p1, p2, rowsums[i], colsums[j],
                   xlabel, ylabel);

         /* Assertion 4: ~x[i] => ~y[j],  y[j] =>  x[i] */
         p1 =
          (allsums - rowsums[i] - colsums[j] + table[i * c + j]) / (allsums - rowsums[i]);
         p2 = table[i * c + j] / colsums[j];
         if (p1 * p2 > 0.8)
            printf("%f %f [%f %f] ~x:%s => ~y:%s\n", p1, p2, rowsums[i], colsums[j],
                   xlabel, ylabel);

         if (!o->all_asserts_flag)
            continue;                            /* skip assertions 2 and 3 */

         /* Assertion 2:  x[i] => ~y[j],  y[j] => ~x[i] */
         p1 = (rowsums[i] - table[i * c + j]) / rowsums[i];
         p2 = (colsums[j] - table[i * c + j]) / colsums[j];
         if (p1 * p2 > 0.8)
            printf("%f %f [%f %f] x:%s => ~y:%s\n", p1, p2, rowsums[i], colsums[j],
                   xlabel, ylabel);

         /* Assertion 3: ~x[i] =>  y[j], ~y[j] =>  x[i] */
         p1 = (colsums[j] - table[i * c + j]) / (allsums - rowsums[i]);
         p2 = (rowsums[i] - table[i * c + j]) / (allsums - colsums[j]);
         if (p1 * p2 > 0.8)
            printf("%f %f [%f %f] ~x:%s => y:%s\n", p1, p2, rowsums[i], colsums[j],
                   xlabel, ylabel);
      }
   }

   /* Find the initial candidates */
   _FREE(table);
   _FREE(rowsums);
   _FREE(colsums);

   return 0;
}

int
main(int argc, char *argv[])
{
   struct options *o = options_new();
   unsigned    r, c;                        /* count table has r rows and c cols */

   options_parse(o, argc, argv);

   if (o->help_flag) {
      options_helpmsg(stderr);
      options_free(o);
      exit(0);
   }

   if (o->version_flag) {
      printf("acca %s\n", PACKAGE_VERSION_STR);
      options_free(o);
      exit(0);
   }

   /* Get the input data */

   xlabels = tokenset_new();                     /* x and y are global */
   ylabels = tokenset_new();

   if (read_input(o->fname)) {                   /* error from read_input() */
   }

   r = tokenset_count(xlabels);
   c = tokenset_count(ylabels);
#if 0
   printf("There are %d samples\n", xysamp);
   printf("The count table has %d rows and %d cols\n", r, c);

   /** The action begins here
    *  Need to assess the significance of four statement pairs:
    *    Pair 1:  x[i]  =>  y[j], ~y[j] => ~x[i],
    *    Pair 2:  x[i]  => ~y[j],  y[j] => ~x[i],
    *    Pair 3: ~x[i]  =>  y[j], ~y[j] =>  x[i].
    *    Pair 4: ~x[i]  => ~y[j],  y[j] =>  x[i].
    */

   /* Compute the scores table */
#endif

   set_scores(o, r, c);

   tokenset_free(xlabels);
   tokenset_free(ylabels);
   _FREE(xids);                                  /* xids and yids malloced in read_input() */
   _FREE(yids);
   options_free(o);

   return 0;
}

#undef _IS_NULL
#undef _FREE
