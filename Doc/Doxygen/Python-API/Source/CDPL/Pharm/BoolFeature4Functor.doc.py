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
class BoolFeature4Functor(Boost.Python.instance):

    ##
    # \brief Initializes the \e %BoolFeature4Functor instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %BoolFeature4Functor instance with a copy of the state of the \e %BoolFeature4Functor instance \a func.
    # \param func The \e %BoolFeature4Functor instance to copy.
    # 
    def __init__(func: BoolFeature4Functor) -> None: pass

    ##
    # \brief Initializes the \e %BoolFeature4Functor instance.
    # \param callable 
    # 
    def __init__(callable: object) -> None: pass

    ##
    # \brief 
    # \param arg1 
    # \param arg2 
    # \param arg3 
    # \param arg4 
    # \return 
    #
    def __call__(arg1: Feature, arg2: Feature, arg3: Feature, arg4: Feature) -> bool: pass

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
