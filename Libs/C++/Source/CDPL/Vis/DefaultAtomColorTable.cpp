/* 
 * DefaultAtomColorTable.cpp 
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

#include "CDPL/Vis/DefaultAtomColorTable.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL;


Vis::DefaultAtomColorTable::DefaultAtomColorTable()
{
    insertEntry(Chem::AtomType::C, Color(40.0 / 255.0, 40.0 / 255.0, 40.0 / 255.0));
    insertEntry(Chem::AtomType::O, Color(240.0 / 255.0, 0.0, 0.0));
    insertEntry(Chem::AtomType::H, Color(100.0 / 255.0, 100.0 / 255.0, 100.0 / 255.0));
    insertEntry(Chem::AtomType::N, Color(143.0 / 255.0, 143.0 / 255.0, 255.0 / 255.0));
    insertEntry(Chem::AtomType::S, Color(255.0 / 255.0, 200.0 / 255.0, 50.0 / 255.0));
    insertEntry(Chem::AtomType::Cl, Color(0.0, 1.0, 0.0));
    insertEntry(Chem::AtomType::B, Color(0.0, 1.0, 0.0));
    insertEntry(Chem::AtomType::P, Color(255.0 / 255.0, 165.0 / 255.0, 0.0));
    insertEntry(Chem::AtomType::Fe, Color(255.0 / 255.0, 165.0 / 255.0, 0.0));
    insertEntry(Chem::AtomType::Ba, Color(255.0 / 255.0, 165.0 / 255.0, 0.0));
    insertEntry(Chem::AtomType::Na, Color(0.0, 0.0, 1.0));
    insertEntry(Chem::AtomType::Mg, Color(34.0 / 255.0, 139.0 / 255.0, 34.0 / 255.0));
    insertEntry(Chem::AtomType::Zn, Color(165.0 / 255.0, 42.0 / 255.0, 42.0 / 255.0));
    insertEntry(Chem::AtomType::Cu, Color(165.0 / 255.0, 42.0 / 255.0, 42.0 / 255.0));
    insertEntry(Chem::AtomType::Ni, Color(165.0 / 255.0, 42.0 / 255.0, 42.0 / 255.0));
    insertEntry(Chem::AtomType::Br, Color(165.0 / 255.0, 42.0 / 255.0, 42.0 / 255.0));
    insertEntry(Chem::AtomType::Ca, Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0));
    insertEntry(Chem::AtomType::Mn, Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0));
    insertEntry(Chem::AtomType::Al, Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0));
    insertEntry(Chem::AtomType::Ti, Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0));
    insertEntry(Chem::AtomType::Cr, Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0));
    insertEntry(Chem::AtomType::Ag, Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0));
    insertEntry(Chem::AtomType::F, Color(218.0 / 255.0, 165.0 / 255.0, 32.0 / 255.0));
    insertEntry(Chem::AtomType::Si, Color(218.0 / 255.0, 165.0 / 255.0, 32.0 / 255.0));
    insertEntry(Chem::AtomType::Au, Color(218.0 / 255.0, 165.0 / 255.0, 32.0 / 255.0));
    insertEntry(Chem::AtomType::I, Color(160.0 / 255.0, 32.0 / 255.0, 240.0 / 255.0));
    insertEntry(Chem::AtomType::Li, Color(178.0 / 255.0, 34.0 / 255.0, 34.0 / 255.0));
    insertEntry(Chem::AtomType::He, Color(255.0 / 255.0, 192.0 / 255.0, 203.0 / 255.0));
}
