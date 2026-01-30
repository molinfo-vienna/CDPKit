.. index:: single: CLI Applications; Pharmacophore Screening
           single: Pharmacophores; Screening
           single: Pharmacophores; Alignment
           single: Molecules; Pharmacophore-based Alignment
           
psdscreen
=========

Performs a pharmacophore-based virtual screening of molecule databases (see :doc:`psdcreate`).

Synopsis
--------

  :program:`psdscreen` [-hVvpxabSICDNPt] [-c arg] [-l arg] [-o arg] [-r arg] [-m arg] [-s arg] [-e arg] [-n arg] [-M arg] [-O arg] [-Q arg] -d arg -q arg 

Mandatory options
-----------------

  -d [ --database ] arg

    Screening database file.

  -q [ --query ] arg

    Specifies the file containing one or more pharmacophore(s) that shall be used as 
    a query for the database search.
    
    Supported Input Formats:
     - Native CDPL-Format (\*.cdf)
     - LigandScout Pharmaceutical Markup Language (\*.pml)
     - Pharmacophore Screening Database (\*.psd)
     - GZip-Compressed Native CDPL-Format (\*.cdf.gz)
     - BZip2-Compressed Native CDPL-Format (\*.cdf.bz2)

Other options
-------------

  -o [ --output ] arg

    Specifies the output file where database molecules matching the query pharmacophore(s) 
    shall be stored.

    Supported Output Formats:
     - JME Molecular Editor String (\*.jme)
     - MDL Structure-Data File (\*.sdf, \*.sd)
     - MDL Molfile (\*.mol)
     - Daylight SMILES String (\*.smi)
     - Daylight SMARTS String (\*.sma)
     - IUPAC International Chemical Identifier (\*.inchi, \*.ichi)
     - Native CDPL-Format (\*.cdf)
     - Tripos Sybyl MOL2 File (\*.mol2)
     - GZip-Compressed MDL Structure-Data File (\*.sdf.gz, \*.sd.gz, \*.sdz)
     - BZip2-Compressed MDL Structure-Data File (\*.sdf.bz2, \*.sd.bz2)
     - GZip-Compressed Native CDPL-Format (\*.cdf.gz)
     - BZip2-Compressed Native CDPL-Format (\*.cdf.bz2)
     - GZip-Compressed Daylight SMILES String (\*.smi.gz)
     - BZip2-Compressed Daylight SMILES String (\*.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 File (\*.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 File (\*.mol2.bz2)
     - Pharmacophore Screening Database (\*.psd)

  -r [ --report ] arg

    Report output file.

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

    Molecule conformer matching mode (FIRST-MATCH, BEST-MATCH, ALL-MATCHES, default: 
    FIRST-MATCH).

  -s [ --start-index ] arg (=0)

    Screening start molecule index (zero-based, default: 0).

  -e [ --end-index ] arg (=0)

    Screening end molecule index (zero-based and not included in the 
    screening run, default: number of molecules in the database).

  -n [ --max-num-hits ] arg (=0)

    Maxmimum number of hits to report (default: no limit).

  -M [ --max-omitted ] arg (=0)

    Allowed maximum number of unmatched features.

  -x [ --check-xvols ] [=arg(=1)]

    Check for exclusion volume clashes (default: true).

  -a [ --align-hits ] [=arg(=1)]

    Align matching conformations to pharmacophore for output (default: true).

  -b [ --best-alignments ] [=arg(=1)]

    Seek best alignments with highest score (default: false).

  -S [ --output-score ] [=arg(=1)]

    Output score property for hit molecule (default: true).

  -I [ --output-mol-index ] [=arg(=1)]

    Output database molecule index property for hit molecule (default: false).

  -C [ --output-conf-index ] [=arg(=1)]

    Output conformation index property for hit molecule (default: false).

  -D [ --output-db-name ] [=arg(=1)]

    Output database name property for hit molecule (default: false).

  -N [ --output-pharm-name ] [=arg(=1)]

    Output query pharmacophore name property for hit molecule (default: false).

  -P [ --output-pharm-index ] [=arg(=1)]

    Output query pharmacophore index property for hit molecule (default: false).

  -t [ --num-threads ] [=arg(=4)]

    Number of parallel execution threads (default: no multithreading, implicit value: 
    number of CPUs, must be >= 0, 0 disables multithreading).

  -u [ --unique-hits ] [=arg(=1)]

    Report molecules matching multiple query pharmacophores only once (default: false) [since V1.1]

  -O [ --output-format ] arg

    Allows to explicitly specify the format of the hit molecule output file by providing 
    one of the supported file-extensions (without leading dot!) as argument.
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file (because missing, misleading or not supported).
    
    Supported Output Formats:
     - JME Molecular Editor String (\*.jme)
     - MDL Structure-Data File (\*.sdf, \*.sd)
     - MDL Molfile (\*.mol)
     - Daylight SMILES String (\*.smi)
     - Daylight SMARTS String (\*.sma)
     - IUPAC International Chemical Identifier (\*.inchi, \*.ichi)
     - Native CDPL-Format (\*.cdf)
     - Tripos Sybyl MOL2 File (\*.mol2)
     - GZip-Compressed MDL Structure-Data File (\*.sdf.gz, \*.sd.gz, \*.sdz)
     - BZip2-Compressed MDL Structure-Data File (\*.sdf.bz2, \*.sd.bz2)
     - GZip-Compressed Native CDPL-Format (\*.cdf.gz)
     - BZip2-Compressed Native CDPL-Format (\*.cdf.bz2)
     - GZip-Compressed Daylight SMILES String (\*.smi.gz)
     - BZip2-Compressed Daylight SMILES String (\*.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 File (\*.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 File (\*.mol2.bz2)
     - Pharmacophore Screening Database (\*.psd)

  -Q [ --query-format ] arg

    Allows to explicitly specify the format of the query pharmacophore file by providing 
    one of the supported file-extensions (without leading dot!) as argument.
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file (because missing, misleading or not supported).
    
    Supported Input Formats:
     - Native CDPL-Format (\*.cdf)
     - LigandScout Pharmaceutical Markup Language (\*.pml)
     - Pharmacophore Screening Database (\*.psd)
     - GZip-Compressed Native CDPL-Format (\*.cdf.gz)
     - BZip2-Compressed Native CDPL-Format (\*.cdf.bz2)
