/* 
 * AtomColorTable.cpp 
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

#include "CDPL/Vis/AtomColorTable.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL;


namespace
{

    const Vis::ColorTable::Entry ELEM_COLORS_2D[] = {
        Vis::ColorTable::Entry(Chem::AtomType::C , Vis::Color( 40.0 / 255.0,  40.0 / 255.0,  40.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::O , Vis::Color(240.0 / 255.0,   0.0        ,   0.0        )),
        Vis::ColorTable::Entry(Chem::AtomType::H , Vis::Color(100.0 / 255.0, 100.0 / 255.0, 100.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::N , Vis::Color(143.0 / 255.0, 143.0 / 255.0, 255.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::S , Vis::Color(255.0 / 255.0, 200.0 / 255.0,  50.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::Cl, Vis::Color(  0.0        ,   1.0        ,   0.0        )),
        Vis::ColorTable::Entry(Chem::AtomType::B , Vis::Color(  0.0        ,   1.0        ,   0.0        )),
        Vis::ColorTable::Entry(Chem::AtomType::P , Vis::Color(255.0 / 255.0, 165.0 / 255.0,   0.0        )),
        Vis::ColorTable::Entry(Chem::AtomType::Fe, Vis::Color(255.0 / 255.0, 165.0 / 255.0,   0.0        )),
        Vis::ColorTable::Entry(Chem::AtomType::Ba, Vis::Color(255.0 / 255.0, 165.0 / 255.0,   0.0        )),
        Vis::ColorTable::Entry(Chem::AtomType::Na, Vis::Color(  0.0        ,   0.0        ,   1.0        )),
        Vis::ColorTable::Entry(Chem::AtomType::Mg, Vis::Color( 34.0 / 255.0, 139.0 / 255.0,  34.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::Zn, Vis::Color(165.0 / 255.0,  42.0 / 255.0,  42.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::Cu, Vis::Color(165.0 / 255.0,  42.0 / 255.0,  42.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::Ni, Vis::Color(165.0 / 255.0,  42.0 / 255.0,  42.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::Br, Vis::Color(165.0 / 255.0,  42.0 / 255.0,  42.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::Ca, Vis::Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::Mn, Vis::Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::Al, Vis::Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::Ti, Vis::Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::Cr, Vis::Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::Ag, Vis::Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::F , Vis::Color(218.0 / 255.0, 165.0 / 255.0,  32.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::Si, Vis::Color(218.0 / 255.0, 165.0 / 255.0,  32.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::Au, Vis::Color(218.0 / 255.0, 165.0 / 255.0,  32.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::I , Vis::Color(160.0 / 255.0,  32.0 / 255.0, 240.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::Li, Vis::Color(178.0 / 255.0,  34.0 / 255.0,  34.0 / 255.0)),
        Vis::ColorTable::Entry(Chem::AtomType::He, Vis::Color(255.0 / 255.0, 192.0 / 255.0, 203.0 / 255.0))
    };
}


namespace CDPL
{

    namespace Vis 
    {

        namespace AtomColorTable
        {

            const ColorTable ELEMENT_COLORS_2D(&ELEM_COLORS_2D[0], &ELEM_COLORS_2D[0] + sizeof(ELEM_COLORS_2D) / sizeof(ColorTable::Entry));
        }

        void initAtomColors() {}
    }
}
