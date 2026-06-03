/* 
 * FeatureCompareFunction.hpp 
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

/**
 * \file
 * \brief Type declaration of a generic wrapper class for storing user-defined Pharm::Feature compare functions.
 */

#ifndef CDPL_PHARM_FEATURECOMPAREFUNCTION_HPP
#define CDPL_PHARM_FEATURECOMPAREFUNCTION_HPP

#include <functional>


namespace CDPL
{

    namespace Pharm
    {

        class Feature;

        /**
         * \brief Generic wrapper class used to store a user-defined feature compare function.
         */
        typedef std::function<bool(const Feature&, const Feature&)> FeatureCompareFunction;
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FEATURECOMPAREFUNCTION_HPP
