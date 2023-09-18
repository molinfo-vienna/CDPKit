##
# __init__.py  
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


from __future__ import absolute_import

import os
import sys
import platform

if sys.version_info[1] >= 8 and platform.system() == 'Windows':
    if 'site-packages' in __file__:
        os.add_dll_directory(os.path.dirname(__file__))
    else:
        os.add_dll_directory(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), '@CDPKIT_EXECUTABLE_INSTALL_DIR@'))

from ._cdpl import *
