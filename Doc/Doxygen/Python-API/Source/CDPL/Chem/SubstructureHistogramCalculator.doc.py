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
# \brief Counts occurrences of registered SMARTS substructure queries in a molecular graph, emitting the per-pattern hit counts into a user-supplied histogram container.
# 
# Patterns are added via addPattern() (each pattern carries a numeric ID, a priority and match-handling flags). On calculate() the registered patterns are run in priority order against the input molecular graph; matched atom/bond regions are masked so that subsequent lower-priority patterns cannot re-count overlapping substructures. The per-pattern hit count is then forwarded to the histogram via the expression <tt>histo</tt>[id]++ for every accepted match.
# 
class SubstructureHistogramCalculator(Boost.Python.instance):

    ##
    # \brief Holds a single SMARTS query pattern, its histogram ID, its priority and match-handling flags.
    # 
    class Pattern(Boost.Python.instance):

        ##
        # \brief Initializes a copy of the \c %Pattern instance \a pattern.
        # \param pattern The \c %Pattern instance to copy.
        # 
        def __init__(pattern: Pattern) -> None: pass

        ##
        # \brief Constructs a pattern from the query molecular graph <em>molgraph</em>.
        # 
        # \param molgraph The SMARTS query molecular graph.
        # \param id The histogram-bin ID to which matches of this pattern contribute.
        # \param priority The priority of this pattern; higher-priority patterns are evaluated first.
        # \param all_matches If <tt>True</tt>, every match of <em>molgraph</em> in the target is processed; if <tt>False</tt>, only the first match is processed.
        # \param unique_matches If <tt>True</tt>, only one of multiple equivalent substructure mappings is processed per match.
        # 
        def __init__(molgraph: MolecularGraph, id: int, priority: int = 0, all_matches: bool = True, unique_matches: bool = True) -> None: pass

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
        # \brief Returns the SMARTS query molecular graph of this pattern.
        # 
        # \return A reference to the query smart reference.
        # 
        def getStructure() -> MolecularGraph: pass

        ##
        # \brief Returns the pattern priority.
        # 
        # \return The priority value.
        # 
        def getPriority() -> int: pass

        ##
        # \brief Returns the histogram-bin ID of this pattern.
        # 
        # \return The histogram-bin ID.
        # 
        def getID() -> int: pass

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

        id = property(getID)

        allMatches = property(processAllMatches)

        uniqueMatches = property(processUniqueMatchesOnly)

    ##
    # \brief Constructs an empty <tt>SubstructureHistogramCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %SubstructureHistogramCalculator instance \a calc.
    # \param calc The \c %SubstructureHistogramCalculator instance to copy.
    # 
    def __init__(calc: SubstructureHistogramCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %SubstructureHistogramCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %SubstructureHistogramCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Registers a new pattern by its query molecular graph and per-pattern settings.
    # 
    # \param molgraph The SMARTS query molecular graph.
    # \param id The histogram-bin ID to which matches of this pattern contribute.
    # \param priority The pattern's priority; higher-priority patterns are evaluated first.
    # \param all_matches If <tt>True</tt>, every match of the query is processed; otherwise only the first.
    # \param unique_matches If <tt>True</tt>, only one of multiple equivalent substructure mappings is processed per match.
    # 
    def addPattern(molgraph: MolecularGraph, id: int = 0, priority: int = 0, all_matches: bool = True, unique_matches: bool = True) -> None: pass

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
    # \throw Base.IndexError if the number of patterns is zero or <em>idx</em> is not in the range [0, getNumPatterns() - 1].
    # 
    def getPattern(idx: int) -> Pattern: pass

    ##
    # \brief Removes the registered pattern at index <em>idx</em>.
    # 
    # \param idx The zero-based pattern index.
    # 
    # \throw Base.IndexError if the number of patterns is zero or <em>idx</em> is not in the range [0, getNumPatterns() - 1].
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
    # \brief Counts substructure occurrences in <em>molgraph</em> and writes the per-pattern hit counts to <em>histo</em>.
    # 
    # For every accepted match, the histogram is updated via <tt>histo</tt>[id] += 1 with the ID being the histogram-bin ID of the matching pattern.
    # 
    # \param molgraph The molecular graph to be analyzed.
    # \param histo The histogram receiving the hit counts.
    # 
    def calculate(molgraph: MolecularGraph, histo: object) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %SubstructureHistogramCalculator instance \a calc.
    # \param calc The \c %SubstructureHistogramCalculator instance to copy.
    # \return \a self
    # 
    def assign(calc: SubstructureHistogramCalculator) -> SubstructureHistogramCalculator: pass

    objectID = property(getObjectID)

    numPatterns = property(getNumPatterns)
