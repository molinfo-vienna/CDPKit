structgen
=========

Performs 3D structure generation for a set of input molecules.

:program:`structgen` is similar to :program:`confgen` but has been designed for use-cases where
a single reasonable low-energy 3D struture of a molecule is sufficient (which can be generated much
faster than a diverse conformer ensemble).

Synopsis
--------
   
  :program:`structgen` [-hVvptASszU] [-c arg] [-l arg] [-f arg] [-m arg] [-d arg] [-q arg] [-D arg] [-E arg] [-T arg] [-Z arg] [-P arg] [-w arg] [-k arg] [-K arg] [-B arg] [-g arg] [-G arg] [-I arg] [-O arg] [-F arg] -i arg [arg]... -o arg

Mandatory options
-----------------

  -i [ --input ] arg

    Specifies one or more input file(s) with molecules for which conformers have to 
    be generated.
    
    Supported Input Formats:
     - JME Molecular Editor String (.jme)
     - MDL Structure-Data File (.sdf, .sd)
     - MDL Molfile (.mol)
     - Daylight SMILES String (.smi)
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

  -o [ --output ] arg

    Specifies the output file where the generated structures will be stored.
    
    Supported Output Formats:
     - MDL Structure-Data File (.sdf, .sd)
     - MDL Molfile (.mol)
     - Native CDPL-Format (.cdf)
     - Tripos Sybyl MOL2 File (.mol2)
     - Atomic Coordinates XYZ File (.xyz)
     - GZip-Compressed MDL Structure-Data File (.sdf.gz, .sd.gz, .sdz)
     - BZip2-Compressed MDL Structure-Data File (.sdf.bz2, .sd.bz2)
     - GZip-Compressed Native CDPL-Format (.cdf.gz)
     - BZip2-Compressed Native CDPL-Format (.cdf.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 File (.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 File (.mol2.bz2)

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

  -f [ --failed ] arg

    Specifies the output file for molecules where structure generation failed.
    
    Supported Output Formats:
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

  -t [ --num-threads ] [=arg(=4)]

    Number of parallel execution threads (default: no multithreading, implicit value: 
    4 threads, must be >= 0, 0 disables multithreading).

  -m [ --mode ] arg

    Structure generation method to use (AUTO, DG, FRAGMENT, default: AUTO).

  -A [ --tol-range-sampling ] [=arg(=1)]

    Additionally generate conformers for angles at the boundaries of the first torsion 
    angle tolerance range (only effective for fragment-based structure generation, default: 
    true).

  -S [ --from-scratch ] [=arg(=1)]

    Discard input 3D-coordinates and generate structures from scratch (default: true).

  -d [ --frag-force-field ] arg

    Force field used for fragment-based structure generation (MMFF94, MMFF94_NO_ESTAT, 
    MMFF94S, MMFF94S_XOOP, MMFF94S_RTOR, MMFF94S_RTOR_XOOP, MMFF94S_NO_ESTAT, MMFF94S_XOOP_NO_ESTAT, 
    MMFF94S_RTOR_NO_ESTAT, MMFF94S_RTOR_XOOP_NO_ESTAT, default: MMFF94S_RTOR_NO_ESTAT).

  -q [ --dg-force-field ] arg

    Force field used for DG-based structure generation (MMFF94, MMFF94_NO_ESTAT, MMFF94S, 
    MMFF94S_XOOP, MMFF94S_RTOR, MMFF94S_RTOR_XOOP, MMFF94S_NO_ESTAT, MMFF94S_XOOP_NO_ESTAT, 
    MMFF94S_RTOR_NO_ESTAT, MMFF94S_RTOR_XOOP_NO_ESTAT, default: MMFF94S).

  -s [ --strict-param ] [=arg(=1)]

    Perform strict MMFF94 parameterization (default: true).

  -D [ --dielectric-const ] arg

    Dielectric constant used for the calculation of electrostatic interaction energies 
    (default: 80.0).

  -E [ --dist-exponent ] arg

    Distance exponent used for the calculation of electrostatic interaction energies 
    (default: 1.0).

  -T [ --timeout ] arg

    Time in seconds after which structure generation will be stopped (default: 1200 
    s, must be >= 0, 0 disables timeout).

  -Z [ --mc-rot-bond-count-thresh ] arg

    Number of rotatable bonds in a ring above which DG-based structure generation will 
    be performed(only effective in generation mode AUTO, default: 10, must be > 0).

  -P [ --ref-tol ] arg

    Energy tolerance at which force field structure refinement stops (only effective 
    in DG-based structure generation, default: 0.001, must be >= 0, 0 results in refinement 
    until convergence).

  -w [ --max-ref-iter ] arg

    Maximum number of force field structure refinement iterations (only effective in 
    DG-based structure generation, default: 0, must be >= 0, 0 disables limit).

  -k [ --add-tor-lib ] arg

    Torsion library to be used in addition to the built-in library (only effective for 
    fragment-based structure generation).

  -K [ --set-tor-lib ] arg

    Torsion library used as a replacement for the built-in library (only effective for 
    fragment-based structure generation).

  -B [ --frag-build-preset ] arg

    Fragment build preset to use (FAST, THOROUGH, only effective for fragment-based 
    structure generation, default: FAST).

  -g [ --add-frag-lib ] arg

    Fragment library to be used in addition to the built-in library (only effective 
    for fragment-based structure generation).

  -G [ --set-frag-lib ] arg

    Fragment library used as a replacement for the built-in library (only effective 
    for fragment-based structure generation).

  -z [ --canonicalize ] [=arg(=1)]

    Canonicalize input molecules (default: false).

  -U [ --hard-timeout ] [=arg(=1)]

    Specifies that exceeding the time limit shall be considered as an error and cause 
    structure generation to fail (default: false).

  -I [ --input-format ] arg

    Allows to explicitly specify the format of the input file(s) by providing one of 
    the supported file-extensions (without leading dot!) as argument.
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file(s) (because missing, misleading or not supported).

  -O [ --output-format ] arg

    Allows to explicitly specify the output format by providing one of the supported 
    file-extensions (without leading dot!) as argument.
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file (because missing, misleading or not supported).
    Note that only storage formats make sense that allow to store atom 3D-coordinates!

  -F [ --failed-format ] arg

    Allows to explicitly specify the output format by providing one of the supported 
    file-extensions (without leading dot!) as argument.
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file (because missing, misleading or not supported).
