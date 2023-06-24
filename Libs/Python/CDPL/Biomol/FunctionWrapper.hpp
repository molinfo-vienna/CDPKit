/* 
 * FunctionWrapper.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2014 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_PYTHON_BIOMOL_FUNCTIONWRAPPER_HPP
#define CDPL_PYTHON_BIOMOL_FUNCTIONWRAPPER_HPP

#define MAKE_FUNCTION_WRAPPER1(RET_TYPE, FUNC_NAME, ARG_TYPE) \
 RET_TYPE FUNC_NAME##Wrapper1(ARG_TYPE arg)                   \
 {                                                            \
  return CDPL::Biomol::FUNC_NAME(arg);                        \
 }

#define MAKE_FUNCTION_WRAPPER2(RET_TYPE, FUNC_NAME, ARG1_TYPE, ARG2_TYPE) \
 RET_TYPE FUNC_NAME##Wrapper2(ARG1_TYPE arg1, ARG2_TYPE arg2)             \
 {                                                                        \
  return CDPL::Biomol::FUNC_NAME(arg1, arg2);                             \
 }

#define MAKE_FUNCTION_WRAPPER3(RET_TYPE, FUNC_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE) \
 RET_TYPE FUNC_NAME##Wrapper3(ARG1_TYPE arg1, ARG2_TYPE arg2, ARG3_TYPE arg3)        \
 {                                                                                   \
  return CDPL::Biomol::FUNC_NAME(arg1, arg2, arg3);                                  \
 }

#define MAKE_FUNCTION_WRAPPER4(RET_TYPE, FUNC_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE) \
 RET_TYPE FUNC_NAME##Wrapper4(ARG1_TYPE arg1, ARG2_TYPE arg2, ARG3_TYPE arg3, ARG4_TYPE arg4)   \
 {                                                                                              \
  return CDPL::Biomol::FUNC_NAME(arg1, arg2, arg3, arg4);                                       \
 }

#define MAKE_FUNCTION_WRAPPER5(RET_TYPE, FUNC_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE, ARG5_TYPE)    \
 RET_TYPE FUNC_NAME##Wrapper5(ARG1_TYPE arg1, ARG2_TYPE arg2, ARG3_TYPE arg3, ARG4_TYPE arg4, ARG5_TYPE arg5) \
 {                                                                                                            \
  return CDPL::Biomol::FUNC_NAME(arg1, arg2, arg3, arg4, arg5);                                               \
 }

#define MAKE_FUNCTION_WRAPPER6(RET_TYPE, FUNC_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE, ARG5_TYPE, ARG6_TYPE)         \
 RET_TYPE FUNC_NAME##Wrapper6(ARG1_TYPE arg1, ARG2_TYPE arg2, ARG3_TYPE arg3, ARG4_TYPE arg4, ARG5_TYPE arg5, ARG6_TYPE arg6) \
 {                                                                                                                            \
  return CDPL::Biomol::FUNC_NAME(arg1, arg2, arg3, arg4, arg5, arg6);                                                         \
 }

#define MAKE_FUNCTION_WRAPPER7(RET_TYPE, FUNC_NAME, ARG1_TYPE, ARG2_TYPE, ARG3_TYPE, ARG4_TYPE, ARG5_TYPE, ARG6_TYPE, ARG7_TYPE)              \
 RET_TYPE FUNC_NAME##Wrapper7(ARG1_TYPE arg1, ARG2_TYPE arg2, ARG3_TYPE arg3, ARG4_TYPE arg4, ARG5_TYPE arg5, ARG6_TYPE arg6, ARG7_TYPE arg7) \
 {                                                                                                                                            \
  return CDPL::Biomol::FUNC_NAME(arg1, arg2, arg3, arg4, arg5, arg6, arg7);                                                                   \
 }

#endif // CDPL_PYTHON_BIOMOL_FUNCTIONWRAPPER_HPP
