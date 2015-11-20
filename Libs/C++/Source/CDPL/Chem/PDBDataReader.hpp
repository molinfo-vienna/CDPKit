/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PDBDataReader.hpp 
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


#ifndef CDPL_CHEM_PDBDATAREADER_HPP
#define CDPL_CHEM_PDBDATAREADER_HPP

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>
#include <list>

#include <boost/unordered_map.hpp>

#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/PDBData.hpp"


namespace CDPL 
{

    namespace Base
    {

		class DataIOBase;
    }

    namespace Chem
    {

		class Molecule;

		class PDBDataReader
		{

		public:
			PDBDataReader(const Base::DataIOBase& io_base): ioBase(io_base) {}

			bool readPDBFile(std::istream&, Molecule&);

			bool skipPDBFile(std::istream&);
		
			bool hasMoreData(std::istream&) const;

		private:
			void init(std::istream&);
			void init(std::istream&, Molecule&);

			std::size_t readGenericDataRecord(std::istream&, std::size_t, PDBData::RecordType, const std::string&);
			void appendRecordData(PDBData::RecordType, const std::string&) const;

			std::size_t skipRecordData(std::istream&, std::size_t, const std::string&) const;

			std::size_t readMODELRecord(std::istream&);
			std::size_t readATOMRecord(std::istream&, Molecule&);
			std::size_t readTERRecord(std::istream&, Molecule&);
			std::size_t readHETATMRecord(std::istream&, Molecule&);
			std::size_t readENDMDLRecord();
			std::size_t readCONECTRecord(std::istream&, Molecule&) const;
			std::size_t readMASTERRecord(std::istream&);

			void readATOMRecord(std::istream&, Molecule&, const std::string&, bool);

			std::size_t startNextRecord(std::istream&, std::string&, std::string&);
			
			void skipInputToNextLine(std::istream&, std::size_t, const std::string&);
			void checkRecordOrder(const std::string&, const std::string&) const;
			void checkMandatoryRecords() const;

			void processAtomSequence(Molecule&, bool);

			void perceiveBondOrders(Molecule&);
			
			typedef std::vector<Atom*> AtomList;
			typedef boost::unordered_map<std::string, std::size_t> RecordHistogram;
			typedef boost::unordered_map<std::size_t, Atom*> SerialToAtomMap;
			typedef boost::unordered_map<std::string, Atom*> NameToAtomMap;

			const Base::DataIOBase& ioBase;
			std::string             stringData;
			bool                    strictErrorChecking;
			bool                    checkLineLength;
			PDBData::SharedPointer  pdbData;
			RecordHistogram         recordHistogram;
			std::size_t             currModelID;
			std::size_t             lastModelID;
			std::size_t             startBondCount;
			std::size_t             numCoordRecords;
			SerialToAtomMap         serialToAtomMap;
			AtomList                atomSequence;
			NameToAtomMap           currResidueAtoms;
			NameToAtomMap           prevResidueAtoms;
			AtomList                currResidueLinkAtoms;
			AtomList                prevResidueLinkAtoms;
			Fragment                readMolGraph;
		};
    }
}

#endif // CDPL_CHEM_PDBDATAREADER_HPP
