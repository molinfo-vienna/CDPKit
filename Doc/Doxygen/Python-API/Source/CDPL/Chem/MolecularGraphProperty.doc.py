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
# \brief Provides keys for built-in Chem.MolecularGraph properties.
# 
class MolecularGraphProperty(Boost.Python.instance):

    ##
    # \brief Specifies the name (or title) of the molecular graph.
    # 
    # \valuetype  <tt>std::string</tt>
    # 
    NAME = CDPL.Base.LookupKey('NAME')

    ##
    # \brief Specifies a free-text comment associated with the molecular graph.
    # 
    # \valuetype  <tt>std::string</tt>
    # 
    COMMENT = CDPL.Base.LookupKey('COMMENT')

    ##
    # \brief Specifies a creation/modification timestamp associated with the molecular graph.
    # 
    # \valuetype  <tt>std::time_t</tt>
    # 
    TIMESTAMP = CDPL.Base.LookupKey('TIMESTAMP')

    ##
    # \brief Specifies the components of the molecular graph.
    # 
    # \valuetype  Chem.FragmentList.SharedPointer
    # 
    COMPONENTS = CDPL.Base.LookupKey('COMPONENTS')

    ##
    # \brief Specifies the complete set of rings of the molecular graph.
    # 
    # \valuetype  Chem.FragmentList.SharedPointer
    # 
    RINGS = CDPL.Base.LookupKey('RINGS')

    ##
    # \brief Specifies the smallest set of smallest rings (SSSR) of the molecular graph.
    # 
    # \valuetype  Chem.FragmentList.SharedPointer
    # 
    SSSR = CDPL.Base.LookupKey('SSSR')

    ##
    # \brief Specifies the union of all rings (the cyclic substructure) of the molecular graph.
    # 
    # \valuetype  Chem.Fragment.SharedPointer
    # 
    CYCLIC_SUBSTRUCTURE = CDPL.Base.LookupKey('CYCLIC_SUBSTRUCTURE')

    ##
    # \brief Specifies the union of all aromatic rings (the aromatic substructure) of the molecular graph.
    # 
    # \valuetype  Chem.Fragment.SharedPointer
    # 
    AROMATIC_SUBSTRUCTURE = CDPL.Base.LookupKey('AROMATIC_SUBSTRUCTURE')

    ##
    # \brief Specifies the perceived &pi;-electron systems of the molecular graph.
    # 
    # \valuetype  Chem.ElectronSystemList.SharedPointer
    # 
    PI_ELECTRON_SYSTEMS = CDPL.Base.LookupKey('PI_ELECTRON_SYSTEMS')

    ##
    # \brief Specifies the substructure match constraints associated with the molecular graph.
    # 
    # \valuetype  Chem.MatchConstraintList.SharedPointer
    # 
    MATCH_CONSTRAINTS = CDPL.Base.LookupKey('MATCH_CONSTRAINTS')

    ##
    # \brief Specifies the substructure match expression associated with the molecular graph.
    # 
    # \valuetype  Chem.MatchExpression<Chem.MolecularGraph>.SharedPointer
    # 
    MATCH_EXPRESSION = CDPL.Base.LookupKey('MATCH_EXPRESSION')

    ##
    # \brief Specifies molecular graph component groups for substructure searching.
    # 
    # \valuetype  Chem.FragmentList.SharedPointer
    # 
    COMPONENT_GROUPS = CDPL.Base.LookupKey('COMPONENT_GROUPS')

    ##
    # \brief Specifies the topological (bond count) all-pair distance matrix.
    # 
    # \valuetype  Math.ULMatrix.SharedPointer
    # 
    TOPOLOGICAL_DISTANCE_MATRIX = CDPL.Base.LookupKey('TOPOLOGICAL_DISTANCE_MATRIX')

    ##
    # \brief Specifies the geometrical (Euclidean) all-pair distance matrix.
    # 
    # \valuetype  Math.DMatrix.SharedPointer
    # 
    GEOMETRICAL_DISTANCE_MATRIX = CDPL.Base.LookupKey('GEOMETRICAL_DISTANCE_MATRIX')

    ##
    # \brief Specifies the stoichiometric multiplier of the molecular graph in a reaction (defaults to <em>1</em>).
    # 
    # \valuetype  <tt>double</tt>
    # 
    STOICHIOMETRIC_NUMBER = CDPL.Base.LookupKey('STOICHIOMETRIC_NUMBER')

    ##
    # \brief Specifies the index of the active conformation (within the per-atom 3D coordinates arrays).
    # 
    # \valuetype  <tt>std::size_t</tt>
    # 
    CONFORMATION_INDEX = CDPL.Base.LookupKey('CONFORMATION_INDEX')

    ##
    # \brief Specifies the conformer energy values.
    # 
    # \valuetype  Util.DArray.SharedPointer
    # 
    CONFORMER_ENERGIES = CDPL.Base.LookupKey('CONFORMER_ENERGIES')

    ##
    # \brief Specifies the structure data block associated with the molecular graph (typically read from/written to MDL SD-file data fields).
    # 
    # \valuetype  Chem.StringDataBlock.SharedPointer
    # 
    STRUCTURE_DATA = CDPL.Base.LookupKey('STRUCTURE_DATA')

    ##
    # \brief Specifies the 64-bit topological hash code of the molecular graph.
    # 
    # \valuetype  <tt>std::uint64_t</tt>
    # 
    HASH_CODE = CDPL.Base.LookupKey('HASH_CODE')

    ##
    # \brief Specifies the user initials stored in the MDL CTAB header.
    # 
    # \see [\ref CTFILE] 
    # \valuetype  <tt>std::string</tt>
    # 
    MDL_USER_INITIALS = CDPL.Base.LookupKey('MDL_USER_INITIALS')

    ##
    # \brief Specifies the program name stored in the MDL CTAB header.
    # 
    # \see [\ref CTFILE] 
    # \valuetype  <tt>std::string</tt>
    # 
    MDL_PROGRAM_NAME = CDPL.Base.LookupKey('MDL_PROGRAM_NAME')

    ##
    # \brief Specifies the registry number stored in the MDL CTAB header.
    # 
    # \see [\ref CTFILE] 
    # \valuetype  <tt>std::size_t</tt>
    # 
    MDL_REGISTRY_NUMBER = CDPL.Base.LookupKey('MDL_REGISTRY_NUMBER')

    ##
    # \brief Specifies the MDL connection table version.
    # 
    # \see [\ref CTFILE] 
    # \valuetype  <tt>unsigned int</tt> (Chem.MDLDataFormatVersion value)
    # 
    MDL_CTAB_VERSION = CDPL.Base.LookupKey('MDL_CTAB_VERSION')

    ##
    # \brief Specifies the dimensionality flag stored in the MDL CTAB header (<em>0</em> = unspecified, <em>2</em> = 2D, <em>3</em> = 3D).
    # 
    # \see [\ref CTFILE] 
    # \valuetype  <tt>std::size_t</tt>
    # 
    MDL_DIMENSIONALITY = CDPL.Base.LookupKey('MDL_DIMENSIONALITY')

    ##
    # \brief Specifies the first (integer) scaling factor stored in the MDL CTAB header.
    # 
    # \see [\ref CTFILE] 
    # \valuetype  <tt>long</tt>
    # 
    MDL_SCALING_FACTOR1 = CDPL.Base.LookupKey('MDL_SCALING_FACTOR1')

    ##
    # \brief Specifies the second (floating-point) scaling factor stored in the MDL CTAB header.
    # 
    # \see [\ref CTFILE] 
    # \valuetype  <tt>double</tt>
    # 
    MDL_SCALING_FACTOR2 = CDPL.Base.LookupKey('MDL_SCALING_FACTOR2')

    ##
    # \brief Specifies the energy value stored in the MDL CTAB header.
    # 
    # \see [\ref CTFILE] 
    # \valuetype  <tt>double</tt>
    # 
    MDL_ENERGY = CDPL.Base.LookupKey('MDL_ENERGY')

    ##
    # \brief Specifies the chiral flag stored in the MDL CTAB header.
    # 
    # \see [\ref CTFILE] 
    # \valuetype  <tt>bool</tt>
    # 
    MDL_CHIRAL_FLAG = CDPL.Base.LookupKey('MDL_CHIRAL_FLAG')

    ##
    # \brief Specifies the <em>Sybyl MOL2</em> partial-charge type of the molecular graph.
    # 
    # \valuetype  <tt>unsigned int</tt> (Chem.MOL2ChargeType value)
    # 
    MOL2_CHARGE_TYPE = CDPL.Base.LookupKey('MOL2_CHARGE_TYPE')

    ##
    # \brief Specifies the <em>Sybyl MOL2</em> molecule type of the molecular graph.
    # 
    # \valuetype  <tt>unsigned int</tt> (Chem.MOL2MoleculeType value)
    # 
    MOL2_MOLECULE_TYPE = CDPL.Base.LookupKey('MOL2_MOLECULE_TYPE')
