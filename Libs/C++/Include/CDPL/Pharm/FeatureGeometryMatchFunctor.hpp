/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureGeometryMatchFunctor.hpp 
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
 * \brief Definition of the class CDPL::Pharm::FeatureGeometryMatchFunctor.
 */

#ifndef CDPL_PHARM_FEATUREGEOMETRYMATCHFUNCTOR_HPP
#define CDPL_PHARM_FEATUREGEOMETRYMATCHFUNCTOR_HPP

#include "CDPL/Pharm/APIPrefix.hpp"

#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Feature;

		/**
		 * \brief FeatureGeometryMatchFunctor.
		 */
		class CDPL_PHARM_API FeatureGeometryMatchFunctor
		{

		  public:
		    static constexpr double DEF_MAX_HBA_INTERACTION_DIR_ANGLE     = 85.0;
		    static constexpr double DEF_MAX_HBA_ORIENTATION_DEVIATION     = 45.0;
		    static constexpr double DEF_MAX_HBD_INTERACTION_DIR_DEVIATION = 45.0;
			static constexpr double DEF_MAX_XBA_INTERACTION_DIR_DEVIATION = 45.0;
			static constexpr double DEF_MAX_XBD_INTERACTION_DIR_DEVIATION = 45.0;
		    static constexpr double DEF_MAX_AR_ORIENTATION_DEVIATION      = 45.0;

			FeatureGeometryMatchFunctor(double max_hba_int_dir_angle = DEF_MAX_HBA_INTERACTION_DIR_ANGLE, 
										double max_hba_orient_dev = DEF_MAX_HBA_ORIENTATION_DEVIATION,
										double max_hbd_int_dir_dev = DEF_MAX_HBD_INTERACTION_DIR_DEVIATION,
										double max_xba_int_dir_dev = DEF_MAX_XBA_INTERACTION_DIR_DEVIATION,
										double max_xbd_int_dir_dev = DEF_MAX_XBD_INTERACTION_DIR_DEVIATION,
										double max_ar_orient_dev = DEF_MAX_AR_ORIENTATION_DEVIATION);
		  
		    double getMaxHBAInteractionDirAngle() const;

			void setMaxHBAInteractionDirAngle(double angle);

			double getMaxHBAOrientationDeviation() const;

			void setMaxHBAOrientationDeviation(double angle);

			double getMaxHBDInteractionDirDeviation() const;

			void setMaxHBDInteractionDirDeviation(double angle);

			double getMaxXBDInteractionDirDeviation() const;

			void setMaxXBDInteractionDirDeviation(double angle);

			double getMaxXBAInteractionDirDeviation() const;

			void setMaxXBAInteractionDirDeviation(double angle);
			
			double getMaxAROrientationDeviation() const;

			void setMaxAROrientationDeviation(double angle);
		  
			/**
			 * \brief Calculates a score reflecting the goodness of the spatial feature orientation match.
			 * \param ftr1 The first feature.
			 * \param ftr2 The second feature.
			 * \return A score from \e 0 (=spatial deviation outside the allowed range) and \e 1 (optimum match) describing the 
			 *         goodness of the spatial orientation match of the two features.
			 */
			double operator()(const Feature& ftr1, const Feature& ftr2) const;

			/**
			 * \brief Calculates a score reflecting the goodness of the spatial feature orientation match.
			 * \param ftr1 The first feature.
			 * \param ftr2 The second feature.
			 * \param xform The transformation to apply to the spatial orientation of the second feature.
			 * \return A score from \e 0 (=spatial deviation outside the allowed range) and \e 1 (optimum match) describing the 
			 *         goodness of the spatial orientation match of the two features.
			 */
			double operator()(const Feature& ftr1, const Feature& ftr2, const Math::Matrix4D& xform) const;

		  private:
		    double calcHBDFeatureMatchScore(const Feature& ftr1, const Feature& ftr2, const Math::Matrix4D& xform) const;
		    double calcHBAFeatureMatchScore(const Feature& ftr1, const Feature& ftr2, const Math::Matrix4D& xform) const;
			double calcXBDFeatureMatchScore(const Feature& ftr1, const Feature& ftr2, const Math::Matrix4D& xform) const;
		    double calcXBAFeatureMatchScore(const Feature& ftr1, const Feature& ftr2, const Math::Matrix4D& xform) const;
		    double calcARFeatureMatchScore(const Feature& ftr1, const Feature& ftr2, const Math::Matrix4D& xform) const;

		    void transformOrientation(const Feature& ftr, const Math::Matrix4D& xform, Math::Vector3D& trans_orient) const;

		    double maxHBAInteractionDirAngle;
		    double maxHBAOrientationDeviation;
		    double maxHBDInteractionDirDeviation;
			double maxXBAInteractionDirDeviation;
			double maxXBDInteractionDirDeviation;
		    double maxAROrientationDeviation;
		};
    }
}

#endif // CDPL_PHARM_FEATUREGEOMETRYMATCHFUNCTOR_HPP
