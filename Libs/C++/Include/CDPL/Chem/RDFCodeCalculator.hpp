/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RDFCodeCalculator.hpp 
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
 * \brief Definition of the class CDPL::Chem::RDFCodeCalculator.
 */

#ifndef CDPL_CHEM_RDFCODECALCULATOR_HPP
#define CDPL_CHEM_RDFCODECALCULATOR_HPP

#include <cstddef>

#include <boost/function.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Atom;

		/**
		 * \addtogroup CDPL_CHEM_RDF_CODES
		 * @{
		 */

		/**
		 * \brief RDFCodeCalculator.
		 * \see [\ref CITB, \ref HBMD]
		 */
		class CDPL_CHEM_API RDFCodeCalculator
		{

		public:
			/**
			 * \brief Type of the generic functor class used to store user-defined atom pair weight functions.
			 *
			 * The provided atom pair weight function (or function object) is required to take the two atoms (as a
			 * \c const reference to Chem::Atom) as its arguments and return the weight of the atom pair as
			 * a floating-point value of type \c double. For details refer to the <em>Boost.Function</em>
			 * documentation [\ref BFUN]. 
			 */
			typedef boost::function2<double, const Atom&, const Atom&> AtomPairWeightFunction;

			/**
			 * \brief Constructs the \c %RDFCodeCalculator instance.
			 */
			RDFCodeCalculator();

			/**
			 * \brief Constructs the \c %RDFCodeCalculator instance and calculates the \e RDF code of the
			 *        molecular graph \a molgraph.
			 *
			 * The calculated \e RDF code can be retrieved by a call to getResult().
			 *
			 * \param molgraph The molecular graph for which to calculate the \e RDF code vector.
			 * \param rdf_code The calculated \e RDF code vector.
			 */
			RDFCodeCalculator(const MolecularGraph& molgraph, Math::DVector& rdf_code);

			/**
			 * \brief Allows to specify the smoothing factor used in the calculation of
			 *        atom pair \e RDF contributions.
			 * \param factor The smoothing factor.
			 * \note The default value of the smoothing factor is <em>1.0</em>.
			 */
			void setSmoothingFactor(double factor);

			/**
			 * \brief Returns the smoothing factor used in the calculation of
			 *        atom pair \e RDF contributions.
			 * \return The applied smoothing factor.
			 */
			double getSmoothingFactor() const;

			/**
			 * \brief Allows to specify the scaling factor for the \e RDF code elements.
			 * \param factor The scaling factor.
			 * \note The default scaling factor is <em>100.0</em>.
			 */
			void setScalingFactor(double factor);

			/**
			 * \brief Returns the scaling factor applied to the \e RDF code elements.
			 * \return The applied scaling factor.
			 */
			double getScalingFactor() const;

			/**
			 * \brief Sets the starting value of the radius.
			 * \param start_radius The starting value of the radius.
			 * \note The default starting radius is <em>0.0</em>&Aring;.
			 */
			void setStartRadius(double start_radius);

			/**
			 * \brief Returns the starting value of the radius.
			 * \return The current radius starting value.
			 */
			double getStartRadius() const;

			/**
			 * \brief Sets the radius step size between successive \e RDF code elements.
			 * \param radius_inc The radius step size.
			 * \note The default radius step size is <em>0.1</em>&Aring;.
			 */
			void setRadiusIncrement(double radius_inc);

			/**
			 * \brief Returns the radius step size between successive \e RDF code elements.
			 * \return The applied radius step size.
			 */
			double getRadiusIncrement() const;

			/**
			 * \brief Sets the number of desired radius incrementation steps.
			 *
			 * The number of performed radius incrementation steps defines the size of the calculated \e RDF code vector
			 * which is equal to the number of steps plus \e 1.
			 *
			 * \param num_steps The number of radius incrementation steps.
			 * \note The default number of steps is \e 128.
			 */
			void setNumSteps(std::size_t num_steps);

			/**
			 * \brief Returns the number of performed radius incrementation steps.
			 * \return The number of performed radius incrementation steps.
			 */
			std::size_t getNumSteps() const;

			/**
			 * \brief Allows to specify a custom atom pair weight function.
			 * \param func A RDFCodeCalculator::AtomPairWeightFunction instance that wraps the target function.
			 * \note The default atom pair weight function returns the value the product of the atom types (see namespace
			 *       Chem::AtomType).
			 */
			void setAtomPairWeightFunction(const AtomPairWeightFunction& func);

			/**
			 * \brief Calculates the \e RDF code of the molecular graph \a molgraph.
			 *
			 * The elements of the returned \e RDF code vector correspond to the values of the radial distribution function
			 * at different radii. The first element provides the \e RDF value at the start radius (see setStartRadius())
			 * which gets incremented by the radius step size (see setRadiusIncrement()) for each successive
			 * element. The total number of calculated \e RDF values (corresponds to the \e RDF code vector's length) is given by
			 * the specified number of incrementation steps (see setNumSteps()) plus \e 1.
			 * 
			 * \param molgraph The molecular graph for which to calculate the \e RDF code.
			 * \param rdf_code The calculated \e RDF code vector.
			 */
			void calculate(const MolecularGraph& molgraph, Math::DVector& rdf_code);

		private:
			RDFCodeCalculator(const RDFCodeCalculator&);

			RDFCodeCalculator& operator=(const RDFCodeCalculator&);

			void init(const MolecularGraph&);

			double                 smoothingFactor;
			double                 scalingFactor;
			double                 startRadius;
			double                 radiusIncrement;
			std::size_t            numSteps;
			AtomPairWeightFunction weightFunc;
			Math::DMatrix          weightMatrix;
		}; 

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_RDFCODECALCULATOR_HPP
