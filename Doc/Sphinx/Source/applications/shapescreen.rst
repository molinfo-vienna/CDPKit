shapescreen
===========

Performs a fast Gaussian shape-based similarity screening of molecule databases.

Synaopsis
---------

  :program:`shapescreen` [-hVvpMPyazuWSACENGFBYt] [-c arg] [-l arg] [-o arg] [-r arg] [-m arg] [-s arg] [-b arg] [-n arg] [-x arg] [-X arg] [-g arg] [-f arg] [-R arg] [-T arg] [-Q arg] [-D arg] [-O arg] -q arg -d arg

Mandatory options
-----------------

  -q [ --query ] arg

    The query molecule input file.
    
    Supported Input Formats:
     - MDL Structure-Data File (.sdf, .sd)
     - MDL Molfile (.mol)
     - Native CDPL-Format (.cdf)
     - Tripos Sybyl MOL2 File (.mol2)
     - Atomic Coordinates XYZ File (*.xyz)
     - GZip-Compressed MDL Structure-Data File (.sdf.gz, .sd.gz, .sdz)
     - BZip2-Compressed MDL Structure-Data File (.sdf.bz2, .sd.bz2)
     - GZip-Compressed Native CDPL-Format (.cdf.gz)
     - BZip2-Compressed Native CDPL-Format (.cdf.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 File (.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 File (.mol2.bz2)
     - Pharmacophore Screening Database (.psd)
       
    Note that atom 3D-coordinates are required for shape screening!

  -d [ --database ] arg

    The screened database input file.
    
    Supported Input Formats:
     - MDL Structure-Data File (.sdf, .sd)
     - MDL Molfile (.mol)
     - Native CDPL-Format (.cdf)
     - Tripos Sybyl MOL2 File (.mol2)
     - Atomic Coordinates XYZ File (*.xyz)
     - GZip-Compressed MDL Structure-Data File (.sdf.gz, .sd.gz, .sdz)
     - BZip2-Compressed MDL Structure-Data File (.sdf.bz2, .sd.bz2)
     - GZip-Compressed Native CDPL-Format (.cdf.gz)
     - BZip2-Compressed Native CDPL-Format (.cdf.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 File (.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 File (.mol2.bz2)
     - Pharmacophore Screening Database (.psd)
       
    Note that atomic 3D-coordinates are required for shape screening!

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

  -o [ --output ] arg

    Hit molecule output file.
    
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
     - Pharmacophore Screening Database (.psd)

  -r [ --report ] arg

    Report output file.

  -m [ --mode ] arg

    Screening mode specifying which of the obtained results for the query molecule are 
    of interest (BEST_OVERALL, BEST_PER_QUERY, BEST_PER_QUERY_CONF, default: BEST_PER_QUERY).

  -s [ --score ] arg

    Primary scoring function that will be in effect for hit identification and ranking 
    operations (TOTAL_OVERLAP_TANIMOTO, SHAPE_TANIMOTO, COLOR_TANIMOTO, TANIMOTO_COMBO, 
    TOTAL_OVERLAP_TVERSKY, SHAPE_TVERSKY, COLOR_TVERSKY, TVERSKY_COMBO, QUERY_TOTAL_OVERLAP_TVERSKY, 
    QUERY_SHAPE_TVERSKY, QUERY_COLOR_TVERSKY, QUERY_TVERSKY_COMBO, DB_TOTAL_OVERLAP_TVERSKY, 
    DB_SHAPE_TVERSKY, DB_COLOR_TVERSKY, DB_TVERSKY_COMBO, default: TANIMOTO_COMBO)

  -b [ --best-hits ] arg

    Maximum number of best scoring hits to output (default: 1000).

  -n [ --max-hits ] arg

    Maximum number of found hits at which the search will terminate (overrides the 'best-
    hits' option, default: 0 - no limit).

  -x [ --cutoff ] arg

    Score cutoff value which determines whether a database molecule is considered as 
    a hit (default: 0.0 - no cutoff).

  -X [ --shape-tanimoto-cutoff ] arg

    Shape tanimoto score cutoff that will be used for hit identifiaction in addition 
    to the value specified by the 'cutoff' option (default: 0.0 - no cutoff).

  -M [ --merge-hits ] [=arg(=1)]

    If true, identified hits are merged into a single, combined hit list. If false, 
    a separate hit list for every query molecule will be maintained (default: false).

  -P [ --split-output ] [=arg(=1)]

    If true, for every query molecule a separate report and hit output file will be 
    generated (default: true).

  -y [ --score-only ] [=arg(=1)]

    If specified, no shape overlay of the query and database molecules will be performed 
    and the input poses get scored as they are (default: false).

  -a [ --opt-overlay ] [=arg(=1)]

    Specifies whether or not to perform an overlay optimization of the generated starting 
    poses (only in effect if option 'score-only' is false, default: true).

  -z [ --thorough-overlay-opt ] [=arg(=1)]

    Specifies whether or not to perform a thorough overlay optimization of the generated 
    starting poses (note: the screening time will increase significantly, default: false).

  -u [ --output-query ] [=arg(=1)]

    If specified, query molecules will be written at the beginning of the hit molecule 
    output file (default: true).

  -g [ --single-conf-db ] arg

    If specified, conformers of the database molecules are treated as individual single 
    conformer molecules (default: false).

  -f [ --color-ftr-type ] arg

    Specifies which type of color features to generate and score (NONE, EXP_PHARM, IMP_PHARM, 
    default: IMP_PHARM).

  -W [ --all-carbon ] [=arg(=1)]

    If specified, every heavy atom is interpreted as carbon (default: true).

  -S [ --shape-center-starts ] [=arg(=1)]

    If specified, principal axes aligned starting poses will be generated where both 
    shape centers are located atorigin the coordinates system (default: true).

  -A [ --atom-center-starts ] [=arg(=1)]

    If specified, principal axes aligned starting poses will be generated so that the 
    center of the smaller shape is located at all the heavy atom centers of the larger 
    shape (default: false).

  -C [ --color-center-starts ] [=arg(=1)]

    If specified, principal axes aligned starting poses will be generated so that the 
    center of the smaller shape is located at the color feature centers of the larger 
    shape (default: false).

  -R [ --random-starts ] arg

    Generates the specified number of principal axes aligned starting poses with randomized 
    shape center displacements (default: 0).

  -E [ --score-sd-tags ] [=arg(=1)]

    If true, score values will be appended as SD-block entries of the output hit molecules 
    (default: true).

  -N [ --query-name-sd-tags ] [=arg(=1)]

    If true, the query molecule name will be appended to the SD-block of the output 
    hit molecules (default: false).

  -G [ --query-idx-sd-tags ] [=arg(=1)]

    If true, the query molecule index will be appended to the SD-block of the output 
    hit molecules (default: false).

  -F [ --query-conf-sd-tags ] [=arg(=1)]

    If true, the query conformer index will be appended to the SD-block of the output 
    hit molecules (default: true).

  -B [ --db-idx-sd-tags ] [=arg(=1)]

    If true, the database molecule index will be appended to the SD-block of the output 
    hit molecules (default: false).

  -Y [ --db-conf-sd-tags ] [=arg(=1)]

    If true, the database conformer index will be appended to the SD-block of the output 
    hit molecules (default: true).

  -T [ --hit-name-ptn ] arg

    Pattern for composing the names of written hit molecules by variable substitution 
    (supported variables: @Q@ = query molecule name, @D@ = database molecule name, @C@ 
    = query molecule conformer index, @c@ = database molecule conformer index, @I@ = 
    query molecule index and @i@ = database molecule index, default: @D@_@c@_@Q@_@C@).

  -t [ --num-threads ] [=arg(=4)]

    Number of parallel execution threads (default: no multithreading, implicit value: 
    4 threads, must be >= 0, 0 disables multithreading).

  -Q [ --query-format ] arg

    Allows to explicitly specify the format of the query molecule file by providing 
    one of the supported file-extensions (without leading dot!) as argument.
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file (because missing, misleading or not supported).
    Note that atomic 3D-coordinates are required for shape screening!
    
  -D [ --database-format ] arg

    Allows to explicitly specify the format of the screening database file by providing 
    one of the supported file-extensions (without leading dot!) as argument.
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file(s) (because missing, misleading or not supported).
    Note that atomic 3D-coordinates are required for shape screening!
    
  -O [ --output-format ] arg

    Allows to explicitly specify the hit molecule output file format by providing one 
    of the supported file-extensions (without leading dot!) as argument.
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file (because missing, misleading or not supported).
