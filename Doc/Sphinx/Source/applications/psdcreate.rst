psdcreate
=========

Creates a pharmacophore-screening database file from one or more molecule input 
files (see :doc:`psdscreen`).

Synopsis
--------

  :program:`psdcreate` [-hVvpdts] [-c arg] [-l arg] [-m arg] [-I arg] [-T arg] -i arg [arg]... -o arg

Mandatory options
-----------------

  -i [ --input ] arg

    Specifies one or more input file(s) with molecules that shall be stored in the created 
    database.
    
    Supported Input Formats:
     - MDL Structure-Data File (.sdf, .sd)
     - MDL Molfile (.mol)
     - IUPAC International Chemical Identifier (.inchi, .ichi)
     - Native CDPL-Format (.cdf)
     - Tripos Sybyl MOL2 File (.mol2)
     - Atomic Coordinates XYZ File (.xyz)
     - GZip-Compressed MDL Structure-Data File (.sdf.gz, .sd.gz, .sdz)
     - BZip2-Compressed MDL Structure-Data File (.sdf.bz2, .sd.bz2)
     - GZip-Compressed Native CDPL-Format (.cdf.gz)
     - BZip2-Compressed Native CDPL-Format (.cdf.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 File (.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 File (.mol2.bz2)
     - Pharmacophore Screening Database (.psd)

  -o [ --output ] arg

    Output database file.

Other options
-------------

  -h [ --help ] [=arg(=SHORT)]

    Print help message and exit (ABOUT, USAGE, SHORT, ALL or 'name of option', default: 
    SHORT).

  -V [ --version ] 

    Print version information and exit.

  -v [ --verbosity ] [=arg(=VERBOSE)]

    Verbosity level of information output (QUIET, ERROR, INFO, VERBOSE, DEBUG, default: 
    INFO).

  -c [ --config ] arg

    Use file with program options.

  -l [ --log-file ] arg

    Redirect text-output to file.

  -p [ --progress ] [=arg(=1)]

    Show progress bar (default: true).

  -m [ --mode ] arg

    Database creation mode (CREATE, APPEND, UPDATE, default: CREATE).

  -d [ --drop-duplicates ] [=arg(=1)]

    Drop duplicate molecules (default: false).

  -t [ --num-threads ] [=arg(=4)]

    Number of parallel execution threads (default: no multithreading, implicit value: 
    4 threads, must be >= 0, 0 disables multithreading).

  -I [ --input-format ] arg

    Allows to explicitly specify the format of the input file(s) by providing one of 
    the supported file-extensions (without leading dot!) as argument.
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file(s) (because missing, misleading or not supported).
    Note that only storage formats make sense that allow to store atom 3D-coordinates!

  -T [ --tmp-file-dir ] arg

    Temporary file directory (default: '/tmp')

  -s [ --add-src-file-prop ] [=arg(=1)]

    Add a source-file property to output molecules (default: false).
