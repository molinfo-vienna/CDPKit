/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDataWriter.hpp 
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


#ifndef CDPL_CHEM_CDFDATAWRITER_HPP
#define CDPL_CHEM_CDFDATAWRITER_HPP

#include <iosfwd>

#include "CDPL/Chem/CDFFormatData.hpp"
#include "CDPL/Internal/CDFDataWriterBase.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"


namespace CDPL 
{

	namespace Base
	{

		class DataIOBase;
	}

	namespace Chem
	{

		class MolecularGraph;

		class CDFDataWriter : private Internal::CDFDataWriterBase
		{

		public:
			CDFDataWriter(const Base::DataIOBase& io_base): ioBase(io_base) {}

			bool writeMolGraph(std::ostream& os, const MolecularGraph& molgraph);

		private:
			void init();

			void outputMolGraphHeader(const MolecularGraph& molgraph);
			void outputAtoms(const MolecularGraph& molgraph);
			void outputBonds(const MolecularGraph& molgraph);
			void outputMolGraphProperties(const MolecularGraph& molgraph);

			bool writeRecordData(std::ostream& os);

			const Base::DataIOBase& ioBase;	
			Internal::ByteBuffer    dataBuffer;
			CDF::Header             cdfHeader;
		};
	}
}

#endif // CDPL_CHEM_CDFDATAWRITER_HPP
