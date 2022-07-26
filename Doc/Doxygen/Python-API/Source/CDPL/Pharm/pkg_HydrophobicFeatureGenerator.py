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
class HydrophobicFeatureGenerator(PatternBasedFeatureGenerator):

    ##
    # \brief 
    #
    DEF_FEATURE_TOL = 1.5

    ##
    # \brief 
    #
    DEF_FEATURE_TYPE = 1

    ##
    # \brief 
    #
    DEF_FEATURE_GEOM = 1

    ##
    # \brief 
    #
    DEF_HYD_THRESHOLD_RING = 2.0

    ##
    # \brief 
    #
    DEF_HYD_THRESHOLD_CHAIN = 0.8

    ##
    # \brief 
    #
    DEF_HYD_THRESHOLD_GROUP = 0.8

    ##
    # \brief Initializes the \e %HydrophobicFeatureGenerator instance.
    # \param self The \e %HydrophobicFeatureGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %HydrophobicFeatureGenerator instance.
    # \param self The \e %HydrophobicFeatureGenerator instance to initialize.
    # \param molgraph 
    # \param pharm 
    #
    def __init__(self: object, molgraph: CDPL.Chem.MolecularGraph, pharm: Pharmacophore) -> None: pass

    ##
    # \brief Initializes the \e %HydrophobicFeatureGenerator instance.
    # \param self The \e %HydrophobicFeatureGenerator instance to initialize.
    # \param gen 
    #
    def __init__(self: object, gen: HydrophobicFeatureGenerator) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %HydrophobicFeatureGenerator instance \a gen.
    # \param self The \e %HydrophobicFeatureGenerator instance this method is called upon.
    # \param gen The \e %HydrophobicFeatureGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: HydrophobicFeatureGenerator, gen: HydrophobicFeatureGenerator) -> HydrophobicFeatureGenerator: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicFeatureGenerator instance this method is called upon.
    # \param type 
    #
    def setFeatureType(self: HydrophobicFeatureGenerator, type: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicFeatureGenerator instance this method is called upon.
    # \param geom 
    #
    def setFeatureGeometry(self: HydrophobicFeatureGenerator, geom: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicFeatureGenerator instance this method is called upon.
    # \param tol 
    #
    def setFeatureTolerance(self: HydrophobicFeatureGenerator, tol: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicFeatureGenerator instance this method is called upon.
    # \param thresh 
    #
    def setRingHydrophobicityThreshold(self: HydrophobicFeatureGenerator, thresh: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicFeatureGenerator instance this method is called upon.
    # \param thresh 
    #
    def setChainHydrophobicityThreshold(self: HydrophobicFeatureGenerator, thresh: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicFeatureGenerator instance this method is called upon.
    # \param thresh 
    #
    def setGroupHydrophobicityThreshold(self: HydrophobicFeatureGenerator, thresh: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicFeatureGenerator instance this method is called upon.
    # \return 
    #
    def getFeatureType(self: HydrophobicFeatureGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicFeatureGenerator instance this method is called upon.
    # \return 
    #
    def getFeatureGeometry(self: HydrophobicFeatureGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicFeatureGenerator instance this method is called upon.
    # \return 
    #
    def getFeatureTolerance(self: HydrophobicFeatureGenerator) -> float: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicFeatureGenerator instance this method is called upon.
    # \return 
    #
    def getRingHydrophobicityThreshold(self: HydrophobicFeatureGenerator) -> float: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicFeatureGenerator instance this method is called upon.
    # \return 
    #
    def getChainHydrophobicityThreshold(self: HydrophobicFeatureGenerator) -> float: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicFeatureGenerator instance this method is called upon.
    # \return 
    #
    def getGroupHydrophobicityThreshold(self: HydrophobicFeatureGenerator) -> float: pass

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

    ##
    # \brief FIXME!
    #
    ringHydThreshold = property(getRingHydThreshold, setRingHydThreshold)

    ##
    # \brief FIXME!
    #
    chainHydThreshold = property(getChainHydThreshold, setChainHydThreshold)

    ##
    # \brief FIXME!
    #
    groupHydThreshold = property(getGroupHydThreshold, setGroupHydThreshold)
