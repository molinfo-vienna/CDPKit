/* 
 * XYZDataReader.hpp 
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


#ifndef CDPL_CHEM_XYZDATAREADER_HPP
#define CDPL_CHEM_XYZDATAREADER_HPP

#include <iosfwd>
#include <string>
#include <cstddef>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace Base
    {

        class DataIOBase;
    }

    namespace Chem
    {

        class XYZDataReader
        {

          public:
            XYZDataReader(const Base::DataIOBase& io_base):
                ioBase(io_base) {}

            bool readMolecule(std::istream&, Molecule&);
            bool skipMolecule(std::istream&);
            bool hasMoreData(std::istream&) const;

          private:
            void readAtomCount(std::istream&);
            void readComment(std::istream&, MolecularGraph&);
            void readAtoms(std::istream&, Molecule&);

            bool addConformer(std::istream&, MolecularGraph&);
            bool readNextConformer(std::istream&, const MolecularGraph&, bool);

            void init(std::istream&);

            const Base::DataIOBase& ioBase;
            bool                    strictErrorChecking;
            bool                    multiConfImport;
            std::size_t             atomCount;
            std::string             tmpString;
            Fragment::SharedPointer confTargetFragment;
            Molecule::SharedPointer confTargetMolecule;
            Molecule::SharedPointer confTestMolecule;
            Math::Vector3DArray     confCoords;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_XYZDATAREADER_HPP
