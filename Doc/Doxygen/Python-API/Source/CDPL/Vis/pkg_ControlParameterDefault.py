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
# \brief Provides default values for built-in control-parameters.
# 
class ControlParameterDefault(Boost.Python.instance):

    ##
    # \brief Default setting (= <tt>Rectangle2D</tt>()) for the control-parameter Vis.ControlParameter.VIEWPORT.
    # 
    VIEWPORT = Rectangle2D()

    ##
    # \brief Default setting (= <tt>SizeAdjustment.IF_REQUIRED</tt>) for the control-parameter Vis.ControlParameter.SIZE_ADJUSTMENT.
    # 
    SIZE_ADJUSTMENT = 2

    ##
    # \brief Default setting (= <tt>Alignment.CENTER</tt>) for the control-parameter Vis.ControlParameter.ALIGNMENT.
    # 
    ALIGNMENT = 15

    ##
    # \brief Default setting (= <tt>Color.TRANSPARENT</tt>) for the control-parameter Vis.ControlParameter.BACKGROUND_COLOR.
    # 
    BACKGROUND_COLOR = Color()

    ##
    # \brief Default setting (= <tt>ArrowStyle.REACTION_SOLID</tt>) for the control-parameter Vis.ControlParameter.REACTION_ARROW_STYLE.
    # 
    REACTION_ARROW_STYLE = 1

    ##
    # \brief Default setting (= <tt>Color.BLACK</tt>) for the control-parameter Vis.ControlParameter.REACTION_ARROW_COLOR.
    # 
    REACTION_ARROW_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(35.0, True, True, True)) for the control-parameter Vis.ControlParameter.REACTION_ARROW_LENGTH.
    # 
    REACTION_ARROW_LENGTH = SizeSpecification(value=35, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(8.0, False, True, True)) for the control-parameter Vis.ControlParameter.REACTION_ARROW_HEAD_LENGTH.
    # 
    REACTION_ARROW_HEAD_LENGTH = SizeSpecification(value=8, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(5.0, False, True, True)) for the control-parameter Vis.ControlParameter.REACTION_ARROW_HEAD_WIDTH.
    # 
    REACTION_ARROW_HEAD_WIDTH = SizeSpecification(value=5, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(0.0, False, True, True)) for the control-parameter Vis.ControlParameter.REACTION_ARROW_SHAFT_WIDTH.
    # 
    REACTION_ARROW_SHAFT_WIDTH = SizeSpecification(value=0, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(1.0, False, True, True)) for the control-parameter Vis.ControlParameter.REACTION_ARROW_LINE_WIDTH.
    # 
    REACTION_ARROW_LINE_WIDTH = SizeSpecification(value=1, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>LayoutStyle.PACKED</tt>) for the control-parameter Vis.ControlParameter.REACTION_COMPONENT_LAYOUT.
    # 
    REACTION_COMPONENT_LAYOUT = 2

    ##
    # \brief Default setting (= <tt>LayoutDirection.HORIZONTAL</tt>) for the control-parameter Vis.ControlParameter.REACTION_COMPONENT_LAYOUT_DIRECTION.
    # 
    REACTION_COMPONENT_LAYOUT_DIRECTION = 0

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(5.0, False, True, True)) for the control-parameter Vis.ControlParameter.REACTION_COMPONENT_MARGIN.
    # 
    REACTION_COMPONENT_MARGIN = SizeSpecification(value=5, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_REACTION_REACTANTS.
    # 
    SHOW_REACTION_REACTANTS = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_REACTION_AGENTS.
    # 
    SHOW_REACTION_AGENTS = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_REACTION_PRODUCTS.
    # 
    SHOW_REACTION_PRODUCTS = True

    ##
    # \brief Default setting (= <tt>Alignment.V_CENTER</tt>) for the control-parameter Vis.ControlParameter.REACTION_AGENT_ALIGNMENT.
    # 
    REACTION_AGENT_ALIGNMENT = 12

    ##
    # \brief Default setting (= <tt>LayoutStyle.LINEAR</tt>) for the control-parameter Vis.ControlParameter.REACTION_AGENT_LAYOUT.
    # 
    REACTION_AGENT_LAYOUT = 1

    ##
    # \brief Default setting (= <tt>LayoutDirection.HORIZONTAL</tt>) for the control-parameter Vis.ControlParameter.REACTION_AGENT_LAYOUT_DIRECTION.
    # 
    REACTION_AGENT_LAYOUT_DIRECTION = 0

    ##
    # \brief Default setting (= <tt>Color.BLACK</tt>) for the control-parameter Vis.ControlParameter.REACTION_PLUS_SIGN_COLOR.
    # 
    REACTION_PLUS_SIGN_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(10.0, False, True, True)) for the control-parameter Vis.ControlParameter.REACTION_PLUS_SIGN_SIZE.
    # 
    REACTION_PLUS_SIGN_SIZE = SizeSpecification(value=10, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(3.0, False, True, True)) for the control-parameter Vis.ControlParameter.REACTION_PLUS_SIGN_LINE_WIDTH.
    # 
    REACTION_PLUS_SIGN_LINE_WIDTH = SizeSpecification(value=3, relative=False, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_REACTION_PLUS_SIGNS.
    # 
    SHOW_REACTION_PLUS_SIGNS = True

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Vis.ControlParameter.USE_CALCULATED_ATOM_COORDINATES.
    # 
    USE_CALCULATED_ATOM_COORDINATES = False

    ##
    # \brief Default setting (= <tt>Color.BLACK</tt>) for the control-parameter Vis.ControlParameter.ATOM_COLOR.
    # 
    ATOM_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default setting (= <tt>Font</tt>()) for the control-parameter Vis.ControlParameter.ATOM_LABEL_FONT.
    # 
    ATOM_LABEL_FONT = Font()

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(10.0, False, False, True)) for the control-parameter Vis.ControlParameter.ATOM_LABEL_SIZE.
    # 
    ATOM_LABEL_SIZE = SizeSpecification(value=10, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default setting (= <tt>Font</tt>()) for the control-parameter Vis.ControlParameter.SECONDARY_ATOM_LABEL_FONT.
    # 
    SECONDARY_ATOM_LABEL_FONT = Font()

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(6.0, False, False, True)) for the control-parameter Vis.ControlParameter.SECONDARY_ATOM_LABEL_SIZE.
    # 
    SECONDARY_ATOM_LABEL_SIZE = SizeSpecification(value=6, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(2.0, False, False, True)) for the control-parameter Vis.ControlParameter.ATOM_LABEL_MARGIN.
    # 
    ATOM_LABEL_MARGIN = SizeSpecification(value=2, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(1.0, False, False, True)) for the control-parameter Vis.ControlParameter.RADICAL_ELECTRON_DOT_SIZE.
    # 
    RADICAL_ELECTRON_DOT_SIZE = SizeSpecification(value=1, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Vis.ControlParameter.SHOW_CARBONS.
    # 
    SHOW_CARBONS = False

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_EXPLICIT_HYDROGENS.
    # 
    SHOW_EXPLICIT_HYDROGENS = False

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_CHARGES.
    # 
    SHOW_CHARGES = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_ISOTOPES.
    # 
    SHOW_ISOTOPES = True

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Vis.ControlParameter.SHOW_HYDROGEN_COUNTS.
    # 
    SHOW_HYDROGEN_COUNTS = False

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_NON_CARBON_HYDROGEN_COUNTS.
    # 
    SHOW_NON_CARBON_HYDROGEN_COUNTS = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_ATOM_QUERY_INFOS.
    # 
    SHOW_ATOM_QUERY_INFOS = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_ATOM_REACTION_INFOS.
    # 
    SHOW_ATOM_REACTION_INFOS = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_RADICAL_ELECTRONS.
    # 
    SHOW_RADICAL_ELECTRONS = True

    ##
    # \brief Default setting (= <tt>Color.BLACK</tt>) for the control-parameter Vis.ControlParameter.BOND_COLOR.
    # 
    BOND_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(30.0)) for the control-parameter Vis.ControlParameter.BOND_LENGTH.
    # 
    BOND_LENGTH = SizeSpecification(value=30, relative=False, in_scaling=False, out_scaling=False)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(1.0, False, False, True)) for the control-parameter Vis.ControlParameter.BOND_LINE_WIDTH.
    # 
    BOND_LINE_WIDTH = SizeSpecification(value=1, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(0.15, True, True, True)) for the control-parameter Vis.ControlParameter.BOND_LINE_SPACING.
    # 
    BOND_LINE_SPACING = SizeSpecification(value=0.15, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(0.15, True, True, True)) for the control-parameter Vis.ControlParameter.STEREO_BOND_WEDGE_WIDTH.
    # 
    STEREO_BOND_WEDGE_WIDTH = SizeSpecification(value=0.15, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(0.1, True, True, True)) for the control-parameter Vis.ControlParameter.STEREO_BOND_HASH_SPACING.
    # 
    STEREO_BOND_HASH_SPACING = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(0.4, True, True, True)) for the control-parameter Vis.ControlParameter.REACTION_CENTER_LINE_LENGTH.
    # 
    REACTION_CENTER_LINE_LENGTH = SizeSpecification(value=0.4, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(0.1, True, True, True)) for the control-parameter Vis.ControlParameter.REACTION_CENTER_LINE_SPACING.
    # 
    REACTION_CENTER_LINE_SPACING = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(0.1, True, True, True)) for the control-parameter Vis.ControlParameter.DOUBLE_BOND_TRIM_LENGTH.
    # 
    DOUBLE_BOND_TRIM_LENGTH = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(0.1, True, True, True)) for the control-parameter Vis.ControlParameter.TRIPLE_BOND_TRIM_LENGTH.
    # 
    TRIPLE_BOND_TRIM_LENGTH = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default setting (= <tt>Font</tt>()) for the control-parameter Vis.ControlParameter.BOND_LABEL_FONT.
    # 
    BOND_LABEL_FONT = Font()

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(8.0, False, False, True)) for the control-parameter Vis.ControlParameter.BOND_LABEL_SIZE.
    # 
    BOND_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(2.0, False, False, True)) for the control-parameter Vis.ControlParameter.BOND_LABEL_MARGIN.
    # 
    BOND_LABEL_MARGIN = SizeSpecification(value=2, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_BOND_REACTION_INFOS.
    # 
    SHOW_BOND_REACTION_INFOS = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_BOND_QUERY_INFOS.
    # 
    SHOW_BOND_QUERY_INFOS = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_STEREO_BONDS.
    # 
    SHOW_STEREO_BONDS = True
