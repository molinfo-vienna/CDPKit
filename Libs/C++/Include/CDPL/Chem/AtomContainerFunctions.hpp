/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::AtomContainer instances.
 */

#ifndef CDPL_CHEM_ATOMCONTAINERFUNCTIONS_HPP
#define CDPL_CHEM_ATOMCONTAINERFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MassComposition.hpp"
#include "CDPL/Chem/ElementHistogram.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL 
{

	namespace Chem 
	{
	
		class AtomContainer;

		/**
		 * \addtogroup CDPL_CHEM_ATOM_CONTAINER_FUNCTIONS
		 * @{
		 */

		CDPL_CHEM_API std::size_t getExplicitAtomCount(const AtomContainer& cntnr);

		CDPL_CHEM_API std::size_t getExplicitAtomCount(const AtomContainer& cntnr, unsigned int type);

		CDPL_CHEM_API std::size_t getExplicitChainAtomCount(const AtomContainer& cntnr);

		CDPL_CHEM_API std::size_t getRingAtomCount(const AtomContainer& cntnr);

		CDPL_CHEM_API std::size_t getAromaticAtomCount(const AtomContainer& cntnr);

		CDPL_CHEM_API std::size_t getHeavyAtomCount(const AtomContainer& cntnr);


		CDPL_CHEM_API long calcFormalCharge(const AtomContainer& cntnr);

		CDPL_CHEM_API double calcExplicitMass(const AtomContainer& cntnr);

		CDPL_CHEM_API void calcExplicitMassComposition(const AtomContainer& cntnr, MassComposition& mass_comp);

		CDPL_CHEM_API void buildExplicitMassCompositionString(const AtomContainer& cntnr, std::string& comp_str);

		CDPL_CHEM_API void buildExplicitMolecularFormula(const AtomContainer& cntnr, std::string& formula);

		CDPL_CHEM_API void buildExplicitElementHistogram(const AtomContainer& cntnr, ElementHistogram& hist);


		CDPL_CHEM_API void calcGeometricalDistanceMatrix(const AtomContainer& cntnr, Math::DMatrix& mtx);

		CDPL_CHEM_API double calcGeometricalRadius(const AtomContainer& cntnr);

		CDPL_CHEM_API double calcGeometricalDiameter(const AtomContainer& cntnr);


		CDPL_CHEM_API bool hasCoordinates(const AtomContainer& cntnr, std::size_t dim);

		CDPL_CHEM_API void get2DCoordinates(const AtomContainer& cntnr, Math::Vector2DArray& coords);

		CDPL_CHEM_API void set2DCoordinates(AtomContainer& cntnr, const Math::Vector2DArray& coords);

		CDPL_CHEM_API void get3DCoordinates(const AtomContainer& cntnr, Math::Vector3DArray& coords);

		CDPL_CHEM_API void set3DCoordinates(AtomContainer& cntnr, const Math::Vector3DArray& coords);	


		CDPL_CHEM_API void setActiveConformation(AtomContainer& cntnr, std::size_t conf_idx);	

		CDPL_CHEM_API void getConformationData(const AtomContainer& cntnr, std::size_t conf_idx, Math::Vector3DArray& coords);

		CDPL_CHEM_API void addConformationData(AtomContainer& cntnr, const Math::Vector3DArray& coords);

		CDPL_CHEM_API std::size_t getNumConformations(const AtomContainer& cntnr);


		CDPL_CHEM_API std::size_t getMaxComponentGroupID(const AtomContainer& cntnr);

		CDPL_CHEM_API std::size_t getMaxReactionAtomMappingID(const AtomContainer& cntnr);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_ATOMCONTAINERFUNCTIONS_HPP
 
