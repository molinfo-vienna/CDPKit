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
class MMFF94InteractionParameterizer(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94InteractionParameterizer instance.
    # \param self The \e %MMFF94InteractionParameterizer instance to initialize.
    # \param param_set 
    #
    def __init__(self: object, param_set: int = 1) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94InteractionParameterizer instance.
    # \param self The \e %MMFF94InteractionParameterizer instance to initialize.
    # \param parameterizer 
    #
    def __init__(self: object, parameterizer: MMFF94InteractionParameterizer) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    #
    # Different Python \e %MMFF94InteractionParameterizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94InteractionParameterizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: MMFF94InteractionParameterizer) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param func 
    #
    def setBondStretchingFilterFunction(self: MMFF94InteractionParameterizer, func: InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param func 
    #
    def setAngleBendingFilterFunction(self: MMFF94InteractionParameterizer, func: InteractionFilterFunction3) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param func 
    #
    def setStretchBendFilterFunction(self: MMFF94InteractionParameterizer, func: InteractionFilterFunction3) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param func 
    #
    def setOutOfPlaneBendingFilterFunction(self: MMFF94InteractionParameterizer, func: InteractionFilterFunction4) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param func 
    #
    def setTorsionFilterFunction(self: MMFF94InteractionParameterizer, func: InteractionFilterFunction4) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param func 
    #
    def setElectrostaticFilterFunction(self: MMFF94InteractionParameterizer, func: InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param func 
    #
    def setVanDerWaalsFilterFunction(self: MMFF94InteractionParameterizer, func: InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    #
    def clearFilterFunctions(self: MMFF94InteractionParameterizer) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setSymbolicAtomTypePatternTable(self: MMFF94InteractionParameterizer, table: MMFF94SymbolicAtomTypePatternTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param map 
    #
    def setHeavyToHydrogenAtomTypeMap(self: MMFF94InteractionParameterizer, map: MMFF94HeavyToHydrogenAtomTypeMap) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param map 
    #
    def setSymbolicToNumericAtomTypeMap(self: MMFF94InteractionParameterizer, map: MMFF94SymbolicToNumericAtomTypeMap) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setAromaticAtomTypeDefinitionTable(self: MMFF94InteractionParameterizer, table: MMFF94AromaticAtomTypeDefinitionTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setAtomTypePropertyTable(self: MMFF94InteractionParameterizer, table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setFormalAtomChargeDefinitionTable(self: MMFF94InteractionParameterizer, table: MMFF94FormalAtomChargeDefinitionTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setBondChargeIncrementTable(self: MMFF94InteractionParameterizer, table: MMFF94BondChargeIncrementTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setPartialBondChargeIncrementTable(self: MMFF94InteractionParameterizer, table: MMFF94PartialBondChargeIncrementTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param map 
    #
    def setPrimaryToParameterAtomTypeMap(self: MMFF94InteractionParameterizer, map: MMFF94PrimaryToParameterAtomTypeMap) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setAngleBendingParameterTable(self: MMFF94InteractionParameterizer, table: MMFF94AngleBendingParameterTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setBondStretchingParameterTable(self: MMFF94InteractionParameterizer, table: MMFF94BondStretchingParameterTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setBondStretchingRuleParameterTable(self: MMFF94InteractionParameterizer, table: MMFF94BondStretchingRuleParameterTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setStretchBendParameterTable(self: MMFF94InteractionParameterizer, table: MMFF94StretchBendParameterTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setDefaultStretchBendParameterTable(self: MMFF94InteractionParameterizer, table: MMFF94DefaultStretchBendParameterTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setOutOfPlaneBendingParameterTable(self: MMFF94InteractionParameterizer, table: MMFF94OutOfPlaneBendingParameterTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setTorsionParameterTable(self: MMFF94InteractionParameterizer, table: MMFF94TorsionParameterTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setVanDerWaalsParameterTable(self: MMFF94InteractionParameterizer, table: MMFF94VanDerWaalsParameterTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param de_const 
    #
    def setDielectricConstant(self: MMFF94InteractionParameterizer, de_const: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param dist_expo 
    #
    def setDistanceExponent(self: MMFF94InteractionParameterizer, dist_expo: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param param_set 
    #
    def setParameterSet(self: MMFF94InteractionParameterizer, param_set: int) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94InteractionParameterizer instance \a parameterizer.
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param parameterizer The \e %MMFF94InteractionParameterizer instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MMFF94InteractionParameterizer, parameterizer: MMFF94InteractionParameterizer) -> MMFF94InteractionParameterizer: pass

    ##
    # \brief 
    # \param self The \e %MMFF94InteractionParameterizer instance this method is called upon.
    # \param molgraph 
    # \param ia_data 
    # \param ia_types 
    # \param strict 
    #
    def parameterize(self: MMFF94InteractionParameterizer, molgraph: CDPL.Chem.MolecularGraph, ia_data: MMFF94InteractionData, ia_types: int = 127, strict: bool = True) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)
