# -*- mode: CMake -*-

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

IF(Qt5Gui_FOUND AND Qt5Widgets_FOUND AND Qt5PrintSupport_FOUND)
  ADD_SUBDIRECTORY(ChOX) 
ENDIF(Qt5Gui_FOUND AND Qt5Widgets_FOUND AND Qt5PrintSupport_FOUND)

IF(Boost_PROGRAM_OPTIONS_FOUND AND Threads_FOUND)
  ADD_SUBDIRECTORY(CmdLine) 
ENDIF(Boost_PROGRAM_OPTIONS_FOUND AND Threads_FOUND)
