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
# \brief Provides keys for built-in Chem.Reaction properties.
# 
class ReactionProperty(Boost.Python.instance):

    ##
    # \brief Specifies the vertical alignment of the reaction agents relative to the reaction arrow.
    # 
    # Supported vertical alignment styles are defined in namespace Vis.Alignment. The specified alignment takes precedence over the alignment specified by the parameter Vis.ControlParameter.REACTION_AGENT_ALIGNMENT.
    # 
    # <b>Value Type:</b> <tt>unsigned int</tt>
    # 
    AGENT_ALIGNMENT = CDPL.Base.LookupKey(id=199, name='AGENT_ALIGNMENT')

    ##
    # \brief Specifies the style of the reaction agent layout.
    # 
    # Supported layout styles are defined in namespace Vis.LayoutStyle. The specified layout style takes precedence over the layout specified by the parameter Vis.ControlParameter.REACTION_AGENT_LAYOUT.
    # 
    # <b>Value Type:</b> <tt>unsigned int</tt>
    # 
    AGENT_LAYOUT = CDPL.Base.LookupKey(id=200, name='AGENT_LAYOUT')

    ##
    # \brief Specifies the direction of the reaction agent layout.
    # 
    # Supported layout directions are defined in namespace Vis.LayoutDirection. The specified layout direction takes precedence over the direction specified by the parameter Vis.ControlParameter.REACTION_AGENT_LAYOUT_DIRECTION.
    # 
    # <b>Value Type:</b> <tt>unsigned int</tt>
    # 
    AGENT_LAYOUT_DIRECTION = CDPL.Base.LookupKey(id=201, name='AGENT_LAYOUT_DIRECTION')

    ##
    # \brief Specifies the color of the reaction arrow.
    # 
    # The specified color takes precedence over the color specified by the parameter Vis.ControlParameter.REACTION_ARROW_COLOR.
    # 
    # <b>Value Type:</b> Vis.Color
    # 
    ARROW_COLOR = CDPL.Base.LookupKey(id=187, name='ARROW_COLOR')

    ##
    # \brief Specifies the head length of the reaction arrow.
    # 
    # The value of the specified length can be absolute or relative to the overall arrow length defined by Vis.ControlParameter.REACTION_ARROW_LENGTH or Vis.ReactionProperty.ARROW_LENGTH. The output- and input-scaling settings are ignored and have no effect. The specified length takes precedence over the length specified by the parameter Vis.ControlParameter.REACTION_ARROW_HEAD_LENGTH.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification
    # 
    ARROW_HEAD_LENGTH = CDPL.Base.LookupKey(id=189, name='ARROW_HEAD_LENGTH')

    ##
    # \brief Specifies the head width of the reaction arrow.
    # 
    # The value of the specified width can be absolute or relative to the overall arrow length defined by Vis.ControlParameter.REACTION_ARROW_LENGTH or Vis.ReactionProperty.ARROW_LENGTH. The output- and input-scaling settings are ignored and have no effect. The specified width takes precedence over the width specified by the parameter Vis.ControlParameter.REACTION_ARROW_HEAD_WIDTH.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification
    # 
    ARROW_HEAD_WIDTH = CDPL.Base.LookupKey(id=190, name='ARROW_HEAD_WIDTH')

    ##
    # \brief Specifies the length of the reaction arrow.
    # 
    # Specifying the length as beeing relative has the effect, that the given length is interpreted as a minimum length for an arrow which is as long as the width of the overall area covered by the drawn reaction agents (if any). The output- and input-scaling settings are ignored and have no effect. The specified length takes precedence over the length specified by the parameter Vis.ControlParameter.REACTION_ARROW_LENGTH.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification
    # 
    ARROW_LENGTH = CDPL.Base.LookupKey(id=188, name='ARROW_LENGTH')

    ##
    # \brief Specifies the line width of the reaction arrow outline.
    # 
    # The value of the specified width can be absolute or relative to the overall arrow length defined by Vis.ControlParameter.REACTION_ARROW_LENGTH or Vis.ReactionProperty.ARROW_LENGTH. The output- and input-scaling settings are ignored and have no effect. The specified width takes precedence over the width specified by the parameter Vis.ControlParameter.REACTION_ARROW_LINE_WIDTH.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification
    # 
    ARROW_LINE_WIDTH = CDPL.Base.LookupKey(id=192, name='ARROW_LINE_WIDTH')

    ##
    # \brief Specifies the shaft width of the reaction arrow.
    # 
    # The value of the specified width can be absolute or relative to the overall arrow length defined by Vis.ControlParameter.REACTION_ARROW_LENGTH or Vis.ReactionProperty.ARROW_LENGTH. The output- and input-scaling settings are ignored and have no effect. The specified width takes precedence over the width specified by the parameter Vis.ControlParameter.REACTION_ARROW_SHAFT_WIDTH.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification
    # 
    ARROW_SHAFT_WIDTH = CDPL.Base.LookupKey(id=191, name='ARROW_SHAFT_WIDTH')

    ##
    # \brief Specifies the style of the reaction arrow.
    # 
    # Supported styles are defined as constants in namespace Vis.ArrowStyle. The arrow style specified by this property takes precedence over the style specified by the parameter Vis.ControlParameter.REACTION_ARROW_STYLE.
    # 
    # <b>Value Type:</b> <tt>unsigned int</tt>
    # 
    ARROW_STYLE = CDPL.Base.LookupKey(id=186, name='ARROW_STYLE')

    ##
    # \brief Specifies the style of the reaction product and reactant layout.
    # 
    # Supported layout styles are defined in namespace Vis.LayoutStyle. The specified layout style takes precedence over the layout specified by the parameter Vis.ControlParameter.REACTION_COMPONENT_LAYOUT.
    # 
    # <b>Value Type:</b> <tt>unsigned int</tt>
    # 
    COMPONENT_LAYOUT = CDPL.Base.LookupKey(id=193, name='COMPONENT_LAYOUT')

    ##
    # \brief Specifies the direction of the reaction product and reactant layout.
    # 
    # Supported layout directions are defined in namespace Vis.LayoutDirection. The specified layout direction takes precedence over the direction specified by the parameter Vis.ControlParameter.REACTION_COMPONENT_LAYOUT_DIRECTION.
    # 
    # <b>Value Type:</b> <tt>unsigned int</tt>
    # 
    COMPONENT_LAYOUT_DIRECTION = CDPL.Base.LookupKey(id=194, name='COMPONENT_LAYOUT_DIRECTION')

    ##
    # \brief Specifies the amount of free space that is added horizontally and vertically to the bounds of a reaction component.
    # 
    # The margin width has to be specified as an absolute value. The output- and input-scaling settings are ignored and have no effect. The specified margin takes precedence over the margin specified by the parameter Vis.ControlParameter.REACTION_COMPONENT_MARGIN.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification
    # 
    COMPONENT_MARGIN = CDPL.Base.LookupKey(id=195, name='COMPONENT_MARGIN')

    ##
    # \brief Specifies whether or not to show the reactants of the reaction.
    # 
    # The reactant visibility specified by this property overrides the setting of the control-parameter Vis.ControlParameter.SHOW_REACTION_REACTANTS.
    # 
    # <b>Value Type:</b> <tt>bool</tt>
    # 
    SHOW_REACTANTS = CDPL.Base.LookupKey(id=196, name='SHOW_REACTANTS')

    ##
    # \brief Specifies whether or not to show the agents of the reaction.
    # 
    # The agent visibility specified by this property overrides the setting of the control-parameter Vis.ControlParameter.SHOW_REACTION_AGENTS.
    # 
    # <b>Value Type:</b> <tt>bool</tt>
    # 
    SHOW_AGENTS = CDPL.Base.LookupKey(id=197, name='SHOW_AGENTS')

    ##
    # \brief Specifies whether or not to show the products of the reaction.
    # 
    # The product visibility specified by this property overrides the setting of the control-parameter Vis.ControlParameter.SHOW_REACTION_PRODUCTS.
    # 
    # <b>Value Type:</b> <tt>bool</tt>
    # 
    SHOW_PRODUCTS = CDPL.Base.LookupKey(id=198, name='SHOW_PRODUCTS')

    ##
    # \brief Specifies the color of the '+' signs between the components of the reaction.
    # 
    # The specified color takes precedence over the color specified by the parameter Vis.ControlParameter.REACTION_PLUS_SIGN_COLOR.
    # 
    # <b>Value Type:</b> Vis.Color
    # 
    PLUS_SIGN_COLOR = CDPL.Base.LookupKey(id=202, name='PLUS_SIGN_COLOR')

    ##
    # \brief Specifies the line width of the '+' signs between the components of the reaction.
    # 
    # The size has to be specified as an absolute value. The output- and input-scaling settings are ignored and have no effect. The specified line width takes precedence over the width specified by the parameter Vis.ControlParameter.REACTION_PLUS_SIGN_LINE_WIDTH.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification
    # 
    PLUS_SIGN_LINE_WIDTH = CDPL.Base.LookupKey(id=204, name='PLUS_SIGN_LINE_WIDTH')

    ##
    # \brief Specifies the size of the '+' signs between the components of the reaction.
    # 
    # The size has to be specified as an absolute value. The output- and input-scaling settings are ignored and have no effect. The specified size takes precedence over the size specified by the parameter Vis.ControlParameter.REACTION_PLUS_SIGN_SIZE.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification
    # 
    PLUS_SIGN_SIZE = CDPL.Base.LookupKey(id=203, name='PLUS_SIGN_SIZE')

    ##
    # \brief Specifies whether or not to draw '+' signs between the components of the reaction.
    # 
    # The visibility specified by this property overrides the setting of the control-parameter Vis.ControlParameter.SHOW_REACTION_PLUS_SIGNS.
    # 
    # <b>Value Type:</b> <tt>bool</tt>
    # 
    SHOW_PLUS_SIGNS = CDPL.Base.LookupKey(id=205, name='SHOW_PLUS_SIGNS')
