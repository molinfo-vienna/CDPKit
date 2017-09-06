/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFPharmacophoreDataWriter.hpp 
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


#ifndef CDPL_PHARM_CDFPHARMACOPHOREDATAWRITER_HPP
#define CDPL_PHARM_CDFPHARMACOPHOREDATAWRITER_HPP

#include <iosfwd>

#include "CDPL/Internal/CDFDataWriterBase.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"


namespace CDPL 
{

	namespace Base
	{

		class ControlParameterContainer;
	}

	namespace Pharm
	{

		class FeatureContainer;

		class CDFPharmacophoreDataWriter : private Internal::CDFDataWriterBase
		{

		public:
			CDFPharmacophoreDataWriter(const Base::ControlParameterContainer& ctrl_params): ctrlParams(ctrl_params) {}

			bool writeFeatureContainer(std::ostream& os, const FeatureContainer& cntnr);

			void writeFeatureContainer(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf);

		private:
			void init();

			void outputFtrContainerHeader(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf) const;
			void outputFeatures(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf) const;
			void outputFtrContainerProperties(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf) const;

			bool writeRecordData(std::ostream& os) const;

			const Base::ControlParameterContainer& ctrlParams;	
			Internal::ByteBuffer                   dataBuffer;
		};
	}
}

#endif // CDPL_PHARM_CDFPHARMACOPHOREDATAWRITER_HPP
