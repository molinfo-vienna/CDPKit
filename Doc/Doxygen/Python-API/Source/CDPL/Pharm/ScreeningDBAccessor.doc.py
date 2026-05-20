#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

##
# \brief Abstract base class for accessors that read the data stored in pharmacophore screening databases.
# 
class ScreeningDBAccessor(Boost.Python.instance):

    ##
    # \brief Initializes the \c %ScreeningDBAccessor instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ScreeningDBAccessor instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ScreeningDBAccessor instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Opens the screening database identified by <em>name</em>.
    # 
    # \param name The database name (path, URI, etc., interpreted by the concrete subclass).
    # 
    def open(name: str) -> None: pass

    ##
    # \brief Closes the currently open database.
    # 
    def close() -> None: pass

    ##
    # \brief Returns the name of the currently open database.
    # 
    # \return A reference to the database name.
    # 
    def getDatabaseName() -> str: pass

    ##
    # \brief Returns the total number of molecules stored in the database.
    # 
    # \return The molecule count.
    # 
    def getNumMolecules() -> int: pass

    ##
    # \brief Returns the total number of pharmacophores stored in the database (one per molecule conformer).
    # 
    # \return The pharmacophore count.
    # 
    def getNumPharmacophores() -> int: pass

    ##
    # \brief Returns the number of pharmacophores stored for the molecule at index <em>mol_idx</em>.
    # 
    # \param mol_idx The zero-based molecule index.
    # 
    # \return The pharmacophore count for the molecule.
    # 
    def getNumPharmacophores(mol_idx: int) -> int: pass

    ##
    # \brief Reads the molecule at index <em>mol_idx</em> into <em>mol</em>.
    # 
    # \param mol_idx The zero-based molecule index.
    # \param mol The output molecule.
    # \param overwrite If <tt>True</tt>, <em>mol</em> is cleared before reading; if <tt>False</tt>, the atoms/bonds are appended.
    # 
    def getMolecule(mol_idx: int, mol: Chem.Molecule, overwrite: bool = True) -> None: pass

    ##
    # \brief Reads the pharmacophore at index <em>pharm_idx</em> into <em>pharm</em>.
    # 
    # \param pharm_idx The zero-based pharmacophore index (across all molecules).
    # \param pharm The output pharmacophore.
    # \param overwrite If <tt>True</tt>, <em>pharm</em> is cleared before reading; if <tt>False</tt>, the features are appended.
    # 
    def getPharmacophore(pharm_idx: int, pharm: Pharmacophore, overwrite: bool = True) -> None: pass

    ##
    # \brief Reads the pharmacophore corresponding to conformer <em>mol_conf_idx</em> of molecule <em>mol_idx</em> into <em>pharm</em>.
    # 
    # \param mol_idx The zero-based molecule index.
    # \param mol_conf_idx The zero-based conformer index within the molecule.
    # \param pharm The output pharmacophore.
    # \param overwrite If <tt>True</tt>, <em>pharm</em> is cleared before reading; if <tt>False</tt>, the features are appended.
    # 
    def getPharmacophore(mol_idx: int, mol_conf_idx: int, pharm: Pharmacophore, overwrite: bool = True) -> None: pass

    ##
    # \brief Returns the molecule index of the pharmacophore at index <em>pharm_idx</em>.
    # 
    # \param pharm_idx The zero-based pharmacophore index.
    # 
    # \return The zero-based molecule index.
    # 
    def getMoleculeIndex(pharm_idx: int) -> int: pass

    ##
    # \brief Returns the conformer index within the parent molecule of the pharmacophore at index <em>pharm_idx</em>.
    # 
    # \param pharm_idx The zero-based pharmacophore index.
    # 
    # \return The zero-based conformer index.
    # 
    def getConformationIndex(pharm_idx: int) -> int: pass

    ##
    # \brief Returns the cached per Pharm.FeatureType frequency histogram of the pharmacophore at index <em>pharm_idx</em>.
    # 
    # \param pharm_idx The zero-based pharmacophore index.
    # 
    # \return A reference to the feature-type histogram.
    # 
    def getFeatureCounts(pharm_idx: int) -> FeatureTypeHistogram: pass

    ##
    # \brief Returns the cached per Pharm.FeatureType frequency histogram of conformer <em>mol_conf_idx</em> of molecule <em>mol_idx</em>.
    # 
    # \param mol_idx The zero-based molecule index.
    # \param mol_conf_idx The zero-based conformer index within the molecule.
    # 
    # \return A reference to the feature-type histogram.
    # 
    def getFeatureCounts(mol_idx: int, mol_conf_idx: int) -> FeatureTypeHistogram: pass

    objectID = property(getObjectID)

    databaseName = property(getDatabaseName)

    numMolecules = property(getNumMolecules)

    numPharmacophores = property(getNumPharmacophores)
