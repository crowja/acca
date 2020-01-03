/**
 *  @file linereader.c
 *  @version 0.2.0-dev0
 *  @date Fri Dec  6 09:54:07 CST 2019
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "varstr.h"
#include "linereader.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

#ifdef  _BUFSIZE
#undef  _BUFSIZE
#endif
#define _BUFSIZE      1024                       /* _BUFSIZE > 1 */

struct linereader {
   FILE       *in;
   char        buf[_BUFSIZE];
   struct varstr *text;
};

struct linereader *
linereader_new(void)
{
   struct linereader *tp;

   tp = (struct linereader *) malloc(sizeof(struct linereader));
   if (_IS_NULL(tp))
      return NULL;

   tp->in = stdin;                               /* default */
   tp->text = varstr_new();

   return tp;
}

void
linereader_free(struct linereader **pp)
{
   if (_IS_NULL(*pp))
      return;

   varstr_free(&(*pp)->text);

   if ((*pp)->in != stdin && !_IS_NULL((*pp)->in))
      fclose((*pp)->in);

   _FREE(*pp);
   *pp = NULL;
}

const char *
linereader_version(void)
{
   return "0.2.0-dev0";
}

int
linereader_init(struct linereader *p, char *fname)
{

   if (p->in != stdin)
      fclose(p->in);

   p->in = fopen(fname, "r");
   if (_IS_NULL(p->in))
      return 1;

   return 0;
}

const char *
linereader_next(struct linereader *p)
{
   varstr_empty(p->text);

   for (;;) {                                    /* loop to consume a single line */

      if (NULL == fgets(p->buf, _BUFSIZE, p->in)) {

         if (strlen(varstr_str(p->text)) == 0)   /* eof and no text accumulated -- done! */
            return NULL;

         else
            break;
      }

      varstr_cat(p->text, p->buf);

      if (NULL != strchr(p->buf, '\n'))
         break;
   }

   return (const char *) varstr_str(p->text);
}

#undef  _IS_NULL
#undef  _FREE
#undef  _BUFSIZE
