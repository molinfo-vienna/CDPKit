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
# \brief Provides preinitialized Base.DataFormat objects for all supported chemical data formats.
# 
class DataFormat(Boost.Python.instance):

    ##
    # \brief Provides meta-information about the native I/O format of the <em>JME Molecular Editor</em> [\ref JME] java applet.
    # 
    JME = CDPL.Base.DataFormat(name='JME', descr='JME Molecular Editor String', mime_type'', file_exts=['jme'], multi_rec=True)

    ##
    # \brief Provides meta-information about the native <em>CDPL</em> format.
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

    ##
    # \brief Provides meta-information about the <em>MDL Mol-File</em> [\ref CTFILE] format.
    # 
    MOL = CDPL.Base.DataFormat(name='MOL', descr='MDL Molfile', mime_type'chemical/x-mdl-molfile', file_exts=['mol'], multi_rec=True)

    ##
    # \brief Provides meta-information about the <em>MDL RD-File</em> [\ref CTFILE] format.
    # 
    RDF = CDPL.Base.DataFormat(name='RDF', descr='MDL Reaction-Data File', mime_type'chemical/x-mdl-rdfile', file_exts=['rdf', 'rd'], multi_rec=True)

    ##
    # \brief Provides meta-information about the gzip-compressed <em>MDL RD-File</em> [\ref CTFILE] format.
    # 
    RDF_GZ = CDPL.Base.DataFormat(name='RDF_GZ', descr='GZip-Compressed MDL Reaction-Data File', mime_type'chemical/x-mdl-rdfile', file_exts=['rdf.gz', 'rd.gz', 'rdz'], multi_rec=True)

    ##
    # \brief Provides meta-information about the bzip2-compressed <em>MDL RD-File</em> [\ref CTFILE] format.
    # 
    RDF_BZ2 = CDPL.Base.DataFormat(name='RDF_BZ2', descr='BZip2-Compressed MDL Reaction-Data File', mime_type'chemical/x-mdl-rdfile', file_exts=['rdf.bz2', 'rd.bz2'], multi_rec=True)

    ##
    # \brief Provides meta-information about the <em>MDL Rxn-File</em> [\ref CTFILE] format.
    # 
    RXN = CDPL.Base.DataFormat(name='RXN', descr='MDL Reaction File', mime_type'chemical/x-mdl-rxnfile', file_exts=['rxn'], multi_rec=True)

    ##
    # \brief Provides meta-information about the <em>MDL SD-File</em> [\ref CTFILE] format.
    # 
    SDF = CDPL.Base.DataFormat(name='SDF', descr='MDL Structure-Data File', mime_type'chemical/x-mdl-sdfile', file_exts=['sdf', 'sd'], multi_rec=True)

    ##
    # \brief Provides meta-information about the gzip-compressed <em>MDL SD-File</em> [\ref CTFILE] format.
    # 
    SDF_GZ = CDPL.Base.DataFormat(name='SDF_GZ', descr='GZip-Compressed MDL Structure-Data File', mime_type'chemical/x-mdl-sdfile', file_exts=['sdf.gz', 'sd.gz', 'sdz'], multi_rec=True)

    ##
    # \brief Provides meta-information about the bzip2-compressed <em>MDL SD-File</em> [\ref CTFILE] format.
    # 
    SDF_BZ2 = CDPL.Base.DataFormat(name='SDF_BZ2', descr='BZip2-Compressed MDL Structure-Data File', mime_type'chemical/x-mdl-sdfile', file_exts=['sdf.bz2', 'sd.bz2'], multi_rec=True)

    ##
    # \brief Provides meta-information about the <em>Daylight SMARTS</em> [\ref SMARTS] format.
    # 
    SMARTS = CDPL.Base.DataFormat(name='SMARTS', descr='Daylight SMARTS String', mime_type'', file_exts=['sma'], multi_rec=True)

    ##
    # \brief Provides meta-information about the <em>Daylight SMILES</em> [\ref SMILES] format.
    # 
    SMILES = CDPL.Base.DataFormat(name='SMILES', descr='Daylight SMILES String', mime_type'chemical/x-daylight-smiles', file_exts=['smi'], multi_rec=True)

    ##
    # \brief Provides meta-information about the gzip-compressed <em>Daylight SMILES</em> [\ref SMILES] format.
    # 
    SMILES_GZ = CDPL.Base.DataFormat(name='SMILES_GZ', descr='GZip-Compressed Daylight SMILES String', mime_type'chemical/x-daylight-smiles', file_exts=['smi.gz'], multi_rec=True)

    ##
    # \brief Provides meta-information about the bzip2-compressed <em>Daylight SMILES</em> [\ref SMILES] format.
    # 
    SMILES_BZ2 = CDPL.Base.DataFormat(name='SMILES_BZ2', descr='BZip2-Compressed Daylight SMILES String', mime_type'chemical/x-daylight-smiles', file_exts=['smi.bz2'], multi_rec=True)

    ##
    # \brief Provides meta-information about the <em>IUPAC International Chemical Identifier (InChI)</em> [\ref INCHI] format.
    # 
    INCHI = CDPL.Base.DataFormat(name='INCHI', descr='IUPAC International Chemical Identifier', mime_type'chemical/x-inchi', file_exts=['inchi', 'ichi'], multi_rec=True)

    ##
    # \brief Provides meta-information about the <em>Sybyl MOL2</em> format.
    # 
    MOL2 = CDPL.Base.DataFormat(name='MOL2', descr='Tripos Sybyl MOL2 File', mime_type'', file_exts=['mol2'], multi_rec=True)

    ##
    # \brief Provides meta-information about the gzip-compressed <em>Sybyl MOL2</em> format.
    # 
    MOL2_GZ = CDPL.Base.DataFormat(name='MOL2_GZ', descr='GZip-Compressed Tripos Sybyl MOL2 File', mime_type'', file_exts=['mol2.gz'], multi_rec=True)

    ##
    # \brief Provides meta-information about the bzip2-compressed <em>Sybyl MOL2</em> format.
    # 
    MOL2_BZ2 = CDPL.Base.DataFormat(name='MOL2_BZ2', descr='BZip2-Compressed Tripos Sybyl MOL2 File', mime_type'', file_exts=['mol2.bz2'], multi_rec=True)

    ##
    # \brief Provides meta-information about the <em>XYZ</em> format.
    # 
    XYZ = CDPL.Base.DataFormat(name='XYZ', descr='Atomic Coordinates XYZ File', mime_type'', file_exts=['xyz'], multi_rec=True)

    ##
    # \brief Provides meta-information about the gzip-compressed <em>XYZ</em> format.
    # 
    XYZ_GZ = CDPL.Base.DataFormat(name='XYZ_GZ', descr='GZip-Compressed Atomic Coordinates XYZ File', mime_type'', file_exts=['xyz.gz'], multi_rec=True)

    ##
    # \brief Provides meta-information about the bzip2-compressed <em>XYZ</em> format.
    # 
    XYZ_BZ2 = CDPL.Base.DataFormat(name='XYZ_BZ2', descr='BZip2-Compressed Atomic Coordinates XYZ File', mime_type'', file_exts=['xyz.bz2'], multi_rec=True)
