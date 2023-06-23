/* 
 * PDBDataWriter.hpp 
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


#ifndef CDPL_BIOMOL_PDBDATAWRITER_HPP
#define CDPL_BIOMOL_PDBDATAWRITER_HPP

#include <iosfwd>
#include <string>
#include <vector>
#include <cstddef>
#include <utility>
#include <unordered_map>
#include <unordered_set>

#include <boost/functional/hash.hpp>

#include "CDPL/Biomol/ResidueDictionary.hpp"
#include "CDPL/Biomol/PDBData.hpp"


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
    }

    namespace Biomol
    {

        class PDBDataWriter
        {

        public:
            PDBDataWriter(const Base::DataIOBase& io_base): ioBase(io_base) {}
        
            bool writePDBFileRecord(std::ostream& os, const Chem::MolecularGraph& molgraph);
        
        private:
            void init(std::ostream& os);

            void processAtomSequence(const Chem::MolecularGraph& molgraph);
            void perceiveCONECTRecordBonds(const Chem::MolecularGraph& molgraph);

            void writeTitleSection(std::ostream& os, const Chem::MolecularGraph& molgraph);
            void writePrimaryStructureSection(std::ostream& os, const Chem::MolecularGraph& molgraph);
            void writeHeterogenSection(std::ostream& os, const Chem::MolecularGraph& molgraph);
            void writeSecondaryStructureSection(std::ostream& os, const Chem::MolecularGraph& molgraph);
            void writeConnAnnotationSection(std::ostream& os, const Chem::MolecularGraph& molgraph);
            void writeMiscSection(std::ostream& os, const Chem::MolecularGraph& molgraph);
            void writeCrystAndCoordTransformSection(std::ostream& os, const Chem::MolecularGraph& molgraph);
            void writeCoordinateSection(std::ostream& os);
            void writeConnectivitySection(std::ostream& os, const Chem::MolecularGraph& molgraph);
            void writeBookkeepingSection(std::ostream& os);

            bool writeGenericDataRecord(std::ostream& os, PDBData::RecordType type, const Chem::MolecularGraph& molgraph, 
                                        const std::string& prefix, std::size_t max_llen);

            long writeATOMRecord(std::ostream& os, long serial, const Chem::Atom& atom, std::size_t conf_idx = 0);
            void writeTERRecord(std::ostream& os, long serial, const Chem::Atom& atom) const;

            void writeNUMMDLRecord(std::ostream& os) const;
            void writeMODELRecord(std::ostream& os, std::size_t model_id) const;
            void writeENDMDLRecord(std::ostream& os) const;

            bool isStandardBond(const Chem::Bond& bond, const Chem::MolecularGraph& tmplt) const;
            bool isLinkingAtom(const Chem::Atom& atom, const Chem::MolecularGraph& tmplt) const;

            const Chem::Atom* getResTemplateAtom(const Chem::Atom& atom, const Chem::MolecularGraph& tmplt) const;

            long checkSerialNumber(long serial_no) const;
            long checkResidueSequenceNumber(long seq_no) const;
            
            bool atomOrderingFunc(const Chem::Atom* atom1, const Chem::Atom* atom2) const;
/*
            long getSerialNumber(const Chem::Atom& atom) const;
            long getResidueSequenceNumber(const Chem::Atom& atom) const;
            char getResidueInsertionCode(const Chem::Atom& atom) const;
            const std::string& getChainID(const Chem::Atom& atom) const;
            bool getHeteroAtomFlag(const Chem::Atom& atom) const;
            const std::string& getResidueCode(const Chem::Atom& atom) const;
            const std::string& getResidueAtomName(const Chem::Atom& atom) const;
*/
            typedef std::vector<const Chem::Atom*> AtomList;
            typedef std::vector<long> AtomSerialList;
            typedef std::unordered_map<std::string, std::size_t> RecordHistogram;
            typedef std::unordered_map<const Chem::Atom*, std::size_t> AtomToSerialMap;
            typedef std::pair<long, long> SerialPair;
            typedef std::unordered_set<SerialPair, boost::hash<SerialPair> > SerialPairSet;
            typedef std::unordered_set<const Chem::Bond*> BondSet;

            typedef ResidueDictionary::SharedPointer ResDictPointer;

            const Base::DataIOBase& ioBase;
            bool                    strictErrorChecking;
            bool                    checkLineLength;
            bool                    truncLines;
            bool                    writeFormCharges;
            bool                    writeConectRecords;
            bool                    writeConectRecsForAllBonds;
            bool                    writeConectRecsRefBondOrders;
            ResDictPointer          resDictionary;
            AtomList                atomSequence;
            RecordHistogram         recordHistogram;
            AtomSerialList          nbrAtomSerials;
            AtomToSerialMap         atomToSerialMap;
            AtomToSerialMap         atomToResidueSerialMap;
            SerialPairSet           writtenConectAtomPairs;
            SerialPairSet           connectedResidueLookup;
            BondSet                 conectRecordBonds;
            std::size_t             numModels;
            //std::size_t             numWrittenModels;
        };
    }
}

#endif // CDPL_BIOMOL_PDBDATAWRITER_HPP
