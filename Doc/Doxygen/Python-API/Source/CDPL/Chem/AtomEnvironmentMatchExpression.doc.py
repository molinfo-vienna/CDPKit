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
# \brief AtomEnvironmentMatchExpression.
# 
class AtomEnvironmentMatchExpression(AtomMatchExpression):

    ##
    # \brief Constructs an <tt>AtomEnvironmentMatchExpression</tt> instance for the specified atom environment pattern and matching mode.
    # 
    # \param env_pattern A substructure search pattern that describes the required (or not desired) structural environment of matching target atoms. Note: The substructure pattern has to be formulated in a way that the first atom of the pattern molecule matches the target atoms.
    # \param not_match Specifies whether the environment of a target atom actually has to match (<tt>True</tt>) or <em>not</em> match (<tt>False</tt>) the given query environment pattern.
    # 
    def __init__(env_pattern: MolecularGraph, not_match: bool) -> None: pass
