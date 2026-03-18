Installing the CDPL Python Bindings
===================================

To be able to follow this tutorial the *CDPL Python* bindings have to be installed on your computer. The most straightforward way to accomplish this task is to install the latest official release deposited on `PyPI`_ using the :program:`pip` command as follows:

.. code:: ipython3

    pip install cdpkit

Other ways to install the Python bindings are described in section `Installation`_.

CDPL Package Overview
=====================

The *CDPL* comprises several sub-packages each providing functionality related to a certain aspect of chem- and pharmacoinformatics. The following table lists all available sub-packages 
together with a brief description of the kind of functionality they provide:

.. list-table::
   :widths: 15 30
   :header-rows: 1

   * - Package
     - Contents
   * - `CDPL.Base`_
     - Core classes defining a software framework for functionality implemented in the other *CDPL* packages
   * - `CDPL.Util`_
     - Implementations of useful general purpose algorithms, containers, function objects and free functions
   * - `CDPL.Math`_
     - Data structures, algorithms and functions related to mathematics
   * - `CDPL.Chem`_
     - Infrastructure for the in-memory representation, I/O and basic processing of molecular
       structures and reactions
   * - `CDPL.MolProp`_
     - Functionality for the calculation/prediction of physicochemical and topological atom, bond and molecule properties
   * - `CDPL.Biomol`_
     - Functionality for the I/O and processing of biological macromolecules
   * - `CDPL.Descr`_
     - Functionality for the generation and processing of pharmacophore and molecule descriptors
   * - `CDPL.Pharm`_
     - Infrastructure for pharmacophore representation, I/O, perception, processing, alignment
       and screening
   * - `CDPL.Shape`_
     - Infrastructure for Gaussian volume-based molecular shape representation, processing, alignment
       and screening
   * - `CDPL.ForceField`_
     - Implementation of MMFF94(s) for molecule conformer energy calculation and 3D structure optimization
   * - `CDPL.ConfGen`_
     - Functionality for molecule 3D structure and conformer ensemble generation
   * - `CDPL.Grid`_
     - Infrastructure for grid data storage, I/O and processing
   * - `CDPL.GRAIL`_
     - Functionality for the generation of GRAIL data sets :cite:`doi:10.1021/acs.jctc.8b00495` and GRADE
       descriptors :cite:`doi:10.1021/acs.jcim.4c01902`
   * - `CDPL.Vis`_
     - Functionality for molecule, reaction and 3D pharmacophore visualization

Basic Concepts
==============

Dynamic Properties
------------------

The *CDPL* stores properties associated with certain types of data like molecules, atoms, bonds, pharmacophores, etc. not as ordinary data members of the implementing classes
but as *key:value* pairs in a dictionary (similar to the `__dict__`_ attribute of Python objects). This design decision was made due to several advantages of this approach:

* Flexibility and extensibility: new properties can be defined at runtime by user code
* Class instance specific property values can be stored directly in the dictionary of the instance they are
  associated with, no external accompanying data structures are required for storing user-defined properties
  unknown to the *CDPL*
* It can be easily determined whether the value of a particular property is available or not by checking if
  the dictionary contains a corresponding entry. C++ class data members (note that *CDPL* Python objects just wrap
  corresponding C++ class instances!) exist in memory after a class instance has been constructed and from that
  point on have a value. This is particularly problematic for properties that cannot be assigned a reasonable
  default value.

All *CDPL* classes supporting this kind of dynamic property storage are derived from class 
`CDPL.Base.PropertyContainer`_ which provides methods for property value lookup, storage, removal, iteration, existence testing and counting. Properties are identified by unique keys of type `CDPL.Base.LookupKey`_ 
that are created on-the-fly during the *CDPL* initialization phase. Keys of pre-defined *CDPL* properties are exported as static attributes of classes that follow the naming scheme *CDPL.<PN>.<CN>Property*. 
*<PN>* denotes the *CDPL* sub-package name (see table above) and *<CN>* is the name of a child class of `CDPL.Base.PropertyContainer`_ for which these properties have been defined (example: atom property keys 
accessible via class `CDPL.Chem.AtomProperty`_). Property values virtually can be of any type and get stored in 
the dictionary as instances of the data wrapper class `CDPL.Base.Any`_. 

Since `CDPL.Base.PropertyContainer`_ methods acting upon a particular property always demand the key of the property as argument and setter/getter methods in addition require knowledge of the value type, corresponding code
is not only tedious to write but also hard to read and error prone. Therefore, each *CDPL* sub-package that introduces properties also provides four free functions (at package level) per property that encapsulate the 
low-level `CDPL.Base.PropertyContainer`_ method calls. These functions internally not only specify the correct property key and value type but also constrain the type of the `CDPL.Base.PropertyContainer`_  
subclass the property has been introduced for. `CDPL.Chem.getOrder()`_, `CDPL.Chem.setOrder()`_, `CDPL.Chem.hasOrder()`_ and `CDPL.Chem.clearOrder()`_ represent an example of such four functions that are provided
for the property `CDPL.Chem.BondProperty.ORDER`_ of `CDPL.Chem.Bond`_ instances using integer as value type.
Using property getter functions (like `CDPL.Chem.getOrder()`_) has the additional benefit that they will, if one 
has been defined, automatically return a default value for unset properties. Defined property default values are exported and accessible as static attributes of classes that follow the naming scheme 
*CDPL.<PN>.<CN>PropertyDefault* (example: `CDPL.Chem.BondPropertyDefault`_; for the meaning of *<PN>* and *<CN>* 
see text above). 

Control-Parameters
------------------

Control-parameters are used for the runtime configuration of arbitrary functionality in a generic, flexible and functionality independent way (in the *CDPL* mainly used by the data I/O and visualization code).
The implementation and usage of the control-parameter infrastructure largely parallels the one for dynamic properties: 

* Control-parameters are identified via unique instances of class `CDPL.Base.LookupKey`_ 
* Values can be of any type and are stored in a dictionary as `CDPL.Base.Any`_ objects
* Keys of pre-defined control-parameters are exported as static attributes of classes that follow the naming
  scheme *CDPL.<PN>.ControlParameter* (<PN> = *CDPL* sub-package name, example: `CDPL.Chem.ControlParameter`_)
* Four convenience functions are provided for each control-parameter introduced by a package

*CDPL* classes employing the control-parameter infrastructure (directly or indirectly) are derived from class
`CDPL.Base.ControlParameterContainer`_. The class provides methods which are similar to those found in 
`CDPL.Base.PropertyContainer`_ but also offers methods (`setParent()`_ and `getParent()`_) that allow to connect
`CDPL.Base.ControlParameterContainer`_ instances in a parent-child manner. This way tree-like hierarchies of 
`CDPL.Base.ControlParameterContainer`_ instances for resolving parameter value requests can be built. 
If a requested parameter value is not stored in a given container, the request gets automatically forwarded to the
registered parent container which may again forward the request to its parent until a value is found or the root of
the tree has been reached. Furthermore, methods are provided which allow the registration of user-defined functions
or function objects that get called on events such as parameter value change (methods 
`registerParameterChangedCallback()`_ and `unregisterParameterChangedCallback()`_), parameter value removal 
(methods `registerParameterRemovedCallback()`_ and `unregisterParameterRemovedCallback()`_) and parent change 
(methods `registerParentChangedCallback()`_ and `unregisterParentChangedCallback()`_).

A notable difference between dynamic properties and control-parameters is that the latter always possess a default value which gets returned by the associated getter function if a parameter value has not been explicitly set. 
Control-parameter default values are exported and accessible as static attributes of classes that follow the 
naming scheme *CDPL.<PN>.ControlParameterDefault* (*<PN>* = *CDPL* sub-package name; example: 
`CDPL.Chem.ControlParameterDefault`_). 

Data I/O Framework
------------------

Classes implementing the input/output of data of a certain type in a particular format (e.g. molecular structures in SD-file format) are derived from abstract base classes that follow the naming scheme 
*CDPL.<PN>.<DT>ReaderBase* and  *CDPL.<PN>.<DT>WriterBase*, respectively. *<PN>* denotes the *CDPL* sub-package
name and *<DT>* is the name of the data type to read or write (e.g. classes `CDPL.Chem.MoleculeReaderBase`_ and
`CDPL.Chem.MolecularGraphWriterBase`_).
These base classes are all derived from the abstract class `CDPL.Base.DataIOBase`_ which itself is derived from `CDPL.Base.ControlParameterContainer`_. Instances of concrete classes implementing the I/O of data in a particular  format thus support the configuration of their runtime behavior by control-parameters (see 
`CDPL.Chem.ControlParameter`_ for examples). The names of the format-specific classes all follow the scheme 
*CDPL.<PN>.<FID><DT>Reader* and *CDPL.<PN>.<FID><DT>Writer*, respectively where *<PN>* denotes the *CDPL* sub-package name, *<FID>* is a format identifier (usually a characteristic file extension) and *<DT>* is the name of 
the data type to read or write (e.g. `CDPL.Chem.SDFMoleculeReader`_ and `CDPL.Chem.SDFMolecularGraphWriter`_). 

