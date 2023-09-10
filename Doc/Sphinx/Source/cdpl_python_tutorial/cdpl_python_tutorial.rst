CDPL Python Tutorial
====================


Reading Molecules from an Input File
---------------------------------------

To kick off your cheminformatics journey, you'll frequently need to read or write molecular data from a variety of file formats.
Using CDPKit, you can easily read and write molecules from various file formats, including SDF, SMILES, MOL, MOL2, and others.
Here is a simple example of how to read molecules from an input file:

.. note::
    The module CDPL.Chem provides functionality for the processing of chemical data.

.. code-block:: python

   import CDPL.Chem as Chem

    def process_molecules_from_file(input_file: str) -> None:
        """
        Reads molecules from the provided input file and outputs the number of atoms and bonds for each molecule.

        Parameters:
        - input_file (str): Path to the input file.
        """
        # Create reader for input molecules (format specified by file extension)
        reader = Chem.MoleculeReader(input_file)

        # create an instance of the default implementation of the Chem.Molecule interface
        mol = Chem.BasicMolecule()
        
        # Iterate over each molecule and print atom and bond count
        try:
            while reader.read(mol): 
                try:
                    print('Molecule with', mol.numAtoms, 'atoms and', mol.numBonds, 'bonds')
                except Exception as e:
                    sys.exit('Error: processing of molecule failed: ' + str(e))
                    
        except Exception as e: # handle exception raised in case of severe read errors
            sys.exit('Error: reading molecule failed: ' + str(e))

    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:
    process_molecules_from_file("path_to_mol_file.mol2")

note::
    The `Chem.MoleculeReader` is versatile and can interpret different types of formats (SDF, SMILES, MOL, MOL2, CDF, etc.), eliminating the need to call a specific reader for each format.

Retrieving MDL Structure Data from SD Files
--------------------------------------------

Sometimes, might want to read the metadata associated with a molecule in an SD file. CDPKit provides a convenient way to do this:

.. code-block:: python

   import CDPL.Chem as Chem

   def retrieve_structure_data_from_sd(input_sd_file: str) -> None:
   """
    Retrieves the structure data of each molecule in the provided SD file and outputs it to the console.

    Parameters:
    - input_sd_file (str): Path to the input SD file.
    """
        # Create reader for MDL SD-files
        reader = Chem.FileSDFMoleculeReader(input_sd_file)

        # create an instance of the default implementation of the Chem.Molecule interface
        mol = Chem.BasicMolecule()

        # Iterate over each molecule in the file and retrieve structure data
        try:
            while reader.read(mol): 
                try:
                    if not Chem.hasStructureData(mol):
                        print('Error: no structure data available for molecule', Chem.getName(mol))
                        continue
                    
                    struct_data = Chem.getStructureData(mol) # retrieve structure data

                    print('Structure data (%s entries) of molecule \'%s\':\n' % (str(len(struct_data)), Chem.getName(mol)))
                    
                    for entry in struct_data: # iterate of structure data entries consisting of a header line and the actual data
                        print('Header:', entry.header)
                        print('Data:', entry.data)
                except Exception as e:
                    sys.exit('Error: processing of molecule failed: ' + str(e))
                    
        except Exception as e: # handle exception raised in case of severe read errors
            sys.exit('Error: reading molecule failed: ' + str(e))

    ##########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:
   retrieve_structure_data_from_sd("path_to_sd_file.sdf")

Writing Molecules to an Output File
---------------------------------------


Once you've processed or analyzed your molecules, you may want to save them to an output file. 
CDPKit provides a convenient way to write molecules to various file formats. 
The format of the output file is determined by its file extension, making it easy to save your molecules in formats such as SDF, MOL, MOL2, and others.

.. note::
   Ensure that the file extension you provide matches the desired output format. For instance, use `.sdf` for Structure-Data Files, `.mol` for MDL Molfiles, and so on.

Here's a simple example of how to write a list of molecules to an output file:

.. code-block:: python

   import CDPL.Chem as Chem

   def write_molecules_to_file(mols: list[Chem.BasicMolecule], output_file: str) -> None:
       """
       Writes a list of molecules to the specified output file.

       Parameters:
       - mols (list): List of CDPKit molecules to write to the output file.
       - output_file (str): Path to the output file.
       """
       # Create a writer for the output molecules (format specified by file extension)
       writer = Chem.MolecularGraphWriter(output_file)

       for mol in mols:
           writer.write(mol)

    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:
   write_molecules_to_file(list_of_molecules, "path_to_output_file.sdf")


Extracting Atom Environments from Molecules and extract SMILES strings for the environments
--------------------------------------------------------------------------------------------


To understand the local chemical environments around specific atoms in a molecule, we can extract the structural environments of atoms within a given molecular graph and output them as SMILES strings.

.. code-block:: python

    import CDPL.Chem as Chem

    def print_atom_environments(mols: list[Chem.BasicMolecule]) -> None:
        """
        Extracts the atom environments of each atom in the provided list of molecules and outputs them as SMILES strings.

        Parameters:
        - mols (list): List of CDPKit molecules to process.
        """

        for mol in mols:
            Chem.calcImplicitHydrogenCounts(mol, False)  # calculate implicit hydrogen counts and set corresponding property for all atoms
            Chem.perceiveHybridizationStates(mol, False) # perceive atom hybridization states and set corresponding property for all atoms
            Chem.perceiveSSSR(mol, False)                # perceive smallest set of smallest rings and store as Chem.MolecularGraph property
            Chem.setRingFlags(mol, False)                # perceive cycles and set corresponding atom and bond properties
            Chem.setAromaticityFlags(mol, False)         # perceive aromaticity and set corresponding atom and bond properties

            frag = Chem.Fragment()                       # for storing extracted atom environments

            print('- Atom environments (radius = 3 bonds)')

            for atom in mol.atoms:
                Chem.getEnvironment(atom, mol, 3, frag)     # extract environment of atom reaching out up to three bonds
                Chem.perceiveComponents(frag, False)        # perceive molecular graph components (required for SMILES generation)

                smiles = Chem.generateSMILES(frag, False, False) # generate non-canonical SMILES string with explicit hydrogen atoms

                print('Atom #%s: %s' % (str(mol.getAtomIndex(atom)), smiles))

    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:
    mols = [list of BasicMolecules]
    print_atom_environments(mols)

ChEMBL Molecule Standardization and Parent Structure Extraction
----------------------------------------------------------------


CDPKit provides a convenient way to standardize molecules using the ChEMBL standardization pipeline. This process can be used to ensure that molecules are represented in a consistent and standardized manner, which is crucial for many cheminformatics tasks.

.. code-block:: python

    import CDPL.Chem as Chem

    def standardize(chembl_proc: Chem.ChEMBLStandardizer, in_mol: Chem.Molecule, out_mol: Chem.Molecule, proc_excluded: bool, extract_parent: bool) -> Chem.ChEMBLStandardizer.ChangeFlags:
        """
        Performs ChEMBL molecule standardization and parent structure extraction (optional) for a given input molecule using a provided Chem.ChEMBLStandardizer instance.
        
        Parameters:
        - chembl_proc (Chem.ChEMBLStandardizer): Instance of the Chem.ChEMBLStandardizer class.
        - in_mol (Chem.Molecule): Input molecule to standardize.
        - out_mol (Chem.Molecule): Output molecule to store the standardized molecule.
        - proc_excluded (bool): If True, molecules flagged as excluded will be processed.
        - extract_parent (bool): If True, the parent structure will be extracted.

        Returns:
        - Chem.ChEMBLStandardizer.ChangeFlags: Flags indicating the carried out modifications.
        """
        # here, the standardization is carried out on a copy of the read input molecule
        # (if only one molecule instance gets provided as argument, modifications will be made in-place)
        change_flags = chembl_proc.standardize(in_mol, out_mol, proc_excluded)

        if extract_parent: # perform parent structure extraction (optional)
            change_flags &= ~Chem.ChEMBLStandardizer.EXCLUDED  # clear excluded flag possibly set by the standardization
                                                           # procedure (might change after salt stripping)
            change_flags |= chembl_proc.getParent(out_mol)     # extract parent structure (in-place) and add information
                                                           # about the carried out modifcations
        return change_flags

    def getListOfChangesString(change_flags: Chem.ChEMBLStandardizer.ChangeFlags, verbose: bool = False) -> str:
        """
        Returns a string listing the carried out modifications.

        Parameters:
        - change_flags (Chem.ChEMBLStandardizer.ChangeFlags): Flags indicating the carried out modifications.
        - verbose (bool): If True, the string will contain a detailed list of the carried out modifications.

        Returns:
        - str: String listing the carried out modifications.
        """
        if not verbose:
            return None

        changes = '   Carried out modifications:'

        # List of possible changes
        change_list = [
            (Chem.ChEMBLStandardizer.EXPLICIT_HYDROGENS_REMOVED, 'Explicit hydrogens removed'),
            (Chem.ChEMBLStandardizer.UNKNOWN_STEREO_STANDARDIZED, 'Undefined stereocenter information standardized'),
            (Chem.ChEMBLStandardizer.BONDS_KEKULIZED, 'Kekule structure generated'),
            (Chem.ChEMBLStandardizer.STRUCTURE_NORMALIZED, 'Functional groups normalized'),
            (Chem.ChEMBLStandardizer.CHARGES_REMOVED, 'Number of charged atoms reduced'),
            (Chem.ChEMBLStandardizer.TARTRATE_STEREO_CLEARED, 'Configuration of chiral tartrate atoms set to undefined'),
            (Chem.ChEMBLStandardizer.STRUCTURE_2D_CORRECTED, '2D structure corrected'),
            (Chem.ChEMBLStandardizer.ISOTOPE_INFO_CLEARED, 'Isotope information cleared'),
            (Chem.ChEMBLStandardizer.SALT_COMPONENTS_REMOVED, 'Salt components removed'),
            (Chem.ChEMBLStandardizer.SOLVENT_COMPONENTS_REMOVED, 'Solvent components removed'),
            (Chem.ChEMBLStandardizer.DUPLICATE_COMPONENTS_REMOVED, 'Duplicate components removed')
        ]

        for flag, description in change_list:
            if change_flags & flag:
                changes += '\n    * ' + description

        return changes

    def getLogMessage(change_flags: Chem.ChEMBLStandardizer.ChangeFlags, proc_excluded: bool, extract_parent: bool, mol_id: str, verbose: bool = False) -> str:
        """
        Returns a log message describing the carried out modifications.

        Parameters:
        - change_flags (Chem.ChEMBLStandardizer.ChangeFlags): Flags indicating the carried out modifications.
        - proc_excluded (bool): If True, molecules flagged as excluded will be processed.
        - extract_parent (bool): If True, the parent structure will be extracted.
        - mol_id (str): Identifier of the molecule.

        Returns:
        - str: Log message describing the carried out modifications.
        """
        if (change_flags & Chem.ChEMBLStandardizer.EXCLUDED) and proc_excluded:
            return f'Molecule {mol_id}: discarded (flagged as excluded)'

        if not proc_excluded and (change_flags & Chem.ChEMBLStandardizer.EXCLUDED):
            return f'Molecule {mol_id}: forwarded unchanged (flagged as excluded)'

        if change_flags:
            return f'Molecule {mol_id}: modified\n{getListOfChangesString(change_flags, verbose)}'

        return f'Molecule {mol_id}: forwarded unchanged'

    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:
    mols = [list of BasicMolecules]  # Example list of BasicMolecules

    chembl_proc = Chem.ChEMBLStandardizer()

    for mol in mols:
        in_mol = mol
        out_mol = Chem.BasicMolecule()
        change_flags = standardize(chembl_proc, in_mol, out_mol, proc_excluded=True, extract_parent=True)
        mol_id = Chem.getName(in_mol).strip() or f'Molecule_{mols.index(mol)}'
        log_msg = getLogMessage(change_flags, proc_excluded=True, extract_parent=True, mol_id=mol_id, verbose=True)
        print(log_msg)


