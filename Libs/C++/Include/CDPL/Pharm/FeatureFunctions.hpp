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
         * \brief Returns the Pharm::FeatureProperty::TYPE property of \a feature.
         * \param feature The feature.
         * \return The Pharm::FeatureType identifier.
         */
        CDPL_PHARM_API unsigned int getType(const Feature& feature);

        /**
         * \brief Sets the Pharm::FeatureProperty::TYPE property of \a feature.
         * \param feature The feature.
         * \param type The new Pharm::FeatureType identifier.
         */
        CDPL_PHARM_API void setType(Feature& feature, unsigned int type);

        /**
         * \brief Removes the Pharm::FeatureProperty::TYPE property from \a feature.
         * \param feature The feature.
         */
        CDPL_PHARM_API void clearType(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::TYPE property of \a feature has been set.
         * \param feature The feature.
         * \return \c true if the type property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasType(const Feature& feature);


        /**
         * \brief Returns the Pharm::FeatureProperty::GEOMETRY property of \a feature.
         * \param feature The feature.
         * \return The Pharm::FeatureGeometry identifier.
         */
        CDPL_PHARM_API unsigned int getGeometry(const Feature& feature);

        /**
         * \brief Sets the Pharm::FeatureProperty::GEOMETRY property of \a feature.
         * \param feature The feature.
         * \param geom The new Pharm::FeatureGeometry identifier.
         */
        CDPL_PHARM_API void setGeometry(Feature& feature, unsigned int geom);

        /**
         * \brief Removes the Pharm::FeatureProperty::GEOMETRY property from \a feature.
         * \param feature The feature.
         */
        CDPL_PHARM_API void clearGeometry(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::GEOMETRY property of \a feature has been set.
         * \param feature The feature.
         * \return \c true if the geometry property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasGeometry(const Feature& feature);


        /**
         * \brief Returns the Pharm::FeatureProperty::ORIENTATION property of \a feature.
         * \param feature The feature.
         * \return A \c const reference to the 3D orientation vector.
         */
        CDPL_PHARM_API const Math::Vector3D& getOrientation(const Feature& feature);

        /**
         * \brief Sets the Pharm::FeatureProperty::ORIENTATION property of \a feature.
         * \param feature The feature.
         * \param orient The new 3D orientation vector.
         */
        CDPL_PHARM_API void setOrientation(Feature& feature, const Math::Vector3D& orient);

        /**
         * \brief Removes the Pharm::FeatureProperty::ORIENTATION property from \a feature.
         * \param feature The feature.
         */
        CDPL_PHARM_API void clearOrientation(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::ORIENTATION property of \a feature has been set.
         * \param feature The feature.
         * \return \c true if the orientation property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasOrientation(const Feature& feature);


        /**
         * \brief Returns the Pharm::FeatureProperty::LENGTH property of \a feature.
         * \param feature The feature.
         * \return The length value.
         */
        CDPL_PHARM_API double getLength(const Feature& feature);

        /**
         * \brief Sets the Pharm::FeatureProperty::LENGTH property of \a feature.
         * \param feature The feature.
         * \param length The new length value.
         */
        CDPL_PHARM_API void setLength(Feature& feature, double length);

        /**
         * \brief Removes the Pharm::FeatureProperty::LENGTH property from \a feature.
         * \param feature The feature.
         */
        CDPL_PHARM_API void clearLength(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::LENGTH property of \a feature has been set.
         * \param feature The feature.
         * \return \c true if the length property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasLength(const Feature& feature);


        /**
         * \brief Returns the Pharm::FeatureProperty::TOLERANCE property of \a feature.
         * \param feature The feature.
         * \return The tolerance value.
         */
        CDPL_PHARM_API double getTolerance(const Feature& feature);

        /**
         * \brief Sets the Pharm::FeatureProperty::TOLERANCE property of \a feature.
         * \param feature The feature.
         * \param tol The new tolerance value.
         */
        CDPL_PHARM_API void setTolerance(Feature& feature, double tol);

        /**
         * \brief Removes the Pharm::FeatureProperty::TOLERANCE property from \a feature.
         * \param feature The feature.
         */
        CDPL_PHARM_API void clearTolerance(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::TOLERANCE property of \a feature has been set.
         * \param feature The feature.
         * \return \c true if the tolerance property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasTolerance(const Feature& feature);


        /**
         * \brief Returns the Pharm::FeatureProperty::WEIGHT property of \a feature.
         * \param feature The feature.
         * \return The weight value.
         */
        CDPL_PHARM_API double getWeight(const Feature& feature);

        /**
         * \brief Sets the Pharm::FeatureProperty::WEIGHT property of \a feature.
         * \param feature The feature.
         * \param weight The new weight value.
         */
        CDPL_PHARM_API void setWeight(Feature& feature, double weight);

        /**
         * \brief Removes the Pharm::FeatureProperty::WEIGHT property from \a feature.
         * \param feature The feature.
         */
        CDPL_PHARM_API void clearWeight(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::WEIGHT property of \a feature has been set.
         * \param feature The feature.
         * \return \c true if the weight property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasWeight(const Feature& feature);


        /**
         * \brief Returns the Pharm::FeatureProperty::SUBSTRUCTURE property of \a feature (the underlying atoms/bonds).
         * \param feature The feature.
         * \return A \c const reference to the feature substructure.
         */
        CDPL_PHARM_API const Chem::Fragment::SharedPointer& getSubstructure(const Feature& feature);

        /**
         * \brief Sets the Pharm::FeatureProperty::SUBSTRUCTURE property of \a feature.
         * \param feature The feature.
         * \param substruct The new feature substructure.
         */
        CDPL_PHARM_API void setSubstructure(Feature& feature, const Chem::Fragment::SharedPointer& substruct);

        /**
         * \brief Removes the Pharm::FeatureProperty::SUBSTRUCTURE property from \a feature.
         * \param feature The feature.
         */
        CDPL_PHARM_API void clearSubstructure(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::SUBSTRUCTURE property of \a feature has been set.
         * \param feature The feature.
         * \return \c true if the substructure property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasSubstructure(const Feature& feature);

        /**
         * \brief Generates a string describing the residue environment of \a feature (residue names of interacting pocket residues).
         * \param feature The feature.
         * \return The generated environment-residue info string.
         * \since 1.3
         */
        CDPL_PHARM_API std::string getEnvironmentResidueInfo(const Feature& feature);

        /**
         * \brief Generates a string describing the residue environment of \a feature into \a info.
         * \param feature The feature.
         * \param info The output string.
         * \return A reference to \a info.
         * \since 1.4
         */
        CDPL_PHARM_API std::string& getEnvironmentResidueInfo(const Feature& feature, std::string& info);

        /**
         * \brief Generates a string describing the per-atom residue environment of \a feature (residue names and atom names of interacting pocket atoms).
         * \param feature The feature.
         * \return The generated environment-residue-atom info string.
         * \since 1.4
         */
        CDPL_PHARM_API std::string getEnvironmentResidueAtomInfo(const Feature& feature);

        /**
         * \brief Generates a string describing the per-atom residue environment of \a feature into \a info.
         * \param feature The feature.
         * \param info The output string.
         * \return A reference to \a info.
         * \since 1.4
         */
        CDPL_PHARM_API std::string& getEnvironmentResidueAtomInfo(const Feature& feature, std::string& info);

        /**
         * \brief Returns the Pharm::FeatureProperty::ENVIRONMENT_SUBSTRUCTURE property of \a feature (interacting pocket residues).
         * \param feature The feature.
         * \return A \c const reference to the environment substructure.
         * \since 1.4
         */
        CDPL_PHARM_API const Chem::Fragment::SharedPointer& getEnvironmentSubstructure(const Feature& feature);

        /**
         * \brief Sets the Pharm::FeatureProperty::ENVIRONMENT_SUBSTRUCTURE property of \a feature.
         * \param feature The feature.
         * \param substruct The new environment substructure.
         */
        CDPL_PHARM_API void setEnvironmentSubstructure(Feature& feature, const Chem::Fragment::SharedPointer& substruct);

        /**
         * \brief Removes the Pharm::FeatureProperty::ENVIRONMENT_SUBSTRUCTURE property from \a feature.
         * \param feature The feature.
         */
        CDPL_PHARM_API void clearEnvironmentSubstructure(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::ENVIRONMENT_SUBSTRUCTURE property of \a feature has been set.
         * \param feature The feature.
         * \return \c true if the environment substructure property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasEnvironmentSubstructure(const Feature& feature);


        /**
         * \brief Returns the Pharm::FeatureProperty::DISABLED_FLAG property of \a feature.
         * \param feature The feature.
         * \return \c true if the feature is flagged as disabled, and \c false otherwise.
         */
        CDPL_PHARM_API bool getDisabledFlag(const Feature& feature);

        /**
         * \brief Sets the Pharm::FeatureProperty::DISABLED_FLAG property of \a feature.
         * \param feature The feature.
         * \param flag The new disabled-flag value.
         */
        CDPL_PHARM_API void setDisabledFlag(Feature& feature, bool flag);

        /**
         * \brief Removes the Pharm::FeatureProperty::DISABLED_FLAG property from \a feature.
         * \param feature The feature.
         */
        CDPL_PHARM_API void clearDisabledFlag(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::DISABLED_FLAG property of \a feature has been set.
         * \param feature The feature.
         * \return \c true if the disabled flag is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasDisabledFlag(const Feature& feature);


        /**
         * \brief Returns the Pharm::FeatureProperty::OPTIONAL_FLAG property of \a feature.
         * \param feature The feature.
         * \return \c true if the feature is flagged as optional, and \c false otherwise.
         */
        CDPL_PHARM_API bool getOptionalFlag(const Feature& feature);

        /**
         * \brief Sets the Pharm::FeatureProperty::OPTIONAL_FLAG property of \a feature.
         * \param feature The feature.
         * \param flag The new optional-flag value.
         */
        CDPL_PHARM_API void setOptionalFlag(Feature& feature, bool flag);

        /**
         * \brief Removes the Pharm::FeatureProperty::OPTIONAL_FLAG property from \a feature.
         * \param feature The feature.
         */
        CDPL_PHARM_API void clearOptionalFlag(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::OPTIONAL_FLAG property of \a feature has been set.
         * \param feature The feature.
         * \return \c true if the optional flag is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasOptionalFlag(const Feature& feature);


        /**
         * \brief Returns the Pharm::FeatureProperty::HYDROPHOBICITY property of \a feature.
         * \param feature The feature.
         * \return The hydrophobicity value.
         */
        CDPL_PHARM_API double getHydrophobicity(const Feature& feature);

        /**
         * \brief Sets the Pharm::FeatureProperty::HYDROPHOBICITY property of \a feature.
         * \param feature The feature.
         * \param hyd The new hydrophobicity value.
         */
        CDPL_PHARM_API void setHydrophobicity(Feature& feature, double hyd);

        /**
         * \brief Removes the Pharm::FeatureProperty::HYDROPHOBICITY property from \a feature.
         * \param feature The feature.
         */
        CDPL_PHARM_API void clearHydrophobicity(Feature& feature);

        /**
         * \brief Tells whether the Pharm::FeatureProperty::HYDROPHOBICITY property of \a feature has been set.
         * \param feature The feature.
         * \return \c true if the hydrophobicity property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasHydrophobicity(const Feature& feature);
        
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FEATUREFUNCTIONS_HPP
