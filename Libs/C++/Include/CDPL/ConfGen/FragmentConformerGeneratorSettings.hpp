/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentConformerGeneratorSettings.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::FragmentConformerGeneratorSettings.
 */

#ifndef CDPL_CONFGEN_FRAGMENTCONFORMERGENERATORSETTINGS_HPP
#define CDPL_CONFGEN_FRAGMENTCONFORMERGENERATORSETTINGS_HPP

#include <cstddef>

#include "CDPL/ConfGen/APIPrefix.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		class CDPL_CONFGEN_API FragmentConformerGeneratorSettings
		{

		  public:
			static const FragmentConformerGeneratorSettings DEFAULT;
			static const FragmentConformerGeneratorSettings FAST;
			static const FragmentConformerGeneratorSettings THOROUGH;

			class CDPL_CONFGEN_API FragmentSettings
			{
		
			public:
				FragmentSettings();

				void setMaxNumSampledConformers(std::size_t max_num);

				std::size_t getMaxNumSampledConformers() const;

				void setMinNumSampledConformers(std::size_t min_num);

				std::size_t getMinNumSampledConformers() const;

				void setTimeout(std::size_t mil_secs);

				std::size_t getTimeout() const;

				void setEnergyWindow(double win_size);

				double getEnergyWindow() const;

				void setMaxNumOutputConformers(std::size_t max_num);

				std::size_t getMaxNumOutputConformers() const;

				void setMinRMSD(double min_rmsd);

				double getMinRMSD() const;

			private:
				std::size_t maxNumSampledConfs;
				std::size_t minNumSampledConfs;
				std::size_t maxNumOutputConfs;
				std::size_t timeout;				
				double      eWindow;
				double      minRMSD;
			};

			FragmentConformerGeneratorSettings();
	
			virtual ~FragmentConformerGeneratorSettings() {}

			void preserveInputBondingGeometries(bool preserve);

			bool preserveInputBondingGeometries() const;

			void setForceFieldType(unsigned int type);
	    
			unsigned int getForceFieldType() const;

			void strictForceFieldParameterization(bool strict);

			bool strictForceFieldParameterization() const;

			void setDielectricConstant(double de_const);

			double getDielectricConstant() const;

			void setDistanceExponent(double exponent);

			double getDistanceExponent() const;

			void setMaxNumRefinementIterations(std::size_t max_iter);

			std::size_t getMaxNumRefinementIterations() const;

			void setRefinementStopGradient(double grad_norm);

			double getRefinementStopGradient() const;

			void setMacrocycleRotorBondCountThreshold(std::size_t min_count);

			std::size_t getMacrocycleRotorBondCountThreshold() const;

			FragmentSettings& getChainSettings();

			const FragmentSettings& getChainSettings() const;

			FragmentSettings& getMacrocycleSettings();

			const FragmentSettings& getMacrocycleSettings() const;

			FragmentSettings& getSmallRingSystemSettings();

			const FragmentSettings& getSmallRingSystemSettings() const;

			void setSmallRingSystemSamplingFactor(std::size_t factor);

			std::size_t getSmallRingSystemSamplingFactor() const;

		  private:
			bool                 preserveBondGeom;
			unsigned int         forceFieldType;
			bool                 strictParam;
			double               dielectricConst;
			double               distExponent;
			std::size_t          maxNumRefIters;
			double               refStopGrad;
			std::size_t          mcRotorBondCountThresh;
			std::size_t          srSamplingFactor;
			FragmentSettings     chainSettings;
			FragmentSettings     mcSettings;
			FragmentSettings     srSettings;
		};
    }
}

#endif // CDPL_CONFGEN_FRAGMENTCONFORMERGENERATORSETTINGS_HPP
