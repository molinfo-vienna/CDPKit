/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomDensityGridCalculator.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Chem::AtomDensityGridCalculator.
 */

#ifndef CDPL_CHEM_ATOMDENSITYGRIDCALCULATOR_HPP
#define CDPL_CHEM_ATOMDENSITYGRIDCALCULATOR_HPP

#include <vector>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Chem/AtomPredicate.hpp"
#include "CDPL/Grid/SpatialGrid.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class AtomContainer;

		/**
		 * \addtogroup CDPL_CHEM_GRID_CALCULATION
		 * @{
		 */

		/**
		 * \brief AtomDensityGridCalculator.
		 */
		class CDPL_CHEM_API AtomDensityGridCalculator
		{

		  public:
			typedef boost::shared_ptr<AtomDensityGridCalculator> SharedPointer;

			typedef boost::function3<double, const Math::Vector3D&, const Math::Vector3D&, const Atom&> DensityFunction;
			typedef boost::function1<double, const Math::DVector&> DensityCombinationFunction;

			AtomDensityGridCalculator();

			AtomDensityGridCalculator(const DensityFunction& func);

			AtomDensityGridCalculator(const DensityFunction& density_func, const DensityCombinationFunction& comb_func); 

			void setDensityFunction(const DensityFunction& func);

			const DensityFunction& getDensityFunction() const;

			void setDensityCombinationFunction(const DensityCombinationFunction& func);

			const DensityCombinationFunction& getDensityCombinationFunction() const;

			/**
			 * \brief Specifies a function for the retrieval of atom 3D-coordinates for feature generation.
			 * \param func The atom 3D-coordinates function.
			 */
			void setAtom3DCoordinatesFunction(const Atom3DCoordinatesFunction& func);

			const Atom3DCoordinatesFunction& getAtom3DCoordinatesFunction() const;

			void calculate(const AtomContainer& atoms, Grid::DSpatialGrid& grid, const AtomPredicate& tgt_atom_pred);
	
			void calculate(const AtomContainer& atoms, Grid::DSpatialGrid& grid);

		  private:
			typedef std::vector<const Atom*> AtomList;

			AtomList                   tgtAtoms;
			Math::DVector              partialDensities;
			DensityFunction            densityFunc;
			DensityCombinationFunction densityCombinationFunc;
			Atom3DCoordinatesFunction  coordsFunc;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_ATOMDENSITYGRIDCALCULATOR_HPP
