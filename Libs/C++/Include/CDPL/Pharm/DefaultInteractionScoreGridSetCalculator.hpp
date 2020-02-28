/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DefaultInteractionScoreGridSetCalculator.hpp 
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
 * \brief Definition of the class CDPL::Pharm::DefaultInteractionScoreGridSetCalculator.
 */

#ifndef CDPL_PHARM_DEFAULTINTERACTIONSCOREGRIDSETCALCULATOR_HPP
#define CDPL_PHARM_DEFAULTINTERACTIONSCOREGRIDSETCALCULATOR_HPP

#include <cstddef>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/InteractionScoreGridSetCalculator.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Grid/RegularGridSet.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		/**
		 * \addtogroup CDPL_PHARM_INTERACTION_SCORE_GRID_CALCULATION
		 * @{
		 */

		/**
		 * \brief DefaultInteractionScoreGridSetCalculator.
		 */
		class CDPL_PHARM_API DefaultInteractionScoreGridSetCalculator : public InteractionScoreGridSetCalculator
		{

		  public:
			DefaultInteractionScoreGridSetCalculator();

			DefaultInteractionScoreGridSetCalculator(double step_size, std::size_t x_size, std::size_t y_size, std::size_t z_size);

			DefaultInteractionScoreGridSetCalculator(double x_step_size, double y_step_size, double z_step_size, 
													 std::size_t x_size, std::size_t y_size, std::size_t z_size);

			const Math::Matrix4D& getCoordinatesTransform() const;

			template <typename T>
			void setCoordinatesTransform(const T& xform) {
				coordsTransform = xform;
			}

			double getXStepSize() const;

			void setXStepSize(double size);

			double getYStepSize() const;

			void setYStepSize(double size);

			double getZStepSize() const;

			void setZStepSize(double size);

			std::size_t getGridXSize() const;

			void setGridXSize(std::size_t size);

			std::size_t getGridYSize() const;

			void setGridYSize(std::size_t size);

			std::size_t getGridZSize() const;

			void setGridZSize(std::size_t size);

			void calculate(const FeatureContainer& features, Grid::DRegularGridSet& grid_set);

		  private:
			Grid::DSpatialGrid::SharedPointer createGrid(unsigned int ftr_type, unsigned int tgt_ftr_type) const;

			void init();

			double                 xStepSize;          
			double                 yStepSize;          
			double                 zStepSize;          
			std::size_t            gridXSize;
			std::size_t            gridYSize;
			std::size_t            gridZSize;
            Math::Matrix4D         coordsTransform;
			Grid::DRegularGridSet* gridSet;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_DEFAULTINTERACTIONSCOREGRIDSETCALCULATOR_HPP