Protonation of Functional Groups 
---------------------------------

In the realm of computational chemistry and molecular modeling, understanding and predicting the behavior of molecules often hinges on the finer details. One such critical detail is the protonation state of a molecule. 
Protonation states influence a molecule's charge, conformation, and reactivity, playing a vital role in processes like drug binding, enzymatic reactions, and more.  

In the following code snippet we will show how to protonate/deprotonate functional groups of a molecule for a given pH value and ionic strength.

.. code-block:: python

    import CDPL.Chem as Chem

    mols = [list of BasicMolecules]  # Example list of BasicMolecules 

    # create and initialize an instance of the class Chem.ProtonationStateStandardizer which
    # implements the protonation state generation algorithm
    prot_state_gen = Chem.ProtonationStateStandardizer()
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        for mol in mols:
            # compose a simple molecule identifier
            mol_id = Chem.getName(mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i) # fallback if name is empty
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i))

            try:
                # protonate/deprotonate functional groups for phys. conditions
                prot_state_gen.standardize(mol, Chem.ProtonationStateStandardizer.PHYSIOLOGICAL_CONDITION_STATE)

                # enforce an update of the molecule components list (structure might have changed)
                Chem.perceiveComponents(mol, True)
                
            except Exception as e:
                sys.exit('Error: processing or output of molecule %s failed: %s' % (mol_id, str(e)))

    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    writer.close()


Molecular Conformation and Generation
======================================

Molecular conformation refers to the spatial arrangement of atoms in a molecule. Each distinct spatial arrangement is a unique conformation. 
In the realm of cheminformatics and molecular modeling, the ability to generate and analyze different conformations of a molecule is crucial. 
This is especially important in drug design, where the biological activity of a molecule can be highly dependent on its conformation.

One of the notable conformation generation tools included in the CDPKit is `CONFORGE`. For a detailed understanding of its methodology and applications:

- `CONFORGE Publication <https://www.researchsquare.com/article/rs-1597257/v1>`_

.. note::
    The module CDPL.ConfGen provides functionality for the generation of conformation ensembles.

Generating low-energy 3D Conformations
---------------------------------------


This process involves generating 3D structures for molecules that may initially be represented in a 2D format. 

Here's how you can generate 3D conformations for a molecule:

.. code-block:: python

   import CDPL.Chem as Chem
   import CDPL.ConfGen as ConfGen

    def generate_3d_conformation(mol: Chem.Molecule, struct_gen: ConfGen.StructureGenerator) -> int:
        """
        Generates a low-energy 3D structure of the argument molecule using the provided initialized ConfGen.StructureGenerator instance.

        Parameters:
        - mol (Chem.Molecule): Molecule to generate a 3D structure for.
        - struct_gen (ConfGen.StructureGenerator): Instance of the ConfGen.StructureGenerator class.

        Returns:
        - int: Status code indicating the success of the 3D structure generation.
        """
        # prepare the molecule for 3D structure generation
        ConfGen.prepareForConformerGeneration(mol) 

        # generate the 3D structure
        status = struct_gen.generate(mol)             

        # if sucessful, store the generated conformer ensemble as
        # per atom 3D coordinates arrays (= the way conformers are represented in CDPKit)
        if status == ConfGen.ReturnCode.SUCCESS:
            struct_gen.setCoordinates(mol)                
            
        # return status code
        return status

    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:

    #Flags
    max_time = 3600 # Max. allowed molecule processing time in seconds (default: 3600 sec)

    mols = [list of BasicMolecules]  # Example list of BasicMolecules

    # create writer for the generated 3D structures (format specified by file extension)
    writer = Chem.MolecularGraphWriter("path_to_output_file.sdf") 

    # export only a single 3D structure (in case of multi-conf. input molecules)
    Chem.setMultiConfExportParameter(writer, False)
    
    # create and initialize an instance of the class ConfGen.StructureGenerator which will
    # perform the actual 3D structure generation work
    struct_gen = ConfGen.StructureGenerator()

    struct_gen.settings.timeout = max_time * 1000 # apply the -t argument

    # dictionary mapping status codes to human readable strings
    status_to_str = { ConfGen.ReturnCode.UNINITIALIZED                  : 'uninitialized',
                      ConfGen.ReturnCode.TIMEOUT                        : 'max. processing time exceeded',
                      ConfGen.ReturnCode.ABORTED                        : 'aborted',
                      ConfGen.ReturnCode.FORCEFIELD_SETUP_FAILED        : 'force field setup failed',
                      ConfGen.ReturnCode.FORCEFIELD_MINIMIZATION_FAILED : 'force field structure refinement failed',
                      ConfGen.ReturnCode.FRAGMENT_LIBRARY_NOT_SET       : 'fragment library not available',
                      ConfGen.ReturnCode.FRAGMENT_CONF_GEN_FAILED       : 'fragment conformer generation failed',
                      ConfGen.ReturnCode.FRAGMENT_CONF_GEN_TIMEOUT      : 'fragment conformer generation timeout',
                      ConfGen.ReturnCode.FRAGMENT_ALREADY_PROCESSED     : 'fragment already processed',
                      ConfGen.ReturnCode.TORSION_DRIVING_FAILED         : 'torsion driving failed',
                      ConfGen.ReturnCode.CONF_GEN_FAILED                : 'conformer generation failed' }
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        for mol in mols:
            # compose a simple molecule identifier
            mol_id = Chem.getName(mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i) # fallback if name is empty
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i))

            try:
                # generate 3D structure of the read molecule
                status = generate_3d_conformation(mol, struct_gen) 

                # check for severe error reported by status code
                if status == ConfGen.ReturnCode.SUCCESS:
                    # enforce the output of 3D coordinates in case of MDL file formats
                    Chem.setMDLDimensionality(mol, 3)

                    # output the generated 3D structure                    
                    if not writer.write(mol):   
                        sys.exit('Error: writing 3D structure of molecule %s failed' % mol_id)
                        
            except Exception as e:
                sys.exit('Error: 3D structure generation or output for molecule %s failed: %s' % (mol_id, str(e)))

    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    writer.close()

Generating Conformation Ensembles
---------------------------------------

Sometimes, it's beneficial to generate multiple conformations for a molecule to capture its flexibility and understand its preferred orientations in various environments.

The function generate_conformation_ensembles() generates a conformation ensemble for a given molecule using the provided initialized ConfGen.ConformerGenerator instance.
The flags min_rmsd, e_window, and max_confs are used to control the output conformer ensemble size and the conformation quality.
They can be set at the beginning of the example script to the desired values. 

Here's how to generate conformation ensembles for a molecule:

