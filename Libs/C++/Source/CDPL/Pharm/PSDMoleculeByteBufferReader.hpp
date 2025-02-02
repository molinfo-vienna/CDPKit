/* 
 * PSDMoleculeByteBufferReader.hpp 
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


#ifndef CDPL_PHARM_PSDMOLECULEBYTEBUFFERREADER_HPP
#define CDPL_PHARM_PSDMOLECULEBYTEBUFFERREADER_HPP

#include <memory>
#include <string>
#include <cstddef>
#include <vector>

#include "CDPL/Base/ControlParameterContainer.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{
    
    namespace Internal
    {

        class ByteBuffer;
    }

    namespace Chem
    {
        
        class CDFDataReader;
        class Molecule;
    }
    
    namespace Pharm
    {
        
        class PSDMoleculeByteBufferReader : private Base::ControlParameterContainer
        {

          public:
            PSDMoleculeByteBufferReader();

            ~PSDMoleculeByteBufferReader();

            void readMolecule(Internal::ByteBuffer& bbuf, Chem::Molecule& mol);

          private:
            struct StereoDescr
            {

                StereoDescr(std::size_t obj_idx):
                    objIndex(obj_idx) {}

                std::size_t  objIndex;
                unsigned int config;
                std::size_t  numRefAtoms;
                std::size_t  refAtomInds[4];
            };
            
            void readHeaderAndName(Internal::ByteBuffer& bbuf, Chem::Molecule& mol);
            void readStructureData(Internal::ByteBuffer& bbuf, Chem::Molecule& mol);
            void readAtoms(Internal::ByteBuffer& bbuf, Chem::Molecule& mol);
            void readConformers(Internal::ByteBuffer& bbuf, Chem::Molecule& mol);
            void readBonds(Internal::ByteBuffer& bbuf, Chem::Molecule& mol);

            void readStereoDescriptor(StereoDescr& descr, Internal::ByteBuffer& bbuf) const;
            void readCoordinates(std::size_t num_atoms, Internal::ByteBuffer& bbuf);

            void setStereoDescriptors(Chem::Molecule& mol) const;

            template <typename T>
            void setStereoDescriptor(T& obj, const Chem::Molecule& mol, const StereoDescr& descr) const;

            typedef std::unique_ptr<Chem::CDFDataReader>            CDFDataReaderPtr;
            typedef std::vector<StereoDescr>                        StereoDescrList;
            typedef std::vector<Math::Vector3DArray::SharedPointer> AtomCoordsArrayList;

            CDFDataReaderPtr    cdfReader;
            StereoDescrList     atomStereoDescrs;
            StereoDescrList     bondStereoDescrs;
            Math::Vector3DArray coordinates;
            AtomCoordsArrayList atomCoordsArrays;
            std::string         tmpString[2];
            std::size_t         startAtomIdx;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PSDMOLECULEBYTEBUFFERREADER_HPP
