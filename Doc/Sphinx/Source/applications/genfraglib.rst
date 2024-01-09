genfraglib
==========

Creates, updates or merges fragment libraries for conformer generation with :doc:`CONFORGE <confgen>`.

Synopsis
--------

  :program:`genfraglib` [-hVvptsb] [-c arg] [-l arg] [-m arg] [-I arg] [-F arg] [-r arg] [-T arg] [-n arg] [-e arg] [-g arg] [-f arg] [-D arg] [-E arg] -i arg [arg]... -o arg

Mandatory options
-----------------

  -i [ --input ] arg

    When operating in CREATE or UPDATE mode, specifies one or more input file(s) with 
    molecules whose fragments shall be stored in the created fragment library.
    
    Supported Input Formats:
     - JME Molecular Editor String (.jme)
     - MDL Structure-Data File (.sdf, .sd)
     - MDL Molfile (.mol)
     - Daylight SMILES String (.smi)
     - Daylight SMARTS String (.sma)
     - IUPAC International Chemical Identifier (.inchi, .ichi)
     - Native CDPL-Format (.cdf)
     - Tripos Sybyl MOL2 File (.mol2)
     - Atomic Coordinates XYZ File (.xyz)
     - GZip-Compressed MDL Structure-Data File (.sdf.gz, .sd.gz, .sdz)
     - BZip2-Compressed MDL Structure-Data File (.sdf.bz2, .sd.bz2)
     - GZip-Compressed Native CDPL-Format (.cdf.gz)
     - BZip2-Compressed Native CDPL-Format (.cdf.bz2)
     - GZip-Compressed Daylight SMILES String (.smi.gz)
     - BZip2-Compressed Daylight SMILES String (.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 File (.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 File (.mol2.bz2)
     - CDPL Conformer Generator Fragment Library Format (.cfl, .cdf)

    In MERGE mode, specifies multiple existing fragment libraries in CDF format.

  -o [ --output ] arg

    Output fragment library file.

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

    Processing mode (CREATE, UPDATE, MERGE default: CREATE).

  -t [ --num-threads ] [=arg(=4)]

    Number of parallel execution threads (default: no multithreading, implicit value: 
    4 threads, must be >= 0, 0 disables multithreading).

  -I [ --input-format ] arg

    Allows to explicitly specify the format of the input file(s) by providing one of 
    the supported file-extensions (without leading dot!) as argument.
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file(s) (because missing, misleading or not supported).

  -F [ --preset ] arg

    Fragment conformer generation preset to use (FAST, THROUGH, default: THOROUGH).

  -r [ --rmsd ] arg

    Minimum RMSD of two small ring system conformations to be considered dissimilar 
    (default: 0.1000, must be >= 0).

  -T [ --timeout ] arg

    Time in seconds after which fragment conformer generation will be stopped (default: 
    1800s, must be >= 0, 0 disables timeout).

  -n [ --max-lib-size ] arg

    Maximum number of output fragments (default: 0, must be >= 0, 0 disables limit, 
    only valid in CREATE mode).

  -e [ --e-window ] arg

    Output energy window for small ring system conformers (default: 8.000000, must be 
    >= 0).

  -g [ --small-rsys-sampling-factor ] arg

    Small ring system conformer sampling factor (default: 20, must be > 1).

  -f [ --force-field ] arg

    Build force field (MMFF94, MMFF94_NO_ESTAT, MMFF94S, MMFF94S_XOOP, MMFF94S_RTOR, 
    MMFF94S_RTOR_XOOP, MMFF94S_NO_ESTAT, MMFF94S_XOOP_NO_ESTAT, MMFF94S_RTOR_NO_ESTAT, 
    MMFF94S_RTOR_XOOP_NO_ESTAT, default: MMFF94S_RTOR_NO_ESTAT).

  -s [ --strict-param ] [=arg(=1)]

    Perform strict MMFF94 parameterization (default: true).

  -D [ --dielectric-const ] arg

    Dielectric constant used for the calculation of electrostatic interaction energies 
    (default: 1.0).

  -E [ --dist-exponent ] arg

    Distance exponent used for the calculation of electrostatic interaction energies 
    (default: 1.0).

  -b [ --pres-bonding-geom ] [=arg(=1)]

    Preserve input bond lengths and angles (default: false).
