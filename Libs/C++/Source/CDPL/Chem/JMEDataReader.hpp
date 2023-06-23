/* 
 * JMEDataReader.hpp 
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


#ifndef CDPL_CHEM_JMEDATAREADER_HPP
#define CDPL_CHEM_JMEDATAREADER_HPP

#include <iosfwd>
#include <string>
#include <cstddef>

#include "CDPL/Chem/MatchConstraintList.hpp"


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
        class Atom;

        class JMEDataReader
        {

        public:
            JMEDataReader(const Base::DataIOBase& io_base): ioBase(io_base) {}

            bool readReaction(std::istream&, Reaction&);
            bool readMolecule(std::istream&, Molecule&);

            bool skipReaction(std::istream&);
            bool skipMolecule(std::istream&);

            bool hasMoreData(std::istream&) const;

        private:
            void init();

            void readComponent(std::istream&, Molecule&) const;
            void skipComponent(std::istream&) const;

            void readAtom(std::istream&, Molecule&) const;

            MatchConstraintList::SharedPointer readAtomList(std::string::const_iterator, std::string::const_iterator) const;
            MatchConstraintList::SharedPointer readAtomSymbol(Atom*, std::string::const_iterator, 
                                                              std::string::const_iterator, bool) const;
            MatchConstraintList::SharedPointer readQueryFlags(std::string::const_iterator, std::string::const_iterator) const;

            long readAtomCharge(std::string::const_iterator, std::string::const_iterator) const;
            void readReactionAtomMappingID(Atom&, std::string::const_iterator, std::string::const_iterator) const;

            void readBond(std::istream&, Molecule&, std::size_t, std::size_t) const;

            const Base::DataIOBase& ioBase;            
            bool                    strictErrorChecking;
            std::size_t             coordsDim;
            std::size_t             atomMappingIDOffset;
        };
    }
}

#endif // CDPL_CHEM_JMEDATAREADER_HPP
