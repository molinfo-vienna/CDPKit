/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PrincipalAxesAlignmentStartGenerator.hpp 
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
 * \brief Definition of the class CDPL::Shape::PrincipalAxesAlignmentStartGenerator.
 */

#ifndef CDPL_SHAPE_PRINCIPALAXESALIGNMENTSTARTGENERATOR_HPP
#define CDPL_SHAPE_PRINCIPALAXESALIGNMENTSTARTGENERATOR_HPP

#include <vector>

#include <boost/random/mersenne_twister.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/GaussianShapeAlignmentStartGenerator.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/QuaternionExpression.hpp"


namespace CDPL 
{

    namespace Shape
    {

		class CDPL_SHAPE_API PrincipalAxesAlignmentStartGenerator : public GaussianShapeAlignmentStartGenerator
		{
			
		  public:
			static const double      DEF_SYMMETRY_THRESHOLD;
			static const std::size_t DEF_NUM_RANDOM_STARTS = 4;
			static const double      DEF_MAX_RANDOM_TRANSLATION;
			
			PrincipalAxesAlignmentStartGenerator();
				
			unsigned int setupReference(GaussianShapeFunction& func, Math::Matrix4D& xform) const; 

			unsigned int setupAligned(GaussianShapeFunction& func, Math::Matrix4D& xform) const; 

			void genShapeCenterStarts(bool generate);

			bool genShapeCenterStarts() const;
			
			void genColorCenterStarts(bool generate);

			bool genColorCenterStarts() const;

			void genNonColorCenterStarts(bool generate);

			bool genNonColorCenterStarts() const;
			
			void genRandomStarts(bool generate);

			bool genRandomStarts() const;

			void genForAlignedShapeCenters(bool generate);

			bool genForAlignedShapeCenters() const;

			void genForReferenceShapeCenters(bool generate);

			bool genForReferenceShapeCenters() const;

			void genForLargerShapeCenters(bool generate);

			bool genForLargerShapeCenters() const;
			
			void setSymmetryThreshold(double thresh);

			double getSymmetryThreshold();

			void setMaxRandomTranslation(double max_trans);

			double getMaxRandomTranslation() const;

			void setNumRandomStarts(std::size_t num_starts);

			std::size_t getNumRandomStarts() const;

			void setRandomSeed(unsigned int seed);
			
			void setReference(const GaussianShapeFunction& func, unsigned int sym_class);

			bool generate(const GaussianShapeFunction& func, unsigned int sym_class);
			
			std::size_t getNumStartTransforms() const;

			std::size_t getNumStartSubTransforms() const;

			const QuaternionTransformation& getStartTransform(std::size_t idx) const;

		  private:
			void generateForElementCenters(const GaussianShapeFunction& func, unsigned int axes_swap_flags, bool ref_shape);
			void generate(const Math::Vector3D& ctr_trans, unsigned int axes_swap_flags);

			template <typename QE>
			void addStartTransform(Math::Vector3D::ConstPointer ctr_trans_data, const Math::QuaternionExpression<QE>& rot_quat);

			typedef std::vector<QuaternionTransformation> StartTransformList;
			typedef boost::random::mt11213b RandomEngine;

			bool                         shapeCtrStarts;
			bool                         colCtrStarts;
			bool                         nonColCtrStarts;
			bool                         randomStarts;
			bool                         genForAlgdShape;
			bool                         genForRefShape;
			bool                         genForLargerShape;
			StartTransformList           startTransforms;
			const GaussianShapeFunction* refShapeFunc;
			double                       symThreshold;
			double                       maxRandomTrans;
			std::size_t                  numRandomStarts;
			unsigned int                 refAxesSwapFlags;
			std::size_t                  numSubTransforms;
			RandomEngine                 randomEngine;
		};
    }
}

#endif // CDPL_SHAPE_PRINCIPALAXESALIGNMENTSTARTGENERATOR_HPP
