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
# \brief InteractionAnalyzer.
# 
class InteractionAnalyzer(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>InteractionAnalyzer</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %InteractionAnalyzer instance \a analyzer.
    # \param analyzer The \e %InteractionAnalyzer instance to copy.
    # 
    def __init__(analyzer: InteractionAnalyzer) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %InteractionAnalyzer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %InteractionAnalyzer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Specifies a function that gets used for checking whether all constraints are actually fulfilled for an interaction between a pair of features of the specified types.
    # 
    # \param type1 An identifier for the type of the first feature.
    # \param type2 An identifier for the type of the second feature.
    # \param func The constraint check function.
    # 
    def setConstraintFunction(type1: int, type2: int, func: BoolFeature2Functor) -> None: pass

    ##
    # \brief Removes the constraint check function that was registered for the specified pair of feature types.
    # 
    # \param type1 An identifier for the type of the first feature.
    # \param type2 An identifier for the type of the second feature.
    # 
    def removeConstraintFunction(type1: int, type2: int) -> None: pass

    ##
    # \brief Returns the constraint check function that was registered for the specified pair of feature types.
    # 
    # \param type1 An identifier for the type of the first feature.
    # \param type2 An identifier for the type of the second feature.
    # 
    # \return The registered constraint check function.
    # 
    def getConstraintFunction(type1: int, type2: int) -> BoolFeature2Functor: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %InteractionAnalyzer instance \a analyzer.
    # \param analyzer The \c %InteractionAnalyzer instance to copy.
    # \return \a self
    # 
    def assign(analyzer: InteractionAnalyzer) -> InteractionAnalyzer: pass

    ##
    # \brief Analyzes possible interactions of the features in feature container <em>cntnr1</em> and with features of <em>cntnr2</em> according to the registered constraint functions.
    # 
    # For every pairwise combination of the features in the first feature container <em>cntnr1</em> with the features in the second feature container <em>cntnr1</em> a lookup for a registered interaction constraint function using the respective feature types is performed. If no function for the corresponding type pair was registered, the pair of features is assumed to be incompatible and that no interaction between them can ever occur. Note that a function that was registered for the type pair <tt>[typeA, typeB]</tt> does not automatically get called for the reverse pair <tt>[typeB, typeA]</tt>! If, however, a function was found, it gets called with the current feature instance of the first feature container as the first argument and the feature instance of the second feature container as the second argument. If the constraint function evaluates to <tt>True</tt>, a corresponding mapping of the first to the second feature object is inserted in the specified output map <em>iactions</em> (be aware that a mapping of the second to the first feature is not added automatically!).
    # 
    # \param cntnr1 The first feature container.
    # \param cntnr2 The second feature container.
    # \param iactions An output map that contains features of <em>cntnr1</em> as keys and interacting features of <em>cntnr2</em> as values.
    # \param append If <tt>False</tt>, <em>iactions</em> gets cleared before adding any feature mappings.
    # 
    def analyze(cntnr1: FeatureContainer, cntnr2: FeatureContainer, iactions: FeatureMapping, append: bool = False) -> None: pass

    objectID = property(getObjectID)
