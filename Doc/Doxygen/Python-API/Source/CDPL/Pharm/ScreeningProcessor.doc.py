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
# \brief High-level driver for pharmacophore-based screening of a Pharm.ScreeningDBAccessor-backed database against a query feature container, reporting alignment hits via a user-supplied callback.
# 
class ScreeningProcessor(Boost.Python.instance):

    ##
    # \brief Specifies which conformer-level hits are reported per molecule.
    # 
    class HitReportMode(Boost.Python.enum):

        ##
        # \brief Report the first conformer that matches the query.
        # 
        FIRST_MATCHING_CONF = 0

        ##
        # \brief Report only the best-scoring matching conformer.
        # 
        BEST_MATCHING_CONF = 1

        ##
        # \brief Report every conformer that matches the query.
        # 
        ALL_MATCHING_CONFS = 2

    ##
    # \brief Data structure representing a single alignment hit produced by the screening processor, bundling the source pharmacophore/molecule, the alignment transformation and the source-database indices.
    # 
    class SearchHit(Boost.Python.instance):

        ##
        # \brief Constructs the <tt>SearchHit</tt> instance with the given references.
        # 
        # \param hit_prov The screening processor that produced the hit.
        # \param qry_pharm The query pharmacophore.
        # \param hit_pharm The hit pharmacophore.
        # \param mol The hit molecule.
        # \param xform The alignment transformation that maps the hit onto the query.
        # \param pharm_idx The zero-based pharmacophore index within the source database.
        # \param mol_idx The zero-based molecule index within the source database.
        # \param conf_idx The zero-based conformer index within the source molecule.
        # 
        def __init__(hit_prov: ScreeningProcessor, qry_pharm: FeatureContainer, hit_pharm: FeatureContainer, mol: Chem.Molecule, xform: Math.Matrix4D, pharm_idx: int, mol_idx: int, conf_idx: int) -> None: pass

        ##
        # \brief Initializes a copy of the \c %SearchHit instance \a hit.
        # \param hit The \c %SearchHit instance to copy.
        # 
        def __init__(hit: SearchHit) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %SearchHit instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %SearchHit instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %SearchHit instance \a hit.
        # \param hit The \c %SearchHit instance to copy.
        # \return \a self
        # 
        def assign(hit: SearchHit) -> SearchHit: pass

        ##
        # \brief Returns the screening processor that produced the hit.
        # 
        # \return A reference to the hit-providing screening processor.
        # 
        def getHitProvider() -> ScreeningProcessor: pass

        ##
        # \brief Returns the query pharmacophore.
        # 
        # \return A reference to the query pharmacophore.
        # 
        def getQueryPharmacophore() -> FeatureContainer: pass

        ##
        # \brief Returns the hit pharmacophore.
        # 
        # \return A reference to the hit pharmacophore.
        # 
        def getHitPharmacophore() -> FeatureContainer: pass

        ##
        # \brief Returns the hit molecule.
        # 
        # \return A reference to the hit molecule.
        # 
        def getHitMolecule() -> Chem.Molecule: pass

        ##
        # \brief Returns the rigid-body transformation that aligns the hit onto the query pharmacophore.
        # 
        # \return A reference to the alignment transformation matrix.
        # 
        def getHitAlignmentTransform() -> Math.Matrix4D: pass

        ##
        # \brief Returns the source-database pharmacophore index of the hit.
        # 
        # \return The zero-based pharmacophore index.
        # 
        def getHitPharmacophoreIndex() -> int: pass

        ##
        # \brief Returns the source-database molecule index of the hit.
        # 
        # \return The zero-based molecule index.
        # 
        def getHitMoleculeIndex() -> int: pass

        ##
        # \brief Returns the conformer index within the source molecule.
        # 
        # \return The zero-based conformer index.
        # 
        def getHitConformationIndex() -> int: pass

        objectID = property(getObjectID)

        hitProvider = property(getHitProvider)

        queryPharmacophore = property(getQueryPharmacophore)

        hitPharmacophore = property(getHitPharmacophore)

        hitMolecule = property(getHitMolecule)

        hitAlignmentTransform = property(getHitAlignmentTransform)

        hitPharmacophoreIndex = property(getHitPharmacophoreIndex)

        hitMoleculeIndex = property(getHitMoleculeIndex)

        hitConformationIndex = property(getHitConformationIndex)

    ##
    # \brief Constructs the <tt>ScreeningProcessor</tt> instance for the given screening database accessor <em>db_acc</em>.
    # 
    # \param db_acc An accessor for the database to screen.
    # 
    def __init__(db_acc: ScreeningDBAccessor) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ScreeningProcessor instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ScreeningProcessor instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Specifies the screening database accessor.
    # 
    # \param db_acc The new database accessor.
    # 
    def setDBAccessor(db_acc: ScreeningDBAccessor) -> None: pass

    ##
    # \brief Returns the currently configured screening database accessor.
    # 
    # \return A reference to the database accessor.
    # 
    def getDBAccessor() -> ScreeningDBAccessor: pass

    ##
    # \brief Sets the hit-report mode.
    # 
    # \param mode The new hit-report mode.
    # 
    def setHitReportMode(mode: HitReportMode) -> None: pass

    ##
    # \brief Returns the currently configured hit-report mode.
    # 
    # \return The hit-report mode.
    # 
    def getHitReportMode() -> HitReportMode: pass

    ##
    # \brief Sets the maximum number of query features that may remain unmatched in a valid hit.
    # 
    # \param max_num The new maximum number of omitted features.
    # 
    def setMaxNumOmittedFeatures(max_num: int) -> None: pass

    ##
    # \brief Returns the currently configured maximum number of omitted features.
    # 
    # \return The maximum number of omitted features.
    # 
    def getMaxNumOmittedFeatures() -> int: pass

    ##
    # \brief Specifies whether the alignment shall check exclusion volume clashes between the query and the hit molecule.
    # 
    # \param check <tt>True</tt> to enable the clash check, and <tt>False</tt> to disable it.
    # 
    def checkXVolumeClashes(check: bool) -> None: pass

    ##
    # \brief Tells whether exclusion volume clashes are checked during alignment.
    # 
    # \return <tt>True</tt> if the clash check is enabled, and <tt>False</tt> otherwise.
    # 
    def xVolumeClashesChecked() -> bool: pass

    ##
    # \brief Specifies whether the alignment shall search for the best-scoring rather than the first valid alignment per pose.
    # 
    # \param seek_best <tt>True</tt> to seek the best alignment, and <tt>False</tt> to accept the first valid alignment.
    # 
    def seekBestAlignments(seek_best: bool) -> None: pass

    ##
    # \brief Tells whether the alignment seeks the best-scoring rather than the first valid alignment.
    # 
    # \return <tt>True</tt> if best-alignment seeking is enabled, and <tt>False</tt> otherwise.
    # 
    def bestAlignmentsSeeked() -> bool: pass

    ##
    # \brief Specifies the hit-callback function.
    # 
    # \param func The hit-callback function.
    # 
    def setHitCallback(func: BoolSearchHitDoubleFunctor) -> None: pass

    ##
    # \brief Returns the currently configured hit-callback function.
    # 
    # \return A reference to the hit-callback function.
    # 
    def getHitCallback() -> BoolSearchHitDoubleFunctor: pass

    ##
    # \brief Specifies the progress-reporting callback.
    # 
    # \param func The progress-callback function.
    # 
    def setProgressCallback(func: BoolSizeType2Functor) -> None: pass

    ##
    # \brief Returns the currently configured progress-reporting callback.
    # 
    # \return A reference to the progress-callback function.
    # 
    def getProgressCallback() -> BoolSizeType2Functor: pass

    ##
    # \brief Specifies the function used to score a search hit.
    # 
    # \param func The scoring function.
    # 
    def setScoringFunction(func: DoubleSearchHitFunctor) -> None: pass

    ##
    # \brief Returns the currently configured scoring function.
    # 
    # \return A reference to the scoring function.
    # 
    def getScoringFunction() -> DoubleSearchHitFunctor: pass

    ##
    # \brief Screens the database with the supplied query pharmacophore.
    # 
    # \param query The query feature container.
    # \param mol_start_idx The zero-based index of the first molecule to screen.
    # \param mol_end_idx The exclusive upper bound of the molecule range. If <em>0</em>, the search runs through the end of the database.
    # 
    # \return The number of accepted hits produced by the search.
    # 
    def searchDB(query: FeatureContainer, mol_start_idx: int = 0, mol_end_idx: int = 0) -> int: pass

    objectID = property(getObjectID)

    dbAcccessor = property(getDBAccessor, setDBAccessor)

    hitCallback = property(getHitCallback, setHitCallback)

    progressCallback = property(getProgressCallback, setProgressCallback)

    scoringFunction = property(getScoringFunction, setScoringFunction)

    hitReportMode = property(getHitReportMode, setHitReportMode)

    maxNumOmittedFeatures = property(getMaxNumOmittedFeatures, setMaxNumOmittedFeatures)

    checkXVolumes = property(xVolumeClashesChecked, checkXVolumeClashes)

    bestAlignments = property(bestAlignmentsSeeked, seekBestAlignments)
