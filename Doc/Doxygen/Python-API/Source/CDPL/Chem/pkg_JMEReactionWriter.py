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
# \brief A writer for reaction data in the native I/O format of the <em>JME Molecular Editor</em> [\ref JME] java applet.
# 
# <tt>JMEReactionWriter</tt> implements the output of Chem.Reaction objects in the native I/O format used by the <em>JME Molecular Editor</em> applet. The output data are written by means of a <tt>std::ostream</tt> object that was provided to the <tt>JMEReactionWriter</tt> constructor.
# 
# Atom and bond attributes that get written for a component of the output reaction are defined by the following Chem.Atom, Chem.Bond and Chem.BondContainer properties:
# 
# <table>
#  <tr><th>Chem.Atom Property</th><th>Description</th><th>Notes</th></tr>
#  <tr><td>Chem.AtomProperty.MATCH_CONSTRAINTS</td><td>Specifies atom matching constraints</td><td>Only written if the constraints have been explicitly assigned and can be expressed by corresponding <em>JME</em> constraints</td></tr>
#  <tr><td>Chem.AtomProperty.COORDINATES_2D</td><td>Specifies the 2D position of the atom</td><td>-</td></tr>
#  <tr><td>Chem.AtomProperty.TYPE</td><td>Specifies the type of the atom (see Chem.AtomType)</td><td>Only written if the atom is a query atom and the type is supported by the <em>JME</em> format.</td></tr>
#  <tr><td>Chem.AtomProperty.SYMBOL</td><td>Specifies the atom symbol (e.g. element symbol)</td><td>Only written if the atom is not a query atom</td></tr>
#  <tr><td>Chem.AtomProperty.FORMAL_CHARGE</td><td>Specifies the fromal charge of the atom</td><td>Only written if the atom is not a query atom and the specified charge is different from zero</td></tr>
#  <tr><td>Chem.AtomProperty.H_COUNT</td><td>Specifies the hydrogen count of the atom</td><td>Only written if the atom is a query atom and a corresponding matching constraint has been specified</td></tr>
#  <tr><td>Chem.AtomProperty.RING_FLAG</td><td>Tells whether the atom is a member of a ring</td><td>Only written if the atom is a query atom and a corresponding matching constraint has been specified</td></tr>
#  <tr><td>Chem.AtomProperty.AROMATICITY_FLAG</td><td>Tells whether the atom is a member of an aromatic ring</td><td>Only written if the atom is a query atom and a corresponding matching constraint has been specified</td></tr>
#  <tr><td>Chem.AtomProperty.REACTION_ATOM_MAPPING_ID</td><td>Specifies the reactant to product atom mapping class</td><td>Only written if the specified mapping number is greater than zero</td></tr>
# </table>
# 
# <table>
#  <tr><th>Chem.Bond Property</th><th>Description</th><th>Notes</th></tr>
#  <tr><td>Chem.BondProperty.ORDER</td><td>Specifies the order of the bond</td><td>-</td></tr>
#  <tr><td>Chem.BondProperty.STEREO_FLAG</td><td>Specifies the 2D stereo bond type (see Chem.BondStereoFlag)</td><td>Either stereo bonds are not supported by the <em>JME</em> format and are written as plain single bonds</td></tr>
# </table>
# 
# <table>
#  <tr><th>Chem.BondContainer Property</th><th>Description</th><th>Notes</th></tr>
#  <tr><td>Chem.BondContainerProperty.HEAVY_BOND_COUNT</td><td>Specifies the heavy bond count of the atoms</td><td>Only written if the atom is a query atom and a corresponding matching constraint has been specified</td></tr>
# </table>
# 
# Beside the editing of conventional chemical structures, the <em>JME</em> applet allows to some extent the specification of atom matching constraints for the definition of substructure search queries. If an atom of a component of the output reaction specifies any constraints by a Chem.MatchConstraintList data structure that has been assigned to the property Chem.AtomProperty.MATCH_CONSTRAINTS, an attempt is made to convert the contained Chem.MatchConstraint objects to equivalent <em>JME</em> query expression primitives.
# 
# Different types of constraints specified by Chem.MatchConstraint instances and the corresponding <em>JME</em> expression primitives are listed in the table below (<em><n></em> denotes a positive integer value and <em><S></em> the symbol of a chemical element; * the value is either provided by the Chem.MatchConstraint instance (see Chem.MatchConstraint.getValue()) or, if no value has been set, by the property specified in parentheses):
# 
# <table>
#  <tr><th>Chem.MatchConstraint object</th><th>Written Expression Primitive</th><th>Description</th></tr>
#  <tr><th>Constraint ID</th><th>Operator</th><th>Value*</th></tr>
#  <tr><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td><td>c</td><td>Aromatic carbon</td></tr>
#  <tr><td>The sub-constraint list must have the logical type Chem.MatchConstraintList.AND_LIST and has to contain the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.C <br>
# (Chem.AtomProperty.TYPE)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>True</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.MatchConstraint.NOT_EQUAL</td><td><tt>False</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td><td>n</td><td>Aromatic nitrogen</td></tr>
#  <tr><td>The sub-constraint list must have the logical type Chem.MatchConstraintList.AND_LIST and has to contain the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.N <br>
# (Chem.AtomProperty.TYPE)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>True</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.MatchConstraint.NOT_EQUAL</td><td><tt>False</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td><td>o <br></td><td>Aromatic oxygen</td></tr>
#  <tr><td>The sub-constraint list must have the logical type Chem.MatchConstraintList.AND_LIST and has to contain the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.O <br>
# (Chem.AtomProperty.TYPE)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>True</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.MatchConstraint.NOT_EQUAL</td><td><tt>False</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td><td>s</td><td>Aromatic sulfur</td></tr>
#  <tr><td>The sub-constraint list must have the logical type Chem.MatchConstraintList.AND_LIST and has to contain the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.S <br>
# (Chem.AtomProperty.TYPE)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>True</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.MatchConstraint.NOT_EQUAL</td><td><tt>False</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td><td>p</td><td>Aromatic phosphorus</td></tr>
#  <tr><td>The sub-constraint list must have the logical type Chem.MatchConstraintList.AND_LIST and has to contain the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.P <br>
# (Chem.AtomProperty.TYPE)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>True</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.MatchConstraint.NOT_EQUAL</td><td><tt>False</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td><td>a</td><td>Any aromatic atom</td></tr>
#  <tr><td>The sub-constraint list must have the logical type Chem.MatchConstraintList.AND_LIST and has to contain the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.ANY <br>
# (Chem.AtomProperty.TYPE)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>True</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.MatchConstraint.NOT_EQUAL</td><td><tt>False</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td><td>A</td><td>Any non-aromatic atom</td></tr>
#  <tr><td>The sub-constraint list must have the logical type Chem.MatchConstraintList.AND_LIST and has to contain the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.ANY <br>
# (Chem.AtomProperty.TYPE)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>False</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.MatchConstraint.NOT_EQUAL</td><td><tt>True</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td><td><em><S></em></td><td>A non-aromatic atom of element <S></td></tr>
#  <tr><td>The sub-constraint list must have the logical type Chem.MatchConstraintList.AND_LIST and has to contain the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Atom type associated with the element <S> <br>
# (Chem.AtomProperty.TYPE)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>False</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.MatchConstraint.NOT_EQUAL</td><td><tt>True</tt> <br>
# (Chem.AtomProperty.AROMATICITY_FLAG)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td><n> <br>
# (Chem.AtomProperty.TYPE)</td><td>#<em><n></em></td><td>An atom with atomic number <n></td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.QH <br>
# (Chem.AtomProperty.TYPE)</td><td>!#6</td><td>Any atom except carbon</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.ANY <br>
# (Chem.AtomProperty.TYPE)</td><td>*</td><td>Any atom</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.RING_TOPOLOGY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>True</tt> <br>
# (Chem.AtomProperty.RING_FLAG)</td><td>R</td><td>Any ring atom</td></tr>
#  <tr><td>Chem.MatchConstraint.NOT_EQUAL</td><td><tt>False</tt> <br>
# (Chem.AtomProperty.RING_FLAG)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.RING_TOPOLOGY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>False</tt> <br>
# (Chem.AtomProperty.RING_FLAG)</td><td>!R</td><td>Any non-ring atom</td></tr>
#  <tr><td>Chem.MatchConstraint.NOT_EQUAL</td><td><tt>True</tt> <br>
# (Chem.AtomProperty.RING_FLAG)</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.H_COUNT</td><td>Chem.MatchConstraint.EQUAL</td><td><n> <br>
# (Chem.getAtomCount(const Chem.Atom&, const Chem.MolecularGraph&, unsigned int))</td><td>H<em><n></em></td><td>Hydrogen count</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.HEAVY_BOND_COUNT</td><td>Chem.MatchConstraint.EQUAL</td><td><n> <br>
# (Chem.getHeavyBondCount(const Chem.Atom&, const Chem.MolecularGraph&))</td><td>D<em><n></em></td><td>Heavy bond count</td></tr>
# </table>
# 
# <tt>JMEReactionWriter</tt> can be configured with the following control-parameters:
# 
# <table>
#  <tr><th>Control-Parameter</th><th>Default Value (see Chem.ControlParameterDefault)</th><th>Description</th></tr>
#  <tr><td>Chem.ControlParameter.STRICT_ERROR_CHECKING</td><td><tt>False</tt></td><td>Specifies whether non-fatal recoverable errors should be ignored or cause a write operation to fail</td></tr>
#  <tr><td>Chem.ControlParameter.COORDINATES_DIMENSION</td><td><tt>2</tt></td><td>Specifies the dimension of atom coordinates</td></tr>
#  <tr><td>Chem.ControlParameter.RECORD_SEPARATOR</td><td><tt>"\n"</tt></td><td>Specifies the data record separator</td></tr>
#  <tr><td>Chem.ControlParameter.BOND_MEMBER_SWAP_STEREO_FIX</td><td><tt>True</tt></td><td>Specifies whether reverse stereo bonds shall be converted to regular stereo bonds by swapping bond start and end atoms</td></tr>
#  <tr><td>Chem.ControlParameter.JME_SEPARATE_COMPONENTS</td><td><tt>True</tt></td><td>Specifies whether the components of a molecule shall be written separately or combined as a single <em>JME</em> component</td></tr>
# </table>
# 
class JMEReactionWriter(ReactionWriterBase):

    ##
    # \brief Constructs a <tt>JMEReactionWriter</tt> instance that will write the reaction data to the output stream <em>os</em>.
    # 
    # \param os The output stream to write to.
    # 
    def __init__(os: Base.OStream) -> None: pass
