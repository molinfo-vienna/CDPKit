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
# \brief Provides preinitialized Base.DataFormat objects for all supported image output formats.
# 
class DataFormat(Boost.Python.instance):

    ##
    # \brief Provides meta-information about the <em>Portable Network Graphics</em> [\ref WPNG] format.
    # 
    PNG = CDPL.Base.DataFormat(name='PNG', descr='Portable Network Graphics Format', mime_type'image/png', file_exts=['png'], multi_rec=False)

    ##
    # \brief Provides meta-information about the <em>Portable Document Format</em> [\ref WPDF].
    # 
    PDF = CDPL.Base.DataFormat(name='PDF', descr='Adobe Portable Document Format', mime_type'application/pdf', file_exts=['pdf'], multi_rec=False)

    ##
    # \brief Provides meta-information about the <em>PostScript</em> [\ref WPS] format.
    # 
    PS = CDPL.Base.DataFormat(name='PS', descr='Adobe PostScript Format', mime_type'application/postscript', file_exts=['ps', 'eps'], multi_rec=False)

    ##
    # \brief Provides meta-information about the <em>Scalable Vector Graphics</em> [\ref WSVG] format.
    # 
    SVG = CDPL.Base.DataFormat(name='SVG', descr='Scalable Vector Graphics Format', mime_type'image/svg+xml', file_exts=['svg'], multi_rec=False)
