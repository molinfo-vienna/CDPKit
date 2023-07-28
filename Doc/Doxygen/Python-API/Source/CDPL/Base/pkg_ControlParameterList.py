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
# \brief A data structure for the storage and lookup of control-parameter values.
# 
# \see Base.ControlParameterContainer for a description of the available methods.
# 
class ControlParameterList(ControlParameterContainer):

    ##
    # \brief Constructs an empty <tt>ControlParameterList</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>ControlParameterContainer</tt> instance <em>cntnr</em>.
    # 
    # \param cntnr The <tt>ControlParameterContainer</tt> instance to copy.
    # 
    # \note Only the control-parameter entries of <em>cntnr</em> are copied. Entries in the parent container of <em>cntnr</em> (if set) will be ignored (see setParent()).
    # 
    def __init__(cntnr: ControlParameterContainer) -> None: pass

    ##
    # \brief Assignment operator.
    # 
    # \param cntnr The <tt>ControlParameterContainer</tt> instance to copy.
    # 
    # \return \a self
    # 
    def assign(cntnr: ControlParameterContainer) -> ControlParameterList: pass
