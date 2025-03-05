#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
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
#

##
# \brief A safe, type checked container for arbitrary data of variable type.
# 
# The code is based on the <tt>std::experimental.any</tt> (N4562, merged into C++17) implementation for C++11 compilers by <a href="https://github.com/thelink2012">Denilson das Mercês Amorim</a>. <tt>Any</tt> provides an optimization for small objects objects with a size of up to 2 words such as <tt>int</tt>, <tt>float</tt> and <tt>std::shared_ptr</tt>. Storing those objects in the container will not trigger a dynamic allocation.
# 
# For more details see [\ref ANY].
# 
class Any(Boost.Python.instance):
    pass
