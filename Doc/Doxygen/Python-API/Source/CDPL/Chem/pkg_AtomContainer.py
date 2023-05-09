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
class AtomContainer(Entity3DContainer):

    ##
    # \brief Initializes the \e %AtomContainer instance.
    #
    def __init__() -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getAtom(idx: int) -> Atom: pass

    ##
    # \brief 
    # \param atom 
    # \return 
    #
    def containsAtom(atom: Atom) -> bool: pass

    ##
    # \brief 
    # \param atom 
    # \return 
    #
    def getAtomIndex(atom: Atom) -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getNumAtoms() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def orderAtoms(func: CDPL.ForceField.InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getEntity(idx: int) -> Entity3D: pass

    ##
    # \brief 
    # \return 
    #
    def getNumEntities() -> int: pass

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
    numAtoms = property(getNumAtoms)
