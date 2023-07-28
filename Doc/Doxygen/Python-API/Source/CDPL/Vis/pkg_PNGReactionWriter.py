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
# \brief Creates 2D depictions of chemical reactions in the <em>Portable Network Graphics (PNG)</em> [\ref WPNG] format.
# 
# <tt>PNGReactionWriter</tt> uses Vis.ReactionView2D for the visualization of chemical reactions. All control-parameters and properties provided for the customization of Vis.ReactionView2D are also supported by <tt>PNGReactionWriter</tt>.
# 
class PNGReactionWriter(CDPL.Chem.ReactionWriterBase):

    ##
    # \brief Constructs a <tt>PNGReactionWriter</tt> instance that will write the image data to the output stream <em>os</em>.
    # 
    # \param os The output stream to write to.
    # 
    # \note PNG is a binary format. To avoid data corruption, the output stream has to be opened in binary mode.
    # 
    def __init__(os: CDPL.Base.OStream) -> None: pass
