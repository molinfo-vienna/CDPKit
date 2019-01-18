/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SystematicConformerGenerator.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::SystematicConformerGenerator.
 */

#ifndef CDPL_CONFGEN_SYSTEMATICCONFORMERGENERATOR_HPP
#define CDPL_CONFGEN_SYSTEMATICCONFORMERGENERATOR_HPP

#include <memory>
#include <cstddef>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/TorsionLibrary.hpp"
#include "CDPL/ConfGen/FragmentLibrary.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
	}

    namespace ConfGen 
    {

		class SystematicConformerGeneratorImpl;

		/**
		 * \addtogroup CDPL_CONFGEN_GENERATORS
		 * @{
		 */

		class CDPL_CONFGEN_API SystematicConformerGenerator
		{

		public:
			class Settings 
			{
				
			public:
				static const std::size_t  DEF_TIMEOUT             = 60 * 60 * 1000;
				static const std::size_t  DEF_MAX_FRAG_BUILD_TIME = 10 * 60 * 1000;
				static const double       DEF_ENERGY_WINDOW;

				Settings();

				void enableHydrogenRotors(bool enable);
				
				bool hydrogenRotorsEnabled() const;

				void enumerateRings(bool enumerate);

				bool ringsEnumerated() const;

				void reuseExistingCoordinates(bool reuse);

				bool existingCoordinatesReused() const;

				void setEnergyWindow(double win_size);

				double getEnergyWindow() const;

				void setTimeout(std::size_t mil_secs);

				std::size_t getTimeout() const;

				void setMaxFragmentBuildTime(std::size_t mil_secs);

				std::size_t getMaxFragmentBuildTime() const;

				void setFragmentLibrary(const FragmentLibrary::SharedPointer& lib);

				const FragmentLibrary::SharedPointer& getFragmentLibrary() const;

				void setTorsionLibrary(const TorsionLibrary::SharedPointer& lib);

				const TorsionLibrary::SharedPointer& getTorsionLibrary() const;

			private:
				bool                           hRotors;
				bool                           enumRings;
				bool                           reuseExistingCoords;
				double                         eWindow;
				std::size_t                    timeout;
				std::size_t                    maxFragBuildTime;
				FragmentLibrary::SharedPointer fragLib;
				TorsionLibrary::SharedPointer  torLib;
			};

			enum Status
			{

			    SUCCESS,
				ERROR,
				TIMEOUT_EXCEEDED
			};

			SystematicConformerGenerator();
	
			void applySettings(const Settings& settings);

			const Settings& getSettings() const;

			Status generate(const Chem::MolecularGraph& molgraph);

		private:
			SystematicConformerGenerator(const SystematicConformerGenerator&);

			SystematicConformerGenerator& operator=(const SystematicConformerGenerator&);

			typedef std::auto_ptr<SystematicConformerGeneratorImpl> ImplementationPointer;

			ImplementationPointer impl;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_SYSTEMATICCONFORMERGENERATOR_HPP
