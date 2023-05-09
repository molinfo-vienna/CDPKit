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
# \brief 
#
class PropertyValueProduct(builtins.object):

    ##
    # \brief Initializes the \e %PropertyValueProduct instance.
    # \param key 
    #
    def __init__(key: PropertyKey) -> None: pass

    ##
    # \brief 
    # \param cntnr1 
    # \param cntnr2 
    # \return 
    #
    def __call__(cntnr1: CDPL.Base.PropertyContainer, cntnr2: CDPL.Base.PropertyContainer) -> object: pass
