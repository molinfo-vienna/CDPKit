/* 
 * CIPMancude.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * The code in this file is a C++11 port of Java code written by John Mayfield
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

/**
 * \file
 * \brief Definition of the class CDPL::Chem::CIPMancude.
 */

#ifndef CDPL_CHEM_CIPMANCUDE_HPP
#define CDPL_CHEM_CIPMANCUDE_HPP

#include <utility>
#include <vector>
#include <deque>
#include <cstddef>


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Atom;

        class CIPMancude
        {

          public:
            typedef std::pair<unsigned int, unsigned short> Fraction;

            void setMolecularGraph(const MolecularGraph& molgraph);

            const Fraction& operator[](const Atom& atom);

          private:
            void calcFracAtomicNos();

            bool seedTypes();
            void relaxTypes();

            std::size_t visitParts();
            void visitPart(std::size_t part, const Atom* atom);

            enum Type
            {
                Cv4D4,      // =CH-
                Nv3D2,      // =N-
                Nv4D3Plus,  // =[N+]<
                Nv2D2Minus, // -[N-]-
                Cv3D3Minus, // -[CH-]-
                Ov3D2Plus,  // -[O+]=
                Other
            };

            typedef std::vector<Type>        TypeArray;
            typedef std::vector<Fraction>    FractionArray;
            typedef std::vector<std::size_t> UIntArray;
            typedef std::deque<const Atom*>  AtomQueue;

            const MolecularGraph* molGraph{0};
            bool                  calculated{false};
            TypeArray             types;
            UIntArray             parts;
            UIntArray             resParts;
            UIntArray             counts;
            FractionArray         fractions;
            AtomQueue             atomQueue;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPMANCUDE_HPP
