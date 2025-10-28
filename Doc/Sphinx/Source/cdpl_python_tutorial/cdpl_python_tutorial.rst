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
    
    mol




.. parsed-literal::

    <CDPL.Chem._chem.BasicMolecule at 0x7fd0b6cf8b30>



Display of the parsed molecule:

.. code:: ipython3

    import CDPL.Vis
    
    display(mol)



.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_8_0.svg


.. code:: ipython3

    mol.removeAtom(0)

.. code:: ipython3

    mol




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_10_0.svg



