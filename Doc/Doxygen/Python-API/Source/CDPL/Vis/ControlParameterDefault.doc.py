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
    # \brief Default setting (= <tt>1.0</tt>) for the control-parameter Vis.ControlParameter.OUTPUT_SCALING_FACTOR.
    # 
    OUTPUT_SCALING_FACTOR = 1.0

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
    # \brief Default setting (= <tt>Brush</tt>(Color.WHITE, Brush.NO_PATTERN)) for the control-parameter Vis.ControlParameter.BACKGROUND_BRUSH.
    # 
    BACKGROUND_BRUSH = Brush(color=Color(r=1, g=1, b=1), style=NO_PATTERN)

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
    # \brief Default setting (= <tt>SizeSpecification</tt>(1.0, False, False, True)) for the control-parameter Vis.ControlParameter.HIGHLIGHT_AREA_OUTLINE_WIDTH.
    # 
    # \since 1.2
    # 
    HIGHLIGHT_AREA_OUTLINE_WIDTH = SizeSpecification(value=1, relative=False, in_scaling=False, out_scaling=True)

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
    # \brief Default setting (= <tt>SizeSpecification</tt>(16.0, False, False, True)) for the control-parameter Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_SIZE.
    # 
    # \since 1.2
    # 
    ATOM_HIGHLIGHT_AREA_SIZE = SizeSpecification(value=16, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default setting (= <tt>Brush</tt>(Color(0.8, 0.8, 1.0)) for the control-parameter Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_BRUSH.
    # 
    # \since 1.2
    # 
    ATOM_HIGHLIGHT_AREA_BRUSH = Brush(color=Color(r=0.8, g=0.8, b=1), style=SOLID_PATTERN)

    ##
    # \brief Default setting (= <tt>Pen</tt>(Color(0.6, 0.6, 0.75)) for the control-parameter Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_OUTLINE_PEN.
    # 
    # \since 1.2
    # 
    ATOM_HIGHLIGHT_AREA_OUTLINE_PEN = Pen(color=Color(r=0.6, g=0.6, b=0.75), width=1, line_style=SOLID_LINE, cap_style=ROUND_CAP, join_style=ROUND_JOIN)

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Vis.ControlParameter.BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE.
    # 
    # \since 1.2
    # 
    BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE = False

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

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Vis.ControlParameter.SHOW_ATOM_CONFIGURATION_LABELS.
    # 
    # \since 1.1
    # 
    SHOW_ATOM_CONFIGURATION_LABELS = False

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_ATOM_CUSTOM_LABELS.
    # 
    # \since 1.2
    # 
    SHOW_ATOM_CUSTOM_LABELS = True

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Vis.ControlParameter.SHOW_BOND_CONFIGURATION_LABELS.
    # 
    # \since 1.1
    # 
    SHOW_BOND_CONFIGURATION_LABELS = False

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.SHOW_BOND_CUSTOM_LABELS.
    # 
    # \since 1.2
    # 
    SHOW_BOND_CUSTOM_LABELS = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.ENABLE_ATOM_HIGHLIGHTING.
    # 
    # \since 1.2
    # 
    ENABLE_ATOM_HIGHLIGHTING = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Vis.ControlParameter.ENABLE_BOND_HIGHLIGHTING.
    # 
    # \since 1.2
    # 
    ENABLE_BOND_HIGHLIGHTING = True

    ##
    # \brief Default setting (= <tt>Color.BLACK</tt>) for the control-parameter Vis.ControlParameter.BOND_COLOR.
    # 
    BOND_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(30.0)) for the control-parameter Vis.ControlParameter.BOND_LENGTH.
    # 
    BOND_LENGTH = SizeSpecification(value=30, relative=False, in_scaling=False, out_scaling=False)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(1.5, False, False, True)) for the control-parameter Vis.ControlParameter.BOND_LINE_WIDTH.
    # 
    BOND_LINE_WIDTH = SizeSpecification(value=1.5, relative=False, in_scaling=False, out_scaling=True)

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
    # \brief Default setting (= <tt>Font</tt>("", 8.0, False, True)) for the control-parameter Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_FONT.
    # 
    # \since 1.1
    # 
    ATOM_CONFIGURATION_LABEL_FONT = Font(family='', size=8, bold=False, italic=True, ulined=False, olined=False, strkdout=False, fxdpitch=False)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(8.0, False, False, True)) for the control-parameter Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_SIZE.
    # 
    # \since 1.1
    # 
    ATOM_CONFIGURATION_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default setting (= <tt>Color.BLACK</tt>) for the control-parameter Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_COLOR.
    # 
    # \since 1.2
    # 
    ATOM_CONFIGURATION_LABEL_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default setting (= <tt>Font</tt>("", 8.0, False, False)) for the control-parameter Vis.ControlParameter.ATOM_CUSTOM_LABEL_FONT.
    # 
    # \since 1.2
    # 
    ATOM_CUSTOM_LABEL_FONT = Font(family='', size=8, bold=False, italic=False, ulined=False, olined=False, strkdout=False, fxdpitch=False)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(8.0, False, False, True)) for the control-parameter Vis.ControlParameter.ATOM_CUSTOM_LABEL_SIZE.
    # 
    # \since 1.2
    # 
    ATOM_CUSTOM_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default setting (= <tt>Color.BLACK</tt>) for the control-parameter Vis.ControlParameter.ATOM_CUSTOM_LABEL_COLOR.
    # 
    # \since 1.2
    # 
    ATOM_CUSTOM_LABEL_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default setting (= <tt>Font</tt>("", 8.0, False, True)) for the control-parameter Vis.ControlParameter.BOND_CONFIGURATION_LABEL_FONT.
    # 
    # \since 1.1
    # 
    BOND_CONFIGURATION_LABEL_FONT = Font(family='', size=8, bold=False, italic=True, ulined=False, olined=False, strkdout=False, fxdpitch=False)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(8.0, False, False, True)) for the control-parameter Vis.ControlParameter.BOND_CONFIGURATION_LABEL_SIZE.
    # 
    # \since 1.1
    # 
    BOND_CONFIGURATION_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default setting (= <tt>Color.BLACK</tt>) for the control-parameter Vis.ControlParameter.BOND_CONFIGURATION_LABEL_COLOR.
    # 
    # \since 1.2
    # 
    BOND_CONFIGURATION_LABEL_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default setting (= <tt>Font</tt>("", 8.0, False, False)) for the control-parameter Vis.ControlParameter.BOND_CUSTOM_LABEL_FONT.
    # 
    # \since 1.2
    # 
    BOND_CUSTOM_LABEL_FONT = Font(family='', size=8, bold=False, italic=False, ulined=False, olined=False, strkdout=False, fxdpitch=False)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(8.0, False, False, True)) for the control-parameter Vis.ControlParameter.BOND_CUSTOM_LABEL_SIZE.
    # 
    # \since 1.2
    # 
    BOND_CUSTOM_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default setting (= <tt>Color.BLACK</tt>) for the control-parameter Vis.ControlParameter.BOND_CUSTOM_LABEL_COLOR.
    # 
    # \since 1.2
    # 
    BOND_CUSTOM_LABEL_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default setting (= <tt>SizeSpecification</tt>(12.0, False, False, True)) for the control-parameter Vis.ControlParameter.BOND_HIGHLIGHT_AREA_WIDTH.
    # 
    # \since 1.2
    # 
    BOND_HIGHLIGHT_AREA_WIDTH = SizeSpecification(value=12, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default setting (= <tt>Brush</tt>(Color(0.8, 0.8, 1.0)) for the control-parameter Vis.ControlParameter.BOND_HIGHLIGHT_AREA_BRUSH.
    # 
    # \since 1.2
    # 
    BOND_HIGHLIGHT_AREA_BRUSH = Brush(color=Color(r=0.8, g=0.8, b=1), style=SOLID_PATTERN)

    ##
    # \brief Default setting (= <tt>Pen</tt>(Color(0.6, 0.6, 0.75)) for the control-parameter Vis.ControlParameter.BOND_HIGHLIGHT_AREA_OUTLINE_PEN.
    # 
    # \since 1.2
    # 
    BOND_HIGHLIGHT_AREA_OUTLINE_PEN = Pen(color=Color(r=0.6, g=0.6, b=0.75), width=1, line_style=SOLID_LINE, cap_style=ROUND_CAP, join_style=ROUND_JOIN)

    ##
    # \brief Default setting (= <tt>Pen</tt>(Pen.NO_LINE)) for the control-parameter Vis.ControlParameter.GRID_VIEW_BORDER_PEN.
    # 
    # \since 1.2
    # 
    GRID_VIEW_BORDER_PEN = Pen(color=Color(), width=1, line_style=NO_LINE, cap_style=ROUND_CAP, join_style=ROUND_JOIN)

    ##
    # \brief Default setting (= <tt>Pen</tt>(Pen.NO_LINE)) for the control-parameter Vis.ControlParameter.GRID_VIEW_ROW_SEPARATOR_PEN.
    # 
    # \since 1.2
    # 
    GRID_VIEW_ROW_SEPARATOR_PEN = Pen(color=Color(), width=1, line_style=NO_LINE, cap_style=ROUND_CAP, join_style=ROUND_JOIN)

    ##
    # \brief Default setting (= <tt>Pen</tt>(Pen.NO_LINE)) for the control-parameter Vis.ControlParameter.GRID_VIEW_COLUMN_SEPARATOR_PEN.
    # 
    # \since 1.2
    # 
    GRID_VIEW_COLUMN_SEPARATOR_PEN = Pen(color=Color(), width=1, line_style=NO_LINE, cap_style=ROUND_CAP, join_style=ROUND_JOIN)

    ##
    # \brief Default setting (= <tt>0.0</tt>) for the control-parameter Vis.ControlParameter.GRID_VIEW_MARGIN.
    # 
    # \since 1.2
    # 
    GRID_VIEW_MARGIN = 0.0

    ##
    # \brief Default setting (= <tt>5.0</tt>) for the control-parameter Vis.ControlParameter.GRID_VIEW_CELL_PADDING.
    # 
    # \since 1.2
    # 
    GRID_VIEW_CELL_PADDING = 5.0

    ##
    # \brief Default setting (= <tt>Font</tt>("", 10.0)) for the control-parameter Vis.ControlParameter.GRID_VIEW_TEXT_FONT.
    # 
    # \since 1.2
    # 
    GRID_VIEW_TEXT_FONT = Font(family='', size=10, bold=False, italic=False, ulined=False, olined=False, strkdout=False, fxdpitch=False)

    ##
    # \brief Default setting (= <tt>Color.BLACK</tt>) for the control-parameter Vis.ControlParameter.GRID_VIEW_TEXT_COLOR.
    # 
    # \since 1.2
    # 
    GRID_VIEW_TEXT_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default setting (= <tt>ColorTable</tt>()) for the control-parameter Vis.ControlParameter.FEATURE_COLOR_TABLE.
    # 
    # \since 1.3
    # 
    FEATURE_COLOR_TABLE = ColorTable({0: (0.6, 0.5, 0, 0.5), 1: (0.8, 0.6, 0.04, 0.2), 2: (0.14, 0.15, 0.45, 0.3), 3: (0.48, 0.12, 0.12, 0.3), 4: (0.12, 0.12, 0.48, 0.3), 5: (0.12, 0.48, 0.12, 0.5), 6: (0.48, 0.12, 0.12, 0.5), 7: (0.69, 0.4, 0.69, 0.5), 8: (0.69, 0.4, 0.69, 0.5), 9: (0.24, 0.24, 0.24, 0.2)})
