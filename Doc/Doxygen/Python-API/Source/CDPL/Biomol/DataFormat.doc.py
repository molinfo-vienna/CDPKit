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
# \brief Provides preinitialized Base.DataFormat objects for all supported biopolymer data formats.
# 
class DataFormat(Boost.Python.instance):

    ##
    # \brief Provides meta-information about the <em>Brookhaven Protein Data Bank Format</em> [\ref PDB] format.
    # 
    PDB = CDPL.Base.DataFormat(name='PDB', descr='Brookhaven Protein Data Bank Entry', mime_type'chemical/x-pdb', file_exts=['pdb', 'ent'], multi_rec=False)

    ##
    # \brief Provides meta-information about the gzip-compressed <em>Brookhaven Protein Data Bank Format</em> [\ref PDB] format.
    # 
    PDB_GZ = CDPL.Base.DataFormat(name='PDB_GZ', descr='GZip-Compressed Brookhaven Protein Data Bank Entry', mime_type'chemical/x-pdb', file_exts=['pdb.gz', 'ent.gz'], multi_rec=False)

    ##
    # \brief Provides meta-information about the bzip2-compressed <em>Brookhaven Protein Data Bank Format</em> [\ref PDB] format.
    # 
    PDB_BZ2 = CDPL.Base.DataFormat(name='PDB_BZ2', descr='BZip2-Compressed Brookhaven Protein Data Bank Entry', mime_type'chemical/x-pdb', file_exts=['pdb.bz2', 'ent.bz2'], multi_rec=False)

    ##
    # \brief Provides meta-information about the <em>Macromolecular Transmission Format</em> [\ref MMTF] format.
    # 
    # \since 1.2
    # 
    MMTF = CDPL.Base.DataFormat(name='MMTF', descr='Macromolecular Transmission Format', mime_type'chemical/x-mmtf', file_exts=['mmtf'], multi_rec=False)

    ##
    # \brief Provides meta-information about the gzip-compressed <em>Macromolecular Transmission Format</em> [\ref MMTF] format.
    # 
    # \since 1.2
    # 
    MMTF_GZ = CDPL.Base.DataFormat(name='MMTF_GZ', descr='GZip-Compressed Macromolecular Transmission Format', mime_type'chemical/x-mmtf', file_exts=['mmtf.gz'], multi_rec=False)

    ##
    # \brief Provides meta-information about the bzip2-compressed <em>Macromolecular Transmission Format</em> [\ref MMTF] format.
    # 
    # \since 1.2
    # 
    MMTF_BZ2 = CDPL.Base.DataFormat(name='MMTF_BZ2', descr='BZip2-Compressed Macromolecular Transmission Format', mime_type'chemical/x-mmtf', file_exts=['mmtf.bz2'], multi_rec=False)

    ##
    # \brief Provides meta-information about the <em>Macromolecular Crystallographic Information File Format</em> [\ref MMCIF] format.
    # 
    MMCIF = CDPL.Base.DataFormat(name='MMCIF', descr='Macromolecular Crystallographic Information File', mime_type'chemical/x-mmcif', file_exts=['mmcif', 'cif'], multi_rec=True)

    ##
    # \brief Provides meta-information about the gzip-compressed <em>Macromolecular Crystallographic Information File Format</em> [\ref MMCIF] format.
    # 
    MMCIF_GZ = CDPL.Base.DataFormat(name='MMCIF_GZ', descr='GZip-Compressed Macromolecular Crystallographic Information File', mime_type'chemical/x-mmcif', file_exts=['mmcif.gz', 'cif.gz'], multi_rec=True)

    ##
    # \brief Provides meta-information about the bzip2-compressed <em>Macromolecular Crystallographic Information File Format</em> [\ref MMCIF] format.
    # 
    MMCIF_BZ2 = CDPL.Base.DataFormat(name='MMCIF_BZ2', descr='BZip2-Compressed Macromolecular Crystallographic Information File', mime_type'chemical/x-mmcif', file_exts=['mmcif.bz2', 'cif.bz2'], multi_rec=True)
