/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFFragmentLibraryDataReader.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CDFFragmentLibraryDataReader.hpp"
#include "CDFMoleculeDataFunctions.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


namespace
{

	class CDFMoleculeDataHolder : public Chem::MolecularGraph
	{

		const Chem::Atom& getAtom(std::size_t idx) const {
			throw Base::IndexError("CDFMoleculeDataHolder: atom index out of bounds");
		}
		
		Chem::Atom& getAtom(std::size_t idx) {
			throw Base::IndexError("CDFMoleculeDataHolder: atom index out of bounds");
		}

		bool containsAtom(const Chem::Atom& atom) const {
			return false;
		}

		std::size_t getAtomIndex(const Chem::Atom& atom) const {
			throw Base::ItemNotFound("CDFMoleculeDataHolder: argument atom not part of the molecule");
		}

		std::size_t getNumAtoms() const {
			return 0;
		}

		std::size_t getNumEntities() const {
			return 0;
		}

		const Chem::Entity3D& getEntity(std::size_t idx) const {
			throw Base::IndexError("CDFMoleculeDataHolder: entity index out of bounds");
		}

		Chem::Entity3D& getEntity(std::size_t idx) {
			throw Base::IndexError("CDFMoleculeDataHolder: entity index out of bounds");
		}

		std::size_t getNumBonds() const {
			return 0;
		}
	    
		const Chem::Bond& getBond(std::size_t idx) const {
			throw Base::IndexError("CDFMoleculeDataHolder: bond index out of bounds");
		}

		Chem::Bond& getBond(std::size_t idx) {
			throw Base::IndexError("CDFMoleculeDataHolder: bond index out of bounds");
		}

		bool containsBond(const Chem::Bond& bond) const {
			return false;
		}

		std::size_t getBondIndex(const Chem::Bond& bond) const {
			throw Base::ItemNotFound("CDFMoleculeDataHolder: argument bond not part of the molecule");
		}
	};
}


bool ConfGen::CDFFragmentLibraryDataReader::read(std::istream& is, FragmentLibrary::Entry& entry)
{
    CDF::Header header;

	strictErrorChecking(true);

    if (!skipToRecord(is, header, CDF::FRAGLIB_DATA_RECORD_ID, false, entryInfoBuffer))
		return false;
  
    readData(is, header.recordDataLength, entryInfoBuffer);

    entryInfoBuffer.setIOPointer(0);
    entryInfoBuffer.getInt(const_cast<Base::uint64&>(entry.first));

	Base::uint64 mol_data_length;

    entryInfoBuffer.getInt(mol_data_length);

    MoleculeDataPointer mol_data_ptr(new Internal::ByteBuffer(mol_data_length));

    readData(is, mol_data_length, *mol_data_ptr);

    entry.second.reset(new CDFMoleculeDataHolder());

    setCDFMoleculeData(*entry.second, mol_data_ptr);

    return true;
}
