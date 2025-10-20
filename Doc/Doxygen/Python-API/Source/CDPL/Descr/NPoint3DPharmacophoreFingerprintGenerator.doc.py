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
# \brief NPoint3DPharmacophoreFingerprintGenerator.
# 
# \since 1.2
# 
class NPoint3DPharmacophoreFingerprintGenerator(NPointPharmacophoreFingerprintGenerator):

    ##
    # \brief 
    #
    DEF_BIN_SIZE = 3.0

    ##
    # \brief Initializes the \e %NPoint3DPharmacophoreFingerprintGenerator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %NPoint3DPharmacophoreFingerprintGenerator instance.
    # \param molgraph 
    # \param fp 
    # 
    def __init__(molgraph: Chem.MolecularGraph, fp: Util.BitSet) -> None: pass

    ##
    # \brief Initializes the \e %NPoint3DPharmacophoreFingerprintGenerator instance.
    # \param cntnr 
    # \param fp 
    # 
    def __init__(cntnr: Pharm.Pharmacophore, fp: Util.BitSet) -> None: pass

    ##
    # \brief Initializes a copy of the \e %NPoint3DPharmacophoreFingerprintGenerator instance \a gen.
    # \param gen The \e %NPoint3DPharmacophoreFingerprintGenerator instance to copy.
    # 
    def __init__(gen: NPoint3DPharmacophoreFingerprintGenerator) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %NPoint3DPharmacophoreFingerprintGenerator instance \a gen.
    # \param gen The \c %NPoint3DPharmacophoreFingerprintGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: NPoint3DPharmacophoreFingerprintGenerator) -> NPoint3DPharmacophoreFingerprintGenerator: pass

    ##
    # \brief 
    # \param molgraph 
    # \param fp 
    #
    def generate(molgraph: Chem.MolecularGraph, fp: Util.BitSet) -> None: pass

    ##
    # \brief 
    # \param cntnr 
    # \param fp 
    #
    def generate(cntnr: Pharm.FeatureContainer, fp: Util.BitSet) -> None: pass
