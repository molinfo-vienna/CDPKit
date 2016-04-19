/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Math.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief A convenience header including everything that is defined in namespace CDPL::Math.
 */

#ifndef CDPL_MATH_HPP
#define CDPL_MATH_HPP

#include "CDPL/Math/AffineTransform.hpp"                                        
#include "CDPL/Math/APIPrefix.hpp"                                              
#include "CDPL/Math/MinimizerVariableArrayTraits.hpp"                                          
#include "CDPL/Math/BFGSMinimizer.hpp"                                          
#include "CDPL/Math/Check.hpp"                                                  
#include "CDPL/Math/CommonType.hpp"                                             
#include "CDPL/Math/Config.hpp"                                                 
#include "CDPL/Math/DirectAssignmentProxy.hpp"                                  
#include "CDPL/Math/Expression.hpp"                                             
#include "CDPL/Math/Functional.hpp"                                             
#include "CDPL/Math/IO.hpp"
#include "CDPL/Math/JacobiDiagonalization.hpp"
#include "CDPL/Math/LinearSolve.hpp"
#include "CDPL/Math/LUDecomposition.hpp"
#include "CDPL/Math/MatrixAdapter.hpp"
#include "CDPL/Math/MatrixAssignment.hpp"
#include "CDPL/Math/MatrixExpression.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/MatrixProxy.hpp"
#include "CDPL/Math/MLRModel.hpp"
#include "CDPL/Math/PrimeNumberTable.hpp"
#include "CDPL/Math/QuaternionAdapter.hpp"
#include "CDPL/Math/QuaternionAssignment.hpp"
#include "CDPL/Math/QuaternionExpression.hpp"
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Math/Range.hpp"
#include "CDPL/Math/Slice.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Math/SVDecomposition.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Math/VectorAdapter.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/VectorArrayFunctions.hpp"
#include "CDPL/Math/VectorAssignment.hpp"
#include "CDPL/Math/VectorExpression.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorIterator.hpp"
#include "CDPL/Math/VectorProxy.hpp"

#endif // CDPL_MATH_HPP
