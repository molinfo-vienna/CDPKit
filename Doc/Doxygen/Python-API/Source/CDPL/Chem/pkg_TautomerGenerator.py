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
    # \brief Initializes the \e %TautomerGenerator instance.
    # \param self The \e %TautomerGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %TautomerGenerator instance.
    # \param self The \e %TautomerGenerator instance to initialize.
    # \param gen 
    #
    def __init__(self: object, gen: TautomerGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %TautomerGenerator instance this method is called upon.
    #
    # Different Python \e %TautomerGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %TautomerGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: TautomerGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \param rule 
    #
    def addTautomerizationRule(self: TautomerGenerator, rule: TautomerizationRule) -> None: pass

    ##
    # \brief 
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \param idx 
    #
    def removeTautomerizationRule(self: TautomerGenerator, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getTautomerizationRule(self: TautomerGenerator, idx: int) -> TautomerizationRule: pass

    ##
    # \brief 
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \return 
    #
    def getNumTautomerizationRules(self: TautomerGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \param func 
    #
    def setCallbackFunction(self: TautomerGenerator, func: BoolMolecularGraphFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \return 
    #
    def getCallbackFunction(self: TautomerGenerator) -> BoolMolecularGraphFunctor: pass

    ##
    # \brief 
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \param mode 
    #
    def setMode(self: TautomerGenerator, mode: Mode) -> None: pass

    ##
    # \brief 
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \return 
    #
    def getMode(self: TautomerGenerator) -> Mode: pass

    ##
    # \brief 
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \param regard 
    #
    def regardStereochemistry(self: TautomerGenerator, regard: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \return 
    #
    def stereochemistryRegarded(self: TautomerGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \param regard 
    #
    def regardIsotopes(self: TautomerGenerator, regard: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \return 
    #
    def isotopesRegarded(self: TautomerGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \param func 
    #
    def setCustomSetupFunction(self: TautomerGenerator, func: VoidMolecularGraphFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \param molgraph 
    #
    def generate(self: TautomerGenerator, molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %TautomerGenerator instance \a gen.
    # \param self The \e %TautomerGenerator instance this method is called upon.
    # \param gen The \e %TautomerGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: TautomerGenerator, gen: TautomerGenerator) -> TautomerGenerator: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    callbackFunction = property(getCallbackFunction, setCallbackFunction)

    ##
    # \brief 
    #
    mode = property(getMode, setMode)

    ##
    # \brief FIXME!
    #
    regStereo = property(getRegStereo, setRegStereo)

    ##
    # \brief FIXME!
    #
    regIsotopes = property(getRegIsotopes, setRegIsotopes)

    ##
    # \brief 
    #
    numTautomerizationRules = property(getNumTautomerizationRules)