.. code-block:: python

   import CDPL.Chem as Chem
   import CDPL.ConfGen as ConfGen

    def generate_conformation_ensembles(mol: Chem.BasicMolecule, conf_gen: ConfGen.ConformerGenerator) -> (int, int):
        """
        Generates a conformation ensemble for the argument molecule using the provided initialized ConfGen.ConformerGenerator instance.
        
        Parameters:
        - mol (Chem.BasicMolecule): Molecule to generate a conformation ensemble for.
        - conf_gen (ConfGen.ConformerGenerator): Instance of the ConfGen.ConformerGenerator class.

        Returns:
        - int: Status code indicating the success of the conformation ensemble generation.
        - int: Number of generated conformers.
        """
        # prepare the molecule for conformer generation
        ConfGen.prepareForConformerGeneration(mol) 

        # generate the conformer ensemble
        status = conf_gen.generate(mol)             
        num_confs = conf_gen.getNumConformers()
        
        # if sucessful, store the generated conformer ensemble as
        # per atom 3D coordinates arrays (= the way conformers are represented in CDPKit)
        if status == ConfGen.ReturnCode.SUCCESS or status == ConfGen.ReturnCode.TOO_MUCH_SYMMETRY:
            conf_gen.setConformers(mol)                
        else:
            num_confs = 0
            
        # return status code and the number of generated conformers
        return (status, num_confs)


    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:

    #Flags
    max_time = 3600 # Max. allowed molecule processing time in seconds (default: 3600 sec)
    min_rmsd = 0.5 # Output conformer RMSD threshold (default: 0.5)
    e_window = 20.0 # Output conformer energy window (default: 20.0)
    max_confs = 100 # Max. output ensemble size (default: 100)


    mols = [list of BasicMolecules]  # Example list of BasicMolecules

    # create writer for the generated conformer ensembles (format specified by file extension)
    writer = Chem.MolecularGraphWriter("path_to_output_file.sdf") 

    # create and initialize an instance of the class ConfGen.ConformerGenerator which
    # will perform the actual conformer ensemble generation work
    conf_gen = ConfGen.ConformerGenerator()

    conf_gen.settings.timeout = max_time * 1000          # apply the -t argument
    conf_gen.settings.minRMSD = min_rmsd                 # apply the -r argument
    conf_gen.settings.energyWindow = e_window            # apply the -e argument
    conf_gen.settings.maxNumOutputConformers = max_confs # apply the -n argument

    # dictionary mapping status codes to human readable strings
    status_to_str = { ConfGen.ReturnCode.UNINITIALIZED                  : 'uninitialized',
                      ConfGen.ReturnCode.TIMEOUT                        : 'max. processing time exceeded',
                      ConfGen.ReturnCode.ABORTED                        : 'aborted',
                      ConfGen.ReturnCode.FORCEFIELD_SETUP_FAILED        : 'force field setup failed',
                      ConfGen.ReturnCode.FORCEFIELD_MINIMIZATION_FAILED : 'force field structure refinement failed',
                      ConfGen.ReturnCode.FRAGMENT_LIBRARY_NOT_SET       : 'fragment library not available',
                      ConfGen.ReturnCode.FRAGMENT_CONF_GEN_FAILED       : 'fragment conformer generation failed',
                      ConfGen.ReturnCode.FRAGMENT_CONF_GEN_TIMEOUT      : 'fragment conformer generation timeout',
                      ConfGen.ReturnCode.FRAGMENT_ALREADY_PROCESSED     : 'fragment already processed',
                      ConfGen.ReturnCode.TORSION_DRIVING_FAILED         : 'torsion driving failed',
                      ConfGen.ReturnCode.CONF_GEN_FAILED                : 'conformer generation failed' }
    
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()
    i = 1
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        for mol in mols:
            # compose a simple molecule identifier
            mol_id = Chem.getName(mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i) # fallback if name is empty
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i))

            try:
                # generate conformer ensemble for read molecule
                status, num_confs = generate_conformation_ensembles(mol, conf_gen) 

                # output generated ensemble (if available)
                if num_confs > 0:
                    if not writer.write(mol):   
                        sys.exit('Error: output of conformer ensemble for molecule %s failed' % mol_id)
                        
            except Exception as e:
                sys.exit('Error: conformer ensemble generation or output for molecule %s failed: %s' % (mol_id, str(e)))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    writer.close()


Pharmacophore Generation and Processing
========================================

This section is about the processing of pharmacophore models, which are abstract representations of 
molecular features.
The pharmacophore concept is widely used in drug design and cheminformatics to understand the
interactions between ligands and their biological targets.

.. note::
    The module `CDPL.Pharm` provides functionality for the generation and processing of pharmacophore models. 
    The possible pharmacophore input fotats are `pml` or `cdf`.

Ligand-based Pharmacophore Generation using Conformations
------------------------------------------------------------
The following example shows how to generate a ligand-based pharmacophore model from a set of molecules
and output it to a '.pml' file.

.. code-block:: python

    import CDPL.Chem as Chem
    import CDPL.Pharm as Pharm

    def generate_pharmacophore(mol: Chem.Molecule) -> Pharm.Pharmacophore:
        """
        Generates the pharmacophore of the molecule.
        
        Parameters:
        - mol (Chem.Molecule): Molecule to generate a pharmacophore for.

        Returns:
        - Pharm.Pharmacophore: Pharmacophore of the argument molecule.
        """
        Pharm.prepareForPharmacophoreGeneration(mol)    # first call utility function preparing the molecule for pharmacophore generation
            
        ph4_gen = Pharm.DefaultPharmacophoreGenerator()     # create an instance of the pharmacophore generator default implementation
        ph4 = Pharm.BasicPharmacophore()                    # create an instance of the default implementation of the Pharm.Pharmacophore interface
        ph4_name = Chem.getName(mol)                        # use the name of the input molecule as pharmacophore name
        
        ph4_gen.generate(mol, ph4)          # generate the pharmacophore
        Pharm.setName(ph4, ph4_name)        # set the pharmacophore name

        return ph4

    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:
    mols = [list of BasicMolecules]  # Example list of BasicMolecules

    # create writer for the generated pharmacophores (format specified by file extension)
    writer = Pharm.FeatureContainerWriter("path_to_output_file.pml")
     
    try:
        for mol in mols:
            # compose a simple molecule identifier
            mol_id = Chem.getName(mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i) # fallback if name is empty
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i))

                ph4 = genPharmacophore(mol)         # generate pharmacophore

                if not writer.write(ph4):   # output pharmacophore
                    sys.exit('Error: writing generated pharmacophore %s failed' % mol_id)
                        
            except Exception as e:
                sys.exit('Error: pharmacophore generation or output for molecule %s failed: %s' % (mol_id, str(e)))

    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    writer.close()


3D Ligand-based Pharmacophore Generation for a set of Conformations
-------------------------------------------------------------------

The following example shows how to generate a ligand-based pharmacophore model from a set of molecules.
The pharmacophore model is generated using the atom coordinates of the specified conformation of each molecule.
The name of the pharmacophore is set to the name of the corresponding molecule.

.. code-block:: python

    import CDPL.Chem as Chem
    import CDPL.Pharm as Pharm

    def generate_pharmacophore(mol: Chem.Molecule, conf_idx: int) -> Pharm.Pharmacophore:
        """
        Generates the pharmacophore of the molecule using atom coordinates of the specified conformation.
        
        Parameters:
        - mol (Chem.Molecule): Molecule to generate a pharmacophore for.
        - conf_idx (int): Index of the conformation to use for the pharmacophore generation.

        Returns:
        - Pharm.Pharmacophore: Pharmacophore of the argument molecule.
        """
        if conf_idx < 1:                                    # for a new molecule
            Pharm.prepareForPharmacophoreGeneration(mol)    # first call utility function preparing the molecule for pharmacophore generation
            
        ph4_gen = Pharm.DefaultPharmacophoreGenerator()     # create an instance of the pharmacophore generator default implementation
        ph4 = Pharm.BasicPharmacophore()                    # create an instance of the default implementation of the Pharm.Pharmacophore interface
        ph4_name = Chem.getName(mol)                        # use the name of the input molecule as pharmacophore name
        
        if conf_idx >= 0:                                   # if mol is a multi-conf. molecule use atom 3D coordinates of the specified conf.
            ph4_gen.setAtom3DCoordinatesFunction(Chem.AtomConformer3DCoordinatesFunctor(conf_idx))
            ph4_name += '#' + str(conf_idx)                 # and append conformer index to the pharmacophore name
            
        ph4_gen.generate(mol, ph4)          # generate the pharmacophore
        Pharm.setName(ph4, ph4_name)        # set the pharmacophore name

        return ph4

    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:
    mols = [list of BasicMolecules]  # Example list of BasicMolecules

    # create writer for the generated pharmacophores (format specified by file extension)
    writer = Pharm.FeatureContainerWriter("path_to_output_file.pml")
     
    try:
        for mol in mols:
            # compose a simple molecule identifier
            mol_id = Chem.getName(mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i) # fallback if name is empty
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i))

            num_confs = Chem.getNumConformations(mol)
            start_conf_idx = 0

            if num_confs == 0:      # test if molecule has conformations
                start_conf_idx = -1 # if not, make sure conformer loop body gets executed

            try:
                for conf_idx in range(start_conf_idx, num_confs): # for each conformer
                    ph4 = genPharmacophore(mol, conf_idx)         # generate pharmacophore

                    if not writer.write(ph4):   # output pharmacophore
                        sys.exit('Error: writing generated pharmacophore %s failed' % mol_id)
                        
            except Exception as e:
                sys.exit('Error: pharmacophore generation or output for molecule %s failed: %s' % (mol_id, str(e)))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    writer.close()

Aligne Ligand-based Pharmacophores for a set of Conformations
-------------------------------------------------------------------

The following example shows how to align a set of ligand-based pharmacophores to a reference pharmacophore.
The function readRefPharmacophore() reads and returns the specified alignment reference pharmacophore.
The function genPharmacophore() generates and returns the pharmacophore of the specified molecule.
The function clearFeatureOrientations() removes feature orientation informations and sets the feature geometry to Pharm.FeatureGeometry.SPHERE.
The flag pos_only, min_pose_rmsd, exhaustive, and num_out_almnts are used to control the alignment process and can
be set at the beginning of the example code.
The flag pos_only is used to control if only the position of features is considered during alignment.
The flag min_pose_rmsd is used to control the minimum required RMSD between two consecutively output molecule alignment poses.
The flag num_out_almnts is used to control the number of top-ranked alignment solutions to output per molecule (default: best alignment solution only).
The flag exhaustive is used to control if an exhaustive alignment search is performed.

