/* 
 * SMILESDataReader.hpp 
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


#ifndef CDPL_CHEM_SMILESDATAREADER_HPP
#define CDPL_CHEM_SMILESDATAREADER_HPP

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <iosfwd>
#include <cstddef>

#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

    namespace Base
    {

        class DataIOBase;
    }

    namespace Chem
    {

        class Reaction;
        class Molecule;

        class SMILESDataReader
        {

        public:
            SMILESDataReader(const Base::DataIOBase& io_base): ioBase(io_base) {}

            bool readReaction(std::istream&, Reaction&);
            bool readMolecule(std::istream&, Molecule&);

            bool skipReaction(std::istream&);
            bool skipMolecule(std::istream&);

            bool hasMoreData(std::istream&) const;

            typedef std::vector<std::size_t> STArray;

        private:
            struct BondParameters
            {

                std::size_t order;
                char        direction;
                bool        aromatic;
                bool        explicitBond;

                void combineWith(const BondParameters&, bool);
            };

            void getParameters();

            void skipRecord(std::istream&, std::string& str, const std::string& error_msg) const;

            void readRecord(std::istream&, std::string& smi_str, std::string& name, const std::string& error_msg) const;
            
            void init(const Molecule&);
        
            void parseSMILES(Molecule&, Atom*);

            void parseRingClosures(Molecule&, Atom&);

            bool parseBondParameters(BondParameters&);

            void createBond(Molecule&, Atom*, Atom*, const BondParameters&, std::size_t);

            Chem::Atom* parseAtom(Molecule&);
            Chem::Atom* parseOrgSubsetAtom(Molecule&);
            Chem::Atom* parseSpecialAtom(Molecule&);

            bool parseElementSymbol(char[3], bool);
            unsigned int parseStereoSpec();
            bool parseImplicitHCount(std::size_t&);
            long parseCharge();
            std::size_t parseReactionAtomMappingID();

            template <typename T>
            bool parseNumber(T&, std::size_t = 0);

            bool getChar(char&, bool);
            void ungetChar();

            void setAtomAromaticityFlag(std::size_t);
            bool getAtomAromaticityFlag(std::size_t) const;

            void addStereoAtom(Atom*, unsigned int);

            void setBondDirection(std::size_t, char);
            char getBondDirection(std::size_t) const;

            void setBondTableEntry(std::size_t, const Bond*);

            void addToBondList(std::size_t, std::size_t, bool = true);
            const STArray& getBondList(std::size_t) const;

            void setAtomStereoDescriptors(const Molecule&) const;
            void setBondStereoDescriptors(Molecule&) const;
                
            void kekulizeBonds(Molecule&);

            struct ClosureBond
            {

                ClosureBond(std::size_t lex_bond_no, Atom* start_atom, const BondParameters& bond_params):
                    lexBondNumber(lex_bond_no), startAtom(start_atom), bondParameters(bond_params) {} 

                std::size_t    lexBondNumber;
                Atom*          startAtom;
                BondParameters bondParameters;
            };

            typedef std::map<std::size_t, ClosureBond> ClosureBondMap;
            typedef std::vector<const Bond*> BondTable;
            typedef std::vector<STArray> BondListTable;
            typedef std::pair<std::size_t, std::size_t> STPair;
            typedef std::vector<STPair> STPairArray;
            typedef std::pair<Atom*, unsigned int> StereoAtomDescr;
            typedef std::vector<StereoAtomDescr> StereoAtomList;
            typedef std::vector<char> BondDirectionTable;

            const Base::DataIOBase& ioBase;
            std::string             molSMILESString;
            std::string             rxnSMILESString;
            std::string             name;
            std::size_t             nextCharIndex;
            std::size_t             openBranchCount;
            std::size_t             startAtomIndex;
            std::size_t             startBondIndex;
            std::size_t             lexicalBondNumber;
            std::size_t             atomMappingIDOffset;
            Util::BitSet            aromaticAtomMask;
            StereoAtomList          stereoAtomList;
            BondDirectionTable      bondDirectionTable;
            BondTable               bondTable;
            ClosureBondMap          closureBondMap;
            BondListTable           nbrBondListTable;
            bool                    strictErrorChecking;
            std::string             recordFormat;
            std::string             recordSeparator;
            Fragment                readMolGraph;
        };
    }
}

#endif // CDPL_CHEM_SMILESDATAREADER_HPP
 
