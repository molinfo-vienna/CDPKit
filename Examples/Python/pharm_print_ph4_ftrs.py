#!/bin/env python

##
# pharm_print_ph4_ftrs.py 
#
# This file is part of the Pharmical Data Processing Toolkit
#
# Copyright (C) 2003-2022 Thomas Seidel <thomas.seidel@univie.ac.at>
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
import os

import CDPL.Pharm as Pharm
import CDPL.Chem as Chem


# outputs all (available) properties of the features stored in the given feature container
def outputFeatureProps(ph4: Pharm.FeatureContainer) -> None: 
    ftr_type_str = { Pharm.FeatureType.UNKNOWN               : 'UNKNOWN',
                     Pharm.FeatureType.HYDROPHOBIC           : 'HYDROPHOBIC',
                     Pharm.FeatureType.AROMATIC              : 'AROMATIC',
                     Pharm.FeatureType.NEGATIVE_IONIZABLE    : 'NEGATIVE_IONIZABLE',
                     Pharm.FeatureType.POSITIVE_IONIZABLE    : 'POSITIVE_IONIZABLE',
                     Pharm.FeatureType.H_BOND_DONOR          : 'H_BOND_DONOR',
                     Pharm.FeatureType.H_BOND_ACCEPTOR       : 'H_BOND_ACCEPTOR',
                     Pharm.FeatureType.HALOGEN_BOND_DONOR    : 'HALOGEN_BOND_DONOR',
                     Pharm.FeatureType.HALOGEN_BOND_ACCEPTOR : 'HALOGEN_BOND_ACCEPTOR',
                     Pharm.FeatureType.EXCLUSION_VOLUME      : 'EXCLUSION_VOLUME' }
  
    geom_str = { Pharm.FeatureGeometry.UNDEF   : 'UNDEF',
                 Pharm.FeatureGeometry.SPHERE  : 'SPHERE',
                 Pharm.FeatureGeometry.VECTOR  : 'VECTOR',
                 Pharm.FeatureGeometry.PLANE   : 'PLANE' }

    print('Composition of pharmacophore \'%s\':' % Pharm.getName(ph4))

    for i in range(0, len(ph4)):
        ftr = ph4[i]

        print(' - Feature #%s:' % str(i))
        print('  - Type: %s' % ftr_type_str[Pharm.getType(ftr)])
        print('  - Geometry: %s' % geom_str[Pharm.getGeometry(ftr)])
        print('  - Tolerance: %s' % Pharm.getTolerance(ftr))
        print('  - Weight: %s' % Pharm.getWeight(ftr))
        print('  - Optional: %s' % Pharm.getOptionalFlag(ftr))
        print('  - Disabled: %s' % Pharm.getDisabledFlag(ftr))
        print('  - Length: %s' % Pharm.getLength(ftr))
        print('  - Hydrophobicity: %s' % Pharm.getHydrophobicity(ftr))

        if Chem.has3DCoordinates(ftr):         # Pharm.Feature derives from Chem.Entity3D - therefore a function from the Chem package is used here!
            print('  - Position: %s' % Chem.get3DCoordinates(ftr))
 
        if Pharm.hasOrientation(ftr):
            print('  - Orientation: %s' % Pharm.getOrientation(ftr))

def main() -> None:
    if len(sys.argv) < 2:
        sys.exit('Usage: %s <input pharm. file>' % sys.argv[0])

    # create reader for input pharmacophores (format specified by file extension)
    reader = Pharm.PharmacophoreReader(sys.argv[1]) 
    
    # create an instance of the default implementation of the Pharm.Pharmacophore interface
    ph4 = Pharm.BasicPharmacophore()
    
    # read and process pharmacophores one after the other until the end of input has been reached
    try:
        while reader.read(ph4): 
            try:
                outputFeatureProps(ph4)
            except Exception as e:
                sys.exit('Error: processing of pharmacophore failed: ' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading pharmacophore failed: ' + str(e))

    sys.exit(0)
        
if __name__ == '__main__':
    main()