.. code-block:: python

    import CDPL.Chem as Chem
    import CDPL.Pharm as Pharm

    def readRefPharmacophore(filename: str) -> Pharm.Pharmacophore:
        """
        Reads and returns the specified alignment reference pharmacophore.

        Parameters:
        - filename (str): Name of the file containing the reference pharmacophore.

        Returns:
        - Pharm.Pharmacophore: Reference pharmacophore.
        """
        # create pharmacophore reader instance
        reader = Pharm.PharmacophoreReader(filename)

        # create an instance of the default implementation of the Pharm.Pharmacophore interface
        ph4 = Pharm.BasicPharmacophore()

        try:
            if not reader.read(ph4): # read reference pharmacophore
                sys.exit('Error: reading reference pharmacophore failed')
                    
        except Exception as e: # handle exception raised in case of severe read errors
            sys.exit('Error: reading reference pharmacophore failed: ' + str(e))

        return ph4

    def genPharmacophore(mol: Chem.Molecule) -> Pharm.Pharmacophore:
        """
        Generates the pharmacophore of the molecule.

        Parameters:
        - mol (Chem.Molecule): Molecule to generate a pharmacophore for.

        Returns:
        - Pharm.Pharmacophore: Pharmacophore of the argument molecule.
        """

        Pharm.prepareForPharmacophoreGeneration(mol)       # call utility function preparing the molecule for pharmacophore generation
            
        ph4_gen = Pharm.DefaultPharmacophoreGenerator()    # create an instance of the pharmacophore generator default implementation
        ph4 = Pharm.BasicPharmacophore()                   # create an instance of the default implementation of the Pharm.Pharmacophore interface

        ph4_gen.generate(mol, ph4)                         # generate the pharmacophore

        return ph4

    def clearFeatureOrientations(ph4: Pharm.BasicPharmacophore) -> None:
        """
        Removes feature orientation informations and sets the feature geometry to Pharm.FeatureGeometry.SPHERE.
        
        Parameters:
        - ph4 (Pharm.BasicPharmacophore): Pharmacophore to clear.
        """
        for ftr in ph4:
            Pharm.clearOrientation(ftr)
            Pharm.setGeometry(ftr, Pharm.FeatureGeometry.SPHERE)

    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:

    # FLAGS
    pos_only = True # True = only position of features is considered during alignment
    num_out_almnts = 1 # Number of top-ranked alignment solutions to output per molecule (default: best alignment solution only)
    min_pose_rmsd = 0.0 # Minimum required RMSD between two consecutively output molecule alignment poses
    exhaustive = False # Perform an exhaustive alignment search (default: false)

    mols = [list of BasicMolecules]  # Example list of BasicMolecules

    # read the reference pharmacophore
    ref_ph4 = readRefPharmacophore("path_to_reference_pharmacophore.pml") 

    # create writer for aligned molecules (format specified by file extension)
    mol_writer = Chem.MolecularGraphWriter("path_to_output_file.sdf") 

    # create instance of class implementing the pharmacophore alignment algorithm
    almnt = Pharm.PharmacophoreAlignment(True) # True = aligned features have to be within the tolerance spheres of the ref. features

    if pos_only:                          # clear feature orientation information
        clearFeatureOrientations(ref_ph4)
    
    almnt.addFeatures(ref_ph4, True)               # set reference features (True = first set = reference)
    almnt.performExhaustiveSearch(exhaustive) # set minimum number of top. mapped feature pairs
    
    # create pharmacophore fit score calculator instance
    almnt_score = Pharm.PharmacophoreFitScore()
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        for mol in mols:
            # compose a simple molecule identifier
            mol_id = Chem.getName(mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i)  # fallback if name is empty
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i))

            try:
                mol_ph4 = genPharmacophore(mol)    # generate input molecule pharmacophore

                if pos_only:                  # clear feature orientation information
                    clearFeatureOrientations(mol_ph4)

                almnt.clearEntities(False)         # clear features of previously aligned pharmacophore
                almnt.addFeatures(mol_ph4, False)  # specify features of the pharmacophore to align

                almnt_solutions = []               # stores the found alignment solutions
                
                while almnt.nextAlignment():                                     # iterate over all alignment solutions that can be found
                    score = almnt_score(ref_ph4, mol_ph4, almnt.getTransform())  # calculate alignment score
                    xform = Math.Matrix4D(almnt.getTransform())                  # make a copy of the alignment transformation (mol. ph4 -> ref. ph4) 

                    almnt_solutions.append((score, xform))

                saved_coords = Math.Vector3DArray()      # create data structure for storing 3D coordinates

                Chem.get3DCoordinates(mol, saved_coords) # save the original atom coordinates

                struct_data = None

                if Chem.hasStructureData(mol):           # get existing structure data if available
                    struct_data = Chem.getStructureData(mol)
                else:                                    # otherwise create and set new structure data
                    struct_data = Chem.StringDataBlock()

                    Chem.setStructureData(mol, strut)

                # add alignment score entry to struct. data
                struct_data.addEntry('<PharmFitScore>', '') 
                
                output_cnt = 0
                last_pose = None
                
                # order solutions by desc. alignment score
                almnt_solutions = sorted(almnt_solutions, key=lambda entry: entry[0], reverse=True)

                # output molecule alignment poses until the max. number of best output solutions has been reached
                for solution in almnt_solutions:
                    if output_cnt == num_out_almnts:
                        break

                    curr_pose = Math.Vector3DArray(saved_coords)

                    Math.transform(curr_pose, solution[1])  # transform atom coordinates

                    # check whether the current pose is 'different enough' from
                    # the last pose to qualify for output
                    if min_pose_rmsd > 0.0 and last_pose and Math.calcRMSD(last_pose, curr_pose) < min_pose_rmsd:
                        continue

                    # apply the transformed atom coordinates
                    Chem.set3DCoordinates(mol, curr_pose)  

                    # store alignment score in the struct. data entry
                    struct_data[len(struct_data) - 1].setData(format(solution[0], '.4f'))     
                    
                    try:
                        if not mol_writer.write(mol): # output the alignment pose of the molecule
                            sys.exit('Error: writing alignment pose of molecule %s failed: %s' % (mol_id, str(e)))

                    except Exception as e: # handle exception raised in case of severe write errors
                        sys.exit('Error: writing alignment pose of molecule %s failed: %s' % (mol_id, str(e)))

                    last_pose = curr_pose
                    output_cnt += 1

            except Exception as e:
                sys.exit('Error: pharmacophore alignment of molecule %s failed: %s' % (mol_id, str(e)))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading input molecule failed: ' + str(e))

    mol_writer.close()

Pharmacophore Features and Feature Types
-----------------------------------------

Pharmacophore features are abstract representations of molecular features.
The script below shows how to process the properties of pharmacophore features.
The function print_pharmacophore_properties() outputs all (available) properties of the features stored in the given feature container.
E.g. the feature type, geometry, tolerance, weight, and hydrophobicity.

