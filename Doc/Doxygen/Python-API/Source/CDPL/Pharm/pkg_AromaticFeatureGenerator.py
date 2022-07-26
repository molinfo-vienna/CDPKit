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
class AromaticFeatureGenerator(PatternBasedFeatureGenerator):

    ##
    # \brief 
    #
    DEF_FEATURE_TOL = 0.9

    ##
    # \brief 
    #
    DEF_FEATURE_TYPE = 2

    ##
    # \brief 
    #
    DEF_FEATURE_GEOM = 3

    ##
    # \brief Initializes the \e %AromaticFeatureGenerator instance.
    # \param self The \e %AromaticFeatureGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %AromaticFeatureGenerator instance.
    # \param self The \e %AromaticFeatureGenerator instance to initialize.
    # \param gen 
    #
    def __init__(self: object, gen: AromaticFeatureGenerator) -> None: pass

    ##
    # \brief Initializes the \e %AromaticFeatureGenerator instance.
    # \param self The \e %AromaticFeatureGenerator instance to initialize.
    # \param molgraph 
    # \param pharm 
    #
    def __init__(self: object, molgraph: CDPL.Chem.MolecularGraph, pharm: Pharmacophore) -> None: pass

    ##
    # \brief 
    # \param self The \e %AromaticFeatureGenerator instance this method is called upon.
    # \param type 
    #
    def setFeatureType(self: AromaticFeatureGenerator, type: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %AromaticFeatureGenerator instance this method is called upon.
    # \param geom 
    #
    def setFeatureGeometry(self: AromaticFeatureGenerator, geom: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %AromaticFeatureGenerator instance this method is called upon.
    # \param tol 
    #
    def setFeatureTolerance(self: AromaticFeatureGenerator, tol: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %AromaticFeatureGenerator instance this method is called upon.
    # \return 
    #
    def getFeatureType(self: AromaticFeatureGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %AromaticFeatureGenerator instance this method is called upon.
    # \return 
    #
    def getFeatureGeometry(self: AromaticFeatureGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %AromaticFeatureGenerator instance this method is called upon.
    # \return 
    #
    def getFeatureTolerance(self: AromaticFeatureGenerator) -> float: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %AromaticFeatureGenerator instance \a gen.
    # \param self The \e %AromaticFeatureGenerator instance this method is called upon.
    # \param gen The \e %AromaticFeatureGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: AromaticFeatureGenerator, gen: AromaticFeatureGenerator) -> AromaticFeatureGenerator: pass

    ##
    # \brief 
    #
    featureType = property(getFeatureType, setFeatureType)

    ##
    # \brief 
    #
    featureGeometry = property(getFeatureGeometry, setFeatureGeometry)

    ##
    # \brief 
    #
    featureTolerance = property(getFeatureTolerance, setFeatureTolerance)
