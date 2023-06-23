/* 
 * JMEReactionReader.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * \file
 * \brief Definition of the class CDPL::Chem::JMEReactionReader.
 */

#ifndef CDPL_CHEM_JMEREACTIONREADER_HPP
#define CDPL_CHEM_JMEREACTIONREADER_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/StreamDataReader.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class JMEDataReader;
		class Reaction;

		/**
		 * \brief A reader for reaction data in the native I/O format of the <em>JME Molecular Editor</em> [\ref JME] java applet.
		 *
		 * \c %JMEReactionReader implements the reading of Chem::Reaction objects from a \c std::istream instance that
		 * provides the reaction data in the native I/O format used by the <em>JME Molecular Editor</em> applet.
		 *
		 * %Atom and bond attributes of a read reaction component are stored as properties of allocated Chem::Atom and Chem::Bond
		 * objects. The affected properties are summarized in the tables below:
		 *
		 * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Chem::Atom Property</th> <th>Description</th> <th>Notes</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomProperty::MATCH_CONSTRAINTS</td>
		 *   <td>Specifies atom matching constraints</td>
		 *   <td>Only set if constraints have been specified</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomProperty::COORDINATES_2D</td>
		 *   <td>Specifies the 2D position of the atom</td>
		 *   <td align="center">-</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomProperty::TYPE</td>
		 *   <td>Specifies the type of the atom (see Chem::AtomType)</td>
		 *   <td>Only set if the atom is a query atom and the specified type is not a member of an
		 *       atom list</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomProperty::SYMBOL</td>
		 *   <td>Specifies the atom symbol (e.g. element symbol)</td>
		 *   <td>Only set if the atom is not a query atom, or the symbol cannot be mapped to a valid atom type
		 *       and is not a member of an atom list</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomProperty::FORMAL_CHARGE</td>
		 *   <td>Specifies the formal charge of the atom</td>
		 *   <td>Only set if the charge has been specified outside of an atom list</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomProperty::REACTION_ATOM_MAPPING_ID</td>
		 *   <td>Specifies the reactant to product atom mapping class</td>
		 *   <td>Only set if a mapping number has been specified that is greater than zero</td>
		 *  </tr>
		 * </table>
		 *
		 * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Chem::Bond Property</th> <th>Description</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::BondProperty::ORDER</td>
		 *   <td>Specifies the order of the bond</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::BondProperty::STEREO_2D_FLAG</td>
		 *   <td>Specifies the 2D stereo bond type (see Chem::BondStereoFlag)</td>
		 *  </tr>
		 * </table>
		 *
		 * Beside the editing of conventional chemical structures, the \e JME applet allows to some extent the specification of
		 * atom matching constraints for the definition of substructure search queries. If such constraints are encountered
		 * during the processing of an atom specification, the constraint primitives are converted to corresponding
		 * Chem::MatchConstraint objects and stored as the value of the Chem::Atom property Chem::AtomProperty::MATCH_CONSTRAINTS
		 * in a Chem::MatchConstraintList data structure.
		 *
		 * The following table lists all of the supported \e JME atom matching constraints and specifies how they are represented
		 * by Chem::MatchConstraint instances (in the table <em>&lt;n&gt;</em> denotes a positive integer value and <em>&lt;S&gt;</em>
		 * the symbol of a chemical element):
		 *
		 * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th rowspan="2">Expression Primitive</th> 
		 *   <th rowspan="2">Description</th> 
		 *   <th colspan="3">Mapped Chem::MatchConstraint object</th>
		 *  </tr>
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Constraint ID</th> <th>Operator</th> <th>Value</th>
		 *  </tr>
		 *  <tr>
		 *   <td align="center" rowspan="4">c</td>
		 *   <td rowspan="4">Aromatic carbon</td>
		 *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
		 *  </tr>
		 *  <tr>
		 *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list has the logical type
		 *    Chem::MatchConstraintList::AND_LIST and contains the elements:</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::TYPE</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">Chem::AtomType::C</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::AROMATICITY</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">\c true</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center" rowspan="4">n</td>
		 *   <td rowspan="4">Aromatic nitrogen</td>
		 *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
		 *  </tr>
		 *  <tr>
		 *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list has the logical type 
		 *    Chem::MatchConstraintList::AND_LIST and contains the elements:</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::TYPE</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">Chem::AtomType::N</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::AROMATICITY</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">\c true</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center" rowspan="4">o</td>
		 *   <td rowspan="4">Aromatic oxygen</td>
		 *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
		 *  </tr>
		 *  <tr>
		 *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list has the logical type 
		 *    Chem::MatchConstraintList::AND_LIST and contains the elements:</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::TYPE</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">Chem::AtomType::O</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::AROMATICITY</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">\c true</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center" rowspan="4">s</td>
		 *   <td rowspan="4">Aromatic sulfur</td>
		 *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
		 *  </tr>
		 *  <tr>
		 *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list has the logical type
		 *    Chem::MatchConstraintList::AND_LIST and contains the elements:</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::TYPE</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">Chem::AtomType::S</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::AROMATICITY</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">\c true</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center" rowspan="4">p</td>
		 *   <td rowspan="4">Aromatic phosphorus</td>
		 *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
		 *  </tr>
		 *  <tr>
		 *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list has the logical type 
		 *    Chem::MatchConstraintList::AND_LIST and contains the elements:</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::TYPE</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">Chem::AtomType::P</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::AROMATICITY</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">\c true</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center" rowspan="4">a</td>
		 *   <td rowspan="4">Any aromatic atom</td>
		 *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
		 *  </tr>
		 *  <tr>
		 *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list has the logical type
		 *    Chem::MatchConstraintList::AND_LIST and contains the elements:</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::TYPE</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">Chem::AtomType::ANY</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::AROMATICITY</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">\c true</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center" rowspan="4">A</td>
		 *   <td rowspan="4">Any non-aromatic atom</td>
		 *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
		 *  </tr>
		 *  <tr>
		 *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list has the logical type
		 *    Chem::MatchConstraintList::AND_LIST and contains the elements:</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::TYPE</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">Chem::AtomType::ANY</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::AROMATICITY</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">\c false</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center" rowspan="4"><em>&lt;S&gt;</em></td>
		 *   <td rowspan="4">A non-aromatic atom of element &lt;S&gt;</td>
		 *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
		 *  </tr>
		 *  <tr>
		 *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list has the logical type
		 *    Chem::MatchConstraintList::AND_LIST and contains the elements:</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::TYPE</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">%Atom type associated with the element &lt;S&gt;</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomMatchConstraint::AROMATICITY</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">\c false</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center">\#<em>&lt;n&gt;</em></td>
		 *   <td>An atom with atomic number &lt;n&gt;</td>
		 *   <td>Chem::AtomMatchConstraint::TYPE</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">&lt;n&gt;</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center">!\#6</td>
		 *   <td>Any atom except carbon</td>
		 *   <td>Chem::AtomMatchConstraint::TYPE</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">Chem::AtomType::QH</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center">*</td>
		 *   <td>Any atom</td>
		 *   <td>Chem::AtomMatchConstraint::TYPE</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">Chem::AtomType::ANY</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center">R</td>
		 *   <td>Any ring atom</td>
		 *   <td>Chem::AtomMatchConstraint::RING_TOPOLOGY</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">\c true</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center">!R</td>
		 *   <td>Any non-ring atom</td>
		 *   <td>Chem::AtomMatchConstraint::RING_TOPOLOGY</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">\c false</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center">+<em>&lt;n&gt;</em></td>
		 *   <td>Positive charge</td>
		 *   <td>Chem::AtomMatchConstraint::CHARGE</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">+&lt;n&gt;</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center">-<em>&lt;n&gt;</em></td>
		 *   <td>Negative charge</td>
		 *   <td>Chem::AtomMatchConstraint::CHARGE</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">-&lt;n&gt;</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center">H<em>&lt;n&gt;</em></td>
		 *   <td>Hydrogen count</td>
		 *   <td>Chem::AtomMatchConstraint::H_COUNT</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">&lt;n&gt;</td>
		 *  </tr>
		 *  <tr>
		 *   <td align="center">D<em>&lt;n&gt;</em></td>
		 *   <td>Heavy bond count</td>
		 *   <td>Chem::AtomMatchConstraint::HEAVY_BOND_COUNT</td>
		 *   <td>Chem::MatchConstraint::EQUAL</td>
		 *   <td align="center">&lt;n&gt;</td>
		 *  </tr>
		 * </table>
		 *
		 * The error handling behaviour of a \c %JMEReactionReader instance can be configured with the following
		 * control-parameter:
		 *
		 * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Control-Parameter</th> <th>Default Value (see Chem::ControlParameterDefault)</th> <th>Description</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::STRICT_ERROR_CHECKING</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether non-fatal recoverable errors should be ignored or cause a read operation to fail</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::COORDINATES_DIMENSION</td>
		 *   <td align="center">\c 2</td>
		 *   <td>Specifies the dimension of atom coordinates</td>
		 *  </tr>
		 * </table>
		 */
		class CDPL_CHEM_API JMEReactionReader : public Util::StreamDataReader<Reaction, JMEReactionReader>
		{

		public:
			/**
			 * \brief Constructs a \c %JMEReactionReader instance that will read the reaction data from the input
			 *        stream \a is.
			 * \param is The input stream to read from.
			 */
			JMEReactionReader(std::istream& is);

			/**
			 * \brief Destructor.
			 */
			~JMEReactionReader();

		private:
			friend class Util::StreamDataReader<Reaction, JMEReactionReader>;

			JMEReactionReader(const JMEReactionReader&);

			JMEReactionReader& operator=(const JMEReactionReader&);

			bool readData(std::istream&, Reaction&, bool overwrite);
			bool skipData(std::istream&);
			bool moreData(std::istream&);

			typedef std::auto_ptr<JMEDataReader> JMEDataReaderPtr;

			JMEDataReaderPtr reader;
		};
	}
}

#endif // CDPL_CHEM_JMEREACTIONREADER_HPP
