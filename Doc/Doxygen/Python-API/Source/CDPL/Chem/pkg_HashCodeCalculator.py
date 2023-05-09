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
class HashCodeCalculator(Boost.Python.instance):

    ##
    # \brief 
    #
    class DefAtomHashSeedFunctor(Boost.Python.instance):

        ##
        # \brief Initializes the \e %DefAtomHashSeedFunctor instance.
        # \param calculator 
        # \param flags 
        #
        def __init__(calculator: HashCodeCalculator, flags: int = 159) -> None: pass

        ##
        # \brief 
        # \param atom 
        # \return 
        #
        def __call__(atom: Atom) -> int: pass

    ##
    # \brief 
    #
    class DefBondHashSeedFunctor(Boost.Python.instance):

        ##
        # \brief Initializes the \e %DefBondHashSeedFunctor instance.
        # \param flags 
        #
        def __init__(flags: int = 15) -> None: pass

        ##
        # \brief 
        # \param bond 
        # \return 
        #
        def __call__(bond: Bond) -> int: pass

    ##
    # \brief 
    #
    DEF_ATOM_PROPERTY_FLAGS = 159

    ##
    # \brief 
    #
    DEF_BOND_PROPERTY_FLAGS = 15

    ##
    # \brief Initializes the \e %HashCodeCalculator instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %HashCodeCalculator instance.
    # \param molgraph 
    #
    def __init__(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %HashCodeCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %HashCodeCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def setAtomHashSeedFunction(func: SizeTypeAtomFunctor) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setBondHashSeedFunction(func: UInt64BondFunctor) -> None: pass

    ##
    # \brief 
    # \param include 
    #
    def includeGlobalStereoFeatures(include: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def globalStereoFeaturesIncluded() -> bool: pass

    ##
    # \brief 
    # \param molgraph 
    # \return 
    #
    def calculate(molgraph: MolecularGraph) -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getResult() -> int: pass

    ##
    # \brief 
    # \param molgraph 
    # \return 
    #
    def __call__(molgraph: MolecularGraph) -> int: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    result = property(getResult)

    ##
    # \brief FIXME!
    #
    globalStereoFeatures = property(getGlobalStereoFeatures, setGlobalStereoFeatures)
