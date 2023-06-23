/* 
 * ControlParameterFunctions.cpp 
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

#include "CDPL/ConfGen/ControlParameterFunctions.hpp"
#include "CDPL/ConfGen/ControlParameter.hpp"
#include "CDPL/ConfGen/ControlParameterDefault.hpp"
#include "CDPL/Base/ControlParameterContainer.hpp"


using namespace CDPL; 


#define MAKE_CONTROL_PARAM_FUNCTIONS(PARAM_NAME, TYPE, FUNC_INFIX)        \
    TYPE ConfGen::get##FUNC_INFIX##Parameter(const Base::ControlParameterContainer& cntnr) \
    {                                                                    \
        return cntnr.getParameterOrDefault<TYPE>(ControlParameter::PARAM_NAME, \
                                                 ControlParameterDefault::PARAM_NAME); \
    }                                                                    \
                                                                        \
    void ConfGen::set##FUNC_INFIX##Parameter(Base::ControlParameterContainer& cntnr, TYPE arg) \
    {                                                                    \
        cntnr.setParameter(ControlParameter::PARAM_NAME, arg);            \
    }                                                                    \
                                                                        \
    bool ConfGen::has##FUNC_INFIX##Parameter(const Base::ControlParameterContainer& cntnr) \
    {                                                                    \
        return cntnr.isParameterSet(ControlParameter::PARAM_NAME);        \
    }                                                                    \
                                                                        \
    void ConfGen::clear##FUNC_INFIX##Parameter(Base::ControlParameterContainer& cntnr) \
    {                                                                    \
        cntnr.removeParameter(ControlParameter::PARAM_NAME);            \
    }


MAKE_CONTROL_PARAM_FUNCTIONS(STRICT_ERROR_CHECKING, bool, StrictErrorChecking)
