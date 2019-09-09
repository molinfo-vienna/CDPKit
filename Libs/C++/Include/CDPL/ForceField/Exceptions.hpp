/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Exceptions.hpp 
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
 * \brief Definition of exception classes.
 */

#ifndef CDPL_FORCEFIELD_EXCEPTIONS_HPP
#define CDPL_FORCEFIELD_EXCEPTIONS_HPP

#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/ForceField/APIPrefix.hpp"


namespace CDPL 
{

    namespace ForceField
    {

	/**
	 * \addtogroup CDPL_FORCEFIELD_EXCEPTIONS
	 * @{
	 */

	class CDPL_FORCEFIELD_API Error : public Base::Exception
	{

	  public:
	    Error(const std::string& msg = "");

	    virtual ~Error() throw();
	};

	class CDPL_FORCEFIELD_API ParameterizationFailed : public Error
	{

	  public:
	    ParameterizationFailed(const std::string& msg = "");

	    virtual ~ParameterizationFailed() throw();
	};

	/**
	 * @}
	 */
    }
}

#endif // CDPL_FORCEFIELD_EXCEPTIONS_HPP
