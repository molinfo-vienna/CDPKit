/* 
 * MOL2DataWriter.hpp 
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


#ifndef CDPL_CHEM_MOL2DATAWRITER_HPP
#define CDPL_CHEM_MOL2DATAWRITER_HPP

#include <iosfwd>
#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include "CDPL/Chem/APIPrefix.hpp"
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
        class Atom;
        class Bond;

        class CDPL_CHEM_API MOL2DataWriter
        {

          public:
            typedef std::function<MOL2DataWriter*(const Base::DataIOBase& io_base)> FactoryFunction;
            
            MOL2DataWriter(const Base::DataIOBase& io_base):
                ioBase(io_base) {}

            virtual ~MOL2DataWriter() {}
            
            bool writeMolecularGraph(std::ostream& os, const MolecularGraph& molgraph);

            static FactoryFunction& factoryFunction();
            
          private:
            void init(std::ostream& os);

            void getAtomCoordsDim(const MolecularGraph& molgraph);
            void initSubstructureData(const MolecularGraph& molgraph);

            void writeMoleculeRecord(std::ostream& os, const MolecularGraph& molgraph, std::size_t conf_idx = 0);
            void writeConformerEnergyComment(std::ostream& os, double energy);
            void writeAtomSection(std::ostream& os, const MolecularGraph& molgraph);
            void writeBondSection(std::ostream& os, const MolecularGraph& molgraph) const;
            void writeSubstructSection(std::ostream& os) const;

            const std::string& getMoleculeTypeString(const MolecularGraph& molgraph) const;
            const std::string& getChargeTypeString(const MolecularGraph& molgraph);

            std::string getAtomName(const Atom& atom);

            const std::string& getAtomTypeString(const Atom& atom, const MolecularGraph& molgraph) const;
            const std::string& getBondTypeString(const Bond& bond, const MolecularGraph& molgraph) const;
            const std::string& getBondOrderString(const Bond& bond) const;

            struct SubstructData
            {

                std::size_t rootAtom;
                std::string name;
                std::string subtype;
                std::string chain;
            };

            typedef std::unordered_map<std::string, std::size_t> StringToSizeMap;
            typedef std::unordered_map<const Atom*, std::size_t> AtomToIDMap;
            typedef std::vector<SubstructData>                   SubstructDataArray;

            const Base::DataIOBase& ioBase;
            bool                    strictErrorChecking;
            bool                    multiConfExport;
            bool                    extendedAtomTypes;
            bool                    aromaticBondTypes;
            bool                    outputSubstructs;
            unsigned int            atomChargeType;
            unsigned int            moleculeType;
            bool                    writeConfEnergyComment;
            std::string             confIdxSuffixPattern;
            std::size_t             coordsDim;
            Math::Vector3DArray     confCoordinates;
            StringToSizeMap         atomSymbolCounts;
            StringToSizeMap         substructNamesToIDs;
            AtomToIDMap             atomsToSubstructIDs;
            SubstructDataArray      substructData;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MOL2DATAWRITER_HPP
