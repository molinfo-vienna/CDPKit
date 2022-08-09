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
class StereoDescriptor(Boost.Python.instance):

    ##
    # \brief 
    #
    class ReferenceAtomArray(Boost.Python.instance):

        ##
        # \brief 
        # \return 
        #
        def __len__() -> int: pass

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
    # \brief Initializes the \e %StereoDescriptor instance.
    # \param config 
    #
    def __init__(config: int) -> None: pass

    ##
    # \brief Initializes the \e %StereoDescriptor instance.
    # \param descr 
    #
    def __init__(descr: StereoDescriptor) -> None: pass

    ##
    # \brief Initializes the \e %StereoDescriptor instance.
    # \param config 
    # \param atom1 
    # \param atom2 
    # \param atom3 
    #
    def __init__(config: int, atom1: Atom, atom2: Atom, atom3: Atom) -> None: pass

    ##
    # \brief Initializes the \e %StereoDescriptor instance.
    # \param config 
    # \param atom1 
    # \param atom2 
    # \param atom3 
    # \param atom4 
    #
    def __init__(config: int, atom1: Atom, atom2: Atom, atom3: Atom, atom4: Atom) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getConfiguration() -> int: pass

    ##
    # \brief 
    # \param config 
    #
    def setConfiguration(config: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumReferenceAtoms() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getReferenceAtoms() -> ReferenceAtomArray: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %StereoDescriptor instance \a descr.
    # \param descr The \e %StereoDescriptor instance to copy.
    # \return The assignment target \a self.
    #
    def assign(descr: StereoDescriptor) -> StereoDescriptor: pass

    ##
    # \brief 
    # \param atom1 
    # \param atom2 
    # \param atom3 
    # \param atom4 
    # \return 
    #
    def getPermutationParity(atom1: Atom, atom2: Atom, atom3: Atom, atom4: Atom) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %StereoDescriptor instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %StereoDescriptor instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param atom 
    # \return 
    #
    def isValid(atom: Atom) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %StereoDescriptor instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    configuration = property(getConfiguration, setConfiguration)

    ##
    # \brief 
    #
    numReferenceAtoms = property(getNumReferenceAtoms)

    ##
    # \brief 
    #
    referenceAtoms = property(getReferenceAtoms)