/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StericAtomClashFactorCalculator.hpp 
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
 * \brief Definition of the class CDPL::Pharm::StericAtomClashFactorCalculator.
 */

#ifndef CDPL_PHARM_STERICATOMCLASHFACTORCALCULATOR_HPP
#define CDPL_PHARM_STERICATOMCLASHFACTORCALCULATOR_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class AtomContainer;
    }

    namespace Pharm
    {

		/**
		 * \addtogroup CDPL_PHARM_FUNCTORS
		 * @{
		 */

		/**
		 * \brief StericAtomClashFactorCalculator.
		 */
		class CDPL_PHARM_API StericAtomClashFactorCalculator
		{

		  public:
			static const double DEF_PROBE_RADIUS;

			StericAtomClashFactorCalculator(double probe_radius = DEF_PROBE_RADIUS): probeRadius(probe_radius) {}

			double getProbeRadius() const;

			double operator()(const Math::Vector3D& pos, const Chem::AtomContainer& atoms, const Chem::Atom3DCoordinatesFunction& coords_func) const;

		  private:
			double probeRadius;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_STERICATOMCLASHFACTORCALCULATOR_HPP
