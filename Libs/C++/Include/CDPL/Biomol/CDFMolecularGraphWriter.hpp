/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFMolecularGraphWriter.hpp 
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
 * \brief Definition of the class CDPL::Biomol::CDFMolecularGraphWriter.
 */

#ifndef CDPL_BIOMOL_CDFMOLECULARGRAPHWRITER_HPP
#define CDPL_BIOMOL_CDFMOLECULARGRAPHWRITER_HPP

#include <memory>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
	}

	namespace Biomol
	{

		class CDFDataWriter;

		/**
		 * \addtogroup CDPL_BIOMOL_CDF_IO
		 * @{
		 */

		/**
		 * \brief A writer for molecular graph data in the native I/O format of the <em>CDPL</em>.
		 */
		class CDPL_BIOMOL_API CDFMolecularGraphWriter : public Base::DataWriter<Chem::MolecularGraph>
		{

		public:
			/**
			 * \brief Constructs a \c %CDFMolecularGraphWriter instance that will write data of molecular graphs to the output
			 *        stream \a os.
			 * \param os The output stream to write to.
			 */
			CDFMolecularGraphWriter(std::ostream& os);

			/**
			 * \brief Destructor.
			 */
			~CDFMolecularGraphWriter();

			/**
			 * \brief Writes data of the molecular graph \a molgraph to the output stream specified in the constructor.
			 * \param molgraph The molecular graph to write.
			 * \return A reference to itself.
			 */
			Base::DataWriter<Chem::MolecularGraph>& write(const Chem::MolecularGraph& molgraph);

			operator const void*() const;
			bool operator!() const;

		private:
			typedef std::auto_ptr<CDFDataWriter> CDFDataWriterPtr;

			CDFMolecularGraphWriter(const CDFMolecularGraphWriter&);

			std::ostream&    output;
			bool             state;
			CDFDataWriterPtr writer;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_BIOMOL_CDFMOLECULARGRAPHWRITER_HPP
