/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GRAILS.hpp 
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
 * \brief A convenience header including everything that is defined in namespace CDPL::GRAILS.
 */

#ifndef CDPL_GRAILS_HPP
#define CDPL_GRAILS_HPP

#include "CDPL/GRAILS/AttributedGridProperty.hpp"
#include "CDPL/GRAILS/AttributedGridPropertyDefault.hpp"

#include "CDPL/GRAILS/GeneralizedBellAtomDensity.hpp"  
#include "CDPL/GRAILS/AtomDensityGridCalculator.hpp"  
#include "CDPL/GRAILS/BuriednessScore.hpp"  
#include "CDPL/GRAILS/BuriednessGridCalculator.hpp"  
#include "CDPL/GRAILS/InteractionScoreGridCalculator.hpp"  
#include "CDPL/GRAILS/InteractionScoreGridSetCalculator.hpp"  
#include "CDPL/GRAILS/DefaultInteractionScoreGridSetCalculator.hpp"  

#include "CDPL/GRAILS/AttributedGridFunctions.hpp"

#endif // CDPL_GRAILS_HPP
