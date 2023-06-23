/* 
 * ScoringFunctions.cpp 
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

#include "CDPL/Shape/ScoringFunctions.hpp"
#include "CDPL/Shape/AlignmentResult.hpp"


using namespace CDPL;


double Shape::calcTotalOverlapTanimotoScore(const AlignmentResult& res)
{
    return (res.getOverlap() / (res.getReferenceSelfOverlap() + res.getAlignedSelfOverlap() - res.getOverlap()));
}

double Shape::calcColorTanimotoScore(const AlignmentResult& res)
{
	double denom = res.getReferenceColorSelfOverlap() + res.getAlignedColorSelfOverlap() - res.getColorOverlap();

	if (denom == 0.0)
		return 0.0;

    return (res.getColorOverlap() / denom);
}

double Shape::calcShapeTanimotoScore(const AlignmentResult& res)
{
    double shape_ovlp = res.getOverlap() - res.getColorOverlap();
    double ref_shape_self_ovlp = res.getReferenceSelfOverlap() - res.getReferenceColorSelfOverlap();
    double al_shape_self_ovlp = res.getAlignedSelfOverlap() - res.getAlignedColorSelfOverlap();
	double denom = ref_shape_self_ovlp + al_shape_self_ovlp - shape_ovlp;

	if (denom == 0.0)
		return 0.0;

    return (shape_ovlp / denom);
}

double Shape::calcTanimotoComboScore(const AlignmentResult& res)
{
	return (calcShapeTanimotoScore(res) + calcColorTanimotoScore(res));
}

double Shape::calcTotalOverlapTverskyScore(const AlignmentResult& res, double alpha, double beta)
{
	double denom = res.getReferenceSelfOverlap() * alpha + res.getAlignedSelfOverlap() * beta;

	if (denom == 0.0)
		return 0.0;

	return (res.getOverlap() / denom);
}

double Shape::calcShapeTverskyScore(const AlignmentResult& res, double alpha, double beta)
{
	double shape_ovlp = res.getOverlap() - res.getColorOverlap();
    double ref_shape_self_ovlp = res.getReferenceSelfOverlap() - res.getReferenceColorSelfOverlap();
    double al_shape_self_ovlp = res.getAlignedSelfOverlap() - res.getAlignedColorSelfOverlap();
	double denom = ref_shape_self_ovlp * alpha + al_shape_self_ovlp * beta;

	if (denom == 0.0)
		return 0.0;

    return (shape_ovlp / denom);
}

double Shape::calcColorTverskyScore(const AlignmentResult& res, double alpha, double beta)
{
	double denom = res.getReferenceColorSelfOverlap() * alpha + res.getAlignedColorSelfOverlap() * beta;

	if (denom == 0.0)
		return 0.0;

    return (res.getColorOverlap() / denom);
}

double Shape::calcTverskyComboScore(const AlignmentResult& res, double alpha, double beta)
{
	return (calcShapeTverskyScore(res, alpha, beta) + calcColorTverskyScore(res, alpha, beta));
}

double Shape::calcReferenceTotalOverlapTverskyScore(const AlignmentResult& res, double alpha)
{
	double denom = res.getReferenceSelfOverlap() * alpha;

	if (denom == 0.0)
		return 0.0;

	return (res.getOverlap() / denom);
}

double Shape::calcReferenceShapeTverskyScore(const AlignmentResult& res, double alpha)
{
	double shape_ovlp = res.getOverlap() - res.getColorOverlap();
    double ref_shape_self_ovlp = res.getReferenceSelfOverlap() - res.getReferenceColorSelfOverlap();
	double denom = ref_shape_self_ovlp * alpha;

	if (denom == 0.0)
		return 0.0;

    return (shape_ovlp / denom);
}

double Shape::calcReferenceColorTverskyScore(const AlignmentResult& res, double alpha)
{
	double denom = res.getReferenceColorSelfOverlap() * alpha;

	if (denom == 0.0)
		return 0.0;

   return (res.getColorOverlap() / denom);
}

double Shape::calcReferenceTverskyComboScore(const AlignmentResult& res, double alpha)
{
	return (calcReferenceShapeTverskyScore(res, alpha) + calcReferenceColorTverskyScore(res, alpha));
}

double Shape::calcAlignedTotalOverlapTverskyScore(const AlignmentResult& res, double beta)
{
	double denom = res.getAlignedSelfOverlap() * beta;

	if (denom == 0.0)
		return 0.0;

	return (res.getOverlap() / denom);
}

double Shape::calcAlignedShapeTverskyScore(const AlignmentResult& res, double beta)
{
	double shape_ovlp = res.getOverlap() - res.getColorOverlap();
    double al_shape_self_ovlp = res.getAlignedSelfOverlap() - res.getAlignedColorSelfOverlap();
	double denom = al_shape_self_ovlp * beta;

	if (denom == 0.0)
		return 0.0;

    return (shape_ovlp / denom);
}

double Shape::calcAlignedColorTverskyScore(const AlignmentResult& res, double beta)
{
	double denom = res.getAlignedColorSelfOverlap() * beta;

	if (denom == 0.0)
		return 0.0;

	return (res.getColorOverlap() / denom);
}

double Shape::calcAlignedTverskyComboScore(const AlignmentResult& res, double beta)
{
	return (calcAlignedShapeTverskyScore(res, beta) + calcAlignedColorTverskyScore(res, beta));
}
