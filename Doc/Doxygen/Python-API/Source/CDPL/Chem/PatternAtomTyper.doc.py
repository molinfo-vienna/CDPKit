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
# \brief Assigns numeric labels to specific atoms of a molecular graph that are described by substructure patterns.
# 
# Patterns are added via addPattern() (each pattern carries a query molecular graph, an atom-label value, a priority and match-handling flags). On execute() the typer iterates the registered patterns in priority order, runs each as a substructure query and assigns the corresponding atom label to every matched atom unless the atom has already received a label from a pattern with higher priority.
# 
class PatternAtomTyper(Boost.Python.instance):

    ##
    # \brief Stores a single substructure query molecular graph, its atom label value, its priority and match-handling flags.
    # 
    class Pattern(Boost.Python.instance):

        ##
        # \brief Initializes a copy of the \c %Pattern instance \a pattern.
        # \param pattern The \c %Pattern instance to copy.
        # 
        def __init__(pattern: Pattern) -> None: pass

        ##
        # \brief Constructs a <tt>Pattern</tt> instance for the specified values.
        # 
        # \param molgraph The query molecular graph.
        # \param atom_label The atom label to assign to atoms matching this pattern.
        # \param priority The priority of this pattern (higher-priority patterns are evaluated first).
        # \param all_matches If <tt>True</tt>, every match of <em>molgraph</em> in the target is processed. If <tt>False</tt>, only the first match is processed.
        # \param unique_matches If <tt>True</tt>, only one of multiple equivalent substructure mappings is reported per match.
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
        # \brief Returns the query molecular graph of this pattern.
        # 
        # \return A shared reference to the query molecular graph.
        # 
        def getStructure() -> MolecularGraph: pass

        ##
        # \brief Returns the pattern priority.
        # 
        # \return The priority value.
        # 
        def getPriority() -> int: pass

        ##
        # \brief Returns the atom label assigned by this pattern.
        # 
        # \return The atom-label value.
        # 
        def getAtomLabel() -> int: pass

        ##
        # \brief Tells whether all substructure matches are processed.
        # 
        # \return <tt>True</tt> if all matches are processed, and <tt>False</tt> if only the first match is.
        # 
        def processAllMatches() -> bool: pass

        ##
        # \brief Tells whether only one of multiple equivalent mappings is processed per match.
        # 
        # \return <tt>True</tt> if unique-only mode is enabled, and <tt>False</tt> otherwise.
        # 
        def processUniqueMatchesOnly() -> bool: pass

        objectID = property(getObjectID)

        structure = property(getStructure)

        priority = property(getPriority)

        atomLabel = property(getAtomLabel)

        allMatches = property(processAllMatches)

        uniqueMatches = property(processUniqueMatchesOnly)

    ##
    # \brief Constructs an empty <tt>PatternAtomTyper</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>PatternAtomTyper</tt> instance <em>typer</em>.
    # 
    # \param typer The <tt>PatternAtomTyper</tt> to copy.
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
    # \brief Registers a new pattern by its query molecular graph and per-pattern settings.
    # 
    # \param molgraph The query molecular graph.
    # \param atom_label The atom label to assign to matched atoms.
    # \param priority The pattern's priority (higher priority patterns are evaluated first).
    # \param all_matches If <tt>True</tt>, every match of the query is processed. Otherwise, only the first.
    # \param unique_matches If <tt>True</tt>, only one of multiple equivalent substructure mappings is processed per match.
    # 
    def addPattern(molgraph: MolecularGraph, atom_label: int = 0, priority: int = 0, all_matches: bool = True, unique_matches: bool = False) -> None: pass

    ##
    # \brief Appends a copy of the pre-built pattern <em>pattern</em>.
    # 
    # \param pattern The pattern to copy and register.
    # 
    def addPattern(pattern: Pattern) -> None: pass

    ##
    # \brief Returns the registered pattern at index <em>idx</em>.
    # 
    # \param idx The zero-based pattern index.
    # 
    # \return A reference to the pattern. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumPatterns()).
    # 
    def getPattern(idx: int) -> Pattern: pass

    ##
    # \brief Removes the registered pattern at index <em>idx</em>.
    # 
    # \param idx The zero-based pattern index.
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumPatterns()).
    # 
    def removePattern(idx: int) -> None: pass

    ##
    # \brief Removes all registered patterns.
    # 
    def clear() -> None: pass

    ##
    # \brief Returns the number of registered patterns.
    # 
    # \return The pattern count.
    # 
    def getNumPatterns() -> int: pass

    ##
    # \brief Returns the atom label assigned to the atom at index <em>idx</em> during the last execute() call.
    # 
    # \param idx The zero-based atom index.
    # 
    # \return The atom label (zero if no pattern matched the atom). 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range <em>[0, N)</em>, where <em>N</em> is the number of atoms of the molecular graph last processed by execute().
    # 
    def getAtomLabel(idx: int) -> int: pass

    ##
    # \brief Returns the index of the pattern that produced the label of the atom at index <em>idx</em>.
    # 
    # \param idx The zero-based atom index.
    # 
    # \return The matching pattern index (returns an undefined value if hasAtomLabel(idx) is <tt>False</tt>). 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range <em>[0, N)</em>, where <em>N</em> is the number of atoms of the molecular graph last processed by execute().
    # 
    def getPatternIndex(idx: int) -> int: pass

    ##
    # \brief Tells whether the atom at index <em>idx</em> has received a label from any matching pattern.
    # 
    # \param idx The zero-based atom index in the molecular graph last processed by execute().
    # 
    # \return <tt>True</tt> if the atom carries a label, and <tt>False</tt> otherwise. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range <em>[0, N)</em>, where <em>N</em> is the number of atoms of the molecular graph last processed by execute().
    # 
    def hasAtomLabel(idx: int) -> bool: pass

    ##
    # \brief Runs the registered patterns against <em>molgraph</em> and assigns atom labels accordingly.
    # 
    # \param molgraph The molecular graph to be typed.
    # 
    def execute(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the state of this typer by a copy of the state of <em>typer</em>.
    # 
    # \param typer The source <tt>PatternAtomTyper</tt>.
    # 
    # \return \a self
    # 
    def assign(typer: PatternAtomTyper) -> PatternAtomTyper: pass

    objectID = property(getObjectID)

    numPatterns = property(getNumPatterns)
