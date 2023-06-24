/* 
 * JMEDataWriter.hpp 
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


#ifndef CDPL_CHEM_JMEDATAWRITER_HPP
#define CDPL_CHEM_JMEDATAWRITER_HPP

#include <iosfwd>
#include <cstddef>


namespace CDPL
{

    namespace Base
    {

        class DataIOBase;
    }

    namespace Chem
    {

        class Reaction;
        class MolecularGraph;
        class Atom;
        class Bond;
        class MatchConstraintList;

        class JMEDataWriter
        {

          public:
            JMEDataWriter(const Base::DataIOBase& io_base):
                ioBase(io_base) {}

            bool writeReaction(std::ostream&, const Reaction&);

            bool writeMolGraph(std::ostream&, const MolecularGraph&, bool = true);

          private:
            void init(std::ostream&);

            bool writeComponent(std::ostream&, const MolecularGraph&);

            void writeAtom(std::ostream&, const MolecularGraph&, const Atom&);
            void writeAtomSymbol(std::ostream&, const Atom&) const;
            void writeAtomCharge(std::ostream&, const Atom&) const;
            void writeAtomString(std::ostream&, const MolecularGraph&, const Atom&);
            bool writeAtomList(std::ostream&, const Atom&, const MatchConstraintList&, bool);
            bool writeAtomType(std::ostream&, const Atom&, const MatchConstraintList&, bool, bool);
            bool writeAtomType(std::ostream&, unsigned int, bool, bool, bool) const;
            bool writeQueryFlags(std::ostream&, const MolecularGraph&, const Atom&, const MatchConstraintList&) const;

            void writeBond(std::ostream&, const MolecularGraph&, const Bond&) const;

            const Base::DataIOBase& ioBase;
            bool                    strictErrorChecking;
            bool                    separateComponents;
            bool                    bondMemberSwapStereoFix;
            std::size_t             coordsDim;
            const void*             writtenAromConstraint;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_JMEDATAWRITER_HPP
