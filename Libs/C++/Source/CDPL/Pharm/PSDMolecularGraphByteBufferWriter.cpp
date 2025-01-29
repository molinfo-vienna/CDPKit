/* 
 * PSDMolecularGraphByteBufferWriter.cpp 
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


#include "StaticInit.hpp"

#include <cstdint>

#include <boost/numeric/conversion/cast.hpp>

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/CDFDataWriter.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"

#include "PSDMolecularGraphByteBufferWriter.hpp"
#include "PSDMoleculeDataFormat.hpp"
#include "PSDDataIOUtilities.hpp"


using namespace CDPL;


Pharm::PSDMolecularGraphByteBufferWriter::PSDMolecularGraphByteBufferWriter()
{
    Chem::setStrictErrorCheckingParameter(*this, true);
    Chem::setCDFOutputSinglePrecisionFloatsParameter(*this, true);
}

Pharm::PSDMolecularGraphByteBufferWriter::~PSDMolecularGraphByteBufferWriter()
{}

void Pharm::PSDMolecularGraphByteBufferWriter::writeMolecularGraph(const Chem::MolecularGraph& molgraph, Internal::ByteBuffer& byte_buf)
{
    try {
        
        if (!cdfWriter)
            cdfWriter.reset(new Chem::CDFDataWriter(*this));

        cdfWriter->writeMolGraph(molgraph, byte_buf);
        
        //doWriteMolecularGraph(molgraph, byte_buf);

    } catch (const std::exception& e) {
        throw Base::IOError(std::string("PSDMolecularGraphByteBufferWriter: writing molecule data failed: ") + e.what());
    }
} 

void Pharm::PSDMolecularGraphByteBufferWriter::doWriteMolecularGraph(const Chem::MolecularGraph& molgraph, Internal::ByteBuffer& byte_buf)
{
    using namespace PSDMoleculeDataFormat;

    byte_buf.resize(0);
    byte_buf.setIOPointer(0);
    byte_buf.putInt(FORMAT_ID, false);
}
