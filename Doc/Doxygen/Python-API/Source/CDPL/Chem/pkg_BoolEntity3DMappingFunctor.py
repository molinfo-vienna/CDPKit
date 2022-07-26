#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
class BoolEntity3DMappingFunctor(Boost.Python.instance):

    ##
    # \brief Initializes the \e %BoolEntity3DMappingFunctor instance.
    # \param self The \e %BoolEntity3DMappingFunctor instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %BoolEntity3DMappingFunctor instance.
    # \param self The \e %BoolEntity3DMappingFunctor instance to initialize.
    # \param func 
    #
    def __init__(self: object, func: BoolEntity3DMappingFunctor) -> None: pass

    ##
    # \brief Initializes the \e %BoolEntity3DMappingFunctor instance.
    # \param arg1 The \e %BoolEntity3DMappingFunctor instance to initialize.
    # \param callable 
    #
    def __init__(arg1: object, callable: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %BoolEntity3DMappingFunctor instance this method is called upon.
    # \param arg1 
    # \return 
    #
    def __call__(self: BoolEntity3DMappingFunctor, arg1: Entity3DMapping) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BoolEntity3DMappingFunctor instance this method is called upon.
    # \return 
    #
    def __bool__(self: BoolEntity3DMappingFunctor) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BoolEntity3DMappingFunctor instance this method is called upon.
    # \return 
    #
    def __nonzero__(self: BoolEntity3DMappingFunctor) -> bool: pass
