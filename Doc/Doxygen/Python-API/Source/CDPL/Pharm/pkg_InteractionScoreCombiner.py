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
class InteractionScoreCombiner(Boost.Python.instance):

    ##
    # \brief Initializes the \e %InteractionScoreCombiner instance.
    # \param self The \e %InteractionScoreCombiner instance to initialize.
    # \param comb 
    #
    def __init__(self: object, comb: InteractionScoreCombiner) -> None: pass

    ##
    # \brief Initializes the \e %InteractionScoreCombiner instance.
    # \param self The \e %InteractionScoreCombiner instance to initialize.
    # \param func1 
    # \param func2 
    # \param comb_func 
    #
    def __init__(self: object, func1: DoubleVector3DFeatureFunctor, func2: DoubleVector3DFeatureFunctor, comb_func: DoubleDouble2Functor) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %InteractionScoreCombiner instance this method is called upon.
    #
    # Different Python \e %InteractionScoreCombiner instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %InteractionScoreCombiner instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: InteractionScoreCombiner) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %InteractionScoreCombiner instance \a con.
    # \param self The \e %InteractionScoreCombiner instance this method is called upon.
    # \param con The \e %InteractionScoreCombiner instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: InteractionScoreCombiner, con: InteractionScoreCombiner) -> InteractionScoreCombiner: pass

    ##
    # \brief 
    # \param self The \e %InteractionScoreCombiner instance this method is called upon.
    # \param ftr1_pos 
    # \param ftr2 
    # \return 
    #
    def __call__(self: InteractionScoreCombiner, ftr1_pos: CDPL.Math.Vector3D, ftr2: Feature) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)
