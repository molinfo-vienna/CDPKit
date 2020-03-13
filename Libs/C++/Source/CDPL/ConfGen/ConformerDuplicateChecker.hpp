/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConformerDuplicateChecker.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::ConformerDuplicateChecker.
 */

#ifndef CDPL_CONFGEN_CONFORMERDUPLICATECHECKER_HPP
#define CDPL_CONFGEN_CONFORMERDUPLICATECHECKER_HPP

#include <map>

#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/ForceField/MMFF94TorsionInteractionData.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		class ConformerDuplicateChecker
		{

		  public:
			ConformerDuplicateChecker(const ForceField::MMFF94TorsionInteractionData& tor_ia_data);
	
			void setTorsionInteractionData(const ForceField::MMFF94TorsionInteractionData& tor_ia_data);

			const ForceField::MMFF94TorsionInteractionData& setTorsionInteractionData() const;

			void setEnergyTolerance(double tol);

			double getEnergyTolerance() const;

			void setAngleTolerance(double tol);

			double getAngleTolerance() const;

			void reset();

			bool isDuplicate(const Math::Vector3DArray& conf_coords);

		  private:
			typedef std::multimap<double, double> EnergyToAngleMap;
			typedef ForceField::MMFF94TorsionInteractionData TorsionInteractionData;

			double                        energyTol;
			double                        angleTol;
			const TorsionInteractionData* torIActionData;
			EnergyToAngleMap              registeredConfs;
		};
    }
}

#endif // CDPL_CONFGEN_CONFORMERDUPLICATECHECKER_HPP
