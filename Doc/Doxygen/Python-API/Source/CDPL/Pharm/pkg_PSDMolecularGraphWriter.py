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
# \brief A writer for molecular graph data in the PSD-format of the <em>CDPL</em>.
# 
class PSDMolecularGraphWriter(CDPL.Chem.MolecularGraphWriterBase):

    ##
    # \brief Constructs a <tt>PSDMolecularGraphWriter</tt> instance that will write the molecular graph data to the I/O stream <em>ios</em>.
    # 
    # \param ios The I/O stream to write to.
    # 
    def __init__(ios: CDPL.Base.IOStream) -> None: pass

    ##
    # \brief Constructs a <tt>PSDMolecularGraphWriter</tt> instance that will write the molecular graph data to the output file <em>file_name</em>.
    # 
    # \param file_name The output file to write to.
    # 
    def __init__(file_name: str) -> None: pass
