Database Cleaning
=================

The script *clean_mol_db.py* reads molecules from an input file, performs (optional) preprocessing,
and then writes only those molecules that fulfill particular user-defined criteria to an output file.

**Synopsis**

  :program:`python` *clean_mol_db.py* [-h] -i <file> -o <file> [-d <file>] [-s] [-c] [-x <element list>] [-a <element list>] [-m <element count list>] [-M <element count list>] [-v <0|1|2|3>]

**Mandatory options**

 -i <file>
 
    Input molecule file

 -o <file>

    Output molecule file

**Other options**

 -h, --help

    Show help message and exit
  
 -d <file>

    Discarded molecule output file
    
 -s

    Keep only the largest molecule component (default: false)
    
 -c

    Minimize the number of charged atoms (default: false) by
    protonation/deprotonation and charge equalization
    
 -x <element list>

    List of excluded chem. elements (default: no elements are excluded)
    
 -a <element list>

    List of allowed chem. elements (default: all elements are allowed)
    
 -m <element count list>
  
    Minimum chem. element specific atom counts (default: no count limits)
    
 -M <element count list>

    Maximum chem. element specific atom counts (default: no count limits)
    
 -v <0|1|2|3>

    Verbosity level (default: 1; 0 -> no console output,
    1 -> print summary, 2 -> verbose, 3 -> extra verbose)

The options *-a* and *-x* both require a list of chemical elements as argument.
Chemical element lists are specified in the form *<S>,...,<S>* where *<S>* is
the symbol of a chemical element or generic atom type. Supported generic
types are:

======  =======
Symbol  Meaning
======  =======
M       any metal
MH      any metal or hydrogen
A       any element except hydrogen
AH      any element
\*      any element (equivalent to AH)
X       any halogen
XH      any halogen or hydrogen
Q       any element except hydrogen and carbon
QH      any element except carbon
======  =======

The options *-m* and *-M* both require a list of chemical element counts as argument.
Chemical element counts are specified in the form *<S>:<N>,...,<S>:<N>* where *<S>* is
the symbol of a chemical element or generic atom type (see above) and *<N>* is
the corresponding minimum or maximum count. If the count part is omitted and only *<S>*
gets specified then the count is assumed to be ``1``.

**Example usage**

.. code-block:: shell

   python clean_mol_db.py -i <path/to/molecule/input/file> -o <path/to/molecule/output/file> -a C,H,N,O,S,P,F,Cl,Br,I -m C,A:3 -M F:9 -c -s

When executed as shown, the script will perform the following operations on each
read input molecule (in the order listed):

#. Reduction of the number of charged atoms (if any and if possible)
#. Removal of all but the largest molecular graph component (only if multi-comp. molecule)
#. Check whether the chem. element of each atom of the working molecule (= result of prev. steps) is either C, H, N, O, S, P, F, Cl, Br, or I.
#. Check whether the atom list of the working molecule contains at least one carbon and three heavy atoms
#. Check whether the atom list of the working molecule contains not more than 9 fluorine atoms

The first check that fails leads to a rejection of the molecule. Working molecules that pass all checks will
be written to the specified output file.
   
**Code**

.. literalinclude:: /downloads/clean_mol_db.py
   :language: python
   :linenos:
   :lines: 21-

:download:`Download source file</downloads/clean_mol_db.py>`
