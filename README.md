# Introduction

The CDPkit is an open-source software toolkit for cheminformatics, which stands for chemical informatics. 
It is widely used in the field of computational chemistry and drug discovery. 
CDPkit provides a wide range of functionality for handling and analyzing chemical structures, 
including molecule representation, pharmacophore generation, substructure searching, molecular fingerprinting, molecular visualization, molecular conformation generation, and property prediction.

At its core, CDPkit allows scientists to manipulate and analyze molecules and chemical reactions using computer algorithms. 
It provides a set of programming tools and libraries that enable researchers to work with molecular data in a systematic and efficient manner. 
CDPkit supports a variety of chemical file formats, such as SDF, MOL, and SMILES, allowing seamless integration with other software and databases.

CDPkit offers a rich set of features for molecular representation and characterization. It provides methods for generating molecular fingerprints, 
which are numerical representations of molecular structures used for similarity searching and machine learning. CDPkit also offers functionality for 
calculating molecular descriptors, which are quantitative measures of molecular properties, such as size, shape, and chemical composition.

One of the key strengths of CDPkit is its ability to perform substructure searching. Given a query molecule or a substructure pattern, 
CDPkit can efficiently search large chemical databases to find molecules that contain the specified substructure. 
This capability is particularly useful in drug discovery, where scientists often need to find compounds that interact with specific target proteins or enzymes.

CDPkit also supports the visualization of molecular structures and properties. It provides methods for generating 2D and 3D molecular depictions, 
allowing scientists to visualize and explore the spatial arrangement of atoms and bonds within a molecule. This visualization capability aids in 
understanding the structure-activity relationships and rationalizing the behavior of chemical compounds.

Furthermore, CDPkit integrates with various machine learning and data mining libraries, enabling scientists to build predictive models for molecular 
properties. This makes it a valuable tool in the field of computational drug discovery, where machine learning is employed to predict the biological activity, toxicity, 
and other properties of potential drug candidates.

In summary, CDPkit is a powerful and versatile toolkit for cheminformatics, offering a comprehensive set of tools and libraries for molecular manipulation, analysis, 
and property prediction. Its wide range of functionality makes it an indispensable resource for scientists working in the field of computational chemistry and drug discovery.

## Getting Started with CDPKit

CDPKit is an open-source cheminformatics toolkit that provides a wide range of functionality for working with chemical structures. This guide will help you get started with CDPKit and introduce you to some of its key features.

### Installation

To install CDPKit, you can use the following steps:

1. **Requirements**
- mandatory c++11 compliant compiler
- mandatory cmake (V >= 3.17)
- mandatory boost-devel C++ libraries (V >= 1.52)
- mandatory python-devel 3.x (optional) and Python-interpreter
- Qt5-devel (optional)
- cairo-devel (V >= 1.14, optional)
- sqlite-devel V3 (optional)
- sphinx (V >= 4.5, optional)
- sphinx-rtd-theme (optional)
- sphinxcontrib-bibtex (optional)
- doxygen (V >= 1.8.5, optional)

**Python Environment**: Ensure you have a Python environment set up. CDPKit is primarily used with Python, so make sure you have Python installed on your system.

2. **Install CDPKit**

build makefiles. The makefiles are generated as follows
(assuming a Linux build):

```
> mkdir <BUILD-DIR>
> cd <BUILD-DIR>
> cmake <CDPKIT-SOURCE-DIR>
```

If the makefiles have been generated without errors, invoking
'make' from within <BUILD-DIR> starts the actual build process: 

```
> make
```

Building CDPKit should proceed without any issues at least on RHEL 7/8 based systems 
(should also work on other current systems with minor configuration tweaks). 

If the build finished without errors

```
> make install
```

will install CDPKit in the /opt directory of your system (please refer to
the CMake documentation for how to change the default path).


### Generating CDPKit documentation:

For a successful build of the CDPKit documentation pages, sphinx, the sphinx-rtd-theme and sphinxcontrib-bibtex
need to be installed on the build host. Furthermore, doxygen has to be available for the generation
of the CDPL C++ and Python API-documentation.

If all prerequisites are fulfilled

```
> make doc
```

should lead to a successful build of the CDPKit documentation which can then be found in <BUILD-DIR>/Doc/html.

### Basic Usage

Once CDPKit is installed, you can start using it in your Python code. Here's an example to get you started:

```python
# Import the necessary CDPKit modules
from CDPKit import Chem

# if the input molecules are expected to be in a specific format, a reader for this format could be created directly, e.g.
# reader = Chem.FileSDFMoleculeReader(molecule.sdf)
# here we provide the reader with a string (path) to the molecule.sdf 
reader = getReaderByFileExt(molecule.sdf) 

# create an instance of the default implementation of the Chem.Molecule interface
mol = Chem.BasicMolecule()

# reads the molecule
reader.read(mol)

# print the number of atoms and bonds for the molecule
print('Processing molecule with {!s} atoms and {!s} bonds'.format(mol.numAtoms, mol.numBonds))

# generate the ligand based pharmacophore model for it
ph4 = genPharmacophore(mol) # generate pharmacophore

# print some stats about it
print(' -> Generated %s features: %s' % (str(ph4.numFeatures), createFeatureCompositionStr(ph4)))

```

In the above code, we import the required CDPKit modules, create a molecule from an SDF string, compute the ligand based pharmacophore model using CDPKit's built-in functions and print some of its molecular features.

### Further Exploration

CDPKit offers a vast range of functionality beyond the basic usage shown above. Some areas to explore include:

- **Substructure Searching**: CDPKit provides powerful methods to search for substructures within molecules. You can use functions like `Chem.MolFromSmarts()` to create a query substructure and `Chem.GetSubstructMatches()` to find matching substructures in a molecule.

- **Descriptor Calculation**: CDPKit allows you to calculate various molecular descriptors, such as Lipinski's Rule of Five properties, topological fingerprints, and more. These descriptors can be used to assess molecular properties and predict biological activities.

- **Chemical Reactions**: CDPKit supports handling and manipulation of chemical reactions. You can create reaction objects, apply transformations, and generate reaction fingerprints for similarity searching.

- **Machine Learning Integration**: CDPKit integrates well with machine learning libraries like scikit-learn and TensorFlow. You can use CDPKit to preprocess molecular data, extract features, and build predictive models for various chemical properties.

### Documentation and Resources

To learn more about CDPKit and explore its features in detail, refer to the official documentation and additional resources:

- **CDPKit Documentation**: Visit the [CDPKit documentation](http://a7srv2.pch.univie.ac.at/cdpkit/getting_started/index.html#getting-started) for comprehensive information, tutorials, and examples.

- **CDPKit GitHub Repository**: Check out the [CDPKit GitHub repository](https://github.com/molinfo-vienna/CDPKit) for source code, issue tracking, and community support.

- **CDPKit Cookbook**: Explore the [CDPKit Cookbook](http://a7srv2.pch.univie.ac.at/cdpkit/cdpl_python_cookbook/index.html) for a collection of code snippets and examples showcasing various CDPKit functionalities.