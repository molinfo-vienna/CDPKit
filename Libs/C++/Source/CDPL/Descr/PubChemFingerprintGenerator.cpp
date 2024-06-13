/* 
 * PubChemFingerprintGenerator.cpp 
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


#include "StaticInit.hpp"

#include <mutex>
#include <vector>

#include "CDPL/Descr/PubChemFingerprintGenerator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"


using namespace CDPL;


namespace
{

    struct ElementCountDef
    {
        std::size_t  bitIndex;
        std::size_t  minCount;
        unsigned int atomicNo;
    };

    const ElementCountDef ELEMENT_COUNTS[] = {
        { 0, 4, Chem::AtomType::H },
        { 1, 8, Chem::AtomType::H },
        { 2, 16, Chem::AtomType::H },
        { 3, 32, Chem::AtomType::H },
        { 4, 1, Chem::AtomType::Li },
        { 5, 2, Chem::AtomType::Li },
        { 6, 1, Chem::AtomType::B },
        { 7, 2, Chem::AtomType::B },
        { 8, 4, Chem::AtomType::B },
        { 9, 2, Chem::AtomType::C },
        { 10, 4, Chem::AtomType::C },
        { 11, 8, Chem::AtomType::C },
        { 12, 16, Chem::AtomType::C },
        { 13, 32, Chem::AtomType::C },
        { 14, 1, Chem::AtomType::N },
        { 15, 2, Chem::AtomType::N },
        { 16, 4, Chem::AtomType::N },
        { 17, 8, Chem::AtomType::N },
        { 18, 1, Chem::AtomType::O },
        { 19, 2, Chem::AtomType::O },
        { 20, 4, Chem::AtomType::O },
        { 21, 8, Chem::AtomType::O },
        { 22, 16, Chem::AtomType::O },
        { 23, 1, Chem::AtomType::F },
        { 24, 2, Chem::AtomType::F },
        { 25, 4, Chem::AtomType::F },
        { 26, 1, Chem::AtomType::Na },
        { 27, 2, Chem::AtomType::Na },
        { 28, 1, Chem::AtomType::Si },
        { 29, 2, Chem::AtomType::Si },
        { 30, 1, Chem::AtomType::P },
        { 31, 2, Chem::AtomType::P },
        { 32, 4, Chem::AtomType::P },
        { 33, 1, Chem::AtomType::S },
        { 34, 2, Chem::AtomType::S },
        { 35, 4, Chem::AtomType::S },
        { 36, 8, Chem::AtomType::S },
        { 37, 1, Chem::AtomType::Cl },
        { 38, 2, Chem::AtomType::Cl },
        { 39, 4, Chem::AtomType::Cl },
        { 40, 8, Chem::AtomType::Cl },
        { 41, 1, Chem::AtomType::K },
        { 42, 2, Chem::AtomType::K },
        { 43, 1, Chem::AtomType::Br },
        { 44, 2, Chem::AtomType::Br },
        { 45, 4, Chem::AtomType::Br },
        { 46, 1, Chem::AtomType::I },
        { 47, 2, Chem::AtomType::I },
        { 48, 4, Chem::AtomType::I },
        { 49, 1, Chem::AtomType::Be },
        { 50, 1, Chem::AtomType::Mg },
        { 51, 1, Chem::AtomType::Al },
        { 52, 1, Chem::AtomType::Ca },
        { 53, 1, Chem::AtomType::Sc },
        { 54, 1, Chem::AtomType::Ti },
        { 55, 1, Chem::AtomType::V },
        { 56, 1, Chem::AtomType::Cr },
        { 57, 1, Chem::AtomType::Mn },
        { 58, 1, Chem::AtomType::Fe },
        { 59, 1, Chem::AtomType::Co },
        { 60, 1, Chem::AtomType::Ni },
        { 61, 1, Chem::AtomType::Cu },
        { 62, 1, Chem::AtomType::Zn },
        { 63, 1, Chem::AtomType::Ga },
        { 64, 1, Chem::AtomType::Ge },
        { 65, 1, Chem::AtomType::As },
        { 66, 1, Chem::AtomType::Se },
        { 67, 1, Chem::AtomType::Kr },
        { 68, 1, Chem::AtomType::Rb },
        { 69, 1, Chem::AtomType::Sr },
        { 70, 1, Chem::AtomType::Y },
        { 71, 1, Chem::AtomType::Zr },
        { 72, 1, Chem::AtomType::Nb },
        { 73, 1, Chem::AtomType::Mo },
        { 74, 1, Chem::AtomType::Ru },
        { 75, 1, Chem::AtomType::Rh },
        { 76, 1, Chem::AtomType::Pd },
        { 77, 1, Chem::AtomType::Ag },
        { 78, 1, Chem::AtomType::Cd },
        { 79, 1, Chem::AtomType::In },
        { 80, 1, Chem::AtomType::Sn },
        { 81, 1, Chem::AtomType::Sb },
        { 82, 1, Chem::AtomType::Te },
        { 83, 1, Chem::AtomType::Xe },
        { 84, 1, Chem::AtomType::Cs },
        { 85, 1, Chem::AtomType::Ba },
        { 86, 1, Chem::AtomType::Lu },
        { 87, 1, Chem::AtomType::Hf },
        { 88, 1, Chem::AtomType::Ta },
        { 89, 1, Chem::AtomType::W },
        { 90, 1, Chem::AtomType::Re },
        { 91, 1, Chem::AtomType::Os },
        { 92, 1, Chem::AtomType::Ir },
        { 93, 1, Chem::AtomType::Pt },
        { 94, 1, Chem::AtomType::Au },
        { 95, 1, Chem::AtomType::Hg },
        { 96, 1, Chem::AtomType::Tl },
        { 97, 1, Chem::AtomType::Pb },
        { 98, 1, Chem::AtomType::Bi },
        { 99, 1, Chem::AtomType::La },
        { 100, 1, Chem::AtomType::Ce },
        { 101, 1, Chem::AtomType::Pr },
        { 102, 1, Chem::AtomType::Nd },
        { 103, 1, Chem::AtomType::Pm },
        { 104, 1, Chem::AtomType::Sm },
        { 105, 1, Chem::AtomType::Eu },
        { 106, 1, Chem::AtomType::Gd },
        { 107, 1, Chem::AtomType::Tb },
        { 108, 1, Chem::AtomType::Dy },
        { 109, 1, Chem::AtomType::Ho },
        { 110, 1, Chem::AtomType::Er },
        { 111, 1, Chem::AtomType::Tm },
        { 112, 1, Chem::AtomType::Yb },
        { 113, 1, Chem::AtomType::Tc },
        { 114, 1, Chem::AtomType::U  }
    };

    struct RingCountDef
    {
        enum RingType
        {
            ANY,
            SAT_OR_ARO_C_ONLY,
            SAT_OR_ARO_N_CONT,
            SAT_OR_ARO_HET_CONT,
            UNSAT_NON_ARO_C_ONLY,
            UNSAT_NON_ARO_N_CONT,
            UNSAT_NON_ARO_HET_CONT,
            AROMATIC,
            HET_AROMATIC
        };

        std::size_t  bitIndex;
        std::size_t  minCount;
        RingType     ringType;
        std::size_t  ringSize;
    };

    const RingCountDef RING_COUNTS[] = {
        { 115, 1, RingCountDef::ANY, 3 },
        { 116, 1, RingCountDef::SAT_OR_ARO_C_ONLY, 3 },
        { 117, 1, RingCountDef::SAT_OR_ARO_N_CONT, 3 },
        { 118, 1, RingCountDef::SAT_OR_ARO_HET_CONT, 3 },
        { 119, 1, RingCountDef::UNSAT_NON_ARO_C_ONLY, 3 },
        { 120, 1, RingCountDef::UNSAT_NON_ARO_N_CONT, 3 },
        { 121, 1, RingCountDef::UNSAT_NON_ARO_HET_CONT, 3 },
        { 122, 2, RingCountDef::ANY, 3 },
        { 123, 2, RingCountDef::SAT_OR_ARO_C_ONLY, 3 },
        { 124, 2, RingCountDef::SAT_OR_ARO_N_CONT, 3 },
        { 125, 2, RingCountDef::SAT_OR_ARO_HET_CONT, 3 },
        { 126, 2, RingCountDef::UNSAT_NON_ARO_C_ONLY, 3 },
        { 127, 2, RingCountDef::UNSAT_NON_ARO_N_CONT, 3 },
        { 128, 2, RingCountDef::UNSAT_NON_ARO_HET_CONT, 3 },

        { 129, 1, RingCountDef::ANY, 4 },
        { 130, 1, RingCountDef::SAT_OR_ARO_C_ONLY, 4 },
        { 131, 1, RingCountDef::SAT_OR_ARO_N_CONT, 4 },
        { 132, 1, RingCountDef::SAT_OR_ARO_HET_CONT, 4 },
        { 133, 1, RingCountDef::UNSAT_NON_ARO_C_ONLY, 4 },
        { 134, 1, RingCountDef::UNSAT_NON_ARO_N_CONT, 4 },
        { 135, 1, RingCountDef::UNSAT_NON_ARO_HET_CONT, 4 },
        { 136, 2, RingCountDef::ANY, 4 },
        { 137, 2, RingCountDef::SAT_OR_ARO_C_ONLY, 4 },
        { 138, 2, RingCountDef::SAT_OR_ARO_N_CONT, 4 },
        { 139, 2, RingCountDef::SAT_OR_ARO_HET_CONT, 4 },
        { 140, 2, RingCountDef::UNSAT_NON_ARO_C_ONLY, 4 },
        { 141, 2, RingCountDef::UNSAT_NON_ARO_N_CONT, 4 },
        { 142, 2, RingCountDef::UNSAT_NON_ARO_HET_CONT, 4 },

        { 143, 1, RingCountDef::ANY, 5 },
        { 144, 1, RingCountDef::SAT_OR_ARO_C_ONLY, 5 },
        { 145, 1, RingCountDef::SAT_OR_ARO_N_CONT, 5 },
        { 146, 1, RingCountDef::SAT_OR_ARO_HET_CONT, 5 },
        { 147, 1, RingCountDef::UNSAT_NON_ARO_C_ONLY, 5 },
        { 148, 1, RingCountDef::UNSAT_NON_ARO_N_CONT, 5 },
        { 149, 1, RingCountDef::UNSAT_NON_ARO_HET_CONT, 5 },
        { 150, 2, RingCountDef::ANY, 5 },
        { 151, 2, RingCountDef::SAT_OR_ARO_C_ONLY, 5 },
        { 152, 2, RingCountDef::SAT_OR_ARO_N_CONT, 5 },
        { 153, 2, RingCountDef::SAT_OR_ARO_HET_CONT, 5 },
        { 154, 2, RingCountDef::UNSAT_NON_ARO_C_ONLY, 5 },
        { 155, 2, RingCountDef::UNSAT_NON_ARO_N_CONT, 5 },
        { 156, 2, RingCountDef::UNSAT_NON_ARO_HET_CONT, 5 },
        { 157, 3, RingCountDef::ANY, 5 },
        { 158, 3, RingCountDef::SAT_OR_ARO_C_ONLY, 5 },
        { 159, 3, RingCountDef::SAT_OR_ARO_N_CONT, 5 },
        { 160, 3, RingCountDef::SAT_OR_ARO_HET_CONT, 5 },
        { 161, 3, RingCountDef::UNSAT_NON_ARO_C_ONLY, 5 },
        { 162, 3, RingCountDef::UNSAT_NON_ARO_N_CONT, 5 },
        { 163, 3, RingCountDef::UNSAT_NON_ARO_HET_CONT, 5 },
        { 164, 4, RingCountDef::ANY, 5 },
        { 165, 4, RingCountDef::SAT_OR_ARO_C_ONLY, 5 },
        { 166, 4, RingCountDef::SAT_OR_ARO_N_CONT, 5 },
        { 167, 4, RingCountDef::SAT_OR_ARO_HET_CONT, 5 },
        { 168, 4, RingCountDef::UNSAT_NON_ARO_C_ONLY, 5 },
        { 169, 4, RingCountDef::UNSAT_NON_ARO_N_CONT, 5 },
        { 170, 4, RingCountDef::UNSAT_NON_ARO_HET_CONT, 5 },
        { 171, 5, RingCountDef::ANY, 5 },
        { 172, 5, RingCountDef::SAT_OR_ARO_C_ONLY, 5 },
        { 173, 5, RingCountDef::SAT_OR_ARO_N_CONT, 5 },
        { 174, 5, RingCountDef::SAT_OR_ARO_HET_CONT, 5 },
        { 175, 5, RingCountDef::UNSAT_NON_ARO_C_ONLY, 5 },
        { 176, 5, RingCountDef::UNSAT_NON_ARO_N_CONT, 5 },
        { 177, 5, RingCountDef::UNSAT_NON_ARO_HET_CONT, 5 },

        { 178, 1, RingCountDef::ANY, 6 },
        { 179, 1, RingCountDef::SAT_OR_ARO_C_ONLY, 6 },
        { 180, 1, RingCountDef::SAT_OR_ARO_N_CONT, 6 },
        { 181, 1, RingCountDef::SAT_OR_ARO_HET_CONT, 6 },
        { 182, 1, RingCountDef::UNSAT_NON_ARO_C_ONLY, 6 },
        { 183, 1, RingCountDef::UNSAT_NON_ARO_N_CONT, 6 },
        { 184, 1, RingCountDef::UNSAT_NON_ARO_HET_CONT, 6 },
        { 185, 2, RingCountDef::ANY, 6 },
        { 186, 2, RingCountDef::SAT_OR_ARO_C_ONLY, 6 },
        { 187, 2, RingCountDef::SAT_OR_ARO_N_CONT, 6 },
        { 188, 2, RingCountDef::SAT_OR_ARO_HET_CONT, 6 },
        { 189, 2, RingCountDef::UNSAT_NON_ARO_C_ONLY, 6 },
        { 190, 2, RingCountDef::UNSAT_NON_ARO_N_CONT, 6 },
        { 191, 2, RingCountDef::UNSAT_NON_ARO_HET_CONT, 6 },
        { 192, 3, RingCountDef::ANY, 6 },
        { 193, 3, RingCountDef::SAT_OR_ARO_C_ONLY, 6 },
        { 194, 3, RingCountDef::SAT_OR_ARO_N_CONT, 6 },
        { 195, 3, RingCountDef::SAT_OR_ARO_HET_CONT, 6 },
        { 196, 3, RingCountDef::UNSAT_NON_ARO_C_ONLY, 6 },
        { 197, 3, RingCountDef::UNSAT_NON_ARO_N_CONT, 6 },
        { 198, 3, RingCountDef::UNSAT_NON_ARO_HET_CONT, 6 },
        { 199, 4, RingCountDef::ANY, 6 },
        { 200, 4, RingCountDef::SAT_OR_ARO_C_ONLY, 6 },
        { 201, 4, RingCountDef::SAT_OR_ARO_N_CONT, 6 },
        { 202, 4, RingCountDef::SAT_OR_ARO_HET_CONT, 6 },
        { 203, 4, RingCountDef::UNSAT_NON_ARO_C_ONLY, 6 },
        { 204, 4, RingCountDef::UNSAT_NON_ARO_N_CONT, 6 },
        { 205, 4, RingCountDef::UNSAT_NON_ARO_HET_CONT, 6 },
        { 206, 5, RingCountDef::ANY, 6 },
        { 207, 5, RingCountDef::SAT_OR_ARO_C_ONLY, 6 },
        { 208, 5, RingCountDef::SAT_OR_ARO_N_CONT, 6 },
        { 209, 5, RingCountDef::SAT_OR_ARO_HET_CONT, 6 },
        { 210, 5, RingCountDef::UNSAT_NON_ARO_C_ONLY, 6 },
        { 211, 5, RingCountDef::UNSAT_NON_ARO_N_CONT, 6 },
        { 212, 5, RingCountDef::UNSAT_NON_ARO_HET_CONT, 6 },

        { 213, 1, RingCountDef::ANY, 7 },
        { 214, 1, RingCountDef::SAT_OR_ARO_C_ONLY, 7 },
        { 215, 1, RingCountDef::SAT_OR_ARO_N_CONT, 7 },
        { 216, 1, RingCountDef::SAT_OR_ARO_HET_CONT, 7 },
        { 217, 1, RingCountDef::UNSAT_NON_ARO_C_ONLY, 7 },
        { 218, 1, RingCountDef::UNSAT_NON_ARO_N_CONT, 7 },
        { 219, 1, RingCountDef::UNSAT_NON_ARO_HET_CONT, 7 },
        { 220, 2, RingCountDef::ANY, 7 },
        { 221, 2, RingCountDef::SAT_OR_ARO_C_ONLY, 7 },
        { 222, 2, RingCountDef::SAT_OR_ARO_N_CONT, 7 },
        { 223, 2, RingCountDef::SAT_OR_ARO_HET_CONT, 7 },
        { 224, 2, RingCountDef::UNSAT_NON_ARO_C_ONLY, 7 },
        { 225, 2, RingCountDef::UNSAT_NON_ARO_N_CONT, 7 },
        { 226, 2, RingCountDef::UNSAT_NON_ARO_HET_CONT, 7 },

        { 227, 1, RingCountDef::ANY, 8 },
        { 228, 1, RingCountDef::SAT_OR_ARO_C_ONLY, 8 },
        { 229, 1, RingCountDef::SAT_OR_ARO_N_CONT, 8 },
        { 230, 1, RingCountDef::SAT_OR_ARO_HET_CONT, 8 },
        { 231, 1, RingCountDef::UNSAT_NON_ARO_C_ONLY, 8 },
        { 232, 1, RingCountDef::UNSAT_NON_ARO_N_CONT, 8 },
        { 233, 1, RingCountDef::UNSAT_NON_ARO_HET_CONT, 8 },
        { 234, 2, RingCountDef::ANY, 8 },
        { 235, 2, RingCountDef::SAT_OR_ARO_C_ONLY, 8 },
        { 236, 2, RingCountDef::SAT_OR_ARO_N_CONT, 8 },
        { 237, 2, RingCountDef::SAT_OR_ARO_HET_CONT, 8 },
        { 238, 2, RingCountDef::UNSAT_NON_ARO_C_ONLY, 8 },
        { 239, 2, RingCountDef::UNSAT_NON_ARO_N_CONT, 8 },
        { 240, 2, RingCountDef::UNSAT_NON_ARO_HET_CONT, 8 },

        { 241, 1, RingCountDef::ANY, 9 },
        { 242, 1, RingCountDef::SAT_OR_ARO_C_ONLY, 9 },
        { 243, 1, RingCountDef::SAT_OR_ARO_N_CONT, 9 },
        { 244, 1, RingCountDef::SAT_OR_ARO_HET_CONT, 9 },
        { 245, 1, RingCountDef::UNSAT_NON_ARO_C_ONLY, 9 },
        { 246, 1, RingCountDef::UNSAT_NON_ARO_N_CONT, 9 },
        { 247, 1, RingCountDef::UNSAT_NON_ARO_HET_CONT, 9 },

        { 248, 1, RingCountDef::ANY, 10 },
        { 249, 1, RingCountDef::SAT_OR_ARO_C_ONLY, 10 },
        { 250, 1, RingCountDef::SAT_OR_ARO_N_CONT, 10 },
        { 251, 1, RingCountDef::SAT_OR_ARO_HET_CONT, 10 },
        { 252, 1, RingCountDef::UNSAT_NON_ARO_C_ONLY, 10 },
        { 253, 1, RingCountDef::UNSAT_NON_ARO_N_CONT, 10 },
        { 254, 1, RingCountDef::UNSAT_NON_ARO_HET_CONT, 10 },

        { 255, 1, RingCountDef::AROMATIC, 0 },
        { 256, 1, RingCountDef::HET_AROMATIC, 0 },
        { 257, 2, RingCountDef::AROMATIC, 0 },
        { 258, 2, RingCountDef::HET_AROMATIC, 0 },
        { 259, 3, RingCountDef::AROMATIC, 0 },
        { 260, 3, RingCountDef::HET_AROMATIC, 0 },
        { 261, 4, RingCountDef::AROMATIC, 0 },
        { 262, 4, RingCountDef::HET_AROMATIC, 0 }
    };

    constexpr std::size_t MAX_RING_SIZE = 10;
    
    struct AtomPairDef
    {
        std::size_t  bitIndex;
        unsigned int atomicNo1;
        unsigned int atomicNo2;
    };

    const AtomPairDef ATOM_PAIRS[] = {
        { 263, Chem::AtomType::Li, Chem::AtomType::H },
        { 264, Chem::AtomType::Li, Chem::AtomType::Li },
        { 265, Chem::AtomType::Li, Chem::AtomType::B },
        { 266, Chem::AtomType::Li, Chem::AtomType::C },
        { 267, Chem::AtomType::Li, Chem::AtomType::O },
        { 268, Chem::AtomType::Li, Chem::AtomType::F },
        { 269, Chem::AtomType::Li, Chem::AtomType::P },
        { 270, Chem::AtomType::Li, Chem::AtomType::S },
        { 271, Chem::AtomType::Li, Chem::AtomType::Cl },
        { 272, Chem::AtomType::B, Chem::AtomType::H },
        { 273, Chem::AtomType::B, Chem::AtomType::B },
        { 274, Chem::AtomType::B, Chem::AtomType::C },
        { 275, Chem::AtomType::B, Chem::AtomType::N },
        { 276, Chem::AtomType::B, Chem::AtomType::O },
        { 277, Chem::AtomType::B, Chem::AtomType::F },
        { 278, Chem::AtomType::B, Chem::AtomType::Si },
        { 279, Chem::AtomType::B, Chem::AtomType::P },
        { 280, Chem::AtomType::B, Chem::AtomType::S },
        { 281, Chem::AtomType::B, Chem::AtomType::Cl },
        { 282, Chem::AtomType::B, Chem::AtomType::Br },
        { 283, Chem::AtomType::C, Chem::AtomType::H },
        { 284, Chem::AtomType::C, Chem::AtomType::C },
        { 285, Chem::AtomType::C, Chem::AtomType::N },
        { 286, Chem::AtomType::C, Chem::AtomType::O },
        { 287, Chem::AtomType::C, Chem::AtomType::F },
        { 288, Chem::AtomType::C, Chem::AtomType::Na },
        { 289, Chem::AtomType::C, Chem::AtomType::Mg },
        { 290, Chem::AtomType::C, Chem::AtomType::Al },
        { 291, Chem::AtomType::C, Chem::AtomType::Si },
        { 292, Chem::AtomType::C, Chem::AtomType::P },
        { 293, Chem::AtomType::C, Chem::AtomType::S },
        { 294, Chem::AtomType::C, Chem::AtomType::Cl },
        { 295, Chem::AtomType::C, Chem::AtomType::As },
        { 296, Chem::AtomType::C, Chem::AtomType::Se },
        { 297, Chem::AtomType::C, Chem::AtomType::Br },
        { 298, Chem::AtomType::C, Chem::AtomType::I },
        { 299, Chem::AtomType::N, Chem::AtomType::H },
        { 300, Chem::AtomType::N, Chem::AtomType::N },
        { 301, Chem::AtomType::N, Chem::AtomType::O },
        { 302, Chem::AtomType::N, Chem::AtomType::F },
        { 303, Chem::AtomType::N, Chem::AtomType::Si },
        { 304, Chem::AtomType::N, Chem::AtomType::P },
        { 305, Chem::AtomType::N, Chem::AtomType::S },
        { 306, Chem::AtomType::N, Chem::AtomType::Cl },
        { 307, Chem::AtomType::N, Chem::AtomType::Br },
        { 308, Chem::AtomType::O, Chem::AtomType::H },
        { 309, Chem::AtomType::O, Chem::AtomType::O },
        { 310, Chem::AtomType::O, Chem::AtomType::Mg },
        { 311, Chem::AtomType::O, Chem::AtomType::Na },
        { 312, Chem::AtomType::O, Chem::AtomType::Al },
        { 313, Chem::AtomType::O, Chem::AtomType::Si },
        { 314, Chem::AtomType::O, Chem::AtomType::P },
        { 315, Chem::AtomType::O, Chem::AtomType::K },
        { 316, Chem::AtomType::F, Chem::AtomType::P },
        { 317, Chem::AtomType::F, Chem::AtomType::S },
        { 318, Chem::AtomType::Al, Chem::AtomType::H },
        { 319, Chem::AtomType::Al, Chem::AtomType::Cl },
        { 320, Chem::AtomType::Si, Chem::AtomType::H },
        { 321, Chem::AtomType::Si, Chem::AtomType::Si },
        { 322, Chem::AtomType::Si, Chem::AtomType::Cl },
        { 323, Chem::AtomType::P, Chem::AtomType::H },
        { 324, Chem::AtomType::P, Chem::AtomType::P },
        { 325, Chem::AtomType::As, Chem::AtomType::H },
        { 326, Chem::AtomType::As, Chem::AtomType::As }
    };

    constexpr auto MAX_ATOMIC_NO = Chem::AtomType::Br;

    struct AtomEnvPattern
    {

        AtomEnvPattern(std::size_t bit_idx, unsigned int ctr_atm_type, const char* ptn_str):
            bitIndex(bit_idx), ctrAtomType(ctr_atm_type), pattern(Chem::parseSMARTS(ptn_str))
            {}

            std::size_t                         bitIndex;
            unsigned int                        ctrAtomType;
            Chem::MolecularGraph::SharedPointer pattern;
    };
    
    typedef std::vector<AtomEnvPattern> AtomEnvPatternList;

    struct SubstructPattern
    {

        SubstructPattern(std::size_t bit_idx, const char* ptn_str):
            bitIndex(bit_idx), pattern(Chem::parseSMARTS(ptn_str))
            {}

            std::size_t                         bitIndex;
            Chem::MolecularGraph::SharedPointer pattern;
    };

    typedef std::vector<AtomEnvPattern>   AtomEnvPatternList;
    typedef std::vector<SubstructPattern> SubstructPatternList;

    AtomEnvPatternList   atomEnvPatterns;
    SubstructPatternList substructPatterns;
    std::once_flag       initFlag;

    void init()
    {
        using namespace Chem;

        atomEnvPatterns.emplace_back(327, AtomType::C, "[#6](~[#35])(~[#6])");
        atomEnvPatterns.emplace_back(328, AtomType::C, "[#6](~[#35])(~[#6])(~[#6])");
        atomEnvPatterns.emplace_back(329, AtomType::C, "[#6!H0]~[#35]");
        atomEnvPatterns.emplace_back(330, AtomType::C, "[#6](~[#35])(:[#6])");
        atomEnvPatterns.emplace_back(331, AtomType::C, "[#6](~[#35])(:[#7])");
        atomEnvPatterns.emplace_back(332, AtomType::C, "[#6](~[#6])(~[#6])");
        atomEnvPatterns.emplace_back(333, AtomType::C, "[#6](~[#6])(~[#6])(~[#6])");
        atomEnvPatterns.emplace_back(334, AtomType::C, "[#6](~[#6])(~[#6])(~[#6])(~[#6])");
        atomEnvPatterns.emplace_back(335, AtomType::C, "[#6!H0](~[#6])(~[#6])(~[#6])");
        atomEnvPatterns.emplace_back(336, AtomType::C, "[#6](~[#6])(~[#6])(~[#6])(~[#7])");
        atomEnvPatterns.emplace_back(337, AtomType::C, "[#6](~[#6])(~[#6])(~[#6])(~[#8])");
        atomEnvPatterns.emplace_back(338, AtomType::C, "[#6!H0](~[#6])(~[#6])(~[#7])");
        atomEnvPatterns.emplace_back(339, AtomType::C, "[#6!H0](~[#6])(~[#6])(~[#8])");
        atomEnvPatterns.emplace_back(340, AtomType::C, "[#6](~[#6])(~[#6])(~[#7])");
        atomEnvPatterns.emplace_back(341, AtomType::C, "[#6](~[#6])(~[#6])(~[#8])");
        atomEnvPatterns.emplace_back(342, AtomType::C, "[#6](~[#6])(~[#17])");
        atomEnvPatterns.emplace_back(343, AtomType::C, "[#6!H0](~[#6])(~[#17])");
        atomEnvPatterns.emplace_back(344, AtomType::C, "[#6!H0]~[#6]");
        atomEnvPatterns.emplace_back(345, AtomType::C, "[#6!H0](~[#6])(~[#7])");
        atomEnvPatterns.emplace_back(346, AtomType::C, "[#6!H0](~[#6])(~[#8])");
        atomEnvPatterns.emplace_back(347, AtomType::C, "[#6!H0](~[#6])(~[#8])(~[#8])");
        atomEnvPatterns.emplace_back(348, AtomType::C, "[#6!H0](~[#6])(~[#15])");
        atomEnvPatterns.emplace_back(349, AtomType::C, "[#6!H0](~[#6])(~[#16])");
        atomEnvPatterns.emplace_back(350, AtomType::C, "[#6](~[#6])(~[#53])");
        atomEnvPatterns.emplace_back(351, AtomType::C, "[#6](~[#6])(~[#7])");
        atomEnvPatterns.emplace_back(352, AtomType::C, "[#6](~[#6])(~[#8])");
        atomEnvPatterns.emplace_back(353, AtomType::C, "[#6](~[#6])(~[#16])");
        atomEnvPatterns.emplace_back(354, AtomType::C, "[#6](~[#6])(~[#14])");
        atomEnvPatterns.emplace_back(355, AtomType::C, "[#6](~[#6])(:[#6])");
        atomEnvPatterns.emplace_back(356, AtomType::C, "[#6](~[#6])(:[#6])(:[#6])");
        atomEnvPatterns.emplace_back(357, AtomType::C, "[#6](~[#6])(:[#6])(:[#7])");
        atomEnvPatterns.emplace_back(358, AtomType::C, "[#6](~[#6])(:[#7])");
        atomEnvPatterns.emplace_back(359, AtomType::C, "[#6](~[#6])(:[#7])(:[#7])");
        atomEnvPatterns.emplace_back(360, AtomType::C, "[#6](~[#17])(~[#17])");
        atomEnvPatterns.emplace_back(361, AtomType::C, "[#6!H0]~[#17]");
        atomEnvPatterns.emplace_back(362, AtomType::C, "[#6](~[#17])(:[#6])");
        atomEnvPatterns.emplace_back(363, AtomType::C, "[#6](~[#9])(~[#9])");
        atomEnvPatterns.emplace_back(364, AtomType::C, "[#6](~[#9])(:[#6])");
        atomEnvPatterns.emplace_back(365, AtomType::C, "[#6!H0]~[#7]");
        atomEnvPatterns.emplace_back(366, AtomType::C, "[#6!H0]~[#8]");
        atomEnvPatterns.emplace_back(367, AtomType::C, "[#6!H0](~[#8])(~[#8])");
        atomEnvPatterns.emplace_back(368, AtomType::C, "[#6!H0]~[#16]");
        atomEnvPatterns.emplace_back(369, AtomType::C, "[#6!H0]~[#14]");
        atomEnvPatterns.emplace_back(370, AtomType::C, "[#6!H0]:[#6]");
        atomEnvPatterns.emplace_back(371, AtomType::C, "[#6!H0](:[#6])(:[#6])");
        atomEnvPatterns.emplace_back(372, AtomType::C, "[#6!H0](:[#6])(:[#7])");
        atomEnvPatterns.emplace_back(373, AtomType::C, "[#6!H0]:[#7]");
        atomEnvPatterns.emplace_back(374, AtomType::C, "[#6;H3,H4]");
        atomEnvPatterns.emplace_back(375, AtomType::C, "[#6](~[#7])(~[#7])");
        atomEnvPatterns.emplace_back(376, AtomType::C, "[#6](~[#7])(:[#6])");
        atomEnvPatterns.emplace_back(377, AtomType::C, "[#6](~[#7])(:[#6])(:[#6])");
        atomEnvPatterns.emplace_back(378, AtomType::C, "[#6](~[#7])(:[#6])(:[#7])");
        atomEnvPatterns.emplace_back(379, AtomType::C, "[#6](~[#7])(:[#7])");
        atomEnvPatterns.emplace_back(380, AtomType::C, "[#6](~[#8])(~[#8])");
        atomEnvPatterns.emplace_back(381, AtomType::C, "[#6](~[#8])(:[#6])");
        atomEnvPatterns.emplace_back(382, AtomType::C, "[#6](~[#8])(:[#6])(:[#6])");
        atomEnvPatterns.emplace_back(383, AtomType::C, "[#6](~[#16])(:[#6])");
        atomEnvPatterns.emplace_back(384, AtomType::C, "[#6](:[#6])(:[#6])");
        atomEnvPatterns.emplace_back(385, AtomType::C, "[#6](:[#6])(:[#6])(:[#6])");
        atomEnvPatterns.emplace_back(386, AtomType::C, "[#6](:[#6])(:[#6])(:[#7])");
        atomEnvPatterns.emplace_back(387, AtomType::C, "[#6](:[#6])(:[#7])");
        atomEnvPatterns.emplace_back(388, AtomType::C, "[#6](:[#6])(:[#7])(:[#7])");
        atomEnvPatterns.emplace_back(389, AtomType::C, "[#6](:[#7])(:[#7])");
        atomEnvPatterns.emplace_back(390, AtomType::N, "[#7](~[#6])(~[#6])");
        atomEnvPatterns.emplace_back(391, AtomType::N, "[#7](~[#6])(~[#6])(~[#6])");
        atomEnvPatterns.emplace_back(392, AtomType::N, "[#7!H0](~[#6])(~[#6])");
        atomEnvPatterns.emplace_back(393, AtomType::N, "[#7!H0]~[#6]");
        atomEnvPatterns.emplace_back(394, AtomType::N, "[#7!H0](~[#6])(~[#7])");
        atomEnvPatterns.emplace_back(395, AtomType::N, "[#7](~[#6])(~[#8])");
        atomEnvPatterns.emplace_back(396, AtomType::N, "[#7](~[#6])(:[#6])");
        atomEnvPatterns.emplace_back(397, AtomType::N, "[#7](~[#6])(:[#6])(:[#6])");
        atomEnvPatterns.emplace_back(398, AtomType::N, "[#7!H0]~[#7]");
        atomEnvPatterns.emplace_back(399, AtomType::N, "[#7!H0]:[#6]");
        atomEnvPatterns.emplace_back(400, AtomType::N, "[#7!H0](:[#6])(:[#6])");
        atomEnvPatterns.emplace_back(401, AtomType::N, "[#7](~[#8])(~[#8])");
        atomEnvPatterns.emplace_back(402, AtomType::N, "[#7](~[#8])(:[#8])");
        atomEnvPatterns.emplace_back(403, AtomType::N, "[#7](:[#6])(:[#6])");
        atomEnvPatterns.emplace_back(404, AtomType::N, "[#7](:[#6])(:[#6])(:[#6])");
        atomEnvPatterns.emplace_back(405, AtomType::O, "[#8](~[#6])(~[#6])");
        atomEnvPatterns.emplace_back(406, AtomType::O, "[#8!H0]~[#6]");
        atomEnvPatterns.emplace_back(407, AtomType::O, "[#8](~[#6])(~[#15])");
        atomEnvPatterns.emplace_back(408, AtomType::O, "[#8!H0]~[#16]");
        atomEnvPatterns.emplace_back(409, AtomType::O, "[#8](:[#6])(:[#6])");
        atomEnvPatterns.emplace_back(410, AtomType::P, "[#15](~[#6])(~[#6])");
        atomEnvPatterns.emplace_back(411, AtomType::P, "[#15](~[#8])(~[#8])");
        atomEnvPatterns.emplace_back(412, AtomType::S, "[#16](~[#6])(~[#6])");
        atomEnvPatterns.emplace_back(413, AtomType::S, "[#16!H0]~[#6]");
        atomEnvPatterns.emplace_back(414, AtomType::S, "[#16](~[#6])(~[#8])");
        atomEnvPatterns.emplace_back(415, AtomType::Si, "[#14](~[#6])(~[#6])");

        atomEnvPatterns.emplace_back(416, AtomType::C, "[#6]=,:[#6]");
        atomEnvPatterns.emplace_back(417, AtomType::C, "[#6]#[#6]");
        atomEnvPatterns.emplace_back(418, AtomType::C, "[#6]=,:[#7]");
        atomEnvPatterns.emplace_back(419, AtomType::C, "[#6]#[#7]");
        atomEnvPatterns.emplace_back(420, AtomType::C, "[#6]=,:[#8]");
        atomEnvPatterns.emplace_back(421, AtomType::C, "[#6]=,:[#16]");
        atomEnvPatterns.emplace_back(422, AtomType::N, "[#7]=,:[#7]");
        atomEnvPatterns.emplace_back(423, AtomType::N, "[#7]=,:[#8]");
        atomEnvPatterns.emplace_back(424, AtomType::N, "[#7]=,:[#15]");
        atomEnvPatterns.emplace_back(425, AtomType::P, "[#15]=,:[#8]");
        atomEnvPatterns.emplace_back(426, AtomType::P, "[#15]=,:[#15]");
        atomEnvPatterns.emplace_back(427, AtomType::C, "[#6](#[#6])(-,:[#6])");
        atomEnvPatterns.emplace_back(428, AtomType::C, "[#6!H0]#[#6]");
        atomEnvPatterns.emplace_back(429, AtomType::C, "[#6](#[#7])(-,:[#6])");
        atomEnvPatterns.emplace_back(430, AtomType::C, "[#6](-,:[#6])(-,:[#6])(=,:[#6])");
        atomEnvPatterns.emplace_back(431, AtomType::C, "[#6](-,:[#6])(-,:[#6])(=,:[#7])");
        atomEnvPatterns.emplace_back(432, AtomType::C, "[#6](-,:[#6])(-,:[#6])(=,:[#8])");
        atomEnvPatterns.emplace_back(433, AtomType::C, "[#6](-,:[#6])(-,:[#17])(=,:[#8])");
        atomEnvPatterns.emplace_back(434, AtomType::C, "[#6!H0](-,:[#6])(=,:[#6])");
        atomEnvPatterns.emplace_back(435, AtomType::C, "[#6!H0](-,:[#6])(=,:[#7])");
        atomEnvPatterns.emplace_back(436, AtomType::C, "[#6!H0](-,:[#6])(=,:[#8])");
        atomEnvPatterns.emplace_back(437, AtomType::C, "[#6](-,:[#6])(-,:[#7])(=,:[#6])");
        atomEnvPatterns.emplace_back(438, AtomType::C, "[#6](-,:[#6])(-,:[#7])(=,:[#7])");
        atomEnvPatterns.emplace_back(439, AtomType::C, "[#6](-,:[#6])(-,:[#7])(=,:[#8])");
        atomEnvPatterns.emplace_back(440, AtomType::C, "[#6](-,:[#6])(-,:[#8])(=,:[#8])");
        atomEnvPatterns.emplace_back(441, AtomType::C, "[#6](-,:[#6])(=,:[#6])");
        atomEnvPatterns.emplace_back(442, AtomType::C, "[#6](-,:[#6])(=,:[#7])");
        atomEnvPatterns.emplace_back(443, AtomType::C, "[#6](-,:[#6])(=,:[#8])");
        atomEnvPatterns.emplace_back(444, AtomType::C, "[#6](-,:[#17])(=,:[#8])");
        atomEnvPatterns.emplace_back(445, AtomType::C, "[#6!H0](-,:[#7])(=,:[#6])");
        atomEnvPatterns.emplace_back(446, AtomType::C, "[#6!H0]=,:[#6]");
        atomEnvPatterns.emplace_back(447, AtomType::C, "[#6!H0]=,:[#7]");
        atomEnvPatterns.emplace_back(448, AtomType::C, "[#6!H0]=,:[#8]");
        atomEnvPatterns.emplace_back(449, AtomType::C, "[#6](-,:[#7])(=,:[#6])");
        atomEnvPatterns.emplace_back(450, AtomType::C, "[#6](-,:[#7])(=,:[#7])");
        atomEnvPatterns.emplace_back(451, AtomType::C, "[#6](-,:[#7])(=,:[#8])");
        atomEnvPatterns.emplace_back(452, AtomType::C, "[#6](-,:[#8])(=,:[#8])");
        atomEnvPatterns.emplace_back(453, AtomType::N, "[#7](-,:[#6])(=,:[#6])");
        atomEnvPatterns.emplace_back(454, AtomType::N, "[#7](-,:[#6])(=,:[#8])");
        atomEnvPatterns.emplace_back(455, AtomType::N, "[#7](-,:[#8])(=,:[#8])");
        atomEnvPatterns.emplace_back(456, AtomType::P, "[#15](-,:[#8])(=,:[#8])");
        atomEnvPatterns.emplace_back(457, AtomType::S, "[#16](-,:[#6])(=,:[#8])");
        atomEnvPatterns.emplace_back(458, AtomType::S, "[#16](-,:[#8])(=,:[#8])");
        atomEnvPatterns.emplace_back(459, AtomType::S, "[#16](=,:[#8])(=,:[#8])");
        atomEnvPatterns.emplace_back(458, AtomType::S, "[#16](=,:[#8])(=,:[#8])"); // also sets bit 458

        substructPatterns.emplace_back(460, "[#6]-,:[#6]-,:[#6]#[#6]");
        substructPatterns.emplace_back(461, "[#8]-,:[#6]-,:[#6]=,:[#7]");
        substructPatterns.emplace_back(462, "[#8]-,:[#6]-,:[#6]=,:[#8]");
        substructPatterns.emplace_back(463, "[#7]:[#6]-,:[#16!H0]");
        substructPatterns.emplace_back(464, "[#7]-,:[#6]-,:[#6]=,:[#6]");
        substructPatterns.emplace_back(465, "[#8]=,:[#16]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(466, "[#7]#[#6]-,:[#6]=,:[#6]");
        substructPatterns.emplace_back(467, "[#6]=,:[#7]-,:[#7]-,:[#6]");
        substructPatterns.emplace_back(468, "[#8]=,:[#16]-,:[#6]-,:[#7]");
        substructPatterns.emplace_back(469, "[#16]-,:[#16]-,:[#6]:[#6]");
        substructPatterns.emplace_back(470, "[#6]:[#6]-,:[#6]=,:[#6]");
        substructPatterns.emplace_back(471, "[#16]:[#6]:[#6]:[#6]");
        substructPatterns.emplace_back(472, "[#6]:[#7]:[#6]-,:[#6]");
        substructPatterns.emplace_back(473, "[#16]-,:[#6]:[#7]:[#6]");
        substructPatterns.emplace_back(474, "[#16]:[#6]:[#6]:[#7]");
        substructPatterns.emplace_back(475, "[#16]-,:[#6]=,:[#7]-,:[#6]");
        substructPatterns.emplace_back(476, "[#6]-,:[#8]-,:[#6]=,:[#6]");
        substructPatterns.emplace_back(477, "[#7]-,:[#7]-,:[#6]:[#6]");
        substructPatterns.emplace_back(478, "[#16]-,:[#6]=,:[#7!H0]");
        substructPatterns.emplace_back(479, "[#16]-,:[#6]-,:[#16]-,:[#6]");
        substructPatterns.emplace_back(480, "[#6]:[#16]:[#6]-,:[#6]");
        substructPatterns.emplace_back(481, "[#8]-,:[#16]-,:[#6]:[#6]");
        substructPatterns.emplace_back(482, "[#6]:[#7]-,:[#6]:[#6]");
        substructPatterns.emplace_back(483, "[#7]-,:[#16]-,:[#6]:[#6]");
        substructPatterns.emplace_back(484, "[#7]-,:[#6]:[#7]:[#6]");
        substructPatterns.emplace_back(485, "[#7]:[#6]:[#6]:[#7]");
        substructPatterns.emplace_back(486, "[#7]-,:[#6]:[#7]:[#7]");
        substructPatterns.emplace_back(487, "[#7]-,:[#6]=,:[#7]-,:[#6]");
        substructPatterns.emplace_back(488, "[#7]-,:[#6]=,:[#7!H0]");
        substructPatterns.emplace_back(489, "[#7]-,:[#6]-,:[#16]-,:[#6]");
        substructPatterns.emplace_back(490, "[#6]-,:[#6]-,:[#6]=,:[#6]");
        substructPatterns.emplace_back(491, "[#6]-,:[#7]:[#6!H0]");
        substructPatterns.emplace_back(492, "[#7]-,:[#6]:[#8]:[#6]");
        substructPatterns.emplace_back(493, "[#8]=,:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(494, "[#8]=,:[#6]-,:[#6]:[#7]");
        substructPatterns.emplace_back(495, "[#6]-,:[#7]-,:[#6]:[#6]");
        substructPatterns.emplace_back(496, "[#7]:[#7]-,:[#6!H0]");
        substructPatterns.emplace_back(497, "[#8]-,:[#6]:[#6]:[#7]");
        substructPatterns.emplace_back(498, "[#8]-,:[#6]=,:[#6]-,:[#6]");
        substructPatterns.emplace_back(499, "[#7]-,:[#6]:[#6]:[#7]");
        substructPatterns.emplace_back(500, "[#6]-,:[#16]-,:[#6]:[#6]");
        substructPatterns.emplace_back(501, "[#17]-,:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(502, "[#7]-,:[#6]=,:[#6!H0]");
        substructPatterns.emplace_back(503, "[#17]-,:[#6]:[#6!H0]");
        substructPatterns.emplace_back(504, "[#7]:[#6]:[#7]-,:[#6]");
        substructPatterns.emplace_back(505, "[#17]-,:[#6]:[#6]-,:[#8]");
        substructPatterns.emplace_back(506, "[#6]-,:[#6]:[#7]:[#6]");
        substructPatterns.emplace_back(507, "[#6]-,:[#6]-,:[#16]-,:[#6]");
        substructPatterns.emplace_back(508, "[#16]=,:[#6]-,:[#7]-,:[#6]");
        substructPatterns.emplace_back(509, "[#35]-,:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(510, "[#7!H0]-,:[#7!H0]");
        substructPatterns.emplace_back(511, "[#16]=,:[#6]-,:[#7!H0]");
        substructPatterns.emplace_back(512, "[#6]-,:[#33]-,:[#8!H0]");
        substructPatterns.emplace_back(513, "[#16]:[#6]:[#6!H0]");
        substructPatterns.emplace_back(514, "[#8]-,:[#7]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(515, "[#7]-,:[#7]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(516, "[#6!H0]=,:[#6!H0]");
        substructPatterns.emplace_back(517, "[#7]-,:[#7]-,:[#6]-,:[#7]");
        substructPatterns.emplace_back(518, "[#8]=,:[#6]-,:[#7]-,:[#7]");
        substructPatterns.emplace_back(519, "[#7]=,:[#6]-,:[#7]-,:[#6]");
        substructPatterns.emplace_back(520, "[#6]=,:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(521, "[#6]:[#7]-,:[#6!H0]");
        substructPatterns.emplace_back(522, "[#6]-,:[#7]-,:[#7!H0]");
        substructPatterns.emplace_back(523, "[#7]:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(524, "[#6]-,:[#6]=,:[#6]-,:[#6]");
        substructPatterns.emplace_back(525, "[#33]-,:[#6]:[#6!H0]");
        substructPatterns.emplace_back(526, "[#17]-,:[#6]:[#6]-,:[#17]");
        substructPatterns.emplace_back(527, "[#6]:[#6]:[#7!H0]");
        substructPatterns.emplace_back(528, "[#7!H0]-,:[#6!H0]");
        substructPatterns.emplace_back(529, "[#17]-,:[#6]-,:[#6]-,:[#17]");
        substructPatterns.emplace_back(530, "[#7]:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(531, "[#16]-,:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(532, "[#16]-,:[#6]:[#6!H0]");
        substructPatterns.emplace_back(533, "[#16]-,:[#6]:[#6]-,:[#7]");
        substructPatterns.emplace_back(534, "[#16]-,:[#6]:[#6]-,:[#8]");
        substructPatterns.emplace_back(535, "[#8]=,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(536, "[#8]=,:[#6]-,:[#6]-,:[#7]");
        substructPatterns.emplace_back(537, "[#8]=,:[#6]-,:[#6]-,:[#8]");
        substructPatterns.emplace_back(538, "[#7]=,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(539, "[#7]=,:[#6]-,:[#6!H0]");
        substructPatterns.emplace_back(540, "[#6]-,:[#7]-,:[#6!H0]");
        substructPatterns.emplace_back(541, "[#8]-,:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(542, "[#8]-,:[#6]:[#6!H0]");
        substructPatterns.emplace_back(543, "[#8]-,:[#6]:[#6]-,:[#7]");
        substructPatterns.emplace_back(544, "[#8]-,:[#6]:[#6]-,:[#8]");
        substructPatterns.emplace_back(545, "[#7]-,:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(546, "[#7]-,:[#6]:[#6!H0]");
        substructPatterns.emplace_back(547, "[#7]-,:[#6]:[#6]-,:[#7]");
        substructPatterns.emplace_back(548, "[#8]-,:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(549, "[#7]-,:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(550, "[#17]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(551, "[#17]-,:[#6]-,:[#6]-,:[#8]");
        substructPatterns.emplace_back(552, "[#6]:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(553, "[#8]=,:[#6]-,:[#6]=,:[#6]");
        substructPatterns.emplace_back(554, "[#35]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(555, "[#7]=,:[#6]-,:[#6]=,:[#6]");
        substructPatterns.emplace_back(556, "[#6]=,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(557, "[#7]:[#6]-,:[#8!H0]");
        substructPatterns.emplace_back(558, "[#8]=,:[#7]-,:[#6]:[#6]");
        substructPatterns.emplace_back(559, "[#8]-,:[#6]-,:[#7!H0]");
        substructPatterns.emplace_back(560, "[#7]-,:[#6]-,:[#7]-,:[#6]");
        substructPatterns.emplace_back(561, "[#17]-,:[#6]-,:[#6]=,:[#8]");
        substructPatterns.emplace_back(562, "[#35]-,:[#6]-,:[#6]=,:[#8]");
        substructPatterns.emplace_back(563, "[#8]-,:[#6]-,:[#8]-,:[#6]");
        substructPatterns.emplace_back(564, "[#6]=,:[#6]-,:[#6]=,:[#6]");
        substructPatterns.emplace_back(565, "[#6]:[#6]-,:[#8]-,:[#6]");
        substructPatterns.emplace_back(566, "[#8]-,:[#6]-,:[#6]-,:[#7]");
        substructPatterns.emplace_back(567, "[#8]-,:[#6]-,:[#6]-,:[#8]");
        substructPatterns.emplace_back(568, "[#7]#[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(569, "[#7]-,:[#6]-,:[#6]-,:[#7]");
        substructPatterns.emplace_back(570, "[#6]:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(571, "[#6!H0]-,:[#8!H0]");
        substructPatterns.emplace_back(572, "[#7]:[#6]:[#7]:[#6]");
        substructPatterns.emplace_back(573, "[#8]-,:[#6]-,:[#6]=,:[#6]");
        substructPatterns.emplace_back(574, "[#8]-,:[#6]-,:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(575, "[#8]-,:[#6]-,:[#6]:[#6]-,:[#8]");
        substructPatterns.emplace_back(576, "[#7]=,:[#6]-,:[#6]:[#6!H0]");
        substructPatterns.emplace_back(577, "[#6]:[#6]-,:[#7]-,:[#6]:[#6]");
        substructPatterns.emplace_back(578, "[#6]-,:[#6]:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(579, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(580, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#7]");
        substructPatterns.emplace_back(581, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#8]");
        substructPatterns.emplace_back(582, "[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(583, "[#17]-,:[#6]:[#6]-,:[#8]-,:[#6]");
        substructPatterns.emplace_back(584, "[#6]:[#6]-,:[#6]=,:[#6]-,:[#6]");
        substructPatterns.emplace_back(585, "[#6]-,:[#6]:[#6]-,:[#7]-,:[#6]");
        substructPatterns.emplace_back(586, "[#6]-,:[#16]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(587, "[#7]-,:[#6]:[#6]-,:[#8!H0]");
        substructPatterns.emplace_back(588, "[#8]=,:[#6]-,:[#6]-,:[#6]=,:[#8]");
        substructPatterns.emplace_back(589, "[#6]-,:[#6]:[#6]-,:[#8]-,:[#6]");
        substructPatterns.emplace_back(590, "[#6]-,:[#6]:[#6]-,:[#8!H0]");
        substructPatterns.emplace_back(591, "[#17]-,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(592, "[#7]-,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(593, "[#7]-,:[#6]-,:[#6]-,:[#6]-,:[#7]");
        substructPatterns.emplace_back(594, "[#6]-,:[#8]-,:[#6]-,:[#6]=,:[#6]");
        substructPatterns.emplace_back(595, "[#6]:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(596, "[#7]=,:[#6]-,:[#7]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(597, "[#8]=,:[#6]-,:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(598, "[#17]-,:[#6]:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(599, "[#6!H0]-,:[#6]=,:[#6!H0]");
        substructPatterns.emplace_back(600, "[#7]-,:[#6]:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(601, "[#7]-,:[#6]:[#6]:[#6]-,:[#7]");
        substructPatterns.emplace_back(602, "[#8]=,:[#6]-,:[#6]-,:[#7]-,:[#6]");
        substructPatterns.emplace_back(603, "[#6]-,:[#6]:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(604, "[#6]-,:[#8]-,:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(605, "[#8]=,:[#6]-,:[#6]-,:[#8]-,:[#6]");
        substructPatterns.emplace_back(606, "[#8]-,:[#6]:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(607, "[#7]-,:[#6]-,:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(608, "[#6]-,:[#6]-,:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(609, "[#17]-,:[#6]-,:[#6]-,:[#7]-,:[#6]");
        substructPatterns.emplace_back(610, "[#6]-,:[#8]-,:[#6]-,:[#8]-,:[#6]");
        substructPatterns.emplace_back(611, "[#7]-,:[#6]-,:[#6]-,:[#7]-,:[#6]");
        substructPatterns.emplace_back(612, "[#7]-,:[#6]-,:[#8]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(613, "[#6]-,:[#7]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(614, "[#6]-,:[#6]-,:[#8]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(615, "[#7]-,:[#6]-,:[#6]-,:[#8]-,:[#6]");
        substructPatterns.emplace_back(616, "[#6]:[#6]:[#7]:[#7]:[#6]");
        substructPatterns.emplace_back(617, "[#6]-,:[#6]-,:[#6]-,:[#8!H0]");
        substructPatterns.emplace_back(618, "[#6]:[#6]-,:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(619, "[#8]-,:[#6]-,:[#6]=,:[#6]-,:[#6]");
        substructPatterns.emplace_back(620, "[#6]:[#6]-,:[#8]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(621, "[#7]-,:[#6]:[#6]:[#6]:[#7]");
        substructPatterns.emplace_back(622, "[#8]=,:[#6]-,:[#8]-,:[#6]:[#6]");
        substructPatterns.emplace_back(623, "[#8]=,:[#6]-,:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(624, "[#8]=,:[#6]-,:[#6]:[#6]-,:[#7]");
        substructPatterns.emplace_back(625, "[#8]=,:[#6]-,:[#6]:[#6]-,:[#8]");
        substructPatterns.emplace_back(626, "[#6]-,:[#8]-,:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(627, "[#8]=,:[#33]-,:[#6]:[#6]:[#6]");
        substructPatterns.emplace_back(628, "[#6]-,:[#7]-,:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(629, "[#16]-,:[#6]:[#6]:[#6]-,:[#7]");
        substructPatterns.emplace_back(630, "[#8]-,:[#6]:[#6]-,:[#8]-,:[#6]");
        substructPatterns.emplace_back(631, "[#8]-,:[#6]:[#6]-,:[#8!H0]");
        substructPatterns.emplace_back(632, "[#6]-,:[#6]-,:[#8]-,:[#6]:[#6]");
        substructPatterns.emplace_back(633, "[#7]-,:[#6]-,:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(634, "[#6]-,:[#6]-,:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(635, "[#7]-,:[#7]-,:[#6]-,:[#7!H0]");
        substructPatterns.emplace_back(636, "[#6]-,:[#7]-,:[#6]-,:[#7]-,:[#6]");
        substructPatterns.emplace_back(637, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(638, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#7]");
        substructPatterns.emplace_back(639, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#8]");
        substructPatterns.emplace_back(640, "[#6]=,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(641, "[#8]-,:[#6]-,:[#6]-,:[#6]=,:[#6]");
        substructPatterns.emplace_back(642, "[#8]-,:[#6]-,:[#6]-,:[#6]=,:[#8]");
        substructPatterns.emplace_back(643, "[#6!H0]-,:[#6]-,:[#7!H0]");
        substructPatterns.emplace_back(644, "[#6]-,:[#6]=,:[#7]-,:[#7]-,:[#6]");
        substructPatterns.emplace_back(645, "[#8]=,:[#6]-,:[#7]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(646, "[#8]=,:[#6]-,:[#7]-,:[#6!H0]");
        substructPatterns.emplace_back(647, "[#8]=,:[#6]-,:[#7]-,:[#6]-,:[#7]");
        substructPatterns.emplace_back(648, "[#8]=,:[#7]-,:[#6]:[#6]-,:[#7]");
        substructPatterns.emplace_back(649, "[#8]=,:[#7]-,:[#6]:[#6]-,:[#8]");
        substructPatterns.emplace_back(650, "[#8]=,:[#6]-,:[#7]-,:[#6]=,:[#8]");
        substructPatterns.emplace_back(651, "[#8]-,:[#6]:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(652, "[#8]-,:[#6]:[#6]:[#6]-,:[#7]");
        substructPatterns.emplace_back(653, "[#8]-,:[#6]:[#6]:[#6]-,:[#8]");
        substructPatterns.emplace_back(654, "[#7]-,:[#6]-,:[#7]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(655, "[#8]-,:[#6]-,:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(656, "[#6]-,:[#6]-,:[#7]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(657, "[#6]-,:[#7]-,:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(658, "[#6]-,:[#6]-,:[#16]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(659, "[#8]-,:[#6]-,:[#6]-,:[#7]-,:[#6]");
        substructPatterns.emplace_back(660, "[#6]-,:[#6]=,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(661, "[#8]-,:[#6]-,:[#8]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(662, "[#8]-,:[#6]-,:[#6]-,:[#8]-,:[#6]");
        substructPatterns.emplace_back(663, "[#8]-,:[#6]-,:[#6]-,:[#8!H0]");
        substructPatterns.emplace_back(664, "[#6]-,:[#6]=,:[#6]-,:[#6]=,:[#6]");
        substructPatterns.emplace_back(665, "[#7]-,:[#6]:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(666, "[#6]=,:[#6]-,:[#6]-,:[#8]-,:[#6]");
        substructPatterns.emplace_back(667, "[#6]=,:[#6]-,:[#6]-,:[#8!H0]");
        substructPatterns.emplace_back(668, "[#6]-,:[#6]:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(669, "[#17]-,:[#6]:[#6]-,:[#6]=,:[#8]");
        substructPatterns.emplace_back(670, "[#35]-,:[#6]:[#6]:[#6]-,:[#6]");
        substructPatterns.emplace_back(671, "[#8]=,:[#6]-,:[#6]=,:[#6]-,:[#6]");
        substructPatterns.emplace_back(672, "[#8]=,:[#6]-,:[#6]=,:[#6!H0]");
        substructPatterns.emplace_back(673, "[#8]=,:[#6]-,:[#6]=,:[#6]-,:[#7]");
        substructPatterns.emplace_back(674, "[#7]-,:[#6]-,:[#7]-,:[#6]:[#6]");
        substructPatterns.emplace_back(675, "[#35]-,:[#6]-,:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(676, "[#7]#[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(677, "[#6]-,:[#6]=,:[#6]-,:[#6]:[#6]");
        substructPatterns.emplace_back(678, "[#6]-,:[#6]-,:[#6]=,:[#6]-,:[#6]");
        substructPatterns.emplace_back(679, "[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(680, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(681, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#8]");
        substructPatterns.emplace_back(682, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#7]");
        substructPatterns.emplace_back(683, "[#7]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(684, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(685, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#7]");
        substructPatterns.emplace_back(686, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#8]");
        substructPatterns.emplace_back(687, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#6]=,:[#8]");
        substructPatterns.emplace_back(688, "[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(689, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(690, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#8]");
        substructPatterns.emplace_back(691, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#7]");
        substructPatterns.emplace_back(692, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(693, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#8]");
        substructPatterns.emplace_back(694, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]=,:[#8]");
        substructPatterns.emplace_back(695, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#7]");
        substructPatterns.emplace_back(696, "[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(697, "[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]([#6])-,:[#6]");
        substructPatterns.emplace_back(698, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(699, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]([#6])-,:[#6]");
        substructPatterns.emplace_back(700, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#8]-,:[#6]");
        substructPatterns.emplace_back(701, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]([#8])-,:[#6]");
        substructPatterns.emplace_back(702, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#7]-,:[#6]");
        substructPatterns.emplace_back(703, "[#8]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]([#7])-,:[#6]");
        substructPatterns.emplace_back(704, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(705, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]([#8])-,:[#6]");
        substructPatterns.emplace_back(706, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6](=,:[#8])-,:[#6]");
        substructPatterns.emplace_back(707, "[#8]=,:[#6]-,:[#6]-,:[#6]-,:[#6]-,:[#6]([#7])-,:[#6]");
        substructPatterns.emplace_back(708, "[#6]-,:[#6]([#6])-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(709, "[#6]-,:[#6]([#6])-,:[#6]-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(710, "[#6]-,:[#6]-,:[#6]([#6])-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(711, "[#6]-,:[#6]([#6])([#6])-,:[#6]-,:[#6]");
        substructPatterns.emplace_back(712, "[#6]-,:[#6]([#6])-,:[#6]([#6])-,:[#6]");

        substructPatterns.emplace_back(713, "[#6]c1ccc([#6])cc1");
        substructPatterns.emplace_back(714, "[#6]c1ccc([#8])cc1");
        substructPatterns.emplace_back(715, "[#6]c1ccc([#16])cc1");
        substructPatterns.emplace_back(716, "[#6]c1ccc([#7])cc1");
        substructPatterns.emplace_back(717, "[#6]c1ccc([#17])cc1");
        substructPatterns.emplace_back(718, "[#6]c1ccc([#35])cc1");
        substructPatterns.emplace_back(719, "[#8]c1ccc([#8])cc1");
        substructPatterns.emplace_back(720, "[#8]c1ccc([#16])cc1");
        substructPatterns.emplace_back(721, "[#8]c1ccc([#7])cc1");
        substructPatterns.emplace_back(722, "[#8]c1ccc([#17])cc1");
        substructPatterns.emplace_back(723, "[#8]c1ccc([#35])cc1");
        substructPatterns.emplace_back(724, "[#16]c1ccc([#16])cc1");
        substructPatterns.emplace_back(725, "[#16]c1ccc([#7])cc1");
        substructPatterns.emplace_back(726, "[#16]c1ccc([#17])cc1");
        substructPatterns.emplace_back(727, "[#16]c1ccc([#35])cc1");
        substructPatterns.emplace_back(728, "[#7]c1ccc([#7])cc1");
        substructPatterns.emplace_back(729, "[#7]c1ccc([#17])cc1");
        substructPatterns.emplace_back(730, "[#7]c1ccc([#35])cc1");
        substructPatterns.emplace_back(731, "[#17]c1ccc([#17])cc1");
        substructPatterns.emplace_back(732, "[#17]c1ccc([#35])cc1");
        substructPatterns.emplace_back(733, "[#35]c1ccc([#35])cc1");
        substructPatterns.emplace_back(734, "[#6]c1cc([#6])ccc1");
        substructPatterns.emplace_back(735, "[#6]c1cc([#8])ccc1");
        substructPatterns.emplace_back(736, "[#6]c1cc([#16])ccc1");
        substructPatterns.emplace_back(737, "[#6]c1cc([#7])ccc1");
        substructPatterns.emplace_back(738, "[#6]c1cc([#17])ccc1");
        substructPatterns.emplace_back(739, "[#6]c1cc([#35])ccc1");
        substructPatterns.emplace_back(740, "[#8]c1cc([#8])ccc1");
        substructPatterns.emplace_back(741, "[#8]c1cc([#16])ccc1");
        substructPatterns.emplace_back(742, "[#8]c1cc([#7])ccc1");
        substructPatterns.emplace_back(743, "[#8]c1cc([#17])ccc1");
        substructPatterns.emplace_back(744, "[#8]c1cc([#35])ccc1");
        substructPatterns.emplace_back(745, "[#16]c1cc([#16])ccc1");
        substructPatterns.emplace_back(746, "[#16]c1cc([#7])ccc1");
        substructPatterns.emplace_back(747, "[#16]c1cc([#17])ccc1");
        substructPatterns.emplace_back(748, "[#16]c1cc([#35])ccc1");
        substructPatterns.emplace_back(749, "[#7]c1cc([#7])ccc1");
        substructPatterns.emplace_back(750, "[#7]c1cc([#17])ccc1");
        substructPatterns.emplace_back(751, "[#7]c1cc([#35])ccc1");
        substructPatterns.emplace_back(752, "[#17]c1cc([#17])ccc1");
        substructPatterns.emplace_back(753, "[#17]c1cc([#35])ccc1");
        substructPatterns.emplace_back(754, "[#35]c1cc([#35])ccc1");
        substructPatterns.emplace_back(755, "[#6]c1c([#6])cccc1");
        substructPatterns.emplace_back(756, "[#6]c1c([#8])cccc1");
        substructPatterns.emplace_back(757, "[#6]c1c([#16])cccc1");
        substructPatterns.emplace_back(758, "[#6]c1c([#7])cccc1");
        substructPatterns.emplace_back(759, "[#6]c1c([#17])cccc1");
        substructPatterns.emplace_back(760, "[#6]c1c([#35])cccc1");
        substructPatterns.emplace_back(761, "[#8]c1c([#8])cccc1");
        substructPatterns.emplace_back(762, "[#8]c1c([#16])cccc1");
        substructPatterns.emplace_back(763, "[#8]c1c([#7])cccc1");
        substructPatterns.emplace_back(764, "[#8]c1c([#17])cccc1");
        substructPatterns.emplace_back(765, "[#8]c1c([#35])cccc1");
        substructPatterns.emplace_back(766, "[#16]c1c([#16])cccc1");
        substructPatterns.emplace_back(767, "[#16]c1c([#7])cccc1");
        substructPatterns.emplace_back(768, "[#16]c1c([#17])cccc1");
        substructPatterns.emplace_back(769, "[#16]c1c([#35])cccc1");
        substructPatterns.emplace_back(770, "[#7]c1c([#7])cccc1");
        substructPatterns.emplace_back(771, "[#7]c1c([#17])cccc1");
        substructPatterns.emplace_back(772, "[#7]c1c([#35])cccc1");
        substructPatterns.emplace_back(773, "[#17]c1c([#17])cccc1");
        substructPatterns.emplace_back(774, "[#17]c1c([#35])cccc1");
        substructPatterns.emplace_back(775, "[#35]c1c([#35])cccc1");
        substructPatterns.emplace_back(776, "[#6][#6]1[#6][#6][#6]([#6])[#6][#6]1");
        substructPatterns.emplace_back(777, "[#6][#6]1[#6][#6][#6]([#8])[#6][#6]1");
        substructPatterns.emplace_back(778, "[#6][#6]1[#6][#6][#6]([#16])[#6][#6]1");
        substructPatterns.emplace_back(779, "[#6][#6]1[#6][#6][#6]([#7])[#6][#6]1");
        substructPatterns.emplace_back(780, "[#6][#6]1[#6][#6][#6]([#17])[#6][#6]1");
        substructPatterns.emplace_back(781, "[#6][#6]1[#6][#6][#6]([#35])[#6][#6]1");
        substructPatterns.emplace_back(782, "[#8][#6]1[#6][#6][#6]([#8])[#6][#6]1");
        substructPatterns.emplace_back(783, "[#8][#6]1[#6][#6][#6]([#16])[#6][#6]1");
        substructPatterns.emplace_back(784, "[#8][#6]1[#6][#6][#6]([#7])[#6][#6]1");
        substructPatterns.emplace_back(785, "[#8][#6]1[#6][#6][#6]([#17])[#6][#6]1");
        substructPatterns.emplace_back(786, "[#8][#6]1[#6][#6][#6]([#35])[#6][#6]1");
        substructPatterns.emplace_back(787, "[#16][#6]1[#6][#6][#6]([#16])[#6][#6]1");
        substructPatterns.emplace_back(788, "[#16][#6]1[#6][#6][#6]([#7])[#6][#6]1");
        substructPatterns.emplace_back(789, "[#16][#6]1[#6][#6][#6]([#17])[#6][#6]1");
        substructPatterns.emplace_back(790, "[#16][#6]1[#6][#6][#6]([#35])[#6][#6]1");
        substructPatterns.emplace_back(791, "[#7][#6]1[#6][#6][#6]([#7])[#6][#6]1");
        substructPatterns.emplace_back(792, "[#7][#6]1[#6][#6][#6]([#17])[#6][#6]1");
        substructPatterns.emplace_back(793, "[#7][#6]1[#6][#6][#6]([#35])[#6][#6]1");
        substructPatterns.emplace_back(794, "[#17][#6]1[#6][#6][#6]([#17])[#6][#6]1");
        substructPatterns.emplace_back(795, "[#17][#6]1[#6][#6][#6]([#35])[#6][#6]1");
        substructPatterns.emplace_back(796, "[#35][#6]1[#6][#6][#6]([#35])[#6][#6]1");
        substructPatterns.emplace_back(797, "[#6][#6]1[#6][#6]([#6])[#6][#6][#6]1");
        substructPatterns.emplace_back(798, "[#6][#6]1[#6][#6]([#8])[#6][#6][#6]1");
        substructPatterns.emplace_back(799, "[#6][#6]1[#6][#6]([#16])[#6][#6][#6]1");
        substructPatterns.emplace_back(800, "[#6][#6]1[#6][#6]([#7])[#6][#6][#6]1");
        substructPatterns.emplace_back(801, "[#6][#6]1[#6][#6]([#17])[#6][#6][#6]1");
        substructPatterns.emplace_back(802, "[#6][#6]1[#6][#6]([#35])[#6][#6][#6]1");
        substructPatterns.emplace_back(803, "[#8][#6]1[#6][#6]([#8])[#6][#6][#6]1");
        substructPatterns.emplace_back(804, "[#8][#6]1[#6][#6]([#16])[#6][#6][#6]1");
        substructPatterns.emplace_back(805, "[#8][#6]1[#6][#6]([#7])[#6][#6][#6]1");
        substructPatterns.emplace_back(806, "[#8][#6]1[#6][#6]([#17])[#6][#6][#6]1");
        substructPatterns.emplace_back(807, "[#8][#6]1[#6][#6]([#35])[#6][#6][#6]1");
        substructPatterns.emplace_back(808, "[#16][#6]1[#6][#6]([#16])[#6][#6][#6]1");
        substructPatterns.emplace_back(809, "[#16][#6]1[#6][#6]([#7])[#6][#6][#6]1");
        substructPatterns.emplace_back(810, "[#16][#6]1[#6][#6]([#17])[#6][#6][#6]1");
        substructPatterns.emplace_back(811, "[#16][#6]1[#6][#6]([#35])[#6][#6][#6]1");
        substructPatterns.emplace_back(812, "[#7][#6]1[#6][#6]([#7])[#6][#6][#6]1");
        substructPatterns.emplace_back(813, "[#7][#6]1[#6][#6]([#17])[#6][#6][#6]1");
        substructPatterns.emplace_back(814, "[#7][#6]1[#6][#6]([#35])[#6][#6][#6]1");
        substructPatterns.emplace_back(815, "[#17][#6]1[#6][#6]([#17])[#6][#6][#6]1");
        substructPatterns.emplace_back(816, "[#17][#6]1[#6][#6]([#35])[#6][#6][#6]1");
        substructPatterns.emplace_back(817, "[#35][#6]1[#6][#6]([#35])[#6][#6][#6]1");
        substructPatterns.emplace_back(818, "[#6][#6]1[#6]([#6])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(819, "[#6][#6]1[#6]([#8])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(820, "[#6][#6]1[#6]([#16])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(821, "[#6][#6]1[#6]([#7])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(822, "[#6][#6]1[#6]([#17])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(823, "[#6][#6]1[#6]([#35])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(824, "[#8][#6]1[#6]([#8])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(825, "[#8][#6]1[#6]([#16])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(826, "[#8][#6]1[#6]([#7])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(827, "[#8][#6]1[#6]([#17])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(828, "[#8][#6]1[#6]([#35])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(829, "[#16][#6]1[#6]([#16])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(830, "[#16][#6]1[#6]([#7])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(831, "[#16][#6]1[#6]([#17])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(832, "[#16][#6]1[#6]([#35])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(833, "[#7][#6]1[#6]([#7])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(834, "[#7][#6]1[#6]([#17])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(835, "[#7][#6]1[#6]([#35])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(836, "[#17][#6]1[#6]([#17])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(837, "[#17][#6]1[#6]([#35])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(838, "[#35][#6]1[#6]([#35])[#6][#6][#6][#6]1");
        substructPatterns.emplace_back(839, "[#6][#6]1[#6][#6]([#6])[#6][#6]1");
        substructPatterns.emplace_back(840, "[#6][#6]1[#6][#6]([#8])[#6][#6]1");
        substructPatterns.emplace_back(841, "[#6][#6]1[#6][#6]([#16])[#6][#6]1");
        substructPatterns.emplace_back(842, "[#6][#6]1[#6][#6]([#7])[#6][#6]1");
        substructPatterns.emplace_back(843, "[#6][#6]1[#6][#6]([#17])[#6][#6]1");
        substructPatterns.emplace_back(844, "[#6][#6]1[#6][#6]([#35])[#6][#6]1");
        substructPatterns.emplace_back(845, "[#8][#6]1[#6][#6]([#8])[#6][#6]1");
        substructPatterns.emplace_back(846, "[#8][#6]1[#6][#6]([#16])[#6][#6]1");
        substructPatterns.emplace_back(847, "[#8][#6]1[#6][#6]([#7])[#6][#6]1");
        substructPatterns.emplace_back(848, "[#8][#6]1[#6][#6]([#17])[#6][#6]1");
        substructPatterns.emplace_back(849, "[#8][#6]1[#6][#6]([#35])[#6][#6]1");
        substructPatterns.emplace_back(850, "[#16][#6]1[#6][#6]([#16])[#6][#6]1");
        substructPatterns.emplace_back(851, "[#16][#6]1[#6][#6]([#7])[#6][#6]1");
        substructPatterns.emplace_back(852, "[#16][#6]1[#6][#6]([#17])[#6][#6]1");
        substructPatterns.emplace_back(853, "[#16][#6]1[#6][#6]([#35])[#6][#6]1");
        substructPatterns.emplace_back(854, "[#7][#6]1[#6][#6]([#7])[#6][#6]1");
        substructPatterns.emplace_back(855, "[#7][#6]1[#6][#6]([#17])[#6][#6]1");
        substructPatterns.emplace_back(856, "[#7][#6]1[#6][#6]([#35])[#6][#6]1");
        substructPatterns.emplace_back(857, "[#17][#6]1[#6][#6]([#17])[#6][#6]1");
        substructPatterns.emplace_back(858, "[#17][#6]1[#6][#6]([#35])[#6][#6]1");
        substructPatterns.emplace_back(859, "[#35][#6]1[#6][#6]([#35])[#6][#6]1");
        substructPatterns.emplace_back(860, "[#6][#6]1[#6]([#6])[#6][#6][#6]1");
        substructPatterns.emplace_back(861, "[#6][#6]1[#6]([#8])[#6][#6][#6]1");
        substructPatterns.emplace_back(862, "[#6][#6]1[#6]([#16])[#6][#6][#6]1");
        substructPatterns.emplace_back(863, "[#6][#6]1[#6]([#7])[#6][#6][#6]1");
        substructPatterns.emplace_back(864, "[#6][#6]1[#6]([#17])[#6][#6][#6]1");
        substructPatterns.emplace_back(865, "[#6][#6]1[#6]([#35])[#6][#6][#6]1");
        substructPatterns.emplace_back(866, "[#8][#6]1[#6]([#8])[#6][#6][#6]1");
        substructPatterns.emplace_back(867, "[#8][#6]1[#6]([#16])[#6][#6][#6]1");
        substructPatterns.emplace_back(868, "[#8][#6]1[#6]([#7])[#6][#6][#6]1");
        substructPatterns.emplace_back(869, "[#8][#6]1[#6]([#17])[#6][#6][#6]1");
        substructPatterns.emplace_back(870, "[#8][#6]1[#6]([#35])[#6][#6][#6]1");
        substructPatterns.emplace_back(871, "[#16][#6]1[#6]([#16])[#6][#6][#6]1");
        substructPatterns.emplace_back(872, "[#16][#6]1[#6]([#7])[#6][#6][#6]1");
        substructPatterns.emplace_back(873, "[#16][#6]1[#6]([#17])[#6][#6][#6]1");
        substructPatterns.emplace_back(874, "[#16][#6]1[#6]([#35])[#6][#6][#6]1");
        substructPatterns.emplace_back(875, "[#7][#6]1[#6]([#7])[#6][#6][#6]1");
        substructPatterns.emplace_back(876, "[#7][#6]1[#6]([#17])[#6][#6]1");
        substructPatterns.emplace_back(877, "[#7][#6]1[#6]([#35])[#6][#6][#6]1");
        substructPatterns.emplace_back(878, "[#17][#6]1[#6]([#17])[#6][#6][#6]1");
        substructPatterns.emplace_back(879, "[#17][#6]1[#6]([#35])[#6][#6][#6]1");
        substructPatterns.emplace_back(880, "[#35][#6]1[#6](Br)[#6][#6][#6]1");
    }
}


Descr::PubChemFingerprintGenerator::PubChemFingerprintGenerator()
{
    subSearch.uniqueMappingsOnly(true);
}

Descr::PubChemFingerprintGenerator::PubChemFingerprintGenerator(const PubChemFingerprintGenerator& gen)
{
    subSearch.uniqueMappingsOnly(true);
}

Descr::PubChemFingerprintGenerator::PubChemFingerprintGenerator(const Chem::MolecularGraph& molgraph, Util::BitSet& fp)
{
    subSearch.uniqueMappingsOnly(true);
    
    generate(molgraph, fp);
}

void Descr::PubChemFingerprintGenerator::generate(const Chem::MolecularGraph& molgraph, Util::BitSet& fp)
{
    std::call_once(initFlag, &init);

    fp.resize(NUM_BITS);
    fp.reset();
    
    setElementCountBits(molgraph, fp);
    setRingCountBits(molgraph, fp);
    setAtomPairBits(molgraph, fp);
    setAtomEnvPatternBits(molgraph, fp);
    setSubstructPatternBits(molgraph, fp);
}

void Descr::PubChemFingerprintGenerator::setElementCountBits(const Chem::MolecularGraph& molgraph, Util::BitSet& fp) const
{
    using namespace Chem;

    std::size_t elem_histo[AtomType::MAX_ATOMIC_NO + 1] = { 0 };

    for (auto& atom : molgraph.getAtoms()) {
        auto atom_type = getType(atom);

        if (atom_type == AtomType::UNKNOWN || atom_type > AtomType::MAX_ATOMIC_NO)
            continue;

        elem_histo[atom_type]++;
        elem_histo[AtomType::H] += getImplicitHydrogenCount(atom);
    }

    for (auto& ec : ELEMENT_COUNTS)
        if (elem_histo[ec.atomicNo] >= ec.minCount)
            fp.set(ec.bitIndex);
}

void Descr::PubChemFingerprintGenerator::setRingCountBits(const Chem::MolecularGraph& molgraph, Util::BitSet& fp)
{
    using namespace Chem;
    
    auto num_bonds = molgraph.getNumBonds();

    aromBondMask.resize(num_bonds);

    for (std::size_t i = 0; i < num_bonds; i++)
        aromBondMask.set(i, getAromaticityFlag(molgraph.getBond(i)));
   
    esssr.perceive(molgraph);
    
    std::size_t ring_histo[(MAX_RING_SIZE + 1) * 10] = { 0 };

    for (auto& ring : esssr) {
        auto r_size = ring.getNumBonds();
        bool sat = true;
        bool unsat = true;
        bool aro = true;
        bool c_only = true;
        bool n_found = false;

        for (std::size_t i = 0; i < r_size; i++) {
            auto& atom = ring.getAtom(i);
            auto atom_type = getType(atom);

            if (atom_type != AtomType::C) {
                c_only = false;
                
                if (atom_type == AtomType::N)
                    n_found = true;
            }

            auto& bond = ring.getBond(i);
            auto aro_bond = aromBondMask.test(molgraph.getBondIndex(bond));
                                              
            if (!aro_bond && getOrder(bond) != 1)
                sat = false;

            if (!aro_bond)
                aro = false;
            
            if (!MolProp::isUnsaturated(atom, ring))
                unsat = false;
        }
        
        if (aro)
            aro = Chem::isAromatic(ring, molgraph, aromBondMask);

        if (aro) {
            ring_histo[RingCountDef::AROMATIC]++;

            if (!c_only)
                ring_histo[RingCountDef::HET_AROMATIC]++;
        }

        if (r_size > MAX_RING_SIZE)
            continue;

        ring_histo[r_size * 10 + RingCountDef::ANY]++;
        
        if (sat || aro) {
            if (c_only)
                ring_histo[r_size * 10 + RingCountDef::SAT_OR_ARO_C_ONLY]++;

            else {
                ring_histo[r_size * 10 + RingCountDef::SAT_OR_ARO_HET_CONT]++;

                if (n_found)
                    ring_histo[r_size * 10 + RingCountDef::SAT_OR_ARO_N_CONT]++;
            }
            
        } else if (unsat) {
            if (c_only)
                ring_histo[r_size * 10 + RingCountDef::UNSAT_NON_ARO_C_ONLY]++;

            else {
                ring_histo[r_size * 10 + RingCountDef::UNSAT_NON_ARO_HET_CONT]++;

                if (n_found)
                    ring_histo[r_size * 10 + RingCountDef::UNSAT_NON_ARO_N_CONT]++;
            }
        }
    }

    for (auto& rc : RING_COUNTS)
        if (ring_histo[rc.ringSize * 10 + rc.ringType] >= rc.minCount)
            fp.set(rc.bitIndex);
}

void Descr::PubChemFingerprintGenerator::setAtomPairBits(const Chem::MolecularGraph& molgraph, Util::BitSet& fp)
{
    using namespace Chem;
    
    foundAtomPairs.clear();

    for (auto& bond : molgraph.getBonds()) {
        auto atom1_type = getType(bond.getBegin());

        if (atom1_type == AtomType::UNKNOWN || atom1_type > MAX_ATOMIC_NO)
            continue;

        auto atom2_type = getType(bond.getEnd());

        if (atom2_type == AtomType::UNKNOWN || atom2_type > MAX_ATOMIC_NO)
            continue;

        if (atom1_type == AtomType::H)
            foundAtomPairs.insert(atom2_type * 256 + atom1_type);

        else if (atom2_type == AtomType::H)
            foundAtomPairs.insert(atom1_type * 256 + atom2_type);

        else {
            if (atom1_type <= atom2_type)
                foundAtomPairs.insert(atom1_type * 256 + atom2_type);
            else
                foundAtomPairs.insert(atom2_type * 256 + atom1_type);

            if (getImplicitHydrogenCount(bond.getBegin()) > 0)
                foundAtomPairs.insert(atom1_type * 256 + AtomType::H);

            if (getImplicitHydrogenCount(bond.getEnd()) > 0)
                foundAtomPairs.insert(atom2_type * 256 + AtomType::H);
        }
    }
    
    for (auto& ap : ATOM_PAIRS)
        if (foundAtomPairs.find(ap.atomicNo1 * 256 + ap.atomicNo2) != foundAtomPairs.end())
            fp.set(ap.bitIndex);
}

void Descr::PubChemFingerprintGenerator::setAtomEnvPatternBits(const Chem::MolecularGraph& molgraph, Util::BitSet& fp)
{
    for (auto& aep : atomEnvPatterns) {
        subSearch.setQuery(*aep.pattern);

        for (auto& atom : molgraph.getAtoms()) {
            if (getType(atom) != aep.ctrAtomType)
                continue;

            atomEnv.clear();

            for (auto& bond : atom.getBonds())
                if (molgraph.containsBond(bond) && molgraph.containsAtom(bond.getNeighbor(atom)))
                    atomEnv.addBond(bond);

            if (subSearch.mappingExists(atomEnv)) {
                fp.set(aep.bitIndex);
                break;
            }
        }
    }
}

void Descr::PubChemFingerprintGenerator::setSubstructPatternBits(const Chem::MolecularGraph& molgraph, Util::BitSet& fp)
{
    for (auto& ssp : substructPatterns) {
        subSearch.setQuery(*ssp.pattern);

        if (subSearch.mappingExists(molgraph))
            fp.set(ssp.bitIndex);
    }
}
