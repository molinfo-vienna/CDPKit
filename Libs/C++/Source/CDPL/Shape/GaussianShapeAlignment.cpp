/* 
 * GaussianShapeAlignment.cpp 
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

#include "CDPL/Shape/GaussianShapeAlignment.hpp"
#include "CDPL/Shape/ScoringFunctions.hpp"
#include "CDPL/Shape/SymmetryClass.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


namespace
{

    bool compareScore(const Shape::AlignmentResult& res1, const Shape::AlignmentResult& res2)
    {
        return (res1.getScore() >= res2.getScore());
    }

    const Shape::GaussianShape& getShape(const Shape::GaussianShapeFunction* func)
    {
        return *func->getShape();
    }

    const std::size_t MAX_SHAPE_FUNC_CACHE_SIZE = 200;
}


constexpr double       Shape::GaussianShapeAlignment::DEF_OPTIMIZATION_STOP_GRADIENT;
constexpr double       Shape::GaussianShapeAlignment::DEF_DISTANCE_CUTOFF;
constexpr unsigned int Shape::GaussianShapeAlignment::DEF_RESULT_SELECTION_MODE;
constexpr std::size_t  Shape::GaussianShapeAlignment::DEF_MAX_OPTIMIZATION_ITERATIONS;
constexpr std::size_t  Shape::GaussianShapeAlignment::DEF_MAX_PRODUCT_ORDER;


Shape::GaussianShapeAlignment::GaussianShapeAlignment():
    shapeFuncCache(MAX_SHAPE_FUNC_CACHE_SIZE), calcSlfOverlaps(true), calcColSlfOverlaps(true),
    resultSelMode(DEF_RESULT_SELECTION_MODE), resultCmpFunc(&compareScore), 
    scoringFunc(&calcTotalOverlapTanimotoScore), currSetIndex(0), currShapeIndex(0)
{
    algdShapeFunc.setMaxOrder(DEF_MAX_PRODUCT_ORDER);
    algdShapeFunc.setDistanceCutoff(DEF_DISTANCE_CUTOFF);

    shapeFuncAlmnt.setMaxNumOptimizationIterations(DEF_MAX_OPTIMIZATION_ITERATIONS);
    shapeFuncAlmnt.setOptimizationStopGradient(DEF_OPTIMIZATION_STOP_GRADIENT);
}

Shape::GaussianShapeAlignment::GaussianShapeAlignment(const GaussianShape& ref_shape):
    shapeFuncCache(MAX_SHAPE_FUNC_CACHE_SIZE), calcSlfOverlaps(true), calcColSlfOverlaps(true),
    resultSelMode(DEF_RESULT_SELECTION_MODE), resultCmpFunc(&compareScore), 
    scoringFunc(&calcTotalOverlapTanimotoScore), currSetIndex(0), currShapeIndex(0)
{
    algdShapeFunc.setMaxOrder(DEF_MAX_PRODUCT_ORDER);
    algdShapeFunc.setDistanceCutoff(DEF_DISTANCE_CUTOFF);

    shapeFuncAlmnt.setMaxNumOptimizationIterations(DEF_MAX_OPTIMIZATION_ITERATIONS);
    shapeFuncAlmnt.setOptimizationStopGradient(DEF_OPTIMIZATION_STOP_GRADIENT);

    addReferenceShape(ref_shape);
}

Shape::GaussianShapeAlignment::GaussianShapeAlignment(const GaussianShapeSet& ref_shapes):
    shapeFuncCache(MAX_SHAPE_FUNC_CACHE_SIZE), calcSlfOverlaps(true), calcColSlfOverlaps(true),
    resultSelMode(DEF_RESULT_SELECTION_MODE), resultCmpFunc(&compareScore), 
    scoringFunc(&calcTotalOverlapTanimotoScore), currSetIndex(0), currShapeIndex(0)
{
    algdShapeFunc.setMaxOrder(DEF_MAX_PRODUCT_ORDER);
    algdShapeFunc.setDistanceCutoff(DEF_DISTANCE_CUTOFF);

    shapeFuncAlmnt.setMaxNumOptimizationIterations(DEF_MAX_OPTIMIZATION_ITERATIONS);
    shapeFuncAlmnt.setOptimizationStopGradient(DEF_OPTIMIZATION_STOP_GRADIENT);

    addReferenceShapes(ref_shapes);
}

Shape::GaussianShapeAlignment::~GaussianShapeAlignment() 
{}

void Shape::GaussianShapeAlignment::setOverlapFunction(GaussianShapeOverlapFunction& func)
{
    shapeFuncAlmnt.setOverlapFunction(func);
}
            
Shape::GaussianShapeOverlapFunction& Shape::GaussianShapeAlignment::getOverlapFunction() const
{
    return shapeFuncAlmnt.getOverlapFunction();
}

const Shape::FastGaussianShapeOverlapFunction& Shape::GaussianShapeAlignment::getDefaultOverlapFunction() const
{
    return shapeFuncAlmnt.getDefaultOverlapFunction();
}

Shape::FastGaussianShapeOverlapFunction& Shape::GaussianShapeAlignment::getDefaultOverlapFunction()
{
    return shapeFuncAlmnt.getDefaultOverlapFunction();
}

void Shape::GaussianShapeAlignment::setStartGenerator(GaussianShapeAlignmentStartGenerator& gen)
{
    shapeFuncAlmnt.setStartGenerator(gen);
}
            
Shape::GaussianShapeAlignmentStartGenerator& Shape::GaussianShapeAlignment::getStartGenerator() const
{
    return shapeFuncAlmnt.getStartGenerator();
}

const Shape::PrincipalAxesAlignmentStartGenerator& Shape::GaussianShapeAlignment::getDefaultStartGenerator() const
{
    return shapeFuncAlmnt.getDefaultStartGenerator();
}

Shape::PrincipalAxesAlignmentStartGenerator& Shape::GaussianShapeAlignment::getDefaultStartGenerator()
{
    return shapeFuncAlmnt.getDefaultStartGenerator();
}

void Shape::GaussianShapeAlignment::setColorMatchFunction(const ColorMatchFunction& func)
{
    shapeFuncAlmnt.setColorMatchFunction(func);
}

const Shape::GaussianShapeAlignment::ColorMatchFunction& Shape::GaussianShapeAlignment::getColorMatchFunction() const
{
    return shapeFuncAlmnt.getColorMatchFunction();
}
    
void Shape::GaussianShapeAlignment::setColorFilterFunction(const ColorFilterFunction& func)
{
    shapeFuncAlmnt.setColorFilterFunction(func);
}

const Shape::GaussianShapeAlignment::ColorFilterFunction& Shape::GaussianShapeAlignment::getColorFilterFunction() const
{
    return shapeFuncAlmnt.getColorFilterFunction();
}

void Shape::GaussianShapeAlignment::setResultCompareFunction(const ResultCompareFunction& func)
{
    if (!func)
        resultCmpFunc = &compareScore;
    else
        resultCmpFunc = func;
}

const Shape::GaussianShapeAlignment::ResultCompareFunction& Shape::GaussianShapeAlignment::getResultCompareFunction() const
{
    return resultCmpFunc;
}

void Shape::GaussianShapeAlignment::setScoringFunction(const ScoringFunction& func)
{
    if (!func)
        scoringFunc = &calcTotalOverlapTanimotoScore;
    else
        scoringFunc = func;
}

const Shape::GaussianShapeAlignment::ScoringFunction& Shape::GaussianShapeAlignment::getScoringFunction() const
{
    return scoringFunc;
}

void Shape::GaussianShapeAlignment::setResultSelectionMode(unsigned int mode)
{
    resultSelMode = mode;
}

unsigned int Shape::GaussianShapeAlignment::getResultSelectionMode() const
{
    return resultSelMode;
}

void Shape::GaussianShapeAlignment::calcSelfOverlaps(bool calc)
{
    calcSlfOverlaps = calc;
}

bool Shape::GaussianShapeAlignment::calcSelfOverlaps() const
{
    return calcSlfOverlaps;
}

void Shape::GaussianShapeAlignment::calcColorSelfOverlaps(bool calc)
{
    calcColSlfOverlaps = calc;
}

bool Shape::GaussianShapeAlignment::calcColorSelfOverlaps() const
{
    return calcColSlfOverlaps;
}

void Shape::GaussianShapeAlignment::calcColorOverlaps(bool calc)
{
    shapeFuncAlmnt.calcColorOverlaps(calc);
}

bool Shape::GaussianShapeAlignment::calcColorOverlaps() const
{
    return shapeFuncAlmnt.calcColorOverlaps();
}

void Shape::GaussianShapeAlignment::performAlignment(bool perf_align)
{
    if (shapeFuncAlmnt.performAlignment() == perf_align)
        return;

    for (std::size_t i = 0, num_ref_shapes = refShapeFuncs.size(); i < num_ref_shapes; i++) {
        refShapeFuncs[i]->reset();

        if (perf_align) 
            refShapeMetaData[i].symClass = shapeFuncAlmnt.setupReference(*refShapeFuncs[i], refShapeMetaData[i].transform);

        else {
            refShapeMetaData[i].symClass = SymmetryClass::UNDEF;
            refShapeMetaData[i].transform = Math::IdentityMatrix<double>(4, 4);
        }
    }

    shapeFuncAlmnt.performAlignment(perf_align);
}

bool Shape::GaussianShapeAlignment::performAlignment() const
{
    return shapeFuncAlmnt.performAlignment();
}

void Shape::GaussianShapeAlignment::optimizeOverlap(bool optimize)
{
    shapeFuncAlmnt.optimizeOverlap(optimize);
}

bool Shape::GaussianShapeAlignment::optimizeOverlap() const
{
    return shapeFuncAlmnt.optimizeOverlap();
}

void Shape::GaussianShapeAlignment::greedyOptimization(bool greedy)
{
    shapeFuncAlmnt.greedyOptimization(greedy);
}

bool Shape::GaussianShapeAlignment::greedyOptimization() const
{
    return shapeFuncAlmnt.greedyOptimization();
}

void Shape::GaussianShapeAlignment::setMaxNumOptimizationIterations(std::size_t max_iter)
{
    shapeFuncAlmnt.setMaxNumOptimizationIterations(max_iter);
}

std::size_t Shape::GaussianShapeAlignment::getMaxNumOptimizationIterations() const
{
    return shapeFuncAlmnt.getMaxNumOptimizationIterations();
}

void Shape::GaussianShapeAlignment::setOptimizationStopGradient(double grad_norm)
{
    shapeFuncAlmnt.setOptimizationStopGradient(grad_norm);
}

double Shape::GaussianShapeAlignment::getOptimizationStopGradient() const
{
    return shapeFuncAlmnt.getOptimizationStopGradient();
}

void Shape::GaussianShapeAlignment::setMaxOrder(std::size_t max_order)
{
    algdShapeFunc.setMaxOrder(max_order);
}

std::size_t Shape::GaussianShapeAlignment::getMaxOrder() const
{
    return algdShapeFunc.getMaxOrder();
}

void Shape::GaussianShapeAlignment::setDistanceCutoff(double cutoff)
{
    algdShapeFunc.setDistanceCutoff(cutoff);
}

double Shape::GaussianShapeAlignment::getDistanceCutoff() const
{
    return algdShapeFunc.getDistanceCutoff();
}

void Shape::GaussianShapeAlignment::clearReferenceShapes()
{
    refShapeFuncs.clear();
    shapeFuncCache.putAll();

    currSetIndex = 0;
    currShapeIndex = 0;
}

void Shape::GaussianShapeAlignment::addReferenceShape(const GaussianShape& shape, bool new_set)
{
    std::size_t num_ref_shapes = refShapeFuncs.size();
    
    if (new_set) {
        if (num_ref_shapes > 0)
            currSetIndex++;

        currShapeIndex = 0;
    }

    if (refShapeMetaData.size() < (num_ref_shapes + 1))
        refShapeMetaData.resize(num_ref_shapes + 1);

    if (!refShapeMetaData[num_ref_shapes].shape)
        refShapeMetaData[num_ref_shapes].shape.reset(new GaussianShape(shape));
    else
        *refShapeMetaData[num_ref_shapes].shape = shape;

    GaussianShapeFunction* func = allocShapeFunction(*refShapeMetaData[num_ref_shapes].shape);

    refShapeFuncs.push_back(func);

    prepareForAlignment(*func, refShapeMetaData[num_ref_shapes], true);
}

void Shape::GaussianShapeAlignment::addReferenceShapes(const GaussianShapeSet& shapes, bool new_set)
{
    std::size_t num_ref_shapes = refShapeFuncs.size();
    std::size_t num_new_ref_shapes = shapes.getSize();
    
    if (new_set) {
        if (num_ref_shapes > 0)
            currSetIndex++;

        currShapeIndex = 0;
    }

    if (refShapeMetaData.size() < (num_ref_shapes + num_new_ref_shapes))
        refShapeMetaData.resize(num_ref_shapes + num_new_ref_shapes);

    for (std::size_t i = 0; i < num_new_ref_shapes; i++) {
        if (!refShapeMetaData[num_ref_shapes + i].shape)
            refShapeMetaData[num_ref_shapes + i].shape.reset(new GaussianShape(shapes[i]));
        else
            *refShapeMetaData[num_ref_shapes + i].shape = shapes[i];


        GaussianShapeFunction* func = allocShapeFunction(*refShapeMetaData[num_ref_shapes + i].shape);

        refShapeFuncs.push_back(func);

        prepareForAlignment(*func, refShapeMetaData[num_ref_shapes + i], true);
    }
}

std::size_t Shape::GaussianShapeAlignment::getNumReferenceShapes() const
{
    return refShapeFuncs.size();
}

const Shape::GaussianShape& Shape::GaussianShapeAlignment::getReferenceShape(std::size_t idx) const
{
    if (idx >= refShapeFuncs.size())
        throw Base::IndexError("GaussianShapeAlignment: reference shape index out of bounds");

    return *refShapeFuncs[idx]->getShape();
}

Shape::GaussianShapeAlignment::ConstShapeIterator Shape::GaussianShapeAlignment::getReferenceShapesBegin() const
{
    return ConstShapeIterator(refShapeFuncs.begin(), &getShape);
}

Shape::GaussianShapeAlignment::ConstShapeIterator Shape::GaussianShapeAlignment::getReferenceShapesEnd() const
{
    return ConstShapeIterator(refShapeFuncs.end(), &getShape);
}

bool Shape::GaussianShapeAlignment::align(const GaussianShape& shape)
{
    results.clear();
    resIndexMap.clear();

    algdShapeFunc.setShape(shape);

    prepareForAlignment(algdShapeFunc, algdShapeMetaData, false);

    for (std::size_t i = 0, num_ref_shapes = refShapeFuncs.size(); i < num_ref_shapes; i++) {
        shapeFuncAlmnt.setReference(*refShapeFuncs[i], refShapeMetaData[i].symClass);

        if (!shapeFuncAlmnt.align(algdShapeFunc, algdShapeMetaData.symClass)) 
            continue;

        processResults(i, 0);
    }

    return !results.empty();
}

bool Shape::GaussianShapeAlignment::align(const GaussianShapeSet& shapes)
{
    results.clear();
    resIndexMap.clear();

    for (std::size_t i = 0, num_algd_shapes = shapes.getSize(), num_ref_shapes = refShapeFuncs.size(); i < num_algd_shapes; i++) {
        algdShapeFunc.setShape(shapes.getElement(i));

        prepareForAlignment(algdShapeFunc, algdShapeMetaData, false);

        for (std::size_t j = 0; j < num_ref_shapes; j++) {
            if (num_ref_shapes > 1 || i == 0)
                shapeFuncAlmnt.setReference(*refShapeFuncs[j], refShapeMetaData[j].symClass);

            if (!shapeFuncAlmnt.align(algdShapeFunc, algdShapeMetaData.symClass))
                continue;

            processResults(j, i);
        }
    }

    return !results.empty();
}

std::size_t Shape::GaussianShapeAlignment::getNumResults() const
{
    return results.size();
}

const Shape::AlignmentResult& Shape::GaussianShapeAlignment::getResult(std::size_t idx) const
{
    if (idx >= results.size())
        throw Base::IndexError("GaussianShapeAlignment: result index out of bounds");

    return results[idx];
}

Shape::AlignmentResult& Shape::GaussianShapeAlignment::getResult(std::size_t idx)
{
    if (idx >= results.size())
        throw Base::IndexError("GaussianShapeAlignment: result index out of bounds");

    return results[idx];
}

Shape::GaussianShapeAlignment::ConstResultIterator Shape::GaussianShapeAlignment::getResultsBegin() const
{
    return results.begin();
}

Shape::GaussianShapeAlignment::ConstResultIterator Shape::GaussianShapeAlignment::getResultsEnd() const
{
    return results.end();
}

Shape::GaussianShapeAlignment::ResultIterator Shape::GaussianShapeAlignment::getResultsBegin()
{
    return results.begin();
}

Shape::GaussianShapeAlignment::ResultIterator Shape::GaussianShapeAlignment::getResultsEnd()
{
    return results.end();
}
    
void Shape::GaussianShapeAlignment::prepareForAlignment(GaussianShapeFunction& func, ShapeMetaData& data, bool ref)
{
    if (ref) {
        data.setIndex = currSetIndex;
        data.index = currShapeIndex++;
    }

    data.selfOverlap = (calcSlfOverlaps ? shapeFuncAlmnt.calcSelfOverlap(func) : 0.0);
    data.colSelfOverlap = (calcColSlfOverlaps ? shapeFuncAlmnt.calcColorSelfOverlap(func) : 0.0);

    if (!shapeFuncAlmnt.performAlignment()) {
        data.symClass = SymmetryClass::UNDEF;
        data.transform = Math::IdentityMatrix<double>(4, 4);

    } else
        data.symClass = (ref ? shapeFuncAlmnt.setupReference(func, data.transform) : shapeFuncAlmnt.setupAligned(func, data.transform));
}

void Shape::GaussianShapeAlignment::processResults(std::size_t ref_idx, std::size_t al_idx)
{
    using namespace AlignmentResultSelectionMode;

    AlignmentResult curr_res;

    curr_res.setReferenceSelfOverlap(refShapeMetaData[ref_idx].selfOverlap);
    curr_res.setReferenceColorSelfOverlap(refShapeMetaData[ref_idx].colSelfOverlap);
    curr_res.setAlignedSelfOverlap(algdShapeMetaData.selfOverlap);
    curr_res.setAlignedColorSelfOverlap(algdShapeMetaData.colSelfOverlap);

    for (std::size_t i = 0, num_res = shapeFuncAlmnt.getNumResults(); i < num_res; i++) {
        std::size_t out_res_idx = 0;
        
        curr_res.setOverlap(shapeFuncAlmnt.getResult(i).getOverlap());
        curr_res.setColorOverlap(shapeFuncAlmnt.getResult(i).getColorOverlap());
        curr_res.setScore(scoringFunc(curr_res));

        switch (resultSelMode) {

            case ALL:
                out_res_idx = results.size();
                results.resize(out_res_idx + 1);
                break;

            case BEST_PER_SHAPE_COMBINATION:
                if (getResultIndex(ResultID(ref_idx, al_idx), out_res_idx))
                    break;

                if (resultCmpFunc(curr_res, results[out_res_idx]))
                    break;

                return;

            case BEST_PER_REFERENCE_SHAPE:
                if (getResultIndex(ResultID(ref_idx, 0), out_res_idx))
                    break;

                if (resultCmpFunc(curr_res, results[out_res_idx]))
                    break;

                return;

            case BEST_PER_REFERENCE_SET:
                if (getResultIndex(ResultID(refShapeMetaData[ref_idx].setIndex, 0), out_res_idx))
                    break;

                if (resultCmpFunc(curr_res, results[out_res_idx]))
                    break;

                return;

            case BEST_OVERALL:
                if (results.empty()) {
                    results.resize(1);
                    break;
                } 

                if (resultCmpFunc(curr_res, results[0]))
                    break;

            default:
                return;
        }

        Math::Matrix4D tmp(prod(refShapeMetaData[ref_idx].transform, shapeFuncAlmnt.getResult(i).getTransform()));

        curr_res.setTransform(prod(tmp, algdShapeMetaData.transform));
        curr_res.setReferenceShapeSetIndex(refShapeMetaData[ref_idx].setIndex);
        curr_res.setReferenceShapeIndex(refShapeMetaData[ref_idx].index);
        curr_res.setAlignedShapeIndex(al_idx);

        results[out_res_idx] = curr_res;
    }
}

bool Shape::GaussianShapeAlignment::getResultIndex(const ResultID& res_id, std::size_t& res_idx)
{
    ResultIndexMap::const_iterator it = resIndexMap.find(res_id);

    if (it == resIndexMap.end()) {
        res_idx = results.size();

        results.resize(res_idx + 1);
        resIndexMap.insert(ResultIndexMap::value_type(res_id, res_idx));

        return true;
    }

    res_idx = it->second;
    return false;
}

Shape::GaussianShapeFunction* Shape::GaussianShapeAlignment::allocShapeFunction(const GaussianShape& shape)
{
    GaussianShapeFunction* func = shapeFuncCache.get();

    func->setMaxOrder(algdShapeFunc.getMaxOrder());
    func->setDistanceCutoff(algdShapeFunc.getDistanceCutoff());
    func->setShape(shape);

    return func;
}
