/* 
 * BondMatchExpressionStringFunction.cpp 
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

#include <functional>

#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/BondMatchConstraint.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/BondDirection.hpp"
#include "CDPL/Chem/ReactionCenterStatus.hpp"


using namespace CDPL; 


namespace
{

    const std::string LEFT_LIST_DELIMITER          = "(";
    const std::string RIGHT_LIST_DELIMITER         = ")";

    const std::string NOT_OPERATOR                 = "!";
    const std::string AND_OPERATOR                 = "&";
    const std::string LESS_OPERATOR                = "<";
    const std::string LESS_EQUAL_OPERATOR          = "<=";
    const std::string GREATER_OPERATOR             = ">";
    const std::string GREATER_EQUAL_OPERATOR       = ">=";

    const std::string AND_LIST_SEPARATOR           = ";";
    const std::string OR_LIST_SEPARATOR            = ",";

    const std::string DIRECTION_SYMBOL             = "D";
    const std::string UNSPECIFIED_DIRECTION_SYMBOL = "?";
    const std::string UP_DIRECTION_SYMBOL          = "/";
    const std::string DOWN_DIRECTION_SYMBOL        = "\\";

    const std::string SINGLE_BOND_SYMBOL           = "-";
    const std::string DOUBLE_BOND_SYMBOL           = "=";
    const std::string TRIPLE_BOND_SYMBOL           = "#";
    const std::string ANY_BOND_SYMBOL              = "~";
    const std::string RING_BOND_SYMBOL             = "@";
    const std::string AROMATIC_BOND_SYMBOL         = ":";

    const std::string RXN_CENTER_STATUS_SYMBOL     = "Rxn";

    const std::string CONFIGURATION_SYMBOL         = "C";
    const std::string NO_CONFIGURATION_SYMBOL      = "N";
    const std::string CIS_CONFIGURATION_SYMBOL     = "C";
    const std::string TRANS_CONFIGURATION_SYMBOL   = "T";
    const std::string EITHER_CONFIGURATION_SYMBOL  = "E";


    template <typename PropFunc>
    void createBooleanPropertyExpressionString(const Chem::Bond& bond, const Chem::MatchConstraint& constraint,
                                               std::string& expr_str, const std::string& constr_sym,
                                               const PropFunc& propFunc) 
    {
        using namespace Chem;

        if (constraint.getRelation() != MatchConstraint::EQUAL && 
            constraint.getRelation() != MatchConstraint::NOT_EQUAL)
            return;

        bool not_operator = false;

        if (constraint.getRelation() == MatchConstraint::NOT_EQUAL) 
            not_operator = !not_operator;

        bool flag;

        if (!constraint.hasValue()) 
            flag = propFunc(bond);
        else
            flag = constraint.getValue<bool>();

        if (!flag) 
            not_operator = !not_operator;

        if (not_operator)
            expr_str.append(NOT_OPERATOR);

        expr_str.append(constr_sym);
    }

    void createOrderExpressionString(const Chem::Bond& bond, const Chem::MatchConstraint& constraint,
                                     std::string& order_expr_str)
    {
        using namespace Chem;

        if (constraint.getRelation() != MatchConstraint::EQUAL && 
            constraint.getRelation() != MatchConstraint::NOT_EQUAL)
            return;

        std::size_t order = 0;
        bool order_valid = false;

        if (!constraint.hasValue()) {
            bool aromatic_bond = getAromaticityFlag(bond);
            order = getOrder(bond);

            if (aromatic_bond) {

                switch (order) {

                    case 1:
                        order = BondMatchConstraint::SINGLE | BondMatchConstraint::AROMATIC;
                        order_valid = true;
                        break;

                    case 2:
                        order = BondMatchConstraint::DOUBLE | BondMatchConstraint::AROMATIC;
                        order_valid = true;
                        break;

                    case 3:
                        order = BondMatchConstraint::TRIPLE | BondMatchConstraint::AROMATIC;
                        order_valid = true;

                    default:
                        break;
                }
            }

        } else {
            order = constraint.getValue<unsigned int>();

            if (order == BondMatchConstraint::IGNORE_AROMATICITY)
                order = getOrder(bond);
            else
                order_valid = true;
        }

        if (!order_valid)
            switch (order) {
            
                case 1:
                    order = BondMatchConstraint::SINGLE;
                    break;

                case 2:
                    order = BondMatchConstraint::DOUBLE;
                    break;

                case 3:
                    order = BondMatchConstraint::TRIPLE;
                    
                default:
                    break;    
            }

        std::size_t list_size = 0;

        if ((order & BondMatchConstraint::ANY_ORDER) == BondMatchConstraint::ANY_ORDER) {
            order_expr_str.append(ANY_BOND_SYMBOL);
            list_size++;

        } else {
            if ((order & BondMatchConstraint::SINGLE) != 0) {
                order_expr_str.append(SINGLE_BOND_SYMBOL);
                list_size++;
            }

            if ((order & BondMatchConstraint::DOUBLE) != 0) {
                if (list_size > 0)
                    order_expr_str.append(OR_LIST_SEPARATOR);

                order_expr_str.append(DOUBLE_BOND_SYMBOL);
                list_size++;
            } 

            if ((order & BondMatchConstraint::TRIPLE) != 0) {
                if (list_size > 0)
                    order_expr_str.append(OR_LIST_SEPARATOR);

                order_expr_str.append(TRIPLE_BOND_SYMBOL);
                list_size++;
            }

            if ((order & BondMatchConstraint::AROMATIC) != 0) {
                if (list_size > 0)
                    order_expr_str.append(OR_LIST_SEPARATOR);

                order_expr_str.append(AROMATIC_BOND_SYMBOL);
                list_size++;
            }
        }
    
        if (list_size == 0)
            return;

        if (list_size > 1) {
            order_expr_str.insert(0, LEFT_LIST_DELIMITER);
            order_expr_str.append(RIGHT_LIST_DELIMITER);
        }

        if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
            order_expr_str.insert(0, NOT_OPERATOR);
    }

    void createRxnCenterStatusExpressionString(const Chem::Bond& bond, const Chem::MatchConstraint& constraint,
                                               std::string& rcs_expr_str) 
    {
        using namespace Chem;

        if (constraint.getRelation() != MatchConstraint::EQUAL)
            return;

        unsigned int rxn_status;

        if (!constraint.hasValue())
            rxn_status = getReactionCenterStatus(bond);
        else
            rxn_status = constraint.getValue<unsigned int>();

        rxn_status &= (ReactionCenterStatus::NO_CENTER | ReactionCenterStatus::IS_CENTER | 
                       ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | 
                       ReactionCenterStatus::BOND_ORDER_CHANGE | ReactionCenterStatus::NO_CHANGE);

        if (rxn_status == 0)
            return;

        rcs_expr_str.append(RXN_CENTER_STATUS_SYMBOL);
    }

    void createDirectionExpressionString(const Chem::Bond& bond, const Chem::MatchConstraint& constraint,
                                         std::string& dir_expr_str) 
    {
        using namespace Chem;

        if (constraint.getRelation() != MatchConstraint::EQUAL && 
            constraint.getRelation() != MatchConstraint::NOT_EQUAL)
            return;

        unsigned int dir;

        if (!constraint.hasValue()) {
            dir = getDirection(bond);

            if (dir == BondDirection::NONE)
                return;

        } else
            dir = constraint.getValue<unsigned int>();

        dir &= (BondDirection::UP | BondDirection::DOWN | BondDirection::UNSPECIFIED);

        if (dir == 0)
            return;

        if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
            dir_expr_str.append(NOT_OPERATOR);

        dir_expr_str.append(DIRECTION_SYMBOL);

        if ((dir & BondDirection::UNSPECIFIED) != 0)
            dir_expr_str.append(UNSPECIFIED_DIRECTION_SYMBOL);

        if ((dir & BondDirection::DOWN) != 0)
            dir_expr_str.append(DOWN_DIRECTION_SYMBOL);

        if ((dir & BondDirection::UP) != 0)
            dir_expr_str.append(UP_DIRECTION_SYMBOL);
    }

    void createConfigurationExpressionString(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, 
                                             const Chem::MatchConstraint& constraint, std::string& geom_expr_str)
    {
        using namespace Chem;

        if (constraint.getRelation() != MatchConstraint::EQUAL && 
            constraint.getRelation() != MatchConstraint::NOT_EQUAL)
            return;

        unsigned int configuration;

        if (!constraint.hasValue()) {
            const StereoDescriptor& stereo_descr = calcStereoDescriptor(bond, molgraph, 0);
            configuration = stereo_descr.getConfiguration();

            if ((configuration & (BondConfiguration::CIS | BondConfiguration::TRANS)) == 0)
                return;

        } else {
            const StereoDescriptor& stereo_descr = constraint.getValue<StereoDescriptor>();

            configuration = stereo_descr.getConfiguration();
        }    
    
        configuration &= (BondConfiguration::NONE | BondConfiguration::Z |
                          BondConfiguration::E | BondConfiguration::EITHER);

        if (configuration == 0)
            return;

        if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
            geom_expr_str.append(NOT_OPERATOR);

        geom_expr_str.append(CONFIGURATION_SYMBOL);

        if ((configuration & BondConfiguration::NONE) != 0)
            geom_expr_str.append(NO_CONFIGURATION_SYMBOL);

        if ((configuration & BondConfiguration::EITHER) != 0)
            geom_expr_str.append(EITHER_CONFIGURATION_SYMBOL);

        if ((configuration & BondConfiguration::Z) != 0)
            geom_expr_str.append(CIS_CONFIGURATION_SYMBOL);

        if ((configuration & BondConfiguration::E) != 0)
            geom_expr_str.append(TRANS_CONFIGURATION_SYMBOL);
    }

    void createExpressionString(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, 
                                const Chem::MatchConstraintList& constr_list, std::string& expr_list_str, bool root);

    void createConstraintListExpressionString(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph,
                                              const Chem::MatchConstraint& constraint, std::string& expr_list_str)
    {
        using namespace Chem;

        if (constraint.getRelation() != MatchConstraint::EQUAL && 
            constraint.getRelation() != MatchConstraint::NOT_EQUAL)
            return;
    
        const MatchConstraintList& constr_list = 
            *constraint.getValue<MatchConstraintList::SharedPointer>();

        createExpressionString(bond, molgraph, constr_list, expr_list_str, false);

        if (!expr_list_str.empty() && constraint.getRelation() == MatchConstraint::NOT_EQUAL)
            expr_list_str.insert(0, NOT_OPERATOR);
    }

    void createExpressionString(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph,
                                const Chem::MatchConstraintList& constr_list, std::string& expr_list_str, bool root)
    {
        using namespace Chem;
        using namespace std::placeholders;
        
        std::size_t list_size = 0;
        std::string expr_str;

        bool or_list = (constr_list.getType() == MatchConstraintList::NOT_OR_LIST || 
                        constr_list.getType() == MatchConstraintList::OR_LIST);

        MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();

        for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
            const MatchConstraint& constraint = *it;

            switch (constraint.getID()) {

                case BondMatchConstraint::CONSTRAINT_LIST:
                    createConstraintListExpressionString(bond, molgraph, constraint, expr_str);
                    break;

                case BondMatchConstraint::ORDER:
                    createOrderExpressionString(bond, constraint, expr_str);
                    break;        

                case BondMatchConstraint::AROMATICITY:
                    createBooleanPropertyExpressionString(bond, constraint, expr_str, AROMATIC_BOND_SYMBOL, 
                                                          std::bind(&getAromaticityFlag, _1));
                    break;        

                case BondMatchConstraint::RING_TOPOLOGY:
                    createBooleanPropertyExpressionString(bond, constraint, expr_str, RING_BOND_SYMBOL, 
                                                          std::bind(&getRingFlag, _1));
                    break;        

                case BondMatchConstraint::CONFIGURATION:
                    createConfigurationExpressionString(bond, molgraph, constraint, expr_str);
                    break;        

                case BondMatchConstraint::REACTION_CENTER_STATUS:
                    createRxnCenterStatusExpressionString(bond, constraint, expr_str);
                    break;        

                case BondMatchConstraint::DIRECTION:
                    createDirectionExpressionString(bond, constraint, expr_str);
                    break;        

                default:
                    continue;
            }

            if (expr_str.empty())
                continue;

            if (list_size > 0) 
                expr_list_str.append(or_list ? OR_LIST_SEPARATOR : AND_LIST_SEPARATOR);
        
            expr_list_str.append(expr_str);
            expr_str.clear();

            list_size++;
        }

        if (list_size == 0)
            return;

        bool not_list = (constr_list.getType() == MatchConstraintList::NOT_AND_LIST || 
                         constr_list.getType() == MatchConstraintList::NOT_OR_LIST);

        if (list_size > 1 && (!root || not_list)) {
            expr_list_str.insert(0, LEFT_LIST_DELIMITER);
            expr_list_str.append(RIGHT_LIST_DELIMITER);
        }

        if (not_list)
            expr_list_str.insert(0, NOT_OPERATOR);
    }
}


void Chem::buildMatchExpressionString(const Bond& bond, const MolecularGraph& molgraph, std::string& expr_str)
{
    createExpressionString(bond, molgraph, *getMatchConstraints(bond), expr_str, true);
}
