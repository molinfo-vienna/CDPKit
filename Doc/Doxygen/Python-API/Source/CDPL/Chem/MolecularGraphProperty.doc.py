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
    # \brief Specifies a textual name (or title) of the molecular graph.
    # 
    # <b>Value Type:</b> <tt>std::string</tt>
    # 
    NAME = CDPL.Base.LookupKey('NAME')

    ##
    # \brief Specifies a free-text comment associated with the molecular graph.
    # 
    # <b>Value Type:</b> <tt>std::string</tt>
    # 
    COMMENT = CDPL.Base.LookupKey('COMMENT')

    ##
    # \brief Specifies the timestamp at which the molecular graph was created/last modified.
    # 
    # <b>Value Type:</b> <tt>std::time_t</tt>
    # 
    TIMESTAMP = CDPL.Base.LookupKey('TIMESTAMP')

    ##
    # \brief Specifies the connected components of the molecular graph.
    # 
    # <b>Value Type:</b> Chem.FragmentList.SharedPointer
    # 
    COMPONENTS = CDPL.Base.LookupKey('COMPONENTS')

    ##
    # \brief Specifies the perceived rings of the molecular graph.
    # 
    # <b>Value Type:</b> Chem.FragmentList.SharedPointer
    # 
    RINGS = CDPL.Base.LookupKey('RINGS')

    ##
    # \brief Specifies the smallest set of smallest rings (SSSR) of the molecular graph.
    # 
    # <b>Value Type:</b> Chem.FragmentList.SharedPointer
    # 
    SSSR = CDPL.Base.LookupKey('SSSR')

    ##
    # \brief Specifies the union of all rings (the cyclic substructure) of the molecular graph.
    # 
    # <b>Value Type:</b> Chem.Fragment.SharedPointer
    # 
    CYCLIC_SUBSTRUCTURE = CDPL.Base.LookupKey('CYCLIC_SUBSTRUCTURE')

    ##
    # \brief Specifies the perceived aromatic substructure of the molecular graph.
    # 
    # <b>Value Type:</b> Chem.Fragment.SharedPointer
    # 
    AROMATIC_SUBSTRUCTURE = CDPL.Base.LookupKey('AROMATIC_SUBSTRUCTURE')

    ##
    # \brief Specifies the perceived &pi;-electron systems of the molecular graph.
    # 
    # <b>Value Type:</b> Chem.ElectronSystemList.SharedPointer
    # 
    PI_ELECTRON_SYSTEMS = CDPL.Base.LookupKey('PI_ELECTRON_SYSTEMS')

    ##
    # \brief Specifies the substructure-search match constraints attached to the molecular graph.
    # 
    # <b>Value Type:</b> Chem.MatchConstraintList.SharedPointer
    # 
    MATCH_CONSTRAINTS = CDPL.Base.LookupKey('MATCH_CONSTRAINTS')

    ##
    # \brief Specifies a cached substructure-search match expression compiled from MATCH_CONSTRAINTS.
    # 
    # <b>Value Type:</b> <tt>Chem.MatchExpression<Chem.MolecularGraph>.SharedPointer</tt>
    # 
    MATCH_EXPRESSION = CDPL.Base.LookupKey('MATCH_EXPRESSION')

    ##
    # \brief Specifies grouped sets of connected components used for substructure matching (e.g. enantiomeric pairs).
    # 
    # <b>Value Type:</b> Chem.FragmentList.SharedPointer
    # 
    COMPONENT_GROUPS = CDPL.Base.LookupKey('COMPONENT_GROUPS')

    ##
    # \brief Specifies the topological (bond-count) all-pair distance matrix.
    # 
    # <b>Value Type:</b> Math.ULMatrix.SharedPointer
    # 
    TOPOLOGICAL_DISTANCE_MATRIX = CDPL.Base.LookupKey('TOPOLOGICAL_DISTANCE_MATRIX')

    ##
    # \brief Specifies the geometrical (Euclidean) all-pair distance matrix.
    # 
    # <b>Value Type:</b> Math.DMatrix.SharedPointer
    # 
    GEOMETRICAL_DISTANCE_MATRIX = CDPL.Base.LookupKey('GEOMETRICAL_DISTANCE_MATRIX')

    ##
    # \brief Specifies the stoichiometric multiplier of the molecular graph in a reaction (defaults to <em>1</em>).
    # 
    # <b>Value Type:</b> <tt>double</tt>
    # 
    STOICHIOMETRIC_NUMBER = CDPL.Base.LookupKey('STOICHIOMETRIC_NUMBER')

    ##
    # \brief Specifies the index of the active conformation (within the per-atom 3D-coordinates arrays).
    # 
    # <b>Value Type:</b> <tt>std::size_t</tt>
    # 
    CONFORMATION_INDEX = CDPL.Base.LookupKey('CONFORMATION_INDEX')

    ##
    # \brief Specifies the per-conformation energy values.
    # 
    # <b>Value Type:</b> Util.DArray.SharedPointer
    # 
    CONFORMER_ENERGIES = CDPL.Base.LookupKey('CONFORMER_ENERGIES')

    ##
    # \brief Specifies structured data tags attached to the molecular graph (e.g. MDL SD-file data fields).
    # 
    # <b>Value Type:</b> Chem.StringDataBlock.SharedPointer
    # 
    STRUCTURE_DATA = CDPL.Base.LookupKey('STRUCTURE_DATA')

    ##
    # \brief Specifies a 64-bit topological hash code identifying the molecular graph.
    # 
    # <b>Value Type:</b> <tt>std::uint64_t</tt>
    # 
    HASH_CODE = CDPL.Base.LookupKey('HASH_CODE')

    ##
    # \brief Specifies the user initials stored in the MDL CTAB header.
    # 
    # <b>Value Type:</b> <tt>std::string</tt>
    # 
    MDL_USER_INITIALS = CDPL.Base.LookupKey('MDL_USER_INITIALS')

    ##
    # \brief Specifies the program name stored in the MDL CTAB header.
    # 
    # <b>Value Type:</b> <tt>std::string</tt>
    # 
    MDL_PROGRAM_NAME = CDPL.Base.LookupKey('MDL_PROGRAM_NAME')

    ##
    # \brief Specifies the registry number stored in the MDL CTAB header.
    # 
    # <b>Value Type:</b> <tt>std::size_t</tt>
    # 
    MDL_REGISTRY_NUMBER = CDPL.Base.LookupKey('MDL_REGISTRY_NUMBER')

    ##
    # \brief Specifies the CTAB version of the MDL connection table.
    # 
    # <b>Value Type:</b> <tt>unsigned</tt> <tt>int</tt> (Chem.MDLDataFormatVersion value)
    # 
    MDL_CTAB_VERSION = CDPL.Base.LookupKey('MDL_CTAB_VERSION')

    ##
    # \brief Specifies the dimensionality flag stored in the MDL CTAB header (<em>0</em> = unspecified, <em>2</em> = 2D, <em>3</em> = 3D).
    # 
    # <b>Value Type:</b> <tt>std::size_t</tt>
    # 
    MDL_DIMENSIONALITY = CDPL.Base.LookupKey('MDL_DIMENSIONALITY')

    ##
    # \brief Specifies the first (integer) scaling factor stored in the MDL CTAB header.
    # 
    # <b>Value Type:</b> <tt>long</tt>
    # 
    MDL_SCALING_FACTOR1 = CDPL.Base.LookupKey('MDL_SCALING_FACTOR1')

    ##
    # \brief Specifies the second (floating-point) scaling factor stored in the MDL CTAB header.
    # 
    # <b>Value Type:</b> <tt>double</tt>
    # 
    MDL_SCALING_FACTOR2 = CDPL.Base.LookupKey('MDL_SCALING_FACTOR2')

    ##
    # \brief Specifies the energy value stored in the MDL CTAB header.
    # 
    # <b>Value Type:</b> <tt>double</tt>
    # 
    MDL_ENERGY = CDPL.Base.LookupKey('MDL_ENERGY')

    ##
    # \brief Specifies the chiral flag stored in the MDL CTAB header.
    # 
    # <b>Value Type:</b> <tt>bool</tt>
    # 
    MDL_CHIRAL_FLAG = CDPL.Base.LookupKey('MDL_CHIRAL_FLAG')

    ##
    # \brief Specifies the partial-charge type of the molecular graph in the Tripos MOL2 format.
    # 
    # <b>Value Type:</b> <tt>unsigned</tt> <tt>int</tt> (Chem.MOL2ChargeType value)
    # 
    MOL2_CHARGE_TYPE = CDPL.Base.LookupKey('MOL2_CHARGE_TYPE')

    ##
    # \brief Specifies the molecule type of the molecular graph in the Tripos MOL2 format.
    # 
    # <b>Value Type:</b> <tt>unsigned</tt> <tt>int</tt> (Chem.MOL2MoleculeType value)
    # 
    MOL2_MOLECULE_TYPE = CDPL.Base.LookupKey('MOL2_MOLECULE_TYPE')
