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
class NOTMolecularGraphMatchExpression(MolecularGraphMatchExpression):

    ##
    # \brief Replaces the current state of \a arg1 with a copy of the state of the \e %NOTMolecularGraphMatchExpression instance \a expression.
    # \param expression The \e %NOTMolecularGraphMatchExpression instance to copy.
    # \return \a arg1
    #
    def assign(expression: NOTMolecularGraphMatchExpression) -> NOTMolecularGraphMatchExpression: pass
