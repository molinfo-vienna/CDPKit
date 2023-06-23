/* 
 * MDLDataReader.hpp 
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


#ifndef CDPL_CHEM_MDLDATAREADER_HPP
#define CDPL_CHEM_MDLDATAREADER_HPP

#include <cstddef>
#include <iosfwd>
#include <string>
#include <map>
#include <vector>
#include <utility>

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

        class Reaction;
        class MatchConstraintList;

        class MDLDataReader
        {

        public:
            MDLDataReader(const Base::DataIOBase& io_base): ioBase(io_base) {}

            bool readMOLFile(std::istream&, Molecule&);
            bool readSDFileRecord(std::istream&, Molecule&);

            bool readRXNFile(std::istream&, Reaction&);
            bool readRDFileRecord(std::istream&, Reaction&);

            bool skipMOLFile(std::istream&);
            bool skipSDFileRecord(std::istream&);

            bool skipRXNFile(std::istream&);
            bool skipRDFileRecord(std::istream&);

            bool hasMoreData(std::istream&) const;

        private:
            bool readMolecule(std::istream&, Molecule&, bool);
            bool skipMolecule(std::istream&, bool);

            bool addConformer(std::istream&, MolecularGraph&);
            bool readNextConformer(std::istream&, const MolecularGraph&, bool);

            void init(std::istream&);

            void readMOLHeaderBlock(std::istream&, Molecule&);
            void skipMOLHeaderBlock(std::istream&);

            void readMOLCTab(std::istream&, Molecule&);
            void skipMOLCTab(std::istream&);

            void readCTabCountsLine(std::istream&, Molecule&);
            void skipCTabCountsLine(std::istream&);

            void readCTabV2000(std::istream&, Molecule&);
            void skipCTabV2000(std::istream&);

            void readCTabV2000AtomBlock(std::istream&, Molecule&, std::size_t);
            bool readCTabV2000BondBlock(std::istream&, Molecule&, std::size_t) const;
            void readCTabV2000AListBlock(std::istream&, Molecule&, std::size_t);
            void readCTabV2000STextBlock(std::istream&) const;

            void readCTabV2000PropertyBlock(std::istream&, Molecule&, std::size_t);
            void skipCTabV2000PropertyBlock(std::istream&);

            void readCTabV2000Atom(std::istream&, Molecule&);
            void readCTabV2000AtomCoords(std::istream&, Atom&);
            void readCTabV2000AtomSymbol(std::istream&, Atom&);
            void readCTabV2000AtomMass(std::istream&, Atom&) const;
            void readCTabV2000AtomCharge(std::istream&, Atom&) const;
            void readCTabV2000AtomParity(std::istream&, Atom&);
            void readCTabV2000AtomQueryHCount(std::istream&, Atom&);
            void readCTabV2000AtomStereoBoxFlag(std::istream&, Atom&) const;
            void readCTabV2000AtomValence(std::istream&, Atom&) const;
            void readCTabV2000AtomRxnInfo(std::istream&, Atom&) const;

            bool readCTabV2000Bond(std::istream&, Molecule&, std::size_t) const;
            Bond& createCTabV2000Bond(std::istream&, Molecule&, std::size_t) const;
            std::size_t readCTabV2000BondType(std::istream&, Bond&, MatchConstraintList&) const;
            void readCTabV2000BondStereo(std::istream&, Bond&) const;
            void readCTabV2000BondQueryTopology(std::istream&, MatchConstraintList&) const;
            void readCTabV2000BondRxnCenterStatus(std::istream&, Bond&) const;

            void readCTabV2000AList(std::istream&, Molecule&, std::size_t);
            void readCTabV2000ChargeProperties(std::istream&, Molecule&, std::size_t) const;
            void readCTabV2000RadicalProperties(std::istream&, Molecule&, std::size_t) const;
            void readCTabV2000IsotopeProperties(std::istream&, Molecule&, std::size_t) const;
            void readCTabV2000RingBondCountProperties(std::istream&, Molecule&, std::size_t) const;
            void readCTabV2000SubstCountProperties(std::istream&, Molecule&, std::size_t) const;
            void readCTabV2000UnsaturationProperties(std::istream&, Molecule&, std::size_t) const;
            void readCTabV2000AtomListProperties(std::istream&, Molecule&, std::size_t);
            void readCTabV2000RegistryNumberProperty(std::istream&, Molecule&);

            void readSDFData(std::istream&, Molecule&);
            void skipSDFData(std::istream&);

            void readRXNHeaderBlock(std::istream&, Reaction&);
            void skipRXNHeaderBlock(std::istream&);

            void readRXNReaction(std::istream&, Reaction&);
            void skipRXNReaction(std::istream&);

            void readRXNV2000Reaction(std::istream&, Reaction&);
            void skipRXNV2000Reaction(std::istream&);

            void readRXNV2000CountsLine(std::istream&, std::size_t&, std::size_t&);

            void readRXNV2000ReactionComponent(std::istream&, Reaction&, unsigned int);
            void skipRXNV2000ReactionComponent(std::istream&);

            void readRDFHeaderBlock(std::istream&);
            void skipRDFHeaderBlock(std::istream&);

            void readRDFReaction(std::istream&, Reaction&);
            void skipRDFReaction(std::istream&);

            void readRDFData(std::istream&, Reaction&);
            void skipRDFData(std::istream&);

            bool hasRDFKeywordPrefix(const std::string&) const;

            void readCTabV3000(std::istream&, Molecule&);
            void readCTabV3000CountsLine(std::istream&, Molecule&);
            void readCTabV3000AtomBlock(std::istream&, Molecule&);
            bool readCTabV3000BondBlock(std::istream&, Molecule&);
            void readPastCTabV3000BlockEnd(std::istream&);

            void readCTabV3000Atom(std::istream&, Molecule&);
            void readCTabV3000AtomIndex(std::istream&, const Molecule&, Atom&);
            void readCTabV3000AtomType(std::istream&, Atom&, MatchConstraintList&);
            void setCTabV3000AtomSymbol(std::string&, Atom&, MatchConstraintList&) const;
            void readCTabV3000AtomCoords(std::istream&, Atom&);
            void readCTabV3000AtomRxnAAMNumber(std::istream&, Atom&) const;
            void readCTabV3000AtomCharge(std::istream&, Atom&) const;
            void readCTabV3000AtomRadicalType(std::istream&, Atom&) const;
            void readCTabV3000AtomStereoConfig(std::istream&, Atom&);
            void readCTabV3000AtomMass(std::istream&, Atom&) const;
            void readCTabV3000AtomValence(std::istream&, Atom&) const;
            void readCTabV3000AtomQueryHCount(std::istream&, Atom&);
            void readCTabV3000AtomStereoBoxFlag(std::istream&, Atom&) const;
            void readCTabV3000AtomRxnInvRetFlag(std::istream&, Atom&, unsigned int&) const;
            void readCTabV3000AtomRxnChangeFlag(std::istream&, Atom&, unsigned int&) const;
            void readCTabV3000AtomQuerySubstCount(std::istream&, Atom&, MatchConstraintList&) const;
            void readCTabV3000AtomQueryUnsaturationFlag(std::istream&, MatchConstraintList&) const;
            void readCTabV3000AtomQueryRingBondCount(std::istream&, Atom&, MatchConstraintList&) const;

            bool readCTabV3000Bond(std::istream&, Molecule&);
            void readCTabV3000BondIndex(std::istream&) const;
            unsigned int readCTabV3000BondType(std::istream&) const;
            Bond& createCTabV3000Bond(std::istream&, Molecule&) const; 
            std::size_t setCTabV3000BondType(unsigned int, Bond&, MatchConstraintList&) const;
            void readCTabV3000BondStereo(std::istream&, Bond&) const;
            void readCTabV3000BondQueryStereoBoxFlag(std::istream&, MatchConstraintList&) const;
            void readCTabV3000BondQueryTopology(std::istream&, MatchConstraintList&) const;
            void readCTabV3000BondRxnCenterStatus(std::istream&, Bond&) const;

            bool readCTabV3000PropertyKeyword(std::istream&, std::string&) const;

            void readCTabV3000PropertyStringValue(std::istream&, std::string&) const;
            void skipCTabV3000PropertyIntValue(std::istream& is);
            void skipCTabV3000PropertyValueList(std::istream& is) const;

            void readRXNV3000Reaction(std::istream&, Reaction&);
            void readRXNV3000CountsLine(std::istream&, std::size_t&, std::size_t&);
            void readRXNV3000ReactionComponent(std::istream&, Reaction&, unsigned int);

            void readV3000BlockBegin(std::istream&, const std::string&);
            void readV3000BlockEnd(std::istream&, const std::string&);

            void readV3000DataLine(std::istream&);

            void readV3000DataEndTag(std::istream&);
            void skipV3000Data(std::istream&);

            void fixAtomCoordsDim(Molecule&, std::size_t) const;
            void addAtomQueryHCountConstraints() const;
            void kekulizeUndefBonds(Molecule&) const;
            void convertParities(Molecule&) const;

            typedef std::map<std::size_t, std::size_t> AtomIndexMap;
            typedef std::vector<std::pair<Atom*, std::size_t> > AtomQueryHCountList;
            typedef std::vector<Atom*> StereoAtomList;

            const Base::DataIOBase& ioBase;
            std::size_t             coordsDim;
            std::size_t             atomCount;
            std::size_t             bondCount;
            std::size_t             atomListCount;
            std::size_t             sTextEntryCount;
            std::size_t             propertyCount;
            std::size_t             atomMappingIDOffset;
            unsigned int            ctabVersion;
            unsigned int            rxnVersion;
            AtomIndexMap            atomIndexMap;
            AtomQueryHCountList     atomQueryHCountList;
            StereoAtomList          stereoAtoms;
            bool                    strictErrorChecking;
            bool                    ignoreParity;
            bool                    trimStrings;
            bool                    trimLines;
            bool                    checkLineLength;
            bool                    multiConfImport;
            std::string             tmpString;
            std::string             line;
            Fragment::SharedPointer confTargetFragment;
            Molecule::SharedPointer confTargetMolecule;
            Molecule::SharedPointer confTestMolecule;
            Math::Vector3DArray     confCoords;
        };
    }
}

#endif // CDPL_CHEM_MDLDATAREADER_HPP
