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
# \brief Provides keys for built-in Chem.Bond properties.
# 
class BondProperty(Boost.Python.instance):

    ##
    # \brief Specifies the bond order.
    # 
    # <b>Value Type:</b> std::size_t
    # 
    ORDER = CDPL.Base.LookupKey('ORDER')

    ##
    # \brief Specifies the SYBYL bond type (see namespace Chem.SybylBondType).
    # 
    # <b>Value Type:</b> unsigned int
    # 
    SYBYL_TYPE = CDPL.Base.LookupKey('SYBYL_TYPE')

    ##
    # \brief Specifies whether the bond is a member of any ring.
    # 
    # <b>Value Type:</b> bool
    # 
    RING_FLAG = CDPL.Base.LookupKey('RING_FLAG')

    ##
    # \brief Specifies whether the bond is a member of an aromatic ring system.
    # 
    # <b>Value Type:</b> bool
    # 
    AROMATICITY_FLAG = CDPL.Base.LookupKey('AROMATICITY_FLAG')

    ##
    # \brief Specifies the stereochemical descriptor of the bond.
    # 
    # <b>Value Type:</b> Chem.StereoDescriptor
    # 
    STEREO_DESCRIPTOR = CDPL.Base.LookupKey('STEREO_DESCRIPTOR')

    ##
    # \brief Specifies whether the bond is a stereogenic center.
    # 
    # <b>Value Type:</b> bool
    # 
    STEREO_CENTER_FLAG = CDPL.Base.LookupKey('STEREO_CENTER_FLAG')

    ##
    # \brief Specifies the CIP stereochemical configuration label of the bond (see namespace Chem.CIPDescriptor).
    # 
    # <b>Value Type:</b> unsigned int
    # 
    CIP_CONFIGURATION = CDPL.Base.LookupKey('CIP_CONFIGURATION')

    ##
    # \brief Specifies the bond direction in a 2D depiction of the molecular structure (see namespace Chem.BondDirection).
    # 
    # <b>Value Type:</b> unsigned int
    # 
    DIRECTION = CDPL.Base.LookupKey('DIRECTION')

    ##
    # \brief Specifies the 2D stereo flag of the bond (see namespace Chem.BondStereoFlag).
    # 
    # <b>Value Type:</b> unsigned int
    # 
    STEREO_2D_FLAG = CDPL.Base.LookupKey('STEREO_2D_FLAG')

    ##
    # \brief Specifies the reaction center status of the bond (see namespace Chem.ReactionCenterStatus).
    # 
    # <b>Value Type:</b> unsigned int
    # 
    REACTION_CENTER_STATUS = CDPL.Base.LookupKey('REACTION_CENTER_STATUS')

    ##
    # \brief Specifies the substructure matching constraints associated with the bond.
    # 
    # <b>Value Type:</b> Chem.MatchConstraintList.SharedPointer
    # 
    MATCH_CONSTRAINTS = CDPL.Base.LookupKey('MATCH_CONSTRAINTS')

    ##
    # \brief Specifies the substructure matching expression associated with the bond.
    # 
    # <b>Value Type:</b> Chem.MatchExpression<Chem.Bond, Chem.MolecularGraph>.SharedPointer
    # 
    MATCH_EXPRESSION = CDPL.Base.LookupKey('MATCH_EXPRESSION')

    ##
    # \brief Specifies a string representation of the substructure matching expression associated with the bond.
    # 
    # <b>Value Type:</b> std::string
    # 
    MATCH_EXPRESSION_STRING = CDPL.Base.LookupKey('MATCH_EXPRESSION_STRING')
