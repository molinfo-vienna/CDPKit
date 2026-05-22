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
# \brief Returns the number of rotatable bonds in <em>molgraph</em> (see ConfGen.isRotatableBond()).
# 
# \param molgraph The molecular graph.
# \param het_h_rotors If <tt>True</tt>, rotors involving only heteroatom-bound hydrogens are also counted as rotatable.
# 
# \return The rotatable-bond count.
# 
def getRotatableBondCount(molgraph: Chem.MolecularGraph, het_h_rotors: bool) -> int: pass

##
# \brief Sets bits in <em>bond_mask</em> for every fragment-link bond of <em>molgraph</em> (see ConfGen.isFragmentLinkBond()).
# 
# \param molgraph The molecular graph.
# \param bond_mask The output bit mask sized to the number of bonds in <em>molgraph</em>.
# \param reset If <tt>True</tt>, the output mask is cleared before bits are set.
# 
# \return The number of fragment-link bonds encountered.
# 
def createFragmentLinkBondMask(molgraph: Chem.MolecularGraph, bond_mask: Util.BitSet, reset: bool = True) -> int: pass

##
# \brief Sets bits in <em>bond_mask</em> for every rotatable bond of <em>molgraph</em> (see ConfGen.isRotatableBond()).
# 
# \param molgraph The molecular graph.
# \param bond_mask The output bit mask sized to the number of bonds in <em>molgraph</em>.
# \param het_h_rotors If <tt>True</tt>, rotors involving only heteroatom-bound hydrogens are also counted as rotatable.
# \param reset If <tt>True</tt>, the output mask is cleared before bits are set.
# 
# \return The number of rotatable bonds encountered.
# 
def createRotatableBondMask(molgraph: Chem.MolecularGraph, bond_mask: Util.BitSet, het_h_rotors: bool, reset: bool = True) -> int: pass

##
# \brief Sets bits in <em>bond_mask</em> for every rotatable bond of <em>molgraph</em> that is not already marked in <em>excl_bond_mask</em>.
# 
# \param molgraph The molecular graph.
# \param excl_bond_mask The bit mask of bonds to exclude from rotatable-bond consideration.
# \param bond_mask The output bit mask sized to the number of bonds in <em>molgraph</em>.
# \param het_h_rotors If <tt>True</tt>, rotors involving only heteroatom-bound hydrogens are also counted as rotatable.
# \param reset If <tt>True</tt>, the output mask is cleared before bits are set.
# 
# \return The number of rotatable bonds encountered.
# 
def createRotatableBondMask(molgraph: Chem.MolecularGraph, excl_bond_mask: Util.BitSet, bond_mask: Util.BitSet, het_h_rotors: bool, reset: bool = True) -> int: pass

##
# \brief Initializes <em>molgraph</em> as a fixed-substructure pattern matched against the supplied <em>tmplt</em> template.
# 
# \param molgraph The molecular graph to initialize.
# \param tmplt The template molecular graph (may be <tt>nullptr</tt>).
# 
# \return <tt>True</tt> if the initialization succeeded, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def initFixedSubstructurePattern(molgraph: Chem.MolecularGraph, tmplt: Chem.MolecularGraph) -> bool: pass

##
# \brief Initializes <em>molgraph</em> as a fixed-substructure template (perception of atom/bond properties and optionally match expressions).
# 
# \param molgraph The molecular graph that will serve as the template.
# \param init_match_expr If <tt>True</tt>, atom/bond match expressions are also generated.
# 
# \since 1.1
# 
def initFixedSubstructureTemplate(molgraph: Chem.MolecularGraph, init_match_expr: bool) -> None: pass

