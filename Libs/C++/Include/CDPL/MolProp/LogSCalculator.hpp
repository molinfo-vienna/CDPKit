/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * LogSCalculator.hpp 
 *  
 * Prediction of aqueous solubility by an atom contribution approach
 * (T. J. Hou, K. Xia, W. Zhang, X. J. Xu, J. Chem. Inf. Comput. Sci. 2004, 44, 266-275)
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
 * \brief Definition of the class CDPL::MolProp::LogSCalculator.
 */

#ifndef CDPL_MOLPROP_LOGSCALCULATOR_HPP
#define CDPL_MOLPROP_LOGSCALCULATOR_HPP

#include <cstddef>

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/Chem/PatternAtomTyper.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

	namespace MolProp
	{

		/**
		 * \brief LogSCalculator.
		 * \see [\ref LOGS]
		 */
		class CDPL_MOLPROP_API LogSCalculator 
		{
			
		  public:
			/**
			 * \brief Specifies the number of different features used by the \f$ \log S \f$ model.
			 */
			static const std::size_t FEATURE_VECTOR_SIZE = 79;

			/**
			 * \brief Constructs the \c %LogSCalculator instance.
			 */
			LogSCalculator();

			/**
			 * \brief Constructs the \c %LogSCalculator instance and calculates the \f$ \log S \f$ of the molecular
			 *        graph \a molgraph.
			 *
			 * The calculated \f$ \log S \f$ can be retrieved by a call to getResult().
			 *
			 * \param molgraph The molecular graph for which to calculate the \f$ \log S \f$.
			 */
			LogSCalculator(const Chem::MolecularGraph& molgraph);

			/**
			 * \brief Calculates the \f$ \log S \f$ of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to calculate the \f$ \log S \f$.
			 * \return The calculated \f$ \log S \f$ of the molecular graph \a molgraph.
			 */
			double calculate(const Chem::MolecularGraph& molgraph);

			/**
			 * \brief Returns the result of the last \f$ \log S \f$ calculation.
			 * \return The result of the last \f$ \log S \f$ calculation, or zero if a calculation
			 *         has not yet been performed.
			 */
			double getResult() const;

			/**
			 * \brief Returns the feature count vector of the last \f$ \log S \f$ calculation.
			 *
			 * The occurrence count of a particular structural feature can be retrieved from the returned vector
			 * via its feature index. The feature index correspond to the numerical identifier of the feature's definition 
			 * in the original publication [\ref LOGS].
			 *
			 * \return The feature count vector of the last \f$ \log S \f$ calculation.
			 * \note The returned feature vector is of size LogSCalculator::FEATURE_VECTOR_SIZE.
			 */
			const Math::DVector& getFeatureVector() const;

		  private:
			void init(const Chem::MolecularGraph& molgraph);
			void countHydrophicCarbons(const Chem::MolecularGraph& molgraph);
			void calcLogS(const Chem::MolecularGraph& molgraph);

			Chem::PatternAtomTyper atomTyper;
			Math::DVector          featureVector;
			double                 logS;
		};
	}
}

#endif // CDPL_MOLPROP_LOGSCALCULATOR_HPP
 
