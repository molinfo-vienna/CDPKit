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


#ifndef CDPL_CHEM_MOL2DATAREADER_HPP
#define CDPL_CHEM_MOL2DATAREADER_HPP

#include <iosfwd>
#include <string>
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <functional>

#include <boost/tokenizer.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
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

        class CDPL_CHEM_API MOL2DataReader
        {

          public:
            typedef std::function<MOL2DataReader*(const Base::DataIOBase& io_base)> FactoryFunction;
            
            MOL2DataReader(const Base::DataIOBase& io_base):
                ioBase(io_base), lineTokenizer(dataLine, boost::char_separator<char>(" \t")) {}

            virtual ~MOL2DataReader() {}
            
            bool hasMoreData(std::istream& is);
            bool skipMolecule(std::istream& is);

            virtual bool readMolecule(std::istream& is, Molecule& mol);
            
            static FactoryFunction& factoryFunction();
            
          private:
            void init(std::istream& is);

            void doReadMolecule(std::istream& is, Molecule& mol);
            void readMoleculeRecord(std::istream& is, Molecule& mol);
            void readAtomSection(std::istream& is, Molecule& mol);
            void readBondSection(std::istream& is, Molecule& mol);
            void readSubstructSection(std::istream& is, Molecule& mol);

            bool addConformer(std::istream& is, MolecularGraph& molgraph);
            bool readNextConformer(std::istream& is, const MolecularGraph& molgraph, bool save_coords);

            void extractStereoAtoms(MolecularGraph& molgraph);

            bool readInputLine(std::istream& is);
            bool readDataLine(std::istream& is);

            bool skipInputToRTI(std::istream& is, const std::string& rti, bool skip_rti);

            typedef std::unordered_map<std::size_t, std::size_t>   AtomIDToIndexMap;
            typedef std::unordered_multimap<std::size_t, Atom*>    SubstructIDToAtomMap;
            typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;
            typedef std::vector<const Atom*>                       StereoAtomList;

            const Base::DataIOBase& ioBase;
            bool                    strictErrorChecking;
            bool                    multiConfImport;
            bool                    calcFormalCharges;
            std::size_t             molAtomCount;
            std::size_t             molBondCount;
            std::size_t             molSubstructCount;
            std::string             inputLine;
            std::string             dataLine;
            Tokenizer               lineTokenizer;
            AtomIDToIndexMap        atomIDsToIndex;
            SubstructIDToAtomMap    substructIDsToAtoms;
            Fragment::SharedPointer confTargetFragment;
            Molecule::SharedPointer confTargetMolecule;
            Molecule::SharedPointer confTestMolecule;
            Math::Vector3DArray     confCoords;
            StereoAtomList          stereoAtoms;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MOL2DATAREADER_HPP
