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
# \brief Hit-callback functor for use with Pharm.ScreeningProcessor that writes each accepted hit molecule (optionally aligned and annotated with score/database properties) to a Base.DataWriter sink.
# 
class FileScreeningHitCollector(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %FileScreeningHitCollector instance \a collector.
    # \param collector The \c %FileScreeningHitCollector instance to copy.
    # 
    def __init__(collector: FileScreeningHitCollector) -> None: pass

    ##
    # \brief Constructs the <tt>FileScreeningHitCollector</tt> instance.
    # 
    # \param writer The molecular-graph writer used to output hit molecules.
    # 
    def __init__(writer: Chem.MolecularGraphWriterBase) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FileScreeningHitCollector instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FileScreeningHitCollector instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %FileScreeningHitCollector instance \a collector.
    # \param collector The \c %FileScreeningHitCollector instance to copy.
    # \return \a self
    # 
    def assign(collector: FileScreeningHitCollector) -> FileScreeningHitCollector: pass

    ##
    # \brief Specifies the molecular-graph writer used to output hit molecules.
    # 
    # \param writer The data writer.
    # 
    def setDataWriter(writer: Chem.MolecularGraphWriterBase) -> None: pass

    ##
    # \brief Returns the currently configured molecular-graph writer.
    # 
    # \return A reference to the data writer.
    # 
    def getDataWriter() -> Chem.MolecularGraphWriterBase: pass

    ##
    # \brief Specifies whether the hit molecule's coordinates shall be transformed by the alignment matrix before writing.
    # 
    # \param align <tt>True</tt> to align the hit molecule, and <tt>False</tt> to write the original coordinates.
    # 
    def alignHitMolecule(align: bool) -> None: pass

    ##
    # \brief Tells whether the hit molecule is aligned before writing.
    # 
    # \return <tt>True</tt> if alignment is performed, and <tt>False</tt> otherwise.
    # 
    def alignHitMolecule() -> bool: pass

    ##
    # \brief Specifies whether the alignment score shall be written as a molecule property.
    # 
    # \param output <tt>True</tt> to write the score property, and <tt>False</tt> to skip it.
    # 
    def outputScoreProperty(output: bool) -> None: pass

    ##
    # \brief Tells whether the alignment score is written as a molecule property.
    # 
    # \return <tt>True</tt> if the score property is written, and <tt>False</tt> otherwise.
    # 
    def outputScoreProperty() -> bool: pass

    ##
    # \brief Specifies whether the source-database name shall be written as a molecule property.
    # 
    # \param output <tt>True</tt> to write the database-name property, and <tt>False</tt> to skip it.
    # 
    def outputDBNameProperty(output: bool) -> None: pass

    ##
    # \brief Tells whether the source-database name is written as a molecule property.
    # 
    # \return <tt>True</tt> if the database-name property is written, and <tt>False</tt> otherwise.
    # 
    def outputDBNameProperty() -> bool: pass

    ##
    # \brief Specifies whether the source-database molecule index shall be written as a molecule property.
    # 
    # \param output <tt>True</tt> to write the molecule-index property, and <tt>False</tt> to skip it.
    # 
    def outputDBMoleculeIndexProperty(output: bool) -> None: pass

    ##
    # \brief Tells whether the source-database molecule index is written as a molecule property.
    # 
    # \return <tt>True</tt> if the molecule-index property is written, and <tt>False</tt> otherwise.
    # 
    def outputDBMoleculeIndexProperty() -> bool: pass

    ##
    # \brief Specifies whether the conformer index within the source molecule shall be written as a molecule property.
    # 
    # \param output <tt>True</tt> to write the conformer-index property, and <tt>False</tt> to skip it.
    # 
    def outputMoleculeConfIndexProperty(output: bool) -> None: pass

    ##
    # \brief Tells whether the conformer index within the source molecule is written as a molecule property.
    # 
    # \return <tt>True</tt> if the conformer-index property is written, and <tt>False</tt> otherwise.
    # 
    def outputMoleculeConfIndexProperty() -> bool: pass

    ##
    # \brief Specifies whether emitted molecule and conformer indices are zero-based (rather than one-based).
    # 
    # \param zero_based <tt>True</tt> to use zero-based indices, and <tt>False</tt> to use one-based indices.
    # 
    def outputZeroBasedIndices(zero_based: bool) -> None: pass

    ##
    # \brief Tells whether emitted molecule and conformer indices are zero-based.
    # 
    # \return <tt>True</tt> if zero-based indices are used, and <tt>False</tt> otherwise.
    # 
    def outputZeroBasedIndices() -> bool: pass

    ##
    # \brief Writes the search hit <em>hit</em> and its alignment score <em>score</em> to the configured data writer.
    # 
    # \param hit The screening search hit.
    # \param score The alignment score of the hit.
    # 
    # \return <tt>True</tt> if the hit was successfully written, and <tt>False</tt> otherwise.
    # 
    def __call__(hit: SearchHit, score: float) -> bool: pass

    objectID = property(getObjectID)

    dataWriter = property(getDataWriter, setDataWriter)

    alignHitMol = property(alignHitMolecule, alignHitMolecule)

    outputScoreProp = property(outputScoreProperty, outputScoreProperty)

    outputDBNameProp = property(outputDBNameProperty, outputDBNameProperty)

    outputDBMoleculeIndexProp = property(outputDBMoleculeIndexProperty, outputDBMoleculeIndexProperty)

    outputMoleculeConfIndexProp = property(outputMoleculeConfIndexProperty, outputMoleculeConfIndexProperty)

    outputZeroBasedInds = property(outputZeroBasedIndices, outputZeroBasedIndices)
