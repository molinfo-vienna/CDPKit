/* 
 * ScreeningProcessor.cpp
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


#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Entity3DContainerFunctions.hpp"

#include "ScreeningProcessor.hpp"
#include "ScoringFunction.hpp"
#include "DescriptorCalculator.hpp"


using namespace SimScreen;


ScreeningProcessor::ScreeningProcessor(const ScoringFunction& scr_func, const DescriptorCalculator& calc):
    scoringFunc(scr_func), descrCalculator(calc.clone()) {}

ScreeningProcessor::ScreeningProcessor(const ScreeningProcessor& proc, const ScoringFunction& scr_func,
                                       const DescriptorCalculator& calc, const ResultCallbackFunc& cb_func):
    scoringFunc(scr_func), descrCalculator(calc.clone()), callbackFunc(cb_func), queryMolBSDescrs(proc.queryMolBSDescrs),
    queryMolDVDescrs(proc.queryMolDVDescrs) {}

ScreeningProcessor::~ScreeningProcessor() {}

const std::string&  ScreeningProcessor::getError() const
{
    return error;
}

bool ScreeningProcessor::addQuery(CDPL::Chem::Molecule& query_mol)
{
    descrCalculator->prepare(query_mol);

    auto bs_descr = false;
    auto descr_conv = false;
    
    switch (scoringFunc.getDescriptorType()) {

        case ScoringFunction::BITSET:
            bs_descr = true;
            descr_conv = (descrCalculator->getDescriptorType() == DescriptorCalculator::VECTOR);
            break;
            
        case ScoringFunction::VECTOR:
            descr_conv = (descrCalculator->getDescriptorType() == DescriptorCalculator::BITSET);
            break;

        case ScoringFunction::ANY:
            bs_descr = (descrCalculator->getDescriptorType() == DescriptorCalculator::BITSET);
    }

    std::size_t num_query_mol_confs = 0;
                  
    if (descrCalculator->requires3DCoordinates()) {
        num_query_mol_confs = getNumConformations(query_mol);

        if ((num_query_mol_confs == 0) && !hasCoordinates(query_mol, 3)) {
            if (bs_descr)
                queryMolBSDescrs.resize(queryMolBSDescrs.size() + 1);
            else
                queryMolDVDescrs.resize(queryMolDVDescrs.size() + 1);
                
            error = "molecule lacks atom 3D coordinates";
            return false;
        }
    }

    std::size_t num_query_mol_descrs = (num_query_mol_confs == 0 ? 1 : num_query_mol_confs);
    
    if (bs_descr) {
        queryMolBSDescrs.resize(queryMolBSDescrs.size() + 1);
        queryMolBSDescrs.back().resize(num_query_mol_descrs);

    } else {
        queryMolDVDescrs.resize(queryMolDVDescrs.size() + 1);
        queryMolDVDescrs.back().resize(num_query_mol_descrs);
    }

    for (std::size_t i = 0; i < num_query_mol_descrs; i++) {
        if (num_query_mol_confs > 0)
            applyConformation(query_mol, i);

        if (bs_descr) {
            if (descr_conv) {
                descrCalculator->calculate(query_mol, tmpDVector);
                convert(tmpDVector, queryMolBSDescrs.back()[i]);

            } else
                descrCalculator->calculate(query_mol, queryMolBSDescrs.back()[i]);

        } else {
            if (descr_conv) {
                descrCalculator->calculate(query_mol, tmpBitSet);
                convert(tmpBitSet, queryMolDVDescrs.back()[i]);

            } else
                descrCalculator->calculate(query_mol, queryMolDVDescrs.back()[i]);
        }
    }
     
    return true;
}

bool ScreeningProcessor::process(CDPL::Chem::Molecule& db_mol, ScreeningMode mode)
{
    descrCalculator->prepare(db_mol);

    auto bs_descr = false;
    auto descr_conv = false;
    
    switch (scoringFunc.getDescriptorType()) {

        case ScoringFunction::BITSET:
            bs_descr = true;
            descr_conv = (descrCalculator->getDescriptorType() == DescriptorCalculator::VECTOR);
            break;
            
        case ScoringFunction::VECTOR:
            descr_conv = (descrCalculator->getDescriptorType() == DescriptorCalculator::BITSET);
            break;

        case ScoringFunction::ANY:
            bs_descr = (descrCalculator->getDescriptorType() == DescriptorCalculator::BITSET);
    }

    std::size_t num_db_mol_confs = 0;
    
    if (descrCalculator->requires3DCoordinates()) {
        num_db_mol_confs = getNumConformations(db_mol);

        if ((num_db_mol_confs == 0) && !hasCoordinates(db_mol, 3)) {
            error = "molecule lacks atom 3D coordinates";
            return false;
        }
    }

    std::size_t num_db_mol_descrs = (num_db_mol_confs == 0 ? 1 : num_db_mol_confs);

    if (bs_descr) {
        if (dbMolBSDescrs.size() < num_db_mol_descrs)
            dbMolBSDescrs.resize(num_db_mol_descrs);

    } else {
        if (dbMolDVDescrs.size() < num_db_mol_descrs)
            dbMolDVDescrs.resize(num_db_mol_descrs);
    }
    
    for (std::size_t i = 0; i < num_db_mol_descrs; i++) {
        if (num_db_mol_confs > 0)
            applyConformation(db_mol, i);

        if (bs_descr) {
            if (descr_conv) {
                descrCalculator->calculate(db_mol, tmpDVector);
                convert(tmpDVector, dbMolBSDescrs[i]);

            } else
                descrCalculator->calculate(db_mol, dbMolBSDescrs[i]);

        } else {
            if (descr_conv) {
                descrCalculator->calculate(db_mol, tmpBitSet);
                convert(tmpBitSet, dbMolDVDescrs[i]);
                
            } else
                descrCalculator->calculate(db_mol, dbMolDVDescrs[i]);
        }
    }
    
    Result best_result;
    auto first = true;

    if (bs_descr) {
        for (std::size_t i = 0, num_qery_mols = queryMolBSDescrs.size(); i < num_qery_mols; i++) {
            auto& query_descr_list = queryMolBSDescrs[i];

            for (std::size_t j = 0, num_query_mol_descrs = query_descr_list.size(); j < num_query_mol_descrs; j++) {
                for (std::size_t k = 0; k < num_db_mol_descrs; k++) {
                    auto score = scoringFunc.calculate(query_descr_list[j], dbMolBSDescrs[k]);

                    if (first || scoringFunc.compare(best_result.score, score)) {
                        best_result.score           = score;
                        best_result.queryMolIdx     = i;
                        best_result.queryMolConfIdx = j;
                        best_result.dbMolConfIdx    = k;
                        first                       = false;
                    }
                }
                
                if (mode == BEST_MATCH_PER_QUERY_CONF) {
                    callbackFunc(best_result);
                    first = true;
                }
            }

            if (!first && (mode == BEST_MATCH_PER_QUERY)) {
                callbackFunc(best_result);
                first = true;
            }
        }

    } else {
        for (std::size_t i = 0, num_qery_mols = queryMolDVDescrs.size(); i < num_qery_mols; i++) {
            auto& query_descr_list = queryMolDVDescrs[i];

            for (std::size_t j = 0, num_query_mol_descrs = query_descr_list.size(); j < num_query_mol_descrs; j++) {
                for (std::size_t k = 0; k < num_db_mol_descrs; k++) {
                    auto score = scoringFunc.calculate(query_descr_list[j], dbMolDVDescrs[k]);

                    if (first || scoringFunc.compare(best_result.score, score)) {
                        best_result.score           = score;
                        best_result.queryMolIdx     = i;
                        best_result.queryMolConfIdx = j;
                        best_result.dbMolConfIdx    = k;
                        first                       = false;
                    }
                }
                
                if (mode == BEST_MATCH_PER_QUERY_CONF) {
                    callbackFunc(best_result);
                    first = true;
                }
            }

            if (!first && (mode == BEST_MATCH_PER_QUERY)) {
                callbackFunc(best_result);
                first = true;
            }
        }
    }

    if (!first && (mode == BEST_OVERALL_MATCH))
        callbackFunc(best_result);

    return true;
}

void ScreeningProcessor::convert(const CDPL::Util::BitSet& bset, CDPL::Math::DVector& vec)
{
    vec.resize(bset.size());

    for (std::size_t i = 0, num_bits = bset.size(); i < num_bits; i++)
        vec[i] = bset.test(i);
}

void ScreeningProcessor::convert(const CDPL::Math::DVector& vec, CDPL::Util::BitSet& bset)
{
    bset.resize(vec.getSize());

    for (std::size_t i = 0, num_elem = vec.getSize(); i < num_elem; i++)
        bset.set(i, vec[i] != 0.0);
}
