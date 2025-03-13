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
class MMFF94BondTyper(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94BondTyper instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %MMFF94BondTyper instance \a typer.
    # \param typer The \e %MMFF94BondTyper instance to copy.
    # 
    def __init__(typer: MMFF94BondTyper) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94BondTyper instance.
    # \param molgraph 
    # \param types 
    # \param strict 
    # 
    def __init__(molgraph: Chem.MolecularGraph, types: Util.UIArray, strict: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94BondTyper instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94BondTyper instances \e a and \e b reference different C++ objects. 
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
    def setAtomTypeFunction(func: MMFF94NumericAtomTypeFunction) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setAromaticRingSetFunction(func: MMFF94RingSetFunction) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setAtomTypePropertyTable(table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94BondTyper instance \a typer.
    # \param typer The \c %MMFF94BondTyper instance to copy.
    # \return \a self
    # 
    def assign(typer: MMFF94BondTyper) -> MMFF94BondTyper: pass

    ##
    # \brief Determines MMFF94 bond type indicies for the bonds of a molecular graph.
    # 
    # Specifically, an nonstandard bond type index of <em>"1"</em> is assigned whenever a single bond (formal bond order 1) is found a) between non-aromatic atoms <em>i</em> and <em>j</em> of types <em>I</em> and <em>J</em> for which <em>"sbmb"</em> entries in of <em>"1"</em> appear in the "MMFFPROP.PAR" file or b) between aromatic atoms belonging to different aromatic rings (as in the case of the central C-C bond in biphenyl).
    # 
    # \param molgraph The molecular graph for which to assign bond type indices
    # \param types The output array storing the determined bond type indices.
    # \param strict If <tt>True</tt>, strict parameterization will be peformed that might fail.
    # 
    def perceiveTypes(molgraph: Chem.MolecularGraph, types: Util.UIArray, strict: bool) -> None: pass

    objectID = property(getObjectID)
