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
# \brief Implementation of Ertl's algorithm [\ref FGPE] for the identification of functional groups in organic molecules.
# 
# \since 1.3
# 
class FunctionalGroupList(Chem.FragmentList):

    ##
    # \brief Constructs an empty <tt>FunctionalGroupList</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a <tt>FunctionalGroupList</tt> instance and extracts the functional groups of <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to extract the functional groups.
    # 
    def __init__(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Constructs a copy of the <tt>FunctionalGroupList</tt> instance <em>fg_list</em>.
    # 
    # \param fg_list The <tt>FunctionalGroupList</tt> to copy.
    # 
    def __init__(fg_list: FunctionalGroupList) -> None: pass

    ##
    # \brief Replaces the contents of this list with a copy of <em>fg_list</em>.
    # 
    # \param fg_list The source list.
    # 
    # \return \a self
    # 
    def assign(fg_list: FunctionalGroupList) -> FunctionalGroupList: pass

    ##
    # \brief Extracts the functional groups of <em>molgraph</em> and stores them as fragments of this list.
    # 
    # \param molgraph The molecular graph for which to extract the functional groups.
    # 
    def extract(molgraph: Chem.MolecularGraph) -> None: pass
