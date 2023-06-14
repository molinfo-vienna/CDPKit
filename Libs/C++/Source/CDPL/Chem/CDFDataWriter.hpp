/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDataWriter.hpp 
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


#ifndef CDPL_CHEM_CDFDATAWRITER_HPP
#define CDPL_CHEM_CDFDATAWRITER_HPP

#include <iosfwd>
#include <vector>
#include <functional>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/StringDataBlock.hpp"
#include "CDPL/Chem/FragmentList.hpp"

#include "CDPL/Internal/CDFDataWriterBase.hpp"
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
		class MolecularGraph;
		class Atom;
		class Bond;
		class StereoDescriptor;

		class CDPL_CHEM_API CDFDataWriter : public Internal::CDFDataWriterBase
		{

		  public:
			typedef std::function<unsigned int(CDFDataWriter&, const Atom&, Internal::ByteBuffer&)> AtomPropertyHandler;
			typedef std::function<unsigned int(CDFDataWriter&, const Bond&, Internal::ByteBuffer&)> BondPropertyHandler;
			typedef std::function<unsigned int(CDFDataWriter&, const MolecularGraph&, Internal::ByteBuffer&)> MolGraphPropertyHandler;

			CDFDataWriter(const Base::ControlParameterContainer& ctrl_params): ctrlParams(ctrl_params) {}

			bool writeMolGraph(std::ostream& os, const MolecularGraph& molgraph);
			void writeMolGraph(const MolecularGraph& molgraph, Internal::ByteBuffer& bbuf);

			bool writeReaction(std::ostream& os, const Reaction& rxn);
			void writeReaction(const Reaction& rxn, Internal::ByteBuffer& bbuf);

			static void registerExternalAtomPropertyHandler(const AtomPropertyHandler& handler);
			static void registerExternalBondPropertyHandler(const BondPropertyHandler& handler);
			static void registerExternalMolGraphPropertyHandler(const MolGraphPropertyHandler& handler);

			const Base::ControlParameterContainer& getCtrlParameters() const;

		  private:
			void init();

			void outputHeader(std::uint8_t type_id, Internal::ByteBuffer& bbuf) const;

			void writeConnectionTable(const MolecularGraph& molgraph, Internal::ByteBuffer& bbuf);

			void outputAtoms(const MolecularGraph& molgraph, Internal::ByteBuffer& bbuf);
			void outputBonds(const MolecularGraph& molgraph, Internal::ByteBuffer& bbuf);
			void outputMolGraphProperties(const MolecularGraph& molgraph, Internal::ByteBuffer& bbuf);
			void outputReactionProperties(const Reaction& rxn, Internal::ByteBuffer& bbuf);

			template <typename H, typename T>
			void outputExternalProperties(const H& handler, const T& obj, Internal::ByteBuffer& bbuf);

			void outputExternalProperties(const Atom& atom, Internal::ByteBuffer& bbuf);
			void outputExternalProperties(const Bond& bond, Internal::ByteBuffer& bbuf);
			void outputExternalProperties(const MolecularGraph& molgraph, Internal::ByteBuffer& bbuf);

			void putStereoDescriptor(const MolecularGraph& molgraph, 
									 unsigned int prop_id, const StereoDescriptor& descr, Internal::ByteBuffer& bbuf) const;

			void putFragmentList(const MolecularGraph& molgraph, unsigned int prop_id, const FragmentList::SharedPointer& frag_list, 
								 Internal::ByteBuffer& bbuf) const;

			void putStringData(unsigned int prop_id, const StringDataBlock::SharedPointer& sdata, Internal::ByteBuffer& bbuf) const;

			bool writeRecordData(std::ostream& os);

			typedef std::vector<AtomPropertyHandler> AtomPropertyHandlerList;
			typedef std::vector<BondPropertyHandler> BondPropertyHandlerList;
			typedef std::vector<MolGraphPropertyHandler> MolGraphPropertyHandlerList;

			const Base::ControlParameterContainer& ctrlParams;	
			Internal::ByteBuffer                   dataBuffer;
			Internal::ByteBuffer                   extDataBuffer;
			static AtomPropertyHandlerList         extAtomPropertyHandlers;
			static BondPropertyHandlerList         extBondPropertyHandlers;
			static MolGraphPropertyHandlerList     extMolGraphPropertyHandlers;
		};
	}
}

#endif // CDPL_CHEM_CDFDATAWRITER_HPP
