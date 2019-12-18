/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DGStructureGenerator.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::DGStructureGenerator.
 */

#ifndef CDPL_CONFGEN_DGSTRUCTUREGENERATOR_HPP
#define CDPL_CONFGEN_DGSTRUCTUREGENERATOR_HPP

#include <cstddef>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/DGConstraintGenerator.hpp"
#include "CDPL/ConfGen/DGStructureGeneratorSettings.hpp"
#include "CDPL/Util/DGCoordinatesGenerator.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		/**
		 * \addtogroup CDPL_CONFGEN_HELPERS
		 * @{
		 */

		class CDPL_CONFGEN_API DGStructureGenerator
		{

		public:
			DGStructureGenerator();

			DGStructureGeneratorSettings& getSettings();

			const DGStructureGeneratorSettings& getSettings() const;

			const Util::BitSet& getExcludedHydrogenMask() const;

			void setup(const Chem::MolecularGraph& molgraph);
			void setup(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData& ia_data);

			bool generate(Math::Vector3DArray& coords);

			bool checkAtomConfigurations(Math::Vector3DArray& coords) const;
			bool checkBondConfigurations(Math::Vector3DArray& coords) const;

			std::size_t getNumAtomStereoCenters() const;
			std::size_t getNumBondStereoCenters() const;

			const DGConstraintGenerator& getConstraintGenerator() const;

		private:
			void setup(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData* ia_data);

			typedef boost::random::mt11213b RandNumEngine;

			const Chem::MolecularGraph*    molGraph;
			DGConstraintGenerator          dgConstraintsGen;
			Util::DG3DCoordinatesGenerator phase1CoordsGen;
			Util::DG3DCoordinatesGenerator phase2CoordsGen;
			RandNumEngine                  randomEngine;
			DGStructureGeneratorSettings   settings;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_DGSTRUCTUREGENERATOR_HPP
