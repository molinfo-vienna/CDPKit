/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDataReader.hpp 
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


#ifndef CDPL_CHEM_CDFDATAREADER_HPP
#define CDPL_CHEM_CDFDATAREADER_HPP

#include <cstddef>
#include <iosfwd>
#include <vector>

#include "CDPL/Chem/CDFFormatData.hpp"

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

		class Molecule;
		class Atom;
		class Bond;

		class CDFDataReader : protected Internal::CDFDataReaderBase
		{

		public:
			CDFDataReader(const Base::ControlParameterContainer& ctrl_params): ctrlParams(ctrl_params) {}

			virtual ~CDFDataReader() {}

			bool readMolecule(std::istream& is, Molecule& mol);

			bool readMolecule(Molecule& mol, Internal::ByteBuffer& bbuf);

			bool skipMolecule(std::istream& is);

			bool hasMoreData(std::istream& is);

		protected:
			virtual void init();

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

			std::size_t readAtoms(Molecule& mol, Internal::ByteBuffer& bbuf);
			void readBonds(Molecule& mol, Internal::ByteBuffer& bbuf, std::size_t num_atoms);
			void readMoleculeProperties(Molecule& mol, Internal::ByteBuffer& bbuf);

			template <typename T>
			void handleExtendedProperties(CDF::PropertySpec prop_spec, T& obj, Internal::ByteBuffer& data);

			virtual bool handleExtendedProperties(Atom& atom, Internal::ByteBuffer& data);
			virtual bool handleExtendedProperties(Bond& bond, Internal::ByteBuffer& data);
			virtual bool handleExtendedProperties(Molecule& mol, Internal::ByteBuffer& data);

			void readStereoDescriptor(CDF::PropertySpec prop_spec, CDFStereoDescr& descr, Internal::ByteBuffer& data) const;
			void setStereoDescriptors(Molecule& mol) const;

			template <typename T>
			void setStereoDescriptor(T& obj, const Molecule& mol, const CDFStereoDescr& descr) const;

			typedef std::vector<CDFStereoDescr> StereoDescrList;

			const Base::ControlParameterContainer& ctrlParams;	
			Internal::ByteBuffer                   dataBuffer;		
			std::size_t                            startAtomIdx;
			StereoDescrList                        atomStereoDescrs;
			StereoDescrList                        bondStereoDescrs;
		};
	}
}

#endif // CDPL_CHEM_CDFDATAREADER_HPP