Data reader classes all expect an instance of class `CDPL.Base.IStream`_ and data writer classes an instance of `CDPL.Base.OStream`_ as argument to their constructor. 
These stream-based I/O classes represent abstract storage devices which allow the same code to handle I/O to files, in-memory strings, or custom adaptor devices that perform arbitrary operations (e.g. compression) on the fly.
Concrete types of storage devices are implemented by dedicated subclasses of `CDPL.Base.IStream`_ and `CDPL.Base.OStream`_  such as class `CDPL.Base.FileIOStream`_ for file I/O and `CDPL.Base.StringIOStream`_ for in-memory string data I/O, respectively. 

Since files represent the most dealt-with kind of data storage, file I/O-specific variants of reader/writer classes 
are provided that make reading/writing data from/to files more convenient. These classes follow the naming scheme 
*CDPL.<PN>.File<FID><DT>Reader* and *CDPL.<PN>.File<FID><DT>Writer* (for the meaning of *<PN>*, *<FID>* and 
*<DT>* see text above). Instead of an instance of `CDPL.Base.IStream`_/`CDPL.Base.OStream`_ they accept the path 
to a file as constructor argument and thus circumvent the need to explicitly create and manage instances of class 
`CDPL.Base.FileIOStream`_.

Each data format implemented by the *CDPL* is described by an instance of class `CDPL.Base.DataFormat`_ which
stores and gives access to relevant format-specific information such as common file-extensions or mime-type. 
Pre-defined data format descriptors are exported as static attributes of classes following the naming scheme
*CDPL.<PN>.DataFormat* where *<PN>* is the name of the *CDPL* sub-package implementing the format (e.g. `CDPL.Chem.DataFormat`_).

The link between a `CDPL.Base.DataFormat`_ instance describing a particular data format and associated classes implementing the reading/writing of data in this format gets established by dedicated input- and output-handler classes. These classes provide factory methods to create a reader/writer class instance for a given file path or `CDPL.Base.IStream`_/`CDPL.Base.OStream`_ instance and follow the naming scheme 
*CDPL.<PN>.<FID><DT>InputHandler* and *CDPL.<PN>.<FID><DT>OutputHandler*, respectively (for the meaning of *<PN>*, 
*<FID>* and *<DT>* see text above; examples: `CDPL.Chem.SDFMoleculeInputHandler`_, 
`CDPL.Chem.SMILESMolecularGraphOutputHandler`_). For each data format supported by the *CDPL* an input- and/or output-handler class instance is registered at a data type-specific singleton class named 
*CDPL.<PN>.<DT>IOManager* (for the meaning of *<PN>* and *<DT>* see text above; example: 
`CDPL.Chem.MoleculeIOManager`_). Amongst others, the I/O manager classes provide methods to lookup a registered handler instance for a given file extension, mime-type or `CDPL.Base.DataFormat`_ object. This way it is possible to, e.g., write code that creates a reader class instance for the input of data from a file where the actual data format is determined lateron at runtime.  
In order to facilitate the writing of data format-independent code the *CDPL* provides special reader and writer classes that perform the runtime lookup of a suitable input/output handler and reader/writer class 
instantiation automatically. The classes follow the naming scheme *CDPL.<PN>.<DT>Reader* and *CDPL.<PN>.<DT>Writer*, respectively (examples: `CDPL.Chem.MoleculeReader`_ and `CDPL.Chem.MolecularGraphWriter`_). The constructors of the classes expect the data source/sink to be provided as a `CDPL.Base.IStream`_/`CDPL.Base.OStream`_ instance or specified as path to a file. If a file path is specified it is attempted to deduce the data format from the file name's extension. Optionally, a 
characteristic file extension string or a `CDPL.Base.DataFormat`_ instance can be provided in case the file extension is missing or unknown to the *CDPL*. If the data source/sink is provided as a `CDPL.Base.IStream`_/`CDPL.Base.OStream`_ instance then the explicit specification of the data format is mandatory.

Working with Molecules
======================

In-memory Representation of Molecular Structures
------------------------------------------------

The *CDPL* models molecular structures as undirected graphs where atoms represent the graph nodes and bonds the edges. Concrete data structures for the in-memory representation of atoms, 
bonds and molecular graphs implement a hierarchy of interfaces (abstract classes) that specify all necessary methods for common operations like atom/bond addition, removal, access, membership testing, counting, and so on. 
 
The following table provides an overview of the most relevant interfaces and data structures provided by the *CDPL* for molecular data representation and processing:
   
.. list-table::
   :widths: 15 12 30 30
   :header-rows: 1

   * - Class Name
     - Class Type
     - Parent Class(es)
     - Description
   * - `CDPL.Chem.Entity3D`_
     - Interface
     - `CDPL.Base.PropertyContainer`_
     - Represents an arbitrary entity that can have a position in 3D space
   * - `CDPL.Chem.Entity3DContainer`_
     - Interface
     - None
     - Represents a collection of `CDPL.Chem.Entity3D`_ instances and specifies methods for read-only
       instance access and querying their number
   * - `CDPL.Chem.AtomContainer`_
     - Interface
     - `CDPL.Chem.Entity3DContainer`_
     - Represents a collection of `CDPL.Chem.Atom`_ instances and specifies methods for read-only
       instance access, querying their number, collection membership testing and ordering
   * - `CDPL.Chem.BondContainer`_
     - Interface
     - None
     - Represents a collection of `CDPL.Chem.Bond`_ instances and specifies methods for read-only
       instance access, querying their number, collection membership testing and ordering
   * - `CDPL.Chem.Atom`_
     - Interface
     - `CDPL.Chem.Entity3D`_, `CDPL.Chem.AtomContainer`_, `CDPL.Chem.BondContainer`_
     - Represents an atom in molecular structures/graphs and provides additional connectivity
       and ownership related methods
   * - `CDPL.Chem.BasicAtom`_
     - Implementation
     - `CDPL.Chem.Atom`_
     - Default implementation of the `CDPL.Chem.Atom`_ interface
   * - `CDPL.Chem.Bond`_
     - Interface
     - `CDPL.Chem.AtomContainer`_, `CDPL.Base.PropertyContainer`_
     - Represents a bond connecting two atoms in molecular structures/graphs, specifies additional connectivity
       and ownership related methods
   * - `CDPL.Chem.BasicBond`_
     - Implementation
     - `CDPL.Chem.Bond`_
     - Default implementation of the `CDPL.Chem.Bond`_ interface
   * - `CDPL.Chem.MolecularGraph`_
     - Interface
     - `CDPL.Chem.AtomContainer`_, `CDPL.Chem.BondContainer`_, `CDPL.Base.PropertyContainer`_
     - Represents an arbitrary molecular graph described by lists of `CDPL.Chem.Atom`_ and  
       `CDPL.Chem.Bond`_ instances
   * - `CDPL.Chem.Molecule`_
     - Interface
     - `CDPL.Chem.MolecularGraph`_
     - Extends the `CDPL.Chem.MolecularGraph`_ interface by methods for atom and bond creation as well as methods 
       for assignment of and merging with other molecular graphs
   * - `CDPL.Chem.BasicMolecule`_
     - Implementation
     - `CDPL.Chem.Molecule`_
     - Default implementation of the `CDPL.Chem.Molecule`_ interface
   * - `CDPL.Chem.Fragment`_
     - Implementation
     - `CDPL.Chem.MolecularGraph`_
     - Stores references (not copies!) to `CDPL.Chem.Atom`_ and `CDPL.Chem.Bond`_ objects owned/managed by one or 
       more `CDPL.Chem.Molecule`_ instances

Representation of Molecule Substructures
----------------------------------------

From scratch, a molecular graph can only be constructed via an instance of class `CDPL.Chem.Molecule`_. 
Adding atoms and bonds by calling dedicated methods (see next section) will create new 
`CDPL.Chem.Atom`_ and `CDPL.Chem.Bond`_ objects which from that point on are owned and managed by the 
creating `CDPL.Chem.Molecule`_ instance. For the specification of arbitrary sets of `CDPL.Chem.Atom`_ and 
`CDPL.Chem.Bond`_  objects that belong to one or more `CDPL.Chem.Molecule`_ instance(s) the `CDPL.Chem`_ package provides the 
class `CDPL.Chem.Fragment`_. Like `CDPL.Chem.Molecule`_, this class also offers methods for adding 
atoms and bonds except that the methods of `CDPL.Chem.Fragment`_ expect existing `CDPL.Chem.Atom`_ or 
`CDPL.Chem.Bond`_ instances as argument. These do not get stored as copies but as light-weight references to the 
original instances which can be retrieved lateron by methods for atom/bond access.
`CDPL.Chem.Molecule`_ as well as `CDPL.Chem.Fragment`_ are subclasses of `CDPL.Chem.MolecularGraph`_ and instances of both can be processed in the same way by any code that operates on `CDPL.Chem.MolecularGraph`_ objects.

Basic Operations on `Molecule`_ Objects
---------------------------------------

Most of the classes for molecular structure representation, molecular data I/O and functions for basic processing reside in package `CDPL.Chem`_.

