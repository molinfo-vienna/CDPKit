/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * LogSReg.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <fstream>
#include <iostream>

#include <boost/lexical_cast.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/SDFMoleculeReader.hpp"
#include "CDPL/Chem/LogSCalculator.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Math/MLRModel.hpp"


int main(int argc, char** argv)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace Math;

	if (argc != 4) {
		std::cerr << "Calculation of LogS regression coefficients for a given training dataset" << std::endl << std::endl
				  << "Usage: " << argv[0] << " [structures] [experimental logS data] [regression coeff. file]" << std::endl;

		return 1;
	}

	try {
		std::ifstream struct_is(argv[1]);

		if (!struct_is) {
			std::cerr << "Error: couldn't open structure file" << std::endl;
			return 1;
		}

		std::ifstream exp_logs_is(argv[2]);

		if (!exp_logs_is) {
			std::cerr << "Error: couldn't open exp. logS data file" << std::endl;
			return 1;
		}

		std::ofstream coeff_os(argv[3]);

		if (!coeff_os) {
			std::cerr << "Error: couldn't open regression coefficient destination file" << std::endl;
			return 1;
		}

		MLRModel<> mlr_model;
		SDFMoleculeReader sdf_reader(struct_is);
		BasicMolecule mol;
		LogSCalculator logs_calc;

		while (sdf_reader.read(mol)) {
			double exp_logs; 
			
			exp_logs_is >> exp_logs;

			perceiveComponents(mol, false);
			perceiveSSSR(mol, false);
			setRingFlags(mol, false);
			calcImplicitHydrogenCounts(mol, false);
			perceiveHybridizationStates(mol, false);
			setAromaticityFlags(mol, false);
			calcTopologicalDistanceMatrix(mol, false);

			logs_calc.calculate(mol);

			mlr_model.addXYData(logs_calc.getFeatureVector(), exp_logs);

			mol.clear();
		}

		mlr_model.buildModel();
		mlr_model.calcStatistics();

		std::cout << "Model Statistics:" << std::endl;
		std::cout << "----------------------------------" << std::endl;
		std::cout << " Correlation Coeff.: " << mlr_model.getCorrelationCoefficient() << std::endl;
		std::cout << " Goodness of Fit:    " << mlr_model.getGoodnessOfFit() << std::endl;
		std::cout << " Standard Deviation: " << mlr_model.getStandardDeviation() << std::endl;
		std::cout << " Chi Square:         " << mlr_model.getChiSquare() << std::endl;

		for (std::size_t i = 0; i < LogSCalculator::FEATURE_VECTOR_SIZE; i++)
			coeff_os << mlr_model.getCoefficients()(i) << ',' << std::endl;

		return 0;

	} catch (std::exception& e) {
		std::cerr << ": " << e.what() << std::endl;
		return 1;
	}
}

