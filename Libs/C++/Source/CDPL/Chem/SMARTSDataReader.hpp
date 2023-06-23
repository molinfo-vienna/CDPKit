/* 
 * SMARTSDataReader.hpp 
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


#ifndef CDPL_CHEM_SMARTSDATAREADER_HPP
#define CDPL_CHEM_SMARTSDATAREADER_HPP

#include <map>
#include <set>
#include <vector>
#include <string>
#include <iosfwd>
#include <cstddef>
#include <memory>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"
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
        class Atom;
        class Bond;

        class SMARTSDataReader
        {

        public:
            SMARTSDataReader(const Base::DataIOBase& io_base): ioBase(io_base) {}

            bool readReaction(std::istream&, Reaction&);
            bool readMolecule(std::istream&, Molecule&);

            bool skipReaction(std::istream&);
            bool skipMolecule(std::istream&);

            bool hasMoreData(std::istream&) const;

            typedef std::vector<std::size_t> BondList;

        private:
            void init(const Molecule&);

            void setMoleculeMatchConstraints(Molecule&) const;

            void parseSMARTS(Molecule&, const Atom*);

            void parseRingClosures(Molecule&, const Atom&);

            void createBond(Molecule&, const Atom*, const Atom*, MatchConstraintList::SharedPointer&, std::size_t);

            MatchConstraintList::SharedPointer combineBondMatchConstraints(const MatchConstraintList::SharedPointer&, 
                                                                           const MatchConstraintList::SharedPointer&) const;
            MatchConstraintList::SharedPointer parseBondExpression();
            MatchConstraintList::SharedPointer parseBondExpression(std::size_t);
            bool parseBondExpressionPrimitive(MatchConstraintList&);

            const Chem::Atom* parseAtom(Molecule&);

            void setComponentGroupID(Atom&);

            MatchConstraintList::SharedPointer parseAtomExpression(Atom&);
            MatchConstraintList::SharedPointer parseAtomExpression(std::size_t, Atom&);

            MatchConstraintList::SharedPointer parseExplicitHAtomExpression(Atom&);
            MatchConstraintList::SharedPointer parseSimpleAtomExpression(char);

            bool parseAtomExpressionPrimitive(MatchConstraintList&);

            bool addEnvironmentConstraint(bool, MatchConstraintList&);
            bool addAtomicNumberConstraint(bool, MatchConstraintList&);
            bool addImplicitHCountConstraint(bool, MatchConstraintList&);
            bool addTotalHCountConstraint(bool, MatchConstraintList&);
            bool addRingSizeConstraint(bool, MatchConstraintList&);
            bool addRingMembershipConstraint(bool, MatchConstraintList&);
            bool addValenceConstraint(bool, MatchConstraintList&);
            bool addUnsaturationConstraint(bool, MatchConstraintList&);
            bool addExplicitDegreeConstraint(bool, MatchConstraintList&);
            bool addConnectivityConstraint(bool, MatchConstraintList&);
            bool addRingConnectivityConstraint(bool, MatchConstraintList&);
            bool addChargeConstraint(char, bool, MatchConstraintList&);
            bool addChiralityConstraint(bool, MatchConstraintList&);
            bool addIsotopeConstraint(char, bool, MatchConstraintList&);
            bool addAtomTypeConstraint(unsigned int, bool, MatchConstraintList&);
            bool addAtomTypeConstraint(unsigned int, bool, bool, MatchConstraintList&);
            bool addHybridizationStateConstraint(bool, MatchConstraintList&);

            void parseReactionAtomMappingID(Atom&);

            Molecule::SharedPointer parseSMARTS(const std::string&);

            bool hasNOTOperatorPrefix();
            bool hasUnspecStereoSuffix();

            template <typename T>
            bool parseNumber(T&, std::size_t = 0);

            bool hasNextChar() const;
            bool getChar(char&, bool);
            void ungetChar();

            void setBondTableEntry(std::size_t, const Bond*);

            void addToBondList(std::size_t, std::size_t, bool = true);
            const BondList& getBondList(std::size_t) const;

            void setAtomStereoDescriptors(const Molecule&) const;
            void setAtomStereoDescriptors(const Molecule&, const Atom&, MatchConstraintList&) const;
            void setAtomStereoDescriptor(const Molecule&, const Atom&, MatchConstraint&) const;

            void addBondConfigurationConstraints(Molecule&) const;
            bool hasBondDirectionConstraint(const MatchConstraintList&) const;

            void destroySMARTSParser(SMARTSDataReader*) const;

            struct ClosureBond
            {

                ClosureBond(std::size_t lex_bond_no, const Atom* start_atom, const MatchConstraintList::SharedPointer& match_constr):
                    lexBondNumber(lex_bond_no), startAtom(start_atom), matchConstraints(match_constr) {} 

                std::size_t                        lexBondNumber;
                const Atom*                        startAtom;
                MatchConstraintList::SharedPointer matchConstraints;
            };

            typedef std::shared_ptr<SMARTSDataReader> SharedPointer;

            typedef std::map<std::size_t, ClosureBond> ClosureBondMap;
            typedef std::vector<const Bond*> BondTable;
            typedef std::vector<BondList> BondListTable;

            const Base::DataIOBase& ioBase;
            std::string             molSMARTSString;
            std::string             rxnSMARTSString;
            std::size_t             nextCharIndex;
            std::size_t             openBranchCount;
            std::size_t             startAtomIndex;
            std::size_t             startBondIndex;
            std::size_t             lexicalBondNumber;
            std::size_t             componentGroupID;
            std::size_t             atomMappingIDOffset;
            BondTable               bondTable;
            ClosureBondMap          closureBondMap;
            BondListTable           nbrBondListTable;
            SharedPointer           smartsParser;
            bool                    haveRxnAtomMappingIDs;
            bool                    haveComponentGroups;
            bool                    strictErrorChecking;
        };
    }
}

#endif // CDPL_CHEM_SMARTSDATAREADER_HPP
 
