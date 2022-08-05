#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
# \brief 
#
class ScreeningDBAccessor(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ScreeningDBAccessor instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %ScreeningDBAccessor instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ScreeningDBAccessor instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param name 
    #
    def open(name: str) -> None: pass

    ##
    # \brief 
    #
    def close() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getDatabaseName() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def getNumMolecules() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getNumPharmacophores() -> int: pass

    ##
    # \brief 
    # \param mol_idx 
    # \return 
    #
    def getNumPharmacophores(mol_idx: int) -> int: pass

    ##
    # \brief 
    # \param mol_idx 
    # \param mol 
    # \param overwrite 
    #
    def getMolecule(mol_idx: int, mol: CDPL.Chem.Molecule, overwrite: bool = True) -> None: pass

    ##
    # \brief 
    # \param pharm_idx 
    # \param pharm 
    # \param overwrite 
    #
    def getPharmacophore(pharm_idx: int, pharm: Pharmacophore, overwrite: bool = True) -> None: pass

    ##
    # \brief 
    # \param mol_idx 
    # \param mol_conf_idx 
    # \param pharm 
    # \param overwrite 
    #
    def getPharmacophore(mol_idx: int, mol_conf_idx: int, pharm: Pharmacophore, overwrite: bool = True) -> None: pass

    ##
    # \brief 
    # \param pharm_idx 
    # \return 
    #
    def getMoleculeIndex(pharm_idx: int) -> int: pass

    ##
    # \brief 
    # \param pharm_idx 
    # \return 
    #
    def getConformationIndex(pharm_idx: int) -> int: pass

    ##
    # \brief 
    # \param pharm_idx 
    # \return 
    #
    def getFeatureCounts(pharm_idx: int) -> FeatureTypeHistogram: pass

    ##
    # \brief 
    # \param mol_idx 
    # \param mol_conf_idx 
    # \return 
    #
    def getFeatureCounts(mol_idx: int, mol_conf_idx: int) -> FeatureTypeHistogram: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    databaseName = property(getDatabaseName)

    ##
    # \brief 
    #
    numMolecules = property(getNumMolecules)

    ##
    # \brief 
    #
    numPharmacophores = property(getNumPharmacophores)
