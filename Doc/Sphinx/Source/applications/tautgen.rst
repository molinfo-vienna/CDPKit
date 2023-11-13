tautgen
=======

Performs tautomer generation/standardization for a set of input molecules.

Synopsis
--------

  :program:`tautgen` [-hVvptsdzS] [-c arg] [-l arg] [-m arg] [-I arg] [-O arg] [-n arg] [--keto-enol] [--imine-enamine] [--nitroso-oxime] [--amide-imidic-acid] [--lactam-lactim] [--ketene-ynol] [--nitro-aci] [--phosphinic-acid] [--sulfenic-acid] [--generic-h13-shift] [--generic-h15-shift] -i arg [arg]... -o arg

Mandatory options
-----------------

  -i [ --input ] arg

    Specifies one or more input file(s) with molecules for which tautomers have to be 
    generated.
    
    Supported Input Formats:
     - JME Molecular Editor String (.jme)
     - MDL Structure-Data File (.sdf, .sd)
     - MDL Molfile (.mol)
     - Daylight SMILES String (.smi)
     - Daylight SMARTS String (.sma)
     - IUPAC International Chemical Identifier (.inchi, .ichi)
     - Native CDPL-Format (.cdf)
     - Tripos Sybyl MOL2 File (.mol2)
     - GZip-Compressed MDL Structure-Data File (.sdf.gz, .sd.gz, .sdz)
     - BZip2-Compressed MDL Structure-Data File (.sdf.bz2, .sd.bz2)
     - GZip-Compressed Native CDPL-Format (.cdf.gz)
     - BZip2-Compressed Native CDPL-Format (.cdf.bz2)
     - GZip-Compressed Daylight SMILES String (.smi.gz)
     - BZip2-Compressed Daylight SMILES String (.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 File (.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 File (.mol2.bz2)

  -o [ --output ] arg

    Specifies the output file where the generated tautomers will be stored.
    
    Supported Output Formats:
     - JME Molecular Editor String (.jme)
     - MDL Structure-Data File (.sdf, .sd)
     - MDL Molfile (.mol)
     - Daylight SMILES String (.smi)
     - Daylight SMARTS String (.sma)
     - IUPAC International Chemical Identifier (.inchi, .ichi)
     - Native CDPL-Format (.cdf)
     - Tripos Sybyl MOL2 File (.mol2)
     - GZip-Compressed MDL Structure-Data File (.sdf.gz, .sd.gz, .sdz)
     - BZip2-Compressed MDL Structure-Data File (.sdf.bz2, .sd.bz2)
     - GZip-Compressed Native CDPL-Format (.cdf.gz)
     - BZip2-Compressed Native CDPL-Format (.cdf.bz2)
     - GZip-Compressed Daylight SMILES String (.smi.gz)
     - BZip2-Compressed Daylight SMILES String (.smi.bz2)
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

  -m [ --mode ] arg

    Tautomer generation mode (STANDARDIZE, TOP_UNIQUE, GEO_UNIQUE, EXHAUSTIVE default: 
    TOP_UNIQUE).

  -t [ --num-threads ] [=arg(=4)]

    Number of parallel execution threads (default: no multithreading, implicit value: 
    4 threads, must be >= 0, 0 disables multithreading).

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

  -s [ --regard-stereo ] [=arg(=1)]

    Consider stereochemistry in topological duplicate detection (default: true).

  -d [ --regard-iso ] [=arg(=1)]

    Whether or not isotope information matters in topological duplicate detection (default: 
    true).

  -z [ --neutralize ] [=arg(=1)]

    Neutralize molecule before generating tautomers (default: false).

  -n [ --max-num-tautomers ] arg

    Maximum number of output tautomers for each molecule (default: 0, must be >= 0, 
    0 disables limit).

  -S [ --title-suffix ] [=arg(=1)]

    Append tautomer number to the title of output molecules (default: false, since V1.1).

  --keto-enol [=arg(=1)]

    Enable keto <-> enol tautomerization (default: true).

  --imine-enamine [=arg(=1)]

    Enable imine <-> enamine tautomerization (default: true).

  --nitroso-oxime [=arg(=1)]

    Enable nitroso <-> oxime tautomerization (default: true).

  --amide-imidic-acid [=arg(=1)]

    Enable amide <-> imidic acid tautomerization (default: true).

  --lactam-lactim [=arg(=1)]

    Enable lactam <-> lactim tautomerization (default: true).

  --ketene-ynol [=arg(=1)]

    Enable ketene <-> ynol form tautomerization (default: true).

  --nitro-aci [=arg(=1)]

    Enable nitro <-> aci form tautomerization (default: true).

  --phosphinic-acid [=arg(=1)]

    Enable phosphinic acid tautomerization (default: true).

  --sulfenic-acid [=arg(=1)]

    Enable sulfenic acid tautomerization (default: true).

  --generic-h13-shift [=arg(=1)]

    Enable generic hydrogen 1 <-> 3 shift tautomerization (default: true).

  --generic-h15-shift [=arg(=1)]

    Enable generic hydrogen 1 <-> 5 shift tautomerization (default: true).
