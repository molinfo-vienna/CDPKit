# About

The CDPkit is an open-source software toolkit for cheminformatics and is written in C++. It also provides an additional Python-interfacing layer.
CDPKit features a high-quality and well-tested modular implementation of basic functionality typically required by any higher-level software application in the field of cheminformatics. 
It provides a wide range of functionality for handling and analyzing chemical structures, including routines for the I/O of small and macromolecular data in different file formats (MDL Mol and SDF, Mol2, PDB, MMTF, SMILES, etc.), ring and aromaticity perception, molecule representation, pharmacophore generation, substructure searching, molecular fingerprinting, molecule fragment generation (RECAP BRICS), molecular visualization, molecular conformation generation ([CONFORT](https://www.researchsquare.com/article/rs-1597257/v1)), and property prediction.

At its core, it provides a set of programming tools and libraries that enable researchers to work with molecular data in a systematic and efficient manner, allowing seamless integration with other software and databases.

Furthermore, CDPkit integrates with various machine learning and data mining libraries, enabling scientists to build predictive models for molecular 
properties. This makes it a valuable tool in the field of computational drug discovery, where machine learning is employed to predict the biological activity, toxicity, 
and other properties of potential drug candidates. An example of the integration can be found in the source code of this [publication](https://www.mdpi.com/1420-3049/26/20/6185).

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

should lead to a successful build of the CDPKit documentation which can then be found in `<BUILD-DIR>/Doc/html`.

### Documentation page
The main page of the documantion will be available online soon.
In the meantime you can access it via `<BUILD-DIR>/Doc/html`.
There, under the `CDPL Python-API` you can see the overview of the currently implemented classes and functions.
You can also access the `CDPL Python Cookbook` there, which is a collection of stand alone scripts of common use cases, including

- Processing of Chemical Data
    - Input and Output
    - Fragmentation and Extraction of Substructures
    - Standardization and Curation

- Pharmacophore Generation and Processing
⋅⋅* Plain Molecule Pharmacophores
⋅⋅* Ligand-Receptor Interaction Pharmacophores
⋅⋅* Retrieving Feature Properties
⋅⋅* Molecule to Reference Pharmacophore Alignment

- Calculation of Atom and Bond Properties
⋅⋅* Connectivity Properties
⋅⋅* Chemical Element Properties
⋅⋅* Classification Properties
⋅⋅* Partial Charges and other Electronic Properties
⋅⋅* Physicochemical Properties

- Calculation of Molecule and Pharmacophore Descriptors
⋅⋅* Extended Connectivity Fingerprints (ECFPs)
⋅⋅* FAME Atom Environment Fingerprints

- Force Field Calculations
⋅⋅* MMFF94 Atom Charges

### Basic Usage

Once CDPKit is installed, you can start using it in your Python code. Here's an example to get you started with basic ligand-based pharmacophore generation using SMILES:

```python
# Import the necessary CDPKit modules
from CDPKit import Chem
from CDPKit import Pharm

# read molecule in SMILES-format
mol = Chem.parseSMILES('Cc1ccccc1')

# print the number of atoms and bonds for the molecule
print('Processing molecule with {!s} atoms and {!s} bonds'.format(mol.numAtoms, mol.numBonds))

# generate the empty pharmacophore model
ph4 = Pharm.BasicPharmacophore()

# generate the ligand based pharmacophore model for the molecule
Pharm.DefaultPharmacophoreGenerator(mol,ph4)

# print the number of features and feature composition
print(' -> Generated %s features: %s' % (str(ph4.numFeatures), createFeatureCompositionStr(ph4)))
```

### Further Exploration

CDPKit offers a vast range of functionality beyond the basic usage shown above. Some areas to explore include:

- **Substructure Searching**: CDPKit provides powerful methods to search for substructures within molecules. You can use functions like `...` to create a query substructure and `...` to find matching substructures in a molecule.

- **Descriptor Calculation**: CDPKit allows you to calculate various molecular descriptors, such as Lipinski's Rule of Five properties, topological fingerprints, and more. These descriptors can be used to assess molecular properties and predict biological activities.

- **Chemical Reactions**: 

- **Machine Learning Integration**: CDPKit integrates well with machine learning libraries like scikit-learn, PyTorch, and TensorFlow. You can use CDPKit to preprocess molecular data, extract features, and build predictive models for various chemical properties.

### Documentation and Resources

To learn more about CDPKit and explore its features in detail, refer to the official documentation and additional resources:

- **CDPKit Documentation**: Visit the [CDPKit documentation](http://a7srv2.pch.univie.ac.at/cdpkit/getting_started/index.html#getting-started) for comprehensive information, tutorials, and examples.

- **CDPKit GitHub Repository**: Check out the [CDPKit GitHub repository](https://github.com/molinfo-vienna/CDPKit) for source code, issue tracking, and community support.

- **CDPKit Cookbook**: Explore the [CDPKit Cookbook](http://a7srv2.pch.univie.ac.at/cdpkit/cdpl_python_cookbook/index.html) for a collection of code snippets and examples showcasing various CDPKit functionalities. The documentation page will be available for external usage soon.

- **CDPKit Conformer Generator**: Visit [CONFORT](https://www.researchsquare.com/article/rs-1597257/v1), the high-quality CDPKit conformer generator intigrated in the toolkit.

- **CDPKit ML integration example**: Check out the [github](https://github.com/spudlig/graph_networks) page of the "Improved Lipophilicity and Aqueous Solubility Prediction with Composite Graph Neural Networks" publication for exploring the ML integration possibilities of the CDPKit.