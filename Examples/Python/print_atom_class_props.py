#!/bin/env python

##
# print_atom_class_props.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
#
# Permission to use, copy, modify, and/or distribute this software for any purpose with
# or without fee is hereby granted.
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
# TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
# NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
# DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
# IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
# CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
##


import sys

import CDPL.Chem as Chem
import CDPL.MolProp as MolProp


# outputs the corresponding properties of each atom of the provided molecular graph
def outputProperties(molgraph: Chem.MolecularGraph) -> None:
    Chem.calcImplicitHydrogenCounts(molgraph, False)  # calculate implicit hydrogen counts and set corresponding property for all atoms
    Chem.perceiveHybridizationStates(molgraph, False) # perceive atom hybridization states and set corresponding property for all atoms
    Chem.perceiveSSSR(molgraph, False)                # perceive smallest set of smallest rings and store as Chem.MolecularGraph property
    Chem.setRingFlags(molgraph, False)                # perceive cycles and set corresponding atom and bond properties
    Chem.setAromaticityFlags(molgraph, False)         # perceive aromaticity and set corresponding atom and bond properties
    MolProp.perceiveHBondDonorAtomTypes(molgraph, False) # perceive H-bond donor atom types and set corresponding atom properties
    MolProp.perceiveHBondAcceptorAtomTypes(molgraph, False) # perceive H-bond acceptor atom types and set corresponding atom properties

    hba_type_str = { MolProp.HBondAcceptorAtomType.UNDEF                   : 'UNDEF',
                     MolProp.HBondAcceptorAtomType.NONE                    : 'NONE',
                     MolProp.HBondAcceptorAtomType.O_H2O                   : 'O_H2O',
                     MolProp.HBondAcceptorAtomType.O_UREA                  : 'O_UREA',
                     MolProp.HBondAcceptorAtomType.O_BARBITURIC_ACID       : 'O_BARBITURIC_ACID',
                     MolProp.HBondAcceptorAtomType.O_URIC_ACID             : 'O_URIC_ACID',
                     MolProp.HBondAcceptorAtomType.O_ETHER                 : 'O_ETHER',
                     MolProp.HBondAcceptorAtomType.O_AMIDE                 : 'O_AMIDE',
                     MolProp.HBondAcceptorAtomType.O_N_OXIDE               : 'O_N_OXIDE',
                     MolProp.HBondAcceptorAtomType.O_ACID                  : 'O_ACID',
                     MolProp.HBondAcceptorAtomType.O_ESTER                 : 'O_ESTER',
                     MolProp.HBondAcceptorAtomType.O_SULFOXIDE             : 'O_SULFOXIDE',
                     MolProp.HBondAcceptorAtomType.O_NITRO                 : 'O_NITRO',
                     MolProp.HBondAcceptorAtomType.O_SELEN_OXIDE           : 'O_SELEN_OXIDE',
                     MolProp.HBondAcceptorAtomType.O_ALDEHYD               : 'O_ALDEHYD',
                     MolProp.HBondAcceptorAtomType.O_KETONE                : 'O_KETONE',
                     MolProp.HBondAcceptorAtomType.O_ALCOHOL               : 'O_ALCOHOL',
                     MolProp.HBondAcceptorAtomType.N_NH3                   : 'N_NH3',
                     MolProp.HBondAcceptorAtomType.N_DIAMINE               : 'N_DIAMINE',
                     MolProp.HBondAcceptorAtomType.N_MONO_DI_NITRO_ANILINE : 'N_MONO_DI_NITRO_ANILINE',
                     MolProp.HBondAcceptorAtomType.N_TRI_NITRO_ANILINE     : 'N_TRI_NITRO_ANILINE',
                     MolProp.HBondAcceptorAtomType.N_HALOGENO_ANILINE      : 'N_HALOGENO_ANILINE',
                     MolProp.HBondAcceptorAtomType.N_ANILINE               : 'N_ANILINE',
                     MolProp.HBondAcceptorAtomType.N_NITRILE               : 'N_NITRILE',
                     MolProp.HBondAcceptorAtomType.N_AZOLE                 : 'N_AZOLE',
                     MolProp.HBondAcceptorAtomType.N_AMINE                 : 'N_AMINE',
                     MolProp.HBondAcceptorAtomType.N_AMIDINE               : 'N_AMIDINE',
                     MolProp.HBondAcceptorAtomType.N_AZO                   : 'N_AZO',
                     MolProp.HBondAcceptorAtomType.N_AZINE                 : 'N_AZINE',
                     MolProp.HBondAcceptorAtomType.N_DIAZINE               : 'N_DIAZINE',
                     MolProp.HBondAcceptorAtomType.N_IMINE                 : 'N_IMINE',
                     MolProp.HBondAcceptorAtomType.S_SULFIDE               : 'S_SULFIDE',
                     MolProp.HBondAcceptorAtomType.S_THIOUREA              : 'S_THIOUREA',
                     MolProp.HBondAcceptorAtomType.P_MONO_DI_PHOSPHINE     : 'P_MONO_DI_PHOSPHINE',
                     MolProp.HBondAcceptorAtomType.P_TRI_PHOSPHINE         : 'P_TRI_PHOSPHINE' }

    hbd_type_str = { MolProp.HBondDonorAtomType.UNDEF                       : 'UNDEF',
                     MolProp.HBondDonorAtomType.NONE                        : 'NONE',
                     MolProp.HBondDonorAtomType.I_HI                        : 'I_HI',
                     MolProp.HBondDonorAtomType.BR_HBR                      : 'BR_HBR',
                     MolProp.HBondDonorAtomType.CL_HCL                      : 'CL_HCL',
                     MolProp.HBondDonorAtomType.S_HSCN                      : 'S_HSCN',
                     MolProp.HBondDonorAtomType.F_HF                        : 'F_HF',
                     MolProp.HBondDonorAtomType.H_H2                        : 'H_H2',
                     MolProp.HBondDonorAtomType.C_HCN                       : 'C_HCN',
                     MolProp.HBondDonorAtomType.C_ETHINE                    : 'C_ETHINE',
                     MolProp.HBondDonorAtomType.N_HN3                       : 'N_HN3',
                     MolProp.HBondDonorAtomType.N_NH3                       : 'N_NH3',
                     MolProp.HBondDonorAtomType.N_NH4                       : 'N_NH4',
                     MolProp.HBondDonorAtomType.N_AMINE                     : 'N_AMINE',
                     MolProp.HBondDonorAtomType.N_AMINIUM                   : 'N_AMINIUM',
                     MolProp.HBondDonorAtomType.N_ANILINE                   : 'N_ANILINE',
                     MolProp.HBondDonorAtomType.N_MONO_DI_NITRO_ANILINE     : 'N_MONO_DI_NITRO_ANILINE',
                     MolProp.HBondDonorAtomType.N_TRI_NITRO_ANILINE         : 'N_TRI_NITRO_ANILINE',
                     MolProp.HBondDonorAtomType.N_PYRROLE                   : 'N_PYRROLE',
                     MolProp.HBondDonorAtomType.N_AMIDE                     : 'N_AMIDE',
                     MolProp.HBondDonorAtomType.N_IMINE                     : 'N_IMINE',
                     MolProp.HBondDonorAtomType.N_IMINIUM                   : 'N_IMINIUM',
                     MolProp.HBondDonorAtomType.S_H2S                       : 'S_H2S',
                     MolProp.HBondDonorAtomType.S_HS                        : 'S_HS',
                     MolProp.HBondDonorAtomType.S_THIOL                     : 'S_THIOL',
                     MolProp.HBondDonorAtomType.O_H3PO4                     : 'O_H3PO4',
                     MolProp.HBondDonorAtomType.O_H2CO3                     : 'O_H2CO3',
                     MolProp.HBondDonorAtomType.O_HCO3                      : 'O_HCO3',
                     MolProp.HBondDonorAtomType.O_H2O2                      : 'O_H2O2',
                     MolProp.HBondDonorAtomType.O_H2O                       : 'O_H2O',
                     MolProp.HBondDonorAtomType.O_CF3SO3H                   : 'O_CF3SO3H',
                     MolProp.HBondDonorAtomType.O_HCLO4                     : 'O_HCLO4',
                     MolProp.HBondDonorAtomType.O_H2SO4                     : 'O_H2SO4',
                     MolProp.HBondDonorAtomType.O_HNO3                      : 'O_HNO3',
                     MolProp.HBondDonorAtomType.O_HSO4                      : 'O_HSO4',
                     MolProp.HBondDonorAtomType.O_HNO2                      : 'O_HNO2',
                     MolProp.HBondDonorAtomType.O_NH2OH                     : 'O_NH2OH',
                     MolProp.HBondDonorAtomType.O_H2PO4                     : 'O_H2PO4',
                     MolProp.HBondDonorAtomType.O_H3BO3                     : 'O_H3BO3',
                     MolProp.HBondDonorAtomType.O_H4SIO4                    : 'O_H4SIO4',
                     MolProp.HBondDonorAtomType.O_HPO4                      : 'O_HPO4',
                     MolProp.HBondDonorAtomType.O_H2BO3                     : 'O_H2BO3',
                     MolProp.HBondDonorAtomType.O_HO                        : 'O_HO',
                     MolProp.HBondDonorAtomType.O_SULFONIC_ACID             : 'O_SULFONIC_ACID',
                     MolProp.HBondDonorAtomType.O_MONO_DI_NITRO_PHENOL      : 'O_MONO_DI_NITRO_PHENOL',
                     MolProp.HBondDonorAtomType.O_HALOGENO_ALCOHOL          : 'O_HALOGENO_ALCOHOL',
                     MolProp.HBondDonorAtomType.O_ALCOHOL                   : 'O_ALCOHOL',
                     MolProp.HBondDonorAtomType.O_TRI_NITRO_PHENOL          : 'O_TRI_NITRO_PHENOL',
                     MolProp.HBondDonorAtomType.O_HALOGENO_PHENOL           : 'O_HALOGENO_PHENOL',
                     MolProp.HBondDonorAtomType.O_PHENOL                    : 'O_PHENOL',
                     MolProp.HBondDonorAtomType.O_CARBOXYLIC_ACID           : 'O_CARBOXYLIC_ACID',
                     MolProp.HBondDonorAtomType.O_HALOGENO_CARBOXYCLIC_ACID : 'O_HALOGENO_CARBOXYCLIC_ACID',
                     MolProp.HBondDonorAtomType.O_ENOL                      : 'O_ENOL',
                     MolProp.HBondDonorAtomType.O_OXIME                     : 'O_OXIME',
                     MolProp.HBondDonorAtomType.O_CL5_PHENOL                : 'O_CL5_PHENOL' }
    
    for atom in molgraph.atoms:
        print('- Atom #%s' % str(molgraph.getAtomIndex(atom)))
        print('\tIs std. hydrogen: %s' % str(MolProp.isOrdinaryHydrogen(atom, molgraph)))
        print('\tIs heavy atom: %s' % str(MolProp.isHeavy(atom)))
        print('\tIs unsaturated: %s' % str(MolProp.isUnsaturated(atom, molgraph)))
        print('\tIs H-bond acceptor: %s' % str(MolProp.isHBondAcceptor(atom, molgraph)))
        print('\tH-bond acceptor type: %s' % hba_type_str[MolProp.getHBondAcceptorType(atom)])
        print('\tIs H-bond donor: %s' % str(MolProp.isHBondDonor(atom, molgraph)))
        print('\tH-bond donor type: %s' % hbd_type_str[MolProp.getHBondDonorType(atom)])
        print('\tIs carbonyl carbon: %s' % str(MolProp.isCarbonylLike(atom, molgraph, True, True)))
        print('\tIs amide carbon: %s' % str(MolProp.isAmideCenter(atom, molgraph, True, True)))
        print('\tIs amide nitrogen: %s' % str(MolProp.isAmideNitrogen(atom, molgraph, True, True)))
        print('\tIs invertible nitrogen: %s' % str(MolProp.isInvertibleNitrogen(atom, molgraph)))
        print('\tIs planar nitrogen: %s' % str(MolProp.isPlanarNitrogen(atom, molgraph)))
        
def main() -> None:
    if len(sys.argv) < 2:
        sys.exit('Usage: %s <input mol. file>' % sys.argv[0])

    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(sys.argv[1]) 
  
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        while reader.read(mol):
            try:
                outputProperties(mol)
            except Exception as e:
                sys.exit('Error: processing of molecule failed: ' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    sys.exit(0)
        
if __name__ == '__main__':
    main()
