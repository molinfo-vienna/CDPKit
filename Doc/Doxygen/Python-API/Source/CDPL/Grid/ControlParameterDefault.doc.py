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
    # \brief Default value (= <tt>False</tt>) of the control-parameter Grid.ControlParameter.STRICT_ERROR_CHECKING.
    # 
    STRICT_ERROR_CHECKING = False

    ##
    # \brief Default value (= <tt>False</tt>) of the control-parameter Grid.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS.
    # 
    # \since 1.2
    # 
    CDF_OUTPUT_SINGLE_PRECISION_FLOATS = True

    ##
    # \brief Default value (= <tt>False</tt>) of the control-parameter Grid.ControlParameter.CUBE_COMMENT_IS_NAME.
    # 
    # \since 1.4
    # 
    CUBE_COMMENT_IS_NAME = False

    ##
    # \brief Default value (= <tt>1/0.52918</tt>) of the control-parameter Grid.ControlParameter.CUBE_INPUT_DISTANCE_SCALING_FACTOR.
    # 
    # The default value performs a conversion from Bohr to Ångstrom.
    # 
    # \since 1.4
    # 
    CUBE_INPUT_DISTANCE_SCALING_FACTOR = 0.52918

    ##
    # \brief Default value (= <tt>0.52918</tt>) of the control-parameter Grid.ControlParameter.CUBE_OUTPUT_DISTANCE_SCALING_FACTOR.
    # 
    # The default value performs a conversion from Ångstrom to Bohr.
    # 
    # \since 1.4
    # 
    CUBE_OUTPUT_DISTANCE_SCALING_FACTOR = 1.8897161646320724