.. code:: ipython3

    import CDPL.Chem as Chem

By the import line above the code in the remainder of this tutorial can conveniently access all package contents 
via the prefix *Chem.\**.

Furthermore, the *CDPL Python* bindings implement the `Rich Output`_ of `Chem.MolecularGraph`_ instances in 
Jupyter notebooks. Rich output is activated by importing the `CDPL.Vis`_ package and will be used in the following 
code snippets to display the skeletal formula of molecular graphs simply by typing the variable name at 
the end of a code cell.

.. code:: ipython3

    import CDPL.Vis

Creation
^^^^^^^^

A `Chem.Molecule`_ object not yet having any atoms and bonds can be created by instantiating the class `Chem.BasicMolecule`_ (the provided default implementation of the`Chem.Molecule`_ interface):

.. code:: ipython3

    mol = Chem.BasicMolecule()

Querying Atom and Bond Counts
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The number of (explicit) atoms can be queried either by acessing the property `numAtoms`_ or by calling the method `getNumAtoms()`_ which are both provided by the `Chem.AtomContainer`_ interface:

.. code:: ipython3

    mol.numAtoms
    # or
    #mol.getNumAtoms()




.. parsed-literal::

    0



In the same manner, the number of explicit bonds can be retrieved by the property `numBonds`_ or by calling the method `getNumBonds()`_ of the `Chem.BondContainer`_ interface:

.. code:: ipython3

    mol.numBonds
    # or
    #mol.getNumBonds()




.. parsed-literal::

    0



Creating Atoms and Bonds
^^^^^^^^^^^^^^^^^^^^^^^^

Atoms are created by calling the method `addAtom()`_ provided by the `Chem.Molecule`_ interface:

.. code:: ipython3

    a = mol.addAtom()

The method returns a `Chem.Atom`_ object which is owned by the creating `Chem.Molecule`_ instance 
**mol**. The created atom does not yet possess any chemical properties like element, formal charge, and so on. The value of these properties needs to be set explicitly by invoking dedicated property functions which take the atom and desired value of the property as arguments. For example

.. code:: ipython3

    Chem.setType(a, Chem.AtomType.C)

The `Chem.setType()`_ function will set the type property of the atom to the atomic number of carbon. The value of the type property can be retrieved by the associated function `Chem.getType()`_

.. code:: ipython3

    Chem.getType(a)




.. parsed-literal::

    6



In a similar fashion, bonds are created by calling the method `addBond()`_ which expects the indices (zero-based) of the two atoms to connect as arguments:

.. code:: ipython3

    # add second carbon atom
    Chem.setType(mol.addAtom(), Chem.AtomType.C)
    
    b = mol.addBond(0, 1)

The method returns a `Chem.Bond`_ object which is also owned and managed by the creating `Chem.Molecule`_ instance *mol*. As with atoms, the created bond does not yet have any properties. To set the bond order to a value of 2 (= double bond) the property function `Chem.setOrder()`_ needs to be called:

.. code:: ipython3

    Chem.setOrder(b, 2)

A previously set bond order property value can be retrieved by the accompanying getter function `Chem.getOrder()`_:

.. code:: ipython3

    Chem.getOrder(b)




.. parsed-literal::

    2



.. code:: ipython3

    mol




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_27_0.svg



To create a more complex molecule, e.g. Pyridine, from the Ethene fragment that is currently described by **mol** the following lines will do the trick:

.. code:: ipython3

    # create missing atoms and set atom types
    Chem.setType(mol.addAtom(), Chem.AtomType.C)
    Chem.setType(mol.addAtom(), Chem.AtomType.C)
    Chem.setType(mol.addAtom(), Chem.AtomType.C)
    Chem.setType(mol.addAtom(), Chem.AtomType.N)
    
    # create missing bonds and set orders
    Chem.setOrder(mol.addBond(1, 2), 1)
    Chem.setOrder(mol.addBond(2, 3), 2)
    Chem.setOrder(mol.addBond(3, 4), 1)
    Chem.setOrder(mol.addBond(4, 5), 2)
    Chem.setOrder(mol.addBond(5, 0), 1)

.. code:: ipython3

    mol.numBonds




.. parsed-literal::

    6



.. code:: ipython3

    mol.numAtoms




.. parsed-literal::

    6



.. code:: ipython3

    mol




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_32_0.svg



Copying Atoms and Bonds
^^^^^^^^^^^^^^^^^^^^^^^

A deep copy of a chemical structure described by a `Chem.MolecularGraph`_ instance can be created in several ways. The first option is to pass the `Chem.MolecularGraph`_ instance as argument to the constructur of class 
`Chem.BasicMolecule`_:

.. code:: ipython3

    mol_copy = Chem.BasicMolecule(mol)
    
    mol_copy




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_34_0.svg



The second possibility is to replace the current atoms and bonds of an existing `Chem.Molecule`_ object by calling the method `assign()`_ or `copy()`_:

.. code:: ipython3

    mol_copy = Chem.BasicMolecule()
    
    Chem.setType(mol_copy.addAtom(), Chem.AtomType.C)
    
    print(mol_copy.numAtoms)
    
    mol_copy.assign(mol)
    # or
    # mol_copy.copy(mol)
    
    mol_copy


.. parsed-literal::

    1




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_36_1.svg



A third option is to call the method `clone()`_ of the `Chem.MolecularGraph`_ interface on the `Chem.Molecule`_ instance to copy:

.. code:: ipython3

    mol_copy = mol.clone()
    
    assert mol_copy.objectID != mol.objectID
    
    mol_copy




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_38_0.svg



It is also possible to concatenate molecular structures either by calling the method `append()`_ or by using the `inplace addition operator <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html#a83ddd4db763aede8ec3e2759609ff862>`__ ``+=``:


.. code:: ipython3

    mol_copy.append(mol)
    
    mol_copy




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_41_0.svg



.. code:: ipython3

    mol_copy += mol_copy
    
    mol_copy




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_42_0.svg



Accessing Atoms and Bonds
^^^^^^^^^^^^^^^^^^^^^^^^^

Atom and bonds of a molecular structure represented by a `Chem.MolecularGraph`_ instance can be accessed by 
calling the methods `getAtom()`_ (`Chem.AtomContainer`_ interface) and `getBond()`_ (`Chem.BondContainer`_ 
interface), respectively. These methods expect the zero-based index of the atom/bond in the parent molecular 
graphs's atom/bond list as argument. Valid atom/bond indices are in the range 
[0, `getNumAtoms()`_)/[0, `getNumBonds()`_). Specifying an index outside the allowed range will trigger an 
exception.

Example: Counting atom types and bond orders

.. code:: ipython3

    type_counts = {}
    order_counts = {}
    
    for i in range(0, mol.numAtoms):
        atom = mol.getAtom(i)
        atom_type = Chem.getType(atom)
    
        if atom_type in type_counts:
            type_counts[atom_type] += 1
        else:
            type_counts[atom_type] = 1
    
    for i in range(0, mol.numBonds):
        bond = mol.getBond(i)
        bond_order = Chem.getOrder(bond)
    
        if bond_order in order_counts:
            order_counts[bond_order] += 1
        else:
            order_counts[bond_order] = 1
    
    print(f'Atom types: {type_counts}')
    print(f'Bond orders: {order_counts}')


.. parsed-literal::

    Atom types: {6: 5, 7: 1}
    Bond orders: {2: 3, 1: 3}


Atoms and bonds can also be accessed in a sequential manner by iterating over the corresponding atom and bond 
lists. The atom sequence can be retrieved via the `Chem.MolecularGraph`_ interface by calling the method 
`getAtoms()`_ or accessing the property `atoms`_. The bond sequence by method `getBonds()`_ or property `bonds`_. 
The following code is an alternative version of the one above that employs sequential atom/bond access:

.. code:: ipython3

    type_counts = {}
    order_counts = {}
    
    for atom in mol.atoms:
        atom_type = Chem.getType(atom)
    
        if atom_type in type_counts:
            type_counts[atom_type] += 1
        else:
            type_counts[atom_type] = 1
    
    for bond in mol.bonds:
        bond_order = Chem.getOrder(bond)
    
        if bond_order in order_counts:
            order_counts[bond_order] += 1
        else:
            order_counts[bond_order] = 1
    
    print(f'Atom types: {type_counts}')
    print(f'Bond orders: {order_counts}')


.. parsed-literal::

    Atom types: {6: 5, 7: 1}
    Bond orders: {2: 3, 1: 3}


Removing all Atoms and Bonds
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Atoms, bonds and properties can be removed completely by calling the method `clear()`_:

.. code:: ipython3

    print(f'Num. atoms before clear(): {mol_copy.numAtoms}')
    print(f'Num. bonds before clear(): {mol_copy.numBonds}')
    
    mol_copy.clear()
    
    print(f'Num. atoms after clear(): {mol_copy.numAtoms}')
    print(f'Num. bonds after clear(): {mol_copy.numBonds}')


.. parsed-literal::

    Num. atoms before clear(): 24
    Num. bonds before clear(): 24
    Num. atoms after clear(): 0
    Num. bonds after clear(): 0


