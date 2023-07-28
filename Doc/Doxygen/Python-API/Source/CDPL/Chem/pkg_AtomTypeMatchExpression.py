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
# \brief AtomTypeMatchExpression.
# 
class AtomTypeMatchExpression(AtomMatchExpression):

    ##
    # \brief Initializes the \e %AtomTypeMatchExpression instance.
    # \param self The \e %AtomTypeMatchExpression instance to initialize.
    # \param expr 
    # 
    def __init__(expr: AtomTypeMatchExpression) -> None: pass

    ##
    # \brief Constructs an <tt>AtomTypeMatchExpression</tt> instance for the specified query atom type and matching mode.
    # 
    # \param atom_type The atom type that has to be matched (or not matched) by target atoms.
    # \param not_match Specifies whether the type of a target atom actually has to match (<tt>True</tt>) or <em>not</em> match (<tt>False</tt>) the query atom type.
    # 
    def __init__(atom_type: int, not_match: bool) -> None: pass

    ##
    # \brief 
    # \param expr 
    # \return 
    #
    def assign(expr: AtomTypeMatchExpression) -> AtomTypeMatchExpression: pass
