/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Raw3DStructureGenerator.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::Raw3DStructureGenerator.
 */

#ifndef CDPL_CONFGEN_RAW3DSTRUCTUREGENERATOR_HPP
#define CDPL_CONFGEN_RAW3DSTRUCTUREGENERATOR_HPP

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/DGConstraintGenerator.hpp"
#include "CDPL/Chem/Hydrogen3DCoordinatesGenerator.hpp"
#include "CDPL/Util/DGCoordinatesGenerator.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		/**
		 * \addtogroup CDPL_CONFGEN_UTILITIES
		 * @{
		 */

		class CDPL_CONFGEN_API Raw3DStructureGenerator
		{

		public:
			Raw3DStructureGenerator();

			void regardAtomConfiguration(bool regard);

			bool atomConfigurationRegarded() const;

			void regardBondConfiguration(bool regard);

			bool bondConfigurationRegarded() const;

			void calculateHydrogenPositions(bool calc);

			bool hydrogenPositionsCalculated() const;

			void setup(const Chem::MolecularGraph& molgraph);
			void setup(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData& ia_data);

			bool generate(Math::Vector3DArray& coords);

		private:
			void setup(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData* ia_data);

			void calcHydrogenCoordinates(Math::Vector3DArray& coords);

			bool checkAtomConfigurations(Math::Vector3DArray& coords) const;
			bool checkBondConfigurations(Math::Vector3DArray& coords) const;

			const Math::Vector3D& get3DCoordinates(const Chem::Atom& atom) const;
			bool has3DCoordinates(const Chem::Atom& atom) const;

			const Chem::MolecularGraph*          molGraph;
			Math::Vector3DArray*                 currCoords;
			DGConstraintGenerator                dgConstraintsGen;
			Util::DG3DCoordinatesGenerator       phase1CoordsGen;
			Util::DG3DCoordinatesGenerator       phase2CoordsGen;
			Chem::Hydrogen3DCoordinatesGenerator hCoordsGen;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_RAW3DSTRUCTUREGENERATOR_HPP
