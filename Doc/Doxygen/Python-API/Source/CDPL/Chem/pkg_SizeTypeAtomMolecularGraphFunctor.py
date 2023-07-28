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
# \brief 
#
class SizeTypeAtomMolecularGraphFunctor(Boost.Python.instance):

    ##
    # \brief Initializes the \e %SizeTypeAtomMolecularGraphFunctor instance.
    # \param self The \e %SizeTypeAtomMolecularGraphFunctor instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %SizeTypeAtomMolecularGraphFunctor instance.
    # \param self The \e %SizeTypeAtomMolecularGraphFunctor instance to initialize.
    # \param func 
    # 
    def __init__(func: SizeTypeAtomMolecularGraphFunctor) -> None: pass

    ##
    # \brief Initializes the \e %SizeTypeAtomMolecularGraphFunctor instance.
    # \param arg1 The \e %SizeTypeAtomMolecularGraphFunctor instance to initialize.
    # \param callable 
    # 
    def __init__(callable: object) -> None: pass

    ##
    # \brief 
    # \param arg1 
    # \param arg2 
    # \return 
    #
    def __call__(arg1: Atom, arg2: MolecularGraph) -> int: pass

    ##
    # \brief 
    # \return 
    #
    def __bool__() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __nonzero__() -> bool: pass
