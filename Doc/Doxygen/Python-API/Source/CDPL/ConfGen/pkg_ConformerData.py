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
class ConformerData(Math.Vector3DArray):

    ##
    # \brief Initializes the \e %ConformerData instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %ConformerData instance.
    # \param data 
    # 
    def __init__(data: ConformerData) -> None: pass

    ##
    # \brief Initializes the \e %ConformerData instance.
    # \param coords 
    # \param energy 
    # 
    def __init__(coords: Math.Vector3DArray, energy: float = 0.0) -> None: pass

    ##
    # \brief 
    # \param data 
    #
    def swap(data: ConformerData) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ConformerData instance \a data.
    # \param data The \e %ConformerData instance to copy.
    # \return \a self
    # 
    def assign(data: ConformerData) -> ConformerData: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Vector3DArray instance \a coords.
    # \param coords The \e %Vector3DArray instance to copy.
    # \return \a self
    # 
    def assign(coords: Math.Vector3DArray) -> ConformerData: pass

    ##
    # \brief 
    # \return 
    #
    def getEnergy() -> float: pass

    ##
    # \brief 
    # \param energy 
    #
    def setEnergy(energy: float) -> None: pass

    energy = property(getEnergy, setEnergy)
