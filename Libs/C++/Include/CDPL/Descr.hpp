/* 
 * Descr.hpp 
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
 * \brief A convenience header including everything that is defined in namespace CDPL::Descr.
 */

#ifndef CDPL_DESCR_HPP
#define CDPL_DESCR_HPP

#include "CDPL/Descr/Entity3DContainerFunctions.hpp"
#include "CDPL/Descr/AtomContainerFunctions.hpp"
#include "CDPL/Descr/MolecularGraphFunctions.hpp"
#include "CDPL/Descr/SimilarityFunctions.hpp"
#include "CDPL/Descr/SimilarityFunctors.hpp"
#include "CDPL/Descr/AutoCorrelation2DVectorCalculator.hpp"
#include "CDPL/Descr/AutoCorrelation3DVectorCalculator.hpp"
#include "CDPL/Descr/AtomAutoCorrelation3DVectorCalculator.hpp"
#include "CDPL/Descr/FeatureAutoCorrelation3DVectorCalculator.hpp"
#include "CDPL/Descr/MoleculeAutoCorr2DDescriptorCalculator.hpp"
#include "CDPL/Descr/MoleculeAutoCorr3DDescriptorCalculator.hpp"
#include "CDPL/Descr/PharmacophoreAutoCorr3DDescriptorCalculator.hpp"
#include "CDPL/Descr/CircularFingerprintGenerator.hpp"
#include "CDPL/Descr/PathFingerprintGenerator.hpp"
#include "CDPL/Descr/MACCSFingerprintGenerator.hpp"
#include "CDPL/Descr/PubChemFingerprintGenerator.hpp"
#include "CDPL/Descr/BurdenMatrixGenerator.hpp"
#include "CDPL/Descr/BCUTDescriptorCalculator.hpp"
#include "CDPL/Descr/MolecularComplexityCalculator.hpp"
#include "CDPL/Descr/RDFCodeCalculator.hpp"
#include "CDPL/Descr/AtomRDFCodeCalculator.hpp"
#include "CDPL/Descr/FeatureRDFCodeCalculator.hpp"
#include "CDPL/Descr/MoleculeRDFDescriptorCalculator.hpp"
#include "CDPL/Descr/PharmacophoreRDFDescriptorCalculator.hpp"
#include "CDPL/Descr/NPointPharmacophoreFingerprintGenerator.hpp"
#include "CDPL/Descr/NPoint2DPharmacophoreFingerprintGenerator.hpp"
#include "CDPL/Descr/NPoint3DPharmacophoreFingerprintGenerator.hpp"

#endif // CDPL_DESCR_HPP
