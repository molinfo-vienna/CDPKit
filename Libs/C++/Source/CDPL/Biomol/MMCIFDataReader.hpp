/* 
 * MMCIFDataReader.hpp 
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


#ifndef CDPL_BIOMOL_MMCIFDATAREADER_HPP
#define CDPL_BIOMOL_MMCIFDATAREADER_HPP

#include <istream>
#include <unordered_map>

#include "CDPL/Biomol/MMCIFData.hpp"


namespace CDPL
{

    namespace Base
    {

        class DataIOBase;
    }

    namespace Chem
    {

        class Molecule;
    }
    
    namespace Biomol
    {

        class MMCIFDataReader
        {

          public:
            MMCIFDataReader(const Base::DataIOBase& io_base):
                ioBase(io_base) {}

            bool hasMoreData(std::istream& is);
            bool skipMolecule(std::istream& is);
            bool readMolecule(std::istream& is, Chem::Molecule& mol);

          private:
            enum Token : int;

            void init(std::istream&);

            void readMacromolecule(const MMCIFData& data, Chem::Molecule& mol);

            void readChemComponents(const MMCIFData& data, Chem::Molecule& mol);
            void readComponentAtoms(const MMCIFData& data, Chem::Molecule& mol);
            bool readComponentBonds(const MMCIFData& data, Chem::Molecule& mol);
            
            MMCIFData::SharedPointer parseInput(std::istream& is);

            void parseLoopSection(std::istream& is, MMCIFData& data);

            bool extractCategoryandItemNames(std::string& cat_name, std::string& item_name, bool strict) const;
  
            Token nextToken(std::istream& is);

            void putbackToken(std::istream& is) const;

            typedef std::pair<const std::string*, const std::string*> CompAtomID;

            struct CompAtomIDHash
            {

                std::size_t operator()(const CompAtomID& atom_id) const;
            };

            struct CompAtomIDCmpFunc
            {

                bool operator()(const CompAtomID& atom_id1, const CompAtomID& atom_id2) const
                {
                    return (*atom_id1.first == *atom_id2.first && *atom_id1.second == *atom_id2.second);
                }
            };

            typedef std::unordered_map<CompAtomID, std::size_t, CompAtomIDHash, CompAtomIDCmpFunc> CompAtomLookupMap;
            
            const Base::DataIOBase& ioBase;
            std::istream::pos_type  lastStreamPos;
            std::string             tokenValue;
            bool                    strictErrorChecking;
            CompAtomLookupMap       compAtomLookupMap;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MMCIFDATAREADER_HPP
