# -*- mode: python; tab-width: 4 -*- 

## 
# GenTorsionAngleHistograms.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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


from __future__ import print_function 

import sys
import math

import CDPL.Base as Base
import CDPL.Chem as Chem
import CDPL.ConfGen as ConfGen
import CDPL.ForceField as ForceField
import CDPL.Math as Math

import numpy as np


BIN_SIZE               = 10.0
CIRCLE_BIN_COUNT       = int(360 / BIN_SIZE)


def calcLonePairPosition(atom, mol, coords):
    lp_pos = Math.Vector3D()
    atom_pos = coords[mol.getAtomIndex(atom)]

    for nbr_atom in atom.atoms:
        lp_pos -= coords[mol.getAtomIndex(nbr_atom)]
        lp_pos -= atom_pos

    lp_pos /= atom.getNumAtoms()
    lp_pos += atom_pos

    return lp_pos

def processMatch(mol_idx, match, mol, coords, rule_to_angle_hists):
    ptn = match.getRule().getMatchPatternString();
    ref_atom1_pos = None

    if not match.atoms[0]:
        ref_atom1_pos = calcLonePairPosition(match.atoms[1], mol, coords)
    else:
        ref_atom1_pos = coords[mol.getAtomIndex(match.atoms[0])]
 
    ref_atom2_pos = None

    if not match.atoms[3]:
        ref_atom2_pos = calcLonePairPosition(match.atoms[2], mol, coords)
    else:
        ref_atom2_pos = coords[mol.getAtomIndex(match.atoms[3])]

    angle = ForceField.calcDihedralAngleCos(ref_atom1_pos, coords[mol.getAtomIndex(match.atoms[1])], \
                                            coords[mol.getAtomIndex(match.atoms[2])], ref_atom2_pos)

    if not math.isfinite(angle):
        #print('   Invalid angle (', angle, ') at molecule', mol_idx, '(', ref_atom1_pos, coords[mol.getAtomIndex(match.atoms[1])], \
        #      coords[mol.getAtomIndex(match.atoms[2])], ref_atom2_pos, ')!', file=sys.stderr)
        return

    histo = None

    if not ptn in rule_to_angle_hists:
        histo = np.zeros([CIRCLE_BIN_COUNT], dtype=np.float)
        rule_to_angle_hists[ptn] = histo
    else:
        histo = rule_to_angle_hists[ptn]

    angle = 180.0 * math.acos(angle) / math.pi
    bin_idx1 = int(round(angle / BIN_SIZE) % CIRCLE_BIN_COUNT)

    histo[bin_idx1] += 1.0

    bin_idx2 = int(round((360.0 - angle) / BIN_SIZE) % CIRCLE_BIN_COUNT)

    histo[bin_idx2] += 1.0

def processRuleHistogram(tor_rule, rule_to_angle_hists):
    ptn = tor_rule.getMatchPatternString()

    print(' > Processing histogram for rule:', ptn, file=sys.stderr) 
    
    if not ptn in rule_to_angle_hists:
        print('  No histogram found!', file=sys.stderr) 
        return

    histo = rule_to_angle_hists[ptn]
    num_samples = np.sum(histo)

    #tor_rule.clear()

    for i in range(0, CIRCLE_BIN_COUNT):
        angle = i * BIN_SIZE

        if angle > 180.0:
            angle = angle - 360.0

        tor_rule.addAngle(ConfGen.TorsionRule.AngleEntry(angle, histo[i], 0.0, 100.0 * histo[i] / num_samples))

def processHistograms(tor_cat, rule_to_angle_hists):
    for rule in tor_cat.rules:
        processRuleHistogram(rule, rule_to_angle_hists)

    for cat in tor_cat.categories:
        processHistograms(cat, rule_to_angle_hists)

def process():
    if len(sys.argv) < 4:
        print('Usage:', sys.argv[0], '[input torsion rules.xml] [structures.sdf] [output torsion histogram library.sdf]', file=sys.stderr)
        sys.exit(2)

    tor_lib = ConfGen.TorsionLibrary()

    try:
        tor_lib.load(Base.FileIOStream(sys.argv[1], 'r'))
    except:
        print('Error while loading input torsion rules:', sys.exc_info()[0], file=sys.stderr)
        sys.exit(2)

    tor_matcher = ConfGen.TorsionRuleMatcher(tor_lib)

    tor_matcher.findAllRuleMappings(True)
    tor_matcher.findUniqueMappingsOnly(True)
    tor_matcher.stopAtFirstMatchingRule(True)

    mol = Chem.BasicMolecule()
    mol_reader = Chem.FileSDFMoleculeReader(sys.argv[2])
    
    Chem.setMultiConfImportParameter(mol_reader, False)

    print('- Analyzing input structures...', file=sys.stderr)

    i = 1
    rule_to_angle_hists = {}
    coords = Math.Vector3DArray()

    while True:
        try:
            if not mol_reader.read(mol):
                break

        except IOError as e:
            print('Error while reading input molecule', i, ':', e, file=sys.stderr)
            i += 1
            continue

        if i % 500 == 0:
             print('   ... At input molecule', i, '...', file=sys.stderr)

        Chem.initSubstructureSearchTarget(mol, False)

        try:
            Chem.get3DCoordinates(mol, coords)

        except Base.ItemNotFound:
            print('Could not get 3D-coordinates for molecule', i, file=sys.stderr)
            i += 1
            continue

        for bond in mol.bonds:
            if Chem.getRingFlag(bond):
                continue

            if Chem.isHydrogenBond(bond):
                continue

            if Chem.getExplicitBondCount(bond.getBegin()) <= 1 or Chem.getExplicitBondCount(bond.getEnd()) <= 1:
                continue

            tor_matcher.findMatches(bond, mol, False)

            for match in tor_matcher:
                processMatch(i, match, mol, coords, rule_to_angle_hists)

        i += 1

    print('- Processing torsion angle histograms...', file=sys.stderr)

    processHistograms(tor_lib, rule_to_angle_hists)

    print('- Writing output torsion library...', file=sys.stderr)
    
    try:
        tor_lib.save(Base.FileIOStream(sys.argv[3], 'w+'))

    except:
        print('Error while writing torsion library:', sys.exc_info()[0], file=sys.stderr)
        sys.exit(2)

    print('DONE!', file=sys.stderr)

if __name__ == '__main__':
    process()