Removing single Atoms and Bonds
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Single atoms and bonds can be removed by calling the methods `removeAtom()`_ and `removeBond()`_, respectively. The methods expect the zero-based index of the atom/bond in the molecule's atom/bond list as 
argument. Valid atom/bond indices are in the range [0, `getNumAtoms()`_)/[0, `getNumBonds()`_). Specifying an 
index outside the allowed range will raise an exception.

.. code:: ipython3

    mol_copy.assign(mol)
    
    print(f'Num. atoms before removeAtom(1): {mol_copy.numAtoms}')
    print(f'Num. bonds before removeAtom(1): {mol_copy.numBonds}')
    
    # remove 2nd atom
    mol_copy.removeAtom(1)
    
    print(f'Num. atoms after removeAtom(1): {mol_copy.numAtoms}')
    print(f'Num. bonds after removeAtom(1): {mol_copy.numBonds}')
    
    mol_copy


.. parsed-literal::

    Num. atoms before removeAtom(1): 6
    Num. bonds before removeAtom(1): 6
    Num. atoms after removeAtom(1): 5
    Num. bonds after removeAtom(1): 4




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_50_1.svg



As can be seen, the removal of an atom automatically triggers the removal of all incident bonds. This is necesessary to maintain molecular graph integrity. Removal of a bond, on the other hand, will only affect 
the bond count:

.. code:: ipython3

    mol_copy.assign(mol)
    
    print(f'Num. atoms before removeBond(2): {mol_copy.numAtoms}')
    print(f'Num. bonds before removeBond(2): {mol_copy.numBonds}')
    
    # remove 3rd bond
    mol_copy.removeBond(2)
    
    print(f'Num. atoms after removeBond(2): {mol_copy.numAtoms}')
    print(f'Num. bonds after removeBond(2): {mol_copy.numBonds}')
    
    mol_copy


.. parsed-literal::

    Num. atoms before removeBond(2): 6
    Num. bonds before removeBond(2): 6
    Num. atoms after removeBond(2): 6
    Num. bonds after removeBond(2): 5




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_52_1.svg



.. warning:: `Chem.Atom`_ or `Chem.Bond`_ instances that are removed from their parent `Chem.Molecule`_ instance 
             become invalid and performing any operations on such instances (e.g. method calls via variables still 
             referencing them) results in undefined behavior!

Removing multiple Atoms and Bonds
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Multiple atoms and bonds can be removed at once via the help of a `Chem.Fragment`_ instance that specifies the 
atoms and bonds to remove. After adding atoms and bonds to the Chem.Fragment`_ instance their removal is initiated 
either by calling the method `remove()`_ with the fragment object as argument or by `inplace subtraction <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html#abe20257ca62b55aa345276de4393887a>`__ (``-=``) of the fragment object:

.. code:: ipython3

    mol_copy = mol.clone()
    frag = Chem.Fragment()
    
    frag.addAtom(mol_copy.getAtom(0))
    frag.addBond(mol_copy.getBond(1)) # this will also add the bonded atoms!
    
    print(f'Num. fragment atoms: {frag.numAtoms}')
    print(f'Num. fragment bonds: {frag.numBonds}')
    
    print(f'Num. atoms before remove(frag): {mol_copy.numAtoms}')
    print(f'Num. bonds before remove(frag): {mol_copy.numBonds}')
    
    mol_copy.remove(frag)
    # or
    #mol_copy -= frag
    
    print(f'Num. atoms after remove(frag): {mol_copy.numAtoms}')
    print(f'Num. bonds after remove(frag): {mol_copy.numBonds}')
    
    mol_copy


.. parsed-literal::

    Num. fragment atoms: 3
    Num. fragment bonds: 1
    Num. atoms before remove(frag): 6
    Num. bonds before remove(frag): 6
    Num. atoms after remove(frag): 3
    Num. bonds after remove(frag): 2




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_55_1.svg



Testing Atom and Bond Ownership
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Whether a particular `Chem.Atom`_ instance belongs to a given `Chem.Molecule`_ instance can be checked either 
by calling the method `containsAtom()`_ (`Chem.AtomContainer`_ interface) or by the membership 
test operator ``ìn`` as follows:

.. code:: ipython3

    mol_copy.assign(mol)
    
    mol.containsAtom(mol.atoms[0])




.. parsed-literal::

    True



.. code:: ipython3

    mol.getAtom(0) in mol




.. parsed-literal::

    True



.. code:: ipython3

    mol.containsAtom(mol_copy.getAtom(0))




.. parsed-literal::

    False



.. code:: ipython3

    mol_copy.atoms[0] in mol




.. parsed-literal::

    False



Similarly, a `Chem.Bond`_ instance membership test can be performed by calling the method `containsBond()`_ 
(`Chem.BondContainer`_ interface) or by using the ``ìn`` operator:

.. code:: ipython3

    mol.containsBond(mol.bonds[0])




.. parsed-literal::

    True



.. code:: ipython3

    mol.getBond(0) in mol




.. parsed-literal::

    True



.. code:: ipython3

    mol.containsBond(mol_copy.getBond(0))




.. parsed-literal::

    False



.. code:: ipython3

    
    mol_copy.bonds[0] in mol




.. parsed-literal::

    False



Retrieving Atom and Bond Indices
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The index of a `Chem.Atom`_ instance in the atom list of the parent `Chem.Molecule`_ 
instance can be retrieved by passing the atom as argument to the method `getAtomIndex()`_ 
(`Chem.AtomContainer`_ interface). In a similar manner, the index of a `Chem.Bond`_ instance can be determined by 
calling the method `getBondIndex()`_ (`Chem.BondContainer`_ interface):

.. code:: ipython3

    mol.getAtomIndex(mol.getAtom(3))




.. parsed-literal::

    3



.. code:: ipython3

    mol.getBondIndex(mol.getBond(2))




.. parsed-literal::

    2



.. warning:: The attempt to retrieve the `Chem.Atom`_ or `Chem.Bond`_ instance index on a `Chem.Molecule`_ instance that is not the parent will raise an exception!

Examples:

.. code:: ipython3

    mol.getAtomIndex(mol_copy.atoms[0])


::


    ---------------------------------------------------------------------------

    ItemNotFound                              Traceback (most recent call last)

    Cell In[38], line 1
    ----> 1 mol.getAtomIndex(mol_copy.atoms[0])


    ItemNotFound: BasicMolecule: argument atom not part of the molecule


.. code:: ipython3

    mol.getBondIndex(mol_copy.bonds[1])


::


    ---------------------------------------------------------------------------

    ItemNotFound                              Traceback (most recent call last)

    Cell In[39], line 1
    ----> 1 mol.getBondIndex(mol_copy.bonds[1])


    ItemNotFound: BasicMolecule: argument bond not part of the molecule


Processing Bonds
^^^^^^^^^^^^^^^^

`Chem.Bond`_ is a subclass of `Chem.AtomContainer`_ and methods/properties of the latter can thus be used 
to access the two bonded `Chem.Atom`_ objects in the same way as it was done for the parent `Chem.Molecule`_ 
instance:

.. code:: ipython3

    bond = mol.getBond(2)
    
    bond.numAtoms




.. parsed-literal::

    2



.. code:: ipython3

    mol.getAtomIndex(bond.getAtom(0))




.. parsed-literal::

    2



.. code:: ipython3

    mol.getAtomIndex(bond.getAtom(1))




.. parsed-literal::

    3



Like class `Chem.MolecularGraph`_, `Chem.Bond`_ provides the property `atoms 
<https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Bond.html>`__ and the method 
`getAtoms() <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Bond.html#ad028eb1083a491b60a5060f769673743>`__ which both give access to the atom pair sequence:

.. code:: ipython3

    mol.getAtomIndex(bond.atoms[0])




.. parsed-literal::

    2



.. code:: ipython3

    mol.getAtomIndex(bond.getAtoms()[1])




.. parsed-literal::

    3



Additionally, the first atom (index=0) can be retrieved directly by calling the method `getBegin()`_ or via the property `begin`_:

.. code:: ipython3

    mol.getAtomIndex(bond.getBegin())




.. parsed-literal::

    2



.. code:: ipython3

    mol.getAtomIndex(bond.begin)




.. parsed-literal::

    2



The second atom (index=1) can be accessed via the property `end`_ or by calling the method `getEnd()`_:

.. code:: ipython3

    mol.getAtomIndex(bond.getEnd())




.. parsed-literal::

    3



.. code:: ipython3

    mol.getAtomIndex(bond.end)




.. parsed-literal::

    3



If one `Chem.Atom`_ instance is given the other instance referenced by the `Chem.Bond`_ object can be retrieved 
by the calling the method `getNeighbor()`_ as follows:

.. code:: ipython3

    mol.getAtomIndex(bond.getNeighbor(bond.atoms[0]))




.. parsed-literal::

    3



.. warning:: Passing a `Chem.Atom`_ instance as argument that is not a member of the bond will trigger an  exception!

.. code:: ipython3

    bond.getNeighbor(mol.atoms[0])


