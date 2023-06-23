/* 
 * CDFDataReader.hpp 
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


#ifndef CDPL_CHEM_CDFDATAREADER_HPP
#define CDPL_CHEM_CDFDATAREADER_HPP

#include <cstddef>
#include <iosfwd>
#include <vector>
#include <functional>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/CDFFormatData.hpp"
#include "CDPL/Chem/StringDataBlock.hpp"
#include "CDPL/Chem/FragmentList.hpp"

#include "CDPL/Internal/CDFDataReaderBase.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"


namespace CDPL 
{

	namespace Base
	{

		class ControlParameterContainer;
	}

	namespace Chem
	{

		class Reaction;
		class Molecule;
		class Atom;
		class Bond;

		class CDPL_CHEM_API CDFDataReader : public Internal::CDFDataReaderBase
		{

		public:
			typedef std::function<bool(unsigned int, CDFDataReader&, Atom&, Internal::ByteBuffer&)> AtomPropertyHandler;
			typedef std::function<bool(unsigned int, CDFDataReader&, Bond&, Internal::ByteBuffer&)> BondPropertyHandler;
			typedef std::function<bool(unsigned int, CDFDataReader&, Molecule&, Internal::ByteBuffer&)> MoleculePropertyHandler;

			CDFDataReader(const Base::ControlParameterContainer& ctrl_params): ctrlParams(ctrl_params) {}

			bool readMolecule(std::istream& is, Molecule& mol);
			bool readReaction(std::istream& is, Reaction& rxn);

			bool readMolecule(Molecule& mol, Internal::ByteBuffer& bbuf);
			bool readReaction(Reaction& rxn, Internal::ByteBuffer& bbuf);

			bool skipMolecule(std::istream& is);
			bool skipReaction(std::istream& is);

			bool hasMoreMoleculeData(std::istream& is);
			bool hasMoreReactionData(std::istream& is);

			static void registerExternalAtomPropertyHandler(const AtomPropertyHandler& handler);
			static void registerExternalBondPropertyHandler(const BondPropertyHandler& handler);
			static void registerExternalMoleculePropertyHandler(const MoleculePropertyHandler& handler);

			const Base::ControlParameterContainer& getCtrlParameters() const;

		private:
			struct CDFStereoDescr
			{

				CDFStereoDescr(std::size_t obj_idx): objIndex(obj_idx) {}

				std::size_t  objIndex;
				unsigned int config;
				std::size_t  numRefAtoms;
				std::size_t  refAtomInds[4];
			};

			void init();

			void readReactionComponents(Reaction& rxn, Internal::ByteBuffer& bbuf);
			void readConnectionTable(Molecule& mol, Internal::ByteBuffer& bbuf);

			std::size_t readAtoms(Molecule& mol, Internal::ByteBuffer& bbuf);
			void readBonds(Molecule& mol, Internal::ByteBuffer& bbuf, std::size_t num_atoms);
			void readMoleculeProperties(Molecule& mol, Internal::ByteBuffer& bbuf);

			void readReactionProperties(Reaction& rxn, Internal::ByteBuffer& bbuf);

			template <typename T>
			void readExternalProperties(CDF::PropertySpec prop_spec, T& obj, Internal::ByteBuffer& data);

			bool readExternalProperties(unsigned int handler_id, Atom& atom, Internal::ByteBuffer& data);
			bool readExternalProperties(unsigned int handler_id, Bond& bond, Internal::ByteBuffer& data);
			bool readExternalProperties(unsigned int handler_id, Molecule& mol, Internal::ByteBuffer& data);

			FragmentList::SharedPointer readFragmentList(const Molecule& mol, CDF::PropertySpec prop_spec, Internal::ByteBuffer& bbuf) const;
			StringDataBlock::SharedPointer readStringData(CDF::PropertySpec prop_spec, Internal::ByteBuffer& bbuf) const;

			void readStereoDescriptor(CDF::PropertySpec prop_spec, CDFStereoDescr& descr, Internal::ByteBuffer& data) const;
			void setStereoDescriptors(Molecule& mol) const;

			template <typename T>
			void setStereoDescriptor(T& obj, const Molecule& mol, const CDFStereoDescr& descr) const;

			typedef std::vector<CDFStereoDescr> StereoDescrList;
			typedef std::vector<AtomPropertyHandler> AtomPropertyHandlerList;
			typedef std::vector<BondPropertyHandler> BondPropertyHandlerList;
			typedef std::vector<MoleculePropertyHandler> MoleculePropertyHandlerList;

			const Base::ControlParameterContainer& ctrlParams;	
			Internal::ByteBuffer                   dataBuffer;		
			std::size_t                            startAtomIdx;
			StereoDescrList                        atomStereoDescrs;
			StereoDescrList                        bondStereoDescrs;
			static AtomPropertyHandlerList         extAtomPropertyHandlers;
			static BondPropertyHandlerList         extBondPropertyHandlers;
			static MoleculePropertyHandlerList     extMoleculePropertyHandlers;
		};
	}
}

#endif // CDPL_CHEM_CDFDATAREADER_HPP
