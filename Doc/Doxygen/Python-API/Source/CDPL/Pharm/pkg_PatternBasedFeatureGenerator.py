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
# \brief PatternBasedFeatureGenerator.
# 
class PatternBasedFeatureGenerator(FeatureGenerator):

    ##
    # \brief 
    #
    class PatternAtomLabelFlag(Boost.Python.enum):

        ##
        # \brief FEATURE_ATOM_FLAG.
        #
        FEATURE_ATOM_FLAG = 1

        ##
        # \brief POS_REF_ATOM_FLAG.
        #
        POS_REF_ATOM_FLAG = 2

        ##
        # \brief GEOM_REF_ATOM1_FLAG.
        #
        GEOM_REF_ATOM1_FLAG = 4

        ##
        # \brief GEOM_REF_ATOM2_FLAG.
        #
        GEOM_REF_ATOM2_FLAG = 8

    ##
    # \brief Constructs the <tt>PatternBasedFeatureGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>PatternBasedFeatureGenerator</tt> instance <em>gen</em>.
    # 
    # \param gen The <tt>PatternBasedFeatureGenerator</tt> instance to copy.
    # 
    def __init__(gen: PatternBasedFeatureGenerator) -> None: pass

    ##
    # \brief Appends a new feature include pattern to the current set of patterns.
    # 
    # \param pattern The substructure search pattern of the feature.
    # \param type The value of the type property of the feature.
    # \param tol The value of the tolerance property of the feature.
    # \param geom The value of the geometry property of the feature.
    # \param length The value of the length property of vector features.
    # 
    def addIncludePattern(pattern: CDPL.Chem.MolecularGraph, type: int, tol: float, geom: int, length: float = 1.0) -> None: pass

    ##
    # \brief Appends a new feature include pattern to the current set of patterns.
    # 
    # \param pattern The substructure search pattern of the feature.
    # 
    def addExcludePattern(pattern: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief Clears the current set of include patterns.
    # 
    def clearIncludePatterns() -> None: pass

    ##
    # \brief Clears the current set of exclude patterns.
    # 
    def clearExcludePatterns() -> None: pass

    ##
    # \brief Replaces the current set include/exclude patterns by the patterns in the <tt>PatternBasedFeatureGenerator</tt> instance <em>gen</em>.
    # 
    # \param gen The <tt>PatternBasedFeatureGenerator</tt> instance providing the new patterns to use.
    # 
    # \return \a self
    # 
    def assign(gen: PatternBasedFeatureGenerator) -> PatternBasedFeatureGenerator: pass

    ##
    # \brief Perceives pharmacophore features according to the specified include/exclude patterns and adds them to the pharmacophore <em>pharm</em>.
    # 
    # \param molgraph The molecular graph for which to perceive the features.
    # \param pharm The output pharmacophore where to add the generated features.
    # 
    def generate(molgraph: CDPL.Chem.MolecularGraph, pharm: Pharmacophore) -> None: pass

    ##
    # \brief 
    # \param molgraph 
    # \param pharm 
    #
    def __call__(molgraph: CDPL.Chem.MolecularGraph, pharm: Pharmacophore) -> None: pass