::


    ---------------------------------------------------------------------------

    ItemNotFound                              Traceback (most recent call last)

    Cell In[50], line 1
    ----> 1 bond.getNeighbor(mol.atoms[0])


    ItemNotFound: BasicBond: argument atom not a member


Processing Atom Connections
^^^^^^^^^^^^^^^^^^^^^^^^^^^

`Chem.Atom`_ sublasses both `Chem.AtomContainer`_ and `Chem.BondContainer`_ which together provide methods and 
properties that can be used to access incident bonds and connected atoms.

Example:

.. code:: ipython3

    for atom in mol.atoms:
        print(f'Atom index: {mol.getAtomIndex(atom)}')
        print(f' Num. connected atoms: {atom.numAtoms}')
        
        for i in range(atom.numAtoms):
            con_atom = atom.getAtom(i)
            con_bond = atom.getBond(i)
            
            print(f'  Connected atom index: {mol.getAtomIndex(con_atom)}')
            print(f'  Bond index: {mol.getBondIndex(con_bond)}')


.. parsed-literal::

    Atom index: 0
     Num. connected atoms: 2
      Connected atom index: 1
      Bond index: 0
      Connected atom index: 5
      Bond index: 5
    Atom index: 1
     Num. connected atoms: 2
      Connected atom index: 0
      Bond index: 0
      Connected atom index: 2
      Bond index: 1
    Atom index: 2
     Num. connected atoms: 2
      Connected atom index: 1
      Bond index: 1
      Connected atom index: 3
      Bond index: 2
    Atom index: 3
     Num. connected atoms: 2
      Connected atom index: 2
      Bond index: 2
      Connected atom index: 4
      Bond index: 3
    Atom index: 4
     Num. connected atoms: 2
      Connected atom index: 3
      Bond index: 3
      Connected atom index: 5
      Bond index: 4
    Atom index: 5
     Num. connected atoms: 2
      Connected atom index: 4
      Bond index: 4
      Connected atom index: 0
      Bond index: 5


Additionally, `Chem.Atom`_ provides the method 
`getAtoms() <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Atom.html#ad315d5b7c1755ffb65ddda9d9fe3819d>`__ and the property `atoms <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Atom.html>`__ for 
accessing the list of bonded `Chem.Atom`_ instances as well as the method 
`getBonds() <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Atom.html#a4171f816134f0dcd7762a1648d8518ab>`__ and the property `bonds <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Bond.html>`__ for 
corresponding `Chem.Bond`_ instance access.

The above code changed to use the mentioned properties:

.. code:: ipython3

    for atom in mol.atoms:
        print(f'Atom index: {mol.getAtomIndex(atom)}')
        print(f' Num. connected atoms: {atom.numAtoms}')
        
        for i in range(atom.numAtoms):
            con_atom = atom.atoms[i]
            con_bond = atom.bonds[i]
            
            print(f'  Connected atom index: {mol.getAtomIndex(con_atom)}')
            print(f'  Bond index: {mol.getBondIndex(con_bond)}')


.. parsed-literal::

    Atom index: 0
     Num. connected atoms: 2
      Connected atom index: 1
      Bond index: 0
      Connected atom index: 5
      Bond index: 5
    Atom index: 1
     Num. connected atoms: 2
      Connected atom index: 0
      Bond index: 0
      Connected atom index: 2
      Bond index: 1
    Atom index: 2
     Num. connected atoms: 2
      Connected atom index: 1
      Bond index: 1
      Connected atom index: 3
      Bond index: 2
    Atom index: 3
     Num. connected atoms: 2
      Connected atom index: 2
      Bond index: 2
      Connected atom index: 4
      Bond index: 3
    Atom index: 4
     Num. connected atoms: 2
      Connected atom index: 3
      Bond index: 3
      Connected atom index: 5
      Bond index: 4
    Atom index: 5
     Num. connected atoms: 2
      Connected atom index: 4
      Bond index: 4
      Connected atom index: 0
      Bond index: 5


The `Chem.Bond`_ instance that connects two specific atoms can be queried using the `Chem.Atom`_ method 
`getBondToAtom()`_. The method is called on one of the `Chem.Atom`_ instances and expects the bonded other 
`Chem.Atom`_ instance as argument:

.. code:: ipython3

    mol.getBondIndex(mol.atoms[0].getBondToAtom(mol.atoms[5]))




.. parsed-literal::

    5



.. warning:: If a `Chem.Bond`_ instance connecting the `Chem.Atom`_ instance pair does not exist then an exception will be raised!

.. code:: ipython3

    mol.atoms[0].getBondToAtom(mol.atoms[2])


::


    ---------------------------------------------------------------------------

    ItemNotFound                              Traceback (most recent call last)

    Cell In[54], line 1
    ----> 1 mol.atoms[0].getBondToAtom(mol.atoms[2])


    ItemNotFound: BasicAtom: argument atom is not a bonded neighbor


Alternatively, the method `findBondToAtom()`_ can be used. In contrast to `getBondToAtom()`_ the method returns 
``None`` if a connecting `Chem.Bond`_ instance does not exist:

.. code:: ipython3

    print(mol.atoms[0].findBondToAtom(mol.atoms[2]))


.. parsed-literal::

    None


Basic Operations on `Fragment`_ Objects
---------------------------------------

`Chem.Fragment`_ (see section `Representation of Molecule Substructures`_) implements the `Chem.MolecularGraph`_ 
interface and thus provides the same methods and properties as `Chem.Molecule`_ for accessing/processing the 
referenced `Chem.Atom`_ and `Chem.Bond`_ instances (see section `Basic Operations on Molecule Objects`_). 
In the following subsections therefore only those methods of `Chem.Fragment`_ will be treated that 
are not present in class `Chem.Molecule`_ or for some other reasons deserve a more closer 
look. 

Creation
^^^^^^^^

An empty `Chem.Fragment`_ object not yet referencing any atoms and bonds can be created by:

.. code:: ipython3

    frag = Chem.Fragment()
    
    frag.numAtoms




.. parsed-literal::

    0



`Chem.Fragment`_ also provides constructors that accept either a `Chem.Fragment`_ or a `Chem.MolecularGraph`_ 
instance as argument. These constructors create a `Chem.Fragment`_ object that will then reference the same 
`Chem.Atom`_ and `Chem.Bond`_ instances as the passed argument:

.. code:: ipython3

    frag = Chem.Fragment(mol)
    
    frag




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_103_0.svg



As noted in section `Representation of Molecule Substructures`_, `Chem.Atom`_ and `Chem.Bond`_ 
instances added to a `Chem.Fragment`_ instance get stored as pointers (not as copies). 
Membership tests for `Chem.Atom`_ and `Chem.Bond`_ instances retrieved from a `Chem.Fragment`_ will therefore  
evaluate to ``True`` when carried out on the source `Chem.MolecularGraph`_ object:

.. code:: ipython3

    atom = frag.getAtom(0)
    
    frag.containsAtom(atom)




.. parsed-literal::

    True



.. code:: ipython3

    mol.containsAtom(atom)




.. parsed-literal::

    True



.. code:: ipython3

    bond = frag.getBond(0)
    
    frag.containsBond(bond)




.. parsed-literal::

    True



.. code:: ipython3

    mol.containsBond(bond)




.. parsed-literal::

    True



Adding single Atoms and Bonds
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

For adding individual `Chem.Atom`_ and `Chem.Bond`_ instances class `Chem.Fragment`_ provides the methods 
`addAtom() <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Fragment.html#afcb879ed6470ef02b6b4bb2c6c8070e8>`__ and 
`addBond() <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Fragment.html#a82b3b0457cfe048ea918b053b9fa37d4>`__, respectively. 
For molecular graph consistency reasons adding a `Chem.Bond`_ instance also adds the two 
`Chem.Atom`_ instances referenced by the bond (if not added already). Furthermore, pointers to `Chem.Atom`_ and 
`Chem.Bond`_ instances get stored only once. In case a given `Chem.Atom`_ or `Chem.Bond`_ instance has already 
been added the methods will do nothing and just return ``False``. 

Examples:

.. code:: ipython3

    # atom already present -> False
    frag.addAtom(mol.atoms[0])




.. parsed-literal::

    False



.. code:: ipython3

    # bond already present -> False
    frag.addBond(mol.bonds[0])




.. parsed-literal::

    False



.. code:: ipython3

    frag = Chem.Fragment()
    
    print(f'Num. atoms before addBond(): {frag.numAtoms}')
    
    frag.addBond(mol_copy.bonds[0])
    
    print(f'Num. atoms after addBond(): {frag.numAtoms}')
    print(f'Num. bonds after addBond(): {frag.numBonds}')
    
    frag


.. parsed-literal::

    Num. atoms before addBond(): 0
    Num. atoms after addBond(): 2
    Num. bonds after addBond(): 1




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_112_1.svg



Adding multiple Atoms and Bonds
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The current lists of `Chem.Atom`_ and `Chem.Bond`_ instances can be **replaced** by the method 
`assign() <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Fragment.html#a870930ae0a11c4614cef10e2d77b4305>`__ which accepts either a `Chem.Fragment`_ or a `Chem.MolecularGraph`_ instance as argument:

