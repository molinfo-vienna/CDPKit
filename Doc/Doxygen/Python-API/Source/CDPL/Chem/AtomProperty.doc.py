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
# \brief Provides keys for built-in Chem.Atom properties.
# 
class AtomProperty(Boost.Python.instance):

    ##
    # \brief Specifies the name of the atom.
    # 
    # \valuetype  <tt>std::string</tt>
    # 
    NAME = CDPL.Base.LookupKey('NAME')

    ##
    # \brief Specifies the element symbol of the atom.
    # 
    # \valuetype  <tt>std::string</tt>
    # 
    SYMBOL = CDPL.Base.LookupKey('SYMBOL')

    ##
    # \brief Specifies the atom type (see namespace Chem.AtomType).
    # 
    # \valuetype  <tt>unsigned int</tt>
    # 
    TYPE = CDPL.Base.LookupKey('TYPE')

    ##
    # \brief Specifies the formal charge of the atom.
    # 
    # \valuetype  <tt>long</tt>
    # 
    FORMAL_CHARGE = CDPL.Base.LookupKey('FORMAL_CHARGE')

    ##
    # \brief Specifies the isotopic mass number of the atom.
    # 
    # \valuetype  <tt>std::size_t</tt>
    # 
    ISOTOPE = CDPL.Base.LookupKey('ISOTOPE')

    ##
    # \brief Specifies the radical type of the atom (see namespace Chem.RadicalType).
    # 
    # \valuetype  <tt>unsigned int</tt>
    # 
    RADICAL_TYPE = CDPL.Base.LookupKey('RADICAL_TYPE')

    ##
    # \brief Specifies the hybridization state of the atom (see namespace Chem.HybridizationState).
    # 
    # \valuetype  <tt>unsigned int</tt>
    # 
    HYBRIDIZATION = CDPL.Base.LookupKey('HYBRIDIZATION')

    ##
    # \brief Specifies whether the atom is a member of any ring.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    RING_FLAG = CDPL.Base.LookupKey('RING_FLAG')

    ##
    # \brief Specifies whether the atom is a member of an aromatic ring system.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    AROMATICITY_FLAG = CDPL.Base.LookupKey('AROMATICITY_FLAG')

    ##
    # \brief Specifies the number of unpaired electrons of the atom.
    # 
    # \valuetype  <tt>std::size_t</tt>
    # 
    UNPAIRED_ELECTRON_COUNT = CDPL.Base.LookupKey('UNPAIRED_ELECTRON_COUNT')

    ##
    # \brief Specifies the number of implicit hydrogens attached to the atom.
    # 
    # \valuetype  <tt>std::size_t</tt>
    # 
    IMPLICIT_HYDROGEN_COUNT = CDPL.Base.LookupKey('IMPLICIT_HYDROGEN_COUNT')

    ##
    # \brief Specifies the 2D coordinates of the atom.
    # 
    # \valuetype  Math.Vector2D
    # 
    COORDINATES_2D = CDPL.Base.LookupKey('COORDINATES_2D')

    ##
    # \brief Specifies an array with the 3D coordinates of the atom for one or more molecular conformations.
    # 
    # \valuetype  Math.Vector3DArray.SharedPointer
    # 
    COORDINATES_3D_ARRAY = CDPL.Base.LookupKey('COORDINATES_3D_ARRAY')

    ##
    # \brief Specifies the Morgan extended connectivity value of the atom.
    # 
    # \valuetype  <tt>std::size_t</tt>
    # 
    MORGAN_NUMBER = CDPL.Base.LookupKey('MORGAN_NUMBER')

    ##
    # \brief Specifies the canonical numbering of the atom.
    # 
    # \valuetype  <tt>std::size_t</tt>
    # 
    CANONICAL_NUMBER = CDPL.Base.LookupKey('CANONICAL_NUMBER')

    ##
    # \brief Specifies the CIP priority of the atom.
    # 
    # \valuetype  <tt>std::size_t</tt>
    # 
    CIP_PRIORITY = CDPL.Base.LookupKey('CIP_PRIORITY')

    ##
    # \brief Specifies the topological symmetry class of the atom.
    # 
    # \valuetype  <tt>std::size_t</tt>
    # 
    SYMMETRY_CLASS = CDPL.Base.LookupKey('SYMMETRY_CLASS')

    ##
    # \brief Specifies the stereochemical descriptor of the atom.
    # 
    # \valuetype  Chem.StereoDescriptor
    # 
    STEREO_DESCRIPTOR = CDPL.Base.LookupKey('STEREO_DESCRIPTOR')

    ##
    # \brief Specifies whether the atom is a stereogenic center.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    STEREO_CENTER_FLAG = CDPL.Base.LookupKey('STEREO_CENTER_FLAG')

    ##
    # \brief Specifies the CIP stereochemical configuration label of the atom (see namespace Chem.CIPDescriptor).
    # 
    # \valuetype  <tt>unsigned int</tt>
    # 
    CIP_CONFIGURATION = CDPL.Base.LookupKey('CIP_CONFIGURATION')

    ##
    # \brief Specifies the MDL stereo parity of the atom (see namespace Chem.MDLParity).
    # 
    # \valuetype  <tt>unsigned int</tt>
    # 
    MDL_PARITY = CDPL.Base.LookupKey('MDL_PARITY')

    ##
    # \brief Specifies the value of the MDL <em>stereo care</em> flag of the atom.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    MDL_DB_STEREO_CARE_FLAG = CDPL.Base.LookupKey('MDL_DB_STEREO_CARE_FLAG')

    ##
    # \brief Specifies the SYBYL atom type (see namespace Chem.SybylAtomType).
    # 
    # \valuetype  <tt>unsigned int</tt>
    # 
    SYBYL_TYPE = CDPL.Base.LookupKey('SYBYL_TYPE')

    ##
    # \brief Specifies the atom name as read from or written to a <em>Sybyl MOL2</em> file.
    # 
    # \valuetype  <tt>std::string</tt>
    # 
    MOL2_NAME = CDPL.Base.LookupKey('MOL2_NAME')

    ##
    # \brief Specifies the atomic partial charge as read from or written to a <em>Sybyl MOL2</em> file.
    # 
    # \valuetype  <tt>double</tt>
    # 
    MOL2_CHARGE = CDPL.Base.LookupKey('MOL2_CHARGE')

    ##
    # \brief Specifies the ID of the substructure the atom belongs to (as read from or written to a <em>Sybyl MOL2</em> file).
    # 
    # \valuetype  <tt>std::size_t</tt>
    # 
    MOL2_SUBSTRUCTURE_ID = CDPL.Base.LookupKey('MOL2_SUBSTRUCTURE_ID')

    ##
    # \brief Specifies the name of the substructure the atom belongs to (as read from or written to a <em>Sybyl MOL2</em> file).
    # 
    # \valuetype  <tt>std::string</tt>
    # 
    MOL2_SUBSTRUCTURE_NAME = CDPL.Base.LookupKey('MOL2_SUBSTRUCTURE_NAME')

    ##
    # \brief Specifies the subtype of the substructure the atom belongs to (as read from or written to a <em>Sybyl MOL2</em> file).
    # 
    # \valuetype  <tt>std::string</tt>
    # 
    MOL2_SUBSTRUCTURE_SUBTYPE = CDPL.Base.LookupKey('MOL2_SUBSTRUCTURE_SUBTYPE')

    ##
    # \brief Specifies the chain identifier of the substructure the atom belongs to (as read from or written to a <em>Sybyl MOL2</em> file).
    # 
    # \valuetype  <tt>std::string</tt>
    # 
    MOL2_SUBSTRUCTURE_CHAIN = CDPL.Base.LookupKey('MOL2_SUBSTRUCTURE_CHAIN')

    ##
    # \brief Specifies the reaction center status of the atom (see namespace Chem.ReactionCenterStatus).
    # 
    # \valuetype  <tt>unsigned int</tt>
    # 
    REACTION_CENTER_STATUS = CDPL.Base.LookupKey('REACTION_CENTER_STATUS')

    ##
    # \brief Specifies the atom-atom mapping ID used to relate reactant atoms to product atoms in a reaction.
    # 
    # \valuetype  <tt>std::size_t</tt>
    # 
    ATOM_MAPPING_ID = CDPL.Base.LookupKey('ATOM_MAPPING_ID')

    ##
    # \brief Specifies the substructure matching constraints associated with the atom.
    # 
    # \valuetype  Chem.MatchConstraintList.SharedPointer
    # 
    MATCH_CONSTRAINTS = CDPL.Base.LookupKey('MATCH_CONSTRAINTS')

    ##
    # \brief Specifies the substructure matching expression associated with the atom.
    # 
    # \valuetype  Chem.MatchExpression<Chem.Atom, Chem.MolecularGraph>.SharedPointer
    # 
    MATCH_EXPRESSION = CDPL.Base.LookupKey('MATCH_EXPRESSION')

    ##
    # \brief Specifies a string representation of the substructure matching expression associated with the atom.
    # 
    # \valuetype  <tt>std::string</tt>
    # 
    MATCH_EXPRESSION_STRING = CDPL.Base.LookupKey('MATCH_EXPRESSION_STRING')

    ##
    # \brief Specifies the ID of the component group the atom belongs to.
    # 
    # \valuetype  <tt>std::size_t</tt>
    # 
    COMPONENT_GROUP_ID = CDPL.Base.LookupKey('COMPONENT_GROUP_ID')
