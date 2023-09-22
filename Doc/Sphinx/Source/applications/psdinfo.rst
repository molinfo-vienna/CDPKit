psdinfo
=======

Provides information about the content of pharmacophore-screening databases (see :doc:`psdcreate`).

Synopsis
--------

  :program:`psdinfo` [-hVvpCPF] [-c arg] [-l arg] -i arg [arg]...

Mandatory options
-----------------

  -i [ --input ] arg

    Database(s) to analyze.

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

  -C [ --conf-stats ] [=arg(=1)]

    Print molecule conformation count statistics (default: false).

  -P [ --pharm-stats ] [=arg(=1)]

    Print pharmacophore feature count statistics (default: false).

  -F [ --feature-stats ] [=arg(=1)]

    Print feature type statistics (default: false).