.. code:: ipython3

    frag.assign(mol)
    
    frag




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_114_0.svg



The current lists of `Chem.Atom`_ and `Chem.Bond`_ instances can be **extended** using the `inplace addition operator <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Fragment.html#a4402deccbaf9c04fee0c40bb2714f4a2>`__ ``+=`` with a `Chem.MolecularGraph`_ instance specifying the atoms and bond to add:

.. code:: ipython3

    frag += mol_copy
    
    frag




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_116_0.svg



Note that only `Chem.Atom`_ and `Chem.Bond`_ instance will be added that are not already part of the `Chem.Fragment`_ instance:

.. code:: ipython3

    # fragment remains unaltered
    frag += mol_copy
    
    frag




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_118_0.svg



Exchanging Atom and Bond Lists
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The current lists of `Chem.Atom`_ and `Chem.Bond`_ instances of two `Chem.Fragment`_ instances can be mutually exchanged by calling the method `swap()`_ on one of the instances providing the other instance as argument:

.. code:: ipython3

    frag2 = Chem.Fragment(mol)
    
    frag.swap(frag2)
    
    frag




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_120_0.svg



.. code:: ipython3

    frag2




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_121_0.svg



Removing single Atoms and Bonds
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Single atoms and bonds can be removed by calling the methods `removeAtom() <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Fragment.html#a2efe66d31aea184246191827019c164b>`__ and `removeBond() <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Fragment.html#ab5c1087e8ffa547824b8dbe787f5797c>`__, respectively. The methods expect the `Chem.Atom`_/`Chem.Bond`_ instance to remove or the zero-based 
index as argument. Valid atom/bond indices are in the range [0, `getNumAtoms()`_)/[0, `getNumBonds()`_). 
Specifying an index outside the allowed range will raise an exception.

Examples:

.. code:: ipython3

    print(f'Num. atoms before removeAtom(1): {frag.numAtoms}')
    print(f'Num. bonds before removeAtom(1): {frag.numBonds}')
    
    # remove 2nd atom
    frag.removeAtom(1)
    
    print(f'Num. atoms after removeAtom(1): {frag.numAtoms}')
    print(f'Num. bonds after removeAtom(1): {frag.numBonds}')
    
    frag


.. parsed-literal::

    Num. atoms before removeAtom(1): 6
    Num. bonds before removeAtom(1): 6
    Num. atoms after removeAtom(1): 5
    Num. bonds after removeAtom(1): 4




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_123_1.svg



In order to maintain molecular graph consistency, removing an atom automatically triggers the removal of all incident bonds. Removal of a bond has no side effect on the atom count:

.. code:: ipython3

    print(f'Num. atoms before removeBond(2): {frag.numAtoms}')
    print(f'Num. bonds before removeBond(2): {frag.numBonds}')
    
    # remove 3rd bond
    frag.removeBond(frag.bonds[2])
    
    print(f'Num. atoms after removeBond(2): {frag.numAtoms}')
    print(f'Num. bonds after removeBond(2): {frag.numBonds}')
    
    frag


.. parsed-literal::

    Num. atoms before removeBond(2): 5
    Num. bonds before removeBond(2): 4
    Num. atoms after removeBond(2): 5
    Num. bonds after removeBond(2): 3




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_125_1.svg



When the removal of a `Chem.Atom`_ or `Chem.Bond`_ instance is attempted that is not part of the
`Chem.Fragment`_ instance then the corresponding methods return ``False`` to indicate that the removal
operation failed:

.. code:: ipython3

    frag.removeAtom(mol_copy.getAtom(0))




.. parsed-literal::

    False



.. code:: ipython3

    frag.removeBond(mol_copy.getBond(0))




.. parsed-literal::

    False



.. code:: ipython3

    frag




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_129_0.svg



Removing multiple Atoms and Bonds
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Multiple `Chem.Atom`_ and `Chem.Bond`_ instances can be removed at once via `inplace subtraction <https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Fragment.html#ad14ca8f184120fbf87435b06dbd5a060>`__ (``-=``) of a `Chem.MolecularGraph`_ instance:

.. code:: ipython3

    frag.assign(mol)
    
    frag += mol_copy
    
    frag




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_131_0.svg



.. code:: ipython3

    frag2.clear()
    
    frag2.addBond(mol_copy.getBond(0))
    frag2.addBond(mol_copy.getBond(1))
    
    frag -= frag2
    
    frag




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_132_0.svg



Attempting to remove `Chem.Atom`_ and `Chem.Bond`_ instances that are not part of the `Chem.Fragment`_ instance 
will have no effect:

.. code:: ipython3

    frag -= frag2
    
    frag




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_134_0.svg



Reading Molecule Data
---------------------

Data provided as Strings
^^^^^^^^^^^^^^^^^^^^^^^^

.. rubric:: SMILES and SMARTS

For the direct parsing of SMILES strings the `CDPL.Chem`_ package provides the built-in utility function `Chem.parseSMILES()`_. The function returns a `Chem.BasicMolecule`_ object representing the chemical structure 
encoded by the given SMILES string. For example:

.. code:: ipython3

    mol = Chem.parseSMILES('c1c(C(=O)O)ccc(CNN)c1')
    
    mol




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_136_0.svg



A similar function called `Chem.parseSMARTS()`_ can be used to parse and and prepare SMARTS patterns for substructure searching:

.. code:: ipython3

    mol = Chem.parseSMARTS('c1:c:[n,o,s]:c:c:1-[C:2](-,=[*])-,=O')
    
    mol




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_138_0.svg



.. rubric:: Other formats

The general procedure for reading molecules from string data in one of the supported input formats (including SMILES and SMARTS) is as follows:

1. Create an instance of class `Base.StringIOStream`_ that wraps the string and serves as input data source for the next steps.
2. Create a suitable `Chem.MoleculeReaderBase`_ subclass instance that will perform the format-specific decoding of the molecule data in step 3.
3. Call the `read()`_ method of the created data reader providing an instance of class `Chem.BasicMolecule`_ for the storage of the read molecular structure as argument. 

Molecule data readers for a specific format (Step 2) can be created in two ways:

1. Via class `Chem.MoleculeReader`_ providing the `Base.StringIOStream`_ instance (Step 1) and a data format specifier (= file extension or one of the data format descriptors defined in class `Chem.DataFormat`_) as constructor arguments.
2. Direct instantiation of a format-specific subclass of `Chem.MoleculeReaderBase`_ (e.g. `Chem.MOL2MoleculeReader`_ implementing the Sybyl MOL2 format input).

Example: Reading a molecule from a string providing data in MDL SDF format

.. code:: ipython3

    import CDPL.Base as Base
    
    sdf_data = """5950
              12162506342D
    
     13 12  0     1  0  0  0  0  0999 V2000
        5.1350   -0.2500    0.0000 O   0  0  0  0  0  0  0  0  0  0  0  0
        4.2690    1.2500    0.0000 O   0  0  0  0  0  0  0  0  0  0  0  0
        2.5369    0.2500    0.0000 N   0  0  0  0  0  0  0  0  0  0  0  0
        3.4030   -0.2500    0.0000 C   0  0  1  0  0  0  0  0  0  0  0  0
        3.4030   -1.2500    0.0000 C   0  0  0  0  0  0  0  0  0  0  0  0
        4.2690    0.2500    0.0000 C   0  0  0  0  0  0  0  0  0  0  0  0
        3.4030    0.3700    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0
        2.7830   -1.2500    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0
        3.4030   -1.8700    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0
        4.0230   -1.2500    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0
        2.0000   -0.0600    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0
        2.5369    0.8700    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0
        5.6720    0.0600    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0
      1  6  1  0  0  0  0
      1 13  1  0  0  0  0
      2  6  2  0  0  0  0
      4  3  1  6  0  0  0
      3 11  1  0  0  0  0
      3 12  1  0  0  0  0
      4  5  1  0  0  0  0
      4  6  1  0  0  0  0
      4  7  1  0  0  0  0
      5  8  1  0  0  0  0
      5  9  1  0  0  0  0
      5 10  1  0  0  0  0
    M  END
    > <PUBCHEM_COMPOUND_CID>
    5950
    
    $$$$
    """
    
    ios = Base.StringIOStream(sdf_data)
    
    reader = Chem.MoleculeReader(ios, 'sdf')
    # or
    #reader = Chem.MoleculeReader(ios, Chem.DataFormat.SDF)
    # or
    #reader = Chem.SDFMoleculeReader(ios)
    
    reader.read(mol)
    mol




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_140_0.svg



Reading Molecules from Files
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Reading molecules from files also requires the creation of a `Chem.MoleculeReaderBase`_ subclass instance that performs the actual format-specific data decoding work. As with string data, several options exist:

