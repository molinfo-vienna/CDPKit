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
# \brief MolecularGraphComponentGroupingMatchExpression.
# 
# \see [\ref SMARTS]
# 
class MolecularGraphComponentGroupingMatchExpression(MolecularGraphMatchExpression):

    ##
    # \brief Initializes the \e %MolecularGraphComponentGroupingMatchExpression instance.
    # \param self The \e %MolecularGraphComponentGroupingMatchExpression instance to initialize.
    # \param expr 
    # 
    def __init__(expr: MolecularGraphComponentGroupingMatchExpression) -> None: pass

    ##
    # \brief Constructs a <tt>MolecularGraphComponentGroupingMatchExpression</tt> instance for the specified component-level grouping.
    # 
    # \param comp_grouping Specifies the component-level grouping constraints that have to be fulfilled by matching target molecuar graphs.
    # 
    def __init__(comp_grouping: FragmentList) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MolecularGraphComponentGroupingMatchExpression instance \a expr.
    # \param self The \e %MolecularGraphComponentGroupingMatchExpression instance this method is called upon.
    # \param expr The \e %MolecularGraphComponentGroupingMatchExpression instance to copy.
    # \return \a self
    # 
    def assign(expr: MolecularGraphComponentGroupingMatchExpression) -> MolecularGraphComponentGroupingMatchExpression: pass
