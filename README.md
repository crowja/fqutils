# FQUTILS

**[Home page](http://crowja.github.com/fqutils)** | **[Releases](https://github.com/crowja/fqutils/downloads)**

Fqutils is a collection of command line tools for working with files in FASTQ format, and
complements the [Fastx Toolkit](http://hannonlab.cshl.edu/fastx_toolkit) developed by
Greg Hannon's lab at Cold Spring Harbor. Fqutils is intended to be useful as part of
the early portions of postsequencing pipelines and quality assessment processes. At present
the package provides the following:

* fqu_are_paired - Checks if two files are pairwise concordant.
* fqu_cat - Like Unix cat, but for files in FASTQ format. Assuming well-formed input the output is guaranteed to be in lazy-FASTQ (i.e., four line) records. Especially useful when your own parsers assume this simpler format.
* fqu_degen - Replaces A, C, G, T with degenerate codes. Options include conversion to purines and pyrimidines (A, G -> R and C, T -> Y) and to a GC representation (C, G -> S and A, T -> W).
* fqu_rselect - Randomly select a subset of records from FASTQ input. 
* fqu_splitq - Segregate FASTQ input into two output files, based on a collection of identifiers.
* fqu_summary - Generate summary statistics for FASTQ input.
* fqu_tidy - Write FASTQ output based on FASTQ input. Like fqu_cat, output is guaranteed to be in four line records. Provides a "--squash" option for reducing the size of each record, currently by ignoring the second header, and a "--tab-delimited" option if you happen to want the output stream in a four column format. These single line records can be particularly convenient for internal processing pipelines.
* fqu_wc - Generates word (kmer) counts for FASTQ input.

## DEPENDENCIES

The package is written in Standard C, and ought to be easily portable to all Unix-like
systems. If this isn't the case please let me know. Fqutils requires Jean-Loup Gailly's and
Mark Adler's [Zlib](http://www.zlib.net/) 1.2.4 or later, which in turn allows the tools to
work transparently with text FASTQ as well as gzip-compressed FASTQ. It also makes use of
Troy Hanson's convenient [uthash](http://uthash.sourceforge.net) macros uthash.h, which is
included.

## INSTALLATION

    # Chdir into the source directory, then configure-make ...
    $ ./configure --prefix=/path/to/install_dir
    $ make
    $ make check
    $ make install

The "make check" step ought to run rather quickly since at present it doesn't do any
testing at all. If your Zlib installation is in a nonstandard location, provide guidance
to the configure script using the standard environment variables; for instance:

    $ LDFLAGS=-L/opt/zlib-1.2.4/lib ./configure --prefix=/path/to/install_dir

## EXAMPLES

    # fqu_tidy
    $ cat foo.fq | fqu_tidy
    $ gunzip -c foo.fq.gz | fqu_tidy
    $ cat foo.fq.gz | fqu_tidy

The third example above demonstrates that gzipped FASTQ streams can be handled directly
without explicit uncompression. 

    # fqu_summary
    $ fqu_summary foo.fq.gz > foo.fqsum
    $ cat foo.fq | fqu_summary > foo.fqsum

    # fqu_splitq
    $ cat foo.fq | fqu_splitq --out baz idfile1.txt idfile2.txt
    $ cat foo.fq.gz | fqu_splitq --out baz idfile1.txt idfile2.txt

## BUGS

If you find what appears to be a bug, send me the smallest possible test set you
can pull together that demonstrates the problem.

## CONTACT ME

If you find Fqutils useful, or have ideas for improvement, drop me a note or better yet open
an issue at [the Fqutils GitHub page](https://github.com/crowja/fqutils).

John A. Crow, <crowja@gmail.com>.

