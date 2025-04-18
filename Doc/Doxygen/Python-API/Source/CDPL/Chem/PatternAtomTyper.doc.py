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
# \brief PatternAtomTyper.
# 
class PatternAtomTyper(Boost.Python.instance):

    ##
    # \brief 
    #
    class Pattern(Boost.Python.instance):

        ##
        # \brief Initializes a copy of the \e %Pattern instance \a pattern.
        # \param pattern The \e %Pattern instance to copy.
        # 
        def __init__(pattern: Pattern) -> None: pass

        ##
        # \brief Initializes the \e %Pattern instance.
        # \param molgraph 
        # \param atom_label 
        # \param priority 
        # \param all_matches 
        # \param unique_matches 
        # 
        def __init__(molgraph: MolecularGraph, atom_label: int = 0, priority: int = 0, all_matches: bool = True, unique_matches: bool = False) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %Pattern instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %Pattern instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %Pattern instance \a pattern.
        # \param pattern The \c %Pattern instance to copy.
        # \return \a self
        # 
        def assign(pattern: Pattern) -> Pattern: pass

        ##
        # \brief 
        # \return 
        #
        def getStructure() -> MolecularGraph: pass

        ##
        # \brief 
        # \return 
        #
        def getPriority() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getAtomLabel() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def processAllMatches() -> bool: pass

        ##
        # \brief 
        # \return 
        #
        def processUniqueMatchesOnly() -> bool: pass

        objectID = property(getObjectID)

        structure = property(getStructure)

        priority = property(getPriority)

        atomLabel = property(getAtomLabel)

        allMatches = property(processAllMatches)

        uniqueMatches = property(processUniqueMatchesOnly)

    ##
    # \brief Initializes the \e %PatternAtomTyper instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %PatternAtomTyper instance \a typer.
    # \param typer The \e %PatternAtomTyper instance to copy.
    # 
    def __init__(typer: PatternAtomTyper) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %PatternAtomTyper instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %PatternAtomTyper instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param molgraph 
    # \param atom_label 
    # \param priority 
    # \param all_matches 
    # \param unique_matches 
    #
    def addPattern(molgraph: MolecularGraph, atom_label: int = 0, priority: int = 0, all_matches: bool = True, unique_matches: bool = False) -> None: pass

    ##
    # \brief 
    # \param pattern 
    #
    def addPattern(pattern: Pattern) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getPattern(idx: int) -> Pattern: pass

    ##
    # \brief 
    # \param idx 
    #
    def removePattern(idx: int) -> None: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumPatterns() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getAtomLabel(idx: int) -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getPatternIndex(idx: int) -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def hasAtomLabel(idx: int) -> bool: pass

    ##
    # \brief 
    # \param molgraph 
    #
    def execute(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %PatternAtomTyper instance \a typer.
    # \param typer The \c %PatternAtomTyper instance to copy.
    # \return \a self
    # 
    def assign(typer: PatternAtomTyper) -> PatternAtomTyper: pass

    objectID = property(getObjectID)

    numPatterns = property(getNumPatterns)
