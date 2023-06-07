/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PEOESigmaChargeCalculator.hpp 
 * 
 * Charge calculation by partial equalization of orbital electronegativities (PEOE)
 * (J. Gasteiger, M. Marsili, Tetrahedron 1980, 36, 3219-3228) 
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
 * \brief Definition of the class CDPL::MolProp::PEOESigmaChargeCalculator.
 */

#ifndef CDPL_MOLPROP_PEOESIGMACHARGECALCULATOR_HPP
#define CDPL_MOLPROP_PEOESIGMACHARGECALCULATOR_HPP

#include <cstddef>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "CDPL/MolProp/APIPrefix.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Atom;
	}

	namespace MolProp
	{

		class MHMOPiChargeCalculator;
		
		/**
		 * \brief PEOESigmaChargeCalculator.
		 * \see [\ref PEOE]
		 */
		class CDPL_MOLPROP_API PEOESigmaChargeCalculator
		{

		  public:
			typedef boost::shared_ptr<PEOESigmaChargeCalculator> SharedPointer;

			static constexpr std::size_t DEF_NUM_ITERATIONS = 20;
			static constexpr double      DEF_DAMPING_FACTOR = 0.48;

			/**
			 * \brief Constructs the \c %PEOESigmaChargeCalculator instance.
			 */
			PEOESigmaChargeCalculator();

			/**
			 * \brief Constructs the \c %PEOESigmaChargeCalculator instance and calculates the sigma charges and
			 *        electronegativities of the atoms in the molecular graph \a molgraph by the \e PEOE method.
			 * \param molgraph The molecular graph for which to perform the calculations.
			 */
			PEOESigmaChargeCalculator(const Chem::MolecularGraph& molgraph);

			/**
			 * \brief Allows to specify the number of charge shifting iterations that have to be performed.
			 * \param num_iter The number of iterations to perform.
			 * \note By default, PEOESigmaChargeCalculator::DEF_NUM_ITERATIONS iterations are performed.
			 */
			void setNumIterations(std::size_t num_iter);

			/**
			 * \brief Returns the number of performed charge shifting iterations.
			 * \return The number of performed iterations.
			 */
			std::size_t getNumIterations() const;

			/**
			 * \brief Allows to specify the applied damping factor.
			 * \param factor The damping factor to apply.
			 * \note The default damping factor is specified by the constant PEOESigmaChargeCalculator::DEF_DAMPING_FACTOR.
			 */
			void setDampingFactor(double factor);

			/**
			 * \brief Returns the applied damping factor.
			 * \return The applied damping factor.
			 */
			double getDampingFactor() const;

			/**
			 * \brief Calculates the sigma charges and electronegativities of the atoms in the molecular graph \a molgraph by the \e PEOE method.
			 * \param molgraph The molecular graph for which to perform the calculations.  
			 */
			void calculate(const Chem::MolecularGraph& molgraph);

			/**
			 * \brief Returns the calculated sigma charge of the atom with index \a idx.
			 * \param idx The index of the atom for which to return the charge.
			 * \throw Base::IndexError If \a idx is not in the range <i>[0, NA - 1]</i> where <i>NA</i> is the
			 *        number of atoms of the molecular graph for which the calculations have been performed.
			 */
			double getCharge(std::size_t idx) const;

			/**
			 * \brief Returns the calculated sigma electronegativity of the atom with index \a idx.
			 * \param idx The index of the atom for which to return the electronegativity.
			 * \throw Base::IndexError If \a idx is not in the range <i>[0, NA - 1]</i> where <i>NA</i> is the
			 *        number of atoms of the molecular graph for which the calculations have been performed.
			 */
			double getElectronegativity(std::size_t idx) const;

		  private:
			friend class MHMOPiChargeCalculator;
			
			PEOESigmaChargeCalculator(const PEOESigmaChargeCalculator&);

			PEOESigmaChargeCalculator& operator=(const PEOESigmaChargeCalculator&);

			void init(const Chem::MolecularGraph& molgraph);
			void calcCharges();

			double getNbrElectronegativityAvg(std::size_t idx) const;
			
			class AtomState
		    {

			  public:
				typedef boost::shared_ptr<AtomState> SharedPointer;

				AtomState();
				AtomState(const Chem::Atom&, const Chem::MolecularGraph&);

				void linkTo(AtomState* nbr_state);

				double getCharge() const;
				double getElectronegativity() const;

				void shiftCharges(double att_fact);
				void updateElectronegativity();

				double getNbrElectronegativityAvg() const;
				
			 private:
				typedef std::vector<AtomState*> AtomStateList;

				AtomStateList  nbrAtomStates;
				double         a;
				double         b;
				double         c;
				double         enegativity;
				double         enegativityP1;
				double         charge;
			};

			typedef std::vector<AtomState::SharedPointer> AtomStateList;
		
			std::size_t    numIterations;
			double         dampingFactor;
			AtomStateList  atomStates;
			AtomStateList  implHStates;
		};
	}
}

#endif // CDPL_MOLPROP_PEOESIGMACHARGECALCULATOR_HPP
