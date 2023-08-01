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
# \brief A writer for reaction data in the <em>Daylight SMILES</em> [\ref SMILES] format.
# 
# <tt>SMILESReactionWriter</tt> supports the following control-parameters:
# 
# <table>
#  <tr><th>Control-Parameter</th><th>Default Value (see Chem.ControlParameterDefault)</th><th>Description</th></tr>
#  <tr><td>Chem.ControlParameter.STRICT_ERROR_CHECKING</td><td><tt>False</tt></td><td>Specifies whether non-fatal recoverable errors should be ignored or cause a write operation to fail</td></tr>
#  <tr><td>Chem.ControlParameter.ORDINARY_HYDROGEN_DEPLETE</td><td><tt>True</tt></td><td>Specifies whether or not to write explicit ordinary hydrogen atoms</td></tr>
#  <tr><td>Chem.ControlParameter.SMILES_RECORD_FORMAT</td><td><tt>"S"</tt></td><td>Specifies the data record format</td></tr>
#  <tr><td>Chem.ControlParameter.SMILES_WRITE_CANONICAL_FORM</td><td><tt>False</tt></td><td>Specifies whether to generate canonical <em>SMILES</em> strings</td></tr>
#  <tr><td>Chem.ControlParameter.SMILES_WRITE_KEKULE_FORM</td><td><tt>False</tt></td><td>Specifies whether to output aromatic rings as <em>Kekul&eacute;</em> structures</td></tr>
#  <tr><td>Chem.ControlParameter.SMILES_WRITE_ATOM_STEREO</td><td><tt>True</tt></td><td>Specifies whether to output the chirality of tetrahedral stereogenic atoms</td></tr>
#  <tr><td>Chem.ControlParameter.SMILES_WRITE_BOND_STEREO</td><td><tt>True</tt></td><td>Specifies whether to output directional bonds for the specification of chain double bond geometries</td></tr>
#  <tr><td>Chem.ControlParameter.SMILES_WRITE_RING_BOND_STEREO</td><td><tt>True</tt></td><td>Specifies whether to output directional bonds for the specification of ring double bond geometries</td></tr>
#  <tr><td>Chem.ControlParameter.SMILES_MIN_STEREO_BOND_RING_SIZE</td><td><tt>8</tt></td><td>Specifies the minimum ring size that is required for the specification of ring double bond geometries</td></tr>
#  <tr><td>Chem.ControlParameter.SMILES_WRITE_ISOTOPE</td><td><tt>True</tt></td><td>Specifies whether to output the mass of isotopes</td></tr>
#  <tr><td>Chem.ControlParameter.SMILES_RXN_WRITE_ATOM_MAPPING_ID</td><td><tt>True</tt></td><td>Specifies whether to output reaction atom-atom mapping numbers</td></tr>
#  <tr><td>Chem.ControlParameter.SMILES_WRITE_SINGLE_BONDS</td><td><tt>False</tt></td><td>Specifies whether to output single bonds</td></tr>
#  <tr><td>Chem.ControlParameter.SMILES_WRITE_AROMATIC_BONDS</td><td><tt>False</tt></td><td>Specifies whether to output aromatic bonds</td></tr>
#  <tr><td>Chem.ControlParameter.SMILES_NO_ORGANIC_SUBSET</td><td><tt>False</tt></td><td>Specifies whether ordinary <em>C, N, O, S, P, F, Cl, Br</em> and <em>I</em> atoms shall be enclosed in brackets</td></tr>
# </table>
# 
class SMILESReactionWriter(ReactionWriterBase):

    ##
    # \brief Constructs a <tt>SMILESReactionWriter</tt> instance that will write the reaction data to the output stream <em>os</em>.
    # 
    # \param os The output stream to write to.
    # 
    def __init__(os: Base.OStream) -> None: pass
