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
# \brief A writer for molecular graph data in the <em>Daylight SMARTS</em> [\ref SMARTS] format.
# 
# <tt>SMARTSMolecularGraphWriter</tt> supports the following control-parameters:
# 
# <table>
#  <tr><th>Control-Parameter</th><th>Default Value (see Chem.ControlParameterDefault)</th><th>Description</th></tr>
#  <tr><td>Chem.ControlParameter.STRICT_ERROR_CHECKING</td><td><tt>False</tt></td><td>Specifies whether non-fatal recoverable errors should be ignored or cause a write operation to fail</td></tr>
#  <tr><td>Chem.ControlParameter.RECORD_SEPARATOR</td><td><tt>"\\n"</tt></td><td>Specifies the data record separator</td></tr>
# </table>
# 
class SMARTSMolecularGraphWriter(MolecularGraphWriterBase):

    ##
    # \brief Constructs a <tt>SMARTSMolecularGraphWriter</tt> instance that will write data of molecular graphs to the output stream <em>os</em>.
    # 
    # \param os The output stream to write to.
    # 
    def __init__(os: CDPL.Base.OStream) -> None: pass
