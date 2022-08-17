/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PSDMolecularGraphWriter.hpp 
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
 * \brief Definition of the class CDPL::Pharm::PSDMolecularGraphWriter.
 */

#ifndef CDPL_PHARM_PSDMOLECULARGRAPHWRITER_HPP
#define CDPL_PHARM_PSDMOLECULARGRAPHWRITER_HPP

#include <string>
#include <iosfwd>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/PSDScreeningDBCreator.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class MolecularGraph;
    }

    namespace Pharm
    {

		/**
		 * \brief A writer for molecular graph data in the PSD-format of the <em>CDPL</em>.
		 */
		class CDPL_PHARM_API PSDMolecularGraphWriter : public Base::DataWriter<Chem::MolecularGraph>
		{

		  public:
			/**
			 * \brief Constructs a \c %PSDMolecularGraphWriter instance that will write the molecular graph data to the 
			 *        I/O stream \a ios.
			 * \param ios The I/O stream to write to.
			 */
			PSDMolecularGraphWriter(std::iostream& ios);

			/**
			 * \brief Constructs a \c %PSDMolecularGraphWriter instance that will write the molecular graph data to the output
			 *        file \a file_name.
			 * \param file_name The output file to write to.
			 */
			PSDMolecularGraphWriter(const std::string& file_name);

			~PSDMolecularGraphWriter();

			PSDMolecularGraphWriter& write(const Chem::MolecularGraph& molgraph);

			void close();

			operator const void*() const;
			bool operator!() const;

		  private:
			PSDScreeningDBCreator  creator;
			std::iostream*         output;
			std::streampos         outputPos;
			bool                   state;
			bool                   closed;
		};
    }
}

#endif // CDPL_PHARM_PSDMOLECULARGRAPHWRITER_HPP
