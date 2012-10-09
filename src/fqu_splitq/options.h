struct options {
   char       *fname;                       /* input file name, if any */
   unsigned max_threads;
   int         optind;
   char       *outname;
   unsigned    verbosity;
};

struct options *options_new( void );
void        options_free( struct options *p );
void        options_helpmsg( FILE *out );
void        options_cmdline( struct options *p, int argc, char *argv[] );
