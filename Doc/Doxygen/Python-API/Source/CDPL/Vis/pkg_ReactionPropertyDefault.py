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
class ReactionPropertyDefault(Boost.Python.instance):

    ##
    # \brief 
    #
    ARROW_STYLE = 1

    ##
    # \brief 
    #
    ARROW_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief 
    #
    ARROW_LENGTH = SizeSpecification(value=35, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    ARROW_HEAD_LENGTH = SizeSpecification(value=8, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    ARROW_HEAD_WIDTH = SizeSpecification(value=5, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    ARROW_SHAFT_WIDTH = SizeSpecification(value=0, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    ARROW_LINE_WIDTH = SizeSpecification(value=1, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    COMPONENT_LAYOUT = 2

    ##
    # \brief 
    #
    COMPONENT_LAYOUT_DIRECTION = 0

    ##
    # \brief 
    #
    COMPONENT_MARGIN = SizeSpecification(value=5, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    SHOW_REACTANTS = True

    ##
    # \brief 
    #
    SHOW_AGENTS = True

    ##
    # \brief 
    #
    SHOW_PRODUCTS = True

    ##
    # \brief 
    #
    AGENT_ALIGNMENT = 12

    ##
    # \brief 
    #
    AGENT_LAYOUT = 1

    ##
    # \brief 
    #
    AGENT_LAYOUT_DIRECTION = 0

    ##
    # \brief 
    #
    PLUS_SIGN_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief 
    #
    PLUS_SIGN_SIZE = SizeSpecification(value=10, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    PLUS_SIGN_LINE_WIDTH = SizeSpecification(value=3, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    SHOW_PLUS_SIGNS = True
