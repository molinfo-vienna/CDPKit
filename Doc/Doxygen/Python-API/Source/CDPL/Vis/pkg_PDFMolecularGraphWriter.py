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
# \brief Creates 2D structure diagrams of molecular graphs in the <em>Portable Document Format (PDF)</em> [\ref WPDF].
# 
# <tt>PDFMolecularGraphWriter</tt> uses Vis.StructureView2D for the creation of 2D structure diagrams. All control-parameters and properties provided for the customization of Vis.StructureView2D are also supported by <tt>PDFMolecularGraphWriter</tt>.
# 
class PDFMolecularGraphWriter(CDPL.Chem.MolecularGraphWriterBase):

    ##
    # \brief Constructs a <tt>PDFMolecularGraphWriter</tt> instance that will write the image data to the output stream <em>os</em>.
    # 
    # \param os The output stream to write to.
    # 
    # \note PDF is a binary format. To avoid data corruption, the output stream has to be opened in binary mode.
    # 
    def __init__(os: CDPL.Base.OStream) -> None: pass
