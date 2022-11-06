/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ModifiedHueckelMOCalculator.hpp 
 * 
 * Modified Hueckel Molecular Orbital calculation of various pi electron system properties
 * (according to T. Kleinöder, PhD Thesis, FAU Erlangen-Nuremberg, 2005) 
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
 * \brief Definition of the class CDPL::MolProp::ModifiedHueckelMOCalculator.
 */

#ifndef CDPL_MOLPROP_PEOESIGMACHARGECALCULATOR_HPP
#define CDPL_MOLPROP_PEOESIGMACHARGECALCULATOR_HPP

#include <vector>
#include <cstddef>

#include <boost/shared_ptr.hpp>

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/Chem/ElectronSystemList.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Base/IntegerTypes.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class MolecularGraph;
		class Bond;
    }

    namespace MolProp
    {

		/**
		 * \brief ModifiedHueckelMOCalculator.
		 * \see [\ref MHMO]
		 */
		class CDPL_MOLPROP_API ModifiedHueckelMOCalculator
		{

		  public:
			typedef boost::shared_ptr<ModifiedHueckelMOCalculator> SharedPointer;

			ModifiedHueckelMOCalculator();

			ModifiedHueckelMOCalculator(const Chem::MolecularGraph& molgraph);

			ModifiedHueckelMOCalculator(const Chem::ElectronSystemList& pi_sys_list, const Chem::MolecularGraph& molgraph);

			void localizedPiBonds(bool localized);

			bool localizedPiBonds() const;
			
			void calculate(const Chem::MolecularGraph& molgraph);

			void calculate(const Chem::ElectronSystemList& pi_sys_list, const Chem::MolecularGraph& molgraph);

			double getPiElectronDensity(std::size_t atom_idx) const;

			double getPiBondOrder(std::size_t bond_idx) const;

			double getEnergy() const;
			
		  private:
			void getAtomPiSysCounts(const Chem::ElectronSystemList& pi_sys_list, const Chem::MolecularGraph& molgraph);

			void calcForPiSys(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph);
			
			void getInvolvedBonds(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph);
			void initHueckelMatrix(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph);

			double getAlpha(const Chem::Atom& atom, const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph) const;
			double getAlphaCorrection(const Chem::Atom& atom, const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph) const;
			double getBeta(const Chem::Bond& bond, const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph) const;

			Base::uint64 getAtomID(const Chem::Atom& atom, const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph) const;
			Base::uint64 getBondID(const Chem::Bond& bond, const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph) const;

			bool diagHueckelMatrix();
			void distElectrons(const Chem::ElectronSystem& pi_sys);
			void updateEnergy();
			void updateAtomElecDensities(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph);
			void updateBondElecDensities(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph);

			double calcElecDensity(std::size_t i, std::size_t j) const;
			
			struct MODescr
		    {

				double energy;
				double coeffVecIndex;
				double elecCount;
			};
			
			typedef Math::Matrix<double> Matrix;
			typedef Math::Vector<double> Vector;
			typedef std::vector<const Chem::Bond*> BondList;
			typedef std::vector<std::size_t> CountsArray;
			typedef std::vector<double> DoubleArray;
			typedef std::vector<MODescr> MODescrArray;
			typedef std::vector<MODescr*> MODescrPtrArray;
			
			Matrix          hueckelMatrix;
			Matrix          hmEigenVectors;
			Vector          hmEigenValues;
			BondList        piSysBonds;
			CountsArray     atomPiSysCounts;
			MODescrArray    moDescriptors;
			MODescrPtrArray moDescriptorPtrs;
			bool            locPiBonds;
			DoubleArray     atomElecDensities;
			DoubleArray     bondElecDensities;
			double          energy;
		};
    }
}

#endif // CDPL_MOLPROP_PEOESIGMACHARGECALCULATOR_HPP