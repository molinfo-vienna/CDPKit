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
# \brief Sets the value of the Biomol.AtomProperty.ALT_LOCATION_ID property of <em>atom</em> to <em>id</em>.
# 
# \param atom The atom.
# \param id The new alternate-location identifier.
# 
def setAltLocationID(atom: Chem.Atom, id: str) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.ALT_LOCATION_ID property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the alternate-location identifier is set, and <tt>False</tt> otherwise.
# 
def hasAltLocationID(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.ALT_LOCATION_ID property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The alternate-location identifier.
# 
def getAltLocationID(atom: Chem.Atom) -> str: pass

##
# \brief Removes the Biomol.AtomProperty.ALT_LOCATION_ID property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearAltLocationID(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Biomol.AtomProperty.B_FACTOR property of <em>atom</em> to <em>factor</em>.
# 
# \param atom The atom.
# \param factor The new temperature (B) factor.
# 
def setBFactor(atom: Chem.Atom, factor: float) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.B_FACTOR property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the temperature factor is set, and <tt>False</tt> otherwise.
# 
def hasBFactor(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.B_FACTOR property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The temperature (B) factor.
# 
def getBFactor(atom: Chem.Atom) -> float: pass

##
# \brief Removes the Biomol.AtomProperty.B_FACTOR property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearBFactor(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Biomol.AtomProperty.CHAIN_ID property of <em>atom</em> to <em>id</em>.
# 
# \param atom The atom.
# \param id The new chain ID.
# 
def setChainID(atom: Chem.Atom, id: str) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.CHAIN_ID property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the chain ID is set, and <tt>False</tt> otherwise.
# 
def hasChainID(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.CHAIN_ID property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return A reference to the chain ID.
# 
def getChainID(atom: Chem.Atom) -> str: pass

##
# \brief Removes the Biomol.AtomProperty.CHAIN_ID property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearChainID(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Biomol.MolecularGraphProperty.CHAIN_ID property of <em>molgraph</em> to <em>id</em>.
# 
# \param molgraph The molecular graph.
# \param id The new chain ID.
# 
def setChainID(molgraph: Chem.MolecularGraph, id: str) -> None: pass

##
# \brief Tells whether <em>molgraph</em> carries an explicit Biomol.MolecularGraphProperty.CHAIN_ID property.
# 
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if the chain ID is set, and <tt>False</tt> otherwise.
# 
def hasChainID(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Biomol.MolecularGraphProperty.CHAIN_ID property of <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return A reference to the chain ID.
# 
def getChainID(molgraph: Chem.MolecularGraph) -> str: pass

##
# \brief Removes the Biomol.MolecularGraphProperty.CHAIN_ID property from <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
def clearChainID(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Biomol.AtomProperty.ENTITY_ID property of <em>atom</em> to <em>id</em>.
# 
# \param atom The atom.
# \param id The new entity ID.
# 
def setEntityID(atom: Chem.Atom, id: str) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.ENTITY_ID property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the entity ID is set, and <tt>False</tt> otherwise.
# 
def hasEntityID(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.ENTITY_ID property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return A reference to the entity ID. 
# 
# \since 1.2
# 
def getEntityID(atom: Chem.Atom) -> str: pass

##
# \brief Removes the Biomol.AtomProperty.ENTITY_ID property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearEntityID(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Biomol.AtomProperty.HETERO_ATOM_FLAG property of <em>atom</em> to <em>is_het</em>.
# 
# \param atom The atom.
# \param is_het <tt>True</tt> to mark the atom as a heteroatom, and <tt>False</tt> otherwise.
# 
def setHeteroAtomFlag(atom: Chem.Atom, is_het: bool) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.HETERO_ATOM_FLAG property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the heteroatom flag is set, and <tt>False</tt> otherwise.
# 
def hasHeteroAtomFlag(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.HETERO_ATOM_FLAG property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the atom is flagged as a heteroatom (PDB <tt>HETATM</tt> record), and <tt>False</tt> otherwise.
# 
def getHeteroAtomFlag(atom: Chem.Atom) -> bool: pass

##
# \brief Removes the Biomol.AtomProperty.HETERO_ATOM_FLAG property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearHeteroAtomFlag(atom: Chem.Atom) -> None: pass

##
# \brief Copies residue-identifying properties from heavy atoms to their attached hydrogen atoms in <em>molgraph</em>.
# 
# \param molgraph The molecular graph whose hydrogen atoms shall receive residue-identifying properties.
# \param overwrite If <tt>True</tt>, existing residue-identifying properties of hydrogen atoms are overwritten.
# \param flags The bitwise-OR combination of Biomol.AtomPropertyFlag values selecting the residue-identifying properties to propagate.
# 
def setHydrogenResidueSequenceInfo(molgraph: Chem.MolecularGraph, overwrite: bool, flags: int = 2147483648) -> None: pass

##
# \brief Sets the value of the Biomol.MolecularGraphProperty.MMCIF_DATA property of <em>molgraph</em> to <em>data</em>.
# 
# \param molgraph The molecular graph.
# \param data The new mmCIF data record.
# 
def setMMCIFData(molgraph: Chem.MolecularGraph, data: MMCIFData) -> None: pass

##
# \brief Tells whether <em>molgraph</em> carries an explicit Biomol.MolecularGraphProperty.MMCIF_DATA property.
# 
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if the mmCIF data record is set, and <tt>False</tt> otherwise.
# 
def hasMMCIFData(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Biomol.MolecularGraphProperty.MMCIF_DATA property of <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return A reference to the mmCIF data record shared reference. 
# 
# \since 1.2
# 
def getMMCIFData(molgraph: Chem.MolecularGraph) -> MMCIFData: pass

##
# \brief Removes the Biomol.MolecularGraphProperty.MMCIF_DATA property from <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
def clearMMCIFData(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Biomol.AtomProperty.MODEL_NUMBER property of <em>atom</em> to <em>model_no</em>.
# 
# \param atom The atom.
# \param model_no The new model number.
# 
def setModelNumber(atom: Chem.Atom, model_no: int) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.MODEL_NUMBER property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the model number is set, and <tt>False</tt> otherwise.
# 
def hasModelNumber(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.MODEL_NUMBER property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The model number.
# 
def getModelNumber(atom: Chem.Atom) -> int: pass

##
# \brief Removes the Biomol.AtomProperty.MODEL_NUMBER property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearModelNumber(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Biomol.MolecularGraphProperty.MODEL_NUMBER property of <em>molgraph</em> to <em>model_no</em>.
# 
# \param molgraph The molecular graph.
# \param model_no The new model number.
# 
def setModelNumber(molgraph: Chem.MolecularGraph, model_no: int) -> None: pass

##
# \brief Tells whether <em>molgraph</em> carries an explicit Biomol.MolecularGraphProperty.MODEL_NUMBER property.
# 
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if the model number is set, and <tt>False</tt> otherwise.
# 
def hasModelNumber(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Biomol.MolecularGraphProperty.MODEL_NUMBER property of <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return The model number.
# 
def getModelNumber(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Removes the Biomol.MolecularGraphProperty.MODEL_NUMBER property from <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
def clearModelNumber(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Biomol.AtomProperty.OCCUPANCY property of <em>atom</em> to <em>occupancy</em>.
# 
# \param atom The atom.
# \param occupancy The new occupancy value.
# 
def setOccupancy(atom: Chem.Atom, occupancy: float) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.OCCUPANCY property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the occupancy is set, and <tt>False</tt> otherwise.
# 
def hasOccupancy(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.OCCUPANCY property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The occupancy value.
# 
def getOccupancy(atom: Chem.Atom) -> float: pass

##
# \brief Removes the Biomol.AtomProperty.OCCUPANCY property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearOccupancy(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Biomol.MolecularGraphProperty.PDB_DATA property of <em>molgraph</em> to <em>data</em>.
# 
# \param molgraph The molecular graph.
# \param data The new PDB data record.
# 
def setPDBData(molgraph: Chem.MolecularGraph, data: PDBData) -> None: pass

##
# \brief Tells whether <em>molgraph</em> carries an explicit Biomol.MolecularGraphProperty.PDB_DATA property.
# 
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if the PDB data record is set, and <tt>False</tt> otherwise.
# 
def hasPDBData(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Biomol.MolecularGraphProperty.PDB_DATA property of <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return A reference to the PDB data record shared reference.
# 
def getPDBData(molgraph: Chem.MolecularGraph) -> PDBData: pass

##
# \brief Removes the Biomol.MolecularGraphProperty.PDB_DATA property from <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
def clearPDBData(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Biomol.AtomProperty.RESIDUE_ALT_ATOM_NAME property of <em>atom</em> to <em>name</em>.
# 
# \param atom The atom.
# \param name The new alternative residue-local atom name.
# 
def setResidueAltAtomName(atom: Chem.Atom, name: str) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.RESIDUE_ALT_ATOM_NAME property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the alternative residue-local atom name is set, and <tt>False</tt> otherwise.
# 
def hasResidueAltAtomName(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.RESIDUE_ALT_ATOM_NAME property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return A reference to the alternative residue-local atom name.
# 
def getResidueAltAtomName(atom: Chem.Atom) -> str: pass

##
# \brief Removes the Biomol.AtomProperty.RESIDUE_ALT_ATOM_NAME property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearResidueAltAtomName(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Biomol.AtomProperty.RESIDUE_ATOM_NAME property of <em>atom</em> to <em>name</em>.
# 
# \param atom The atom.
# \param name The new residue-local atom name.
# 
def setResidueAtomName(atom: Chem.Atom, name: str) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.RESIDUE_ATOM_NAME property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the residue-local atom name is set, and <tt>False</tt> otherwise.
# 
def hasResidueAtomName(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.RESIDUE_ATOM_NAME property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return A reference to the residue-local atom name.
# 
def getResidueAtomName(atom: Chem.Atom) -> str: pass

##
# \brief Removes the Biomol.AtomProperty.RESIDUE_ATOM_NAME property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearResidueAtomName(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Biomol.AtomProperty.RESIDUE_CODE property of <em>atom</em> to <em>code</em>.
# 
# \param atom The atom.
# \param code The new residue three-letter code.
# 
def setResidueCode(atom: Chem.Atom, code: str) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.RESIDUE_CODE property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the residue code is set, and <tt>False</tt> otherwise.
# 
def hasResidueCode(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.RESIDUE_CODE property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return A reference to the residue three-letter code.
# 
def getResidueCode(atom: Chem.Atom) -> str: pass

##
# \brief Removes the Biomol.AtomProperty.RESIDUE_CODE property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearResidueCode(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Biomol.MolecularGraphProperty.RESIDUE_CODE property of <em>molgraph</em> to <em>code</em>.
# 
# \param molgraph The molecular graph.
# \param code The new residue three-letter code.
# 
def setResidueCode(molgraph: Chem.MolecularGraph, code: str) -> None: pass

##
# \brief Tells whether <em>molgraph</em> carries an explicit Biomol.MolecularGraphProperty.RESIDUE_CODE property.
# 
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if the residue code is set, and <tt>False</tt> otherwise.
# 
def hasResidueCode(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Biomol.MolecularGraphProperty.RESIDUE_CODE property of <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return A reference to the residue three-letter code.
# 
def getResidueCode(molgraph: Chem.MolecularGraph) -> str: pass

##
# \brief Removes the Biomol.MolecularGraphProperty.RESIDUE_CODE property from <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
def clearResidueCode(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Biomol.AtomProperty.RESIDUE_INSERTION_CODE property of <em>atom</em> to <em>code</em>.
# 
# \param atom The atom.
# \param code The new residue insertion code.
# 
def setResidueInsertionCode(atom: Chem.Atom, code: str) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.RESIDUE_INSERTION_CODE property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the residue insertion code is set, and <tt>False</tt> otherwise.
# 
def hasResidueInsertionCode(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.RESIDUE_INSERTION_CODE property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The residue insertion code.
# 
def getResidueInsertionCode(atom: Chem.Atom) -> str: pass

##
# \brief Removes the Biomol.AtomProperty.RESIDUE_INSERTION_CODE property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearResidueInsertionCode(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Biomol.MolecularGraphProperty.RESIDUE_INSERTION_CODE property of <em>molgraph</em> to <em>code</em>.
# 
# \param molgraph The molecular graph.
# \param code The new residue insertion code.
# 
def setResidueInsertionCode(molgraph: Chem.MolecularGraph, code: str) -> None: pass

##
# \brief Tells whether <em>molgraph</em> carries an explicit Biomol.MolecularGraphProperty.RESIDUE_INSERTION_CODE property.
# 
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if the residue insertion code is set, and <tt>False</tt> otherwise.
# 
def hasResidueInsertionCode(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Biomol.MolecularGraphProperty.RESIDUE_INSERTION_CODE property of <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return The residue insertion code.
# 
def getResidueInsertionCode(molgraph: Chem.MolecularGraph) -> str: pass

##
# \brief Removes the Biomol.MolecularGraphProperty.RESIDUE_INSERTION_CODE property from <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
def clearResidueInsertionCode(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Biomol.AtomProperty.RESIDUE_LEAVING_ATOM_FLAG property of <em>atom</em> to <em>leaving</em>.
# 
# \param atom The atom.
# \param leaving <tt>True</tt> to mark the atom as a leaving atom, and <tt>False</tt> otherwise.
# 
def setResidueLeavingAtomFlag(atom: Chem.Atom, leaving: bool) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.RESIDUE_LEAVING_ATOM_FLAG property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the leaving-atom flag is set, and <tt>False</tt> otherwise.
# 
def hasResidueLeavingAtomFlag(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.RESIDUE_LEAVING_ATOM_FLAG property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the atom is a leaving atom in its parent residue, and <tt>False</tt> otherwise.
# 
def getResidueLeavingAtomFlag(atom: Chem.Atom) -> bool: pass

##
# \brief Removes the Biomol.AtomProperty.RESIDUE_LEAVING_ATOM_FLAG property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearResidueLeavingAtomFlag(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Biomol.AtomProperty.RESIDUE_LINKING_ATOM_FLAG property of <em>atom</em> to <em>linking</em>.
# 
# \param atom The atom.
# \param linking <tt>True</tt> to mark the atom as a linking atom, and <tt>False</tt> otherwise.
# 
def setResidueLinkingAtomFlag(atom: Chem.Atom, linking: bool) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.RESIDUE_LINKING_ATOM_FLAG property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the linking-atom flag is set, and <tt>False</tt> otherwise.
# 
def hasResidueLinkingAtomFlag(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.RESIDUE_LINKING_ATOM_FLAG property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the atom is a linking atom between residues, and <tt>False</tt> otherwise.
# 
def getResidueLinkingAtomFlag(atom: Chem.Atom) -> bool: pass

##
# \brief Removes the Biomol.AtomProperty.RESIDUE_LINKING_ATOM_FLAG property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearResidueLinkingAtomFlag(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Biomol.AtomProperty.RESIDUE_SEQUENCE_NUMBER property of <em>atom</em> to <em>seq_no</em>.
# 
# \param atom The atom.
# \param seq_no The new residue sequence number.
# 
def setResidueSequenceNumber(atom: Chem.Atom, seq_no: int) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.RESIDUE_SEQUENCE_NUMBER property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the residue sequence number is set, and <tt>False</tt> otherwise.
# 
def hasResidueSequenceNumber(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.RESIDUE_SEQUENCE_NUMBER property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The residue sequence number.
# 
def getResidueSequenceNumber(atom: Chem.Atom) -> int: pass

##
# \brief Removes the Biomol.AtomProperty.RESIDUE_SEQUENCE_NUMBER property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearResidueSequenceNumber(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Biomol.MolecularGraphProperty.RESIDUE_SEQUENCE_NUMBER property of <em>molgraph</em> to <em>seq_no</em>.
# 
# \param molgraph The molecular graph.
# \param seq_no The new residue sequence number.
# 
def setResidueSequenceNumber(molgraph: Chem.MolecularGraph, seq_no: int) -> None: pass

##
# \brief Tells whether <em>molgraph</em> carries an explicit Biomol.MolecularGraphProperty.RESIDUE_SEQUENCE_NUMBER property.
# 
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if the residue sequence number is set, and <tt>False</tt> otherwise.
# 
def hasResidueSequenceNumber(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Biomol.MolecularGraphProperty.RESIDUE_SEQUENCE_NUMBER property of <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return The residue sequence number.
# 
def getResidueSequenceNumber(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Removes the Biomol.MolecularGraphProperty.RESIDUE_SEQUENCE_NUMBER property from <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
def clearResidueSequenceNumber(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Biomol.AtomProperty.SERIAL_NUMBER property of <em>atom</em> to <em>serial_no</em>.
# 
# \param atom The atom.
# \param serial_no The new atom serial number.
# 
def setSerialNumber(atom: Chem.Atom, serial_no: int) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit Biomol.AtomProperty.SERIAL_NUMBER property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the atom serial number is set, and <tt>False</tt> otherwise.
# 
def hasSerialNumber(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Biomol.AtomProperty.SERIAL_NUMBER property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The atom serial number.
# 
def getSerialNumber(atom: Chem.Atom) -> int: pass

##
# \brief Removes the Biomol.AtomProperty.SERIAL_NUMBER property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearSerialNumber(atom: Chem.Atom) -> None: pass

##
# \brief Tells whether <em>atom1</em> and <em>atom2</em> belong to the same residue, comparing the atom properties selected by <em>flags</em>.
# 
# \param atom1 The first atom.
# \param atom2 The second atom.
# \param flags The bitwise-OR combination of Biomol.AtomPropertyFlag values selecting the residue-identifying properties to compare.
# 
# \return <tt>True</tt> if both atoms agree on all selected properties, and <tt>False</tt> otherwise.
# 
def areInSameResidue(atom1: Chem.Atom, atom2: Chem.Atom, flags: int = 2147483648) -> bool: pass

##
# \brief Merges alternative residue conformers in <em>mol</em> whose residue centers lie within <em>max_ctr_dist</em> of one another.
# 
# Many PDB and mmCIF structures encode alternative conformations of a residue as multiple residues with distinct alternate-location identifiers but mostly overlapping atom positions. This function detects such interfering residue copies (residues whose geometric centers are closer than <em>max_ctr_dist</em>) and combines them into a single residue with all observed atom positions, leaving the molecule's topology and residue ordering otherwise unchanged.
# 
# \param mol The molecule whose interfering residues are to be combined.
# \param max_ctr_dist The maximum distance between residue centers that still qualifies them as interfering copies of one another.
# 
# \return <tt>True</tt> if at least one residue group was combined, and <tt>False</tt> if no interfering residues were found.
# 
def combineInterferingResidueCoordinates(mol: Chem.Molecule, max_ctr_dist: float = 1.0) -> bool: pass

##
# \brief Extracts the residues of <em>macromol</em> that contain at least one atom within <em>max_dist</em> of any atom of <em>core</em>.
# 
# \param core The core molecular graph defining the reference atom positions.
# \param macromol The macromolecular graph providing the candidate residues.
# \param env_residues The output fragment receiving the extracted environment residues.
# \param max_dist The maximum allowed distance between any atom of the environment residue and the nearest core atom.
# \param append If <tt>True</tt>, the extracted residue atoms and bonds are appended to <em>env_residues</em>; if <tt>False</tt>, <em>env_residues</em> is cleared first.
# 
def extractEnvironmentResidues(core: Chem.MolecularGraph, macromol: Chem.MolecularGraph, env_residues: Chem.Fragment, max_dist: float, append: bool = False) -> None: pass

##
# \brief Extracts the residues of <em>macromol</em> that contain at least one atom within <em>max_dist</em> of any atom of <em>core</em>, using <em>coords_func</em> to obtain atom positions.
# 
# \param core The core molecular graph defining the reference atom positions.
# \param macromol The macromolecular graph providing the candidate residues.
# \param env_residues The output fragment receiving the extracted environment residues.
# \param coords_func The function used to retrieve the 3D coordinates of an atom.
# \param max_dist The maximum allowed distance between any atom of the environment residue and the nearest core atom.
# \param append If <tt>True</tt>, the extracted residue atoms and bonds are appended to <em>env_residues</em>; if <tt>False</tt>, <em>env_residues</em> is cleared first.
# 
def extractEnvironmentResidues(core: Chem.MolecularGraph, macromol: Chem.MolecularGraph, env_residues: Chem.Fragment, coords_func: Chem.Atom3DCoordinatesFunction, max_dist: float, append: bool = False) -> None: pass

##
# \brief Extracts the atoms of <em>macromol</em> that lie within <em>max_dist</em> of any atom of <em>core</em>.
# 
# \param core The core molecular graph defining the reference atom positions.
# \param macromol The macromolecular graph providing the candidate atoms.
# \param env_atoms The output fragment receiving the extracted environment atoms.
# \param max_dist The maximum allowed distance between an environment atom and the nearest core atom.
# \param inc_core_atoms If <tt>True</tt>, the atoms of <em>core</em> are also added to <em>env_atoms</em>.
# \param append If <tt>True</tt>, the extracted atoms are appended to <em>env_atoms</em>; if <tt>False</tt>, <em>env_atoms</em> is cleared first.
# 
def extractProximalAtoms(core: Chem.MolecularGraph, macromol: Chem.MolecularGraph, env_atoms: Chem.Fragment, max_dist: float, inc_core_atoms: bool = False, append: bool = False) -> None: pass

##
# \brief Extracts the atoms of <em>macromol</em> that lie within <em>max_dist</em> of any atom of <em>core</em>, using <em>coords_func</em> to obtain atom positions.
# 
# \param core The core molecular graph defining the reference atom positions.
# \param macromol The macromolecular graph providing the candidate atoms.
# \param env_atoms The output fragment receiving the extracted environment atoms.
# \param coords_func The function used to retrieve the 3D coordinates of an atom.
# \param max_dist The maximum allowed distance between an environment atom and the nearest core atom.
# \param inc_core_atoms If <tt>True</tt>, the atoms of <em>core</em> are also added to <em>env_atoms</em>.
# \param append If <tt>True</tt>, the extracted atoms are appended to <em>env_atoms</em>; if <tt>False</tt>, <em>env_atoms</em> is cleared first.
# 
def extractProximalAtoms(core: Chem.MolecularGraph, macromol: Chem.MolecularGraph, env_atoms: Chem.Fragment, coords_func: Chem.Atom3DCoordinatesFunction, max_dist: float, inc_core_atoms: bool = False, append: bool = False) -> None: pass

##
# \brief Extracts the substructure of the residue <em>atom</em> belongs to into <em>res_substruct</em>.
# 
# \param atom The query atom whose residue substructure is to be extracted.
# \param molgraph The molecular graph providing the residue context.
# \param res_substruct The output fragment receiving the extracted residue substructure.
# \param cnctd_only If <tt>True</tt>, only atoms in the connected component of <em>atom</em> within the residue are extracted.
# \param flags The bitwise-OR combination of Biomol.AtomPropertyFlag values selecting the residue-identifying properties.
# \param append If <tt>True</tt>, the extracted atoms and bonds are appended to <em>res_substruct</em>; if <tt>False</tt>, <em>res_substruct</em> is cleared first.
# 
def extractResidueSubstructure(atom: Chem.Atom, molgraph: Chem.MolecularGraph, res_substruct: Chem.Fragment, cnctd_only: bool = False, flags: int = 2147483648, append: bool = False) -> None: pass

##
# \brief Extracts the substructures of all residues represented in <em>molgraph</em> from the parent macromolecular graph <em>parent_molgraph</em>.
# 
# \param molgraph The molecular graph providing the residue selection.
# \param parent_molgraph The macromolecular graph from which to extract the residue substructures.
# \param res_substructs The output fragment receiving the extracted residue substructures.
# \param cnctd_only If <tt>True</tt>, only atoms in the connected component of each residue's representative atom are extracted.
# \param flags The bitwise-OR combination of Biomol.AtomPropertyFlag values selecting the residue-identifying properties.
# \param append If <tt>True</tt>, the extracted atoms and bonds are appended to <em>res_substructs</em>; if <tt>False</tt>, <em>res_substructs</em> is cleared first.
# 
def extractResidueSubstructures(molgraph: Chem.MolecularGraph, parent_molgraph: Chem.MolecularGraph, res_substructs: Chem.Fragment, cnctd_only: bool = False, flags: int = 2147483648, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param idx 
# \param res_code 
# \param chain_id 
# \param res_seq_no 
# \param ins_code 
# \param model_no 
# \param atom_name 
# \param serial_no 
# \return 
#
def findResidueAtom(cntnr: object, idx: int, res_code: str = '', chain_id: str = '', res_seq_no: int = -9223372036854775808, ins_code: str = '\x00', model_no: int = 0, atom_name: str = '', serial_no: int = -9223372036854775808) -> int: pass

##
# \brief 
# \param cntnr 
# \param idx 
# \param res_code 
# \param chain_id 
# \param res_seq_no 
# \param ins_code 
# \param model_no 
# \param atom_name 
# \param serial_no 
# \return 
#
def findResidue(cntnr: object, idx: int, res_code: str = '', chain_id: str = '', res_seq_no: int = -9223372036854775808, ins_code: str = '\x00', model_no: int = 0, atom_name: str = '', serial_no: int = -9223372036854775808) -> int: pass

##
# \brief Tells whether <em>atom</em> is a backbone atom of a PDB-style amino-acid or nucleotide residue.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the atom's residue-local name identifies it as a backbone atom, and <tt>False</tt> otherwise.
# 
def isPDBBackboneAtom(atom: Chem.Atom) -> bool: pass

##
# \brief Tells whether the residue-identity attributes of <em>atom</em> match the given filter values.
# 
# Each filter argument is ignored when set to its sentinel value (<tt>nullptr</tt> / <tt>0</tt> / IGNORE_SEQUENCE_NO / IGNORE_SERIAL_NO). All supplied filters must match for the function to return <tt>True</tt>.
# 
# \param atom The atom to test.
# \param res_code The PDB three-letter residue code to match (or <tt>nullptr</tt> to ignore).
# \param chain_id The PDB chain ID to match (or <tt>nullptr</tt> to ignore).
# \param res_seq_no The PDB residue sequence number to match (or IGNORE_SEQUENCE_NO to ignore).
# \param ins_code The PDB insertion code to match (or <tt>0</tt> to ignore).
# \param model_no The PDB model number to match (or <tt>0</tt> to ignore).
# \param atom_name The PDB atom name to match (or <tt>nullptr</tt> to ignore).
# \param serial_no The PDB atom serial number to match (or IGNORE_SERIAL_NO to ignore).
# 
# \return <tt>True</tt> if all supplied filters match, and <tt>False</tt> otherwise.
# 
def matchesResidueInfo(atom: Chem.Atom, res_code: str = '', chain_id: str = '', res_seq_no: int = -9223372036854775808, ins_code: str = '\x00', model_no: int = 0, atom_name: str = '', serial_no: int = -9223372036854775808) -> bool: pass

##
# \brief Tells whether the residue-identity attributes of <em>molgraph</em> match the given filter values.
# 
# Each filter argument is ignored when set to its sentinel value (<tt>nullptr</tt> / <tt>0</tt> / IGNORE_SEQUENCE_NO). All supplied filters must match for the function to return <tt>True</tt>.
# 
# \param molgraph The molecular graph to test.
# \param res_code The PDB three-letter residue code to match (or <tt>nullptr</tt> to ignore).
# \param chain_id The PDB chain ID to match (or <tt>nullptr</tt> to ignore).
# \param res_seq_no The PDB residue sequence number to match (or IGNORE_SEQUENCE_NO to ignore).
# \param ins_code The PDB insertion code to match (or <tt>0</tt> to ignore).
# \param model_no The PDB model number to match (or <tt>0</tt> to ignore).
# 
# \return <tt>True</tt> if all supplied filters match, and <tt>False</tt> otherwise.
# 
def matchesResidueInfo(molgraph: Chem.MolecularGraph, res_code: str = '', chain_id: str = '', res_seq_no: int = -9223372036854775808, ins_code: str = '\x00', model_no: int = 0) -> bool: pass

##
# \brief Sets the Biomol.ControlParameter.APPLY_DICT_ATOM_TYPES parameter of <em>cntnr</em> to <em>apply</em>.
# 
# \param cntnr The control-parameter container.
# \param apply <tt>True</tt> to apply dictionary-derived atom types, and <tt>False</tt> to skip them.
# 
def setApplyDictAtomTypesParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.APPLY_DICT_ATOM_TYPES parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasApplyDictAtomTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.APPLY_DICT_ATOM_TYPES parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The apply-dictionary-atom types flag. 
# 
# \since 1.2
# 
def getApplyDictAtomTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.APPLY_DICT_ATOM_TYPES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearApplyDictAtomTypesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.APPLY_DICT_FORMAL_CHARGES parameter of <em>cntnr</em> to <em>apply</em>.
# 
# \param cntnr The control-parameter container.
# \param apply <tt>True</tt> to apply dictionary-derived formal charges, and <tt>False</tt> to skip them.
# 
def setApplyDictFormalChargesParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.APPLY_DICT_FORMAL_CHARGES parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasApplyDictFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.APPLY_DICT_FORMAL_CHARGES parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The apply-dictionary-formal charges flag. 
# 
# \since 1.2
# 
def getApplyDictFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.APPLY_DICT_FORMAL_CHARGES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearApplyDictFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.CALC_MISSING_FORMAL_CHARGES parameter of <em>cntnr</em> to <em>calc</em>.
# 
# \param cntnr The control-parameter container.
# \param calc <tt>True</tt> to calculate missing formal charges, and <tt>False</tt> to leave them unset.
# 
def setCalcMissingFormalChargesParameter(cntnr: Base.ControlParameterContainer, calc: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.CALC_MISSING_FORMAL_CHARGES parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasCalcMissingFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.CALC_MISSING_FORMAL_CHARGES parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The calc-missing-formal charges flag. 
# 
# \since 1.2
# 
def getCalcMissingFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.CALC_MISSING_FORMAL_CHARGES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearCalcMissingFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.CHECK_LINE_LENGTH parameter of <em>cntnr</em> to <em>check</em>.
# 
# \param cntnr The control-parameter container.
# \param check <tt>True</tt> to enable line-length checking, and <tt>False</tt> to disable it.
# 
def setCheckLineLengthParameter(cntnr: Base.ControlParameterContainer, check: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.CHECK_LINE_LENGTH parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasCheckLineLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.CHECK_LINE_LENGTH parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The check-line-length flag.
# 
def getCheckLineLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.CHECK_LINE_LENGTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearCheckLineLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.COMBINE_INTERFERING_RESIDUE_COORDINATES parameter of <em>cntnr</em> to <em>comb</em>.
# 
# \param cntnr The control-parameter container.
# \param comb <tt>True</tt> to merge interfering residue conformers, and <tt>False</tt> to keep them separate.
# 
def setCombineInterferingResidueCoordinatesParameter(cntnr: Base.ControlParameterContainer, comb: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.COMBINE_INTERFERING_RESIDUE_COORDINATES parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasCombineInterferingResidueCoordinatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.COMBINE_INTERFERING_RESIDUE_COORDINATES parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The combine-interfering-residue-coordinates flag.
# 
def getCombineInterferingResidueCoordinatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.COMBINE_INTERFERING_RESIDUE_COORDINATES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearCombineInterferingResidueCoordinatesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.MMCIF_APPLY_DICT_ATOM_BONDING parameter of <em>cntnr</em> to <em>apply</em>.
# 
# \param cntnr The control-parameter container.
# \param apply <tt>True</tt> to apply dictionary-derived atom-bonding during mmCIF input, and <tt>False</tt> to skip it.
# 
def setMMCIFApplyDictAtomBondingParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.MMCIF_APPLY_DICT_ATOM_BONDING parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMMCIFApplyDictAtomBondingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.MMCIF_APPLY_DICT_ATOM_BONDING parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The mmCIF-apply-dict-atom-bonding flag. 
# 
# \since 1.2
# 
def getMMCIFApplyDictAtomBondingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.MMCIF_APPLY_DICT_ATOM_BONDING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMMCIFApplyDictAtomBondingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.MMCIF_APPLY_DICT_BOND_ORDERS parameter of <em>cntnr</em> to <em>apply</em>.
# 
# \param cntnr The control-parameter container.
# \param apply <tt>True</tt> to apply dictionary-derived bond orders during mmCIF input, and <tt>False</tt> to skip them.
# 
def setMMCIFApplyDictBondOrdersParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.MMCIF_APPLY_DICT_BOND_ORDERS parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMMCIFApplyDictBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.MMCIF_APPLY_DICT_BOND_ORDERS parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The mmCIF-apply-dict-bond-orders flag. 
# 
# \since 1.2
# 
def getMMCIFApplyDictBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.MMCIF_APPLY_DICT_BOND_ORDERS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMMCIFApplyDictBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output <tt>True</tt> to emit biopolymer residues using the <tt>chem_comp</tt> data category, and <tt>False</tt> to use the regular polymer-residue encoding.
# 
def setMMCIFOutputBiopolymersAsChemCompParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMMCIFOutputBiopolymersAsChemCompParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The mmCIF-output-biopolymers-as-chem-comp flag. 
# 
# \since 1.2
# 
def getMMCIFOutputBiopolymersAsChemCompParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMMCIFOutputBiopolymersAsChemCompParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.MMCIF_OUTPUT_DATA_POSTPROC_FUNCTION parameter of <em>cntnr</em> to <em>func</em>.
# 
# \param cntnr The control-parameter container.
# \param func The new mmCIF-output data-postprocessing function.
# 
def setMMCIFOutputDataPostprocFunctionParameter(cntnr: Base.ControlParameterContainer, func: MMCIFDataProcessingFunction) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.MMCIF_OUTPUT_DATA_POSTPROC_FUNCTION parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMMCIFOutputDataPostprocFunctionParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.MMCIF_OUTPUT_DATA_POSTPROC_FUNCTION parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return A reference to the mmCIF-output data-postprocessing function. 
# 
# \since 1.2
# 
def getMMCIFOutputDataPostprocFunctionParameter(cntnr: Base.ControlParameterContainer) -> MMCIFDataProcessingFunction: pass

##
# \brief Removes the Biomol.ControlParameter.MMCIF_OUTPUT_DATA_POSTPROC_FUNCTION parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMMCIFOutputDataPostprocFunctionParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES parameter of <em>cntnr</em> to <em>apply</em>.
# 
# \param cntnr The control-parameter container.
# \param apply <tt>True</tt> to apply dictionary-derived atom-bonding to non-standard residues, and <tt>False</tt> to skip it.
# 
def setPDBApplyDictAtomBondingToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPDBApplyDictAtomBondingToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The PDB-apply-dict-atom-bonding-to-non-std-residues flag.
# 
def getPDBApplyDictAtomBondingToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPDBApplyDictAtomBondingToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES parameter of <em>cntnr</em> to <em>apply</em>.
# 
# \param cntnr The control-parameter container.
# \param apply <tt>True</tt> to apply dictionary-derived atom-bonding to standard residues, and <tt>False</tt> to skip it.
# 
def setPDBApplyDictAtomBondingToStdResiduesParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPDBApplyDictAtomBondingToStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The PDB-apply-dict-atom-bonding-to-std-residues flag.
# 
def getPDBApplyDictAtomBondingToStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPDBApplyDictAtomBondingToStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES parameter of <em>cntnr</em> to <em>apply</em>.
# 
# \param cntnr The control-parameter container.
# \param apply <tt>True</tt> to apply dictionary-derived bond orders to non-standard residues, and <tt>False</tt> to skip it.
# 
def setPDBApplyDictBondOrdersToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPDBApplyDictBondOrdersToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The PDB-apply-dict-bond-orders-to-non-std-residues flag.
# 
def getPDBApplyDictBondOrdersToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPDBApplyDictBondOrdersToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.PDB_APPLY_DICT_BOND_ORDERS_TO_STD_RESIDUES parameter of <em>cntnr</em> to <em>apply</em>.
# 
# \param cntnr The control-parameter container.
# \param apply <tt>True</tt> to apply dictionary-derived bond orders to standard residues, and <tt>False</tt> to skip it.
# 
def setPDBApplyDictBondOrdersToStdResiduesParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PDB_APPLY_DICT_BOND_ORDERS_TO_STD_RESIDUES parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPDBApplyDictBondOrdersToStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PDB_APPLY_DICT_BOND_ORDERS_TO_STD_RESIDUES parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The PDB-apply-dict-bond-orders-to-std-residues flag.
# 
def getPDBApplyDictBondOrdersToStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.PDB_APPLY_DICT_BOND_ORDERS_TO_STD_RESIDUES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPDBApplyDictBondOrdersToStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS parameter of <em>cntnr</em> to <em>deduce</em>.
# 
# \param cntnr The control-parameter container.
# \param deduce <tt>True</tt> to deduce bond orders from the duplication pattern of bonded atom pairs in <tt>CONECT</tt> records, and <tt>False</tt> to skip the deduction.
# 
def setPDBDeduceBondOrdersFromCONECTRecordsParameter(cntnr: Base.ControlParameterContainer, deduce: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPDBDeduceBondOrdersFromCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The PDB-deduce-bond-orders-from-CONECT-records flag.
# 
def getPDBDeduceBondOrdersFromCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPDBDeduceBondOrdersFromCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param evaluate 
#
def setPDBEvaluateMASTERRecordParameter(cntnr: Base.ControlParameterContainer, evaluate: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PDB_EVALUATE_MASTER_RECORD parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPDBEvaluateMASTERRecordParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PDB_EVALUATE_MASTER_RECORD parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The PDB-evaluate-MASTER-record flag.
# 
def getPDBEvaluateMASTERRecordParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.PDB_EVALUATE_MASTER_RECORD parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPDBEvaluateMASTERRecordParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.PDB_FORMAT_VERSION parameter of <em>cntnr</em> to <em>ver</em>.
# 
# \param cntnr The control-parameter container.
# \param ver The new PDB format version (see Biomol.PDBFormatVersion).
# 
def setPDBFormatVersionParameter(cntnr: Base.ControlParameterContainer, ver: int) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PDB_FORMAT_VERSION parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPDBFormatVersionParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PDB_FORMAT_VERSION parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The PDB format version (see Biomol.PDBFormatVersion).
# 
def getPDBFormatVersionParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Biomol.ControlParameter.PDB_FORMAT_VERSION parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPDBFormatVersionParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.PDB_IGNORE_CONECT_RECORDS parameter of <em>cntnr</em> to <em>ignore</em>.
# 
# \param cntnr The control-parameter container.
# \param ignore <tt>True</tt> to skip <tt>CONECT</tt> records during PDB data input, and <tt>False</tt> to process them.
# 
def setPDBIgnoreCONECTRecordsParameter(cntnr: Base.ControlParameterContainer, ignore: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PDB_IGNORE_CONECT_RECORDS parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPDBIgnoreCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PDB_IGNORE_CONECT_RECORDS parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The PDB-ignore-CONECT-records flag. 
# 
# \since 1.3
# 
def getPDBIgnoreCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.PDB_IGNORE_CONECT_RECORDS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPDBIgnoreCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.PDB_IGNORE_FORMAL_CHARGE_FIELD parameter of <em>cntnr</em> to <em>ignore</em>.
# 
# \param cntnr The control-parameter container.
# \param ignore <tt>True</tt> to ignore the formal charge field of <tt>ATOM/<tt>HETATM</tt> records</tt>, and <tt>False</tt> to honor it.
# 
def setPDBIgnoreFormalChargeFieldParameter(cntnr: Base.ControlParameterContainer, ignore: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PDB_IGNORE_FORMAL_CHARGE_FIELD parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPDBIgnoreFormalChargeFieldParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PDB_IGNORE_FORMAL_CHARGE_FIELD parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The PDB-ignore-formal charge-field flag.
# 
def getPDBIgnoreFormalChargeFieldParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.PDB_IGNORE_FORMAL_CHARGE_FIELD parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPDBIgnoreFormalChargeFieldParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS_FOR_ALL_BONDS parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output <tt>True</tt> to write <tt>CONECT</tt> records for all bonds (and not only for non-standard ones), and <tt>False</tt> to write them only for non-standard bonds.
# 
def setPDBOutputCONECTRecordsForAllBondsParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS_FOR_ALL_BONDS parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPDBOutputCONECTRecordsForAllBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS_FOR_ALL_BONDS parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The PDB-output-CONECT-records-for-all-bonds flag. 
# 
# \since 1.2
# 
def getPDBOutputCONECTRecordsForAllBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS_FOR_ALL_BONDS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPDBOutputCONECTRecordsForAllBondsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output <tt>True</tt> to write <tt>CONECT</tt> records, and <tt>False</tt> to skip them.
# 
def setPDBOutputCONECTRecordsParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPDBOutputCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The PDB-output-CONECT-records flag. 
# 
# \since 1.2
# 
def getPDBOutputCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPDBOutputCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS_REFLECTING_BOND_ORDER parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output <tt>True</tt> to encode the bond order via the duplication count of bonded atom pairs in <tt>CONECT</tt> records, and <tt>False</tt> to emit each pair only once.
# 
def setPDBOutputCONECTRecordsReflectingBondOrderParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS_REFLECTING_BOND_ORDER parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPDBOutputCONECTRecordsReflectingBondOrderParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS_REFLECTING_BOND_ORDER parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The PDB-output-CONECT-records-reflecting-bond-order flag. 
# 
# \since 1.2
# 
def getPDBOutputCONECTRecordsReflectingBondOrderParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS_REFLECTING_BOND_ORDER parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPDBOutputCONECTRecordsReflectingBondOrderParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.PDB_OUTPUT_FORMAL_CHARGES parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output <tt>True</tt> to write the formal charge field of <tt>ATOM/<tt>HETATM</tt> records</tt>, and <tt>False</tt> to leave it blank.
# 
def setPDBOutputFormalChargesParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PDB_OUTPUT_FORMAL_CHARGES parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPDBOutputFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PDB_OUTPUT_FORMAL_CHARGES parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The PDB-output-formal charges flag. 
# 
# \since 1.2
# 
def getPDBOutputFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.PDB_OUTPUT_FORMAL_CHARGES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPDBOutputFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.PDB_TRUNCATE_LINES parameter of <em>cntnr</em> to <em>trunc</em>.
# 
# \param cntnr The control-parameter container.
# \param trunc <tt>True</tt> to truncate output PDB data lines exceeding the maximum allowed line length, and <tt>False</tt> to fail the write operation instead.
# 
def setPDBTruncateLinesParameter(cntnr: Base.ControlParameterContainer, trunc: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PDB_TRUNCATE_LINES parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPDBTruncateLinesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PDB_TRUNCATE_LINES parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The PDB-truncate-lines flag.
# 
def getPDBTruncateLinesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.PDB_TRUNCATE_LINES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPDBTruncateLinesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.PERCEIVE_MISSING_BOND_ORDERS parameter of <em>cntnr</em> to <em>perceive</em>.
# 
# \param cntnr The control-parameter container.
# \param perceive <tt>True</tt> to perceive missing bond orders, and <tt>False</tt> to leave them unset.
# 
def setPerceiveMissingBondOrdersParameter(cntnr: Base.ControlParameterContainer, perceive: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.PERCEIVE_MISSING_BOND_ORDERS parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPerceiveMissingBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.PERCEIVE_MISSING_BOND_ORDERS parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The perceive-missing-bond-orders flag. 
# 
# \since 1.2
# 
def getPerceiveMissingBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.PERCEIVE_MISSING_BOND_ORDERS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPerceiveMissingBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.RESIDUE_DICTIONARY parameter of <em>cntnr</em> to <em>dict</em>.
# 
# \param cntnr The control-parameter container.
# \param dict The new residue dictionary.
# 
def setResidueDictionaryParameter(cntnr: Base.ControlParameterContainer, dict: ResidueDictionary) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.RESIDUE_DICTIONARY parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasResidueDictionaryParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.RESIDUE_DICTIONARY parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return A reference to the residue-dictionary shared reference. 
# 
# \since 1.2
# 
def getResidueDictionaryParameter(cntnr: Base.ControlParameterContainer) -> ResidueDictionary: pass

##
# \brief Removes the Biomol.ControlParameter.RESIDUE_DICTIONARY parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearResidueDictionaryParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Biomol.ControlParameter.STRICT_ERROR_CHECKING parameter of <em>cntnr</em> to <em>strict</em>.
# 
# \param cntnr The control-parameter container.
# \param strict <tt>True</tt> to enable strict error checking, and <tt>False</tt> to disable it.
# 
def setStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer, strict: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Biomol.ControlParameter.STRICT_ERROR_CHECKING parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Biomol.ControlParameter.STRICT_ERROR_CHECKING parameter of <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The strict-error-checking flag.
# 
def getStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Biomol.ControlParameter.STRICT_ERROR_CHECKING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> None: pass
