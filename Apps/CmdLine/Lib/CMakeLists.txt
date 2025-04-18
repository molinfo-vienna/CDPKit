##
# CMakeLists.txt  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
##

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}")

set(cmdline_LIB_SRCS
  CmdLineBase.cpp
  HelperFunctions.cpp)

add_library(cmdline-static STATIC ${cmdline_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

set_target_properties(cmdline-static PROPERTIES 
  OUTPUT_NAME cmdline
  CLEAN_DIRECT_OUTPUT 1)

target_link_libraries(cmdline-static Boost::program_options)

if(CXX_FILESYSTEM_HAVE_FS)
  target_link_libraries(cmdline-static std::filesystem)
else()
  target_link_libraries(cmdline-static Boost::filesystem)
endif(CXX_FILESYSTEM_HAVE_FS)