.. code-block:: python

    import CDPL.Chem as Chem
    import CDPL.Pharm as Pharm

    def print_pharmacophore_properties(ph4: Pharm.FeatureContainer) -> None: 
        """
        Outputs all (available) properties of the features stored in the given feature container.

        Parameters:
        - ph4 (Pharm.FeatureContainer): Feature container to process.
        """
        ftr_type_str = { Pharm.FeatureType.UNKNOWN               : 'UNKNOWN',
                        Pharm.FeatureType.HYDROPHOBIC           : 'HYDROPHOBIC',
                        Pharm.FeatureType.AROMATIC              : 'AROMATIC',
                        Pharm.FeatureType.NEGATIVE_IONIZABLE    : 'NEGATIVE_IONIZABLE',
                        Pharm.FeatureType.POSITIVE_IONIZABLE    : 'POSITIVE_IONIZABLE',
                        Pharm.FeatureType.H_BOND_DONOR          : 'H_BOND_DONOR',
                        Pharm.FeatureType.H_BOND_ACCEPTOR       : 'H_BOND_ACCEPTOR',
                        Pharm.FeatureType.HALOGEN_BOND_DONOR    : 'HALOGEN_BOND_DONOR',
                        Pharm.FeatureType.HALOGEN_BOND_ACCEPTOR : 'HALOGEN_BOND_ACCEPTOR',
                        Pharm.FeatureType.EXCLUSION_VOLUME      : 'EXCLUSION_VOLUME' }
    
        geom_str = { Pharm.FeatureGeometry.UNDEF   : 'UNDEF',
                    Pharm.FeatureGeometry.SPHERE  : 'SPHERE',
                    Pharm.FeatureGeometry.VECTOR  : 'VECTOR',
                    Pharm.FeatureGeometry.PLANE   : 'PLANE' }

        print('Composition of pharmacophore \'%s\':' % Pharm.getName(ph4))

        for i in range(0, len(ph4)):
            ftr = ph4[i]

            print(' - Feature #%s:' % str(i))
            print('  - Type: %s' % ftr_type_str[Pharm.getType(ftr)])
            print('  - Geometry: %s' % geom_str[Pharm.getGeometry(ftr)])
            print('  - Tolerance: %s' % Pharm.getTolerance(ftr))
            print('  - Weight: %s' % Pharm.getWeight(ftr))
            print('  - Optional: %s' % Pharm.getOptionalFlag(ftr))
            print('  - Disabled: %s' % Pharm.getDisabledFlag(ftr))
            print('  - Length: %s' % Pharm.getLength(ftr))
            print('  - Hydrophobicity: %s' % Pharm.getHydrophobicity(ftr))

            if Chem.has3DCoordinates(ftr):         # Pharm.Feature derives from Chem.Entity3D - therefore a function from the Chem package is used here!
                print('  - Position: %s' % Chem.get3DCoordinates(ftr))
    
            if Pharm.hasOrientation(ftr):
                print('  - Orientation: %s' % Pharm.getOrientation(ftr))


    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:

    # create reader for input pharmacophores (format specified by file extension)
    reader = Pharm.PharmacophoreReader("path_to_input_file.pml") 

    # create an instance of the default implementation of the Pharm.Pharmacophore interface
    ph4 = Pharm.BasicPharmacophore()

    # read and process pharmacophores one after the other until the end of input has been reached
    try:
        while reader.read(ph4):
            try:
                print_pharmacophore_properties(ph4)
            except Exception as e:
                sys.exit('Error: processing of pharmacophore failed: ' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading pharmacophore failed: ' + str(e))


3D Structure-based Pharmacophore Generation
--------------------------------------------

The following example shows how to generate a 3D structure-based pharmacophore model from a set of molecules.
It also reads and preprocesses the specified receptor structure.

.. note::
    The receptor structure can be in the format `*.mol2, *.pdb, *.mmtf`



.. code-block:: python

    import CDPL.Chem as Chem
    import CDPL.Pharm as Pharm

    def process_receptor_structure(path: str, strip_res_list: bool) -> Chem.Molecule:
        """
        Reads and preprocesses the specified receptor structure.

        Parameters:
        - path (str): Path to the receptor structure file.
        - strip_res_list (bool): Whitespace separated list of PDB three-letter codes specifying residues to remove from the receptor structure (e.g. an existing ligand).

        Returns:
        - Chem.Molecule: Receptor structure.

        """

        # create reader for receptor structure (format specified by file extension)
        reader = Chem.MoleculeReader("path_to_receptor_structure_file.pdb")") 
        
        sup_fmts = [ Chem.DataFormat.MOL2,
                    Biomol.DataFormat.PDB,
                    Biomol.DataFormat.MMTF ]
                            
        if reader.getDataFormat() not in sup_fmts:   # check if the format is supported by this script 
            sys.exit('Error: receptor input file format \'%s\' not supported' % name_and_ext[1])

        rec_mol = Chem.BasicMolecule()    # create an instance of the default implementation of the
                                        # Chem.Molecule interface that will store the receptor struct.
        try:
            if not reader.read(rec_mol):  # read receptor structure
                sys.exit('Error: reading receptor structure failed')

        except Exception as e:
            sys.exit('Error: reading receptor structure failed:\n' + str(e))            

        # preprocess the receptor structure (removal of residues and
        # calculation of properties required by the pharm. generation procedure)
        try:
            # if structure comes from an MOL2 file, convert MOL2 residue data into PDB-style data
            if reader.getDataFormat() == Chem.DataFormat.MOL2: 
                Biomol.convertMOL2ToPDBResidueInfo(rec_mol, True)

            rem_atoms = False

            # delete atoms belonging to residues that should be stripped
            if strip_res_list:            
                atoms_to_rem = Chem.Fragment() # will store the atoms to delete
                res_to_strip = { tlc.upper() for tlc in strip_res_list }
            
                for atom in rec_mol.atoms:     # identify and note atoms belonging to the stripped residues
                    if Biomol.getResidueCode(atom).upper() in res_to_strip:
                        atoms_to_rem.addAtom(atom)

                if atoms_to_rem.numAtoms > 0:
                    rec_mol -= atoms_to_rem    # delete atoms from the receptor structure
                    rem_atoms = True

            # prepares the receptor structure for pharmacophore generation
            Chem.perceiveSSSR(rec_mol, rem_atoms)
            Chem.setRingFlags(rec_mol, rem_atoms)
            Chem.calcImplicitHydrogenCounts(rec_mol, rem_atoms)
            Chem.perceiveHybridizationStates(rec_mol, rem_atoms)
            Chem.setAromaticityFlags(rec_mol, rem_atoms)

            if Chem.makeHydrogenComplete(rec_mol):                    # make implicit hydrogens (if any) explicit
                Chem.calcHydrogen3DCoordinates(rec_mol)               # calculate 3D coordinates for the added expl. hydrogens
                Biomol.setHydrogenResidueSequenceInfo(rec_mol, False) # set residue information for the added expl. hydrogens

            MolProp.calcAtomHydrophobicities(rec_mol, False)          # calculate atom hydrophobicity values (needed for hydrophobic
                                                                    # pharm. feature generation)
        except Exception as e:
            sys.exit('Error: processing of receptor structure failed: ' + str(e))            

        return rec_mol

    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:
    # Flags
    strip_res_list = False # Whitespace separated list of PDB three-letter codes specifying residues to remove from the receptor structure (e.g. an existing ligand)
    gen_x_vols = False # Generate exclusion volume spheres on pharm. feature atoms of interacting residues
    
    
    lig_mols = [list of BasicMolecules]  # Example list of BasicMolecules

    rec_mol = process_receptor_structure(path_to_receptor_structure_file, strip_res_list)          # read and preprocess the receptor structure
    ph4_writer = Pharm.FeatureContainerWriter("path_to_pha_file.pml") # create writer for the generated pharmacophores (format specified by file extension)

    ia_ph4 = Pharm.BasicPharmacophore()     # create an instance of the default implementation of the Pharm.Pharmacophore
                                            # interface that will store the generated pharmacophores

    ph4_gen = Pharm.InteractionPharmacophoreGenerator() # create an instance of the pharmacophore generator

    ph4_gen.addExclusionVolumes(gen_x_vols)        # specify whether to generate exclusion volume spheres 
                                                        # on pharm. feature atoms of interacting residues
    try:

        # read and process ligand molecules one after the other until the end of input has been reached (or a severe error occurs)
        for lig_mol in lig_reader:
            mol_id = Chem.getName(lig_mol).strip() # compose a simple ligand identifier for messages

            if mol_id == '':
                mol_id = '#' + str(i)  # fallback if name is empty or not available
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i))

            try:
                Pharm.prepareForPharmacophoreGeneration(lig_mol) # make ligand ready for pharm. generation

                ph4_gen.generate(lig_mol, rec_mol, ia_ph4, True) # generate the pharmacophore (True = extract ligand environment residues on-the-fly)

                try:
                    if not ph4_writer.write(ia_ph4): # output pharmacophore
                        sys.exit('Error: writing interaction pharmacophore of molecule %s failed: %s' % (mol_id, str(e)))

                except Exception as e:               # handle exception raised in case of severe write errors
                    sys.exit('Error: writing interaction pharmacophore of molecule %s failed: %s' % (mol_id, str(e)))
                
            except Exception as e:                   # handle exception raised in case of severe processing errors
                sys.exit('Error: interaction pharmacophore generation for molecule %s failed: %s' % (mol_id, str(e)))

    except Exception as e:                           # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule %s failed: %s' % (str(i), str(e)))

    ph4_writer.close()


Calculation of Atom and Bond Properties
========================================


CDPKit provides a convenient way to calculate various properties of atoms and bonds in a molecule.

Calculation of Atomic Properties
---------------------------------------

Atomic properties provide important chemical information about each atom in a molecule that 
is useful for many cheminformatics tasks. The following code snippet shows how to calculate
and output the corresponding properties of each atom of the provided molecular graph. It includes
the calculation of implicit hydrogen counts, atom hybridization states, smallest set of smallest rings,
cycles, aromaticity, and H-bond donor and acceptor atom types.


