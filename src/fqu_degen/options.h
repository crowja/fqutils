struct options {
   unsigned    conversion_type;
   char       *fname;                       /* input file name, if any */
   unsigned    max_threads;
   int         optind;
   unsigned    verbosity;
};

struct options *options_new( void );
void        options_free( struct options *p );
void        options_helpmsg( FILE *out );
void        options_cmdline( struct options *p, int argc, char *argv[] );
