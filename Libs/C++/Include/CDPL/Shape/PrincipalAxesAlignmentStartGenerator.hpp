/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PrincipalAxesAlignmentStartGenerator.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Shape::PrincipalAxesAlignmentStartGenerator.
 */

#ifndef CDPL_SHAPE_PRINCIPALAXESALIGNMENTSTARTGENERATOR_HPP
#define CDPL_SHAPE_PRINCIPALAXESALIGNMENTSTARTGENERATOR_HPP

#include <vector>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/GaussianShapeAlignmentStartGenerator.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/QuaternionExpression.hpp"


namespace CDPL 
{

    namespace Shape
    {

		/**
		 * \addtogroup CDPL_SHAPE_ALIGNMENT
		 * @{
		 */

		class CDPL_SHAPE_API PrincipalAxesAlignmentStartGenerator : public GaussianShapeAlignmentStartGenerator
		{
			
		  public:
			enum CenterAlignmentMode
			{

			    SHAPE_CENTROID            = 0x1,
				NON_COLOR_ELEMENT_CENTERS = 0x2,
				COLOR_ELEMENT_CENTERS     = 0x4,
			};

			PrincipalAxesAlignmentStartGenerator();
				
			unsigned int setupReference(GaussianShapeFunction& func, Math::Matrix4D& xform) const; 

			unsigned int setupAligned(GaussianShapeFunction& func, Math::Matrix4D& xform) const; 

			void setCenterAlignmentMode(CenterAlignmentMode mode);

			CenterAlignmentMode getCenterAlignmentMode() const;

			void setSymmetryThreshold(double thresh);

			double getSymmetryThreshold();

			void setReference(const GaussianShapeFunction& func, unsigned int sym_class);

			bool generate(const GaussianShapeFunction& func, unsigned int sym_class);
			
			std::size_t getNumStartTransforms() const;

			const QuaternionTransformation& getStartTransform(std::size_t idx) const;

		  private:
			typedef std::vector<QuaternionTransformation> StartTransformList;

			void generate(const Math::Vector3D& ctr_trans, const GaussianShapeFunction& func, unsigned int axes_swap_flags);

			template <typename QE>
			void addStartTransform(Math::Vector3D::ConstPointer ctr_trans_data, const Math::QuaternionExpression<QE>& rot_quat);
		
			CenterAlignmentMode  ctrAlignmentMode;
			StartTransformList   startTransforms;
			const GaussianShape* refShape;
			double               symThreshold;
			unsigned int         refAxesSwapFlags;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_SHAPE_PRINCIPALAXESALIGNMENTSTARTGENERATOR_HPP
