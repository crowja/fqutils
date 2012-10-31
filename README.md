# FQUTILS

**[Home page](http://crowja.github.com/fqutils)** | **[Downloads](https://github.com/crowja/fqutils/downloads)** | **[Issues](https://github.com/crowja/fqutils/issues)**

Fqutils is a collection of command line tools for working with files in FASTQ format, and
complements the [Fastx Toolkit](http://hannonlab.cshl.edu/fastx_toolkit) developed by
Greg Hannon's lab at Cold Spring Harbor. Fqutils is intended to be useful as part of
the early portions of postsequencing pipelines and quality assessment processes. Note that Fqutils
correctly parses FASTQ as specified in the standard, and as a convenience produces *Lazy-FASTQ* output -- four line (header1-sequence-header2-quality) records. At present the package provides the following:

<table>
<tr><td>fqu_are_paired</td><td>Checks if two files are associated pairwise: Does the first record appearing in FASTQ file_1 have the same identifier as the first record in FASTQ file_2? ..., etc.</td></tr>
<tr><td>fqu_cat</td><td>Like Unix cat, but for files in FASTQ format. Assuming well-formed input the output is guaranteed to be in lazy-FASTQ records. Especially useful when your own parsers assume this simpler format.</td></tr>
<tr><td>fqu_cull</td><td>Reports a subset of a FASTQ stream, based on a collection of identifiers.</td></tr>
<tr><td>fqu_degen</td><td>Replaces A, C, G, T with degenerate codes. Options include conversion to purines and pyrimidines (A, G -> R and C, T -> Y) and to a GC representation (C, G -> S and A, T -> W).</td></tr>
<tr><td>fqu_rselect</td><td>Randomly select a subset of records from FASTQ input.</td></tr>
<tr><td>fqu_splitq</td><td>Segregate FASTQ input into two output files, based on a collection of identifiers.</td></tr>
<tr><td>fqu_summary</td><td>Generate summary statistics for FASTQ input.
These include total record (sequence) count, maximum sequence size, a estimation
of the quality offset (33 or 64), basecounts per position, a GC content histogram,
and per position quartiles of the qualities.</td></tr>
<tr><td>fqu_tidy</td><td>Write FASTQ output based on FASTQ input. Like fqu_cat, output is guaranteed to be in four line records. Provides a "--squash" option for reducing the size of each record, currently by ignoring the second header, and a "--tab-delimited" option if you happen to want the output stream in a four column format. These single line records can be particularly convenient for internal processing pipelines.</td></tr>
<tr><td>fqu_wc</td><td>Generates word (kmer) counts for FASTQ input.</td></tr>
</table>

## DEPENDENCIES

The package is written in Standard C, and ought to be easily portable to all Unix-like
systems. If you find this isn't the case please let me know. Fqutils requires Jean-Loup
Gailly's and Mark Adler's [Zlib](http://www.zlib.net/) 1.2.4 or later, which in turn allows
the tools to work transparently with text FASTQ as well as gzip-compressed FASTQ. It also
makes use of Troy Hanson's convenient [uthash macro collection](http://uthash.sourceforge.net), which is included.

## INSTALLATION

    ### Chdir into the source directory, then configure-make ...
    $ ./configure --prefix=/path/to/install_dir
    $ make
    $ make check
    $ make install

The "make check" step ought to run rather quickly since at present it doesn't do any
testing at all. If your Zlib installation is in a nonstandard location, provide guidance
to the configure script using the standard environment variables; for instance:

    $ LDFLAGS=-L/opt/zlib-1.2.4/lib ./configure --prefix=/path/to/install_dir

## EXAMPLES

    ### fqu_tidy
    $ cat foo.fq | fqu_tidy
    $ gunzip -c foo.fq.gz | fqu_tidy
    $ cat foo.fq.gz | fqu_tidy

The third example above demonstrates that gzipped FASTQ streams can be handled directly
without explicit uncompression. 

    ### fqu_summary
    $ fqu_summary foo.fq.gz > foo.fqsum
    $ cat foo.fq | fqu_summary > foo.fqsum

    ### fqu_splitq
    $ cat foo.fq | fqu_splitq --out baz idfile1.txt idfile2.txt
    $ cat foo.fq.gz | fqu_splitq --out baz idfile1.txt idfile2.txt

## ACKNOWLEDGEMENTS

Special thanks to:
* Laurent Guerby and the good folks at the [GCC Compile Farm](http://gcc.gnu.org/wiki/CompileFarm) for 
providing an environment for testing across multiple systems.


## LICENSE

See the LICENSE file in the distribution. Fqutils is distributed under the zlib/libpng license.

Note that Fqutils is provided by the copyright holders "as is" and without any express or implied
warranties, including, without limitation, the implied warranties of merchantibility and fitness
for a particular purpose.

## COPYRIGHT

Copyright 2012 by John A. Crow and the National Center for Genome Resources. All rights reserved.

## BUGS

If you find what appears to be a bug, send me the smallest possible test set you
can pull together that demonstrates the problem.

## CONTACT ME

If you find Fqutils useful, or have ideas for improvement, drop me a note or better yet open
an issue at [the Fqutils GitHub page](https://github.com/crowja/fqutils).

John A. Crow, <crowja@gmail.com>.


