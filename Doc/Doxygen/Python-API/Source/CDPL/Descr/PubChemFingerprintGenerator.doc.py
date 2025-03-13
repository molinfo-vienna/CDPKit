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
# \brief Generation of 881 bit PubChem fingerprints.
# 
# \since 1.2 
# 
# \see [\ref PCDS]
# 
class PubChemFingerprintGenerator(Boost.Python.instance):

    ##
    # \brief 
    #
    NUM_BITS = 881

    ##
    # \brief Constructs the <tt>PubChemFingerprintGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>PubChemFingerprintGenerator</tt> instance and generates the fingerprint of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to generate the fingerprint.
    # \param fp The generated fingerprint.
    # 
    def __init__(molgraph: Chem.MolecularGraph, fp: Util.BitSet) -> None: pass

    ##
    # \brief Initializes a copy of the \e %PubChemFingerprintGenerator instance \a gen.
    # \param gen The \e %PubChemFingerprintGenerator instance to copy.
    # 
    def __init__(gen: PubChemFingerprintGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %PubChemFingerprintGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %PubChemFingerprintGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %PubChemFingerprintGenerator instance \a gen.
    # \param gen The \c %PubChemFingerprintGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: PubChemFingerprintGenerator) -> PubChemFingerprintGenerator: pass

    ##
    # \brief Generates the fingerprint of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to generate the fingerprint.
    # \param fp The generated fingerprint.
    # 
    def generate(molgraph: Chem.MolecularGraph, fp: Util.BitSet) -> None: pass

    objectID = property(getObjectID)
