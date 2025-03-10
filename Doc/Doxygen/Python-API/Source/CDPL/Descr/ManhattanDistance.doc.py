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
# \brief Functor class for calculating the <em>Manhattan Distance</em> [\ref MADI] between bitsets and vectors.
# 
class ManhattanDistance(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ManhattanDistance instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %ManhattanDistance instance \a func.
    # \param func The \e %ManhattanDistance instance to copy.
    # 
    def __init__(func: ManhattanDistance) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %ManhattanDistance instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ManhattanDistance instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ManhattanDistance instance \a func.
    # \param func The \e %ManhattanDistance instance to copy.
    # \return \a self
    # 
    def assign(func: ManhattanDistance) -> ManhattanDistance: pass

    ##
    # \brief Calculates the <em>Manhattan Distance</em> [\ref MADI] between the vectors <em>v1</em> and <em>v2</em>.
    # 
    # The <em>Manhattan Distance</em> \f$ D_{12} \f$ is calculated by:
    # 
    # \[ D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}_1 \]
    # 
    # \param v1 The first vector.
    # \param v2 The second vector.
    # 
    # \return The calculated distance measure.
    # 
    def __call__(v1: Math.FVector, v2: Math.FVector) -> float: pass

    ##
    # \brief Calculates the <em>Manhattan Distance</em> [\ref MADI] between the vectors <em>v1</em> and <em>v2</em>.
    # 
    # The <em>Manhattan Distance</em> \f$ D_{12} \f$ is calculated by:
    # 
    # \[ D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}_1 \]
    # 
    # \param v1 The first vector.
    # \param v2 The second vector.
    # 
    # \return The calculated distance measure.
    # 
    def __call__(v1: Math.DVector, v2: Math.DVector) -> float: pass

    ##
    # \brief Calculates the <em>Manhattan Distance</em> [\ref MADI] between the vectors <em>v1</em> and <em>v2</em>.
    # 
    # The <em>Manhattan Distance</em> \f$ D_{12} \f$ is calculated by:
    # 
    # \[ D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}_1 \]
    # 
    # \param v1 The first vector.
    # \param v2 The second vector.
    # 
    # \return The calculated distance measure.
    # 
    def __call__(v1: Math.LVector, v2: Math.LVector) -> float: pass

    ##
    # \brief Calculates the <em>Manhattan Distance</em> [\ref MADI] between the vectors <em>v1</em> and <em>v2</em>.
    # 
    # The <em>Manhattan Distance</em> \f$ D_{12} \f$ is calculated by:
    # 
    # \[ D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}_1 \]
    # 
    # \param v1 The first vector.
    # \param v2 The second vector.
    # 
    # \return The calculated distance measure.
    # 
    def __call__(v1: Math.ULVector, v2: Math.ULVector) -> float: pass

    objectID = property(getObjectID)
