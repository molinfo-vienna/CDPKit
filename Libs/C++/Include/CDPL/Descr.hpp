/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Descr.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief A convenience header including everything that is defined in namespace CDPL::Descr.
 */

#ifndef CDPL_DESCR_HPP
#define CDPL_DESCR_HPP

#include "CDPL/Descr/AutoCorrelation2DVectorCalculator.hpp"
#include "CDPL/Descr/AutoCorrelation3DVectorCalculator.hpp"
#include "CDPL/Descr/AtomAutoCorrelation3DVectorCalculator.hpp"
#include "CDPL/Descr/MoleculeAutoCorr2DDescriptorCalculator.hpp"
#include "CDPL/Descr/MoleculeAutoCorr3DDescriptorCalculator.hpp"

#include "CDPL/Descr/CircularFingerprintGenerator.hpp"
#include "CDPL/Descr/PathFingerprintGenerator.hpp"

#include "CDPL/Descr/BurdenMatrixGenerator.hpp"
#include "CDPL/Descr/BCUTDescriptorCalculator.hpp"

#include "CDPL/Descr/RDFCodeCalculator.hpp"
#include "CDPL/Descr/AtomRDFCodeCalculator.hpp"
#include "CDPL/Descr/MoleculeRDFDescriptorCalculator.hpp"

#include "CDPL/Pharm/FeatureRDFCodeCalculator.hpp"
#include "CDPL/Pharm/FeatureAutoCorrelation3DVectorCalculator.hpp"
#include "CDPL/Pharm/PharmacophoreRDFDescriptorCalculator.hpp"
#include "CDPL/Pharm/PharmacophoreAutoCorr3DDescriptorCalculator.hpp"

#include "CDPL/Descr/SimilarityFunctions.hpp"

#endif // CDPL_DESCR_HPP
