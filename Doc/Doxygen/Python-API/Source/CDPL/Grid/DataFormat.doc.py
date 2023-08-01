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
# \brief Provides preinitialized Base.DataFormat objects for all supported data formats.
# 
class DataFormat(Boost.Python.instance):

    ##
    # \brief Provides meta-information about the native binary <em>CDPL</em> format.
    # 
    CDF = CDPL.Base.DataFormat(name='CDF', descr='Native CDPL-Format', mime_type'', file_exts=['cdf'], multi_rec=True)

    ##
    # \brief Provides meta-information about the gzip-compressed native <em>CDPL</em> format.
    # 
    CDF_GZ = CDPL.Base.DataFormat(name='CDF_GZ', descr='GZip-Compressed Native CDPL-Format', mime_type'', file_exts=['cdf.gz'], multi_rec=True)

    ##
    # \brief Provides meta-information about the bzip2-compressed native <em>CDPL</em> format.
    # 
    CDF_BZ2 = CDPL.Base.DataFormat(name='CDF_BZ2', descr='BZip2-Compressed Native CDPL-Format', mime_type'', file_exts=['cdf.bz2'], multi_rec=True)
