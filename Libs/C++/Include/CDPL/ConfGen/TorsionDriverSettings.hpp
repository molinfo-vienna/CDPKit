/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionDriverSettings.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::TorsionDriverSettings.
 */

#ifndef CDPL_CONFGEN_TORSIONDRIVERSETTINGS_HPP
#define CDPL_CONFGEN_TORSIONDRIVERSETTINGS_HPP

#include <cstddef>

#include "CDPL/ConfGen/APIPrefix.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		/**
		 * \addtogroup CDPL_CONFGEN_DATA_STRUCTURES
		 * @{
		 */

		class CDPL_CONFGEN_API TorsionDriverSettings
		{

		  public:
			static const TorsionDriverSettings DEFAULT;

			TorsionDriverSettings();

			void sampleHeteroAtomHydrogens(bool sample);
				
			bool sampleHeteroAtomHydrogens() const;

			void sampleAngleToleranceRanges(bool sample);
				
			bool sampleAngleToleranceRanges() const;

			void orderByEnergy(bool order);

			bool orderByEnergy() const;

			void setEnergyWindow(double win_size);

			double getEnergyWindow() const;

			void setMaxPoolSize(std::size_t max_size);

			std::size_t getMaxPoolSize() const;

			void setForceFieldType(unsigned int type);
	    
			unsigned int getForceFieldType() const;
			
			void strictForceFieldParameterization(bool strict);

			bool strictForceFieldParameterization() const;

			void setDielectricConstant(double de_const);

			double getDielectricConstant() const;

			void setDistanceExponent(double exponent);

			double getDistanceExponent() const;

		  private:
			bool         sampleHetAtomHs;
			bool         sampleTolRanges;
			bool         energyOrdered;
			double       eWindow;
			std::size_t  maxPoolSize;
			unsigned int forceFieldType;
			bool         strictParam;
			double       dielectricConst;
			double       distExponent;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_TORSIONDRIVERSETTINGS_HPP