.. code-block:: python

    import sys
    import os

    import CDPL.Chem as Chem
    import CDPL.MolProp as MolProp

    def outputProperties(molgraph: Chem.MolecularGraph) -> None:
        """
        Outputs the corresponding properties of each atom of the provided molecular graph.

        Parameters:
        - molgraph (Chem.MolecularGraph): Molecular graph to process.
        """
        Chem.calcImplicitHydrogenCounts(molgraph, False)  # calculate implicit hydrogen counts and set corresponding property for all atoms
        Chem.perceiveHybridizationStates(molgraph, False) # perceive atom hybridization states and set corresponding property for all atoms
        Chem.perceiveSSSR(molgraph, False)                # perceive smallest set of smallest rings and store as Chem.MolecularGraph property
        Chem.setRingFlags(molgraph, False)                # perceive cycles and set corresponding atom and bond properties
        Chem.setAromaticityFlags(molgraph, False)         # perceive aromaticity and set corresponding atom and bond properties
        MolProp.perceiveHBondDonorAtomTypes(molgraph, False) # perceive H-bond donor atom types and set corresponding atom properties
        MolProp.perceiveHBondAcceptorAtomTypes(molgraph, False) # perceive H-bond acceptor atom types and set corresponding atom properties

        hba_type_str = { MolProp.HBondAcceptorAtomType.UNDEF                   : 'UNDEF',
                        MolProp.HBondAcceptorAtomType.NONE                    : 'NONE',
                        MolProp.HBondAcceptorAtomType.O_H2O                   : 'O_H2O',
                        MolProp.HBondAcceptorAtomType.O_UREA                  : 'O_UREA',
                        MolProp.HBondAcceptorAtomType.O_BARBITURIC_ACID       : 'O_BARBITURIC_ACID',
                        MolProp.HBondAcceptorAtomType.O_URIC_ACID             : 'O_URIC_ACID',
                        MolProp.HBondAcceptorAtomType.O_ETHER                 : 'O_ETHER',
                        MolProp.HBondAcceptorAtomType.O_AMIDE                 : 'O_AMIDE',
                        MolProp.HBondAcceptorAtomType.O_N_OXIDE               : 'O_N_OXIDE',
                        MolProp.HBondAcceptorAtomType.O_ACID                  : 'O_ACID',
                        MolProp.HBondAcceptorAtomType.O_ESTER                 : 'O_ESTER',
                        MolProp.HBondAcceptorAtomType.O_SULFOXIDE             : 'O_SULFOXIDE',
                        MolProp.HBondAcceptorAtomType.O_NITRO                 : 'O_NITRO',
                        MolProp.HBondAcceptorAtomType.O_SELEN_OXIDE           : 'O_SELEN_OXIDE',
                        MolProp.HBondAcceptorAtomType.O_ALDEHYD               : 'O_ALDEHYD',
                        MolProp.HBondAcceptorAtomType.O_KETONE                : 'O_KETONE',
                        MolProp.HBondAcceptorAtomType.O_ALCOHOL               : 'O_ALCOHOL',
                        MolProp.HBondAcceptorAtomType.N_NH3                   : 'N_NH3',
                        MolProp.HBondAcceptorAtomType.N_DIAMINE               : 'N_DIAMINE',
                        MolProp.HBondAcceptorAtomType.N_MONO_DI_NITRO_ANILINE : 'N_MONO_DI_NITRO_ANILINE',
                        MolProp.HBondAcceptorAtomType.N_TRI_NITRO_ANILINE     : 'N_TRI_NITRO_ANILINE',
                        MolProp.HBondAcceptorAtomType.N_HALOGENO_ANILINE      : 'N_HALOGENO_ANILINE',
                        MolProp.HBondAcceptorAtomType.N_ANILINE               : 'N_ANILINE',
                        MolProp.HBondAcceptorAtomType.N_NITRILE               : 'N_NITRILE',
                        MolProp.HBondAcceptorAtomType.N_AZOLE                 : 'N_AZOLE',
                        MolProp.HBondAcceptorAtomType.N_AMINE                 : 'N_AMINE',
                        MolProp.HBondAcceptorAtomType.N_AMIDINE               : 'N_AMIDINE',
                        MolProp.HBondAcceptorAtomType.N_AZO                   : 'N_AZO',
                        MolProp.HBondAcceptorAtomType.N_AZINE                 : 'N_AZINE',
                        MolProp.HBondAcceptorAtomType.N_DIAZINE               : 'N_DIAZINE',
                        MolProp.HBondAcceptorAtomType.N_IMINE                 : 'N_IMINE',
                        MolProp.HBondAcceptorAtomType.S_SULFIDE               : 'S_SULFIDE',
                        MolProp.HBondAcceptorAtomType.S_THIOUREA              : 'S_THIOUREA',
                        MolProp.HBondAcceptorAtomType.P_MONO_DI_PHOSPHINE     : 'P_MONO_DI_PHOSPHINE',
                        MolProp.HBondAcceptorAtomType.P_TRI_PHOSPHINE         : 'P_TRI_PHOSPHINE' }

        hbd_type_str = { MolProp.HBondDonorAtomType.UNDEF                       : 'UNDEF',
                        MolProp.HBondDonorAtomType.NONE                        : 'NONE',
                        MolProp.HBondDonorAtomType.I_HI                        : 'I_HI',
                        MolProp.HBondDonorAtomType.BR_HBR                      : 'BR_HBR',
                        MolProp.HBondDonorAtomType.CL_HCL                      : 'CL_HCL',
                        MolProp.HBondDonorAtomType.S_HSCN                      : 'S_HSCN',
                        MolProp.HBondDonorAtomType.F_HF                        : 'F_HF',
                        MolProp.HBondDonorAtomType.H_H2                        : 'H_H2',
                        MolProp.HBondDonorAtomType.C_HCN                       : 'C_HCN',
                        MolProp.HBondDonorAtomType.C_ETHINE                    : 'C_ETHINE',
                        MolProp.HBondDonorAtomType.N_HN3                       : 'N_HN3',
                        MolProp.HBondDonorAtomType.N_NH3                       : 'N_NH3',
                        MolProp.HBondDonorAtomType.N_NH4                       : 'N_NH4',
                        MolProp.HBondDonorAtomType.N_AMINE                     : 'N_AMINE',
                        MolProp.HBondDonorAtomType.N_AMINIUM                   : 'N_AMINIUM',
                        MolProp.HBondDonorAtomType.N_ANILINE                   : 'N_ANILINE',
                        MolProp.HBondDonorAtomType.N_MONO_DI_NITRO_ANILINE     : 'N_MONO_DI_NITRO_ANILINE',
                        MolProp.HBondDonorAtomType.N_TRI_NITRO_ANILINE         : 'N_TRI_NITRO_ANILINE',
                        MolProp.HBondDonorAtomType.N_PYRROLE                   : 'N_PYRROLE',
                        MolProp.HBondDonorAtomType.N_AMIDE                     : 'N_AMIDE',
                        MolProp.HBondDonorAtomType.N_IMINE                     : 'N_IMINE',
                        MolProp.HBondDonorAtomType.N_IMINIUM                   : 'N_IMINIUM',
                        MolProp.HBondDonorAtomType.S_H2S                       : 'S_H2S',
                        MolProp.HBondDonorAtomType.S_HS                        : 'S_HS',
                        MolProp.HBondDonorAtomType.S_THIOL                     : 'S_THIOL',
                        MolProp.HBondDonorAtomType.O_H3PO4                     : 'O_H3PO4',
                        MolProp.HBondDonorAtomType.O_H2CO3                     : 'O_H2CO3',
                        MolProp.HBondDonorAtomType.O_HCO3                      : 'O_HCO3',
                        MolProp.HBondDonorAtomType.O_H2O2                      : 'O_H2O2',
                        MolProp.HBondDonorAtomType.O_H2O                       : 'O_H2O',
                        MolProp.HBondDonorAtomType.O_CF3SO3H                   : 'O_CF3SO3H',
                        MolProp.HBondDonorAtomType.O_HCLO4                     : 'O_HCLO4',
                        MolProp.HBondDonorAtomType.O_H2SO4                     : 'O_H2SO4',
                        MolProp.HBondDonorAtomType.O_HNO3                      : 'O_HNO3',
                        MolProp.HBondDonorAtomType.O_HSO4                      : 'O_HSO4',
                        MolProp.HBondDonorAtomType.O_HNO2                      : 'O_HNO2',
                        MolProp.HBondDonorAtomType.O_NH2OH                     : 'O_NH2OH',
                        MolProp.HBondDonorAtomType.O_H2PO4                     : 'O_H2PO4',
                        MolProp.HBondDonorAtomType.O_H3BO3                     : 'O_H3BO3',
                        MolProp.HBondDonorAtomType.O_H4SIO4                    : 'O_H4SIO4',
                        MolProp.HBondDonorAtomType.O_HPO4                      : 'O_HPO4',
                        MolProp.HBondDonorAtomType.O_H2BO3                     : 'O_H2BO3',
                        MolProp.HBondDonorAtomType.O_HO                        : 'O_HO',
                        MolProp.HBondDonorAtomType.O_SULFONIC_ACID             : 'O_SULFONIC_ACID',
                        MolProp.HBondDonorAtomType.O_MONO_DI_NITRO_PHENOL      : 'O_MONO_DI_NITRO_PHENOL',
                        MolProp.HBondDonorAtomType.O_HALOGENO_ALCOHOL          : 'O_HALOGENO_ALCOHOL',
                        MolProp.HBondDonorAtomType.O_ALCOHOL                   : 'O_ALCOHOL',
                        MolProp.HBondDonorAtomType.O_TRI_NITRO_PHENOL          : 'O_TRI_NITRO_PHENOL',
                        MolProp.HBondDonorAtomType.O_HALOGENO_PHENOL           : 'O_HALOGENO_PHENOL',
                        MolProp.HBondDonorAtomType.O_PHENOL                    : 'O_PHENOL',
                        MolProp.HBondDonorAtomType.O_CARBOXYLIC_ACID           : 'O_CARBOXYLIC_ACID',
                        MolProp.HBondDonorAtomType.O_HALOGENO_CARBOXYCLIC_ACID : 'O_HALOGENO_CARBOXYCLIC_ACID',
                        MolProp.HBondDonorAtomType.O_ENOL                      : 'O_ENOL',
                        MolProp.HBondDonorAtomType.O_OXIME                     : 'O_OXIME',
                        MolProp.HBondDonorAtomType.O_CL5_PHENOL                : 'O_CL5_PHENOL' }
        
        for atom in molgraph.atoms:
            print('- Atom #%s' % str(molgraph.getAtomIndex(atom)))
            print('\tIs std. hydrogen: %s' % str(MolProp.isOrdinaryHydrogen(atom, molgraph)))
            print('\tIs heavy atom: %s' % str(MolProp.isHeavy(atom)))
            print('\tIs unsaturated: %s' % str(MolProp.isUnsaturated(atom, molgraph)))
            print('\tIs H-bond acceptor: %s' % str(MolProp.isHBondAcceptor(atom, molgraph)))
            print('\tH-bond acceptor type: %s' % hba_type_str[MolProp.getHBondAcceptorType(atom)])
            print('\tIs H-bond donor: %s' % str(MolProp.isHBondDonor(atom, molgraph)))
            print('\tH-bond donor type: %s' % hbd_type_str[MolProp.getHBondDonorType(atom)])
            print('\tIs carbonyl carbon: %s' % str(MolProp.isCarbonylLikeAtom(atom, molgraph, True, True)))
            print('\tIs amide carbon: %s' % str(MolProp.isAmideCenterAtom(atom, molgraph, True, True)))
            print('\tIs amide nitrogen: %s' % str(MolProp.isAmideNitrogen(atom, molgraph, True, True)))
            print('\tIs invertible nitrogen: %s' % str(MolProp.isInvertibleNitrogen(atom, molgraph)))
            print('\tIs planar nitrogen: %s' % str(MolProp.isPlanarNitrogen(atom, molgraph)))
            
            if len(sys.argv) < 2:
                sys.exit('Usage: %s <input mol. file>' % sys.argv[0])


    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:
    mols = [list of BasicMolecules]  # Example list of BasicMolecules

    # read and process molecules one after the other until the end of input has been reached
    try:
        for mol in mols:
            try:
                outputProperties(mol)
            except Exception as e:
                sys.exit('Error: processing of molecule failed: ' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))


Calculation of Connectivity Properties
---------------------------------------



This code provides a way to calculate various properties of atoms and bonds in a molecule.
The code snippet provided below shows how to calculate and output the corresponding properties of each atom of the provided molecular graph.
It includes the calculation of implicit hydrogen counts, atom hybridization states, smallest set of smallest rings, cycles, aromaticity,
and a variety of other connectivity properties such as the number of connected carbon atoms, heteroatoms, halogens, heavy atoms, chain atoms,
ring atoms, aromatic atoms, incident bonds, and incident single bonds as well as valecny, coordination, and ring sizes.

