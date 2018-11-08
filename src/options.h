struct options {
   char       *fname;                       /* input file name, if any */
   unsigned    all_asserts_flag;
   char       *appname;
   char       *appvers;
   unsigned    help_flag;
   unsigned    nthreads;
   unsigned    quiet_flag;
   unsigned    verbosity;
   unsigned    version_flag;
};

struct options *options_new(void);
void        options_free(struct options *p);
void        options_help_msg(struct options *p, FILE *out);
void        options_parse(struct options *p, int argc, char *argv[]);
