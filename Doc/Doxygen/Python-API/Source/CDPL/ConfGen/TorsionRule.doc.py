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
# \brief Data structure for the representation of single torsion library rules.
# 
# Eeach rule consists of a <em>SMARTS</em> match pattern and a list of preferred torsion angles (each with tolerances and a score).
# 
class TorsionRule(Boost.Python.instance):

    ##
    # \brief One preferred torsion angle for a rule, characterized by its value, the two tolerance bands and a score.
    # 
    class AngleEntry(Boost.Python.instance):

        ##
        # \brief Constructs the <tt>AngleEntry</tt> with the given angle value, tolerances and score.
        # 
        # \param ang The angle value in degrees.
        # \param tol1 The first (preferred) tolerance band.
        # \param tol2 The second (relaxed) tolerance band.
        # \param score The score (higher = more preferred).
        # 
        def __init__(ang: float, tol1: float, tol2: float, score: float) -> None: pass

        ##
        # \brief Initializes a copy of the \c %AngleEntry instance \a entry.
        # \param entry The \c %AngleEntry instance to copy.
        # 
        def __init__(entry: AngleEntry) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %AngleEntry instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %AngleEntry instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %AngleEntry instance \a entry.
        # \param entry The \c %AngleEntry instance to copy.
        # \return \a self
        # 
        def assign(entry: AngleEntry) -> AngleEntry: pass

        ##
        # \brief Returns the angle value.
        # 
        # \return The angle value in degrees.
        # 
        def getAngle() -> float: pass

        ##
        # \brief Returns the score (higher values mark more strongly preferred angles).
        # 
        # \return The score.
        # 
        def getScore() -> float: pass

        ##
        # \brief Returns the first (preferred) tolerance band.
        # 
        # \return The first tolerance band in degrees.
        # 
        def getTolerance1() -> float: pass

        ##
        # \brief Returns the second (relaxed) tolerance band.
        # 
        # \return The second tolerance band in degrees.
        # 
        def getTolerance2() -> float: pass

        objectID = property(getObjectID)

        angle = property(getAngle)

        score = property(getScore)

        tolerance1 = property(getTolerance1)

        tolerance2 = property(getTolerance2)

    ##
    # \brief Initializes the \c %TorsionRule instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %TorsionRule instance \a rule.
    # \param rule The \c %TorsionRule instance to copy.
    # 
    def __init__(rule: TorsionRule) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %TorsionRule instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %TorsionRule instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %TorsionRule instance \a rule.
    # \param rule The \c %TorsionRule instance to copy.
    # \return \a self
    # 
    def assign(rule: TorsionRule) -> TorsionRule: pass

    ##
    # \brief Returns the <em>SMARTS</em> match pattern.
    # 
    # \return A reference to the <em>SMARTS</em> match pattern.
    # 
    def getMatchPatternString() -> str: pass

    ##
    # \brief Sets the <em>SMARTS</em> match pattern.
    # 
    # \param ptn_str The new <em>SMARTS</em> match pattern.
    # 
    def setMatchPatternString(ptn_str: str) -> None: pass

    ##
    # \brief Returns the match pattern molecular graph.
    # 
    # \return A shared reference to the match pattern molecular graph.
    # 
    def getMatchPattern() -> Chem.MolecularGraph: pass

    ##
    # \brief Sets the match pattern molecular graph.
    # 
    # \param ptn The new match pattern molecular graph.
    # 
    def setMatchPattern(ptn: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Returns the number of stored angle entries.
    # 
    # \return The angle entry count.
    # 
    def getNumAngles() -> int: pass

    ##
    # \brief Returns the angle entry at index <em>idx</em>.
    # 
    # \param idx The zero-based angle entry index.
    # 
    # \return A reference to the angle entry. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumAngles()).
    # 
    def getAngle(idx: int) -> AngleEntry: pass

    ##
    # \brief Removes the angle entry at index <em>idx</em>.
    # 
    # \param idx The zero-based angle entry index.
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumAngles()).
    # 
    def removeAngle(idx: int) -> None: pass

    ##
    # \brief Appends the angle entry <em>ang_entry</em> to the rule.
    # 
    # \param ang_entry The angle entry to append.
    # 
    def addAngle(ang_entry: AngleEntry) -> None: pass

    ##
    # \brief 
    # \param ang 
    # \param tol1 
    # \param tol2 
    # \param score 
    #
    def addAngle(ang: float, tol1: float, tol2: float, score: float) -> None: pass

    ##
    # \brief Clears the match pattern and removes all angle entries.
    # 
    def clear() -> None: pass

    ##
    # \brief Swaps the contents of this rule with <em>rule</em>.
    # 
    # \param rule The other torsion rule.
    # 
    def swap(rule: TorsionRule) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> AngleEntry: pass

    ##
    # \brief 
    # \param idx 
    #
    def __delitem__(idx: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += ang_entry</tt>.
    # \param ang_entry Specifies the second addend.
    # \return The updated \c %None instance \a self.
    # 
    def __iadd__(ang_entry: AngleEntry) -> None: pass

    objectID = property(getObjectID)

    numAngles = property(getNumAngles)

    matchPatternString = property(getMatchPatternString, setMatchPatternString)

    matchPattern = property(getMatchPattern, setMatchPattern)
