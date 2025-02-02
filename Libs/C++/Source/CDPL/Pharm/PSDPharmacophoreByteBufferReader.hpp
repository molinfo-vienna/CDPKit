/* 
 * PSDPharmacophoreByteBufferReader.hpp 
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


#ifndef CDPL_PHARM_PSDPHARMACOPHOREBYTEBUFFERREADER_HPP
#define CDPL_PHARM_PSDPHARMACOPHOREBYTEBUFFERREADER_HPP

#include <memory>
#include <string>

#include "CDPL/Base/ControlParameterContainer.hpp"


namespace CDPL
{
    
    namespace Internal
    {

        class ByteBuffer;
    }
    
    namespace Pharm
    {

        class CDFDataReader;
        class Pharmacophore;
        
        class PSDPharmacophoreByteBufferReader : private Base::ControlParameterContainer
        {

          public:
            PSDPharmacophoreByteBufferReader();

            ~PSDPharmacophoreByteBufferReader();

            void readPharmacophore(Internal::ByteBuffer& bbuf, Pharmacophore& pharm);

          private:
            void readHeaderAndName(Internal::ByteBuffer& bbuf, Pharmacophore& pharm);
            void readFeatures(Internal::ByteBuffer& bbuf, Pharmacophore& pharm) const;
            
            typedef std::unique_ptr<CDFDataReader> CDFDataReaderPtr;
            
            CDFDataReaderPtr cdfReader;
            std::string      pharmName;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PSDPHARMACOPHOREBYTEBUFFERREADER_HPP
