.. index:: single: CLI Applications; Similarity Screening

simscreen
=========

Performs a fast fingerprint-based similarity screening of molecule databases.

Synopsis
--------

  :program:`simscreen` [-hVvpMTugSNGFBYt] [-c arg] [-l arg] [-o arg] [-r arg] [-m arg] [-f arg] [-e arg] [-b arg] [-n arg] [-x arg] [-P arg] [-Q arg] [-D arg] [-O arg] [--tversky-weight-a arg] [--tversky-weight-b arg] [--ecfp-size arg] [--ecfp-radius arg] [--ecfp-inc-H arg] [--ecfp-inc-chirality arg] [--daylight-size arg] [--daylight-min-path-len arg] [--daylight-max-path-len arg] [--daylight-inc-H arg] [--pharm-2d-size arg] [--pharm-2d-min-tuple-size arg] [--pharm-2d-max-tuple-size arg] [--pharm-2d-bin-size arg] [--pharm-3d-size arg] [--pharm-3d-min-tuple-size arg] [--pharm-3d-max-tuple-size arg] [--pharm-3d-bin-size arg] -q arg -d arg

Mandatory options
-----------------

  -q [ --query ] arg

    The query molecule input file.
    
    Supported Input Formats:
     - JME Molecular Editor String (\*.jme)
     - MDL Structure-Data Format (\*.sdf, \*.sd)
     - MDL Molfile (\*.mol)
     - Daylight SMILES Format (\*.smi)
     - Daylight SMARTS Format (\*.sma)
     - IUPAC International Chemical Identifier (\*.inchi, \*.ichi)
     - Native CDPL Format (\*.cdf)
     - Tripos Sybyl MOL2 Format (\*.mol2)
     - Atomic Coordinates XYZ Format (\*.xyz)
     - Chemical Markup Language Format (\*.cml)
     - GZip-Compressed MDL Structure-Data Format (\*.sdf.gz, \*.sd.gz, \*.sdz)
     - BZip2-Compressed MDL Structure-Data Format (\*.sdf.bz2, \*.sd.bz2)
     - GZip-Compressed Native CDPL Format (\*.cdf.gz)
     - BZip2-Compressed Native CDPL Format (\*.cdf.bz2)
     - GZip-Compressed Daylight SMILES Format (\*.smi.gz)
     - BZip2-Compressed Daylight SMILES Format (\*.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 Format (\*.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 Format (\*.mol2.bz2)
     - GZip-Compressed Atomic Coordinates XYZ Format (\*.xyz.gz)
     - BZip2-Compressed Atomic Coordinates XYZ Format (\*.xyz.bz2)
     - GZip-Compressed Chemical Markup Language Format (\*.cml.gz)
     - BZip2-Compressed Chemical Markup Language Format (\*.cml.bz2)
     - Brookhaven Protein Data Bank Entry Format (\*.pdb, \*.ent)
     - Macromolecular Transmission Format (\*.mmtf)
     - Macromolecular Crystallographic Information File Format (\*.mmcif, \*.cif)
     - GZip-Compressed Brookhaven Protein Data Bank Entry Format (\*.pdb.gz, \*.ent.gz)
     - BZip2-Compressed Brookhaven Protein Data Bank Entry Format (\*.pdb.bz2, \*.ent.bz2)
     - GZip-Compressed Macromolecular Transmission Format (\*.mmtf.gz)
     - BZip2-Compressed Macromolecular Transmission Format (\*.mmtf.bz2)
     - GZip-Compressed Macromolecular Crystallographic Information File Format (\*.mmcif.gz, \*.cif.gz)
     - BZip2-Compressed Macromolecular Crystallographic Information File Format (\*.mmcif.bz2,\*.cif.bz2)
     - Pharmacophore Screening Database Format (\*.psd)

  -d [ --database ] arg

    The molecule database file to screen.
    
    Supported Input Formats:
     - JME Molecular Editor String (\*.jme)
     - MDL Structure-Data Format (\*.sdf, \*.sd)
     - MDL Molfile (\*.mol)
     - Daylight SMILES Format (\*.smi)
     - Daylight SMARTS Format (\*.sma)
     - IUPAC International Chemical Identifier (\*.inchi, \*.ichi)
     - Native CDPL Format (\*.cdf)
     - Tripos Sybyl MOL2 Format (\*.mol2)
     - Atomic Coordinates XYZ Format (\*.xyz)
     - Chemical Markup Language Format (\*.cml)
     - GZip-Compressed MDL Structure-Data Format (\*.sdf.gz, \*.sd.gz, \*.sdz)
     - BZip2-Compressed MDL Structure-Data Format (\*.sdf.bz2, \*.sd.bz2)
     - GZip-Compressed Native CDPL Format (\*.cdf.gz)
     - BZip2-Compressed Native CDPL Format (\*.cdf.bz2)
     - GZip-Compressed Daylight SMILES Format (\*.smi.gz)
     - BZip2-Compressed Daylight SMILES Format (\*.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 Format (\*.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 Format (\*.mol2.bz2)
     - GZip-Compressed Atomic Coordinates XYZ Format (\*.xyz.gz)
     - BZip2-Compressed Atomic Coordinates XYZ Format (\*.xyz.bz2)
     - GZip-Compressed Chemical Markup Language Format (\*.cml.gz)
     - BZip2-Compressed Chemical Markup Language Format (\*.cml.bz2)
     - Brookhaven Protein Data Bank Entry Format (\*.pdb, \*.ent)
     - Macromolecular Transmission Format (\*.mmtf)
     - Macromolecular Crystallographic Information File Format (\*.mmcif, \*.cif)
     - GZip-Compressed Brookhaven Protein Data Bank Entry Format (\*.pdb.gz, \*.ent.gz)
     - BZip2-Compressed Brookhaven Protein Data Bank Entry Format (\*.pdb.bz2, \*.ent.bz2)
     - GZip-Compressed Macromolecular Transmission Format (\*.mmtf.gz)
     - BZip2-Compressed Macromolecular Transmission Format (\*.mmtf.bz2)
     - GZip-Compressed Macromolecular Crystallographic Information File Format (\*.mmcif.gz, \*.cif.gz)
     - BZip2-Compressed Macromolecular Crystallographic Information File Format (\*.mmcif.bz2, \*.cif.bz2)
     - Pharmacophore Screening Database Format (\*.psd)

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
     - JME Molecular Editor String (\*.jme)
     - MDL Structure-Data Format (\*.sdf, \*.sd)
     - MDL Molfile (\*.mol)
     - Daylight SMILES Format (\*.smi)
     - Daylight SMARTS Format (\*.sma)
     - IUPAC International Chemical Identifier (\*.inchi, \*.ichi)
     - Native CDPL Format (\*.cdf)
     - Tripos Sybyl MOL2 Format (\*.mol2)
     - Atomic Coordinates XYZ Format (\*.xyz)
     - Chemical Markup Language Format (\*.cml)
     - GZip-Compressed MDL Structure-Data Format (\*.sdf.gz, \*.sd.gz, \*.sdz)
     - BZip2-Compressed MDL Structure-Data Format (\*.sdf.bz2, \*.sd.bz2)
     - GZip-Compressed Native CDPL Format (\*.cdf.gz)
     - BZip2-Compressed Native CDPL Format (\*.cdf.bz2)
     - GZip-Compressed Daylight SMILES Format (\*.smi.gz)
     - BZip2-Compressed Daylight SMILES Format (\*.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 Format (\*.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 Format (\*.mol2.bz2)
     - GZip-Compressed Atomic Coordinates XYZ Format (\*.xyz.gz)
     - BZip2-Compressed Atomic Coordinates XYZ Format (\*.xyz.bz2)
     - GZip-Compressed Chemical Markup Language Format (\*.cml.gz)
     - BZip2-Compressed Chemical Markup Language Format (\*.cml.bz2)
     - Brookhaven Protein Data Bank Entry Format (\*.pdb, \*.ent)
     - Macromolecular Transmission Format (\*.mmtf)
     - Macromolecular Crystallographic Information File Format (\*.mmcif, \*.cif)
     - GZip-Compressed Brookhaven Protein Data Bank Entry Format (\*.pdb.gz, \*.ent.gz)
     - BZip2-Compressed Brookhaven Protein Data Bank Entry Format (\*.pdb.bz2, \*.ent.bz2)
     - GZip-Compressed Macromolecular Transmission Format (\*.mmtf.gz)
     - BZip2-Compressed Macromolecular Transmission Format (\*.mmtf.bz2)
     - GZip-Compressed Macromolecular Crystallographic Information File Format (\*.mmcif.gz, \*.cif.gz)
     - BZip2-Compressed Macromolecular Crystallographic Information File Format (\*.mmcif.bz2, \*.cif.bz2)
     - Pharmacophore Screening Database Format (\*.psd)

  -r [ --report ] arg

    Report output file.

  -m [ --mode ] arg

    Specifies which kind of obtained results for the query/database molecule pairings 
    are of interest (BEST_OVERALL, BEST_PER_QUERY, BEST_PER_QUERY_CONF, default: BEST_PER_QUERY).

  -f [ --func ] arg

    Function to use for molecule similarity/distance calculation and ranking operations 
    (TANIMOTO_SIM, TVERSKY_SIM, COSINE_SIM, DICE_SIM, MANHATTAN_SIM, MANHATTAN_DIST, 
    HAMMING_DIST, EUCLIDEAN_SIM, EUCLIDEAN_DIST, default: TANIMOTO_SIM)

  -e [ --descr ] arg

    Type of molecule descriptor to use for similarity/distance calculations (ECFP, DAYLIGHT, 
    PUBCHEM, MACCS, PHARM_2D, PHARM_3D, default: ECFP)

  -b [ --best-hits ] arg

    Maximum number of best scoring hits to output (default: 1000).

  -n [ --max-hits ] arg

    Maximum number of found hits at which the screen will terminate (overrides the --
    best-hits option, default: 0 - no limit).

  -x [ --cutoff ] arg

    Similarity/distance cutoff value which determines whether an database molecule is 
    considered as a hit (default: -1.0 -> no cutoff).

  -M [ --merge-hits ] [=arg(=1)]

    If true, identified hits are merged into a single, combined hit list. If false, 
    a separate hit list for every query molecule will be maintained (default: false).

  -T [ --split-output ] [=arg(=1)]

    If true, for every query molecule a separate report and hit output file will be 
    generated (default: true).

  -u [ --output-query ] [=arg(=1)]

    If specified, query molecules will be written at the beginning of the hit molecule 
    output file (default: true).

  -g [ --single-conf ] [=arg(=1)]

    If specified, conformers of the database molecules are treated as individual single 
    conformer molecules (default: false).

  -S [ --score-sd-tags ] [=arg(=1)]

    If true, similarity/distance score values will be appended as SD-block entries of 
    the output hit molecules (default: true).

  -N [ --query-name-sd-tags ] [=arg(=1)]

    If true, the query molecule name will be appended to the SD-block of the output 
    hit molecules (default: false).

  -G [ --query-idx-sd-tags ] [=arg(=1)]

    If true, the query molecule index will be appended to the SD-block of the output 
    hit molecules (default: false).

  -F [ --query-conf-sd-tags ] [=arg(=1)]

    If true, the query molecule conformer index will be appended to the SD-block of 
    the output hit molecules (default: true).

  -B [ --db-idx-sd-tags ] [=arg(=1)]

    If true, the database molecule index will be appended to the SD-block of the output 
    hit molecules (default: false).

  -Y [ --db-conf-sd-tags ] [=arg(=1)]

    If true, the database molecule conformer index will be appended to the SD-block 
    of the output hit molecules (default: true).

  -P [ --hit-name-ptn ] arg

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
    
    Supported Input Formats:
     - JME Molecular Editor String (\*.jme)
     - MDL Structure-Data Format (\*.sdf, \*.sd)
     - MDL Molfile (\*.mol)
     - Daylight SMILES Format (\*.smi)
     - Daylight SMARTS Format (\*.sma)
     - IUPAC International Chemical Identifier (\*.inchi, \*.ichi)
     - Native CDPL Format (\*.cdf)
     - Tripos Sybyl MOL2 Format (\*.mol2)
     - Atomic Coordinates XYZ Format (\*.xyz)
     - Chemical Markup Language Format (\*.cml)
     - GZip-Compressed MDL Structure-Data Format (\*.sdf.gz, \*.sd.gz, \*.sdz)
     - BZip2-Compressed MDL Structure-Data Format (\*.sdf.bz2, \*.sd.bz2)
     - GZip-Compressed Native CDPL Format (\*.cdf.gz)
     - BZip2-Compressed Native CDPL Format (\*.cdf.bz2)
     - GZip-Compressed Daylight SMILES Format (\*.smi.gz)
     - BZip2-Compressed Daylight SMILES Format (\*.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 Format (\*.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 Format (\*.mol2.bz2)
     - GZip-Compressed Atomic Coordinates XYZ Format (\*.xyz.gz)
     - BZip2-Compressed Atomic Coordinates XYZ Format (\*.xyz.bz2)
     - GZip-Compressed Chemical Markup Language Format (\*.cml.gz)
     - BZip2-Compressed Chemical Markup Language Format (\*.cml.bz2)
     - Brookhaven Protein Data Bank Entry Format (\*.pdb, \*.ent)
     - Macromolecular Transmission Format (\*.mmtf)
     - Macromolecular Crystallographic Information File Format (\*.mmcif, \*.cif)
     - GZip-Compressed Brookhaven Protein Data Bank Entry Format (\*.pdb.gz, \*.ent.gz)
     - BZip2-Compressed Brookhaven Protein Data Bank Entry Format (\*.pdb.bz2, \*.ent.bz2)
     - GZip-Compressed Macromolecular Transmission Format (\*.mmtf.gz)
     - BZip2-Compressed Macromolecular Transmission Format (\*.mmtf.bz2)
     - GZip-Compressed Macromolecular Crystallographic Information File Format (\*.mmcif.gz, \*.cif.gz)
     - BZip2-Compressed Macromolecular Crystallographic Information File Format (\*.mmcif.bz2, \*.cif.bz2)
     - Pharmacophore Screening Database Format (\*.psd)
    
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file (because missing, misleading or not supported).

  -D [ --database-format ] arg

    Allows to explicitly specify the format of the screening database file by providing 
    one of the supported file-extensions (without leading dot!) as argument.
    
    Supported Input Formats:
     - JME Molecular Editor String (\*.jme)
     - MDL Structure-Data Format (\*.sdf, \*.sd)
     - MDL Molfile (\*.mol)
     - Daylight SMILES Format (\*.smi)
     - Daylight SMARTS Format (\*.sma)
     - IUPAC International Chemical Identifier (\*.inchi, \*.ichi)
     - Native CDPL Format (\*.cdf)
     - Tripos Sybyl MOL2 Format (\*.mol2)
     - Atomic Coordinates XYZ Format (\*.xyz)
     - Chemical Markup Language Format (\*.cml)
     - GZip-Compressed MDL Structure-Data Format (\*.sdf.gz, \*.sd.gz, \*.sdz)
     - BZip2-Compressed MDL Structure-Data Format (\*.sdf.bz2, \*.sd.bz2)
     - GZip-Compressed Native CDPL Format (\*.cdf.gz)
     - BZip2-Compressed Native CDPL Format (\*.cdf.bz2)
     - GZip-Compressed Daylight SMILES Format (\*.smi.gz)
     - BZip2-Compressed Daylight SMILES Format (\*.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 Format (\*.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 Format (\*.mol2.bz2)
     - GZip-Compressed Atomic Coordinates XYZ Format (\*.xyz.gz)
     - BZip2-Compressed Atomic Coordinates XYZ Format (\*.xyz.bz2)
     - GZip-Compressed Chemical Markup Language Format (\*.cml.gz)
     - BZip2-Compressed Chemical Markup Language Format (\*.cml.bz2)
     - Brookhaven Protein Data Bank Entry Format (\*.pdb, \*.ent)
     - Macromolecular Transmission Format (\*.mmtf)
     - Macromolecular Crystallographic Information File Format (\*.mmcif, \*.cif)
     - GZip-Compressed Brookhaven Protein Data Bank Entry Format (\*.pdb.gz, \*.ent.gz)
     - BZip2-Compressed Brookhaven Protein Data Bank Entry Format (\*.pdb.bz2, \*.ent.bz2)
     - GZip-Compressed Macromolecular Transmission Format (\*.mmtf.gz)
     - BZip2-Compressed Macromolecular Transmission Format (\*.mmtf.bz2)
     - GZip-Compressed Macromolecular Crystallographic Information File Format (\*.mmcif.gz, \*.cif.gz)
     - BZip2-Compressed Macromolecular Crystallographic Information File Format (\*.mmcif.bz2, \*.cif.bz2)
     - Pharmacophore Screening Database Format (\*.psd)
    
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file(s) (because missing, misleading or not supported).

  -O [ --output-format ] arg

    Allows to explicitly specify the hit molecule output file format by providing one 
    of the supported file-extensions (without leading dot!) as argument.
    
    Supported Output Formats:
     - JME Molecular Editor String (\*.jme)
     - MDL Structure-Data Format (\*.sdf, \*.sd)
     - MDL Molfile (\*.mol)
     - Daylight SMILES Format (\*.smi)
     - Daylight SMARTS Format (\*.sma)
     - IUPAC International Chemical Identifier (\*.inchi, \*.ichi)
     - Native CDPL Format (\*.cdf)
     - Tripos Sybyl MOL2 Format (\*.mol2)
     - Atomic Coordinates XYZ Format (\*.xyz)
     - Chemical Markup Language Format (\*.cml)
     - GZip-Compressed MDL Structure-Data Format (\*.sdf.gz, \*.sd.gz, \*.sdz)
     - BZip2-Compressed MDL Structure-Data Format (\*.sdf.bz2, \*.sd.bz2)
     - GZip-Compressed Native CDPL Format (\*.cdf.gz)
     - BZip2-Compressed Native CDPL Format (\*.cdf.bz2)
     - GZip-Compressed Daylight SMILES Format (\*.smi.gz)
     - BZip2-Compressed Daylight SMILES Format (\*.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 Format (\*.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 Format (\*.mol2.bz2)
     - GZip-Compressed Atomic Coordinates XYZ Format (\*.xyz.gz)
     - BZip2-Compressed Atomic Coordinates XYZ Format (\*.xyz.bz2)
     - GZip-Compressed Chemical Markup Language Format (\*.cml.gz)
     - BZip2-Compressed Chemical Markup Language Format (\*.cml.bz2)
     - Brookhaven Protein Data Bank Entry Format (\*.pdb, \*.ent)
     - Macromolecular Transmission Format (\*.mmtf)
     - Macromolecular Crystallographic Information File Format (\*.mmcif, \*.cif)
     - GZip-Compressed Brookhaven Protein Data Bank Entry Format (\*.pdb.gz, \*.ent.gz)
     - BZip2-Compressed Brookhaven Protein Data Bank Entry Format (\*.pdb.bz2, \*.ent.bz2)
     - GZip-Compressed Macromolecular Transmission Format (\*.mmtf.gz)
     - BZip2-Compressed Macromolecular Transmission Format (\*.mmtf.bz2)
     - GZip-Compressed Macromolecular Crystallographic Information File Format (\*.mmcif.gz, \*.cif.gz)
     - BZip2-Compressed Macromolecular Crystallographic Information File Format (\*.mmcif.bz2, \*.cif.bz2)
     - Pharmacophore Screening Database Format (\*.psd)
    
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file (because missing, misleading or not supported).

  --ecfp-size arg

    Size of the generated fingerprint (default: 8191).

  --ecfp-radius arg

    Atom environment radius in number of bonds (default: 2 -> ECFP4).

  --ecfp-inc-H arg

    Whether or not to include hydrogen atoms (default: false).

  --ecfp-inc-chirality arg

    Whether or not to regard the chriality of stereo atoms(default: false).

  --daylight-size arg

    Size of the generated fingerprint (default: 8191).

  --daylight-min-path-len arg

    Minimum considered atom path length in number of bonds (default: 0).

  --daylight-max-path-len arg

    Maximum considered atom path length in number of bonds (default: 5).

  --daylight-inc-H arg

    Whether or not to include hydrogen atoms (default: false).

  --pharm-2d-size arg

    Size of the generated fingerprint (default: 8191).

  --pharm-2d-min-tuple-size arg

    Minimum feature tuple size (default: 1).

  --pharm-2d-max-tuple-size arg

    Maximum feature tuple size (default: 3).

  --pharm-2d-bin-size arg

    Feature distance bin size (default: 2.0, must be > 0).

  --pharm-3d-size arg

    Size of the generated fingerprint (default: 8191).

  --pharm-3d-min-tuple-size arg

    Minimum feature tuple size (default: 1).

  --pharm-3d-max-tuple-size arg

    Maximum feature tuple size (default: 3).

  --pharm-3d-bin-size arg

    Feature distance bin size (default: 3.0, must be > 0).

  --tversky-weight-a arg

    Weight factor of the query molecule fingerprint exclusive bits (default: 1.0).

  --tversky-weight-b arg

    Weight factor of the database molecule fingerprint exclusive bits (default: 0.0).
