/* 
 * DefaultFeatureColorTable.cpp 
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

#include "CDPL/Vis/DefaultFeatureColorTable.hpp"
#include "CDPL/Pharm/FeatureType.hpp"


using namespace CDPL;


Vis::DefaultFeatureColorTable::DefaultFeatureColorTable()
{
    insertEntry(Pharm::FeatureType::AROMATIC, Color(0.14, 0.15, 0.45, 0.3));
    insertEntry(Pharm::FeatureType::HYDROPHOBIC, Color(0.8, 0.6, 0.04, 0.2));
    insertEntry(Pharm::FeatureType::POSITIVE_IONIZABLE, Color(0.12, 0.12, 0.48, 0.3));
    insertEntry(Pharm::FeatureType::NEGATIVE_IONIZABLE, Color(0.48, 0.12, 0.12, 0.3));
    insertEntry(Pharm::FeatureType::H_BOND_DONOR, Color(0.12, 0.48, 0.12, 0.5));
    insertEntry(Pharm::FeatureType::H_BOND_ACCEPTOR, Color(0.48, 0.12, 0.12, 0.5));
    insertEntry(Pharm::FeatureType::HALOGEN_BOND_DONOR, Color(0.69, 0.4, 0.69, 0.5));
    insertEntry(Pharm::FeatureType::HALOGEN_BOND_ACCEPTOR, Color(0.69, 0.4, 0.69, 0.5));
    insertEntry(Pharm::FeatureType::EXCLUSION_VOLUME, Color(0.24, 0.24, 0.24, 0.2));
    insertEntry(Pharm::FeatureType::UNKNOWN, Color(0.6, 0.5, 0.0, 0.5));
}
