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
# \brief Provides default values for built-in Chem.Reaction properties.
# 
class ReactionPropertyDefault(Boost.Python.instance):

    ##
    # \brief Default value of the Vis.ReactionProperty.ARROW_STYLE property.
    # 
    ARROW_STYLE = 1

    ##
    # \brief Default value of the Vis.ReactionProperty.ARROW_COLOR property.
    # 
    ARROW_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default value of the Vis.ReactionProperty.ARROW_LENGTH property.
    # 
    ARROW_LENGTH = SizeSpecification(value=35, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.ReactionProperty.ARROW_HEAD_LENGTH property.
    # 
    ARROW_HEAD_LENGTH = SizeSpecification(value=8, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.ReactionProperty.ARROW_HEAD_WIDTH property.
    # 
    ARROW_HEAD_WIDTH = SizeSpecification(value=5, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.ReactionProperty.ARROW_SHAFT_WIDTH property.
    # 
    ARROW_SHAFT_WIDTH = SizeSpecification(value=0, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.ReactionProperty.ARROW_LINE_WIDTH property.
    # 
    ARROW_LINE_WIDTH = SizeSpecification(value=1, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.ReactionProperty.COMPONENT_LAYOUT property.
    # 
    COMPONENT_LAYOUT = 2

    ##
    # \brief Default value of the Vis.ReactionProperty.COMPONENT_LAYOUT_DIRECTION property.
    # 
    COMPONENT_LAYOUT_DIRECTION = 0

    ##
    # \brief Default value of the Vis.ReactionProperty.COMPONENT_MARGIN property.
    # 
    COMPONENT_MARGIN = SizeSpecification(value=5, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.ReactionProperty.SHOW_REACTANTS property.
    # 
    SHOW_REACTANTS = True

    ##
    # \brief Default value of the Vis.ReactionProperty.SHOW_AGENTS property.
    # 
    SHOW_AGENTS = True

    ##
    # \brief Default value of the Vis.ReactionProperty.SHOW_PRODUCTS property.
    # 
    SHOW_PRODUCTS = True

    ##
    # \brief Default value of the Vis.ReactionProperty.AGENT_ALIGNMENT property.
    # 
    AGENT_ALIGNMENT = 12

    ##
    # \brief Default value of the Vis.ReactionProperty.AGENT_LAYOUT property.
    # 
    AGENT_LAYOUT = 1

    ##
    # \brief Default value of the Vis.ReactionProperty.AGENT_LAYOUT_DIRECTION property.
    # 
    AGENT_LAYOUT_DIRECTION = 0

    ##
    # \brief Default value of the Vis.ReactionProperty.PLUS_SIGN_COLOR property.
    # 
    PLUS_SIGN_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default value of the Vis.ReactionProperty.PLUS_SIGN_SIZE property.
    # 
    PLUS_SIGN_SIZE = SizeSpecification(value=10, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.ReactionProperty.PLUS_SIGN_LINE_WIDTH property.
    # 
    PLUS_SIGN_LINE_WIDTH = SizeSpecification(value=3, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.ReactionProperty.SHOW_PLUS_SIGNS property.
    # 
    SHOW_PLUS_SIGNS = True
