/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * LookupKeyDefinition.hpp 
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
 * \brief Definition of the preprocessor macro \ref CDPL_DEFINE_LOOKUP_KEY.
 */

#ifndef CDPL_BASE_LOOKUPKEYDEFINITION_HPP
#define CDPL_BASE_LOOKUPKEYDEFINITION_HPP

#include "CDPL/Base/LookupKey.hpp"

/**
 * \addtogroup CDPL_BASE_CONTROL_PARAMETERS_AND_PROPERTIES
 * @{
 */

/**
 * \brief Defines a constant CDPL::Base::LookupKey variable with the specified name.
 *
 * The variable is initialized with a new unique CDPL::Base::LookupKey instance
 * created by a call to CDPL::Base::LookupKey::create(const std::string& name).
 *
 * \param name The name of the variable to define.
 */
#define CDPL_DEFINE_LOOKUP_KEY(name) \
const CDPL::Base::LookupKey name = CDPL::Base::LookupKey::create(#name);

/**
 * @}
 */

#endif // CDPL_BASE_LOOKUPKEYDEFINITION_HPP
