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
class MMFF94InteractionParameterizer(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94InteractionParameterizer instance.
    # \param self The \e %MMFF94InteractionParameterizer instance to initialize.
    # \param param_set 
    # 
    def __init__(param_set: int = 1) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94InteractionParameterizer instance.
    # \param self The \e %MMFF94InteractionParameterizer instance to initialize.
    # \param parameterizer 
    # 
    def __init__(parameterizer: MMFF94InteractionParameterizer) -> None: pass

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
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def setBondStretchingFilterFunction(func: InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setAngleBendingFilterFunction(func: InteractionFilterFunction3) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setStretchBendFilterFunction(func: InteractionFilterFunction3) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setOutOfPlaneBendingFilterFunction(func: InteractionFilterFunction4) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setTorsionFilterFunction(func: InteractionFilterFunction4) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setElectrostaticFilterFunction(func: InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setVanDerWaalsFilterFunction(func: InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    #
    def clearFilterFunctions() -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setSymbolicAtomTypePatternTable(table: MMFF94SymbolicAtomTypePatternTable) -> None: pass

    ##
    # \brief 
    # \param map 
    #
    def setHeavyToHydrogenAtomTypeMap(map: MMFF94HeavyToHydrogenAtomTypeMap) -> None: pass

    ##
    # \brief 
    # \param map 
    #
    def setSymbolicToNumericAtomTypeMap(map: MMFF94SymbolicToNumericAtomTypeMap) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setAromaticAtomTypeDefinitionTable(table: MMFF94AromaticAtomTypeDefinitionTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setAtomTypePropertyTable(table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setFormalAtomChargeDefinitionTable(table: MMFF94FormalAtomChargeDefinitionTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setBondChargeIncrementTable(table: MMFF94BondChargeIncrementTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setPartialBondChargeIncrementTable(table: MMFF94PartialBondChargeIncrementTable) -> None: pass

    ##
    # \brief 
    # \param map 
    #
    def setPrimaryToParameterAtomTypeMap(map: MMFF94PrimaryToParameterAtomTypeMap) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setAngleBendingParameterTable(table: MMFF94AngleBendingParameterTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setBondStretchingParameterTable(table: MMFF94BondStretchingParameterTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setBondStretchingRuleParameterTable(table: MMFF94BondStretchingRuleParameterTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setStretchBendParameterTable(table: MMFF94StretchBendParameterTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setDefaultStretchBendParameterTable(table: MMFF94DefaultStretchBendParameterTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setOutOfPlaneBendingParameterTable(table: MMFF94OutOfPlaneBendingParameterTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setTorsionParameterTable(table: MMFF94TorsionParameterTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setVanDerWaalsParameterTable(table: MMFF94VanDerWaalsParameterTable) -> None: pass

    ##
    # \brief 
    # \param de_const 
    #
    def setDielectricConstant(de_const: float) -> None: pass

    ##
    # \brief 
    # \param dist_expo 
    #
    def setDistanceExponent(dist_expo: float) -> None: pass

    ##
    # \brief 
    # \param param_set 
    #
    def setParameterSet(param_set: int) -> None: pass

    ##
    # \brief 
    # \param parameterizer 
    # \return 
    #
    def assign(parameterizer: MMFF94InteractionParameterizer) -> MMFF94InteractionParameterizer: pass

    ##
    # \brief 
    # \param molgraph 
    # \param ia_data 
    # \param ia_types 
    # \param strict 
    #
    def parameterize(molgraph: CDPL.Chem.MolecularGraph, ia_data: MMFF94InteractionData, ia_types: int = 127, strict: bool = True) -> None: pass

    objectID = property(getObjectID)