.. code-block:: python

    import sys
    import os

    import CDPL.Chem as Chem
    import CDPL.MolProp as MolProp
    
    def outputProperties(molgraph: Chem.MolecularGraph) -> None:
        """
        Outputs the corresponding properties of each atom of the provided molecular graph.

        Parameters:
        - molgraph (Chem.MolecularGraph): Molecular graph to process.
        """
        Chem.calcImplicitHydrogenCounts(molgraph, False)  # calculate implicit hydrogen counts and set corresponding property for all atoms
        Chem.perceiveHybridizationStates(molgraph, False) # perceive atom hybridization states and set corresponding property for all atoms
        Chem.perceiveSSSR(molgraph, False)                # perceive smallest set of smallest rings and store as Chem.MolecularGraph property
        Chem.setRingFlags(molgraph, False)                # perceive cycles and set corresponding atom and bond properties
        Chem.setAromaticityFlags(molgraph, False)         # perceive aromaticity and set corresponding atom and bond properties

        vsepr_geom_str = { MolProp.CoordinationGeometry.UNDEF                  : 'UNDEF',
                    MolProp.CoordinationGeometry.NONE                   : 'NONE',
                    MolProp.CoordinationGeometry.LINEAR                 : 'LINEAR',
                    MolProp.CoordinationGeometry.TRIGONAL_PLANAR        : 'TRIGONAL_PLANAR',
                    MolProp.CoordinationGeometry.TETRAHEDRAL            : 'TETRAHEDRAL',
                    MolProp.CoordinationGeometry.TRIGONAL_BIPYRAMIDAL   : 'TRIGONAL_BIPYRAMIDAL',
                    MolProp.CoordinationGeometry.OCTAHEDRAL             : 'OCTAHEDRAL',
                    MolProp.CoordinationGeometry.PENTAGONAL_BIPYRAMIDAL : 'PENTAGONAL_BIPYRAMIDAL',
                    MolProp.CoordinationGeometry.SQUARE_ANTIPRISMATIC   : 'SQUARE_ANTIPRISMATIC',
                    MolProp.CoordinationGeometry.BENT                   : 'BENT',
                    MolProp.CoordinationGeometry.TRIGONAL_PYRAMIDAL     : 'TRIGONAL_PYRAMIDAL',
                    MolProp.CoordinationGeometry.SQUARE_PLANAR          : 'SQUARE_PLANAR',
                    MolProp.CoordinationGeometry.SQUARE_PYRAMIDAL       : 'SQUARE_PYRAMIDAL',
                    MolProp.CoordinationGeometry.T_SHAPED               : 'T_SHAPED',
                    MolProp.CoordinationGeometry.SEESAW                 : 'SEESAW',
                    MolProp.CoordinationGeometry.PENTAGONAL_PYRAMIDAL   : 'PENTAGONAL_PYRAMIDAL',
                    MolProp.CoordinationGeometry.PENTAGONAL_PLANAR      : 'PENTAGONAL_PLANAR' }
        
        for atom in molgraph.atoms:
            print('- Atom #%s' % str(molgraph.getAtomIndex(atom)))
            print('\tNum. connected std. hydrogens (incl. impl. H): %s' % str(MolProp.getOrdinaryHydrogenCount(atom, molgraph)))
            print('\tNum. connected carbon atoms: %s' % str(MolProp.getExplicitAtomCount(atom, molgraph, Chem.AtomType.C)))
            print('\tNum. connected heteroatoms: %s' % str(MolProp.getExplicitAtomCount(atom, molgraph, Chem.AtomType.HET, False)))
            print('\tNum. connected halogens: %s' % str(MolProp.getExplicitAtomCount(atom, molgraph, Chem.AtomType.X, False)))
            print('\tNum. connected heavy atoms: %s' % str(MolProp.getHeavyAtomCount(atom, molgraph)))
            print('\tNum. connected chain atoms (excl. impl. H): %s' % str(MolProp.getExplicitChainAtomCount(atom, molgraph)))
            print('\tNum. connected chain atoms (incl. impl. H): %s' % str(MolProp.getChainAtomCount(atom, molgraph)))
            print('\tNum. connected ring atoms: %s' % str(MolProp.getRingAtomCount(atom, molgraph)))
            print('\tNum. connected aromatic atoms: %s' % str(MolProp.getAromaticAtomCount(atom, molgraph)))
            print('\tNum. incident bonds (excl. impl. H): %s' % str(MolProp.getExplicitBondCount(atom, molgraph)))
            print('\tNum. incident bonds (incl. impl. H): %s' % str(MolProp.getBondCount(atom, molgraph)))
            print('\tNum. incident single bonds (excl. impl. H): %s' % str(MolProp.getExplicitBondCount(atom, molgraph, 1)))
            print('\tNum. incident single bonds (incl. impl. H): %s' % str(MolProp.getBondCount(atom, molgraph, 1)))
            print('\tNum. incident double bonds: %s' % str(MolProp.getBondCount(atom, molgraph, 2)))
            print('\tNum. incident triple bonds: %s' % str(MolProp.getBondCount(atom, molgraph, 3)))
            print('\tNum. incident chain bonds (excl. impl. H): %s' % str(MolProp.getExplicitChainBondCount(atom, molgraph)))
            print('\tNum. incident chain bonds (incl. impl. H): %s' % str(MolProp.getChainBondCount(atom, molgraph)))
            print('\tNum. incident ring bonds (incl. impl. H): %s' % str(MolProp.getRingBondCount(atom, molgraph)))
            print('\tNum. incident aromatic bonds (incl. impl. H): %s' % str(MolProp.getAromaticBondCount(atom, molgraph)))
            print('\tNum. incident heavy atom bonds (incl. impl. H): %s' % str(MolProp.getHeavyBondCount(atom, molgraph)))
            print('\tNum. incident rotatable bonds (incl. impl. H): %s' % str(MolProp.getRotatableBondCount(atom, molgraph, False, False)))
            print('\tValence (excl. impl. H): %s' % str(MolProp.calcExplicitValence(atom, molgraph)))
            print('\tValence (incl. impl. H): %s' % str(MolProp.calcValence(atom, molgraph)))
            print('\tSteric number: %s' % str(MolProp.calcStericNumber(atom, molgraph)))
            print('\tVSEPR coordination geometry: %s' % vsepr_geom_str[MolProp.getVSEPRCoordinationGeometry(atom, molgraph)])


    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:
    mols = [list of BasicMolecules]  # Example list of BasicMolecules
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        for mol in mols:
            try:
                outputProperties(mol)
            except Exception as e:
                sys.exit('Error: processing of molecule failed: ' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))




Calculation of Molecule and Pharmacophore Descriptors
=========================================================

The calculation of molecular descriptors is a fundamental operation in cheminformatics. 
It allows for the quantification of various chemical properties of molecules, which can be
used for various cheminformatics tasks, such as:

- **Drug Discovery**: Identifying molecules that contain a particular pharmacophore or active site.
- **Chemical Database Querying**: Filtering large chemical databases to retrieve molecules of interest.
- **Chemical Analysis**: Identifying the presence of particular functional groups or fragments in molecules.

.. note::
    The CDPKit moduls CDPL.Descr and CDPL.Util provide a convenient way to calculate various molecular descriptors.

Extended Connectivity Fingerprints (ECFPs)
-------------------------------------------

Morgan circular fingerprints, also known as extended connectivity fingerprints (ECFPs), 
are a type of structural fingerprints that encode the local chemical environment of each atom in a 
molecule. They are widely used in cheminformatics for various tasks, such as similarity searching, 
virtual screening, and machine learning.

The following code snippet calculates and outputs the ECFP4 fingerprints of the provided molecules.
Following parameters can be set: 

- **num_bits**: The number of bits of the fingerprint (default: 1024)
- **radius**: Max. atom environment radius in number of bonds (default: 2)
- **inc_hs**: Whether to include explicit hydrogens (by default, the fingerprint is generated for the H-deplete molecular graph)
- **inc_config**: Whether to include atom chirality (by default, the fingerprint is generated for the H-deplete molecular graph)

