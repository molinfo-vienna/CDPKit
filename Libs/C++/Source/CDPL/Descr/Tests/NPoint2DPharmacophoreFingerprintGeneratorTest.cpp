/* 
 * NPoint2DPharmacophoreFingerprintGeneratorTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Descr/NPoint2DPharmacophoreFingerprintGenerator.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MoleculeReader.hpp"
#include "CDPL/Pharm/MoleculeFunctions.hpp"
#include "CDPL/Util/BitSet.hpp"


BOOST_AUTO_TEST_CASE(NPoint2DPharmacophoreFingerprintGeneratorTest)
{
    using namespace CDPL;
    using namespace Descr;

    NPoint2DPharmacophoreFingerprintGenerator fp_gen;
    Chem::BasicMolecule mol;
    Util::BitSet gen_fp1(8101);
    Util::BitSet gen_fp2(gen_fp1.size());
    
    BOOST_CHECK(Chem::MoleculeReader(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/LS1.sdf").read(mol));

    Pharm::prepareForPharmacophoreGeneration(mol);
    
    fp_gen.generate(mol, gen_fp1);

    BOOST_CHECK(gen_fp1.count() > 0);
    BOOST_CHECK(gen_fp1.size() == gen_fp2.size());
    
    //---

    fp_gen.setBinSize(NPoint2DPharmacophoreFingerprintGenerator::DEF_BIN_SIZE / 2);

    fp_gen.generate(mol, gen_fp2);

    BOOST_CHECK(gen_fp1 != gen_fp2);

    fp_gen.setBinSize(NPoint2DPharmacophoreFingerprintGenerator::DEF_BIN_SIZE);

    fp_gen.generate(mol, gen_fp2);

    BOOST_CHECK(gen_fp1 == gen_fp2);

    //---

    fp_gen.setMinFeatureTupleSize(NPoint2DPharmacophoreFingerprintGenerator::DEF_MIN_FEATURE_TUPLE_SIZE + 1);

    fp_gen.generate(mol, gen_fp2);

    BOOST_CHECK(gen_fp1 != gen_fp2);

    fp_gen.setMinFeatureTupleSize(NPoint2DPharmacophoreFingerprintGenerator::DEF_MIN_FEATURE_TUPLE_SIZE);

    fp_gen.generate(mol, gen_fp2);

    BOOST_CHECK(gen_fp1 == gen_fp2);

    //---

    fp_gen.setMaxFeatureTupleSize(NPoint2DPharmacophoreFingerprintGenerator::DEF_MAX_FEATURE_TUPLE_SIZE + 1);

    fp_gen.generate(mol, gen_fp2);

    BOOST_CHECK(gen_fp1 != gen_fp2);

    fp_gen.setMaxFeatureTupleSize(NPoint2DPharmacophoreFingerprintGenerator::DEF_MAX_FEATURE_TUPLE_SIZE);

    fp_gen.generate(mol, gen_fp2);

    BOOST_CHECK(gen_fp1 == gen_fp2);

    //---

    fp_gen.setFeatureDistanceType(NPoint2DPharmacophoreFingerprintGenerator::MAX_PATH_LENGTH);

    fp_gen.generate(mol, gen_fp2);

    BOOST_CHECK(gen_fp1 != gen_fp2);

    fp_gen.setFeatureDistanceType(NPoint2DPharmacophoreFingerprintGenerator::DEF_FEATURE_DISTANCE_TYPE);

    fp_gen.generate(mol, gen_fp2);

    BOOST_CHECK(gen_fp1 == gen_fp2);

    //---

    fp_gen.setFeatureDistanceType(NPoint2DPharmacophoreFingerprintGenerator::AVG_PATH_LENGTH);

    fp_gen.generate(mol, gen_fp2);

    BOOST_CHECK(gen_fp1 != gen_fp2);

    fp_gen.setFeatureDistanceType(NPoint2DPharmacophoreFingerprintGenerator::DEF_FEATURE_DISTANCE_TYPE);

    fp_gen.generate(mol, gen_fp2);

    BOOST_CHECK(gen_fp1 == gen_fp2);
}
