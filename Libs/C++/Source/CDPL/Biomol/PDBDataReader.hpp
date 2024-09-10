/* 
 * PDBDataReader.hpp 
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


#ifndef CDPL_BIOMOL_PDBDATAREADER_HPP
#define CDPL_BIOMOL_PDBDATAREADER_HPP

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>

#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Biomol/PDBData.hpp"
#include "CDPL/Biomol/ResidueDictionary.hpp"


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

        class PDBDataReader
        {

          public:
            PDBDataReader(const Base::DataIOBase& io_base):
                ioBase(io_base) {}

            bool readPDBFile(std::istream&, Chem::Molecule&);

            bool skipPDBFile(std::istream&);

            bool hasMoreData(std::istream&) const;

          private:
            void init(std::istream&);
            void init(std::istream&, Chem::Molecule&);

            std::size_t readGenericDataRecord(std::istream&, std::size_t, PDBData::RecordType, const std::string&);
            void        appendRecordData(PDBData::RecordType, const std::string&) const;

            std::size_t skipRecordData(std::istream&, std::size_t, const std::string&) const;

            std::size_t readMODELRecord(std::istream&);
            std::size_t readATOMRecord(std::istream&, Chem::Molecule&);
            std::size_t readTERRecord(std::istream&, Chem::Molecule&);
            std::size_t readHETATMRecord(std::istream&, Chem::Molecule&);
            std::size_t readENDMDLRecord(Chem::Molecule&);
            std::size_t readCONECTRecord(std::istream&, Chem::Molecule&);
            std::size_t readMASTERRecord(std::istream&);

            void readATOMRecord(std::istream&, Chem::Molecule&, const std::string&, bool);

            std::size_t startNextRecord(std::istream&, std::string&, std::string&);

            void skipInputToNextLine(std::istream&, std::size_t, const std::string&);
            void checkRecordOrder(const std::string&, const std::string&) const;
            void checkMandatoryRecords() const;

            void processAtomSequence(Chem::Molecule&, bool);

            void setBondOrdersFromResTemplates(Chem::Molecule&);
            void perceiveBondOrders(Chem::Molecule&);
            void calcAtomCharges(Chem::Molecule&);

            const Chem::Atom*  getResTemplateAtom(const Chem::MolecularGraph& tmplt, const std::string& atom_name) const;
            const std::string& getResTemplateAtomName(const Chem::Atom& atom) const;

            struct StringPtrHash
            {

                std::size_t operator()(const std::string* str_ptr) const
                {
                    if (!str_ptr)
                        return 0;

                    return std::hash<std::string>{}(*str_ptr);
                }
            };

            struct StringPtrCmpFunc
            {

                bool operator()(const std::string* str_ptr1, const std::string* str_ptr2) const
                {
                    if (!str_ptr1)
                        return !str_ptr2;

                    if (!str_ptr2)
                        return false;

                    return (*str_ptr1 == *str_ptr2);
                }
            };

            typedef std::vector<Chem::Atom*>                                                AtomList;
            typedef std::unordered_map<std::string, std::size_t>                            RecordHistogram;
            typedef std::unordered_map<std::size_t, std::unordered_map<long, Chem::Atom*> > SerialToAtomMap;
            typedef std::unordered_map<const std::string*, Chem::Atom*,
                                       StringPtrHash, StringPtrCmpFunc>                     NameToAtomMap;
            typedef std::unordered_map<std::string, std::size_t>                            BondOrderCache;

            typedef ResidueDictionary::SharedPointer ResDictPointer;

            const Base::DataIOBase& ioBase;
            std::string             stringData;
            bool                    strictErrorChecking;
            bool                    checkLineLength;
            ResDictPointer          resDictionary;
            bool                    applyDictAtomBondingToStdResidues;
            bool                    applyDictOrderToStdResidues;
            bool                    applyDictAtomBondingToNonStdResidues;
            bool                    applyDictOrderToNonStdResidues;
            bool                    ignoreConectRecords;
            bool                    setOrdersFromCONECTRecords;
            bool                    ignoreChargeField;
            bool                    applyDictAtomCharges;
            bool                    applyDictAtomTypes;
            bool                    calcCharges;
            bool                    perceiveOrders;
            bool                    evalMASTERRecord;
            unsigned int            formatVersion;
            PDBData::SharedPointer  pdbData;
            RecordHistogram         recordHistogram;
            std::size_t             currModelID;
            std::size_t             lastModelID;
            std::size_t             startAtomCount;
            std::size_t             startBondCount;
            std::size_t             numCoordRecords;
            SerialToAtomMap         serialToAtomMap;
            AtomList                atomSequence;
            NameToAtomMap           currResidueAtoms;
            AtomList                currResidueLinkAtoms;
            AtomList                prevResidueLinkAtoms;
            BondOrderCache          bondOrderCache;
            Chem::Fragment          readMolGraph;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_PDBDATAREADER_HPP
