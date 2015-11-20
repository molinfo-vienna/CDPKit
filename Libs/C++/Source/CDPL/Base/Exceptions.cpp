/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Exceptions.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Base::Exception::Exception(const std::string& msg): message(msg) {}

Base::Exception::~Exception() throw() {}

const char* CDPL::Base::Exception::what() const throw()
{
	return message.c_str();
}


Base::ValueError::ValueError(const std::string& msg): Exception(msg) {}

Base::ValueError::~ValueError() throw() {}


Base::NullPointerException::NullPointerException(const std::string& msg): ValueError(msg) {}

Base::NullPointerException::~NullPointerException() throw() {}


Base::RangeError::RangeError(const std::string& msg): ValueError(msg) {}

Base::RangeError::~RangeError() throw() {}


Base::SizeError::SizeError(const std::string& msg): ValueError(msg) {}

Base::SizeError::~SizeError() throw() {}


Base::IndexError::IndexError(const std::string& msg): RangeError(msg) {}

Base::IndexError::~IndexError() throw() {}


Base::ItemNotFound::ItemNotFound(const std::string& msg): Exception(msg) {}

Base::ItemNotFound::~ItemNotFound() throw() {}


Base::BadCast::BadCast(const std::string& msg): Exception(msg) {}

Base::BadCast::~BadCast() throw() {}


Base::OperationFailed::OperationFailed(const std::string& msg): Exception(msg) {}

Base::OperationFailed::~OperationFailed() throw() {}


Base::CalculationFailed::CalculationFailed(const std::string& msg): OperationFailed(msg) {}

Base::CalculationFailed::~CalculationFailed() throw() {}


Base::IOError::IOError(const std::string& msg): OperationFailed(msg) {}

Base::IOError::~IOError() throw() {}
