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
# \brief BondDirectionMatchExpression.
# 
class BondDirectionMatchExpression(BondMatchExpression):

    ##
    # \brief Initializes the \e %BondDirectionMatchExpression instance.
    # \param self The \e %BondDirectionMatchExpression instance to initialize.
    # \param expr 
    # 
    def __init__(expr: BondDirectionMatchExpression) -> None: pass

    ##
    # \brief Constructs an <tt>BondDirectionMatchExpression</tt> instance for the specified matching mode and bond direction constraints.
    # 
    # \param dir_flags A bitwise OR combination of the flags defined in namespace Chem.BondDirection that specifies constraints on the direction of matching target bonds.
    # \param not_match Specifies whether the direction of a target bond actually has to match (<tt>True</tt>) or <em>not</em> match (<tt>False</tt>) the query direction constraints.
    # 
    def __init__(dir_flags: int, not_match: bool) -> None: pass

    ##
    # \brief 
    # \param expr 
    # \return 
    #
    def assign(expr: BondDirectionMatchExpression) -> BondDirectionMatchExpression: pass
