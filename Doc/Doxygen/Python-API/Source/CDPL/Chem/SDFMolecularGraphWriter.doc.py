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
# \brief A writer for molecular graph data in the <em>MDL Mol-File</em> [\ref CTFILE] format.
# 
# <tt>SDFMolecularGraphWriter</tt> supports the following control-parameters:
# 
# <table>
#  <tr><th>Control-Parameter</th><th>Default Value (see Chem.ControlParameterDefault)</th><th>Description</th></tr>
#  <tr><td>Chem.ControlParameter.COORDINATES_DIMENSION</td><td><tt>0</tt></td><td>Specifies the dimension of atom coordinates</td></tr>
#  <tr><td>Chem.ControlParameter.STRICT_ERROR_CHECKING</td><td><tt>False</tt></td><td>Specifies whether non-fatal recoverable errors should be ignored or cause a write operation to fail</td></tr>
#  <tr><td>Chem.ControlParameter.BOND_MEMBER_SWAP_STEREO_FIX</td><td><tt>True</tt></td><td>Specifies whether reverse stereo bonds shall be converted to regular stereo bonds by swapping bond start and end atoms</td></tr>
#  <tr><td>Chem.ControlParameter.MULTI_CONF_EXPORT</td><td><tt>True</tt></td><td>Specifies whether to write all molecule conformations on output</td></tr>
#  <tr><td>Chem.ControlParameter.MDL_CTAB_VERSION</td><td><tt>0</tt></td><td>Specifies the desired connection table format</td></tr>
#  <tr><td>Chem.ControlParameter.MDL_IGNORE_PARITY</td><td><tt>True</tt></td><td>Specifies whether the stereo parity of atoms shall be ignored</td></tr>
#  <tr><td>Chem.ControlParameter.MDL_UPDATE_TIMESTAMP</td><td><tt>False</tt></td><td>Specifies whether the timestamp of <em>Mol-</em> and <em>Rxn-File</em> header blocks has to be updated</td></tr>
#  <tr><td>Chem.ControlParameter.MDL_TRIM_STRINGS</td><td><tt>True</tt></td><td>Specifies whether to remove leading and trailing whitespace from string values</td></tr>
#  <tr><td>Chem.ControlParameter.MDL_TRIM_LINES</td><td><tt>False</tt></td><td>Specifies whether to remove leading and trailing whitespace from data lines</td></tr>
#  <tr><td>Chem.ControlParameter.MDL_TRUNCATE_STRINGS</td><td><tt>False</tt></td><td>Specifies whether string values that exceed the size of an output data field may be truncated</td></tr>
#  <tr><td>Chem.ControlParameter.MDL_TRUNCATE_LINES</td><td><tt>False</tt></td><td>Specifies whether data lines that exceed the maximum allowed line length may be truncated</td></tr>
#  <tr><td>Chem.ControlParameter.MDL_IGNORE_LINE_LENGTH_LIMIT</td><td><tt>True</tt></td><td>Specifies whether to check if data lines exceed the maximum allowed line length</td></tr>
# </table>
# 
class SDFMolecularGraphWriter(MolecularGraphWriterBase):

    ##
    # \brief Constructs a <tt>SDFMolecularGraphWriter</tt> instance that will write data of molecular graphs to the output stream <em>os</em>.
    # 
    # \param os The output stream to write to.
    # 
    def __init__(os: Base.OStream) -> None: pass
