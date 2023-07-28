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
# \brief Implements the perception of aromatic atoms and bonds in a molecular graph.
# 
class AromaticSubstructure(Fragment):

    ##
    # \brief Constructs an empty <tt>AromaticSubstructure</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Construct a <tt>AromaticSubstructure</tt> instance that consists of the aromatic atoms and bonds of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to perceive aromatic atoms and bonds.
    # 
    def __init__(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the currently stored atoms and bonds by the set of aromatic atoms and bonds of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to perceive aromatic atoms and bonds.
    # 
    def perceive(molgraph: MolecularGraph) -> None: pass
