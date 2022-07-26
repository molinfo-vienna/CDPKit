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
class AtomContainer(Entity3DContainer):

    ##
    # \brief Initializes the \e %AtomContainer instance.
    # \param self The \e %AtomContainer instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomContainer instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getAtom(self: AtomContainer, idx: int) -> Atom: pass

    ##
    # \brief 
    # \param self The \e %AtomContainer instance this method is called upon.
    # \param atom 
    # \return 
    #
    def containsAtom(self: AtomContainer, atom: Atom) -> bool: pass

    ##
    # \brief 
    # \param self The \e %AtomContainer instance this method is called upon.
    # \param atom 
    # \return 
    #
    def getAtomIndex(self: AtomContainer, atom: Atom) -> int: pass

    ##
    # \brief 
    # \param self The \e %AtomContainer instance this method is called upon.
    # \return 
    #
    def getNumAtoms(self: AtomContainer) -> int: pass

    ##
    # \brief 
    # \param self The \e %AtomContainer instance this method is called upon.
    # \param func 
    #
    def orderAtoms(self: AtomContainer, func: CDPL.ForceField.InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomContainer instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getEntity(self: AtomContainer, idx: int) -> Entity3D: pass

    ##
    # \brief 
    # \param self The \e %AtomContainer instance this method is called upon.
    # \return 
    #
    def getNumEntities(self: AtomContainer) -> int: pass

    ##
    # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
    # \param self The \e %AtomContainer instance this method is called upon.
    # \param atom The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: AtomContainer, atom: Atom) -> bool: pass

    ##
    # \brief 
    # \param self The \e %AtomContainer instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: AtomContainer, idx: int) -> Atom: pass

    ##
    # \brief 
    # \param self The \e %AtomContainer instance this method is called upon.
    # \return 
    #
    def __len__(self: AtomContainer) -> int: pass

    ##
    # \brief 
    #
    numAtoms = property(getNumAtoms)
