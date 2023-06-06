/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomTypeMatchExpression.hpp 
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
 * \brief Definition of the class CDPL::Chem::AtomTypeMatchExpression.
 */

#ifndef CDPL_CHEM_ATOMTYPEMATCHEXPRESSION_HPP
#define CDPL_CHEM_ATOMTYPEMATCHEXPRESSION_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchExpression.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Atom;
		class MolecularGraph;

		/**
		 * \brief AtomTypeMatchExpression.
		 */
		class CDPL_CHEM_API AtomTypeMatchExpression : public MatchExpression<Atom, MolecularGraph>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %AtomTypeMatchExpression instances.
			 */
			typedef boost::shared_ptr<AtomTypeMatchExpression> SharedPointer;

			/**
			 * \brief Constructs an \c %AtomTypeMatchExpression instance for the specified query atom type and matching mode.
			 * \param atom_type The atom type that has to be matched (or not matched) by target atoms. 
			 * \param not_match Specifies whether the type of a target atom actually has to match (\c true) or \e not match (\c false)
			 *                  the query atom type.
			 */
			AtomTypeMatchExpression(unsigned int atom_type, bool not_match); 

			/**
			 * \brief Checks whether the atom type of \a target_atom matches (or does not match) the query atom type specified in the constructor.
			 *
			 * The following table lists all supported query atom types and associated matching target atom types:
			 *
			 * <table bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
			 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
			 *   <th>Query %Atom Type</th> <th>Matching Target %Atom Types</th>
			 *  </tr>
			 *  <tr>
			 *   <td>Types in the range from Chem::AtomType::H to Chem::AtomType::MAX_ATOMIC_NO</td>
			 *   <td>Any target atom with the same atom type</td>
			 *  </tr>
			 *  <tr>
			 *   <td>Chem::AtomType::ANY</td>
			 *   <td>Any target atom type</td>
			 *  </tr>
			 *  <tr>
			 *   <td>Chem::AtomType::AH</td>
			 *   <td>Any target atom type</td>
			 *  </tr>
			 *  <tr>
			 *   <td>Chem::AtomType::A</td>
			 *   <td>Any target atom type except Chem::AtomType::H</td>
			 *  </tr>
			 *  <tr>
			 *   <td>Chem::AtomType::Q</td>
			 *   <td>Any target atom type except Chem::AtomType::H and Chem::AtomType::C</td>
			 *  </tr>
			 *  <tr>
			 *   <td>Chem::AtomType::QH</td>
			 *   <td>Any target atom type except Chem::AtomType::C</td>
			 *  </tr>
			 *  <tr>
			 *   <td>Chem::AtomType::M</td>
			 *   <td>Any target atom type for which Chem::AtomTypeDB::isMetal() returns \c true</td>
			 *  </tr>
			 *  <tr>
			 *   <td>Chem::AtomType::MH</td>
			 *   <td>Chem::AtomType::H or any target atom type for which Chem::AtomTypeDB::isMetal() returns \c true</td>
			 *  </tr>
			 *  <tr>
			 *   <td>Chem::AtomType::X</td>
			 *   <td>Any target atom type for which Chem::AtomTypeDB::isHalogen() returns \c true</td>
			 *  </tr>
			 *  <tr>
			 *   <td>Chem::AtomType::XH</td>
			 *   <td>Chem::AtomType::H or any target atom type for which Chem::AtomTypeDB::isHalogen() returns \c true</td>
			 *  </tr>
			 * </table>
			 *
			 * For any other query atom types the method will always return \c true - irrespective of matching mode
			 * and target atom type! 
			 *
			 * \param query_atom The query atom (ignored).
			 * \param query_molgraph The molecular graph containing the query atom (ignored).
			 * \param target_atom The checked target atom.
			 * \param target_molgraph The molecular graph containing the target atom (ignored).
			 * \param aux_data Auxiliary information for expression evaluation (ignored).
			 * \return If the matching mode is 'not match' (see constructor), the method returns \c false if the type of the
			 *         target atom is equivalent to the query atom type (see table), and \c true if the atom types do not match. 
			 *         Otherwise, the method will return \c true if the atom types are equivalent, and \c false if they are not.
			 * \note The atom type of \a target_atom is taken from the Chem::Atom property Chem::AtomProperty::TYPE.
			 */
			bool operator()(const Atom& query_atom, const MolecularGraph& query_molgraph, const Atom& target_atom, 
							const MolecularGraph& target_molgraph, const Base::Any& aux_data) const;

		private:
			unsigned int atomType;
			bool         notMatch;
		};
	}
}

#endif // CDPL_CHEM_ATOMTYPEMATCHEXPRESSION_HPP
