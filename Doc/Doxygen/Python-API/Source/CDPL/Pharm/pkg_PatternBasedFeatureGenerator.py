#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
    # \brief Initializes the \e %PatternBasedFeatureGenerator instance.
    # \param self The \e %PatternBasedFeatureGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %PatternBasedFeatureGenerator instance.
    # \param self The \e %PatternBasedFeatureGenerator instance to initialize.
    # \param gen 
    #
    def __init__(self: object, gen: PatternBasedFeatureGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %PatternBasedFeatureGenerator instance this method is called upon.
    # \param pattern 
    # \param type 
    # \param tol 
    # \param geom 
    # \param length 
    #
    def addIncludePattern(self: PatternBasedFeatureGenerator, pattern: CDPL.Chem.MolecularGraph, type: int, tol: float, geom: int, length: float = 1.0) -> None: pass

    ##
    # \brief 
    # \param self The \e %PatternBasedFeatureGenerator instance this method is called upon.
    # \param pattern 
    #
    def addExcludePattern(self: PatternBasedFeatureGenerator, pattern: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %PatternBasedFeatureGenerator instance this method is called upon.
    #
    def clearIncludePatterns(self: PatternBasedFeatureGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %PatternBasedFeatureGenerator instance this method is called upon.
    #
    def clearExcludePatterns(self: PatternBasedFeatureGenerator) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %PatternBasedFeatureGenerator instance \a gen.
    # \param self The \e %PatternBasedFeatureGenerator instance this method is called upon.
    # \param gen The \e %PatternBasedFeatureGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: PatternBasedFeatureGenerator, gen: PatternBasedFeatureGenerator) -> PatternBasedFeatureGenerator: pass

    ##
    # \brief 
    # \param self The \e %PatternBasedFeatureGenerator instance this method is called upon.
    # \param molgraph 
    # \param pharm 
    #
    def generate(self: PatternBasedFeatureGenerator, molgraph: CDPL.Chem.MolecularGraph, pharm: Pharmacophore) -> None: pass

    ##
    # \brief 
    # \param self The \e %PatternBasedFeatureGenerator instance this method is called upon.
    # \param molgraph 
    # \param pharm 
    #
    def __call__(self: PatternBasedFeatureGenerator, molgraph: CDPL.Chem.MolecularGraph, pharm: Pharmacophore) -> None: pass
