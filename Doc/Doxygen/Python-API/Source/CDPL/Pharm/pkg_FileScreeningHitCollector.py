#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
# \brief 
#
class FileScreeningHitCollector(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FileScreeningHitCollector instance.
    # \param collector 
    #
    def __init__(collector: FileScreeningHitCollector) -> None: pass

    ##
    # \brief Initializes the \e %FileScreeningHitCollector instance.
    # \param writer 
    #
    def __init__(writer: CDPL.Chem.MolecularGraphWriter) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %FileScreeningHitCollector instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FileScreeningHitCollector instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FileScreeningHitCollector instance \a collector.
    # \param collector The \e %FileScreeningHitCollector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(collector: FileScreeningHitCollector) -> FileScreeningHitCollector: pass

    ##
    # \brief 
    # \param writer 
    #
    def setDataWriter(writer: CDPL.Chem.MolecularGraphWriter) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getDataWriter() -> CDPL.Chem.MolecularGraphWriter: pass

    ##
    # \brief 
    # \param align 
    #
    def alignHitMolecule(align: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isHitMoleculeAligned() -> bool: pass

    ##
    # \brief 
    # \param write 
    #
    def writeScoreProperty(write: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isScorePropertyWritten() -> bool: pass

    ##
    # \brief 
    # \param write 
    #
    def writeDBNameProperty(write: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isDBNamePropertyWritten() -> bool: pass

    ##
    # \brief 
    # \param write 
    #
    def writeDBMoleculeIndexProperty(write: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isDBMoleculeIndexPropertyWritten() -> bool: pass

    ##
    # \brief 
    # \param write 
    #
    def writeMoleculeConfIndexProperty(write: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isMoleculeConfIndexPropertyWritten() -> bool: pass

    ##
    # \brief 
    # \param hit 
    # \param score 
    # \return 
    #
    def __call__(hit: SearchHit, score: float) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    dataWriter = property(getDataWriter, setDataWriter)

    ##
    # \brief FIXME!
    #
    hitMoleculeAlignment = property(getHitMoleculeAlignment, setHitMoleculeAlignment)

    ##
    # \brief FIXME!
    #
    scorePropertyOutput = property(getScorePropertyOutput, setScorePropertyOutput)

    ##
    # \brief FIXME!
    #
    dbNamePropertyOutput = property(getDbNamePropertyOutput, setDbNamePropertyOutput)

    ##
    # \brief FIXME!
    #
    dbMoleculeIndexPropertyOutput = property(getDbMoleculeIndexPropertyOutput, setDbMoleculeIndexPropertyOutput)

    ##
    # \brief FIXME!
    #
    moleculeConfIndexPropertyOutput = property(getMoleculeConfIndexPropertyOutput, setMoleculeConfIndexPropertyOutput)
