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
# \brief Provides keys for built-in control-parameters.
# 
class ControlParameter(Boost.Python.instance):

    ##
    # \brief Specifies whether non-fatal recoverable I/O errors should be ignored or cause an I/O operation to fail.
    # 
    # If the control-parameter is set to <tt>True</tt>, not only severe errors cause an I/O operation to fail, but also non-fatal errors from which a recovery would be possible. If the control-parameter is set to <tt>False</tt>, I/O operations will proceed even if a non-fatal error has been detected.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    STRICT_ERROR_CHECKING = CDPL.Base.LookupKey('STRICT_ERROR_CHECKING')

    ##
    # \brief Specifies whether CDF-format grid output uses single-precision floats (<tt>True</tt>) or double-precision (<tt>False</tt>). 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.2
    # 
    CDF_OUTPUT_SINGLE_PRECISION_FLOATS = CDPL.Base.LookupKey('CDF_OUTPUT_SINGLE_PRECISION_FLOATS')

    ##
    # \brief Specifies whether the comment line of a <em>Gaussian CUBE</em> file is taken as the grid name or treated as a regular comment on data I/O.
    # 
    # \see [\ref CUBE] 
    # \valuetype  <tt>bool</tt> 
    # 
    # \since 1.4
    # 
    CUBE_COMMENT_IS_NAME = CDPL.Base.LookupKey('CUBE_COMMENT_IS_NAME')

    ##
    # \brief Specifies the scaling factor to apply to distances read from data in <em>Gaussian CUBE</em> format.
    # 
    # \see [\ref CUBE] 
    # \valuetype  <tt>double</tt> 
    # 
    # \since 1.4
    # 
    CUBE_INPUT_DISTANCE_SCALING_FACTOR = CDPL.Base.LookupKey('CUBE_INPUT_DISTANCE_SCALING_FACTOR')

    ##
    # \brief Specifies the scaling factor to apply to distances for <em>Gaussian CUBE</em> format data output.
    # 
    # \see [\ref CUBE] 
    # \valuetype  <tt>double</tt> 
    # 
    # \since 1.4
    # 
    CUBE_OUTPUT_DISTANCE_SCALING_FACTOR = CDPL.Base.LookupKey('CUBE_OUTPUT_DISTANCE_SCALING_FACTOR')
