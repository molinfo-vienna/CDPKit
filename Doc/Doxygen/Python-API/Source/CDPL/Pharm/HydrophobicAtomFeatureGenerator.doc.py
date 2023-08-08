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
# \brief HydrophobicAtomFeatureGenerator.
# 
# \see [\ref CATA]
# 
class HydrophobicAtomFeatureGenerator(PatternBasedFeatureGenerator):

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
    DEF_HYD_THRESHOLD = 0.5

    ##
    # \brief Constructs the <tt>HydrophobicAtomFeatureGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Perceives hydrophobic group features of the molecular graph a\ molgraph and adds them to the pharmacophore <em>pharm</em>.
    # 
    # \param molgraph The molecular graph for which to perceive the features.
    # \param pharm The output pharmacophore where to add the generated features.
    # 
    def __init__(molgraph: Chem.MolecularGraph, pharm: Pharmacophore) -> None: pass

    ##
    # \brief Constructs a copy of the <tt>HydrophobicAtomFeatureGenerator</tt> instance <em>gen</em>.
    # 
    # \param gen The <tt>HydrophobicAtomFeatureGenerator</tt> to copy.
    # 
    def __init__(gen: HydrophobicAtomFeatureGenerator) -> None: pass

    ##
    # \brief Copies the <tt>HydrophobicAtomFeatureGenerator</tt> instance <em>gen</em>.
    # 
    # \param gen The <tt>HydrophobicAtomFeatureGenerator</tt> to copy.
    # 
    # \return \a self
    # 
    def assign(gen: HydrophobicAtomFeatureGenerator) -> HydrophobicAtomFeatureGenerator: pass

    ##
    # \brief Specifies the value of the feature type property that has to be set on newly generated features.
    # 
    # \param type The value of the feature type property.
    # 
    # \note The default type is specified by the constant HydrophobicAtomFeatureGenerator.DEF_FEATURE_TYPE. 
    # 
    # \see FeatureProperty.TYPE
    # 
    def setFeatureType(type: int) -> None: pass

    ##
    # \brief Specifies the value of the feature geometry property that has to be set on newly generated features.
    # 
    # \param geom The value of the feature geometry property.
    # 
    # \note The default type is specified by the constant HydrophobicAtomFeatureGenerator.DEF_FEATURE_GEOM. 
    # 
    # \see FeatureProperty.GEOMETRY
    # 
    def setFeatureGeometry(geom: int) -> None: pass

    ##
    # \brief Specifies the value of the feature tolerance property that has to be set on newly generated features.
    # 
    # \param tol The value of the feature tolerance property.
    # 
    # \note The default value is specified by the constant HydrophobicAtomFeatureGenerator.DEF_FEATURE_TOL. 
    # 
    # \see FeatureProperty.TOLERANCE
    # 
    def setFeatureTolerance(tol: float) -> None: pass

    ##
    # \brief Specifies the minimum hydrophobicity of an atom that is required for the generation of a new feature.
    # 
    # \param thresh The minimum atom hydrophobicity.
    # 
    # \note The default value is specified by the constant HydrophobicAtomFeatureGenerator.DEF_HYD_THRESHOLD.
    # 
    def setHydrophobicityThreshold(thresh: float) -> None: pass

    ##
    # \brief Returns the value of the feature type property that gets set on newly generated features.
    # 
    # \return The used value of the feature type property. 
    # 
    # \see FeatureProperty.TYPE
    # 
    def getFeatureType() -> int: pass

    ##
    # \brief Returns the value of the feature geometry property that gets set on newly generated features.
    # 
    # \return The used value of the feature geometry property. 
    # 
    # \see FeatureProperty.GEOMETRY
    # 
    def getFeatureGeometry() -> int: pass

    ##
    # \brief Returns the value of the feature tolerance property that gets set on newly generated features.
    # 
    # \return The value of the feature tolerance property. 
    # 
    # \see FeatureProperty.TOLERANCE
    # 
    def getFeatureTolerance() -> float: pass

    ##
    # \brief Returns the minimum hydrophobicity of an atom that is required for the generation of a new feature.
    # 
    # \return The specified minimum atom hydrophobicity.
    # 
    def getHydrophobicityThreshold() -> float: pass

    featureType = property(getFeatureType, setFeatureType)

    featureGeometry = property(getFeatureGeometry, setFeatureGeometry)

    featureTolerance = property(getFeatureTolerance, setFeatureTolerance)

    hydThreshold = property(getHydrophobicityThreshold, setHydrophobicityThreshold)
