Installing the CDPL Python bindings
===================================

To be able to follow this tutorial the *CDPL Python* bindings need to be installed on your computer. The most straightforward way to accomplish this task is to install the latest official release deposited on `PyPI <https://pypi.org/project/CDPKit>`_ using the :program:`pip` command as follows:

.. code:: ipython3

    pip install cdpkit

Other possible options for installing the Python bindings can be found `here <https://cdpkit.org/installation.html>`_.

Working with molecules
======================

The primary data structure for the in-memory representation of molecules (class `Chem.BasicMolecule <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BasicMolecule.html>`_) as well as all basic processing functionality is located in package `CDPL.Chem <https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html>`_. 
Importing the package as shown below will make all contained classes and functions accessible via the prefix *Chem.\**.

.. code:: ipython3

    import CDPL.Chem as Chem

An initally empty molecule object can then be created as follows:

.. code:: ipython3

    mol = Chem.BasicMolecule()

The number of (explicit) atoms can be queried either by acessing the property `numAtoms <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1AtomContainer.html>`_ or by calling the method `getNumAtoms() <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1AtomContainer.html#aa18ef7240d27820c882998d8c8dbdfd7>`_:

.. code:: ipython3

    mol.numAtoms
    # or
    mol.getNumAtoms()




.. parsed-literal::

    0



In the same manner, the number of bonds can be retrieved by:

.. code:: ipython3

    mol.numBonds
    # or
    mol.getNumBonds()




.. parsed-literal::

    0



Atoms are created by calling the method `addAtom() <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html#ab998b55e7f56b00f47e3acbfa4511f2e>`_:

.. code:: ipython3

    a = mol.addAtom()

The method returns a `Chem.BasicAtom <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BasicAtom.html>`_ object which is owned by the creating *Chem.BasicMolecule* instance *mol*. The created atom does not yet possess any chemical properties like element, formal charge, and so on. The values of these properties need to be set explicitly by invoking dedicated property functions which take the atom and desired value of the property as arguments. For example

.. code:: ipython3

    Chem.setType(a, Chem.AtomType.C)

will set the type property of the atom to the atomic number of carbon. The value of the type property can be retrieved by the associated function

.. code:: ipython3

    Chem.getType(a)




.. parsed-literal::

    6



In a similar fashion, bonds are created by calling the method `addBond() <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html#acd42f15d874185b4eea2cf497a509ea6>`_ 
which expects the indices (zero-based) of the two atoms to connect as arguments:

.. code:: ipython3

    Chem.setType(mol.addAtom(), Chem.AtomType.C) # add second carbon atom
    
    b = mol.addBond(0, 1)

The method returns a `Chem.BasicBond <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BasicBond.html>`_ object which is also owned by the creating *Chem.BasicMolecule* instance *mol*. As with atoms, the created bond does not yet have any properties set. To set the bond order to a value of 2 (= double bond) the property function `Chem.setOrder() <https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#ab4460ac3bac716de49c744c52d980181>`_ needs to be invoked:

.. code:: ipython3

    Chem.setOrder(b, 2)

A previously set bond order property value can be accessed by the accompanying getter function `Chem.getOrder() <https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#a2a3103e8e0338219a5703da063cd3ef5>`_:

.. code:: ipython3

    Chem.getOrder(b)




.. parsed-literal::

    2


