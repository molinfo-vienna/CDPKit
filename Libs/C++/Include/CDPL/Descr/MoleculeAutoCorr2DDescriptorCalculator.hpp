/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeAutoCorr2DDescriptorCalculator.hpp 
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
 * \brief Definition of the class CDPL::Descr::MoleculeAutoCorr2DDescriptorCalculator.
 */

#ifndef CDPL_DESCR_MOLECULEAUTOCORR2DDESCRIPTORCALCULATOR_HPP
#define CDPL_DESCR_MOLECULEAUTOCORR2DDESCRIPTORCALCULATOR_HPP

#include <boost/function.hpp>

#include "CDPL/Descr/APIPrefix.hpp"
#include "CDPL/Descr/AutoCorrelation2DVectorCalculator.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class Atom;
		class MolecularGraph;
	}

    namespace Descr
    {

		/**
		 * \brief MoleculeAutoCorr2DDescriptorCalculator.
		 */
		class CDPL_DESCR_API MoleculeAutoCorr2DDescriptorCalculator
		{

		  public:
			typedef boost::function4<double, const Chem::Atom&, const Chem::Atom&, unsigned int, unsigned int> AtomPairWeightFunction;

			enum Mode 
			{

		      SEMI_SPLIT,
			  FULL_SPLIT
			};
		
			/**
			 * \brief Constructs the \c %MoleculeAutoCorr2DDescriptorCalculator instance.
			 */
			MoleculeAutoCorr2DDescriptorCalculator();
			
			MoleculeAutoCorr2DDescriptorCalculator(const Chem::MolecularGraph& molgraph, Math::DVector& descr);

			/**
			 * \brief Allows to specify that maximum bond path length to consider.
			 * \param max_dist The maximum considered bond path length.
			 * \note The default value is \e 15.
			 */
			void setMaxDistance(std::size_t max_dist);

			/**
			 * \brief Returns the maximum considered bond path length.
			 * \return The maximum considered bond path length.
			 */
			std::size_t getMaxDistance() const;

			/**
			 * \brief Allows to specify a custom atom pair weight function.
			 * \param func A AtomPairWeightFunction instance that wraps the target function.
			 */
			void setAtomPairWeightFunction(const AtomPairWeightFunction& func);

			void setMode(Mode mode);

			Mode getMode() const;

			void calculate(const Chem::MolecularGraph& molgraph, Math::DVector& descr);

		  private:
			AutoCorrelation2DVectorCalculator autoCorrCalculator;
			AtomPairWeightFunction            weightFunc;
			Mode                              mode;
		}; 
    }
}

#endif // CDPL_DESCR_MOLECULEAUTOCORR2DDESCRIPTORCALCULATOR_HPP
