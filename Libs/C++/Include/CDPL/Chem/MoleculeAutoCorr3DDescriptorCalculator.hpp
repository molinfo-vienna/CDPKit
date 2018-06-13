/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeAutoCorr3DDescriptorCalculator.hpp 
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
 * \brief Definition of the class CDPL::Chem::MoleculeAutoCorr3DDescriptorCalculator.
 */

#ifndef CDPL_CHEM_MOLECULEAUTOCORR3DDESCRIPTORCALCULATOR_HPP
#define CDPL_CHEM_MOLECULEAUTOCORR3DDESCRIPTORCALCULATOR_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AutoCorrelation3DVectorCalculator.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Atom;
		class AtomContainer;

		/**
		 * \addtogroup CDPL_CHEM_DESCRIPTORS
		 * @{
		 */

		/**
		 * \brief MoleculeAutoCorr3DDescriptorCalculator.
		 */
		class CDPL_CHEM_API MoleculeAutoCorr3DDescriptorCalculator
		{

			typedef AutoCorrelation3DVectorCalculator<Atom> AutoCorr3DVectorCalculator;

		public:
			typedef AutoCorr3DVectorCalculator::Entity3DCoordinatesFunction Atom3DCoordinatesFunction;
			typedef AutoCorr3DVectorCalculator::EntityPairWeightFunction AtomPairWeightFunction;
	
			/**
			 * \brief Constructs the \c %MoleculeAutoCorr3DDescriptorCalculator instance.
			 */
			MoleculeAutoCorr3DDescriptorCalculator();
			
			MoleculeAutoCorr3DDescriptorCalculator(const AtomContainer& cntnr, Math::DVector& descr);

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
			 * \brief Sets the radius step size between successive descriptor vector elements.
			 * \param radius_inc The radius step size.
			 * \note The default radius step size is <em>0.1</em>&Aring;.
			 */
			void setRadiusIncrement(double radius_inc);

			/**
			 * \brief Returns the radius step size between successive \e AutoCorr3D code elements.
			 * \return The applied radius step size.
			 */
			double getRadiusIncrement() const;

			/**
			 * \brief Sets the number of desired radius incrementation steps.
			 *
			 * The number of performed radius incrementation steps defines the size of the calculated descriptor vector
			 * which is equal to the number of steps.
			 *
			 * \param num_steps The number of radius incrementation steps.
			 * \note The default number of steps is \e 99.
			 */
			void setNumSteps(std::size_t num_steps);

			/**
			 * \brief Returns the number of performed radius incrementation steps.
			 * \return The number of performed radius incrementation steps.
			 */
			std::size_t getNumSteps() const;

			/**
			 * \brief Allows to specify the atom coordinates function.
			 * \param func A Atom3DCoordinatesFunction instance that wraps the target function.
			 * \note The coordinates function must be specified before calling calculate(), otherwise a zero distance
			 *       for each atom pair will be used for the calculation.
			 */
			void setAtom3DCoordinatesFunction(const Atom3DCoordinatesFunction& func);

			/**
			 * \brief Allows to specify a custom atom pair weight function.
			 * \param func A AtomPairWeightFunction instance that wraps the target function.
			 */
			void setAtomPairWeightFunction(const AtomPairWeightFunction& func);

			void calculate(const AtomContainer& cntnr, Math::DVector& descr);

		  private:
			AutoCorr3DVectorCalculator autoCorrCalculator;
			AtomPairWeightFunction     weightFunc;
		}; 

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_MOLECULEAUTOCORR3DDESCRIPTORCALCULATOR_HPP
