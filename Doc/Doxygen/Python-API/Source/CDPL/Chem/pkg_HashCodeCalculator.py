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
class HashCodeCalculator(Boost.Python.instance):

    ##
    # \brief 
    #
    class DefAtomHashSeedFunctor(Boost.Python.instance):

        ##
        # \brief Initializes the \e %DefAtomHashSeedFunctor instance.
        # \param self The \e %DefAtomHashSeedFunctor instance to initialize.
        # \param calculator 
        # \param flags 
        #
        def __init__(self: object, calculator: HashCodeCalculator, flags: int = 159) -> None: pass

        ##
        # \brief 
        # \param self The \e %DefAtomHashSeedFunctor instance this method is called upon.
        # \param atom 
        # \return 
        #
        def __call__(self: DefAtomHashSeedFunctor, atom: Atom) -> int: pass

    ##
    # \brief 
    #
    class DefBondHashSeedFunctor(Boost.Python.instance):

        ##
        # \brief Initializes the \e %DefBondHashSeedFunctor instance.
        # \param self The \e %DefBondHashSeedFunctor instance to initialize.
        # \param calculator 
        # \param flags 
        #
        def __init__(self: object, calculator: HashCodeCalculator, flags: int = 15) -> None: pass

        ##
        # \brief 
        # \param self The \e %DefBondHashSeedFunctor instance this method is called upon.
        # \param bond 
        # \return 
        #
        def __call__(self: DefBondHashSeedFunctor, bond: Bond) -> int: pass

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
    # \param self The \e %HashCodeCalculator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %HashCodeCalculator instance.
    # \param self The \e %HashCodeCalculator instance to initialize.
    # \param molgraph 
    #
    def __init__(self: object, molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %HashCodeCalculator instance this method is called upon.
    #
    # Different Python \e %HashCodeCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %HashCodeCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: HashCodeCalculator) -> int: pass

    ##
    # \brief 
    # \param self The \e %HashCodeCalculator instance this method is called upon.
    # \param func 
    #
    def setAtomHashSeedFunction(self: HashCodeCalculator, func: SizeTypeAtomFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %HashCodeCalculator instance this method is called upon.
    # \param func 
    #
    def setBondHashSeedFunction(self: HashCodeCalculator, func: UInt64BondFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %HashCodeCalculator instance this method is called upon.
    # \param include 
    #
    def includeGlobalStereoFeatures(self: HashCodeCalculator, include: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %HashCodeCalculator instance this method is called upon.
    # \return 
    #
    def globalStereoFeaturesIncluded(self: HashCodeCalculator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %HashCodeCalculator instance this method is called upon.
    # \param molgraph 
    # \return 
    #
    def calculate(self: HashCodeCalculator, molgraph: MolecularGraph) -> int: pass

    ##
    # \brief 
    # \param self The \e %HashCodeCalculator instance this method is called upon.
    # \return 
    #
    def getResult(self: HashCodeCalculator) -> int: pass

    ##
    # \brief 
    # \param self The \e %HashCodeCalculator instance this method is called upon.
    # \param molgraph 
    # \return 
    #
    def __call__(self: HashCodeCalculator, molgraph: MolecularGraph) -> int: pass

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
