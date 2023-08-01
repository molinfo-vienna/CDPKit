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
# \brief A writer for molecular graph data in the <em>Macromolecular Transmission Format (MMTF)</em> [\ref MMTF].
# 
class MMTFMolecularGraphWriter(Chem.MolecularGraphWriterBase):

    ##
    # \brief Constructs a <tt>MMTFMolecularGraphWriter</tt> instance that will write data of molecular graphs to the output stream <em>os</em>.
    # 
    # \param os The output stream to write to.
    # 
    def __init__(os: Base.OStream) -> None: pass
