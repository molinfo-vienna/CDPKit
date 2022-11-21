/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolProp.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief A convenience header including everything that is defined in namespace CDPL::MolProp.
 */

#ifndef CDPL_MOLPROP_HPP
#define CDPL_MOLPROP_HPP

#include "CDPL/MolProp/AtomProperty.hpp"
#include "CDPL/MolProp/BondProperty.hpp"

#include "CDPL/MolProp/MassComposition.hpp"
#include "CDPL/MolProp/ElementHistogram.hpp"

#include "CDPL/MolProp/CoordinationGeometry.hpp"

#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/MolProp/BondFunctions.hpp"
#include "CDPL/MolProp/AtomContainerFunctions.hpp"
#include "CDPL/MolProp/BondContainerFunctions.hpp"
#include "CDPL/MolProp/MolecularGraphFunctions.hpp"

#include "CDPL/MolProp/TPSACalculator.hpp"
#include "CDPL/MolProp/AtomHydrophobicityCalculator.hpp"
#include "CDPL/MolProp/LogSCalculator.hpp"
#include "CDPL/MolProp/XLogPCalculator.hpp"
#include "CDPL/MolProp/PEOESigmaChargeCalculator.hpp"
#include "CDPL/MolProp/MHMOPiChargeCalculator.hpp"

#endif // CDPL_MOLPROP_HPP
