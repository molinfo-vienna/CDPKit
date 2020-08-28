/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Shape.hpp 
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
 * \brief A convenience header including everything that is defined in namespace CDPL::Shape.
 */

#ifndef CDPL_SHAPE_HPP
#define CDPL_SHAPE_HPP

#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Shape/GaussianShapeSet.hpp"
#include "CDPL/Shape/QuaternionTransformation.hpp"

#include "CDPL/Shape/GaussianShapeGenerator.hpp"

#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/GaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/ExactGaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/FastGaussianShapeOverlapFunction.hpp"

#include "CDPL/Shape/AlignmentResult.hpp"
#include "CDPL/Shape/ScoringFunctions.hpp"
#include "CDPL/Shape/ScoringFunctors.hpp"

#include "CDPL/Shape/GaussianShapeAlignmentStartGenerator.hpp"
#include "CDPL/Shape/PrincipalAxesAlignmentStartGenerator.hpp"
#include "CDPL/Shape/GaussianShapeFunctionAlignment.hpp"
#include "CDPL/Shape/GaussianShapeAlignment.hpp"

#include "CDPL/Shape/ScreeningSettings.hpp"
#include "CDPL/Shape/ScreeningProcessor.hpp"

#include "CDPL/Shape/SymmetryClass.hpp"

#include "CDPL/Shape/GaussianShapeFunctions.hpp"
#include "CDPL/Shape/UtilityFunctions.hpp"

#endif // CDPL_SHAPE_HPP