1. Instantiation of class `Chem.MoleculeReader`_ passing the path to the file as constructor argument. When just a path is provided as argument then the data format will be determined automatically from the file extension. To override this behavior, a second argument specifying the actual file extension string to use (e.g. sdf, smi, mol2, ..) or one one of the data format descriptors defined in class `Chem.DataFormat`_ has to be provided.
2. Instantiation of class `Chem.MoleculeReader`_ passing an instance of class `Base.FileIOStream`_ that was created for the file as the first and and a format specifier as the second argument. The format specification can be a characteristic file extension or one of the data format descriptors defined in class `Chem.DataFormat`_.
3. Direct instantiation of a format-specific subclass of `Chem.MoleculeReaderBase`_ (e.g. `Chem.SDFMoleculeReader`_ implementing reading MDL SD-file format data) that accepts an instance of class `Base.FileIOStream`_ as constructor argument.
4. Direct instantiation of a format-specific subclass of `Chem.MoleculeReaderBase`_ (e.g. `Chem.FileSDFMoleculeReader`_) that accepts a file path as constructor argument.

.. code:: ipython3
        
    # - Option 1 -
    reader = Chem.MoleculeReader('/path/to/input/file.sdf')
    # or
    reader = Chem.MoleculeReader('/path/to/input/file', 'smi')
    # or
    reader = Chem.MoleculeReader('/path/to/input/file', Chem.DataFormat.SMILES)

    # - Option 2 -
    reader = Chem.MoleculeReader(Base.FileIOStream('/path/to/input/file'), 'sdf')
    # or
    reader = Chem.MoleculeReader(Base.FileIOStream('/path/to/input/file'), Chem.DataFormat.SDF)

    # - Option 3 -
    reader = Chem.MOL2MoleculeReader(Base.FileIOStream('/path/to/input/file'))

    # - Option 4 -
    reader = Chem.FileSDFMoleculeReader('/path/to/input/file')

Sequential Molecule Reading
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Given a properly initialized `Chem.MoleculeReaderBase`_ subclass instance, molecules can be read in the order provided by the input data by repeatedly calling the `read()`_ method. If there are no more molecules to read, the return value of the method will evaluate to ``False``:

.. code:: ipython3

    smi_data = """c1n(ccn1)c1ccc(cc1)c1ccc(n1c1c(cc(cc1)C(=O)N)C)CCC(=O)[O-] 022_3QJ5_A
    CNC(=O)[C@H](C(C)(C)C)NC(=O)[C@@H]([C@H](C)N([O-])C=O)CCCc1ccccc1 023_2WO9_B
    N1N(C(c2c(C=1Nc1cc([nH]n1)C)ccc(N1CC[NH+](CC1)C)c2)=O)C(C)C 027_3PIX_A
    """
    
    ios = Base.StringIOStream(smi_data)
    reader = Chem.MoleculeReader(ios, 'smi')
    mol_count = 0
    
    while reader.read(mol_copy):
       mol_count += 1
    
    print(f'Read {mol_count} molecules')


.. parsed-literal::

    Read 3 molecules


Random Molecule Access
^^^^^^^^^^^^^^^^^^^^^^

There is a special version of the `read()`_ method of class `Chem.MoleculeReaderBase`_ which expects the index (zero-based) of the molecule to read as its first argument. This way molecules can be read in any order, no matter what their order is in the input data. The number of available molecules can be queried either by calling the method `getNumRecords()`_ or by accessing the property `numRecords`_.

Example:

.. code:: ipython3

    ios = Base.StringIOStream(smi_data)
    reader = Chem.MoleculeReader(ios, 'smi')
    
    num_mols = reader.getNumRecords()
    # or
    #num_mols = reader.numRecords
    
    print(f'Number of input molecules: {num_mols}')


.. parsed-literal::

    Number of input molecules: 3


.. code:: ipython3

    # read the 2nd molecule
    reader.read(1, mol_copy)
    
    mol_copy




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_147_0.svg



.. code:: ipython3

    # read the 1st molecule
    reader.read(0, mol_copy)
    
    mol_copy




.. image:: cdpl_python_tutorial_files/cdpl_python_tutorial_148_0.svg



.. warning:: If the index is out of the valid range then a corresponding exception will be thrown!

.. code:: ipython3

    # there is no 4th molecule
    reader.read(3, mol_copy)


::


    ---------------------------------------------------------------------------

    IndexError                                Traceback (most recent call last)

    Cell In[85], line 2
          1 # there is no 4th molecule
    ----> 2 reader.read(3, mol_copy)


    IndexError: StreamDataReader: record index out of bounds


Writing Molecule Data
---------------------

Direct String Output
^^^^^^^^^^^^^^^^^^^^

.. rubric:: SMILES

For a direct generation of SMILES strings the `CDPL.Chem`_ package provides the built-in utility function `Chem.generateSMILES()`_. 
The function expects a `Chem.MolecularGraph`_ instance representing the chemical structure as first argument. Further optional arguments allow to customize the SMILES output in several aspects.

Examples:

.. code:: ipython3

    Chem.calcBasicProperties(mol, False) # calculate required properties, more on that later
    
    Chem.generateSMILES(mol) # by default, non-canonical SMILES strinsg are generated




.. parsed-literal::

    'OC(=O)[C@@H](N)C'



.. code:: ipython3

    Chem.generateSMILES(mol, True) # second arg. True -> generate canonical SMILES




.. parsed-literal::

    'C[C@@H](C(O)=O)N'



.. code:: ipython3

    Chem.generateSMILES(mol, True, False) # third arg. False -> output also standard H-atoms




.. parsed-literal::

    '[H][C@@](C(=O)O[H])(C([H])([H])[H])N([H])[H]'



.. rubric:: InChI

InChI strings can be generated by means of the utility function `Chem.generateINCHI()`_. The function also 
expects a `Chem.MolecularGraph`_ instance as its first argument. A second optional argument of type ``str`` allows to provide settings for the InChI generation code (supported options are described `here <https://github.com/IUPAC-InChI/InChI/blob/dev/INCHI-1-DOC/APIReference/InChI_API_Reference.md#getinchi>`__). The third argument controls the dimension of the atom coordinates (0 = auto sel., 2 = 2D or 3 = 3D) that are output as part of the generated auxiliary 
information (if enabled by the provided settings, see second example).

Examples:

.. code:: ipython3

    Chem.generateINCHI(mol)




.. parsed-literal::

    'InChI=1S/C3H7NO2/c1-2(4)3(5)6/h2H,4H2,1H3,(H,5,6)/t2-/m0/s1'



.. code:: ipython3

    Chem.generateINCHI(mol, '/WarnOnEmptyStructure /NEWPSOFF', 0)




.. parsed-literal::

    'InChI=1S/C3H7NO2/c1-2(4)3(5)6/h2H,4H2,1H3,(H,5,6)/t2-/m0/s1 AuxInfo=1/1/N:5,4,6,3,1,2/E:(5,6)/it:im/rA:13OONCCCHHHHHHH/rB:;;n3;s4;s1d2s4;s4;s5;s5;s5;s3;s3;s1;/rC:5.135,-.25,0;4.269,1.25,0;2.5369,.25,0;3.403,-.25,0;3.403,-1.25,0;4.269,.25,0;3.403,.37,0;2.783,-1.25,0;3.403,-1.87,0;4.023,-1.25,0;2,-.06,0;2.5369,.87,0;5.672,.06,0;'



.. rubric:: InChI Keys

InChI Keys are generated via the utility function `Chem.generateINCHIKey()`_ which expects a `Chem.MolecularGraph`_ instance as argument:

.. code:: ipython3

    Chem.generateINCHIKey(mol)




.. parsed-literal::

    'QNAYBMKLOCPYGJ-REOHCLBHSA-N'



.. _Rich Output: https://ipython.readthedocs.io/en/stable/interactive/plotting.html

.. _PyPI: https://pypi.org/project/CDPKit

.. _\_\_dict\_\_: https://docs.python.org/3/reference/datamodel.html#object.__dict\_\_

.. _Installation: https://cdpkit.org/installation.html

.. _CDPL.Base: https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Base.html

.. _CDPL.Util: https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Util.html

.. _CDPL.Math: https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Math.html

.. _CDPL.Chem: https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html

.. _CDPL.MolProp: https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1MolProp.html

.. _CDPL.Biomol: https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Biomol.html

.. _CDPL.Descr: https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Descr.html

.. _CDPL.Pharm: https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Pharm.html

.. _CDPL.Shape: https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Shape.html

.. _CDPL.ForceField: https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1ForceField.html

.. _CDPL.ConfGen: https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1ConfGen.html

.. _CDPL.Grid: https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Grid.html

.. _CDPL.GRAIL: https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1GRAIL.html

.. _CDPL.Vis: https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Vis.html

.. _CDPL.Base.IStream: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1IStream.html

.. _CDPL.Base.OStream: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1OStream.html

.. _CDPL.Base.IOStream: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1IOStream.html

.. _CDPL.Base.StringIOStream: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1StringIOStream.html

.. _Base.StringIOStream: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1StringIOStream.html

.. _CDPL.Base.FileIOStream: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1FileIOStream.html

.. _Base.FileIOStream: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1FileIOStream.html

.. _CDPL.Base.PropertyContainer: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1PropertyContainer.html

.. _CDPL.Base.ControlParameterContainer: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1ControlParameterContainer.html

.. _CDPL.Base.LookupKey: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1LookupKey.html

.. _CDPL.Base.Any: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1Any.html

