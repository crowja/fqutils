## (0.4.1 release)
* Now using uthash-1.9.7 http://uthash.sourceforge.net.
* Following benchmarking, mainly of fqu_wc, the uthash.h hash function was set to
be SFH rather than the default JEN.
* Added initial unit tests.


## 0.4.0 release
* Introduced fqu_cull to pull selected records from a FASTQ stream. Fqu_split already does something similar, but can't act as a filter.
* First man pages hacked into existence.


## 0.3.1 minor release
* Added --check-initial option to fqu_wc to check only the first few words
of a sequence rather than all.
