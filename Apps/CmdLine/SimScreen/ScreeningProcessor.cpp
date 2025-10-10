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
    scoringFunc(scr_func), descrCalculator(calc.clone()), callbackFunc(cb_func), queryBSDescrs(proc.queryBSDescrs),
    queryDVDescrs(proc.queryDVDescrs) {}

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
                
    if (descrCalculator->requires3DCoordinates()) {
        auto num_confs = getNumConformations(query_mol);

        if (num_confs == 0) {
            if (!hasCoordinates(query_mol, 3)) {
                error = "molecule lacks atom 3D coordinates";
                return false;
            }

            if (bs_descr) {
                queryBSDescrs.resize(queryBSDescrs.size() + 1);
                queryBSDescrs.back().resize(1);

                if (descr_conv) {
                    descrCalculator->calculate(query_mol, tmpDVector);
                    convert(tmpDVector, queryBSDescrs.back().front());
                    
                } else
                    descrCalculator->calculate(query_mol, queryBSDescrs.back().front());
                
            } else {
                queryDVDescrs.resize(queryDVDescrs.size() + 1);
                queryDVDescrs.back().resize(1);

                if (descr_conv) {
                    descrCalculator->calculate(query_mol, tmpBitSet);
                    convert(tmpBitSet, queryDVDescrs.back().front());
                    
                } else
                    descrCalculator->calculate(query_mol, queryDVDescrs.back().front());
            }
            
        } else {
            if (bs_descr) {
                queryBSDescrs.resize(queryBSDescrs.size() + 1);
                queryBSDescrs.back().resize(num_confs);

            } else {
                queryDVDescrs.resize(queryDVDescrs.size() + 1);
                queryDVDescrs.back().resize(num_confs);
            }
             
            for (std::size_t i = 0; i < num_confs; i++) {
                applyConformation(query_mol, i);

                if (bs_descr) {
                    if (descr_conv) {
                        descrCalculator->calculate(query_mol, tmpDVector);
                        convert(tmpDVector, queryBSDescrs.back()[i]);

                    } else
                        descrCalculator->calculate(query_mol, queryBSDescrs.back()[i]);

                } else {
                    if (descr_conv) {
                        descrCalculator->calculate(query_mol, tmpBitSet);
                        convert(tmpBitSet, queryDVDescrs.back()[i]);

                    } else
                        descrCalculator->calculate(query_mol, queryDVDescrs.back()[i]);
                }
            }
        }
        
    } else {
        if (bs_descr) {
            queryBSDescrs.resize(queryBSDescrs.size() + 1);
            queryBSDescrs.back().resize(1);

            if (descr_conv) {
                descrCalculator->calculate(query_mol, tmpDVector);
                convert(tmpDVector, queryBSDescrs.back().front());
                    
            } else
                descrCalculator->calculate(query_mol, queryBSDescrs.back().front());
                
        } else {
            queryDVDescrs.resize(queryDVDescrs.size() + 1);
            queryDVDescrs.back().resize(1);

            if (descr_conv) {
                descrCalculator->calculate(query_mol, tmpBitSet);
                convert(tmpBitSet, queryDVDescrs.back().front());
                    
            } else
                descrCalculator->calculate(query_mol, queryDVDescrs.back().front());
        }
    }
    
    return true; // TODO
}

bool ScreeningProcessor::process(CDPL::Chem::Molecule& db_mol, ScreeningMode mode)
{
    return false; // TODO
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
