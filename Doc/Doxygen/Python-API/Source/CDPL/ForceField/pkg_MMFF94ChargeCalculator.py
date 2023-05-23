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
class MMFF94ChargeCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94ChargeCalculator instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MMFF94ChargeCalculator instance.
    # \param calc 
    #
    def __init__(calc: MMFF94ChargeCalculator) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94ChargeCalculator instance.
    # \param molgraph 
    # \param charges 
    # \param strict 
    #
    def __init__(molgraph: CDPL.Chem.MolecularGraph, charges: CDPL.Util.DArray, strict: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %MMFF94ChargeCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94ChargeCalculator instances \e a and \e b reference different C++ objects. 
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
    def setAromaticRingSetFunction(func: MMFF94RingSetFunction) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setNumericAtomTypeFunction(func: MMFF94NumericAtomTypeFunction) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setSymbolicAtomTypeFunction(func: MMFF94SymbolicAtomTypeFunction) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setBondTypeIndexFunction(func: MMFF94BondTypeIndexFunction) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setAtomTypePropertyTable(table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setFormalChargeDefinitionTable(table: MMFF94FormalAtomChargeDefinitionTable) -> None: pass

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
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94ChargeCalculator instance \a parameterizer.
    # \param parameterizer The \e %MMFF94ChargeCalculator instance to copy.
    # \return \a self
    #
    def assign(parameterizer: MMFF94ChargeCalculator) -> MMFF94ChargeCalculator: pass

    ##
    # \brief 
    # \param molgraph 
    # \param charges 
    # \param strict 
    #
    def calculate(molgraph: CDPL.Chem.MolecularGraph, charges: CDPL.Util.DArray, strict: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFormalCharges() -> CDPL.Util.DArray: pass

    ##
    # \brief 
    # \param arg1 
    # \return 
    #
    def formalCharges() -> CDPL.Util.DArray: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)
