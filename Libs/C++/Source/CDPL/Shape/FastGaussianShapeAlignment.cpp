/* 
 * FastGaussianShapeAlignment.cpp 
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


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing" // fastexp causes annoying aliasing warnings!

#include "StaticInit.hpp"

#include <cmath>
#include <algorithm>
#include <functional>

#include <boost/random/uniform_real.hpp>

#include "CDPL/Shape/FastGaussianShapeAlignment.hpp"
#include "CDPL/Shape/ScoringFunctions.hpp"
#include "CDPL/Shape/UtilityFunctions.hpp"
#include "CDPL/Shape/SymmetryClass.hpp"
#include "CDPL/Math/JacobiDiagonalization.hpp"
#include "CDPL/Math/MatrixProxy.hpp"
#include "CDPL/Math/AffineTransform.hpp"
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "Utilities.hpp"

#if defined(__APPLE__) && defined(__clang__)
# define exp_func(arg) std::exp(arg)
#elif defined(_MSC_VER)
# define exp_func(arg) std::exp(arg)
#else
# include "FastExp/fastexp.h"
# define exp_func(arg) fastexp::IEEE<double, 3>::evaluate(arg)
#endif


using namespace CDPL;


namespace
{

    const Math::DQuaternion IDENTITY_ROT(1.0, 0.0, 0.0, 0.0);

    const Math::DQuaternion X_180_ROT(0.0, 1.0, 0.0, 0.0);
    const Math::DQuaternion Y_180_ROT(0.0, 0.0, 1.0, 0.0);
    const Math::DQuaternion Z_180_ROT(0.0, 0.0, 0.0, 1.0);
    
    const Math::DQuaternion XY_SWAP_ROT(std::cos(M_PI * 0.25), 0.0, 0.0, std::sin(M_PI * 0.25));
    const Math::DQuaternion YZ_SWAP_ROT(std::cos(M_PI * 0.25), std::sin(M_PI * 0.25), 0.0, 0.0);
    const Math::DQuaternion XZ_SWAP_ROT(std::cos(M_PI * 0.25), 0.0, std::sin(M_PI * 0.25), 0.0);

    const Math::DQuaternion XYZ_SWAP_ROT1(std::cos(M_PI / 3.0), std::sin(M_PI / 3.0) * 0.5773502692,
                                          std::sin(M_PI / 3.0) * 0.5773502692, std::sin(M_PI / 3.0) * 0.5773502692);
    const Math::DQuaternion XYZ_SWAP_ROT2(std::cos(2.0 * M_PI / 3.0), std::sin(2.0 * M_PI / 3.0) * 0.5773502692,
                                          std::sin(2.0 * M_PI / 3.0) * 0.5773502692, std::sin(2.0 * M_PI / 3.0) * 0.5773502692);

    unsigned int getAxesSwapFlags(unsigned int sym_class)
    {
        using namespace Shape;
        
        switch (sym_class) {

            case SymmetryClass::ASYMMETRIC:
                return 0;

            case SymmetryClass::PROLATE:
                return 0b01;

            case SymmetryClass::OBLATE:
                return 0b10;

            default:
                break;
        }

        return 0b11;
    }

    bool compareScore(const Shape::AlignmentResult& res1, const Shape::AlignmentResult& res2)
    {
        return (res1.getScore() >= res2.getScore());
    }

    constexpr double RADIUS_SCALING_FACTOR                     = 1.4;
    constexpr double QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR = 10000.0;
    constexpr double BFGS_MINIMIZER_STEP_SIZE                  = 0.1;
    constexpr double BFGS_MINIMIZER_TOLERANCE                  = 0.5;
}


constexpr double       Shape::FastGaussianShapeAlignment::DEF_OPTIMIZATION_STOP_GRADIENT;
constexpr unsigned int Shape::FastGaussianShapeAlignment::DEF_RESULT_SELECTION_MODE;
constexpr std::size_t  Shape::FastGaussianShapeAlignment::DEF_MAX_OPTIMIZATION_ITERATIONS;
constexpr double       Shape::FastGaussianShapeAlignment::DEF_SYMMETRY_THRESHOLD;
constexpr std::size_t  Shape::FastGaussianShapeAlignment::DEF_NUM_RANDOM_STARTS;
constexpr double       Shape::FastGaussianShapeAlignment::DEF_MAX_RANDOM_TRANSLATION;


Shape::FastGaussianShapeAlignment::FastGaussianShapeAlignment():
    perfAlignment(true), optOverlap(true), greedyOpt(false), maxNumOptIters(DEF_MAX_OPTIMIZATION_ITERATIONS), 
    optStopGrad(DEF_OPTIMIZATION_STOP_GRADIENT), resultSelMode(DEF_RESULT_SELECTION_MODE), resultCmpFunc(&compareScore), 
    scoringFunc(&calcTotalOverlapTanimotoScore), currSetIndex(0), currShapeIndex(0),
    shapeCtrStarts(true), colCtrStarts(false), nonColCtrStarts(false), randomStarts(false),
    genForAlgdShape(false), genForRefShape(true), genForLargerShape(true),
    symThreshold(DEF_SYMMETRY_THRESHOLD), maxRandomTrans(DEF_MAX_RANDOM_TRANSLATION),
    numRandomStarts(DEF_NUM_RANDOM_STARTS), numSubTransforms(0),
    minimizer(std::bind(&FastGaussianShapeAlignment::calcAlignmentFunctionValue, this, std::placeholders::_1),
              std::bind(&FastGaussianShapeAlignment::calcAlignmentFunctionGradient, this, std::placeholders::_1, std::placeholders::_2))
{}

Shape::FastGaussianShapeAlignment::FastGaussianShapeAlignment(const GaussianShape& ref_shape):
    perfAlignment(true), optOverlap(true), greedyOpt(false), maxNumOptIters(DEF_MAX_OPTIMIZATION_ITERATIONS), 
    optStopGrad(DEF_OPTIMIZATION_STOP_GRADIENT), resultSelMode(DEF_RESULT_SELECTION_MODE), resultCmpFunc(&compareScore), 
    scoringFunc(&calcTotalOverlapTanimotoScore), currSetIndex(0), currShapeIndex(0),
    shapeCtrStarts(true), colCtrStarts(false), nonColCtrStarts(false), randomStarts(false),
    genForAlgdShape(false), genForRefShape(true), genForLargerShape(true),
    symThreshold(DEF_SYMMETRY_THRESHOLD), maxRandomTrans(DEF_MAX_RANDOM_TRANSLATION),
    numRandomStarts(DEF_NUM_RANDOM_STARTS), numSubTransforms(0),
    minimizer(std::bind(&FastGaussianShapeAlignment::calcAlignmentFunctionValue, this, std::placeholders::_1),
              std::bind(&FastGaussianShapeAlignment::calcAlignmentFunctionGradient, this, std::placeholders::_1, std::placeholders::_2))
{
    addReferenceShape(ref_shape);
}

Shape::FastGaussianShapeAlignment::FastGaussianShapeAlignment(const GaussianShapeSet& ref_shapes):
    perfAlignment(true), optOverlap(true), greedyOpt(false), maxNumOptIters(DEF_MAX_OPTIMIZATION_ITERATIONS), 
    optStopGrad(DEF_OPTIMIZATION_STOP_GRADIENT), resultSelMode(DEF_RESULT_SELECTION_MODE), resultCmpFunc(&compareScore), 
    scoringFunc(&calcTotalOverlapTanimotoScore), currSetIndex(0), currShapeIndex(0),
    shapeCtrStarts(true), colCtrStarts(false), nonColCtrStarts(false), randomStarts(false),
    genForAlgdShape(false), genForRefShape(true), genForLargerShape(true),
    symThreshold(DEF_SYMMETRY_THRESHOLD), maxRandomTrans(DEF_MAX_RANDOM_TRANSLATION),
    numRandomStarts(DEF_NUM_RANDOM_STARTS), numSubTransforms(0),
    minimizer(std::bind(&FastGaussianShapeAlignment::calcAlignmentFunctionValue, this, std::placeholders::_1),
              std::bind(&FastGaussianShapeAlignment::calcAlignmentFunctionGradient, this, std::placeholders::_1, std::placeholders::_2))
{
    addReferenceShapes(ref_shapes);
}

Shape::FastGaussianShapeAlignment::~FastGaussianShapeAlignment() 
{}

void Shape::FastGaussianShapeAlignment::setResultCompareFunction(const ResultCompareFunction& func)
{
    if (!func)
        resultCmpFunc = &compareScore;
    else
        resultCmpFunc = func;
}

const Shape::FastGaussianShapeAlignment::ResultCompareFunction& Shape::FastGaussianShapeAlignment::getResultCompareFunction() const
{
    return resultCmpFunc;
}

void Shape::FastGaussianShapeAlignment::setScoringFunction(const ScoringFunction& func)
{
    if (!func)
        scoringFunc = &calcTotalOverlapTanimotoScore;
    else
        scoringFunc = func;
}

const Shape::FastGaussianShapeAlignment::ScoringFunction& Shape::FastGaussianShapeAlignment::getScoringFunction() const
{
    return scoringFunc;
}

void Shape::FastGaussianShapeAlignment::setResultSelectionMode(unsigned int mode)
{
    resultSelMode = mode;
}

unsigned int Shape::FastGaussianShapeAlignment::getResultSelectionMode() const
{
    return resultSelMode;
}

void Shape::FastGaussianShapeAlignment::performAlignment(bool perf_align)
{
    perfAlignment = perf_align;
}

bool Shape::FastGaussianShapeAlignment::performAlignment() const
{
    return perfAlignment;
}

void Shape::FastGaussianShapeAlignment::optimizeOverlap(bool optimize)
{
    optOverlap = optimize;
}

bool Shape::FastGaussianShapeAlignment::optimizeOverlap() const
{
    return optOverlap;
}

void Shape::FastGaussianShapeAlignment::greedyOptimization(bool greedy)
{
    greedyOpt = greedy;
}

bool Shape::FastGaussianShapeAlignment::greedyOptimization() const
{
    return greedyOpt;
}

void Shape::FastGaussianShapeAlignment::setMaxNumOptimizationIterations(std::size_t max_iter)
{
    maxNumOptIters = max_iter;
}

std::size_t Shape::FastGaussianShapeAlignment::getMaxNumOptimizationIterations() const
{
    return maxNumOptIters;
}

void Shape::FastGaussianShapeAlignment::setOptimizationStopGradient(double grad_norm)
{
    optStopGrad = grad_norm;
}

double Shape::FastGaussianShapeAlignment::getOptimizationStopGradient() const
{
    return optStopGrad;
}

void Shape::FastGaussianShapeAlignment::clearReferenceShapes()
{
    refShapeData.clear();

    currSetIndex = 0;
    currShapeIndex = 0;
}

void Shape::FastGaussianShapeAlignment::addReferenceShape(const GaussianShape& shape, bool new_set)
{
    std::size_t num_ref_shapes = refShapeData.size();
    
    if (new_set) {
        if (num_ref_shapes > 0)
            currSetIndex++;

        currShapeIndex = 0;
    }

    refShapeData.resize(num_ref_shapes + 1);

    setupShapeData(shape, refShapeData[num_ref_shapes], true);
}

void Shape::FastGaussianShapeAlignment::addReferenceShapes(const GaussianShapeSet& shapes, bool new_set)
{
    std::size_t num_ref_shapes = refShapeData.size();
    std::size_t num_new_ref_shapes = shapes.getSize();
    
    if (new_set) {
        if (num_ref_shapes > 0)
            currSetIndex++;

        currShapeIndex = 0;
    }

    refShapeData.resize(num_ref_shapes + num_new_ref_shapes);

    for (std::size_t i = 0; i < num_new_ref_shapes; i++)
        setupShapeData(shapes.getElement(i), refShapeData[num_ref_shapes + i], true);
}

std::size_t Shape::FastGaussianShapeAlignment::getNumReferenceShapes() const
{
    return refShapeData.size();
}

void Shape::FastGaussianShapeAlignment::genShapeCenterStarts(bool generate)
{
    shapeCtrStarts = generate;
}

bool Shape::FastGaussianShapeAlignment::genShapeCenterStarts() const
{
    return shapeCtrStarts;
}
            
void Shape::FastGaussianShapeAlignment::genColorCenterStarts(bool generate)
{
    colCtrStarts = generate;
}

bool Shape::FastGaussianShapeAlignment::genColorCenterStarts() const
{
    return colCtrStarts;
}

void Shape::FastGaussianShapeAlignment::genNonColorCenterStarts(bool generate)
{
    nonColCtrStarts = generate;
}

bool Shape::FastGaussianShapeAlignment::genNonColorCenterStarts() const
{
    return nonColCtrStarts;
}
            
void Shape::FastGaussianShapeAlignment::genRandomStarts(bool generate)
{
    randomStarts = generate;
}

bool Shape::FastGaussianShapeAlignment::genRandomStarts() const
{
    return randomStarts;
}

void Shape::FastGaussianShapeAlignment::genForAlignedShapeCenters(bool generate)
{
    genForAlgdShape = generate;
}

bool Shape::FastGaussianShapeAlignment::genForAlignedShapeCenters() const
{
    return genForAlgdShape;
}

void Shape::FastGaussianShapeAlignment::genForReferenceShapeCenters(bool generate)
{
    genForRefShape = generate;
}

bool Shape::FastGaussianShapeAlignment::genForReferenceShapeCenters() const
{
    return genForRefShape;
}

void Shape::FastGaussianShapeAlignment::genForLargerShapeCenters(bool generate)
{
    genForLargerShape = generate;
}

bool Shape::FastGaussianShapeAlignment::genForLargerShapeCenters() const
{
    return genForLargerShape;
}

void Shape::FastGaussianShapeAlignment::setSymmetryThreshold(double thresh)
{
    symThreshold = thresh;
}

double Shape::FastGaussianShapeAlignment::getSymmetryThreshold()
{
    return symThreshold;
}

void Shape::FastGaussianShapeAlignment::setMaxRandomTranslation(double max_trans)
{
    maxRandomTrans = max_trans;
}

double Shape::FastGaussianShapeAlignment::getMaxRandomTranslation() const
{
    return maxRandomTrans;
}

void Shape::FastGaussianShapeAlignment::setNumRandomStarts(std::size_t num_starts)
{
    numRandomStarts = num_starts;
}

std::size_t Shape::FastGaussianShapeAlignment::getNumRandomStarts() const
{
    return numRandomStarts;
}

void Shape::FastGaussianShapeAlignment::setRandomSeed(unsigned int seed)
{
    randomEngine.seed(seed);
}

bool Shape::FastGaussianShapeAlignment::align(const GaussianShape& shape)
{
    if (shape.getNumElements() == 0)
        return false;

    results.clear();
    resIndexMap.clear();

    setupShapeData(shape, algdShapeData, false);
    prepareForAlignment();
    
    for (std::size_t i = 0, num_ref_shapes = refShapeData.size(); i < num_ref_shapes; i++)
        alignAndProcessResults(i, 0);

    return !results.empty();
}

bool Shape::FastGaussianShapeAlignment::align(const GaussianShapeSet& shapes)
{
    results.clear();
    resIndexMap.clear();

    for (std::size_t i = 0, num_algd_shapes = shapes.getSize(), num_ref_shapes = refShapeData.size(); i < num_algd_shapes; i++) {
        if (shapes.getElement(i).getNumElements() == 0)
            continue;

        setupShapeData(shapes.getElement(i), algdShapeData, false);
        prepareForAlignment();
        
        for (std::size_t j = 0; j < num_ref_shapes; j++)
            alignAndProcessResults(j, i);
    }

    return !results.empty();
}

std::size_t Shape::FastGaussianShapeAlignment::getNumResults() const
{
    return results.size();
}

const Shape::AlignmentResult& Shape::FastGaussianShapeAlignment::getResult(std::size_t idx) const
{
    if (idx >= results.size())
        throw Base::IndexError("FastGaussianShapeAlignment: result index out of bounds");

    return results[idx];
}

Shape::AlignmentResult& Shape::FastGaussianShapeAlignment::getResult(std::size_t idx)
{
    if (idx >= results.size())
        throw Base::IndexError("FastGaussianShapeAlignment: result index out of bounds");

    return results[idx];
}

Shape::FastGaussianShapeAlignment::ConstResultIterator Shape::FastGaussianShapeAlignment::getResultsBegin() const
{
    return results.begin();
}

Shape::FastGaussianShapeAlignment::ConstResultIterator Shape::FastGaussianShapeAlignment::getResultsEnd() const
{
    return results.end();
}

Shape::FastGaussianShapeAlignment::ResultIterator Shape::FastGaussianShapeAlignment::getResultsBegin()
{
    return results.begin();
}

Shape::FastGaussianShapeAlignment::ResultIterator Shape::FastGaussianShapeAlignment::getResultsEnd()
{
    return results.end();
}

Shape::FastGaussianShapeAlignment::ConstResultIterator Shape::FastGaussianShapeAlignment::begin() const
{
    return results.begin();
}

Shape::FastGaussianShapeAlignment::ConstResultIterator Shape::FastGaussianShapeAlignment::end() const
{
    return results.end();
}

Shape::FastGaussianShapeAlignment::ResultIterator Shape::FastGaussianShapeAlignment::begin()
{
    return results.begin();
}

Shape::FastGaussianShapeAlignment::ResultIterator Shape::FastGaussianShapeAlignment::end()
{
    return results.end();
}

void Shape::FastGaussianShapeAlignment::alignAndProcessResults(std::size_t ref_idx, std::size_t al_idx)
{
    const ShapeData& ref_data = refShapeData[ref_idx];

    if (ref_data.elements.empty())
        return;
    
    AlignmentResult curr_res;

    if (!perfAlignment) {
        curr_res.setOverlap(calcOverlap(ref_data, algdShapeData, false));
        curr_res.setColorOverlap(calcOverlap(ref_data, algdShapeData, true));

        processResult(curr_res, ref_idx, al_idx);
        return;
    }

    if (!generateStartTransforms(ref_data))
        return;

    currRefShapeIdx = ref_idx;

    QuaternionTransformation opt_xform;
    QuaternionTransformation opt_xform_grad;

    for (std::size_t i = 0, num_starts = startTransforms.size(); i < num_starts; ) {
        if (optOverlap && greedyOpt) {
            std::size_t best_start_xform = 0;
            double highest_ovlp = 0.0;
            
            for (std::size_t j = 0; j < numSubTransforms && i < num_starts; j++, i++) {
                quaternionToMatrix(startTransforms[i], xformMatrix);
                transformAlignedShape();

                double overlap = calcOverlap(ref_data, algdShapeData, false);

                if (j == 0 || overlap > highest_ovlp) {
                    best_start_xform = i;
                    highest_ovlp = overlap;
                }
            }

            opt_xform = startTransforms[best_start_xform];

            minimizer.setup(opt_xform, opt_xform_grad, BFGS_MINIMIZER_STEP_SIZE, BFGS_MINIMIZER_TOLERANCE);
            minimizer.minimize(opt_xform, opt_xform_grad, maxNumOptIters, optStopGrad, -1.0, false);
        
            if (!std::isfinite(minimizer.getFunctionValue())) // sanity check 
                continue;

            normalize(opt_xform);
            quaternionToMatrix(opt_xform, xformMatrix);
            transformAlignedShape();

            curr_res.setOverlap(calcOverlap(ref_data, algdShapeData, false));
            curr_res.setColorOverlap(calcOverlap(ref_data, algdShapeData, true));

            processResult(curr_res, ref_idx, al_idx);
            continue;
        }

        bool have_sol = false;

        for (std::size_t j = 0; j < numSubTransforms && i < num_starts; j++, i++) {
            if (!optOverlap) {
                quaternionToMatrix(startTransforms[i], xformMatrix);

            } else {
                opt_xform = startTransforms[i];

                minimizer.setup(opt_xform, opt_xform_grad, BFGS_MINIMIZER_STEP_SIZE, BFGS_MINIMIZER_TOLERANCE);
                minimizer.minimize(opt_xform, opt_xform_grad, maxNumOptIters, optStopGrad, -1.0, false);
        
                if (!std::isfinite(minimizer.getFunctionValue()))  // sanity check
                    continue;

                normalize(opt_xform);
                quaternionToMatrix(opt_xform, xformMatrix);
            }

            transformAlignedShape();

            double overlap = calcOverlap(ref_data, algdShapeData, false);

            if (!have_sol || overlap > curr_res.getOverlap()) {
                curr_res.setOverlap(overlap);
                curr_res.setColorOverlap(calcOverlap(ref_data, algdShapeData, true));
                curr_res.setTransform(xformMatrix);

                have_sol = true;
            }
        }

        if (have_sol) {
            xformMatrix = curr_res.getTransform();
            processResult(curr_res, ref_idx, al_idx);
        }
    }
}

void Shape::FastGaussianShapeAlignment::processResult(AlignmentResult& res, std::size_t ref_idx, std::size_t al_idx)
{
    using namespace AlignmentResultSelectionMode;

    res.setReferenceSelfOverlap(refShapeData[ref_idx].selfOverlap);
    res.setReferenceColorSelfOverlap(refShapeData[ref_idx].colSelfOverlap);
    res.setAlignedSelfOverlap(algdShapeData.selfOverlap);
    res.setAlignedColorSelfOverlap(algdShapeData.colSelfOverlap);
    res.setScore(scoringFunc(res));

    std::size_t out_res_idx = 0;

    switch (resultSelMode) {

        case ALL:
            out_res_idx = results.size();
            results.resize(out_res_idx + 1);
            break;

        case BEST_PER_SHAPE_COMBINATION:
            if (getResultIndex(ResultID(ref_idx, al_idx), out_res_idx))
                break;

            if (resultCmpFunc(res, results[out_res_idx]))
                break;

            return;

        case BEST_PER_REFERENCE_SHAPE:
            if (getResultIndex(ResultID(ref_idx, 0), out_res_idx))
                break;

            if (resultCmpFunc(res, results[out_res_idx]))
                break;

            return;

        case BEST_PER_REFERENCE_SET:
            if (getResultIndex(ResultID(refShapeData[ref_idx].setIndex, 0), out_res_idx))
                break;

            if (resultCmpFunc(res, results[out_res_idx]))
                break;

            return;

        case BEST_OVERALL:
            if (results.empty()) {
                results.resize(1);
                break;
            } 

            if (resultCmpFunc(res, results[0]))
                break;

        default:
            return;
    }

    if (perfAlignment) {
        Math::Matrix4D tmp(prod(refShapeData[ref_idx].transform, xformMatrix));
        res.setTransform(prod(tmp, algdShapeData.transform));

    } else
        res.setTransform(Math::IdentityMatrix<double>(4, 4));

    res.setReferenceShapeSetIndex(refShapeData[ref_idx].setIndex);
    res.setReferenceShapeIndex(refShapeData[ref_idx].index);
    res.setAlignedShapeIndex(al_idx);

    results[out_res_idx] = res;
}

void Shape::FastGaussianShapeAlignment::setupShapeData(const GaussianShape& shape, ShapeData& data, bool ref)
{
    std::size_t num_elem = shape.getNumElements();

    data.elements.resize(num_elem);
    data.colElemOffs = 0;
    data.equalNonColDelta = true;

    if (ref) {
        data.setIndex = currSetIndex;
        data.index = currShapeIndex++;
    }

    for (std::size_t i = 0; i < num_elem; i++) {
        const GaussianShape::Element& gs_elem = shape.getElement(i);

        if (gs_elem.getColor() > 0)
            continue;

        setupShapeDataElement(gs_elem, data.elements[data.colElemOffs]);

        if (data.equalNonColDelta && data.colElemOffs > 0) 
            data.equalNonColDelta = (data.elements[data.colElemOffs].delta == data.elements[data.colElemOffs - 1].delta);

        data.colElemOffs++;
    }

    for (std::size_t i = 0, j = data.colElemOffs; i < num_elem; i++) {
        const GaussianShape::Element& gs_elem = shape.getElement(i);

        if (gs_elem.getColor() == 0)
            continue;

        setupShapeDataElement(gs_elem, data.elements[j++]);
    }

    data.selfOverlap = calcOverlap(data, data, false);
    data.colSelfOverlap = calcOverlap(data, data, true);

    if (!perfAlignment) 
        return;

    Math::Vector3D shape_ctr;
    Math::Vector3D::Pointer shape_ctr_data = shape_ctr.getData();
    double shape_vol = 0.0;

    for (std::size_t i = 0; i < num_elem; i++) {
        const ShapeData::Element& elem = data.elements[i];
        Math::Vector3D::ConstPointer elem_ctr = elem.center.getData();

        shape_ctr_data[0] += elem.volume * elem_ctr[0];
        shape_ctr_data[1] += elem.volume * elem_ctr[1];
        shape_ctr_data[2] += elem.volume * elem_ctr[2];

        shape_vol += elem.volume;
    }

    shape_ctr /= shape_vol;

    Math::Matrix3D quad_tensor;
    Math::Matrix3D::ArrayPointer tensor_data = quad_tensor.getData();

    for (std::size_t i = 0; i < num_elem; i++) {
        const ShapeData::Element& elem = data.elements[i];
        Math::Vector3D::ConstPointer elem_ctr = elem.center.getData();

        double diag_const = 1.0 / (2.0 * elem.delta);
        double trans_elem_ctr[3] = { elem_ctr[0] - shape_ctr_data[0], elem_ctr[1] - shape_ctr_data[1], elem_ctr[2] - shape_ctr_data[2] };

        tensor_data[0][1] += trans_elem_ctr[0] * trans_elem_ctr[1] * elem.volume;
        tensor_data[0][2] += trans_elem_ctr[0] * trans_elem_ctr[2] * elem.volume;
        tensor_data[1][2] += trans_elem_ctr[1] * trans_elem_ctr[2] * elem.volume;

        tensor_data[0][0] += (trans_elem_ctr[0] * trans_elem_ctr[0] + diag_const) * elem.volume;
        tensor_data[1][1] += (trans_elem_ctr[1] * trans_elem_ctr[1] + diag_const) * elem.volume;
        tensor_data[2][2] += (trans_elem_ctr[2] * trans_elem_ctr[2] + diag_const) * elem.volume;
    }

    tensor_data[1][0] = tensor_data[0][1];
    tensor_data[2][0] = tensor_data[0][2];
    tensor_data[2][1] = tensor_data[1][2];

    quad_tensor /= shape_vol;

    Math::Matrix3D eigen_vecs;
    Math::Vector3D x_axis, y_axis, z_axis, moments;
    Math::Vector3D::Pointer moments_data = moments.getData();
    
    jacobiDiagonalize(quad_tensor, moments, eigen_vecs);

    std::pair<double, int> ordered_moments[3] = {
        std::make_pair(moments_data[0], 0),
        std::make_pair(moments_data[1], 1),
        std::make_pair(moments_data[2], 2)
    };

    std::sort(ordered_moments, ordered_moments + 3);

    moments_data[0] = ordered_moments[2].first;
    moments_data[1] = ordered_moments[1].first;
    moments_data[2] = ordered_moments[0].first;
    
    x_axis.assign(column(eigen_vecs, ordered_moments[2].second));
    y_axis.assign(column(eigen_vecs, ordered_moments[1].second));
    z_axis.assign(crossProd(x_axis, y_axis));
    y_axis.assign(crossProd(z_axis, x_axis));

    x_axis /= length(x_axis);
    y_axis /= length(y_axis);
    z_axis /= length(z_axis);
    
    Math::Matrix4D::ArrayPointer xform_data = data.transform.getData();

    xform_data[0][0] = x_axis(0);
    xform_data[0][1] = x_axis(1);
    xform_data[0][2] = x_axis(2);
    xform_data[0][3] = 0.0;
    
    xform_data[1][0] = y_axis(0);
    xform_data[1][1] = y_axis(1);
    xform_data[1][2] = y_axis(2);
    xform_data[1][3] = 0.0;
    
    xform_data[2][0] = z_axis(0);
    xform_data[2][1] = z_axis(1);
    xform_data[2][2] = z_axis(2);
    xform_data[2][3] = 0.0;

    xform_data[3][0] = 0.0;
    xform_data[3][1] = 0.0;
    xform_data[3][2] = 0.0;
    xform_data[3][3] = 1.0;

    data.transform = data.transform * Math::TranslationMatrix<double>(4, -shape_ctr_data[0], -shape_ctr_data[1], -shape_ctr_data[2]);
    
    Math::Vector3D tmp_vec;
    Math::Vector3D::Pointer tmp_vec_data = tmp_vec.getData();

    for (std::size_t i = 0; i < num_elem; i++) {
        ShapeData::Element& elem = data.elements[i];

        transform(tmp_vec_data, xform_data, elem.center.getData());

        elem.center = tmp_vec;
    }
    
    if (ref) {
        xform_data[0][0] = x_axis(0);
        xform_data[1][0] = x_axis(1);
        xform_data[2][0] = x_axis(2);
    
        xform_data[0][1] = y_axis(0);
        xform_data[1][1] = y_axis(1);
        xform_data[2][1] = y_axis(2);
    
        xform_data[0][2] = z_axis(0);
        xform_data[1][2] = z_axis(1);
        xform_data[2][2] = z_axis(2);

        xform_data[0][3] = shape_ctr_data[0];
        xform_data[1][3] = shape_ctr_data[1];
        xform_data[2][3] = shape_ctr_data[2];

        xform_data[3][0] = 0.0;
        xform_data[3][1] = 0.0;
        xform_data[3][2] = 0.0;
        xform_data[3][3] = 1.0;
    }

    data.symClass = perceiveSymmetryClass(moments, symThreshold);    
}

void Shape::FastGaussianShapeAlignment::setupShapeDataElement(const GaussianShape::Element& gs_elem, ShapeData::Element& sd_elem) const
{
    sd_elem.center = gs_elem.getPosition();
    sd_elem.color = gs_elem.getColor();
    sd_elem.weightFactor = gs_elem.getHardness();
    sd_elem.radius = gs_elem.getRadius();

    double lambda = 4.0 * M_PI / (3.0 * sd_elem.weightFactor);

    sd_elem.delta = (M_PI / std::pow(lambda, 2.0 / 3.0)) / (sd_elem.radius * sd_elem.radius);

    double vol_factor = M_PI / sd_elem.delta;

    sd_elem.volume = sd_elem.weightFactor * vol_factor * std::sqrt(vol_factor);
}

void Shape::FastGaussianShapeAlignment::prepareForAlignment()
{
    startPoseCoords.resize(algdShapeData.elements.size());
    optPoseCoordsGrad.resize(startPoseCoords.getSize());

    for (std::size_t i = 0, num_algd_elem = startPoseCoords.size(); i < num_algd_elem; i++)
        startPoseCoords[i] = algdShapeData.elements[i].center;
}

bool Shape::FastGaussianShapeAlignment::generateStartTransforms(const ShapeData& ref_data)
{
    unsigned int axes_swap_flags = getAxesSwapFlags(ref_data.symClass) | getAxesSwapFlags(algdShapeData.symClass);

    startTransforms.clear();
    numSubTransforms = 4;
    
    if (axes_swap_flags & 0b01) 
        numSubTransforms += 4;
                
    if (axes_swap_flags & 0b10) 
        numSubTransforms += 4;
    
    if (axes_swap_flags == 0b11)
        numSubTransforms += 12;

    if (shapeCtrStarts)
        generateTransforms(Math::Vector3D(), axes_swap_flags);

    if (colCtrStarts | nonColCtrStarts) {
        if (genForLargerShape && !genForAlgdShape && !genForRefShape) {
            if (algdShapeData.elements.size() > ref_data.elements.size())
                generateTransformsForElementCenters(algdShapeData, axes_swap_flags, false);                
            else
                generateTransformsForElementCenters(ref_data, axes_swap_flags, true);

        } else if (genForLargerShape && !genForAlgdShape && genForRefShape) {
            if (algdShapeData.elements.size() > ref_data.elements.size()) {
                generateTransformsForElementCenters(algdShapeData, axes_swap_flags, false);                
                generateTransformsForElementCenters(ref_data, axes_swap_flags, true);                

            } else
                generateTransformsForElementCenters(ref_data, axes_swap_flags, true);

        }  else if (genForLargerShape && genForAlgdShape && !genForRefShape) {            
            if (algdShapeData.elements.size() > ref_data.elements.size()) 
                generateTransformsForElementCenters(algdShapeData, axes_swap_flags, false);                

            else {
                generateTransformsForElementCenters(algdShapeData, axes_swap_flags, false);                
                generateTransformsForElementCenters(ref_data, axes_swap_flags, true);
            }

        } else {
            if (genForAlgdShape)
                generateTransformsForElementCenters(algdShapeData, axes_swap_flags, false);                

            if (genForRefShape)
                generateTransformsForElementCenters(ref_data, axes_swap_flags, true);
        }
    }
    
    if (randomStarts) {
        boost::random::uniform_real_distribution<double> rand_dist(-maxRandomTrans, maxRandomTrans);

        for (std::size_t i = 0; i < numRandomStarts; i++)
            generateTransforms(Math::vec(rand_dist(randomEngine), rand_dist(randomEngine), rand_dist(randomEngine)), axes_swap_flags);
    }
        
    return !startTransforms.empty();
}

void Shape::FastGaussianShapeAlignment::generateTransformsForElementCenters(const ShapeData& data, unsigned int axes_swap_flags, bool ref_shape)
{
    if (colCtrStarts && nonColCtrStarts) {
        for (std::size_t i = 0, num_elem = data.elements.size(); i < num_elem; i++) {
            if (ref_shape)
                generateTransforms(data.elements[i].center, axes_swap_flags);
            else
                generateTransforms(-data.elements[i].center, axes_swap_flags);
        }

    } else if (nonColCtrStarts) {
        for (std::size_t i = 0, num_elem = data.colElemOffs; i < num_elem; i++) {
            if (ref_shape)
                generateTransforms(data.elements[i].center, axes_swap_flags);
            else
                generateTransforms(-data.elements[i].center, axes_swap_flags);
        }

    } else if (colCtrStarts) {
        for (std::size_t i = data.colElemOffs, num_elem = data.elements.size(); i < num_elem; i++)  {
            if (ref_shape)
                generateTransforms(data.elements[i].center, axes_swap_flags);
            else
                generateTransforms(-data.elements[i].center, axes_swap_flags);
        }
    }
}

void Shape::FastGaussianShapeAlignment::generateTransforms(const Math::Vector3D& ctr_trans, unsigned int axes_swap_flags)
{
    Math::Vector3D::ConstPointer ctr_trans_data = ctr_trans.getData();

    addStartTransform(ctr_trans_data, IDENTITY_ROT);
    addStartTransform(ctr_trans_data, X_180_ROT);
    addStartTransform(ctr_trans_data, Y_180_ROT);
    addStartTransform(ctr_trans_data, Z_180_ROT);

    if (axes_swap_flags & 0b01) {
        addStartTransform(ctr_trans_data, XY_SWAP_ROT);
        addStartTransform(ctr_trans_data, X_180_ROT * XY_SWAP_ROT);
        addStartTransform(ctr_trans_data, Y_180_ROT * XY_SWAP_ROT);
        addStartTransform(ctr_trans_data, Z_180_ROT * XY_SWAP_ROT);
    }
            
    if (axes_swap_flags & 0b10) {
        addStartTransform(ctr_trans_data, YZ_SWAP_ROT);
        addStartTransform(ctr_trans_data, X_180_ROT * YZ_SWAP_ROT);
        addStartTransform(ctr_trans_data, Y_180_ROT * YZ_SWAP_ROT);
        addStartTransform(ctr_trans_data, Z_180_ROT * YZ_SWAP_ROT);
    }

    if (axes_swap_flags == 0b11) {
        addStartTransform(ctr_trans_data, XZ_SWAP_ROT);
        addStartTransform(ctr_trans_data, X_180_ROT * XZ_SWAP_ROT);
        addStartTransform(ctr_trans_data, Y_180_ROT * XZ_SWAP_ROT);
        addStartTransform(ctr_trans_data, Z_180_ROT * XZ_SWAP_ROT);
        
        addStartTransform(ctr_trans_data, XYZ_SWAP_ROT1);
        addStartTransform(ctr_trans_data, X_180_ROT * XYZ_SWAP_ROT1);
        addStartTransform(ctr_trans_data, Y_180_ROT * XYZ_SWAP_ROT1);
        addStartTransform(ctr_trans_data, Z_180_ROT * XYZ_SWAP_ROT1);

        addStartTransform(ctr_trans_data, XYZ_SWAP_ROT2);
        addStartTransform(ctr_trans_data, X_180_ROT * XYZ_SWAP_ROT2);
        addStartTransform(ctr_trans_data, Y_180_ROT * XYZ_SWAP_ROT2);
        addStartTransform(ctr_trans_data, Z_180_ROT * XYZ_SWAP_ROT2);
    }
}

template <typename QE>
void Shape::FastGaussianShapeAlignment::addStartTransform(Math::Vector3D::ConstPointer ctr_trans_data, const Math::QuaternionExpression<QE>& rot_quat)
{
    QuaternionTransformation xform;
    QuaternionTransformation::Pointer xform_data = xform.getData();

    xform_data[0] = rot_quat().getC1();
    xform_data[1] = rot_quat().getC2();
    xform_data[2] = rot_quat().getC3();
    xform_data[3] = rot_quat().getC4();
    xform_data[4] = ctr_trans_data[0];
    xform_data[5] = ctr_trans_data[1];
    xform_data[6] = ctr_trans_data[2];

    startTransforms.push_back(xform);
}

void Shape::FastGaussianShapeAlignment::transformAlignedShape()
{
    for (std::size_t i = 0, num_elem = algdShapeData.elements.size(); i < num_elem; i++) 
        transform(algdShapeData.elements[i].center.getData(), xformMatrix.getData(), startPoseCoords[i].getData());
}

double Shape::FastGaussianShapeAlignment::calcAlignmentFunctionValue(const QuaternionTransformation& xform_quat)
{
    QuaternionTransformation::ConstPointer xform_quat_data = xform_quat.getData();
    QuaternionTransformation::Pointer norm_xform_quat_data = normXformQuat.getData();

    double quat_norm_sqrd = xform_quat_data[0] * xform_quat_data[0] + xform_quat_data[1] * xform_quat_data[1] + 
        xform_quat_data[2] * xform_quat_data[2] + xform_quat_data[3] * xform_quat_data[3];
    double quat_non_unity_pen = 1.0 - quat_norm_sqrd;

    quat_non_unity_pen *= 0.5 * QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR * quat_non_unity_pen;

    double inv_quat_norm = 1.0 / std::sqrt(quat_norm_sqrd);

    for (std::size_t i = 0; i < 4; i++)
        norm_xform_quat_data[i] = xform_quat_data[i] * inv_quat_norm;

    for (std::size_t i = 4; i < 7; i++)
        norm_xform_quat_data[i] = xform_quat_data[i];
        
    quaternionToMatrix(normXformQuat, xformMatrix);
    transformAlignedShape();

    return (quat_non_unity_pen - calcOverlap(refShapeData[currRefShapeIdx], algdShapeData, false));
}

double Shape::FastGaussianShapeAlignment::calcAlignmentFunctionGradient(const QuaternionTransformation& xform_quat, QuaternionTransformation& xform_grad)
{
    xform_grad.clear();

    QuaternionTransformation::ConstPointer xform_quat_data = xform_quat.getData();
    QuaternionTransformation::Pointer grad_data = xform_grad.getData();
    QuaternionTransformation::Pointer norm_xform_quat_data = normXformQuat.getData();
    Math::Matrix4D::ConstArrayPointer xform_mtx_data = xformMatrix.getData();

    double quat_norm_sqrd = xform_quat_data[0] * xform_quat_data[0] + xform_quat_data[1] * xform_quat_data[1] + 
        xform_quat_data[2] * xform_quat_data[2] + xform_quat_data[3] * xform_quat_data[3];
    double inv_quat_norm_sqrd = 1.0 / quat_norm_sqrd;
    double inv_quat_norm = std::sqrt(inv_quat_norm_sqrd);

    for (std::size_t i = 0; i < 4; i++)
        norm_xform_quat_data[i] = xform_quat_data[i] * inv_quat_norm;

    for (std::size_t i = 4; i < 7; i++)
        norm_xform_quat_data[i] = xform_quat_data[i];
        
    quaternionToMatrix(normXformQuat, xformMatrix);
    transformAlignedShape();

    double neg_overlap = -calcOverlapGradient(refShapeData[currRefShapeIdx], optPoseCoordsGrad);

    double dq1[3][3] = { { xform_quat_data[0], -xform_quat_data[3],  xform_quat_data[2] },
                         { xform_quat_data[3],  xform_quat_data[0], -xform_quat_data[1] },
                         {-xform_quat_data[2],  xform_quat_data[1],  xform_quat_data[0] } };

    double dq2[3][3] = { { xform_quat_data[1], -xform_quat_data[2],  xform_quat_data[3] },
                         { xform_quat_data[2], -xform_quat_data[1], -xform_quat_data[0] },
                         { xform_quat_data[3],  xform_quat_data[0], -xform_quat_data[1] } };

    double dq3[3][3] = { {-xform_quat_data[2],  xform_quat_data[1],  xform_quat_data[0] },
                         { xform_quat_data[1],  xform_quat_data[2],  xform_quat_data[3] },
                         {-xform_quat_data[0],  xform_quat_data[3], -xform_quat_data[2] } };

    double dq4[3][3] = { {-xform_quat_data[3], -xform_quat_data[0],  xform_quat_data[1] },
                         { xform_quat_data[0], -xform_quat_data[3],  xform_quat_data[2] },
                         { xform_quat_data[1],  xform_quat_data[2],  xform_quat_data[3] } };

    for (std::size_t i = 0; i < 3; i++)
        for (std::size_t j = 0; j < 3; j++) {
            dq1[i][j] = (dq1[i][j] - xform_mtx_data[i][j] * xform_quat_data[0]) * inv_quat_norm_sqrd;
            dq2[i][j] = (dq2[i][j] - xform_mtx_data[i][j] * xform_quat_data[1]) * inv_quat_norm_sqrd;
            dq3[i][j] = (dq3[i][j] - xform_mtx_data[i][j] * xform_quat_data[2]) * inv_quat_norm_sqrd;
            dq4[i][j] = (dq4[i][j] - xform_mtx_data[i][j] * xform_quat_data[3]) * inv_quat_norm_sqrd;
        }
    
    for (std::size_t i = 0, num_elem = startPoseCoords.getSize(); i < num_elem; i++) {
        const Math::Vector3D::ConstPointer elem_pos = startPoseCoords[i].getData();
        const Math::Vector3D::ConstPointer pos_grad = optPoseCoordsGrad[i].getData();
        
        grad_data[0] +=
            pos_grad[0] * ( dq1[0][0] * elem_pos[0] + dq1[0][1] * elem_pos[1] + dq1[0][2] * elem_pos[2]) +
            pos_grad[1] * ( dq1[1][0] * elem_pos[0] + dq1[1][1] * elem_pos[1] + dq1[1][2] * elem_pos[2]) +
            pos_grad[2] * ( dq1[2][0] * elem_pos[0] + dq1[2][1] * elem_pos[1] + dq1[2][2] * elem_pos[2]);

        grad_data[1] +=
            pos_grad[0] * ( dq2[0][0] * elem_pos[0] + dq2[0][1] * elem_pos[1] + dq2[0][2] * elem_pos[2]) +
            pos_grad[1] * ( dq2[1][0] * elem_pos[0] + dq2[1][1] * elem_pos[1] + dq2[1][2] * elem_pos[2]) +
            pos_grad[2] * ( dq2[2][0] * elem_pos[0] + dq2[2][1] * elem_pos[1] + dq2[2][2] * elem_pos[2]);

        grad_data[2] +=
            pos_grad[0] * ( dq3[0][0] * elem_pos[0] + dq3[0][1] * elem_pos[1] + dq3[0][2] * elem_pos[2]) +
            pos_grad[1] * ( dq3[1][0] * elem_pos[0] + dq3[1][1] * elem_pos[1] + dq3[1][2] * elem_pos[2]) +
            pos_grad[2] * ( dq3[2][0] * elem_pos[0] + dq3[2][1] * elem_pos[1] + dq3[2][2] * elem_pos[2]);

        grad_data[3] +=
            pos_grad[0] * ( dq4[0][0] * elem_pos[0] + dq4[0][1] * elem_pos[1] + dq4[0][2] * elem_pos[2]) +
            pos_grad[1] * ( dq4[1][0] * elem_pos[0] + dq4[1][1] * elem_pos[1] + dq4[1][2] * elem_pos[2]) +
            pos_grad[2] * ( dq4[2][0] * elem_pos[0] + dq4[2][1] * elem_pos[1] + dq4[2][2] * elem_pos[2]);

        grad_data[4] -= pos_grad[0];
        grad_data[5] -= pos_grad[1];
        grad_data[6] -= pos_grad[2];
    }
    
    double quat_non_unity_pen = 1.0 - quat_norm_sqrd;
    double pen_grad_factor = QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR * quat_non_unity_pen;

    for (std::size_t i = 0; i < 4; i++)
        grad_data[i] = -2.0 * (grad_data[i] + pen_grad_factor * xform_quat_data[i]);
    
    return (neg_overlap + 0.5 * pen_grad_factor * quat_non_unity_pen);
}

double Shape::FastGaussianShapeAlignment::calcOverlap(const ShapeData& ref_data, const ShapeData& ovl_data, bool color) const
{
    double overlap = 0.0;

    if (!color) {
        if (ref_data.equalNonColDelta && ovl_data.equalNonColDelta && ref_data.elements[0].delta == ovl_data.elements[0].delta) {

            double max_dist = ref_data.elements[0].radius * 2.0 * RADIUS_SCALING_FACTOR;
            double elem_delta = ref_data.elements[0].delta;
            double delta_fact =  elem_delta * 0.5;
            double delta = 2 * elem_delta;
            double vol_factor = M_PI / delta;

            vol_factor *= std::sqrt(vol_factor) * ref_data.elements[0].weightFactor * ref_data.elements[0].weightFactor;
            max_dist *= max_dist;

            for (std::size_t i = 0, num_ovl_elem = ovl_data.colElemOffs; i < num_ovl_elem; i++) {
                const ShapeData::Element& elem1 = ovl_data.elements[i];
                Math::Vector3D::ConstPointer elem1_ctr = elem1.center.getData();

                for (std::size_t j = 0, num_ref_elem = ref_data.colElemOffs; j < num_ref_elem; j++) {
                    const ShapeData::Element& elem2 = ref_data.elements[j];
                    double sqrd_ctr_dist = calcSquaredDistance(elem1_ctr, elem2.center.getData());

                    if (sqrd_ctr_dist > max_dist)
                        continue;

                    double prod_fact_exp = -delta_fact * sqrd_ctr_dist;

                    overlap += exp_func(prod_fact_exp);
                }
            }

            overlap *= vol_factor;

        } else {
            for (std::size_t i = 0, num_ovl_elem = ovl_data.colElemOffs; i < num_ovl_elem; i++) {
                const ShapeData::Element& elem1 = ovl_data.elements[i];
                Math::Vector3D::ConstPointer elem1_ctr = elem1.center.getData();

                for (std::size_t j = 0, num_ref_elem = ref_data.colElemOffs; j < num_ref_elem; j++) {
                    const ShapeData::Element& elem2 = ref_data.elements[j];
                    double sqrd_ctr_dist = calcSquaredDistance(elem1_ctr, elem2.center.getData());
                    double max_dist = (elem1.radius + elem2.radius) * RADIUS_SCALING_FACTOR;

                    if (sqrd_ctr_dist > (max_dist * max_dist))
                        continue;

                    double delta = elem1.delta + elem2.delta;
                    double vol_factor = M_PI / delta;
                    double prod_fact_exp = -elem1.delta * elem2.delta * sqrd_ctr_dist / delta;

                    overlap += elem1.weightFactor * elem2.weightFactor * vol_factor *
                        std::sqrt(vol_factor) * exp_func(prod_fact_exp);
                }
            }
        }
    }

    for (std::size_t i = ovl_data.colElemOffs, num_ovl_elem = ovl_data.elements.size(); i < num_ovl_elem; i++) {
        const ShapeData::Element& elem1 = ovl_data.elements[i];
        Math::Vector3D::ConstPointer elem1_ctr = elem1.center.getData();

        for (std::size_t j = ref_data.colElemOffs, num_ref_elem = ref_data.elements.size(); j < num_ref_elem; j++) {
            const ShapeData::Element& elem2 = ref_data.elements[j];

            if (elem1.color != elem2.color)
                continue;
        
            double sqrd_ctr_dist = calcSquaredDistance(elem1_ctr, elem2.center.getData());
            double max_dist = (elem1.radius + elem2.radius) * RADIUS_SCALING_FACTOR;

            if (sqrd_ctr_dist > (max_dist * max_dist))
                continue;

            double delta = elem1.delta + elem2.delta;
            double vol_factor = M_PI / delta;
            double prod_fact_exp = -elem1.delta * elem2.delta * sqrd_ctr_dist / delta;

            overlap += elem1.weightFactor * elem2.weightFactor * vol_factor *
                std::sqrt(vol_factor) * exp_func(prod_fact_exp);
        }
    }
        
    return overlap;
}

double Shape::FastGaussianShapeAlignment::calcOverlapGradient(const ShapeData& ref_data, Math::Vector3DArray& grad) const
{
    Math::Vector3DArray::StorageType& grad_data = grad.getData();
    Math::Vector3D inters_prod_ctr;
    Math::Vector3D::Pointer inters_prod_ctr_data = inters_prod_ctr.getData();
    double overlap = 0.0;

    if (ref_data.equalNonColDelta && algdShapeData.equalNonColDelta && ref_data.elements[0].delta == algdShapeData.elements[0].delta) {
        double max_dist = ref_data.elements[0].radius * 2.0 * RADIUS_SCALING_FACTOR;
        double elem_delta = ref_data.elements[0].delta;
        double delta_fact =  elem_delta * 0.5;
        double vol_factor = M_PI * 0.5 / elem_delta;

        vol_factor *= std::sqrt(vol_factor) * ref_data.elements[0].weightFactor * ref_data.elements[0].weightFactor;
        max_dist *= max_dist;

        double grad_fact = -elem_delta * vol_factor;

        for (std::size_t i = 0, num_ovl_elem = algdShapeData.colElemOffs; i < num_ovl_elem; i++) {
            const ShapeData::Element& elem1 = algdShapeData.elements[i];
            Math::Vector3D::ConstPointer elem1_ctr = elem1.center.getData();
            Math::Vector3D::Pointer elem1_grad = grad_data[i].getData();

            elem1_grad[0] = 0.0;
            elem1_grad[1] = 0.0;
            elem1_grad[2] = 0.0;

            for (std::size_t j = 0, num_ref_elem = ref_data.colElemOffs; j < num_ref_elem; j++) {
                const ShapeData::Element& elem2 = ref_data.elements[j];
                Math::Vector3D::ConstPointer elem2_ctr = elem2.center.getData();
                double sqrd_ctr_dist = calcSquaredDistance(elem1_ctr, elem2_ctr);

                if (sqrd_ctr_dist > max_dist)
                    continue;

                double prod_fact_exp = -delta_fact * sqrd_ctr_dist;
                double overlap_contrib = exp_func(prod_fact_exp);

                overlap += overlap_contrib;
    
                elem1_grad[0] += overlap_contrib * (elem1_ctr[0] - elem2_ctr[0]);
                elem1_grad[1] += overlap_contrib * (elem1_ctr[1] - elem2_ctr[1]);
                elem1_grad[2] += overlap_contrib * (elem1_ctr[2] - elem2_ctr[2]);
            }

            elem1_grad[0] *= grad_fact;
            elem1_grad[1] *= grad_fact;
            elem1_grad[2] *= grad_fact;
        }

        overlap *= vol_factor;

    } else {
        for (std::size_t i = 0, num_ovl_elem = algdShapeData.colElemOffs; i < num_ovl_elem; i++) {
            const ShapeData::Element& elem1 = algdShapeData.elements[i];
            Math::Vector3D::ConstPointer elem1_ctr = elem1.center.getData();
            Math::Vector3D::Pointer elem1_grad = grad_data[i].getData();

            elem1_grad[0] = 0.0;
            elem1_grad[1] = 0.0;
            elem1_grad[2] = 0.0;

            for (std::size_t j = 0, num_ref_elem = ref_data.colElemOffs; j < num_ref_elem; j++) {
                const ShapeData::Element& elem2 = ref_data.elements[j];
                Math::Vector3D::ConstPointer elem2_ctr = elem2.center.getData();
                double sqrd_ctr_dist = calcSquaredDistance(elem1_ctr, elem2_ctr);
                double max_dist = (elem1.radius + elem2.radius) * RADIUS_SCALING_FACTOR;

                if (sqrd_ctr_dist > (max_dist * max_dist))
                    continue;

                double delta = elem1.delta + elem2.delta;
                double vol_factor = M_PI / delta;
                double prod_fact_exp = -elem1.delta * elem2.delta * sqrd_ctr_dist / delta;
                double overlap_contrib = elem1.weightFactor * elem2.weightFactor * vol_factor *
                    std::sqrt(vol_factor) * exp_func(prod_fact_exp);

                overlap += overlap_contrib;

                inters_prod_ctr_data[0] = (elem1_ctr[0] * elem1.delta + elem2_ctr[0] * elem2.delta) / delta;
                inters_prod_ctr_data[1] = (elem1_ctr[1] * elem1.delta + elem2_ctr[1] * elem2.delta) / delta;
                inters_prod_ctr_data[2] = (elem1_ctr[2] * elem1.delta + elem2_ctr[2] * elem2.delta) / delta;
            
                double grad_factor = -elem1.delta * 2.0 * overlap_contrib;
            
                elem1_grad[0] += grad_factor * (elem1_ctr[0] - inters_prod_ctr_data[0]);
                elem1_grad[1] += grad_factor * (elem1_ctr[1] - inters_prod_ctr_data[1]);
                elem1_grad[2] += grad_factor * (elem1_ctr[2] - inters_prod_ctr_data[2]);
            }
        }
    }

    for (std::size_t i = algdShapeData.colElemOffs, num_ovl_elem = algdShapeData.elements.size(); i < num_ovl_elem; i++) {
        const ShapeData::Element& elem1 = algdShapeData.elements[i];
        Math::Vector3D::ConstPointer elem1_ctr = elem1.center.getData();
        Math::Vector3D::Pointer elem1_grad = grad_data[i].getData();

        elem1_grad[0] = 0.0;
        elem1_grad[1] = 0.0;
        elem1_grad[2] = 0.0;

        for (std::size_t j = ref_data.colElemOffs, num_ref_elem = ref_data.elements.size(); j < num_ref_elem; j++) {
            const ShapeData::Element& elem2 = ref_data.elements[j];

            if (elem2.color != elem1.color)
                continue;
    
            Math::Vector3D::ConstPointer elem2_ctr = elem2.center.getData();
            double sqrd_ctr_dist = calcSquaredDistance(elem1_ctr, elem2_ctr);
            double max_dist = (elem1.radius + elem2.radius) * RADIUS_SCALING_FACTOR;

            if (sqrd_ctr_dist > (max_dist * max_dist))
                continue;

            double delta = elem1.delta + elem2.delta;
            double vol_factor = M_PI / delta;
            double prod_fact_exp = -elem1.delta * elem2.delta * sqrd_ctr_dist / delta;
            double overlap_contrib = elem1.weightFactor * elem2.weightFactor * vol_factor *
                std::sqrt(vol_factor) * exp_func(prod_fact_exp);

            overlap += overlap_contrib;

            inters_prod_ctr_data[0] = (elem1_ctr[0] * elem1.delta + elem2_ctr[0] * elem2.delta) / delta;
            inters_prod_ctr_data[1] = (elem1_ctr[1] * elem1.delta + elem2_ctr[1] * elem2.delta) / delta;
            inters_prod_ctr_data[2] = (elem1_ctr[2] * elem1.delta + elem2_ctr[2] * elem2.delta) / delta;

            double grad_factor = -elem1.delta * 2.0 * overlap_contrib;
            
            elem1_grad[0] += grad_factor * (elem1_ctr[0] - inters_prod_ctr_data[0]);
            elem1_grad[1] += grad_factor * (elem1_ctr[1] - inters_prod_ctr_data[1]);
            elem1_grad[2] += grad_factor * (elem1_ctr[2] - inters_prod_ctr_data[2]);
        }
    }
    
    return overlap;
}

bool Shape::FastGaussianShapeAlignment::getResultIndex(const ResultID& res_id, std::size_t& res_idx)
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

#pragma GCC diagnostic pop
