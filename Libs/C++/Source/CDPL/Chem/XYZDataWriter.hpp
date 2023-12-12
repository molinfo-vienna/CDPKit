/* 
 * XYZDataWriter.hpp 
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


#ifndef CDPL_CHEM_XYZDATAWRITER_HPP
#define CDPL_CHEM_XYZDATAWRITER_HPP

#include <iosfwd>

#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace Base
    {

        class DataIOBase;
    }

    namespace Chem
    {

        class MolecularGraph;
        class AtomContainer;

        class XYZDataWriter
        {

          public:
            XYZDataWriter(const Base::DataIOBase& io_base):
                ioBase(io_base) {}

            bool writeMolecularGraph(std::ostream& os, const MolecularGraph& molgraph);

          private:
            void init(std::ostream& os);

            void writeRecord(std::ostream& os, const AtomContainer& cntnr, double energy);
            void writeRecord(std::ostream& os, const MolecularGraph& molgraph);
            void writeAtomList(std::ostream& os, const AtomContainer& cntnr);

            const Base::DataIOBase& ioBase;
            bool                    multiConfExport;
            bool                    writeConfEnergyComment;
            bool                    commentIsName;
            Math::Vector3DArray     confCoordinates;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_XYZDATAWRITER_HPP
