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
class ControlParameter(Boost.Python.instance):

    ##
    # \brief 
    #
    ALIGNMENT = CDPL.Base.LookupKey(id=211, name='ALIGNMENT')

    ##
    # \brief 
    #
    ATOM_COLOR = CDPL.Base.LookupKey(id=234, name='ATOM_COLOR')

    ##
    # \brief 
    #
    ATOM_COLOR_TABLE = CDPL.Base.LookupKey(id=235, name='ATOM_COLOR_TABLE')

    ##
    # \brief 
    #
    RADICAL_ELECTRON_DOT_SIZE = CDPL.Base.LookupKey(id=242, name='RADICAL_ELECTRON_DOT_SIZE')

    ##
    # \brief 
    #
    ATOM_LABEL_FONT = CDPL.Base.LookupKey(id=237, name='ATOM_LABEL_FONT')

    ##
    # \brief 
    #
    ATOM_LABEL_MARGIN = CDPL.Base.LookupKey(id=241, name='ATOM_LABEL_MARGIN')

    ##
    # \brief 
    #
    ATOM_LABEL_SIZE = CDPL.Base.LookupKey(id=238, name='ATOM_LABEL_SIZE')

    ##
    # \brief 
    #
    SECONDARY_ATOM_LABEL_FONT = CDPL.Base.LookupKey(id=239, name='SECONDARY_ATOM_LABEL_FONT')

    ##
    # \brief 
    #
    SECONDARY_ATOM_LABEL_SIZE = CDPL.Base.LookupKey(id=240, name='SECONDARY_ATOM_LABEL_SIZE')

    ##
    # \brief 
    #
    BACKGROUND_COLOR = CDPL.Base.LookupKey(id=213, name='BACKGROUND_COLOR')

    ##
    # \brief 
    #
    BOND_COLOR = CDPL.Base.LookupKey(id=253, name='BOND_COLOR')

    ##
    # \brief 
    #
    BOND_LABEL_FONT = CDPL.Base.LookupKey(id=262, name='BOND_LABEL_FONT')

    ##
    # \brief 
    #
    BOND_LABEL_MARGIN = CDPL.Base.LookupKey(id=264, name='BOND_LABEL_MARGIN')

    ##
    # \brief 
    #
    BOND_LABEL_SIZE = CDPL.Base.LookupKey(id=263, name='BOND_LABEL_SIZE')

    ##
    # \brief 
    #
    BOND_LENGTH = CDPL.Base.LookupKey(id=252, name='BOND_LENGTH')

    ##
    # \brief 
    #
    BOND_LINE_SPACING = CDPL.Base.LookupKey(id=255, name='BOND_LINE_SPACING')

    ##
    # \brief 
    #
    BOND_LINE_WIDTH = CDPL.Base.LookupKey(id=254, name='BOND_LINE_WIDTH')

    ##
    # \brief 
    #
    REACTION_CENTER_LINE_LENGTH = CDPL.Base.LookupKey(id=258, name='REACTION_CENTER_LINE_LENGTH')

    ##
    # \brief 
    #
    REACTION_CENTER_LINE_SPACING = CDPL.Base.LookupKey(id=259, name='REACTION_CENTER_LINE_SPACING')

    ##
    # \brief 
    #
    STEREO_BOND_HASH_SPACING = CDPL.Base.LookupKey(id=257, name='STEREO_BOND_HASH_SPACING')

    ##
    # \brief 
    #
    STEREO_BOND_WEDGE_WIDTH = CDPL.Base.LookupKey(id=256, name='STEREO_BOND_WEDGE_WIDTH')

    ##
    # \brief 
    #
    DOUBLE_BOND_TRIM_LENGTH = CDPL.Base.LookupKey(id=260, name='DOUBLE_BOND_TRIM_LENGTH')

    ##
    # \brief 
    #
    REACTION_AGENT_ALIGNMENT = CDPL.Base.LookupKey(id=224, name='REACTION_AGENT_ALIGNMENT')

    ##
    # \brief 
    #
    REACTION_AGENT_LAYOUT = CDPL.Base.LookupKey(id=225, name='REACTION_AGENT_LAYOUT')

    ##
    # \brief 
    #
    REACTION_AGENT_LAYOUT_DIRECTION = CDPL.Base.LookupKey(id=226, name='REACTION_AGENT_LAYOUT_DIRECTION')

    ##
    # \brief 
    #
    REACTION_ARROW_COLOR = CDPL.Base.LookupKey(id=215, name='REACTION_ARROW_COLOR')

    ##
    # \brief 
    #
    REACTION_ARROW_HEAD_LENGTH = CDPL.Base.LookupKey(id=217, name='REACTION_ARROW_HEAD_LENGTH')

    ##
    # \brief 
    #
    REACTION_ARROW_HEAD_WIDTH = CDPL.Base.LookupKey(id=218, name='REACTION_ARROW_HEAD_WIDTH')

    ##
    # \brief 
    #
    REACTION_ARROW_LENGTH = CDPL.Base.LookupKey(id=216, name='REACTION_ARROW_LENGTH')

    ##
    # \brief 
    #
    REACTION_ARROW_LINE_WIDTH = CDPL.Base.LookupKey(id=220, name='REACTION_ARROW_LINE_WIDTH')

    ##
    # \brief 
    #
    REACTION_ARROW_SHAFT_WIDTH = CDPL.Base.LookupKey(id=219, name='REACTION_ARROW_SHAFT_WIDTH')

    ##
    # \brief 
    #
    REACTION_ARROW_STYLE = CDPL.Base.LookupKey(id=214, name='REACTION_ARROW_STYLE')

    ##
    # \brief 
    #
    REACTION_COMPONENT_LAYOUT = CDPL.Base.LookupKey(id=221, name='REACTION_COMPONENT_LAYOUT')

    ##
    # \brief 
    #
    REACTION_COMPONENT_LAYOUT_DIRECTION = CDPL.Base.LookupKey(id=222, name='REACTION_COMPONENT_LAYOUT_DIRECTION')

    ##
    # \brief 
    #
    REACTION_COMPONENT_MARGIN = CDPL.Base.LookupKey(id=223, name='REACTION_COMPONENT_MARGIN')

    ##
    # \brief 
    #
    REACTION_PLUS_SIGN_COLOR = CDPL.Base.LookupKey(id=227, name='REACTION_PLUS_SIGN_COLOR')

    ##
    # \brief 
    #
    REACTION_PLUS_SIGN_LINE_WIDTH = CDPL.Base.LookupKey(id=229, name='REACTION_PLUS_SIGN_LINE_WIDTH')

    ##
    # \brief 
    #
    REACTION_PLUS_SIGN_SIZE = CDPL.Base.LookupKey(id=228, name='REACTION_PLUS_SIGN_SIZE')

    ##
    # \brief 
    #
    SHOW_REACTION_REACTANTS = CDPL.Base.LookupKey(id=230, name='SHOW_REACTION_REACTANTS')

    ##
    # \brief 
    #
    SHOW_REACTION_AGENTS = CDPL.Base.LookupKey(id=231, name='SHOW_REACTION_AGENTS')

    ##
    # \brief 
    #
    SHOW_REACTION_PRODUCTS = CDPL.Base.LookupKey(id=232, name='SHOW_REACTION_PRODUCTS')

    ##
    # \brief 
    #
    SHOW_CHARGES = CDPL.Base.LookupKey(id=245, name='SHOW_CHARGES')

    ##
    # \brief 
    #
    SHOW_HYDROGEN_COUNTS = CDPL.Base.LookupKey(id=247, name='SHOW_HYDROGEN_COUNTS')

    ##
    # \brief 
    #
    SHOW_ISOTOPES = CDPL.Base.LookupKey(id=246, name='SHOW_ISOTOPES')

    ##
    # \brief 
    #
    SHOW_NON_CARBON_HYDROGEN_COUNTS = CDPL.Base.LookupKey(id=248, name='SHOW_NON_CARBON_HYDROGEN_COUNTS')

    ##
    # \brief 
    #
    SHOW_ATOM_QUERY_INFOS = CDPL.Base.LookupKey(id=249, name='SHOW_ATOM_QUERY_INFOS')

    ##
    # \brief 
    #
    SHOW_RADICAL_ELECTRONS = CDPL.Base.LookupKey(id=251, name='SHOW_RADICAL_ELECTRONS')

    ##
    # \brief 
    #
    SHOW_ATOM_REACTION_INFOS = CDPL.Base.LookupKey(id=250, name='SHOW_ATOM_REACTION_INFOS')

    ##
    # \brief 
    #
    SHOW_BOND_QUERY_INFOS = CDPL.Base.LookupKey(id=266, name='SHOW_BOND_QUERY_INFOS')

    ##
    # \brief 
    #
    SHOW_BOND_REACTION_INFOS = CDPL.Base.LookupKey(id=265, name='SHOW_BOND_REACTION_INFOS')

    ##
    # \brief 
    #
    SHOW_STEREO_BONDS = CDPL.Base.LookupKey(id=267, name='SHOW_STEREO_BONDS')

    ##
    # \brief 
    #
    SHOW_CARBONS = CDPL.Base.LookupKey(id=244, name='SHOW_CARBONS')

    ##
    # \brief 
    #
    SHOW_EXPLICIT_HYDROGENS = CDPL.Base.LookupKey(id=243, name='SHOW_EXPLICIT_HYDROGENS')

    ##
    # \brief 
    #
    SIZE_ADJUSTMENT = CDPL.Base.LookupKey(id=210, name='SIZE_ADJUSTMENT')

    ##
    # \brief 
    #
    TRIPLE_BOND_TRIM_LENGTH = CDPL.Base.LookupKey(id=261, name='TRIPLE_BOND_TRIM_LENGTH')

    ##
    # \brief 
    #
    USE_CALCULATED_ATOM_COORDINATES = CDPL.Base.LookupKey(id=236, name='USE_CALCULATED_ATOM_COORDINATES')

    ##
    # \brief 
    #
    VIEWPORT = CDPL.Base.LookupKey(id=209, name='VIEWPORT')