.. code:: python

    import CDPL.Descr as Descr
    import CDPL.Util as Util

    def genECFP(mol: Chem.Molecule, num_bits: int, radius: int, inc_hs: bool, inc_config: bool) -> Util.BitSet:
        """
        Generates the binary ECFP for the given molecule.

        Parameters:
        - mol (Chem.Molecule): Molecule to process.
        - num_bits (int): Number of bits of the fingerprint.
        - radius (int): Max. atom environment radius in number of bonds.
        - inc_hs (bool): Whether to include explicit hydrogens.
        - inc_config (bool): Whether to include atom chirality.

        Returns:
        - Util.BitSet: The generated fingerprint.
        """

        Chem.calcImplicitHydrogenCounts(mol, False)        # calculate implicit hydrogen counts (if not yet done)
        Chem.perceiveHybridizationStates(mol, False)       # perceive atom hybridization states and set corresponding property for all atoms
        Chem.setRingFlags(mol, False)                      # perceive cycles and set corresponding atom and bond properties
        Chem.perceiveSSSR(mol, False)                      # perceive smallest set of smallest rings and store as Chem.MolecularGraph property
        Chem.setAromaticityFlags(mol, False)               # perceive aromaticity and set corresponding atom and bond properties
        
        ecfp_gen = Descr.CircularFingerprintGenerator()    # create ECFP generator instance

        if inc_config:
            ecfp_gen.includeChirality(True)                # allow atom chirality to have an impact on the ECFP generation
            Chem.calcAtomStereoDescriptors(mol, False)     # calculate atom stereo descriptors and set corresponding property for all atoms

        if inc_hs:        
            ecfp_gen.includeHydrogens(True)                # include explicit hydrogens in the ECFP generation
            Chem.makeHydrogenComplete(mol)                 # make any implicit hydrogens explicit
            
        fp = Util.BitSet()                                 # create fingerprint bitset
        fp.resize(num_bits)                                # set desired fingerprint size

        ecfp_gen.setNumIterations(radius)                  # set num. iterations (=atom. env. radius)
        ecfp_gen.generate(mol)                             # extract chracteristic structural features
        ecfp_gen.setFeatureBits(fp)                        # set bits associated with the extracted structural features

        # if needed, fp could be converted into a numpy single precision float array as follows:
        # fp = numpy.array(fp, dtype=numpy.float32)
        
        return fp

    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:

    # set parameters
    num_bits = 1024  # fingerprint size
    radius = 4       # atom environment radius
    inc_hs = True    # include explicit hydrogens
    inc_config = True # include atom chirality

    mols = [list of BasicMolecules]  # Example list of BasicMolecules


    # read and process molecules one after the other until the end of input has been reached
    try:
        for mol in mols:
            try:
                fp = genECFP(mol, num_bits, radius, inc_hs, inc_config)

                # do something with the fingerprint

            except Exception as e:
                sys.exit('Error: processing of molecule failed: ' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    out_file.close()

FAME Atom Environment Fingerprints
-------------------------------------
The FAME (Fast Atom Environment) Atom Environment Fingerprints represent the local environment around atoms in molecules.
It provide a high-resolution view of the molecular landscape, making them especially valuable for tasks like similarity searching, compound clustering, and structure-activity relationship studies. 
Their detailed representation can capture nuances that more generic fingerprints might overlook, offering a more refined perspective on molecular structures.

The following code snippet calculates and outputs the FAME descriptors of the provided molecules.

Following parameters can be set: 
- **radius**: Max. atom environment radius in number of bonds (default: 2)

.. code:: python

    import CDPL.Chem as Chem

    def genFAMEDescriptor(ctr_atom: Chem.Atom, molgraph: Chem.MolecularGraph, radius: int) -> numpy.array:
        """
        Generates the FAME descriptor for the given atom of the provided molecule.

        Parameters:
        - ctr_atom (Chem.Atom): Atom for which the FAME descriptor is to be calculated.
        - molgraph (Chem.MolecularGraph): Molecule to process.        
        - radius (int): Max. atom environment radius in number of bonds.

        Returns:
        - numpy.array: The generated FAME descriptor.
        """

        env = Chem.Fragment()                                                      # for storing of extracted environment atoms
        descr = numpy.zeros((Chem.SybylAtomType.MAX_TYPE + 1) * (radius + 1))
        
        Chem.getEnvironment(ctr_atom, molgraph, radius, env)                       # extract environment of center atom reaching
                                                                                # out up to 'radius' bonds
        for atom in env.atoms:                                                     # iterate over extracted environment atoms
            sybyl_type = Chem.getSybylType(atom)                                   # retrieve Sybyl type of environment atom
            top_dist = Chem.getTopologicalDistance(ctr_atom, atom, molgraph)       # get top. distance between center atom and environment atom
            descr[top_dist * (Chem.SybylAtomType.MAX_TYPE + 1) + sybyl_type] += 1  # instead of 1 (= Sybyl type presence) also any other numeric atom
                                                                                # property could be summed up here
        return descr
            
    def procMolecule(molgraph: Chem.MolecularGraph) -> None: 
        """
        Processes the provided molecule.

        Parameters:
        - molgraph (Chem.MolecularGraph): Molecule to process.
        """
        Chem.calcImplicitHydrogenCounts(molgraph, False)     # calculate implicit hydrogen counts and set corresponding property for all atoms
        Chem.perceiveHybridizationStates(molgraph, False)    # perceive atom hybridization states and set corresponding property for all atoms
        Chem.perceiveSSSR(molgraph, False)                   # perceive smallest set of smallest rings and store as Chem.MolecularGraph property
        Chem.setRingFlags(molgraph, False)                   # perceive cycles and set corresponding atom and bond properties
        Chem.setAromaticityFlags(molgraph, False)            # perceive aromaticity and set corresponding atom and bond properties
        Chem.perceiveSybylAtomTypes(molgraph, False)         # perceive Sybyl atom types and set corresponding property for all atoms
        Chem.calcTopologicalDistanceMatrix(molgraph, False)  # calculate topological distance matrix and store as Chem.MolecularGraph property
    
        for atom in molgraph.atoms:
            descr = genFAMEDescriptor(atom, molgraph, 5)     # generate atom environment descriptor using a radius of five bonds

            print(descr)

    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:

    mols = [list of BasicMolecules]  # Example list of BasicMolecules
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        for mol in mols: 
            try:
                procMolecule(mol)
            except Exception as e:
                sys.exit('Error: processing of molecule failed: ' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))


Force Field Calculations
==========================

Force fields are mathematical models used to predict the molecular mechanics of molecules. They are essential in molecular modeling, helping to estimate the spatial arrangement of atoms in a molecule, their potential energy, and other properties. One of the widely recognized force fields is the Merck Molecular Force Field (MMFF94). It is designed to be applicable to a broad range of molecules, making it versatile for various computational chemistry tasks.

MMFF94 Atom Charges Calculation
---------------------------------------

The MMFF94 force field, in particular, provides a method to calculate partial atomic charges, which can be crucial in understanding the electrostatic interactions of a molecule.

The following code snippet calculates and outputs the MMFF94 charges of the atoms for a given list of molecules:

.. code-block:: python

    import CDPL.Chem as Chem
    import CDPL.ForceField as ForceField

     def calc_and_output_charges(mol: Chem.BasicMolecule) -> None:
        """
        Calculates and outputs the MMFF94 charges of the atoms for the provided molecule.

        Parameters:
            mol (Chem.BasicMolecule): The molecule for which the MMFF94 charges are to be calculated.
        """
        # Various preprocessing steps to prepare the molecule
        Chem.calcImplicitHydrogenCounts(mol, False)  # calculate implicit hydrogen counts and set corresponding property for all atoms
        Chem.makeHydrogenComplete(mol)               # make all implicit hydrogens explicit
        Chem.perceiveHybridizationStates(mol, False) # perceive atom hybridization states and set corresponding property for all atoms
        Chem.perceiveSSSR(mol, False)                # perceive smallest set of smallest rings and store as Chem.MolecularGraph property
        Chem.setRingFlags(mol, False)                # perceive cycles and set corresponding atom and bond properties
        Chem.setAromaticityFlags(mol, False)         # perceive aromaticity and set corresponding atom and bond properties
    
        ForceField.perceiveMMFF94AromaticRings(mol, False)        # perceive aromatic rings according to the MMFF94 aroamticity model and store data as Chem.MolecularGraph property
        ForceField.assignMMFF94AtomTypes(mol, False, False)       # perceive MMFF94 atom types (tolerant mode) set corresponding property for all atoms
        ForceField.assignMMFF94BondTypeIndices(mol, False, False) # perceive MMFF94 bond types (tolerant mode) set corresponding property for all bonds
        ForceField.calcMMFF94AtomCharges(mol, False, False)       # calculate MMFF94 atom charges (tolerant mode) set corresponding property for all atoms


        print('- MMFF94 partial charges')
        for atom in mol.atoms:
            print('Atom #%s: %s' % (str(atom.getIndex()), str(ForceField.getMMFF94Charge(atom))))

    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:
    mols = [list_of_BasicMolecules]
    for mol in mols:
        calc_and_output_charges(mol)

For a deeper understanding of MMFF94 and its applications:

- `MMFF94 Original Publication <https://pubs.acs.org/doi/abs/10.1021/ja9621760>`_

This code provides a way to calculate the MMFF94 charges for each atom in a molecule, which can be essential for various cheminformatics analyses.


Substructure Searching and Matching
====================================


Substructure search is a fundamental operation in cheminformatics. It allows for the identification of molecules that contain a specific structural motif or pattern. This is particularly useful in various applications, such as:

- **Drug Discovery**: Identifying molecules that contain a particular pharmacophore or active site.
- **Chemical Database Querying**: Filtering large chemical databases to retrieve molecules of interest.
- **Chemical Analysis**: Identifying the presence of particular functional groups or fragments in molecules.

Filtering Molecules Based on a SMARTS Pattern
-----------------------------------------------


The SMARTS notation (SMiles ARbitrary Target Specification) is a language used to describe structural patterns in molecules. It's an extension of the SMILES notation and allows for more complex and specific pattern descriptions.
CDPKit provides a convenient way to filter molecules that match a specific structural motif described by a SMARTS pattern. This can be useful in various cheminformatics applications, such as database querying, drug discovery, and chemical analysis.


.. code-block:: python

   import CDPL.Chem as Chem

    def filter_molecules_by_smarts(input_file: str, output_file: str, smarts_pattern: str, quiet: bool = False) -> None:
        """
        Filters molecules from the input file that match the provided SMARTS pattern and writes them to the output file.
        
        Parameters:
            input_file (str): Path to the input file containing the molecules to be filtered.
            output_file (str): Path to the output file to which the filtered molecules are written.
            smarts_pattern (str): SMARTS pattern describing the structural motif to be matched.
            quiet (bool): If set to True, no progress information is printed to the console.
        """
        try:
            sub_srch_ptn = Chem.parseSMARTS(smarts_pattern)
            Chem.initSubstructureSearchQuery(sub_srch_ptn, False)
        except Exception as e:
            print(f'Error: parsing of SMARTS pattern failed: {str(e)}')
            return

        substr_srch = Chem.SubstructureSearch(sub_srch_ptn)
        reader = Chem.MoleculeReader(input_file)
        writer = Chem.MolecularGraphWriter(output_file)
        mol = Chem.BasicMolecule()
        i = 1

        try:
            while reader.read(mol):
                mol_id = Chem.getName(mol).strip() or f'Molecule_{i}'

                Chem.initSubstructureSearchTarget(mol, False)

                if substr_srch.mappingExists(mol):
                    if not quiet:
                        print(f' -> substructure found, forwarding molecule {mol_id} to output file')
                    writer.write(mol)
                elif not quiet:
                    print(f' -> substructure not found in molecule {mol_id}')

                i += 1

        except Exception as e:
            print(f'Error: {str(e)}')

        writer.close()

    ###########################################################################
    ###########################################################################
    ###########################################################################
    ################################ Example usage:
    filter_molecules_by_smarts("input.sdf", "output.sdf", "[#6]1:[#6]:[#6]:[#6]:[#6]:[#6]:1")

