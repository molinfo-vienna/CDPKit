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
# \brief Enumerates the tautomers of a molecular graph by iteratively applying a configurable set of Chem.TautomerizationRule instances and reporting each accepted tautomer to a user-supplied callback.
# 
# After registering tautomerization rules (via addTautomerizationRule()) and a callback (via setCallbackFunction()), each call to generate() seeds the enumeration with the input molecular graph, applies every registered rule to every intermediate tautomer to derive the next generation, and reports each newly-generated tautomer to the callback. The Mode setting controls how aggressively duplicates are filtered.
# 
class TautomerGenerator(Boost.Python.instance):

    ##
    # \brief Selects the duplicate-filtering strategy applied during tautomer enumeration.
    # 
    class Mode(Boost.Python.enum):

        ##
        # \brief Two tautomers are considered equal if they share the same constitutional (topological) connection table.
        # 
        TOPOLOGICALLY_UNIQUE = 0

        ##
        # \brief Two tautomers are considered equal if they share the same connection table AND the same stereo-configuration.
        # 
        GEOMETRICALLY_UNIQUE = 1

        ##
        # \brief Every accepted tautomer is reported, even if topologically/geometrically equivalent to an already-reported one.
        # 
        EXHAUSTIVE = 2

    ##
    # \brief Constructs the <tt>TautomerGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>TautomerGenerator</tt> instance <em>gen</em>.
    # 
    # \param gen The <tt>TautomerGenerator</tt> to copy.
    # 
    def __init__(gen: TautomerGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %TautomerGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %TautomerGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Registers a new tautomerization rule.
    # 
    # \param rule The tautomerization rule to register.
    # 
    def addTautomerizationRule(rule: TautomerizationRule) -> None: pass

    ##
    # \brief Removes the registered tautomerization rule at index <em>idx</em>.
    # 
    # \param idx The zero-based rule index.
    # 
    # \throw Base.IndexError if the number of rules is zero or <em>idx</em> is not in the range [0, getNumTautomerizationRules() - 1].
    # 
    def removeTautomerizationRule(idx: int) -> None: pass

    ##
    # \brief Returns the registered tautomerization rule at index <em>idx</em>.
    # 
    # \param idx The zero-based rule index.
    # 
    # \return A reference to the rule smart reference. 
    # 
    # \throw Base.IndexError if the number of rules is zero or <em>idx</em> is not in the range [0, getNumTautomerizationRules() - 1].
    # 
    def getTautomerizationRule(idx: int) -> TautomerizationRule: pass

    ##
    # \brief Returns the number of registered tautomerization rules.
    # 
    # \return The rule count.
    # 
    def getNumTautomerizationRules() -> int: pass

    ##
    # \brief Sets the callback invoked for every accepted tautomer.
    # 
    # The callback receives the tautomer molecular graph as its argument and returns a boolean: returning <tt>False</tt> aborts the enumeration.
    # 
    # \param func The new callback function.
    # 
    def setCallbackFunction(func: BoolMolecularGraphFunctor) -> None: pass

    ##
    # \brief Returns the currently configured callback.
    # 
    # \return A reference to the callback function.
    # 
    def getCallbackFunction() -> BoolMolecularGraphFunctor: pass

    ##
    # \brief Sets the duplicate-filtering mode.
    # 
    # \param mode The new Mode value.
    # 
    def setMode(mode: Mode) -> None: pass

    ##
    # \brief Returns the currently configured duplicate-filtering mode.
    # 
    # \return The Mode value.
    # 
    def getMode() -> Mode: pass

    ##
    # \brief Specifies whether tautomer stereochemistry shall be preserved/regarded during duplicate filtering.
    # 
    # \param regard If <tt>True</tt>, stereo-configurations are taken into account.
    # 
    def regardStereochemistry(regard: bool) -> None: pass

    ##
    # \brief Tells whether stereochemistry is regarded during duplicate filtering.
    # 
    # \return <tt>True</tt> if stereochemistry is regarded, and <tt>False</tt> otherwise.
    # 
    def stereochemistryRegarded() -> bool: pass

    ##
    # \brief Specifies whether atom isotope information shall be regarded during duplicate filtering.
    # 
    # \param regard If <tt>True</tt>, isotopes are taken into account.
    # 
    def regardIsotopes(regard: bool) -> None: pass

    ##
    # \brief Tells whether isotope information is regarded during duplicate filtering.
    # 
    # \return <tt>True</tt> if isotopes are regarded, and <tt>False</tt> otherwise.
    # 
    def isotopesRegarded() -> bool: pass

    ##
    # \brief Tells whether 2D atom coordinates are cleared from the generated tautomers.
    # 
    # \return <tt>True</tt> if 2D coordinates are cleared, and <tt>False</tt> otherwise. 
    # 
    # \since 1.3
    # 
    def coordinates2DCleared() -> bool: pass

    ##
    # \brief Tells whether 3D atom coordinates are cleared from the generated tautomers.
    # 
    # \return <tt>True</tt> if 3D coordinates are cleared, and <tt>False</tt> otherwise. 
    # 
    # \since 1.3
    # 
    def coordinates3DCleared() -> bool: pass

    ##
    # \brief Specifies whether tautomers that differ only by resonance (no atom-connectivity change) shall be filtered out.
    # 
    # \param remove If <tt>True</tt>, resonance-only duplicates are not reported.
    # 
    # \since 1.1
    # 
    def removeResonanceDuplicates(remove: bool) -> None: pass

    ##
    # \brief Tells whether resonance-only duplicates are filtered out.
    # 
    # \return <tt>True</tt> if resonance duplicates are removed, and <tt>False</tt> otherwise. 
    # 
    # \since 1.1
    # 
    def resonanceDuplicatesRemoved() -> bool: pass

    ##
    # \brief Sets the optional setup function invoked on the input molecular graph before enumeration starts.
    # 
    # The setup function may modify the input (e.g. add explicit hydrogens, perceive aromaticity) prior to enumeration.
    # 
    # \param func The new custom-setup function.
    # 
    def setCustomSetupFunction(func: VoidMolecularGraphFunctor) -> None: pass

    ##
    # \brief Enumerates the tautomers of <em>molgraph</em> and reports each accepted one to the registered callback.
    # 
    # \param molgraph The molecular graph whose tautomers shall be generated.
    # 
    def generate(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the state of this generator by a copy of the state of <em>gen</em>.
    # 
    # \param gen The source <tt>TautomerGenerator</tt>.
    # 
    # \return \a self
    # 
    def assign(gen: TautomerGenerator) -> TautomerGenerator: pass

    objectID = property(getObjectID)

    clearCoordinates2D = property(coordinates2DCleared, clearCoordinates2D)

    clearCoordinates3D = property(coordinates3DCleared, clearCoordinates3D)

    callbackFunction = property(getCallbackFunction, setCallbackFunction)

    mode = property(getMode, setMode)

    regStereo = property(stereochemistryRegarded, regardStereochemistry)

    regIsotopes = property(isotopesRegarded, regardIsotopes)

    remResonanceDuplicates = property(resonanceDuplicatesRemoved, removeResonanceDuplicates)

    numTautomerizationRules = property(getNumTautomerizationRules)
