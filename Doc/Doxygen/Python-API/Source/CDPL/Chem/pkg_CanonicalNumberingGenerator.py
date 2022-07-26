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
class CanonicalNumberingGenerator(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_ATOM_PROPERTY_FLAGS = 414

    ##
    # \brief 
    #
    DEF_BOND_PROPERTY_FLAGS = 26

    ##
    # \brief Initializes the \e %CanonicalNumberingGenerator instance.
    # \param self The \e %CanonicalNumberingGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %CanonicalNumberingGenerator instance.
    # \param self The \e %CanonicalNumberingGenerator instance to initialize.
    # \param molgraph 
    # \param numbering 
    #
    def __init__(self: object, molgraph: MolecularGraph, numbering: CDPL.Util.STArray) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %CanonicalNumberingGenerator instance this method is called upon.
    #
    # Different Python \e %CanonicalNumberingGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %CanonicalNumberingGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: CanonicalNumberingGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %CanonicalNumberingGenerator instance this method is called upon.
    # \param flags 
    #
    def setAtomPropertyFlags(self: CanonicalNumberingGenerator, flags: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %CanonicalNumberingGenerator instance this method is called upon.
    # \return 
    #
    def getAtomPropertyFlags(self: CanonicalNumberingGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %CanonicalNumberingGenerator instance this method is called upon.
    # \param flags 
    #
    def setBondPropertyFlags(self: CanonicalNumberingGenerator, flags: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %CanonicalNumberingGenerator instance this method is called upon.
    # \return 
    #
    def getBondPropertyFlags(self: CanonicalNumberingGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %CanonicalNumberingGenerator instance this method is called upon.
    # \param func 
    #
    def setHydrogenCountFunction(self: CanonicalNumberingGenerator, func: SizeTypeAtomMolecularGraphFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %CanonicalNumberingGenerator instance this method is called upon.
    # \return 
    #
    def getHydrogenCountFunction(self: CanonicalNumberingGenerator) -> SizeTypeAtomMolecularGraphFunctor: pass

    ##
    # \brief 
    # \param self The \e %CanonicalNumberingGenerator instance this method is called upon.
    # \param molgraph 
    # \param numbering 
    #
    def generate(self: CanonicalNumberingGenerator, molgraph: MolecularGraph, numbering: CDPL.Util.STArray) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    atomPropertyFlags = property(getAtomPropertyFlags, setAtomPropertyFlags)

    ##
    # \brief 
    #
    bondPropertyFlags = property(getBondPropertyFlags, setBondPropertyFlags)

    ##
    # \brief FIXME!
    #
    hydrogenCountFunc = property(getHydrogenCountFunc, setHydrogenCountFunc)
