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
class ElectronSystem(AtomContainer):

    ##
    # \brief Initializes the \e %ElectronSystem instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %ElectronSystem instance.
    # \param elec_sys 
    #
    def __init__(elec_sys: ElectronSystem) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %ElectronSystem instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ElectronSystem instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ElectronSystem instance \a elec_sys.
    # \param elec_sys The \e %ElectronSystem instance to copy.
    # \return \a self
    #
    def assign(elec_sys: ElectronSystem) -> ElectronSystem: pass

    ##
    # \brief 
    # \param atom 
    # \param elec_contrib 
    # \return 
    #
    def addAtom(atom: Atom, elec_contrib: int) -> bool: pass

    ##
    # \brief 
    # \param elec_sys 
    # \return 
    #
    def addAtoms(elec_sys: ElectronSystem) -> bool: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeAtom(idx: int) -> None: pass

    ##
    # \brief 
    # \param atom 
    # \return 
    #
    def removeAtom(atom: Atom) -> bool: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \param elec_sys 
    #
    def swap(elec_sys: ElectronSystem) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumElectrons() -> int: pass

    ##
    # \brief 
    # \param atom 
    # \return 
    #
    def getElectronContrib(atom: Atom) -> int: pass

    ##
    # \brief 
    # \param atom 
    # \return 
    #
    def getElectronContrib(atom: int) -> int: pass

    ##
    # \brief 
    # \param atom 
    # \param elec_contrib 
    #
    def setElectronContrib(atom: Atom, elec_contrib: int) -> None: pass

    ##
    # \brief 
    # \param atom 
    # \param elec_contrib 
    #
    def setElectronContrib(atom: int, elec_contrib: int) -> None: pass

    ##
    # \brief 
    # \param elec_sys 
    #
    def merge(elec_sys: ElectronSystem) -> None: pass

    ##
    # \brief 
    # \param elec_sys 
    # \return 
    #
    def overlaps(elec_sys: ElectronSystem) -> bool: pass

    ##
    # \brief 
    # \param elec_sys 
    # \return 
    #
    def contains(elec_sys: ElectronSystem) -> bool: pass

    ##
    # \brief 
    # \param elec_sys 
    # \param bonds 
    # \return 
    #
    def connected(elec_sys: ElectronSystem, bonds: BondContainer) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
    # \param atom The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(atom: Atom) -> bool: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> Atom: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numElectrons = property(getNumElectrons)
