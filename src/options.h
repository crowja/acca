struct options {
   char       *fname;                       /* input file name, if any */
   unsigned    all_asserts_flag;
   unsigned    help_flag;
   unsigned    quiet_flag;
   unsigned    verbosity;
   unsigned    version_flag;
};

struct options *options_new(void);
void        options_free(struct options *p);
void        options_helpmsg(FILE *out);
void        options_parse(struct options *p, int argc, char *argv[]);
