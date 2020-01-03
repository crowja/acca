#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "options.h"
#include "fgetopt.h"
#include "linewrapper.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)             ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)                ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

#ifdef  QUOTE
#undef  QUOTE
#endif
#define QUOTE(name) #name

#ifdef  STR
#undef  STR
#endif
#define STR(macro) QUOTE(macro)

#ifndef PACKAGE_VERSION
#define PACKAGE_VERSION dev
#endif

#ifdef  PACKAGE_VERSION_STR
#undef  PACKAGE_VERSION_STR
#endif
#define PACKAGE_VERSION_STR STR(PACKAGE_VERSION)

/**
 *  Structure is defined in options.h since it needs to be visible.
 */

/*** options_new() ***/

struct options *
options_new(void)
{
   struct options *tp;

   tp = (struct options *) malloc(sizeof(struct options));
   if (_IS_NULL(tp))
      return NULL;

   tp->all_asserts_flag = 0;
   tp->appname = "acca";
   tp->appvers = "0.4.1-dev0";
   tp->fname = NULL;
   tp->help_flag = 0;
   tp->nthreads = 0;
   tp->quiet_flag = 0;
   tp->verbosity = 0;
   tp->version_flag = 0;

   return tp;
}

/*** options_free() ***/

void
options_free(struct options **pp)
{
   if (_IS_NULL(*pp))
      return;

   _FREE((*pp)->fname);
   _FREE(*pp);
   *pp = NULL;
}

/*** options_help_msg() ***/

void
options_help_msg(struct options *p, FILE *out)
{
   unsigned    indent = 5;
   unsigned    width = 75;
   struct linewrapper *w = lwrap_new();

   fprintf(out, "Usage: acca [options] infile1 [infile2 ...]\n");
   fprintf(out, "Options:\n");

   fprintf(out, "%s\n", "-a, --all-asserts");
   fprintf(out, "%s\n",
           lwrap_format(w, indent, width, "By default the statements x[i] => y[j] "
                        "(and its contrapositive) and ~x[i] => ~y[j] (and its "
                        "contrapositive) are assessed. This option specifies "
                        "including two others: x[i]=> ~y[j], ~x[i] => y[j]."));

   fprintf(out, "%s\n", "-h, --help");
   fprintf(out, "%s\n",
           lwrap_format(w, indent, width, "Print this help message and exit."));

   fprintf(out, "%s\n", "-N<n>, --nthreads=<n>");
   fprintf(out, "%s\n",
           lwrap_format(w, indent, width,
                        "Use <n> OpenMP threads. Default is one thread per "
                        "cpu online."));

   fprintf(out, "%s\n", "-q, --quiet");
   fprintf(out, "%s\n",
           lwrap_format(w, indent, width,
                        "Run quietly. Resets accumulated -V and --verbosity flags."));

   fprintf(out, "%s\n", "-V, --verbosity");
   fprintf(out, "%s\n",
           lwrap_format(w, indent, width,
                        "Increase the level of reporting, multiples accumulate."));

   fprintf(out, "%s\n", "-v, --version");
   fprintf(out, "%s\n",
           lwrap_format(w, indent, width, "Print the version information and exit."));

   lwrap_free(&w);
}


/*** options_parse() ***/

void
options_parse(struct options *p, int argc, char *argv[])
{
   int         c;
   int         t;
   int         oindex = 0;
   char        opts[] = "ahN:p:qvV";
   static struct option long_options[] = {
      {"all-asserts", no_argument, NULL, 'a'},
      {"help", no_argument, NULL, 'h'},
      {"nthreads", required_argument, NULL, 'N'},
      {"prefix", required_argument, NULL, 'p'},
      {"quiet", no_argument, NULL, 'q'},
      {"version", no_argument, NULL, 'v'},
      {"verbose", no_argument, NULL, 'V'},
      {NULL, 0, NULL, 0}
   };

   optarg = NULL;                                /* initialized */
   opterr = 0;                                   /* suppress fgetopt error messages */
   optopt = '\0';                                /* initialized */

   for (;;) {

      c = fgetopt_long(argc, argv, opts, long_options, &oindex);

      if (c == -1)                               /* end of the options */
         break;

      switch (c) {

         case 'a':
            p->all_asserts_flag = 1;
            break;

         case 'h':
            p->help_flag = 1;
            return;

         case 'N':
            t = atoi(optarg);
            if (t > 0)
               p->nthreads = t;
            break;

         case 'p':
            printf("prefix set as %s\n", optarg);
            break;

         case 'q':
            p->verbosity = 0;
            break;

         case 'V':
            p->verbosity += 1;
            break;

         case 'v':
            p->version_flag = 1;
            return;

         case '?':
            fprintf(stderr, " ... bad option \n");      /* FIXME running with -d -h yields a core dump */
            break;

         default:
            abort();
      }
   }

   if (optind < argc) {                          /* remains NULL otherwise */
      p->fname = (char *) realloc(p->fname, (1 + strlen(argv[optind])) * sizeof(char));
      strcpy(p->fname, argv[optind]);
   }
}

#undef _IS_NULL
#undef _FREE
#undef QUOTE
#undef STR
#undef PACKAGE_VERSION
#undef PACKAGE_VERSION_STR
