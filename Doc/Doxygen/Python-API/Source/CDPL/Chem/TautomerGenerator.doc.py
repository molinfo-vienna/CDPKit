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
# \brief TautomerGenerator.
# 
class TautomerGenerator(Boost.Python.instance):

    ##
    # \brief 
    #
    class Mode(Boost.Python.enum):

        ##
        # \brief TOPOLOGICALLY_UNIQUE.
        #
        TOPOLOGICALLY_UNIQUE = 0

        ##
        # \brief GEOMETRICALLY_UNIQUE.
        #
        GEOMETRICALLY_UNIQUE = 1

        ##
        # \brief EXHAUSTIVE.
        #
        EXHAUSTIVE = 2

    ##
    # \brief Constructs the <tt>TautomerGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %TautomerGenerator instance \a gen.
    # \param gen The \e %TautomerGenerator instance to copy.
    # 
    def __init__(gen: TautomerGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %TautomerGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %TautomerGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param rule 
    #
    def addTautomerizationRule(rule: TautomerizationRule) -> None: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeTautomerizationRule(idx: int) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getTautomerizationRule(idx: int) -> TautomerizationRule: pass

    ##
    # \brief 
    # \return 
    #
    def getNumTautomerizationRules() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def setCallbackFunction(func: BoolMolecularGraphFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getCallbackFunction() -> BoolMolecularGraphFunctor: pass

    ##
    # \brief 
    # \param mode 
    #
    def setMode(mode: Mode) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMode() -> Mode: pass

    ##
    # \brief 
    # \param regard 
    #
    def regardStereochemistry(regard: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def stereochemistryRegarded() -> bool: pass

    ##
    # \brief 
    # \param regard 
    #
    def regardIsotopes(regard: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isotopesRegarded() -> bool: pass

    ##
    # \brief 
    # \param remove 
    #
    def removeResonanceDuplicates(remove: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def resonanceDuplicatesRemoved() -> bool: pass

    ##
    # \brief 
    # \param func 
    #
    def setCustomSetupFunction(func: VoidMolecularGraphFunctor) -> None: pass

    ##
    # \brief Generates all unique tautomers of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to generate the tautomers.
    # 
    def generate(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %TautomerGenerator instance \a gen.
    # \param gen The \c %TautomerGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: TautomerGenerator) -> TautomerGenerator: pass

    objectID = property(getObjectID)

    callbackFunction = property(getCallbackFunction, setCallbackFunction)

    mode = property(getMode, setMode)

    regStereo = property(stereochemistryRegarded, regardStereochemistry)

    regIsotopes = property(isotopesRegarded, regardIsotopes)

    remResonanceDuplicates = property(resonanceDuplicatesRemoved, removeResonanceDuplicates)

    numTautomerizationRules = property(getNumTautomerizationRules)
