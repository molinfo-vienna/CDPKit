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
# \brief ReactionAtomMappingMatchExpression.
# 
class ReactionAtomMappingMatchExpression(ReactionMatchExpression):

    ##
    # \brief Initializes a copy of the \e %ReactionAtomMappingMatchExpression instance \a expr.
    # \param expr The \e %ReactionAtomMappingMatchExpression instance to copy.
    # 
    def __init__(expr: ReactionAtomMappingMatchExpression) -> None: pass

    ##
    # \brief Constructs a <tt>ReactionAtomMappingMatchExpression</tt> instance for the specified reactant to product atom mapping.
    # 
    # \param atom_mapping Specifies the reactant to product atom mapping constraint that has to be fulfilled by matching target reactions.
    # 
    def __init__(atom_mapping: AtomMapping) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ReactionAtomMappingMatchExpression instance \a expr.
    # \param expr The \c %ReactionAtomMappingMatchExpression instance to copy.
    # \return \a self
    # 
    def assign(expr: ReactionAtomMappingMatchExpression) -> ReactionAtomMappingMatchExpression: pass
