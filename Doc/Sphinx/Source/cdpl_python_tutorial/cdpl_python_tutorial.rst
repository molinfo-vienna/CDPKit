Installing the CDPL Python bindings
===================================

.. code:: ipython3

    pip install cdpkit

Processing Molecules
====================

The data structures for the in-memory representation of molecules as
well as functionality for their processing are located in package
CDPL.Chem

.. code:: ipython3

    import CDPL.Chem as Chem

First example: parsing a SMILES string

.. code:: ipython3

    mol = Chem.parseSMILES('c1ccccc1')

Display of the parsed molecule:

.. code:: ipython3

    import CDPL.Vis
    
    display(mol)

