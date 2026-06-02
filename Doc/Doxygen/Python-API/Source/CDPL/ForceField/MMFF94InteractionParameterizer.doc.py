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
# \brief One-stop MMFF94 parameterizer that combines atom typing, bond typing, partial-charge assignment and per-interaction-type parameter look-up into a single <tt>parameterize()</tt> call.
# 
# The constructor installs default parameter tables and atom-/bond-typing helpers for the selected ForceField.MMFF94ParameterSet variant (<tt>STATIC</tt>, <tt>DYNAMIC</tt>, etc.); every table, map and filter function can be overridden via the corresponding setter. Calling parameterize() runs atom typing, bond typing, formal/partial-charge assignment, aromaticity perception and topological-distance calculation, then dispatches to the seven per-interaction MMFF94*InteractionParameterizer members and stores the resulting interaction lists in the supplied ForceField.MMFF94InteractionData object.
# 
class MMFF94InteractionParameterizer(Boost.Python.instance):

    ##
    # \brief Constructs the parameterizer with the default tables for the chosen MMFF94 parameter set.
    # 
    # \param param_set The parameter-set variant (see namespace ForceField.MMFF94ParameterSet).
    # 
    def __init__(param_set: int = 1) -> None: pass

    ##
    # \brief Constructs a copy of the parameterizer <em>parameterizer</em>.
    # 
    # \param parameterizer The parameterizer to copy.
    # 
    def __init__(parameterizer: MMFF94InteractionParameterizer) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94InteractionParameterizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94InteractionParameterizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Installs a filter that decides whether a candidate bond-stretching interaction is kept.
    # 
    # \param func The filter functor (returns <tt>True</tt> to keep the interaction).
    # 
    def setBondStretchingFilterFunction(func: Chem.BoolAtom2Functor) -> None: pass

    ##
    # \brief Installs a filter that decides whether a candidate angle-bending interaction is kept.
    # 
    # \param func The filter functor (returns <tt>True</tt> to keep the interaction).
    # 
    def setAngleBendingFilterFunction(func: InteractionFilterFunction3) -> None: pass

    ##
    # \brief Installs a filter that decides whether a candidate stretch-bend interaction is kept.
    # 
    # \param func The filter functor (returns <tt>True</tt> to keep the interaction).
    # 
    def setStretchBendFilterFunction(func: InteractionFilterFunction3) -> None: pass

    ##
    # \brief Installs a filter that decides whether a candidate out-of-plane bending interaction is kept.
    # 
    # \param func The filter functor (returns <tt>True</tt> to keep the interaction).
    # 
    def setOutOfPlaneBendingFilterFunction(func: InteractionFilterFunction4) -> None: pass

    ##
    # \brief Installs a filter that decides whether a candidate torsion interaction is kept.
    # 
    # \param func The filter functor (returns <tt>True</tt> to keep the interaction).
    # 
    def setTorsionFilterFunction(func: InteractionFilterFunction4) -> None: pass

    ##
    # \brief Installs a filter that decides whether a candidate electrostatic interaction is kept.
    # 
    # \param func The filter functor (returns <tt>True</tt> to keep the interaction).
    # 
    def setElectrostaticFilterFunction(func: Chem.BoolAtom2Functor) -> None: pass

    ##
    # \brief Installs a filter that decides whether a candidate van-der-Waals interaction is kept.
    # 
    # \param func The filter functor (returns <tt>True</tt> to keep the interaction).
    # 
    def setVanDerWaalsFilterFunction(func: Chem.BoolAtom2Functor) -> None: pass

    ##
    # \brief Removes every previously installed interaction-filter function.
    # 
    def clearFilterFunctions() -> None: pass

    ##
    # \brief Sets the symbolic-atom-type pattern table to use during atom typing.
    # 
    # \param table The new symbolic-atom-type pattern table.
    # 
    def setSymbolicAtomTypePatternTable(table: MMFF94SymbolicAtomTypePatternTable) -> None: pass

    ##
    # \brief Sets the heavy-to-hydrogen atom-type map used to derive hydrogen atom types from their non-hydrogen neighbors.
    # 
    # \param map The new heavy-to-hydrogen atom-type map.
    # 
    def setHeavyToHydrogenAtomTypeMap(map: MMFF94HeavyToHydrogenAtomTypeMap) -> None: pass

    ##
    # \brief Sets the symbolic-to-numeric atom-type map used to convert symbolic types to numeric ones.
    # 
    # \param map The new symbolic-to-numeric atom-type map.
    # 
    def setSymbolicToNumericAtomTypeMap(map: MMFF94SymbolicToNumericAtomTypeMap) -> None: pass

    ##
    # \brief Sets the aromatic-atom-type definition table used to override types of aromatic atoms.
    # 
    # \param table The new aromatic-atom-type definition table.
    # 
    def setAromaticAtomTypeDefinitionTable(table: MMFF94AromaticAtomTypeDefinitionTable) -> None: pass

    ##
    # \brief Sets the atom-type property table used to resolve per-numeric-type properties.
    # 
    # \param table The new atom-type property table.
    # 
    def setAtomTypePropertyTable(table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief Sets the formal-atomic-charge definition table used during charge assignment.
    # 
    # \param table The new formal-atomic-charge definition table.
    # 
    def setFormalAtomChargeDefinitionTable(table: MMFF94FormalAtomChargeDefinitionTable) -> None: pass

    ##
    # \brief Sets the bond charge-increment table used during partial-charge calculation.
    # 
    # \param table The new bond-charge-increment table.
    # 
    def setBondChargeIncrementTable(table: MMFF94BondChargeIncrementTable) -> None: pass

    ##
    # \brief Sets the partial bond charge-increment table used during partial-charge calculation.
    # 
    # \param table The new partial-bond-charge-increment table.
    # 
    def setPartialBondChargeIncrementTable(table: MMFF94PartialBondChargeIncrementTable) -> None: pass

    ##
    # \brief Sets the primary-to-parameter atom-type map used by the parameter look-ups.
    # 
    # \param map The new primary-to-parameter atom-type map.
    # 
    def setPrimaryToParameterAtomTypeMap(map: MMFF94PrimaryToParameterAtomTypeMap) -> None: pass

    ##
    # \brief Sets the angle-bending parameter table to use.
    # 
    # \param table The new angle-bending parameter table.
    # 
    def setAngleBendingParameterTable(table: MMFF94AngleBendingParameterTable) -> None: pass

    ##
    # \brief Sets the bond-stretching parameter table to use.
    # 
    # \param table The new bond-stretching parameter table.
    # 
    def setBondStretchingParameterTable(table: MMFF94BondStretchingParameterTable) -> None: pass

    ##
    # \brief Sets the bond-stretching rule parameter table used as a fallback when no explicit bond-stretching entry is available.
    # 
    # \param table The new bond-stretching rule parameter table.
    # 
    def setBondStretchingRuleParameterTable(table: MMFF94BondStretchingRuleParameterTable) -> None: pass

    ##
    # \brief Sets the stretch-bend parameter table to use.
    # 
    # \param table The new stretch-bend parameter table.
    # 
    def setStretchBendParameterTable(table: MMFF94StretchBendParameterTable) -> None: pass

    ##
    # \brief Sets the default stretch-bend parameter table used as a periodic-row fallback.
    # 
    # \param table The new default stretch-bend parameter table.
    # 
    def setDefaultStretchBendParameterTable(table: MMFF94DefaultStretchBendParameterTable) -> None: pass

    ##
    # \brief Sets the out-of-plane bending parameter table to use.
    # 
    # \param table The new out-of-plane bending parameter table.
    # 
    def setOutOfPlaneBendingParameterTable(table: MMFF94OutOfPlaneBendingParameterTable) -> None: pass

    ##
    # \brief Sets the torsion parameter table to use.
    # 
    # \param table The new torsion parameter table.
    # 
    def setTorsionParameterTable(table: MMFF94TorsionParameterTable) -> None: pass

    ##
    # \brief Sets the van-der-Waals parameter table to use.
    # 
    # \param table The new van-der-Waals parameter table.
    # 
    def setVanDerWaalsParameterTable(table: MMFF94VanDerWaalsParameterTable) -> None: pass

    ##
    # \brief Sets the dielectric constant used by the electrostatic interaction parameterizer.
    # 
    # \param de_const The new dielectric constant.
    # 
    def setDielectricConstant(de_const: float) -> None: pass

    ##
    # \brief Sets the distance exponent used by the electrostatic interaction parameterizer.
    # 
    # \param dist_expo The new distance exponent.
    # 
    def setDistanceExponent(dist_expo: float) -> None: pass

    ##
    # \brief Switches the active MMFF94 parameter-set variant and reinstalls the matching default tables.
    # 
    # \param param_set The new parameter-set variant (see namespace ForceField.MMFF94ParameterSet).
    # 
    def setParameterSet(param_set: int) -> None: pass

    ##
    # \brief Copies the state of <em>parameterizer</em>.
    # 
    # \param parameterizer The parameterizer to copy.
    # 
    # \return \a self
    # 
    def assign(parameterizer: MMFF94InteractionParameterizer) -> MMFF94InteractionParameterizer: pass

    ##
    # \brief Parameterizes the MMFF94 force-field interactions for <em>molgraph</em> and stores them in <em>ia_data</em>.
    # 
    # \param molgraph The molecular graph to parameterize.
    # \param ia_data The output container receiving the perceived interactions.
    # \param ia_types A bitmask of ForceField.InteractionType flags selecting which interaction types are parameterized.
    # \param strict If <tt>True</tt>, the parameterization fails when any required parameter is missing; otherwise fallback strategies (rule-based parameters, default values) are used.
    # 
    def parameterize(molgraph: Chem.MolecularGraph, ia_data: MMFF94InteractionData, ia_types: int = 127, strict: bool = True) -> None: pass

    objectID = property(getObjectID)
