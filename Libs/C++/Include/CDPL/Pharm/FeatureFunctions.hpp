/* 
 * FeatureFunctions.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * \file
 * \brief Declaration of functions that operate on Pharm::Feature instances.
 */

#ifndef CDPL_PHARM_FEATUREFUNCTIONS_HPP
#define CDPL_PHARM_FEATUREFUNCTIONS_HPP

#include <string>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class Feature;

        /**
         * \brief Returns the value of the Pharm::FeatureProperty::TYPE property of the feature \a feature.
         * \param feature The feature for which to get the property value.
         * \return The feature type identifier (see namespace Pharm::FeatureType).
         */
        CDPL_PHARM_API unsigned int getType(const Feature& feature);

        /**
         * \brief Sets the value of the Pharm::FeatureProperty::TYPE property of the feature \a feature to \a type.
         * \param feature The feature for which to set the property value.
         * \param type The new feature type identifier (see namespace Pharm::FeatureType).
         */
        CDPL_PHARM_API void setType(Feature& feature, unsigned int type);

        /**
         * \brief Clears the value of the Pharm::FeatureProperty::TYPE property of the feature \a feature.
         * \param feature The feature for which to clear the property value.
         */
        CDPL_PHARM_API void clearType(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::TYPE property of the feature \a feature is set.
         * \param feature The feature for which to query the property value.
         * \return \c true if the type property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasType(const Feature& feature);


        /**
         * \brief Returns the value of the Pharm::FeatureProperty::GEOMETRY property of the feature \a feature.
         * \param feature The feature for which to get the property value.
         * \return The feature geometry identifier (see namespace Pharm::FeatureGeometry).
         */
        CDPL_PHARM_API unsigned int getGeometry(const Feature& feature);

        /**
         * \brief Sets the value of the Pharm::FeatureProperty::GEOMETRY property of the feature \a feature to \a geom.
         * \param feature The feature for which to set the property value.
         * \param geom The new feature geometry identifier (see namespace Pharm::FeatureGeometry).
         */
        CDPL_PHARM_API void setGeometry(Feature& feature, unsigned int geom);

        /**
         * \brief Clears the value of the Pharm::FeatureProperty::GEOMETRY property of the feature \a feature.
         * \param feature The feature for which to clear the property value.
         */
        CDPL_PHARM_API void clearGeometry(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::GEOMETRY property of the feature \a feature is set.
         * \param feature The feature for which to query the property value.
         * \return \c true if the geometry property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasGeometry(const Feature& feature);


        /**
         * \brief Returns the value of the Pharm::FeatureProperty::ORIENTATION property of the feature \a feature.
         * \param feature The feature for which to get the property value.
         * \return A \c const reference to the 3D orientation vector.
         */
        CDPL_PHARM_API const Math::Vector3D& getOrientation(const Feature& feature);

        /**
         * \brief Sets the value of the Pharm::FeatureProperty::ORIENTATION property of the feature \a feature to \a orient.
         * \param feature The feature for which to set the property value.
         * \param orient The new 3D orientation vector.
         */
        CDPL_PHARM_API void setOrientation(Feature& feature, const Math::Vector3D& orient);

        /**
         * \brief Clears the value of the Pharm::FeatureProperty::ORIENTATION property of the feature \a feature.
         * \param feature The feature for which to clear the property value.
         */
        CDPL_PHARM_API void clearOrientation(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::ORIENTATION property of the feature \a feature is set.
         * \param feature The feature for which to query the property value.
         * \return \c true if the orientation property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasOrientation(const Feature& feature);


        /**
         * \brief Returns the value of the Pharm::FeatureProperty::LENGTH property of the feature \a feature.
         * \param feature The feature for which to get the property value.
         * \return The length value.
         */
        CDPL_PHARM_API double getLength(const Feature& feature);

        /**
         * \brief Sets the value of the Pharm::FeatureProperty::LENGTH property of the feature \a feature to \a length.
         * \param feature The feature for which to set the property value.
         * \param length The new length value.
         */
        CDPL_PHARM_API void setLength(Feature& feature, double length);

        /**
         * \brief Clears the value of the Pharm::FeatureProperty::LENGTH property of the feature \a feature.
         * \param feature The feature for which to clear the property value.
         */
        CDPL_PHARM_API void clearLength(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::LENGTH property of the feature \a feature is set.
         * \param feature The feature for which to query the property value.
         * \return \c true if the length property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasLength(const Feature& feature);


        /**
         * \brief Returns the value of the Pharm::FeatureProperty::TOLERANCE property of the feature \a feature.
         * \param feature The feature for which to get the property value.
         * \return The tolerance value.
         */
        CDPL_PHARM_API double getTolerance(const Feature& feature);

        /**
         * \brief Sets the value of the Pharm::FeatureProperty::TOLERANCE property of the feature \a feature to \a tol.
         * \param feature The feature for which to set the property value.
         * \param tol The new tolerance value.
         */
        CDPL_PHARM_API void setTolerance(Feature& feature, double tol);

        /**
         * \brief Clears the value of the Pharm::FeatureProperty::TOLERANCE property of the feature \a feature.
         * \param feature The feature for which to clear the property value.
         */
        CDPL_PHARM_API void clearTolerance(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::TOLERANCE property of the feature \a feature is set.
         * \param feature The feature for which to query the property value.
         * \return \c true if the tolerance property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasTolerance(const Feature& feature);


        /**
         * \brief Returns the value of the Pharm::FeatureProperty::WEIGHT property of the feature \a feature.
         * \param feature The feature for which to get the property value.
         * \return The weight value.
         */
        CDPL_PHARM_API double getWeight(const Feature& feature);

        /**
         * \brief Sets the value of the Pharm::FeatureProperty::WEIGHT property of the feature \a feature to \a weight.
         * \param feature The feature for which to set the property value.
         * \param weight The new weight value.
         */
        CDPL_PHARM_API void setWeight(Feature& feature, double weight);

        /**
         * \brief Clears the value of the Pharm::FeatureProperty::WEIGHT property of the feature \a feature.
         * \param feature The feature for which to clear the property value.
         */
        CDPL_PHARM_API void clearWeight(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::WEIGHT property of the feature \a feature is set.
         * \param feature The feature for which to query the property value.
         * \return \c true if the weight property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasWeight(const Feature& feature);


        /**
         * \brief Returns the value of the Pharm::FeatureProperty::SUBSTRUCTURE property of the feature \a feature (the underlying atoms/bonds).
         * \param feature The feature for which to get the property value.
         * \return The stored feature substructure.
         */
        CDPL_PHARM_API const Chem::Fragment::SharedPointer& getSubstructure(const Feature& feature);

        /**
         * \brief Sets the value of the Pharm::FeatureProperty::SUBSTRUCTURE property of the feature \a feature to \a substruct.
         * \param feature The feature for which to set the property value.
         * \param substruct The new feature substructure.
         */
        CDPL_PHARM_API void setSubstructure(Feature& feature, const Chem::Fragment::SharedPointer& substruct);

        /**
         * \brief Clears the value of the Pharm::FeatureProperty::SUBSTRUCTURE property of the feature \a feature.
         * \param feature The feature for which to clear the property value.
         */
        CDPL_PHARM_API void clearSubstructure(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::SUBSTRUCTURE property of the feature \a feature is set.
         * \param feature The feature for which to query the property value.
         * \return \c true if the substructure property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasSubstructure(const Feature& feature);

        /**
         * \brief Generates a string describing the environment residues associated with the feature \a feature.
         * \param feature The feature.
         * \return The generated environment residue info string.
         * \since 1.3
         */
        CDPL_PHARM_API std::string getEnvironmentResidueInfo(const Feature& feature);

        /**
         * \brief Generates a string describing the environment residues associated with the feature \a feature.
         * \param feature The feature.
         * \param info Will store the generated environment residue info string.
         * \return A reference to \a info.
         * \since 1.4
         */
        CDPL_PHARM_API std::string& getEnvironmentResidueInfo(const Feature& feature, std::string& info);

        /**
         * \brief Generates a string describing the environment residue atoms associated with the feature \a feature.
         * \param feature The feature.
         * \return The generated environment residue atom info string.
         * \since 1.4
         */
        CDPL_PHARM_API std::string getEnvironmentResidueAtomInfo(const Feature& feature);

        /**
         * \brief Generates a string describing the environment residue atoms associated with the feature \a feature.
         * \param feature The feature.
         * \param info Will store the generated environment residue atom info string.
         * \return A reference to \a info.
         * \since 1.4
         */
        CDPL_PHARM_API std::string& getEnvironmentResidueAtomInfo(const Feature& feature, std::string& info);

        /**
         * \brief Returns the value of the Pharm::FeatureProperty::ENVIRONMENT_SUBSTRUCTURE property of the feature \a feature.
         * \param feature The feature for which to get the property value.
         * \return The stored environment substructure.
         * \since 1.4
         */
        CDPL_PHARM_API const Chem::Fragment::SharedPointer& getEnvironmentSubstructure(const Feature& feature);

        /**
         * \brief Sets the value of the Pharm::FeatureProperty::ENVIRONMENT_SUBSTRUCTURE property of the feature \a feature to \a substruct.
         * \param feature The feature for which to set the property value.
         * \param substruct The new environment substructure.
         */
        CDPL_PHARM_API void setEnvironmentSubstructure(Feature& feature, const Chem::Fragment::SharedPointer& substruct);

        /**
         * \brief Clears the value of the Pharm::FeatureProperty::ENVIRONMENT_SUBSTRUCTURE property of the feature \a feature.
         * \param feature The feature for which to clear the property value.
         */
        CDPL_PHARM_API void clearEnvironmentSubstructure(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::ENVIRONMENT_SUBSTRUCTURE property of the feature \a feature is set.
         * \param feature The feature.
         * \return \c true if the environment substructure property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasEnvironmentSubstructure(const Feature& feature);


        /**
         * \brief Returns the value of the Pharm::FeatureProperty::DISABLED_FLAG property of the feature \a feature.
         * \param feature The feature for which to get the property value.
         * \return \c true if the feature is flagged as disabled, and \c false otherwise.
         */
        CDPL_PHARM_API bool getDisabledFlag(const Feature& feature);

        /**
         * \brief Sets the value of the Pharm::FeatureProperty::DISABLED_FLAG property of the feature \a feature to \a flag.
         * \param feature The feature for which to set the property value.
         * \param flag The new disabled flag value.
         */
        CDPL_PHARM_API void setDisabledFlag(Feature& feature, bool flag);

        /**
         * \brief Clears the value of the Pharm::FeatureProperty::DISABLED_FLAG property of the feature \a feature.
         * \param feature The feature for which to clear the property value.
         */
        CDPL_PHARM_API void clearDisabledFlag(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::DISABLED_FLAG property of the feature \a feature is set.
         * \param feature The feature for which to query the property value.
         * \return \c true if the disabled flag is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasDisabledFlag(const Feature& feature);


        /**
         * \brief Returns the value of the Pharm::FeatureProperty::OPTIONAL_FLAG property of the feature \a feature.
         * \param feature The feature for which to get the property value.
         * \return \c true if the feature is flagged as optional, and \c false otherwise.
         */
        CDPL_PHARM_API bool getOptionalFlag(const Feature& feature);

        /**
         * \brief Sets the value of the Pharm::FeatureProperty::OPTIONAL_FLAG property of the feature \a feature to \a flag.
         * \param feature The feature for which to set the property value.
         * \param flag The new optional flag value.
         */
        CDPL_PHARM_API void setOptionalFlag(Feature& feature, bool flag);

        /**
         * \brief Clears the value of the Pharm::FeatureProperty::OPTIONAL_FLAG property of the feature \a feature.
         * \param feature The feature for which to clear the property value.
         */
        CDPL_PHARM_API void clearOptionalFlag(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::OPTIONAL_FLAG property of the feature \a feature is set.
         * \param feature The feature for which to query the property value.
         * \return \c true if the optional flag is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasOptionalFlag(const Feature& feature);


        /**
         * \brief Returns the value of the Pharm::FeatureProperty::HYDROPHOBICITY property of the feature \a feature.
         * \param feature The feature for which to get the property value.
         * \return The hydrophobicity value.
         */
        CDPL_PHARM_API double getHydrophobicity(const Feature& feature);

        /**
         * \brief Sets the value of the Pharm::FeatureProperty::HYDROPHOBICITY property of the feature \a feature to \a hyd.
         * \param feature The feature for which to set the property value.
         * \param hyd The new hydrophobicity value.
         */
        CDPL_PHARM_API void setHydrophobicity(Feature& feature, double hyd);

        /**
         * \brief Clears the value of the Pharm::FeatureProperty::HYDROPHOBICITY property of the feature \a feature.
         * \param feature The feature for which to clear the property value.
         */
        CDPL_PHARM_API void clearHydrophobicity(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::HYDROPHOBICITY property of the feature \a feature is set.
         * \param feature The feature for which to query the property value.
         * \return \c true if the hydrophobicity property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasHydrophobicity(const Feature& feature);
        
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FEATUREFUNCTIONS_HPP
