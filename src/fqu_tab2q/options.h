struct options {
   char       *fname;                       /* input file name, if any */
   unsigned    quiet_flag;
   unsigned    squash_flag;
   unsigned    verbosity;
};

struct options *options_new( void );
void        options_free( struct options *p );
void        options_helpmsg( FILE *out );
void        options_cmdline( struct options *p, int argc, char *argv[] );
