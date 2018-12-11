# -*- mode: python; tab-width: 4 -*- 

## 
# XLogPReg.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2008 Thomas A. Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
##


import sys
import CDPL.Base as Base
import CDPL.Chem as Chem
import CDPL.Math as Math

def process():
    if len(sys.argv) < 4:
	    print >> sys.stderr, 'Usage:', sys.argv[0], 'training-set.sdf logP-data regression-coeff-file'
        sys.exit(2)

	struct_is = Base.FileIOStream(sys.argv[1], 'r')
	exp_logp_is = Base.FileIOStream(sys.argv[2], 'r')
	coeff_os = Base.FileIOStream(sys.argv[3], 'w')

    mlr_model = Math.DMLRModel()
	sdf_reader = Chem.SDFMoleculeReader(struct_is)
	mol = Chem.BasicMolecule()
	xlogp_calc = Chem.XLogPCalculator()

    histo = Math.DVector()
    histo.resize(Chem.XLogPCalculator.FEATURE_VECTOR_SIZE)

    Chem.setMultiConfImportParameter(sdf_reader, False)

	while sdf_reader.read(mol):
		exp_logp = float(exp_logp_is.readline())

		Chem.perceiveComponents(mol, False)
		Chem.perceiveSSSR(mol, False)
		Chem.setRingFlags(mol, False)
		Chem.calcImplicitHydrogenCounts(mol, False)
		Chem.perceiveHybridizationStates(mol, False)
		Chem.setAromaticityFlags(mol, False)
		Chem.calcTopologicalDistanceMatrix(mol, False)

		xlogp_calc.calculate(mol)

        histo += xlogp_calc.getFeatureVector()

		mlr_model.addXYData(xlogp_calc.getFeatureVector(), exp_logp)

	mlr_model.buildModel()
	mlr_model.calcStatistics()

	print 'Model Statistics:'
	print '----------------------------------'
	print ' Correlation Coeff.: ', mlr_model.getCorrelationCoefficient()
	print ' Goodness of Fit:    ', mlr_model.getGoodnessOfFit()
	print ' Standard Deviation: ', mlr_model.getStandardDeviation()
	print ' Chi Square:         ', mlr_model.getChiSquare()

#    i = 0
#    for v in histo:
#        print (str(i) + ':'), v
#        i = i + 1

	for coeff in mlr_model.getCoefficients():
		coeff_os.write(str(coeff) + ',\n')

if __name__ == '__main__':
    process()
