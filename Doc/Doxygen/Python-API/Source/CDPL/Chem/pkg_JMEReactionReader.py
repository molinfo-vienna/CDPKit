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
# \brief A reader for reaction data in the native I/O format of the <em>JME Molecular Editor</em> [\ref JME] java applet.
# 
# <tt>JMEReactionReader</tt> implements the reading of Chem.Reaction objects from a <tt>std::istream</tt> instance that provides the reaction data in the native I/O format used by the <em>JME Molecular Editor</em> applet.
# 
# Atom and bond attributes of a read reaction component are stored as properties of allocated Chem.Atom and Chem.Bond objects. The affected properties are summarized in the tables below:
# 
# <table>
#  <tr><th>Chem.Atom Property</th><th>Description</th><th>Notes</th></tr>
#  <tr><td>Chem.AtomProperty.MATCH_CONSTRAINTS</td><td>Specifies atom matching constraints</td><td>Only set if constraints have been specified</td></tr>
#  <tr><td>Chem.AtomProperty.COORDINATES_2D</td><td>Specifies the 2D position of the atom</td><td>-</td></tr>
#  <tr><td>Chem.AtomProperty.TYPE</td><td>Specifies the type of the atom (see Chem.AtomType)</td><td>Only set if the atom is a query atom and the specified type is not a member of an atom list</td></tr>
#  <tr><td>Chem.AtomProperty.SYMBOL</td><td>Specifies the atom symbol (e.g. element symbol)</td><td>Only set if the atom is not a query atom, or the symbol cannot be mapped to a valid atom type and is not a member of an atom list</td></tr>
#  <tr><td>Chem.AtomProperty.FORMAL_CHARGE</td><td>Specifies the formal charge of the atom</td><td>Only set if the charge has been specified outside of an atom list</td></tr>
#  <tr><td>Chem.AtomProperty.REACTION_ATOM_MAPPING_ID</td><td>Specifies the reactant to product atom mapping class</td><td>Only set if a mapping number has been specified that is greater than zero</td></tr>
# </table>
# 
# <table>
#  <tr><th>Chem.Bond Property</th><th>Description</th></tr>
#  <tr><td>Chem.BondProperty.ORDER</td><td>Specifies the order of the bond</td></tr>
#  <tr><td>Chem.BondProperty.STEREO_2D_FLAG</td><td>Specifies the 2D stereo bond type (see Chem.BondStereoFlag)</td></tr>
# </table>
# 
# Beside the editing of conventional chemical structures, the <em>JME</em> applet allows to some extent the specification of atom matching constraints for the definition of substructure search queries. If such constraints are encountered during the processing of an atom specification, the constraint primitives are converted to corresponding Chem.MatchConstraint objects and stored as the value of the Chem.Atom property Chem.AtomProperty.MATCH_CONSTRAINTS in a Chem.MatchConstraintList data structure.
# 
# The following table lists all of the supported <em>JME</em> atom matching constraints and specifies how they are represented by Chem.MatchConstraint instances (in the table <em><n></em> denotes a positive integer value and <em><S></em> the symbol of a chemical element):
# 
# <table>
#  <tr><th>Expression Primitive</th><th>Description</th><th>Mapped Chem.MatchConstraint object</th></tr>
#  <tr><th>Constraint ID</th><th>Operator</th><th>Value</th></tr>
#  <tr><td>c</td><td>Aromatic carbon</td><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td></tr>
#  <tr><td>The sub-constraint list has the logical type Chem.MatchConstraintList.AND_LIST and contains the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.C</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>True</tt></td></tr>
#  <tr><td>n</td><td>Aromatic nitrogen</td><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td></tr>
#  <tr><td>The sub-constraint list has the logical type Chem.MatchConstraintList.AND_LIST and contains the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.N</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>True</tt></td></tr>
#  <tr><td>o</td><td>Aromatic oxygen</td><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td></tr>
#  <tr><td>The sub-constraint list has the logical type Chem.MatchConstraintList.AND_LIST and contains the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.O</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>True</tt></td></tr>
#  <tr><td>s</td><td>Aromatic sulfur</td><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td></tr>
#  <tr><td>The sub-constraint list has the logical type Chem.MatchConstraintList.AND_LIST and contains the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.S</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>True</tt></td></tr>
#  <tr><td>p</td><td>Aromatic phosphorus</td><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td></tr>
#  <tr><td>The sub-constraint list has the logical type Chem.MatchConstraintList.AND_LIST and contains the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.P</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>True</tt></td></tr>
#  <tr><td>a</td><td>Any aromatic atom</td><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td></tr>
#  <tr><td>The sub-constraint list has the logical type Chem.MatchConstraintList.AND_LIST and contains the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.ANY</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>True</tt></td></tr>
#  <tr><td>A</td><td>Any non-aromatic atom</td><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td></tr>
#  <tr><td>The sub-constraint list has the logical type Chem.MatchConstraintList.AND_LIST and contains the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.ANY</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>False</tt></td></tr>
#  <tr><td><em><S></em></td><td>A non-aromatic atom of element <S></td><td>Chem.AtomMatchConstraint.CONSTRAINT_LIST</td><td>Chem.MatchConstraint.EQUAL</td><td>A reference to a Chem.MatchConstraintList object</td></tr>
#  <tr><td>The sub-constraint list has the logical type Chem.MatchConstraintList.AND_LIST and contains the elements:</td></tr>
#  <tr><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Atom type associated with the element <S></td></tr>
#  <tr><td>Chem.AtomMatchConstraint.AROMATICITY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>False</tt></td></tr>
#  <tr><td>#<em><n></em></td><td>An atom with atomic number <n></td><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td><n></td></tr>
#  <tr><td>!#6</td><td>Any atom except carbon</td><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.QH</td></tr>
#  <tr><td>*</td><td>Any atom</td><td>Chem.AtomMatchConstraint.TYPE</td><td>Chem.MatchConstraint.EQUAL</td><td>Chem.AtomType.ANY</td></tr>
#  <tr><td>R</td><td>Any ring atom</td><td>Chem.AtomMatchConstraint.RING_TOPOLOGY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>True</tt></td></tr>
#  <tr><td>!R</td><td>Any non-ring atom</td><td>Chem.AtomMatchConstraint.RING_TOPOLOGY</td><td>Chem.MatchConstraint.EQUAL</td><td><tt>False</tt></td></tr>
#  <tr><td>+<em><n></em></td><td>Positive charge</td><td>Chem.AtomMatchConstraint.CHARGE</td><td>Chem.MatchConstraint.EQUAL</td><td>+<n></td></tr>
#  <tr><td>-<em><n></em></td><td>Negative charge</td><td>Chem.AtomMatchConstraint.CHARGE</td><td>Chem.MatchConstraint.EQUAL</td><td>-<n></td></tr>
#  <tr><td>H<em><n></em></td><td>Hydrogen count</td><td>Chem.AtomMatchConstraint.H_COUNT</td><td>Chem.MatchConstraint.EQUAL</td><td><n></td></tr>
#  <tr><td>D<em><n></em></td><td>Heavy bond count</td><td>Chem.AtomMatchConstraint.HEAVY_BOND_COUNT</td><td>Chem.MatchConstraint.EQUAL</td><td><n></td></tr>
# </table>
# 
# The error handling behaviour of a <tt>JMEReactionReader</tt> instance can be configured with the following control-parameter:
# 
# <table>
#  <tr><th>Control-Parameter</th><th>Default Value (see Chem.ControlParameterDefault)</th><th>Description</th></tr>
#  <tr><td>Chem.ControlParameter.STRICT_ERROR_CHECKING</td><td><tt>False</tt></td><td>Specifies whether non-fatal recoverable errors should be ignored or cause a read operation to fail</td></tr>
#  <tr><td>Chem.ControlParameter.COORDINATES_DIMENSION</td><td><tt>2</tt></td><td>Specifies the dimension of atom coordinates</td></tr>
# </table>
# 
class JMEReactionReader(ReactionReaderBase):

    ##
    # \brief Constructs a <tt>JMEReactionReader</tt> instance that will read the reaction data from the input stream <em>is</em>.
    # 
    # \param is The input stream to read from.
    # 
    def __init__(is: Base.IStream) -> None: pass
