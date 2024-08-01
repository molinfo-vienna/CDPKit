/* 
 * MOL2DataReader.hpp 
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


#ifndef CDPL_BIOMOL_MOL2DATAREADER_HPP
#define CDPL_BIOMOL_MOL2DATAREADER_HPP

#include <cstddef>

#include "CDPL/Chem/MOL2DataReader.hpp"


namespace CDPL
{

    namespace Biomol
    {

        class MOL2DataReader : public Chem::MOL2DataReader
        {

          public:
            MOL2DataReader(const Base::DataIOBase& io_base):
                Chem::MOL2DataReader(io_base) {}

            static void registerFactoryFunction();

            bool readMolecule(std::istream& is, Chem::Molecule& mol);

          private:
            void convertMOL2ToPDBResidueInfo(Chem::Molecule& mol, std::size_t atom_idx_offs) const;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MOL2DATAREADER_HPP
