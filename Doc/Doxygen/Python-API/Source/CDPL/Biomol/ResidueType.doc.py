#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
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
#

##
# \brief Provides constants for the specification of the type of a chemical component (residue).
# 
# Type values follow the categories used by the <em>PDB Chemical Component Dictionary</em> for the classification of polymer residues, small-molecule ligands, and saccharide components.
# 
class ResidueType(Boost.Python.instance):

    ##
    # \brief Specifies an unknown residue type.
    # 
    UNKNOWN = 0

    ##
    # \brief Specifies a residue type not covered by the other constants in this namespace.
    # 
    OTHER = 1

    ##
    # \brief Specifies a non-polymer chemical component (e.g. small-molecule ligand).
    # 
    NON_POLYMER = 2

    ##
    # \brief Specifies the C-terminal residue of an L-peptide chain.
    # 
    # \since 1.2
    # 
    L_PEPTIDE_CARBOXY_TERMINUS = 3

    ##
    # \brief Specifies the N-terminal residue of an L-peptide chain.
    # 
    # \since 1.2
    # 
    L_PEPTIDE_AMINO_TERMINUS = 4

    ##
    # \brief Specifies the N-terminal residue of a D-peptide chain.
    # 
    # \since 1.2
    # 
    D_PEPTIDE_AMINO_TERMINUS = 5

    ##
    # \brief Specifies a peptide-linking residue of unspecified chirality.
    # 
    PEPTIDE_LINKING = 6

    ##
    # \brief Specifies a peptide-linking L-amino acid residue.
    # 
    # \since 1.2
    # 
    L_PEPTIDE_LINKING = 7

    ##
    # \brief Specifies a peptide-linking D-amino acid residue.
    # 
    # \since 1.2
    # 
    D_PEPTIDE_LINKING = 8

    ##
    # \brief Specifies a peptide-linking L--amino acid residue.
    # 
    # \since 1.2
    # 
    L_BETA_PEPTIDE_LINKING = 9

    ##
    # \brief Specifies a peptide-linking D--amino acid residue.
    # 
    # \since 1.2
    # 
    D_BETA_PEPTIDE_LINKING = 10

    ##
    # \brief Specifies a peptide-linking L--amino acid residue.
    # 
    # \since 1.2
    # 
    L_GAMMA_PEPTIDE_LINKING = 11

    ##
    # \brief Specifies a peptide-linking D--amino acid residue.
    # 
    # \since 1.2
    # 
    D_GAMMA_PEPTIDE_LINKING = 12

    ##
    # \brief Specifies a peptide-like (non-standard) residue.
    # 
    PEPTIDE_LIKE = 13

    ##
    # \brief Specifies an RNA residue at the 3'-hydroxy terminus.
    # 
    # \since 1.2
    # 
    RNA_3_HYDROXY_TERMINUS = 14

    ##
    # \brief Specifies an RNA residue at the 5'-hydroxy terminus.
    # 
    # \since 1.2
    # 
    RNA_5_HYDROXY_TERMINUS = 15

    ##
    # \brief Specifies a DNA residue at the 3'-hydroxy terminus.
    # 
    # \since 1.2
    # 
    DNA_3_HYDROXY_TERMINUS = 16

    ##
    # \brief Specifies a DNA residue at the 5'-hydroxy terminus.
    # 
    # \since 1.2
    # 
    DNA_5_HYDROXY_TERMINUS = 17

    ##
    # \brief Specifies an RNA-linking residue.
    # 
    RNA_LINKING = 18

    ##
    # \brief Specifies a DNA-linking residue.
    # 
    DNA_LINKING = 19

    ##
    # \brief Specifies an L-RNA-linking residue.
    # 
    # \since 1.2
    # 
    L_RNA_LINKING = 20

    ##
    # \brief Specifies an L-DNA-linking residue.
    # 
    # \since 1.2
    # 
    L_DNA_LINKING = 21

    ##
    # \brief Specifies an L-saccharide with a 1,4-glycosidic linkage.
    # 
    # \since 1.2
    # 
    L_SACCHARIDE_1_4_LINKING = 22

    ##
    # \brief Specifies a D-saccharide with a 1,4-glycosidic linkage.
    # 
    # \since 1.2
    # 
    D_SACCHARIDE_1_4_LINKING = 23

    ##
    # \brief Specifies an L-saccharide with an -glycosidic linkage.
    # 
    # \since 1.2
    # 
    L_SACCHARIDE_ALPHA_LINKING = 24

    ##
    # \brief Specifies a D-saccharide with an -glycosidic linkage.
    # 
    # \since 1.2
    # 
    D_SACCHARIDE_ALPHA_LINKING = 25

    ##
    # \brief Specifies an L-saccharide with a -glycosidic linkage.
    # 
    # \since 1.2
    # 
    L_SACCHARIDE_BETA_LINKING = 26

    ##
    # \brief Specifies a D-saccharide with a -glycosidic linkage.
    # 
    # \since 1.2
    # 
    D_SACCHARIDE_BETA_LINKING = 27

    ##
    # \brief Specifies an L-saccharide residue.
    # 
    # \since 1.2
    # 
    L_SACCHARIDE = 28

    ##
    # \brief Specifies a D-saccharide residue.
    # 
    # \since 1.2
    # 
    D_SACCHARIDE = 29

    ##
    # \brief Specifies a saccharide residue of unspecified chirality.
    # 
    SACCHARIDE = 30
