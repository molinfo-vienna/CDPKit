/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMTFDataReader.hpp 
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


#ifndef CDPL_CHEM_MMTFDATAREADER_HPP
#define CDPL_CHEM_MMTFDATAREADER_HPP

#include <iosfwd>
#include <vector>
#include <cstddef>

#include <msgpack.hpp>
#include <mmtf.hpp>


namespace CDPL 
{

    namespace Base
    {

		class DataIOBase;
    }

    namespace Chem
    {

		class Molecule;
		class Atom;
    }

    namespace Biomol
    {

		class MMTFDataReader
		{

		public:
			MMTFDataReader(const Base::DataIOBase& io_base): ioBase(io_base) {}

			bool readRecord(std::istream& is, Chem::Molecule& mol);

			bool skipRecord(std::istream& is);
		
			bool hasMoreData(std::istream& is) const;

		private:
			bool readRecordData(std::istream& is, msgpack::object_handle& handle);

			void buildMolecule(Chem::Molecule& mol);
			
			void addBond(Chem::Molecule& mol, std::size_t atom1_idx, std::size_t atom2_idx, std::size_t order) const;

			typedef std::vector<Chem::Atom*> AtomArray;

			const Base::DataIOBase& ioBase;
			AtomArray               atoms;
			mmtf::StructureData     structData;
		};
    }
}

#endif // CDPL_CHEM_MMTFDATAREADER_HPP
