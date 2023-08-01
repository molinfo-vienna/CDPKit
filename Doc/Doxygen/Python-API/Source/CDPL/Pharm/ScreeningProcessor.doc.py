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
# \brief ScreeningProcessor.
# 
class ScreeningProcessor(Boost.Python.instance):

    ##
    # \brief 
    #
    class HitReportMode(Boost.Python.enum):

        ##
        # \brief FIRST_MATCHING_CONF.
        #
        FIRST_MATCHING_CONF = 0

        ##
        # \brief BEST_MATCHING_CONF.
        #
        BEST_MATCHING_CONF = 1

        ##
        # \brief ALL_MATCHING_CONFS.
        #
        ALL_MATCHING_CONFS = 2

    ##
    # \brief 
    #
    class SearchHit(Boost.Python.instance):

        ##
        # \brief Initializes the \e %SearchHit instance.
        # \param hit_prov 
        # \param qry_pharm 
        # \param hit_pharm 
        # \param mol 
        # \param xform 
        # \param pharm_idx 
        # \param mol_idx 
        # \param conf_idx 
        # 
        def __init__(hit_prov: ScreeningProcessor, qry_pharm: FeatureContainer, hit_pharm: FeatureContainer, mol: Chem.Molecule, xform: Math.Matrix4D, pharm_idx: int, mol_idx: int, conf_idx: int) -> None: pass

        ##
        # \brief Initializes the \e %SearchHit instance with a copy of the state of the \e %SearchHit instance \a hit.
        # \param hit The \e %SearchHit instance to copy.
        # 
        def __init__(hit: SearchHit) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \e %SearchHit instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SearchHit instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %SearchHit instance \a hit.
        # \param hit The \e %SearchHit instance to copy.
        # \return \a self
        # 
        def assign(hit: SearchHit) -> SearchHit: pass

        ##
        # \brief 
        # \return 
        #
        def getHitProvider() -> ScreeningProcessor: pass

        ##
        # \brief 
        # \return 
        #
        def getQueryPharmacophore() -> FeatureContainer: pass

        ##
        # \brief 
        # \return 
        #
        def getHitPharmacophore() -> FeatureContainer: pass

        ##
        # \brief 
        # \return 
        #
        def getHitMolecule() -> Chem.Molecule: pass

        ##
        # \brief 
        # \return 
        #
        def getHitAlignmentTransform() -> Math.Matrix4D: pass

        ##
        # \brief 
        # \return 
        #
        def getHitPharmacophoreIndex() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getHitMoleculeIndex() -> int: pass

        ##
        # \brief 
        # \return 
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
    # Different Python \e %ScreeningProcessor instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ScreeningProcessor instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param db_acc 
    #
    def setDBAccessor(db_acc: ScreeningDBAccessor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getDBAccessor() -> ScreeningDBAccessor: pass

    ##
    # \brief 
    # \param mode 
    #
    def setHitReportMode(mode: HitReportMode) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getHitReportMode() -> HitReportMode: pass

    ##
    # \brief 
    # \param max_num 
    #
    def setMaxNumOmittedFeatures(max_num: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxNumOmittedFeatures() -> int: pass

    ##
    # \brief 
    # \param check 
    #
    def checkXVolumeClashes(check: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def xVolumeClashesChecked() -> bool: pass

    ##
    # \brief 
    # \param seek_best 
    #
    def seekBestAlignments(seek_best: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def bestAlignmentsSeeked() -> bool: pass

    ##
    # \brief 
    # \param func 
    #
    def setHitCallback(func: BoolSearchHitDoubleFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getHitCallback() -> BoolSearchHitDoubleFunctor: pass

    ##
    # \brief 
    # \param func 
    #
    def setProgressCallback(func: BoolSizeType2Functor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getProgressCallback() -> BoolSizeType2Functor: pass

    ##
    # \brief 
    # \param func 
    #
    def setScoringFunction(func: DoubleSearchHitFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getScoringFunction() -> DoubleSearchHitFunctor: pass

    ##
    # \brief 
    # \param query 
    # \param mol_start_idx 
    # \param mol_end_idx 
    # \return 
    #
    def searchDB(query: FeatureContainer, mol_start_idx: int = 0, mol_end_idx: int = 0) -> int: pass

    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    # \brief 
    #
    dbAcccessor = property(getDbAcccessor, setDbAcccessor)

    hitCallback = property(getHitCallback, setHitCallback)

    progressCallback = property(getProgressCallback, setProgressCallback)

    scoringFunction = property(getScoringFunction, setScoringFunction)

    hitReportMode = property(getHitReportMode, setHitReportMode)

    maxNumOmittedFeatures = property(getMaxNumOmittedFeatures, setMaxNumOmittedFeatures)

    ##
    # \brief FIXME!
    # \brief 
    #
    checkXVolumes = property(getCheckXVolumes, setCheckXVolumes)

    ##
    # \brief FIXME!
    # \brief 
    #
    bestAlignments = property(getBestAlignments, setBestAlignments)
