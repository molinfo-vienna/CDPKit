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
# \brief Assigns MMFF94 symbolic and numeric atom types to the atoms of a molecular graph.
# 
# Typing is performed in four stages: provisional symbolic types are assigned by SMARTS pattern matching, aromatic atom types are then reassigned according to the MMFF94 aromatic-ring rules, hydrogen atoms receive types derived from their heavy-atom neighbors, and finally the symbolic types are translated to the corresponding numeric type indices used by the rest of the MMFF94 parameter tables.
# 
class MMFF94AtomTyper(Boost.Python.instance):

    ##
    # \brief Constructs an empty <tt>MMFF94AtomTyper</tt> instance using the default MMFF94 parameter tables.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94AtomTyper instance \a typer.
    # \param typer The \c %MMFF94AtomTyper instance to copy.
    # 
    def __init__(typer: MMFF94AtomTyper) -> None: pass

    ##
    # \brief Constructs an <tt>MMFF94AtomTyper</tt> instance and immediately perceives the atom types of <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph to be typed.
    # \param sym_types Output array receiving the perceived MMFF94 symbolic atom type strings.
    # \param num_types Output array receiving the perceived MMFF94 numeric atom type indices.
    # \param strict If <tt>True</tt>, atoms for which no MMFF94 type could be perceived cause an error to be reported. Otherwise, perception never fails and problematic atoms get assigned a suitable fallback type.
    # 
    def __init__(molgraph: Chem.MolecularGraph, sym_types: Util.SArray, num_types: Util.UIArray, strict: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94AtomTyper instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94AtomTyper instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Sets the SMARTS-pattern table used for provisional symbolic atom type assignment.
    # 
    # \param table The new symbolic atom type pattern table.
    # 
    def setSymbolicAtomTypePatternTable(table: MMFF94SymbolicAtomTypePatternTable) -> None: pass

    ##
    # \brief Sets the table used for the reassignment of aromatic atom types.
    # 
    # \param table The new aromatic atom type definition table.
    # 
    def setAromaticAtomTypeDefinitionTable(table: MMFF94AromaticAtomTypeDefinitionTable) -> None: pass

    ##
    # \brief Sets the map used to derive hydrogen atom types from heavy-atom neighbor types.
    # 
    # \param map The new heavy-to-hydrogen atom type map.
    # 
    def setHeavyToHydrogenAtomTypeMap(map: MMFF94HeavyToHydrogenAtomTypeMap) -> None: pass

    ##
    # \brief Sets the map used to translate symbolic into numeric atom types.
    # 
    # \param map The new symbolic-to-numeric atom type map.
    # 
    def setSymbolicToNumericAtomTypeMap(map: MMFF94SymbolicToNumericAtomTypeMap) -> None: pass

    ##
    # \brief Sets the table providing the per-numeric-type atom property data.
    # 
    # \param table The new atom type property table.
    # 
    def setAtomTypePropertyTable(table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief Sets the function used to obtain the set of MMFF94 aromatic rings for the input molecular graph.
    # 
    # \param func The new aromatic ring set retrieval function.
    # 
    def setAromaticRingSetFunction(func: MMFF94RingSetFunction) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94AtomTyper instance \a typer.
    # \param typer The \c %MMFF94AtomTyper instance to copy.
    # \return \a self
    # 
    def assign(typer: MMFF94AtomTyper) -> MMFF94AtomTyper: pass

    ##
    # \brief Perceives the MMFF94 atom types of <em>molgraph</em> and writes them to <em>sym_types</em> and <em>num_types</em>.
    # 
    # \param molgraph The molecular graph to be typed.
    # \param sym_types Output array receiving the perceived MMFF94 symbolic atom type strings.
    # \param num_types Output array receiving the perceived MMFF94 numeric atom type indices.
    # \param strict If <tt>True</tt>, atoms for which no MMFF94 type could be perceived cause an error to be reported. Otherwise, perception never fails and problematic atoms get assigned a suitable fallback type.
    # 
    def perceiveTypes(molgraph: Chem.MolecularGraph, sym_types: Util.SArray, num_types: Util.UIArray, strict: bool) -> None: pass

    objectID = property(getObjectID)
