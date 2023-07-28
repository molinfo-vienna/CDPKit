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
class MMFF94AtomTyper(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94AtomTyper instance.
    # \param self The \e %MMFF94AtomTyper instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MMFF94AtomTyper instance.
    # \param self The \e %MMFF94AtomTyper instance to initialize.
    # \param typer 
    # 
    def __init__(typer: MMFF94AtomTyper) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94AtomTyper instance.
    # \param self The \e %MMFF94AtomTyper instance to initialize.
    # \param molgraph 
    # \param sym_types 
    # \param num_types 
    # \param strict 
    # 
    def __init__(molgraph: CDPL.Chem.MolecularGraph, sym_types: CDPL.Util.SArray, num_types: CDPL.Util.UIArray, strict: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94AtomTyper instance this method is called upon.
    # 
    # Different Python \e %MMFF94AtomTyper instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94AtomTyper instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param table 
    #
    def setSymbolicAtomTypePatternTable(table: MMFF94SymbolicAtomTypePatternTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setAromaticAtomTypeDefinitionTable(table: MMFF94AromaticAtomTypeDefinitionTable) -> None: pass

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
    def setAtomTypePropertyTable(table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setAromaticRingSetFunction(func: MMFF94RingSetFunction) -> None: pass

    ##
    # \brief 
    # \param typer 
    # \return 
    #
    def assign(typer: MMFF94AtomTyper) -> MMFF94AtomTyper: pass

    ##
    # \brief 
    # \param molgraph 
    # \param sym_types 
    # \param num_types 
    # \param strict 
    #
    def perceiveTypes(molgraph: CDPL.Chem.MolecularGraph, sym_types: CDPL.Util.SArray, num_types: CDPL.Util.UIArray, strict: bool) -> None: pass

    objectID = property(getObjectID)
