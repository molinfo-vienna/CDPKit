/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibraryGenerator.hpp 
 *
 * This file is part of the ConfGenical Data Processing Toolkit
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
 * \brief Definition of the class CDPL::ConfGen::FragmentLibraryGenerator.
 */

#ifndef CDPL_CONFGEN_FRAGMENTLIBRARYGENERATOR_HPP
#define CDPL_CONFGEN_FRAGMENTLIBRARYGENERATOR_HPP

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/FragmentLibrary.hpp"
#include "CDPL/ConfGen/FragmentLibraryEntry.hpp"
#include "CDPL/ConfGen/FragmentConformerGenerator.hpp"
#include "CDPL/Chem/SmallestSetOfSmallestRings.hpp"
#include "CDPL/Chem/Molecule.hpp"


namespace CDPL 
{

    namespace ConfGen
    {

		/**
		 * \addtogroup CDPL_CONFGEN_HELPERS
		 * @{
		 */

		/**
		 * \brief FragmentLibraryGenerator.
		 */
		class CDPL_CONFGEN_API FragmentLibraryGenerator
		{

		  public:
			FragmentLibraryGenerator();

			FragmentLibraryGenerator(const FragmentLibrary::SharedPointer& lib);

			void setFragmentLibrary(const FragmentLibrary::SharedPointer& lib);

			const FragmentLibrary::SharedPointer& getFragmentLibrary() const;

			FragmentConformerGeneratorSettings& getSettings();

			const FragmentConformerGeneratorSettings& getSettings() const;

			void setAbortCallback(const CallbackFunction& func);

			const CallbackFunction& getAbortCallback() const;

			void setTimeoutCallback(const CallbackFunction& func);

			const CallbackFunction& getTimeoutCallback() const;

			unsigned int process(const Chem::MolecularGraph& frag);
	
			std::size_t getNumGeneratedConformers() const;

			Base::uint64 getLibraryEntryHashCode() const;

		  private:
			FragmentLibraryGenerator(const FragmentLibraryGenerator&);

			FragmentLibraryGenerator& operator=(const FragmentLibraryGenerator&);

			Chem::Molecule::SharedPointer addNewLibraryEntry(const Chem::MolecularGraph& frag);

			void removeNewLibraryEntry() const;

			FragmentLibrary::SharedPointer                  fragLib;
			FragmentLibraryEntry                            fragLibEntry;
			FragmentConformerGenerator                      fragConfGen;
			Chem::SmallestSetOfSmallestRings::SharedPointer fragSSSR;
			std::size_t                                     numGenConfs;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_FRAGMENTLIBRARYGENERATOR_HPP
