/* 
 * JMEReactionWriter.hpp 
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
 * \brief Definition of the class CDPL::Chem::JMEReactionWriter.
 */

#ifndef CDPL_CHEM_JMEREACTIONWRITER_HPP
#define CDPL_CHEM_JMEREACTIONWRITER_HPP

#include <memory>
#include <iosfwd>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL
{

    namespace Chem
    {

        class JMEDataWriter;
        class Reaction;

        /**
         * \brief A writer for reaction data in the native I/O format of the <em>JME Molecular Editor</em> [\ref JME] java applet.
         *
         * \c %JMEReactionWriter implements the output of Chem::Reaction objects in the native I/O format used by the
         * <em>JME Molecular Editor</em> applet. The output data are written by means of a \c std::ostream object that
         * was provided to the \c %JMEReactionWriter constructor.
         *
         * %Atom and bond attributes that get written for a component of the output reaction are defined by the following Chem::Atom,
         * Chem::Bond and Chem::BondContainer properties:
         *
         * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
         *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
         *   <th>Chem::Atom Property</th> <th>Description</th> <th>Notes</th>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomProperty::MATCH_CONSTRAINTS</td>
         *   <td>Specifies atom matching constraints</td>
         *   <td>Only written if the constraints have been explicitly assigned and can be expressed by
         *       corresponding \e JME constraints</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomProperty::COORDINATES_2D</td>
         *   <td>Specifies the 2D position of the atom</td>
         *   <td align="center">-</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomProperty::TYPE</td>
         *   <td>Specifies the type of the atom (see Chem::AtomType)</td>
         *   <td>Only written if the atom is a query atom and the type is supported by the \e JME format.
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomProperty::SYMBOL</td>
         *   <td>Specifies the atom symbol (e.g. element symbol)</td>
         *   <td>Only written if the atom is not a query atom</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomProperty::FORMAL_CHARGE</td>
         *   <td>Specifies the fromal charge of the atom</td>
         *   <td>Only written if the atom is not a query atom and the specified charge is different from zero</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomProperty::H_COUNT</td>
         *   <td>Specifies the hydrogen count of the atom</td>
         *   <td>Only written if the atom is a query atom and a corresponding matching constraint has been specified</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomProperty::RING_FLAG</td>
         *   <td>Tells whether the atom is a member of a ring</td>
         *   <td>Only written if the atom is a query atom and a corresponding matching constraint has been specified</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomProperty::AROMATICITY_FLAG</td>
         *   <td>Tells whether the atom is a member of an aromatic ring</td>
         *   <td>Only written if the atom is a query atom and a corresponding matching constraint has been specified</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomProperty::REACTION_ATOM_MAPPING_ID</td>
         *   <td>Specifies the reactant to product atom mapping class</td>
         *   <td>Only written if the specified mapping number is greater than zero</td>
         *  </tr>
         * </table>
         *
         * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
         *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
         *   <th>Chem::Bond Property</th> <th>Description</th> <th>Notes</th>
         *  </tr>
         *  <tr>
         *   <td>Chem::BondProperty::ORDER</td>
         *   <td>Specifies the order of the bond</td>
         *   <td align="center">-</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::BondProperty::STEREO_FLAG</td>
         *   <td>Specifies the 2D stereo bond type (see Chem::BondStereoFlag)</td>
         *   <td>Either stereo bonds are not supported by the \e JME format and are written as plain
         *       single bonds</td>
         *  </tr>
         * </table>
         *
         * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
         *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
         *   <th>Chem::BondContainer Property</th> <th>Description</th> <th>Notes</th>
         *  </tr>
         *  <tr>
         *   <td>Chem::BondContainerProperty::HEAVY_BOND_COUNT</td>
         *   <td>Specifies the heavy bond count of the atoms</td>
         *   <td>Only written if the atom is a query atom and a corresponding matching constraint has been specified</td>
         *  </tr>
         * </table>
         *
         * Beside the editing of conventional chemical structures, the \e JME applet allows to some extent the specification of
         * atom matching constraints for the definition of substructure search queries. If an atom of a component of the output
         * reaction specifies any constraints by a Chem::MatchConstraintList data structure that has been assigned to the property
         * Chem::AtomProperty::MATCH_CONSTRAINTS, an attempt is made to convert the contained Chem::MatchConstraint objects to
         * equivalent \e JME query expression primitives.
         *
         * Different types of constraints specified by Chem::MatchConstraint instances and the corresponding \e JME expression
         * primitives are listed in the table below (<em>&lt;n&gt;</em> denotes a positive integer value and <em>&lt;S&gt;</em>
         * the symbol of a chemical element; * the value is either provided by the Chem::MatchConstraint instance
         * (see Chem::MatchConstraint::getValue()) or, if no value has been set, by the property specified in parentheses):
         *
         * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
         *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
         *   <th colspan="3">Chem::MatchConstraint object</th>
         *   <th rowspan="2">Written Expression Primitive</th> 
         *   <th rowspan="2">Description</th> 
         *  </tr>
         *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
         *   <th>Constraint ID</th> <th>Operator</th> <th>Value*</th>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
         *   <td align="center" rowspan="5">c</td>
         *   <td rowspan="5">Aromatic carbon</td>
         *  </tr>
         *  <tr>
         *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list must have the logical type
         *    Chem::MatchConstraintList::AND_LIST and has to contain the elements:</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::TYPE</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">Chem::AtomType::C <br>(Chem::AtomProperty::TYPE)</td>
         *  </tr>
         *  <tr>
         *   <td rowspan="2">Chem::AtomMatchConstraint::AROMATICITY</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">\c true <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::MatchConstraint::NOT_EQUAL</td>
         *   <td align="center">\c false <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
         *   <td align="center" rowspan="5">n</td>
         *   <td rowspan="5">Aromatic nitrogen</td>
         *  </tr>
         *  <tr>
         *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list must have the logical type 
         *    Chem::MatchConstraintList::AND_LIST and has to contain the elements:</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::TYPE</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">Chem::AtomType::N <br>(Chem::AtomProperty::TYPE)</td>
         *  </tr>
         *  <tr>
         *   <td rowspan="2">Chem::AtomMatchConstraint::AROMATICITY</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">\c true <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::MatchConstraint::NOT_EQUAL</td>
         *   <td align="center">\c false <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
         *   <td align="center" rowspan="5">o</td>    
         *   <td rowspan="5">Aromatic oxygen</td>
         *  </tr>
         *  <tr>
         *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list must have the logical type 
         *    Chem::MatchConstraintList::AND_LIST and has to contain the elements:</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::TYPE</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">Chem::AtomType::O <br>(Chem::AtomProperty::TYPE)</td>
         *  </tr>
         *  <tr>
         *   <td rowspan="2">Chem::AtomMatchConstraint::AROMATICITY</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">\c true <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::MatchConstraint::NOT_EQUAL</td>
         *   <td align="center">\c false <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
         *   <td align="center" rowspan="5">s</td>
         *   <td rowspan="5">Aromatic sulfur</td>
         *  </tr>
         *  <tr>
         *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list must have the logical type
         *    Chem::MatchConstraintList::AND_LIST and has to contain the elements:</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::TYPE</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">Chem::AtomType::S <br>(Chem::AtomProperty::TYPE)</td>
         *  </tr>
         *  <tr>
         *   <td rowspan="2">Chem::AtomMatchConstraint::AROMATICITY</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">\c true <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::MatchConstraint::NOT_EQUAL</td>
         *   <td align="center">\c false <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
         *   <td align="center" rowspan="5">p</td>
         *   <td rowspan="5">Aromatic phosphorus</td>
         *  </tr>
         *  <tr>
         *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list must have the logical type 
         *    Chem::MatchConstraintList::AND_LIST and has to contain the elements:</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::TYPE</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">Chem::AtomType::P <br>(Chem::AtomProperty::TYPE)</td>
         *  </tr>
         *  <tr>
         *   <td rowspan="2">Chem::AtomMatchConstraint::AROMATICITY</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">\c true <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::MatchConstraint::NOT_EQUAL</td>
         *   <td align="center">\c false <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
         *   <td align="center" rowspan="5">a</td>
         *   <td rowspan="5">Any aromatic atom</td>
         *  </tr>
         *  <tr>
         *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list must have the logical type
         *    Chem::MatchConstraintList::AND_LIST and has to contain the elements:</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::TYPE</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">Chem::AtomType::ANY <br>(Chem::AtomProperty::TYPE)</td>
         *  </tr>
         *  <tr>
         *   <td rowspan="2">Chem::AtomMatchConstraint::AROMATICITY</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">\c true <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::MatchConstraint::NOT_EQUAL</td>
         *   <td align="center">\c false <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
         *   <td align="center" rowspan="5">A</td>
         *   <td rowspan="5">Any non-aromatic atom</td>
         *  </tr>
         *  <tr>
         *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list must have the logical type
         *    Chem::MatchConstraintList::AND_LIST and has to contain the elements:</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::TYPE</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">Chem::AtomType::ANY <br>(Chem::AtomProperty::TYPE)</td>
         *  </tr>
         *  <tr>
         *   <td rowspan="2">Chem::AtomMatchConstraint::AROMATICITY</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">\c false <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::MatchConstraint::NOT_EQUAL</td>
         *   <td align="center">\c true <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::CONSTRAINT_LIST</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">A pointer to a Chem::MatchConstraintList object</td> 
         *   <td align="center" rowspan="5"><em>&lt;S&gt;</em></td>
         *   <td rowspan="5">A non-aromatic atom of element &lt;S&gt;</td>
         *  </tr>
         *  <tr>
         *   <td bgcolor="#EEEEEE" align="center" colspan="3">The sub-constraint list must have the logical type
         *    Chem::MatchConstraintList::AND_LIST and has to contain the elements:</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::TYPE</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">%Atom type associated with the element &lt;S&gt; <br>(Chem::AtomProperty::TYPE)</td>
         *  </tr>
         *  <tr>
         *   <td rowspan="2">Chem::AtomMatchConstraint::AROMATICITY</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">\c false <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::MatchConstraint::NOT_EQUAL</td>
         *   <td align="center">\c true <br>(Chem::AtomProperty::AROMATICITY_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::TYPE</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">&lt;n&gt; <br>(Chem::AtomProperty::TYPE)</td>
         *   <td align="center">\#<em>&lt;n&gt;</em></td>
         *   <td>An atom with atomic number &lt;n&gt;</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::TYPE</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">Chem::AtomType::QH <br>(Chem::AtomProperty::TYPE)</td>
         *   <td align="center">!\#6</td>
         *   <td>Any atom except carbon</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::TYPE</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">Chem::AtomType::ANY <br>(Chem::AtomProperty::TYPE)</td>
         *   <td align="center">*</td>
         *   <td>Any atom</td>
         *  </tr>
         *  <tr>
         *   <td rowspan="2">Chem::AtomMatchConstraint::RING_TOPOLOGY</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">\c true <br>(Chem::AtomProperty::RING_FLAG)</td>
         *   <td rowspan="2" align="center">R</td>
         *   <td rowspan="2">Any ring atom</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::MatchConstraint::NOT_EQUAL</td>
         *   <td align="center">\c false <br>(Chem::AtomProperty::RING_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td rowspan="2">Chem::AtomMatchConstraint::RING_TOPOLOGY</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">\c false <br>(Chem::AtomProperty::RING_FLAG)</td>
         *   <td rowspan="2" align="center">!R</td>
         *   <td rowspan="2">Any non-ring atom</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::MatchConstraint::NOT_EQUAL</td>
         *   <td align="center">\c true <br>(Chem::AtomProperty::RING_FLAG)</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::H_COUNT</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">&lt;n&gt; <br>(Chem::getAtomCount(const Chem::Atom&, const Chem::MolecularGraph&, unsigned int))</td>
         *   <td align="center">H<em>&lt;n&gt;</em></td>
         *   <td>Hydrogen count</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::AtomMatchConstraint::HEAVY_BOND_COUNT</td>
         *   <td>Chem::MatchConstraint::EQUAL</td>
         *   <td align="center">&lt;n&gt; <br>(Chem::getHeavyBondCount(const Chem::Atom&, const Chem::MolecularGraph&))</td>
         *   <td align="center">D<em>&lt;n&gt;</em></td>
         *   <td>Heavy bond count</td>
         *  </tr>
         * </table>
         *
         * \c %JMEReactionWriter can be configured with the following control-parameters:
         *
         * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
         *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
         *   <th>Control-Parameter</th> <th>Default Value (see Chem::ControlParameterDefault)</th> <th>Description</th>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::STRICT_ERROR_CHECKING</td>
         *   <td align="center">\c false</td>
         *   <td>Specifies whether non-fatal recoverable errors should be ignored or cause a write operation to fail</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::COORDINATES_DIMENSION</td>
         *   <td align="center">\c 2</td>
         *   <td>Specifies the dimension of atom coordinates</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::RECORD_SEPARATOR</td>
         *   <td align="center">\c "\n"</td>
         *   <td>Specifies the data record separator</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::BOND_MEMBER_SWAP_STEREO_FIX</td>
         *   <td align="center">\c true</td>
         *   <td>Specifies whether reverse stereo bonds shall be converted to regular stereo bonds by swapping bond start and
         *       end atoms</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::JME_SEPARATE_COMPONENTS</td>
         *   <td align="center">\c true</td>
         *   <td>Specifies whether the components of a molecule shall be written separately or combined as a single
         *       \e JME component</td>
         *  </tr>
         * </table>
         */
        class CDPL_CHEM_API JMEReactionWriter : public Base::DataWriter<Reaction>
        {

          public:
            /**
             * \brief Constructs a \c %JMEReactionWriter instance that will write the reaction data to the output
             *        stream \a os.
             * \param os The output stream to write to.
             */
            JMEReactionWriter(std::ostream& os);

            /**
             * \brief Destructor.
             */
            ~JMEReactionWriter();

            /**
             * \brief Writes the reaction \a rxn to the output stream specified in the constructor.
             * \param rxn The reaction to write.
             * \return A reference to itself.
             */
            Base::DataWriter<Reaction>& write(const Reaction& rxn);

                 operator const void*() const;
            bool operator!() const;

          private:
            typedef std::auto_ptr<JMEDataWriter> JMEDataWriterPtr;

            JMEReactionWriter(const JMEReactionWriter&);

            JMEReactionWriter& operator=(const JMEReactionWriter&);

            std::ostream&    output;
            bool             state;
            JMEDataWriterPtr writer;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_JMEREACTIONWRITER_HPP
