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
    # <b>Value Type:</b> std::string
    # 
    NAME = CDPL.Base.LookupKey('NAME')

    ##
    # \brief Specifies the element symbol of the atom.
    # 
    # <b>Value Type:</b> std::string
    # 
    SYMBOL = CDPL.Base.LookupKey('SYMBOL')

    ##
    # \brief Specifies the atom type (see namespace Chem.AtomType).
    # 
    # <b>Value Type:</b> unsigned int
    # 
    TYPE = CDPL.Base.LookupKey('TYPE')

    ##
    # \brief Specifies the formal charge of the atom.
    # 
    # <b>Value Type:</b> long
    # 
    FORMAL_CHARGE = CDPL.Base.LookupKey('FORMAL_CHARGE')

    ##
    # \brief Specifies the isotopic mass number of the atom.
    # 
    # <b>Value Type:</b> std::size_t
    # 
    ISOTOPE = CDPL.Base.LookupKey('ISOTOPE')

    ##
    # \brief Specifies the radical type of the atom (see namespace Chem.RadicalType).
    # 
    # <b>Value Type:</b> unsigned int
    # 
    RADICAL_TYPE = CDPL.Base.LookupKey('RADICAL_TYPE')

    ##
    # \brief Specifies the hybridization state of the atom (see namespace Chem.HybridizationState).
    # 
    # <b>Value Type:</b> unsigned int
    # 
    HYBRIDIZATION = CDPL.Base.LookupKey('HYBRIDIZATION')

    ##
    # \brief Specifies whether the atom is a member of any ring.
    # 
    # <b>Value Type:</b> bool
    # 
    RING_FLAG = CDPL.Base.LookupKey('RING_FLAG')

    ##
    # \brief Specifies whether the atom is a member of an aromatic ring system.
    # 
    # <b>Value Type:</b> bool
    # 
    AROMATICITY_FLAG = CDPL.Base.LookupKey('AROMATICITY_FLAG')

    ##
    # \brief Specifies the number of unpaired electrons of the atom.
    # 
    # <b>Value Type:</b> std::size_t
    # 
    UNPAIRED_ELECTRON_COUNT = CDPL.Base.LookupKey('UNPAIRED_ELECTRON_COUNT')

    ##
    # \brief Specifies the number of implicit hydrogens attached to the atom.
    # 
    # <b>Value Type:</b> std::size_t
    # 
    IMPLICIT_HYDROGEN_COUNT = CDPL.Base.LookupKey('IMPLICIT_HYDROGEN_COUNT')

    ##
    # \brief Specifies the 2D coordinates of the atom.
    # 
    # <b>Value Type:</b> Math.Vector2D
    # 
    COORDINATES_2D = CDPL.Base.LookupKey('COORDINATES_2D')

    ##
    # \brief Specifies an array with the 3D coordinates of the atom for one or more molecular conformations.
    # 
    # <b>Value Type:</b> Math.Vector3DArray.SharedPointer
    # 
    COORDINATES_3D_ARRAY = CDPL.Base.LookupKey('COORDINATES_3D_ARRAY')

    ##
    # \brief Specifies the Morgan extended connectivity value of the atom.
    # 
    # <b>Value Type:</b> std::size_t
    # 
    MORGAN_NUMBER = CDPL.Base.LookupKey('MORGAN_NUMBER')

    ##
    # \brief Specifies the canonical numbering of the atom.
    # 
    # <b>Value Type:</b> std::size_t
    # 
    CANONICAL_NUMBER = CDPL.Base.LookupKey('CANONICAL_NUMBER')

    ##
    # \brief Specifies the CIP priority of the atom.
    # 
    # <b>Value Type:</b> std::size_t
    # 
    CIP_PRIORITY = CDPL.Base.LookupKey('CIP_PRIORITY')

    ##
    # \brief Specifies the topological symmetry class of the atom.
    # 
    # <b>Value Type:</b> std::size_t
    # 
    SYMMETRY_CLASS = CDPL.Base.LookupKey('SYMMETRY_CLASS')

    ##
    # \brief Specifies the stereochemical descriptor of the atom.
    # 
    # <b>Value Type:</b> Chem.StereoDescriptor
    # 
    STEREO_DESCRIPTOR = CDPL.Base.LookupKey('STEREO_DESCRIPTOR')

    ##
    # \brief Specifies whether the atom is a stereogenic center.
    # 
    # <b>Value Type:</b> bool
    # 
    STEREO_CENTER_FLAG = CDPL.Base.LookupKey('STEREO_CENTER_FLAG')

    ##
    # \brief Specifies the CIP stereochemical configuration label of the atom (see namespace Chem.CIPDescriptor).
    # 
    # <b>Value Type:</b> unsigned int
    # 
    CIP_CONFIGURATION = CDPL.Base.LookupKey('CIP_CONFIGURATION')

    ##
    # \brief Specifies the MDL stereo parity of the atom (see namespace Chem.MDLParity).
    # 
    # <b>Value Type:</b> unsigned int
    # 
    MDL_PARITY = CDPL.Base.LookupKey('MDL_PARITY')

    ##
    # \brief Specifies the value of the MDL <em>stereo care</em> flag of the atom.
    # 
    # <b>Value Type:</b> bool
    # 
    MDL_DB_STEREO_CARE_FLAG = CDPL.Base.LookupKey('MDL_DB_STEREO_CARE_FLAG')

    ##
    # \brief Specifies the SYBYL atom type (see namespace Chem.SybylAtomType).
    # 
    # <b>Value Type:</b> unsigned int
    # 
    SYBYL_TYPE = CDPL.Base.LookupKey('SYBYL_TYPE')

    ##
    # \brief Specifies the atom name as read from or written to a <em>Sybyl MOL2</em> file.
    # 
    # <b>Value Type:</b> std::string
    # 
    MOL2_NAME = CDPL.Base.LookupKey('MOL2_NAME')

    ##
    # \brief Specifies the atomic partial charge as read from or written to a <em>Sybyl MOL2</em> file.
    # 
    # <b>Value Type:</b> double
    # 
    MOL2_CHARGE = CDPL.Base.LookupKey('MOL2_CHARGE')

    ##
    # \brief Specifies the ID of the substructure the atom belongs to (as read from or written to a <em>Sybyl MOL2</em> file).
    # 
    # <b>Value Type:</b> std::size_t
    # 
    MOL2_SUBSTRUCTURE_ID = CDPL.Base.LookupKey('MOL2_SUBSTRUCTURE_ID')

    ##
    # \brief Specifies the name of the substructure the atom belongs to (as read from or written to a <em>Sybyl MOL2</em> file).
    # 
    # <b>Value Type:</b> std::string
    # 
    MOL2_SUBSTRUCTURE_NAME = CDPL.Base.LookupKey('MOL2_SUBSTRUCTURE_NAME')

    ##
    # \brief Specifies the subtype of the substructure the atom belongs to (as read from or written to a <em>Sybyl MOL2</em> file).
    # 
    # <b>Value Type:</b> std::string
    # 
    MOL2_SUBSTRUCTURE_SUBTYPE = CDPL.Base.LookupKey('MOL2_SUBSTRUCTURE_SUBTYPE')

    ##
    # \brief Specifies the chain identifier of the substructure the atom belongs to (as read from or written to a <em>Sybyl MOL2</em> file).
    # 
    # <b>Value Type:</b> std::string
    # 
    MOL2_SUBSTRUCTURE_CHAIN = CDPL.Base.LookupKey('MOL2_SUBSTRUCTURE_CHAIN')

    ##
    # \brief Specifies the reaction center status of the atom (see namespace Chem.ReactionCenterStatus).
    # 
    # <b>Value Type:</b> unsigned int
    # 
    REACTION_CENTER_STATUS = CDPL.Base.LookupKey('REACTION_CENTER_STATUS')

    ##
    # \brief Specifies the atom-atom mapping ID used to relate reactant atoms to product atoms in a reaction.
    # 
    # <b>Value Type:</b> std::size_t
    # 
    ATOM_MAPPING_ID = CDPL.Base.LookupKey('ATOM_MAPPING_ID')

    ##
    # \brief Specifies the substructure matching constraints associated with the atom.
    # 
    # <b>Value Type:</b> Chem.MatchConstraintList.SharedPointer
    # 
    MATCH_CONSTRAINTS = CDPL.Base.LookupKey('MATCH_CONSTRAINTS')

    ##
    # \brief Specifies the substructure matching expression associated with the atom.
    # 
    # <b>Value Type:</b> Chem.MatchExpression<Chem.Atom, Chem.MolecularGraph>.SharedPointer
    # 
    MATCH_EXPRESSION = CDPL.Base.LookupKey('MATCH_EXPRESSION')

    ##
    # \brief Specifies a string representation of the substructure matching expression associated with the atom.
    # 
    # <b>Value Type:</b> std::string
    # 
    MATCH_EXPRESSION_STRING = CDPL.Base.LookupKey('MATCH_EXPRESSION_STRING')

    ##
    # \brief Specifies the ID of the component group the atom belongs to.
    # 
    # <b>Value Type:</b> std::size_t
    # 
    COMPONENT_GROUP_ID = CDPL.Base.LookupKey('COMPONENT_GROUP_ID')