##
# \brief Tells whether <em>bond</em> is a link bond between two fragments under the fragment-based conformer-generation heuristics.
# 
# \param bond The bond to test.
# \param molgraph The parent molecular graph.
# 
# \return <tt>True</tt> if <em>bond</em> connects two fragments, and <tt>False</tt> otherwise.
# 
def isFragmentLinkBond(bond: Chem.Bond, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Tells whether <em>bond</em> is rotatable under the conformer-generation rotatable-bond heuristics.
# 
# \param bond The bond to test.
# \param molgraph The parent molecular graph.
# \param het_h_rotors If <tt>True</tt>, rotors involving only heteroatom-bound hydrogens are also counted as rotatable.
# 
# \return <tt>True</tt> if <em>bond</em> is rotatable, and <tt>False</tt> otherwise.
# 
def isRotatableBond(bond: Chem.Bond, molgraph: Chem.MolecularGraph, het_h_rotors: bool) -> bool: pass

##
# \brief Parameterizes the MMFF94 interactions of <em>molgraph</em> via <em>parameterizer</em> and stores them in <em>param_data</em>.
# 
# \param molgraph The molecular graph.
# \param parameterizer The MMFF94 interaction parameterizer.
# \param param_data The output interaction-data structure.
# \param ff_type The MMFF94 force-field variant (see ForceField.MMFF94InteractionParameterizer for valid values).
# \param strict If <tt>True</tt>, missing parameters are treated as fatal errors.
# \param estat_de_const The dielectric constant used in the electrostatic-energy term.
# \param estat_dist_expo The distance exponent used in the electrostatic-energy term.
# 
# \return A ConfGen.ReturnCode value reporting the outcome of the parameterization.
# 
def parameterizeMMFF94Interactions(molgraph: Chem.MolecularGraph, parameterizer: ForceField.MMFF94InteractionParameterizer, param_data: ForceField.MMFF94InteractionData, ff_type: int, strict: bool, estat_de_const: float, estat_dist_expo: float) -> int: pass

##
# \brief Classifies <em>molgraph</em> as a ConfGen.FragmentType (chain, flexible ring, rigid ring, etc.).
# 
# \param molgraph The molecular graph.
# 
# \return The ConfGen.FragmentType identifier.
# 
def perceiveFragmentType(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Prepares <em>mol</em> for conformer generation by completing its hydrogens, perceiving SSSR, ring flags, implicit hydrogen counts, hybridization states, aromaticity and (optionally) canonicalizing the atom ordering.
# 
# \param mol The molecule to prepare (modified in place).
# \param canonicalize If <tt>True</tt>, the atom ordering of <em>mol</em> is canonicalized.
# 
def prepareForConformerGeneration(mol: Chem.Molecule, canonicalize: bool = False) -> None: pass

##
# \brief Configures the fixed-substructure handling of <em>molgraph</em> using the matches produced by <em>sub_search</em>.
# 
# \param sub_search The common-connected-substructure-search engine providing the matches.
# \param max_num_matches The maximum number of matches to process (<em>0</em> means unlimited).
# \param molgraph The molecular graph that holds the input atoms (modified in place).
# \param fixed_substr The output fragment receiving the matched atoms/bonds.
# \param fixed_substr_coords Optional output array receiving the 3D coordinates of the fixed substructure atoms.
# 
# \return The number of matches processed. 
# 
# \since 1.1
# 
def setupFixedSubstructureData(sub_search: Chem.CommonConnectedSubstructureSearch, max_num_matches: int, molgraph: Chem.MolecularGraph, fixed_substr: Chem.Fragment, fixed_substr_coords: Math.Vector3DArray = 0) -> int: pass

##
# \brief Configures the fixed-substructure handling of <em>molgraph</em> using the matches produced by <em>sub_search</em>.
# 
# \param sub_search The common-connected-substructure-search engine providing the matches.
# \param max_num_matches The maximum number of matches to process (<em>0</em> means unlimited).
# \param molgraph The molecular graph that holds the input atoms (modified in place).
# \param fixed_substr The output fragment receiving the matched atoms/bonds.
# \param fixed_substr_coords Optional output array receiving the 3D coordinates of the fixed substructure atoms.
# 
# \return The number of matches processed. 
# 
# \since 1.1
# 
def setupFixedSubstructureData(sub_search: Chem.SubstructureSearch, max_num_matches: int, molgraph: Chem.MolecularGraph, fixed_substr: Chem.Fragment, fixed_substr_coords: Math.Vector3DArray = 0) -> int: pass

##
# \brief 
# \param cntnr 
# \param strict 
#
def setStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer, strict: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> None: pass
