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
# \brief Container for the 3D coordinates of a generated conformer plus its associated energy value.
# 
# <tt>ConformerData</tt> extends Math.Vector3DArray with an energy field that is filled by force-field-based conformer-generation steps.
# 
class ConformerData(Math.Vector3DArray):

    ##
    # \brief Constructs an empty <tt>ConformerData</tt> instance with zero energy.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %ConformerData instance \a data.
    # \param data The \c %ConformerData instance to copy.
    # 
    def __init__(data: ConformerData) -> None: pass

    ##
    # \brief Constructs the <tt>ConformerData</tt> instance with the given coordinates and energy.
    # 
    # \param coords The 3D coordinate vectors of the conformer.
    # \param energy The energy value to assign.
    # 
    def __init__(coords: Math.Vector3DArray, energy: float = 0.0) -> None: pass

    ##
    # \brief Swaps the contents (coordinates and energy) of this instance with <em>data</em>.
    # 
    # \param data The other <tt>ConformerData</tt> instance.
    # 
    def swap(data: ConformerData) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ConformerData instance \a data.
    # \param data The \c %ConformerData instance to copy.
    # \return \a self
    # 
    def assign(data: ConformerData) -> ConformerData: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %Vector3DArray instance \a coords.
    # \param coords The \c %Vector3DArray instance to copy.
    # \return \a self
    # 
    def assign(coords: Math.Vector3DArray) -> ConformerData: pass

    ##
    # \brief Returns the energy value.
    # 
    # \return The currently stored energy value.
    # 
    def getEnergy() -> float: pass

    ##
    # \brief Sets the energy value.
    # 
    # \param energy The new energy value.
    # 
    def setEnergy(energy: float) -> None: pass

    energy = property(getEnergy, setEnergy)
