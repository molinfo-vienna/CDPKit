.. index:: single: CLI Applications; Substructure Searching
           single: Molecules; Substructure Matching

subsearch
=========

Performs substructure searching on a set of input molecules.

Synopsis
--------

  :program:`subsearch` [-hVvp] [-c arg] [-l arg] [-n arg] [-I arg] [-O arg] [-N arg] [-e arg] -i arg [arg]... -o arg -s arg [arg]...

Mandatory options
-----------------

  -i [ --input ] arg

    Specifies one or more molecule input file(s) to be searched for matching substructures.
    
    Supported Input Formats:
     - JME Molecular Editor String (.jme)
     - MDL Structure-Data Format (.sdf, .sd)
     - MDL Molfile (.mol)
     - Daylight SMILES Format (.smi)
     - Daylight SMARTS Format (.sma)
     - IUPAC International Chemical Identifier (.inchi, .ichi)
     - Native CDPL Format (.cdf)
     - Tripos Sybyl MOL2 Format (.mol2)
     - Atomic Coordinates XYZ Format (.xyz)
     - Chemical Markup Language Format (.cml)
     - GZip-Compressed MDL Structure-Data Format (.sdf.gz, .sd.gz, .sdz)
     - BZip2-Compressed MDL Structure-Data Format (.sdf.bz2, .sd.bz2)
     - GZip-Compressed Native CDPL Format (.cdf.gz)
     - BZip2-Compressed Native CDPL Format (.cdf.bz2)
     - GZip-Compressed Daylight SMILES Format (.smi.gz)
     - BZip2-Compressed Daylight SMILES Format (.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 Format (.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 Format (.mol2.bz2)
     - GZip-Compressed Atomic Coordinates XYZ Format (.xyz.gz)
     - BZip2-Compressed Atomic Coordinates XYZ Format (.xyz.bz2)
     - GZip-Compressed Chemical Markup Language Format (.cml.gz)
     - BZip2-Compressed Chemical Markup Language Format (.cml.bz2)

  -o [ --output ] arg

    Specifies the output file where the matching molecules will be stored.
    
    Supported Output Formats:
     - JME Molecular Editor String (.jme)
     - MDL Structure-Data Format (.sdf, .sd)
     - MDL Molfile (.mol)
     - Daylight SMILES Format (.smi)
     - Daylight SMARTS Format (.sma)
     - IUPAC International Chemical Identifier (.inchi, .ichi)
     - Native CDPL Format (.cdf)
     - Tripos Sybyl MOL2 Format (.mol2)
     - Atomic Coordinates XYZ Format (.xyz)
     - Chemical Markup Language Format (.cml)
     - GZip-Compressed MDL Structure-Data Format (.sdf.gz, .sd.gz, .sdz)
     - BZip2-Compressed MDL Structure-Data Format (.sdf.bz2, .sd.bz2)
     - GZip-Compressed Native CDPL Format (.cdf.gz)
     - BZip2-Compressed Native CDPL Format (.cdf.bz2)
     - GZip-Compressed Daylight SMILES Format (.smi.gz)
     - BZip2-Compressed Daylight SMILES Format (.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 Format (.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 Format (.mol2.bz2)
     - GZip-Compressed Atomic Coordinates XYZ Format (.xyz.gz)
     - BZip2-Compressed Atomic Coordinates XYZ Format (.xyz.bz2)
     - GZip-Compressed Chemical Markup Language Format (.cml.gz)
     - BZip2-Compressed Chemical Markup Language Format (.cml.bz2)

  -s [ --substructs ] arg

    Substructure SMARTS pattern(s).

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

  -n [ --nm-output ] arg

    Specifies the output file where the non-matching molecules will be stored.
    
    Supported Output Formats:
     - JME Molecular Editor String (.jme)
     - MDL Structure-Data Format (.sdf, .sd)
     - MDL Molfile (.mol)
     - Daylight SMILES Format (.smi)
     - Daylight SMARTS Format (.sma)
     - IUPAC International Chemical Identifier (.inchi, .ichi)
     - Native CDPL Format (.cdf)
     - Tripos Sybyl MOL2 Format (.mol2)
     - Atomic Coordinates XYZ Format (.xyz)
     - Chemical Markup Language Format (.cml)
     - GZip-Compressed MDL Structure-Data Format (.sdf.gz, .sd.gz, .sdz)
     - BZip2-Compressed MDL Structure-Data Format (.sdf.bz2, .sd.bz2)
     - GZip-Compressed Native CDPL Format (.cdf.gz)
     - BZip2-Compressed Native CDPL Format (.cdf.bz2)
     - GZip-Compressed Daylight SMILES Format (.smi.gz)
     - BZip2-Compressed Daylight SMILES Format (.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 Format (.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 Format (.mol2.bz2)
     - GZip-Compressed Atomic Coordinates XYZ Format (.xyz.gz)
     - BZip2-Compressed Atomic Coordinates XYZ Format (.xyz.bz2)
     - GZip-Compressed Chemical Markup Language Format (.cml.gz)
     - BZip2-Compressed Chemical Markup Language Format (.cml.bz2)

  -I [ --input-format ] arg

    Allows to explicitly specify the format of the input file(s) by providing one of 
    the supported file-extensions (without leading dot!) as argument.
    
    Supported Input Formats:
     - JME Molecular Editor String (.jme)
     - MDL Structure-Data Format (.sdf, .sd)
     - MDL Molfile (.mol)
     - Daylight SMILES Format (.smi)
     - Daylight SMARTS Format (.sma)
     - IUPAC International Chemical Identifier (.inchi, .ichi)
     - Native CDPL Format (.cdf)
     - Tripos Sybyl MOL2 Format (.mol2)
     - Atomic Coordinates XYZ Format (.xyz)
     - Chemical Markup Language Format (.cml)
     - GZip-Compressed MDL Structure-Data Format (.sdf.gz, .sd.gz, .sdz)
     - BZip2-Compressed MDL Structure-Data Format (.sdf.bz2, .sd.bz2)
     - GZip-Compressed Native CDPL Format (.cdf.gz)
     - BZip2-Compressed Native CDPL Format (.cdf.bz2)
     - GZip-Compressed Daylight SMILES Format (.smi.gz)
     - BZip2-Compressed Daylight SMILES Format (.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 Format (.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 Format (.mol2.bz2)
     - GZip-Compressed Atomic Coordinates XYZ Format (.xyz.gz)
     - BZip2-Compressed Atomic Coordinates XYZ Format (.xyz.bz2)
     - GZip-Compressed Chemical Markup Language Format (.cml.gz)
     - BZip2-Compressed Chemical Markup Language Format (.cml.bz2)
    
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file(s) (because missing, misleading or not supported).

  -O [ --output-format ] arg

    Allows to explicitly specify the matching molecule output format by providing one 
    of the supported file-extensions (without leading dot!) as argument.
    
    Supported Output Formats:
     - JME Molecular Editor String (.jme)
     - MDL Structure-Data Format (.sdf, .sd)
     - MDL Molfile (.mol)
     - Daylight SMILES Format (.smi)
     - Daylight SMARTS Format (.sma)
     - IUPAC International Chemical Identifier (.inchi, .ichi)
     - Native CDPL Format (.cdf)
     - Tripos Sybyl MOL2 Format (.mol2)
     - Atomic Coordinates XYZ Format (.xyz)
     - Chemical Markup Language Format (.cml)
     - GZip-Compressed MDL Structure-Data Format (.sdf.gz, .sd.gz, .sdz)
     - BZip2-Compressed MDL Structure-Data Format (.sdf.bz2, .sd.bz2)
     - GZip-Compressed Native CDPL Format (.cdf.gz)
     - BZip2-Compressed Native CDPL Format (.cdf.bz2)
     - GZip-Compressed Daylight SMILES Format (.smi.gz)
     - BZip2-Compressed Daylight SMILES Format (.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 Format (.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 Format (.mol2.bz2)
     - GZip-Compressed Atomic Coordinates XYZ Format (.xyz.gz)
     - BZip2-Compressed Atomic Coordinates XYZ Format (.xyz.bz2)
     - GZip-Compressed Chemical Markup Language Format (.cml.gz)
     - BZip2-Compressed Chemical Markup Language Format (.cml.bz2)
    
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file (because missing, misleading or not supported).

  -N [ --nm-output-format ] arg

    Allows to explicitly specify the non-matching molecule output format by providing 
    one of the supported file-extensions (without leading dot!) as argument.
    
    Supported Output Formats:
     - JME Molecular Editor String (.jme)
     - MDL Structure-Data Format (.sdf, .sd)
     - MDL Molfile (.mol)
     - Daylight SMILES Format (.smi)
     - Daylight SMARTS Format (.sma)
     - IUPAC International Chemical Identifier (.inchi, .ichi)
     - Native CDPL Format (.cdf)
     - Tripos Sybyl MOL2 Format (.mol2)
     - Atomic Coordinates XYZ Format (.xyz)
     - Chemical Markup Language Format (.cml)
     - GZip-Compressed MDL Structure-Data Format (.sdf.gz, .sd.gz, .sdz)
     - BZip2-Compressed MDL Structure-Data Format (.sdf.bz2, .sd.bz2)
     - GZip-Compressed Native CDPL Format (.cdf.gz)
     - BZip2-Compressed Native CDPL Format (.cdf.bz2)
     - GZip-Compressed Daylight SMILES Format (.smi.gz)
     - BZip2-Compressed Daylight SMILES Format (.smi.bz2)
     - GZip-Compressed Tripos Sybyl MOL2 Format (.mol2.gz)
     - BZip2-Compressed Tripos Sybyl MOL2 Format (.mol2.bz2)
     - GZip-Compressed Atomic Coordinates XYZ Format (.xyz.gz)
     - BZip2-Compressed Atomic Coordinates XYZ Format (.xyz.bz2)
     - GZip-Compressed Chemical Markup Language Format (.cml.gz)
     - BZip2-Compressed Chemical Markup Language Format (.cml.bz2)
    
    This option is useful when the format cannot be auto-detected from the actual extension 
    of the file (because missing, misleading or not supported).

  -e [ --match-expr ] arg

    Allows to define a complex substructure query in the form of a logical expression 
    that specifies how the individual SMARTS pattern matching results have to be merged 
    into a single overall molecule matching result. When no expression is specified 
    the default logic is an OR combination. That is, at least one of the given SMARTS 
    patterns has to match for a positive molecule matching result.
    
    Supported logical operations:
     - AND (symbol: &)
     - OR  (symbol: \|)
     - XOR (symbol: ^)
     - NOT (symbol: !)
    
    Parentheses can be used for grouping without limit on nesting depth. Any whitespace 
    characters will be stripped before expression evaluation and thus can be used freely.
    SMARTS patterns specified by option -s are referenced by positive integer numbers 
    >= 1. The numeric id of a pattern corresponds to its position in the argument list 
    of option -s.
    
    Example: -e '!(1&(2^3)) | 4'