.. _CDPL.Base.DataIOBase: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1DataIOBase.html

.. _CDPL.Base.DataFormat: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1DataFormat.html

.. _CDPL.Chem.ControlParameter: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1ControlParameter.html

.. _CDPL.Chem.ControlParameterDefault: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1ControlParameterDefault.html

.. _CDPL.Chem.AtomProperty: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1AtomProperty.html

.. _CDPL.Chem.BondProperty.ORDER: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BondProperty.html

.. _CDPL.Chem.BondPropertyDefault: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BondPropertyDefault.html

.. _CDPL.Chem.getOrder(): https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#a2a3103e8e0338219a5703da063cd3ef5

.. _CDPL.Chem.setOrder(): https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#ab4460ac3bac716de49c744c52d980181

.. _CDPL.Chem.hasOrder(): https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#ad021960310274a588d47cb4f2d25098c

.. _CDPL.Chem.clearOrder(): https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#aedc63dddcd7838a82e1327dec7ca5504

.. _CDPL.Chem.Entity3D: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Entity3D.html

.. _CDPL.Chem.Entity3DContainer: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Entity3DContainer.html

.. _CDPL.Chem.Atom: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Atom.html

.. _Chem.Atom: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Atom.html

.. _CDPL.Chem.BasicAtom: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BasicAtom.html

.. _Chem.BasicAtom: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BasicAtom.html

.. _CDPL.Chem.Bond: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Bond.html

.. _Chem.Bond: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Bond.html

.. _CDPL.Chem.BasicBond: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BasicBond.html

.. _Chem.BasicBond: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BasicBond.html

.. _CDPL.Chem.AtomContainer: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1AtomContainer.html

.. _Chem.AtomContainer: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1AtomContainer.html

.. _CDPL.Chem.BondContainer: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BondContainer.html

.. _Chem.BondContainer: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BondContainer.html

.. _CDPL.Chem.MolecularGraph: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MolecularGraph.html

.. _Chem.MolecularGraph: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MolecularGraph.html

.. _CDPL.Chem.Molecule: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html

.. _Chem.Molecule: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html

.. _Molecule: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html

.. _CDPL.Chem.BasicMolecule: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BasicMolecule.html

.. _Chem.BasicMolecule: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BasicMolecule.html

.. _CDPL.Chem.Fragment: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Fragment.html

.. _Chem.Fragment: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Fragment.html

.. _Fragment: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Fragment.html

.. _CDPL.Chem.MoleculeReader: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MoleculeReader.html

.. _Chem.MoleculeReader: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MoleculeReader.html

.. _CDPL.Chem.MolecularGraphWriter: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MolecularGraphWriter.html

.. _Chem.MolecularGraphWriter: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MolecularGraphWriter.html

.. _Chem.MOL2MoleculeReader: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MOL2MoleculeReader.html

.. _CDPL.Chem.SDFMoleculeReader: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1SDFMoleculeReader.html

.. _Chem.SDFMoleculeReader: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1SDFMoleculeReader.html

.. _Chem.FileSDFMoleculeReader: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1FileSDFMoleculeReader.html

.. _CDPL.Chem.MoleculeReaderBase: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MoleculeReaderBase.html

.. _Chem.MoleculeReaderBase: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MoleculeReaderBase.html

.. _CDPL.Chem.MolecularGraphWriterBase: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MolecularGraphWriterBase.html

.. _CDPL.Chem.SDFMolecularGraphWriter: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1SDFMolecularGraphWriter.html

.. _CDPL.Chem.DataFormat: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1DataFormat.html

.. _Chem.DataFormat: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1DataFormat.html

.. _CDPL.Chem.SDFMoleculeInputHandler: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1SDFMoleculeInputHandler.html

.. _CDPL.Chem.SMILESMolecularGraphOutputHandler: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1SMILESMolecularGraphOutputHandler.html

.. _CDPL.Chem.MoleculeIOManager: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MoleculeIOManager.html

.. _numAtoms: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1AtomContainer.html

.. _getNumAtoms(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1AtomContainer.html#aa18ef7240d27820c882998d8c8dbdfd7

.. _numBonds: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BondContainer.html

.. _getNumBonds(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BondContainer.html#ae0aa42f2445494d5e0bf3e3019545236

.. _addAtom(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html#ab998b55e7f56b00f47e3acbfa4511f2e

.. _addBond(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html#acd42f15d874185b4eea2cf497a509ea6

.. _getAtom(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1AtomContainer.html#ae4dc0c96b4675cdd0726a6a0a55c681f

.. _getBond(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BondContainer.html#aad68f03787b42d08b22bfc820e5016a6

.. _getAtoms(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MolecularGraph.html#a19ccf5296f5354f6d9187cfa6d691277

.. _getBonds(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MolecularGraph.html#a4a2419ae3fc47e3b71853c679df1eb06

.. _atoms: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MolecularGraph.html

.. _bonds: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MolecularGraph.html

.. _assign(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html#aeb88efb7a7e545f1255dd3525335ec9d

.. _copy(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html#a3a66552396e11b9f1661aaf2cb735c0f

.. _clone(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MolecularGraph.html#a3b93772b99b46746a36302794f42cb6f

.. _append(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html#a8adeff4dfaf59e1ae10d4ac70c8e1e95

.. _clear(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html#a1e86b5a4d16e62b1e59fad00b4addf4c

.. _removeAtom(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html#ac08a7c0881d235387268a219c97bf651

.. _removeBond(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html#a633c5d5776b547c5b0103dfc6fab9421

.. _remove(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Molecule.html#a260a01ae4366901b071043f8617be64a

.. _containsAtom(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1AtomContainer.html#a14a7fa0141f6589604621099f6708cdd

.. _containsBond(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BondContainer.html#ad32cbbec53ec26028a614beb8d1b9433

.. _getAtomIndex(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1AtomContainer.html#a0948b758760f41820137c161a17cb7ac

.. _getBondIndex(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1BondContainer.html#aa79fcf4b2cf4112b85e5e9fbf17146f6

.. _getBegin(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Bond.html#ac0ee2582c2e1e5170cf177adb0f1b607

.. _begin: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Bond.html

.. _getEnd(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Bond.html#a13715c1f120b748dbdfa831ab74645fb

.. _end: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Bond.html

.. _getNeighbor(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Bond.html#a35bdb2637eb405a3da3cc359475a1e31

.. _getBondToAtom(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Atom.html#a497cb5e9b1a04c0cee82dfb52bc05211

.. _findBondToAtom(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Atom.html#a50618b3ee26e58792e35618622ff5697

.. _swap(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1Fragment.html#a7dd0fcc088c1a7da30e75e3f61d5ac1a

.. _read(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MoleculeReaderBase.html#a07056e4d2a6de5045d59f2356d3d5521

.. _write(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MolecularGraphWriterBase.html#abd69e3d91024fff2fe687d804e36f1ea

.. _numRecords: https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MoleculeReaderBase.html

.. _getNumRecords(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Chem_1_1MoleculeReaderBase.html#aedf59cb63964cb6d497d251acddd4c80

.. _Chem.setType(): https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#a6b7bd15a77897e642d44ec56395db91f

.. _Chem.getType(): https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#a2ab1b85967b8f213bced1ac9b9dcbd6b

.. _Chem.setOrder(): https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#ab4460ac3bac716de49c744c52d980181

.. _Chem.getOrder(): https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#a2a3103e8e0338219a5703da063cd3ef5

.. _Chem.parseSMILES(): https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#a97463a5b3b08debaa2b2299a2644e912

.. _Chem.generateSMILES(): https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#a6b2f4f87930cf893cc80c2930b268014

.. _Chem.parseSMARTS(): https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#a5248eaa483ae5dc078a8f276c91ed5dc

.. _Chem.generateINCHI(): https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#ae64b94b51bd619fb7cfcf1fc39fc3198

.. _Chem.generateINCHIKey(): https://cdpkit.org/cdpl_api_doc/python_api_doc/namespaceCDPL_1_1Chem.html#aaed4c5b1939731a06640f651593e8908

.. _setParent(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1ControlParameterContainer.html#ac6b8c89fead591acfcdc6d31996a3b84

.. _getParent(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1ControlParameterContainer.html#a9d4db56fae26568869b283896b10171a

.. _registerParameterChangedCallback(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1ControlParameterContainer.html#a18609f39cfa56248ac4191a1a24740cc

.. _unregisterParameterChangedCallback(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1ControlParameterContainer.html#ac4130ab4db30b557cc3cbe536c747cea

.. _registerParameterRemovedCallback(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1ControlParameterContainer.html#a59d55eed967a82380c8b2ed2cd40405b

.. _unregisterParameterRemovedCallback(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1ControlParameterContainer.html#a6e8209de7f5cfb7a7b3f94cf109b0156

.. _registerParentChangedCallback(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1ControlParameterContainer.html#acf09cf417dfc41787e89825762bb2e32

.. _unregisterParentChangedCallback(): https://cdpkit.org/cdpl_api_doc/python_api_doc/classCDPL_1_1Base_1_1ControlParameterContainer.html#aca5b0565223043518608dd7a84cb5e0f

