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
# \brief NOTReactionMatchExpression.
# 
class NOTReactionMatchExpression(ReactionMatchExpression):

    ##
    # \brief Constructs a <tt>NOTReactionMatchExpression</tt> object that wraps the match expression instance specified by <em>expr_ptr</em>.
    # 
    # \param expr_ptr A reference to the wrapped Chem.MatchExpression instance.
    # 
    def __init__(expr_ptr: NOTReactionMatchExpression) -> None: pass

    ##
    # \brief Constructs a <tt>NOTReactionMatchExpression</tt> object that wraps the match expression instance specified by <em>expr_ptr</em>.
    # 
    # \param expr_ptr A reference to the wrapped Chem.MatchExpression instance.
    # 
    def __init__(expr_ptr: ReactionMatchExpression) -> None: pass

    ##
    # \brief 
    # \param expression 
    # \return 
    #
    def assign(expression: NOTReactionMatchExpression) -> NOTReactionMatchExpression: pass
