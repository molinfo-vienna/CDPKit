/* 
 * JMEDataWriter.cpp 
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


#include "StaticInit.hpp"

#include <ostream>
#include <iomanip>
#include <locale>
#include <string>
#include <algorithm>
#include <cassert>
#include <functional>

#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/AtomMatchConstraint.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"

#include "JMEDataWriter.hpp"
#include "JMEFormatData.hpp"


namespace
{

    const std::string DEF_ATOM_SYMBOL = "?";
}


using namespace CDPL;


bool Chem::JMEDataWriter::writeReaction(std::ostream& os, const Reaction& rxn)
{
    init(os);

    bool first_comp = true;

    Reaction::ConstComponentIterator comps_end = rxn.getComponentsEnd(ReactionRole::REACTANT);

    for (Reaction::ConstComponentIterator it = rxn.getComponentsBegin(ReactionRole::REACTANT); it != comps_end; ++it) {
        const Molecule& comp = *it;

        if (comp.getNumAtoms() == 0)
            continue;

        if (!first_comp)
            os << JME::COMPONENT_SEPARATOR;

        if (!writeMolGraph(os, comp, false))
            return false;

        first_comp = false;
    }

    os << JME::REACTION_ROLE_SEPARATOR;

    first_comp = true;

    comps_end = rxn.getComponentsEnd(ReactionRole::AGENT);

    for (Reaction::ConstComponentIterator it = rxn.getComponentsBegin(ReactionRole::AGENT); it != comps_end; ++it) {
        const Molecule& comp = *it;

        if (comp.getNumAtoms() == 0)
            continue;

        if (!first_comp)
            os << JME::COMPONENT_SEPARATOR;

        if (!writeMolGraph(os, comp, false))
            return false;

        first_comp = false;
    }

    os << JME::REACTION_ROLE_SEPARATOR;

    first_comp = true;

    comps_end = rxn.getComponentsEnd(ReactionRole::PRODUCT);

    for (Reaction::ConstComponentIterator it = rxn.getComponentsBegin(ReactionRole::PRODUCT); it != comps_end; ++it) {
        const Molecule& comp = *it;

        if (comp.getNumAtoms() == 0)
            continue;

        if (!first_comp)
            os << JME::COMPONENT_SEPARATOR;

        if (!writeMolGraph(os, comp, false))
            return false;

        first_comp = false;
    }

    os << getRecordSeparatorParameter(ioBase);
    
    return os.good();
}

bool Chem::JMEDataWriter::writeMolGraph(std::ostream& os, const MolecularGraph& molgraph, bool call_init)
{
    if (call_init) 
        init(os);

    if (!separateComponents) 
        return writeComponent(os, molgraph);

    bool first_comp = true;

    const FragmentList& comp_list = *getComponents(molgraph);
    FragmentList::ConstElementIterator comps_end = comp_list.getElementsEnd();

    for (FragmentList::ConstElementIterator it = comp_list.getElementsBegin(); it != comps_end; ++it) {
        if (!first_comp) 
            os << JME::COMPONENT_SEPARATOR;

        const Fragment& frag = *it;
            
        if (frag.getNumAtoms() > 0) {
            if (!writeComponent(os, frag))
                return false;
            
            first_comp = false;
        }
    }

    os << getRecordSeparatorParameter(ioBase);
    
    return os.good();
}

void Chem::JMEDataWriter::init(std::ostream& os)
{
    strictErrorChecking = getStrictErrorCheckingParameter(ioBase);
    separateComponents = getJMESeparateComponentsParameter(ioBase);
    bondMemberSwapStereoFix = getBondMemberSwapStereoFixParameter(ioBase);
    coordsDim = getCoordinatesDimensionParameter(ioBase);

    switch (coordsDim) {

        case 0:
        case 2:
        case 3:
            break;

        default:
            coordsDim = 2;
    }

    os.imbue(std::locale::classic());

    os << std::dec << std::noshowpos << std::noshowbase;
}

bool Chem::JMEDataWriter::writeComponent(std::ostream& os, const MolecularGraph& molgraph)
{
    using namespace std::placeholders;
    
    os << molgraph.getNumAtoms() << ' ' << getCompleteBondCount(molgraph);  

    std::for_each(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(),
                  std::bind(&JMEDataWriter::writeAtom, this, std::ref(os), std::ref(molgraph), _1));
    
    std::for_each(molgraph.getBondsBegin(), molgraph.getBondsEnd(),
                  std::bind(&JMEDataWriter::writeBond, this, std::ref(os), std::ref(molgraph), _1));

    return os.good();
}

void Chem::JMEDataWriter::writeAtom(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom)
{
    using namespace JME;

    os << ' ';

    writeAtomString(os, molgraph, atom);

    std::size_t rxn_aam_id = getAtomMappingID(atom);

    if (rxn_aam_id > 0)
        os << AtomString::RXN_ATOM_ID_SEPARATOR << rxn_aam_id;

    switch (coordsDim) {

        case 2: {
            const Math::Vector2D& coords = get2DCoordinates(atom);

            os << ' ' << coords(0); 
            os << ' ' << coords(1);
            return;
        }

        case 3: {
            const Math::Vector3D& coords = get3DCoordinates(atom);

            os << ' ' << coords(0); 
            os << ' ' << coords(1);
            os << ' ' << coords(2);
        }

        default:
            return;
    }
}

void Chem::JMEDataWriter::writeAtomSymbol(std::ostream& os, const Atom& atom) const
{
    using namespace JME;

    const std::string& symbol = getSymbol(atom);

    if (symbol.length() == 0) {
        if (strictErrorChecking)
            throw Base::IOError("JMEDataWriter: empty atom symbol");

        os << DEF_ATOM_SYMBOL;

    } else
        os << symbol;
}

void Chem::JMEDataWriter::writeAtomCharge(std::ostream& os, const Atom& atom) const
{
    using namespace JME;

    long charge = getFormalCharge(atom);
  
    if (charge != 0) {
        os << (charge > 0 ? AtomString::POSITIVE_CHARGE_PREFIX : AtomString::NEGATIVE_CHARGE_PREFIX);

        if (charge > 1 || charge < -1)
            os << (charge > 0 ? charge : -charge);
    }
}

void Chem::JMEDataWriter::writeAtomString(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom)
{
    const MatchConstraintList& constr_list = *getMatchConstraints(atom);

    if (constr_list.getSize() == 0) {
        writeAtomSymbol(os, atom);
        writeAtomCharge(os, atom);
        return;
    }

    writtenAromConstraint = 0;

    if (constr_list.getType() == MatchConstraintList::AND_LIST) {
        bool wrote_alist = false;

        MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();

        for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
            const MatchConstraint& constraint = *it;

            if (constraint.getID() != AtomMatchConstraint::CONSTRAINT_LIST)
                continue;

            if (constraint.getRelation() != MatchConstraint::EQUAL)
                continue;

            const MatchConstraintList& constr_list = *constraint.getValue<MatchConstraintList::SharedPointer>();

            if (constr_list.getType() != MatchConstraintList::OR_LIST)
                continue;

            if ((wrote_alist = writeAtomList(os, atom, constr_list, false)))
                break;
        }

        bool wrote_atom_type = true;

        if (!wrote_alist) 
            if (!writeAtomType(os, atom, constr_list, false, true)) 
                if (!writeAtomType(os, atom, constr_list, false, false)) {
                    writeAtomSymbol(os, atom);
                    wrote_atom_type = false;
                }

        if (!(writeQueryFlags(os, molgraph, atom, constr_list) || wrote_alist || wrote_atom_type))
            writeAtomCharge(os,atom);

        return;
    }

    if (constr_list.getType() == MatchConstraintList::OR_LIST) {
        bool wrote_alist = writeAtomList(os, atom, constr_list, false);

        if (constr_list.getSize() == 1) {
            bool wrote_atom_type = true;

            if (!wrote_alist) 
                if (!writeAtomType(os, atom, constr_list, false, true)) 
                    if (!writeAtomType(os, atom, constr_list, false, false)) {
                        writeAtomSymbol(os, atom);
                        wrote_atom_type = false;
                    }

            if (!(writeQueryFlags(os, molgraph, atom, constr_list) || wrote_alist || wrote_atom_type))
                writeAtomCharge(os,atom);

            return;
        }

        if (wrote_alist)
            return;
    }

    writeAtomSymbol(os, atom);
    writeAtomCharge(os, atom);
}

bool Chem::JMEDataWriter::writeAtomList(std::ostream& os, const Atom& atom, const MatchConstraintList& constr_list,
                                        bool write_separator)
{
    using namespace JME;

    MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();

    for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
        const MatchConstraint& constraint = *it;

        switch (constraint.getID()) {

            case AtomMatchConstraint::CONSTRAINT_LIST: {
                if (constraint.getRelation() != MatchConstraint::EQUAL)
                    continue;

                const MatchConstraintList& constr_list = 
                    *constraint.getValue<MatchConstraintList::SharedPointer>();

                if (constr_list.getType() == MatchConstraintList::AND_LIST) 
                    write_separator |= writeAtomType(os, atom, constr_list, write_separator, false);

                else if (constr_list.getType() == MatchConstraintList::OR_LIST)
                    write_separator |= writeAtomList(os, atom, constr_list, write_separator);

                continue;
            }

            case AtomMatchConstraint::TYPE: {
                if (constraint.getRelation() != MatchConstraint::EQUAL)
                    continue;

                unsigned int atom_type;

                if (!constraint.hasValue()) 
                    atom_type = getType(atom);
                else
                    atom_type = constraint.getValue<unsigned int>();

                switch (atom_type) {

                    case AtomType::ANY:
                        if (write_separator)
                            os << AtomString::ATOM_LIST_SEPARATOR;

                        os << AtomString::ANY_ATOM_SYMBOL;
                        break;

                    case AtomType::QH:
                        if (write_separator)
                            os << AtomString::ATOM_LIST_SEPARATOR;

                        os << AtomString::ANY_NON_C_ATOM_SYMBOL;
                        break;

                    default:
                        if (atom_type == AtomType::UNKNOWN ||
                            atom_type > AtomType::MAX_ATOMIC_NO)
                            continue;

                        if (write_separator)
                            os << AtomString::ATOM_LIST_SEPARATOR;

                        os << AtomString::ATOMIC_NUMBER_PREFIX << atom_type;
                }

                write_separator = true;
                continue;
            }

            case AtomMatchConstraint::AROMATICITY: {
                if (constraint.getRelation() != MatchConstraint::EQUAL &&  
                    constraint.getRelation() != MatchConstraint::NOT_EQUAL)
                    continue;

                bool is_aromatic;

                if (!constraint.hasValue()) 
                    is_aromatic = getAromaticityFlag(atom);
                else
                    is_aromatic = constraint.getValue<bool>();

                if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
                    is_aromatic = !is_aromatic; 

                if (write_separator)
                    os << AtomString::ATOM_LIST_SEPARATOR;

                os << (is_aromatic ? AtomString::ANY_AROM_ATOM_SYMBOL : AtomString::ANY_NON_AROM_ATOM_SYMBOL);

                write_separator = true;
            }

            default:
                continue;
        }
    }

    return write_separator;
}

bool Chem::JMEDataWriter::writeAtomType(std::ostream& os, const Atom& atom, const MatchConstraintList& constr_list,
                                        bool write_separator, bool type_mandatory)
{
    using namespace JME;

    MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();

    for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
        const MatchConstraint& constraint = *it;

        switch (constraint.getID()) {

            case AtomMatchConstraint::CONSTRAINT_LIST: {
                if (constraint.getRelation() != MatchConstraint::EQUAL)
                    continue;

                const MatchConstraintList& constr_list = 
                    *constraint.getValue<MatchConstraintList::SharedPointer>();

                if (constr_list.getType() == MatchConstraintList::AND_LIST || 
                    (constr_list.getType() == MatchConstraintList::OR_LIST && constr_list.getSize() == 1))
                    if (writeAtomType(os, atom, constr_list, write_separator, type_mandatory))
                        return true;

                continue;
            }

            case AtomMatchConstraint::TYPE: {
                if (constraint.getRelation() != MatchConstraint::EQUAL)
                    continue;

                unsigned int atom_type;

                if (!constraint.hasValue()) 
                    atom_type = getType(atom);
                else
                    atom_type = constraint.getValue<unsigned int>();

                if (atom_type == AtomType::UNKNOWN ||
                    (atom_type > AtomType::MAX_ATOMIC_NO &&
                     atom_type != AtomType::ANY && 
                     atom_type != AtomType::QH))
                    continue;

                if (it + 1 != constr_end) {
                    const MatchConstraint& next_constraint = *(it + 1);

                    if (next_constraint.getID() == AtomMatchConstraint::AROMATICITY && 
                        (next_constraint.getRelation() == MatchConstraint::EQUAL ||  
                         next_constraint.getRelation() == MatchConstraint::NOT_EQUAL)) {

                        bool is_aromatic = false;

                        if (!next_constraint.hasValue()) 
                            is_aromatic = getAromaticityFlag(atom);
                        else
                            is_aromatic = next_constraint.getValue<bool>();

                        if (next_constraint.getRelation() == MatchConstraint::NOT_EQUAL)
                            is_aromatic = !is_aromatic; 

                        if (writeAtomType(os, atom_type, true, is_aromatic, write_separator))
                            writtenAromConstraint = &next_constraint;
                        
                        return true;
                    }
                }

                writeAtomType(os, atom_type, false, false, write_separator);
                return true;
            }

            case AtomMatchConstraint::AROMATICITY: {
                if (constraint.getRelation() != MatchConstraint::EQUAL &&  
                    constraint.getRelation() != MatchConstraint::NOT_EQUAL)
                    continue;

                unsigned int atom_type = AtomType::UNKNOWN;

                if (it + 1 != constr_end) {
                    const MatchConstraint& next_constraint = *(it + 1);

                    if (next_constraint.getID() == AtomMatchConstraint::TYPE && 
                        next_constraint.getRelation() == MatchConstraint::EQUAL) {

                        if (!next_constraint.hasValue()) 
                            atom_type = getType(atom);
                        else
                            atom_type = constraint.getValue<unsigned int>();

                        if (atom_type > AtomType::MAX_ATOMIC_NO &&
                            atom_type != AtomType::ANY && 
                            atom_type != AtomType::QH)
                            atom_type = AtomType::UNKNOWN;
                    }
                }

                if (atom_type == AtomType::UNKNOWN && type_mandatory)
                    continue;

                bool is_aromatic;

                if (!constraint.hasValue()) 
                    is_aromatic = getAromaticityFlag(atom);
                else
                    is_aromatic = constraint.getValue<bool>();

                if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
                    is_aromatic = !is_aromatic; 

                if (writeAtomType(os, atom_type, true, is_aromatic, write_separator))
                    writtenAromConstraint = &constraint;

                return true;
            }

            default:
                continue;
        }
    }

    return false;
}
    
bool Chem::JMEDataWriter::writeAtomType(std::ostream& os, unsigned int atom_type, bool aromaticity, bool is_aromatic,
                                        bool write_alist_separator) const
{
    using namespace JME;

    std::string symbol;

    switch (atom_type) {

        case AtomType::ANY:
            if (aromaticity) 
                symbol.append(is_aromatic ? AtomString::ANY_AROM_ATOM_SYMBOL : AtomString::ANY_NON_AROM_ATOM_SYMBOL);
            else
                symbol.append(AtomString::ANY_ATOM_SYMBOL);

            break;

        case AtomType::QH:
            symbol.append(AtomString::ANY_NON_C_ATOM_SYMBOL);
            aromaticity = false;
            break;

        case AtomType::N:
            if (aromaticity) 
                symbol.push_back(is_aromatic ? 'n' : 'N');

            else {
                symbol.push_back(AtomString::ATOMIC_NUMBER_PREFIX);
                symbol.push_back('7');
            }

            break;

        case AtomType::O:
            if (aromaticity) 
                symbol.push_back(is_aromatic ? 'o' : 'O');

            else {
                symbol.push_back(AtomString::ATOMIC_NUMBER_PREFIX);
                symbol.push_back('8');
            }

            break;

        case AtomType::S:
            if (aromaticity) 
                symbol.push_back(is_aromatic ? 's' : 'S');

            else {
                symbol.push_back(AtomString::ATOMIC_NUMBER_PREFIX);
                symbol.append("16");
            }

            break;
            
        case AtomType::P:
            if (aromaticity) 
                symbol.push_back(is_aromatic ? 'p' : 'P');

            else {
                symbol.push_back(AtomString::ATOMIC_NUMBER_PREFIX);
                symbol.append("15");
            }

            break;

        case AtomType::C:
            if (aromaticity) 
                symbol.push_back(is_aromatic ? 'c' : 'C');

            else {
                symbol.push_back(AtomString::ATOMIC_NUMBER_PREFIX);
                symbol.push_back('6');
            }

            break;

        case AtomType::F:
            symbol.push_back('F');

            if (aromaticity && is_aromatic)
                aromaticity = false;

            break;

        case AtomType::Cl:
            symbol.append("Cl");

            if (aromaticity && is_aromatic)
                aromaticity = false;

            break;

        case AtomType::Br:
            symbol.append("Br");

            if (aromaticity && is_aromatic)
                aromaticity = false;

            break;

        case AtomType::I:
            symbol.push_back('I');

            if (aromaticity && is_aromatic)
                aromaticity = false;

            break;

        default:
            if (atom_type == AtomType::UNKNOWN) {
                if (aromaticity) {
                    symbol.append(is_aromatic ? AtomString::ANY_AROM_ATOM_SYMBOL : AtomString::ANY_NON_AROM_ATOM_SYMBOL);
                    break;
                }

                assert(false);
            }

            if (aromaticity && !is_aromatic) {
                symbol.append(AtomDictionary::getSymbol(atom_type));
                break;
            }

            aromaticity = false;

            symbol.push_back(AtomString::ATOMIC_NUMBER_PREFIX);
            symbol.append(std::to_string(atom_type));
            break;
    }

    if (write_alist_separator)
        os << AtomString::ATOM_LIST_SEPARATOR;

    os << symbol;

    return aromaticity;
}

bool Chem::JMEDataWriter::writeQueryFlags(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom, 
                                          const MatchConstraintList& constr_list) const
{
    using namespace JME;

    bool result = false;

    MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();

    for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
        const MatchConstraint& constraint = *it;

        switch (constraint.getID()) {

            case AtomMatchConstraint::CONSTRAINT_LIST: {
                if (constraint.getRelation() != MatchConstraint::EQUAL)
                    continue;

                const MatchConstraintList& constr_list = 
                    *constraint.getValue<MatchConstraintList::SharedPointer>();

                if (constr_list.getType() == MatchConstraintList::AND_LIST|| 
                    (constr_list.getType() == MatchConstraintList::OR_LIST && constr_list.getSize() == 1))
                    result |= writeQueryFlags(os, molgraph, atom, constr_list);

                continue;
            }
                
            case AtomMatchConstraint::AROMATICITY: {
                if (&constraint == writtenAromConstraint)
                    continue;

                if (constraint.getRelation() != MatchConstraint::EQUAL &&  
                    constraint.getRelation() != MatchConstraint::NOT_EQUAL)
                    continue;

                bool is_aromatic;

                if (!constraint.hasValue()) 
                    is_aromatic = getAromaticityFlag(atom);
                else
                    is_aromatic = constraint.getValue<bool>();

                if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
                    is_aromatic = !is_aromatic; 

                os << AtomString::QUERY_FLAGS_SEPARATOR 
                   << (is_aromatic ? AtomString::ANY_AROM_ATOM_SYMBOL : AtomString::ANY_NON_AROM_ATOM_SYMBOL);

                break;
            }
            
            case AtomMatchConstraint::RING_TOPOLOGY: {
                if (constraint.getRelation() != MatchConstraint::EQUAL &&  
                    constraint.getRelation() != MatchConstraint::NOT_EQUAL)
                    continue;

                bool in_ring;

                if (!constraint.hasValue()) 
                    in_ring = getRingFlag(atom);
                else
                    in_ring = constraint.getValue<bool>();

                if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
                    in_ring = !in_ring; 

                os << AtomString::QUERY_FLAGS_SEPARATOR 
                   << (in_ring ? AtomString::RING_ATOM_FLAG : AtomString::CHAIN_ATOM_FLAG);

                break;
            }

            case AtomMatchConstraint::HEAVY_BOND_COUNT: {
                if (constraint.getRelation() != MatchConstraint::EQUAL)
                    continue;

                std::size_t heavy_bnd_count;

                if (!constraint.hasValue()) 
                    heavy_bnd_count = Internal::getHeavyBondCount(atom, molgraph);
                else
                    heavy_bnd_count = constraint.getValue<std::size_t>();

                os << AtomString::QUERY_FLAGS_SEPARATOR 
                   << AtomString::HEAVY_BOND_COUNT_PREFIX << std::to_string(heavy_bnd_count);

                break;
            }

            case AtomMatchConstraint::H_COUNT:{
                if (constraint.getRelation() != MatchConstraint::EQUAL)
                    continue;

                std::size_t h_count;

                if (!constraint.hasValue()) 
                    h_count = Internal::getAtomCount(atom, molgraph, AtomType::H);
                else
                    h_count = constraint.getValue<std::size_t>();

                os << AtomString::QUERY_FLAGS_SEPARATOR 
                   << AtomString::H_COUNT_PREFIX << std::to_string(h_count);

                break;
            }

            default:
                continue;
        }

        result = true;
    }

    return result;
}

void Chem::JMEDataWriter::writeBond(std::ostream& os, const MolecularGraph& molgraph, const Bond& bond) const
{
    using namespace JME;

    if (!molgraph.containsAtom(bond.getBegin()) || !molgraph.containsAtom(bond.getEnd()))
        return;

    int bond_type = BondType::SINGLE;
    bool swap_atoms = false;

    switch (getOrder(bond)) {

        case 1: {
            switch (get2DStereoFlag(bond)) {

                case BondStereoFlag::REVERSE_DOWN: 
                    if (bondMemberSwapStereoFix) {
                        bond_type = BondType::DOWN; 
                        swap_atoms = true;
                        break;
                    }

                case BondStereoFlag::UP:
                    bond_type = BondType::UP; 
                    break;

                case BondStereoFlag::REVERSE_UP: 
                    if (bondMemberSwapStereoFix) {
                        bond_type = BondType::UP; 
                        swap_atoms = true;
                        break;
                    }

                case BondStereoFlag::DOWN: 
                    bond_type = BondType::DOWN; 

                default:
                    break;
            }

            break;
        }

        case 2:
            bond_type = BondType::DOUBLE; 
            break;

        case 3:
            bond_type = BondType::TRIPLE; 
            break;

        default:
            if (strictErrorChecking)
                throw Base::IOError("JMEDataWriter: invalid bond order");

            break;
    }

    std::size_t atom_id1 = molgraph.getAtomIndex(bond.getBegin()) + 1;
    std::size_t atom_id2 = molgraph.getAtomIndex(bond.getEnd()) + 1;

    if (swap_atoms)
        os << ' ' << atom_id2 << ' ' << atom_id1;
    else
        os << ' ' << atom_id1 << ' ' << atom_id2;

    os << ' ' << bond_type;
}
