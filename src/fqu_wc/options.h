struct options {
   char       *fname;                       /* input file name, if any */
   unsigned    check_initial;
   unsigned    max_threads;
   unsigned    min_count;
   int         optind;
   unsigned    verbosity;
   unsigned    word_size;
};

struct options *options_new( void );
void        options_free( struct options *p );
void        options_helpmsg( FILE *out );
void        options_cmdline( struct options *p, int argc, char *argv[] );
