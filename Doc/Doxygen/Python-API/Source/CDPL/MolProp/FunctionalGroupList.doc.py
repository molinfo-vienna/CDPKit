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
    # \brief Initializes the \e %FunctionalGroupList instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %FunctionalGroupList instance.
    # \param molgraph 
    # 
    def __init__(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Initializes a copy of the \e %FunctionalGroupList instance \a fg_list.
    # \param fg_list The \e %FunctionalGroupList instance to copy.
    # 
    def __init__(fg_list: FunctionalGroupList) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %FunctionalGroupList instance \a fg_list.
    # \param fg_list The \c %FunctionalGroupList instance to copy.
    # \return \a self
    # 
    def assign(fg_list: FunctionalGroupList) -> FunctionalGroupList: pass

    ##
    # \brief 
    # \param molgraph 
    #
    def extract(molgraph: Chem.MolecularGraph) -> None: pass
