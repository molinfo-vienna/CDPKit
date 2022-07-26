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
        # \param self The \e %SearchHit instance to initialize.
        # \param hit_prov 
        # \param qry_pharm 
        # \param hit_pharm 
        # \param mol 
        # \param xform 
        # \param pharm_idx 
        # \param mol_idx 
        # \param conf_idx 
        #
        def __init__(self: object, hit_prov: ScreeningProcessor, qry_pharm: FeatureContainer, hit_pharm: FeatureContainer, mol: CDPL.Chem.Molecule, xform: CDPL.Math.Matrix4D, pharm_idx: int, mol_idx: int, conf_idx: int) -> None: pass

        ##
        # \brief Initializes the \e %SearchHit instance.
        # \param self The \e %SearchHit instance to initialize.
        # \param hit 
        #
        def __init__(self: object, hit: SearchHit) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %SearchHit instance this method is called upon.
        #
        # Different Python \e %SearchHit instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SearchHit instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: SearchHit) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %SearchHit instance \a hit.
        # \param self The \e %SearchHit instance this method is called upon.
        # \param hit The \e %SearchHit instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: SearchHit, hit: SearchHit) -> SearchHit: pass

        ##
        # \brief 
        # \param self The \e %SearchHit instance this method is called upon.
        # \return 
        #
        def getHitProvider(self: SearchHit) -> ScreeningProcessor: pass

        ##
        # \brief 
        # \param self The \e %SearchHit instance this method is called upon.
        # \return 
        #
        def getQueryPharmacophore(self: SearchHit) -> FeatureContainer: pass

        ##
        # \brief 
        # \param self The \e %SearchHit instance this method is called upon.
        # \return 
        #
        def getHitPharmacophore(self: SearchHit) -> FeatureContainer: pass

        ##
        # \brief 
        # \param self The \e %SearchHit instance this method is called upon.
        # \return 
        #
        def getHitMolecule(self: SearchHit) -> CDPL.Chem.Molecule: pass

        ##
        # \brief 
        # \param self The \e %SearchHit instance this method is called upon.
        # \return 
        #
        def getHitAlignmentTransform(self: SearchHit) -> CDPL.Math.Matrix4D: pass

        ##
        # \brief 
        # \param self The \e %SearchHit instance this method is called upon.
        # \return 
        #
        def getHitPharmacophoreIndex(self: SearchHit) -> int: pass

        ##
        # \brief 
        # \param self The \e %SearchHit instance this method is called upon.
        # \return 
        #
        def getHitMoleculeIndex(self: SearchHit) -> int: pass

        ##
        # \brief 
        # \param self The \e %SearchHit instance this method is called upon.
        # \return 
        #
        def getHitConformationIndex(self: SearchHit) -> int: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        hitProvider = property(getHitProvider)

        ##
        # \brief 
        #
        queryPharmacophore = property(getQueryPharmacophore)

        ##
        # \brief 
        #
        hitPharmacophore = property(getHitPharmacophore)

        ##
        # \brief 
        #
        hitMolecule = property(getHitMolecule)

        ##
        # \brief 
        #
        hitAlignmentTransform = property(getHitAlignmentTransform)

        ##
        # \brief 
        #
        hitPharmacophoreIndex = property(getHitPharmacophoreIndex)

        ##
        # \brief 
        #
        hitMoleculeIndex = property(getHitMoleculeIndex)

        ##
        # \brief 
        #
        hitConformationIndex = property(getHitConformationIndex)

    ##
    # \brief Initializes the \e %ScreeningProcessor instance.
    # \param self The \e %ScreeningProcessor instance to initialize.
    # \param db_acc 
    #
    def __init__(self: object, db_acc: ScreeningDBAccessor) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    #
    # Different Python \e %ScreeningProcessor instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ScreeningProcessor instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: ScreeningProcessor) -> int: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \param db_acc 
    #
    def setDBAccessor(self: ScreeningProcessor, db_acc: ScreeningDBAccessor) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \return 
    #
    def getDBAccessor(self: ScreeningProcessor) -> ScreeningDBAccessor: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \param mode 
    #
    def setHitReportMode(self: ScreeningProcessor, mode: HitReportMode) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \return 
    #
    def getHitReportMode(self: ScreeningProcessor) -> HitReportMode: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \param max_num 
    #
    def setMaxNumOmittedFeatures(self: ScreeningProcessor, max_num: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \return 
    #
    def getMaxNumOmittedFeatures(self: ScreeningProcessor) -> int: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \param check 
    #
    def checkXVolumeClashes(self: ScreeningProcessor, check: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \return 
    #
    def xVolumeClashesChecked(self: ScreeningProcessor) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \param seek_best 
    #
    def seekBestAlignments(self: ScreeningProcessor, seek_best: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \return 
    #
    def bestAlignmentsSeeked(self: ScreeningProcessor) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \param func 
    #
    def setHitCallback(self: ScreeningProcessor, func: BoolSearchHitDoubleFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \return 
    #
    def getHitCallback(self: ScreeningProcessor) -> BoolSearchHitDoubleFunctor: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \param func 
    #
    def setProgressCallback(self: ScreeningProcessor, func: BoolSizeType2Functor) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \return 
    #
    def getProgressCallback(self: ScreeningProcessor) -> BoolSizeType2Functor: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \param func 
    #
    def setScoringFunction(self: ScreeningProcessor, func: DoubleSearchHitFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \return 
    #
    def getScoringFunction(self: ScreeningProcessor) -> DoubleSearchHitFunctor: pass

    ##
    # \brief 
    # \param self The \e %ScreeningProcessor instance this method is called upon.
    # \param query 
    # \param mol_start_idx 
    # \param mol_end_idx 
    # \return 
    #
    def searchDB(self: ScreeningProcessor, query: FeatureContainer, mol_start_idx: int = 0, mol_end_idx: int = 0) -> int: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    dbAcccessor = property(getDbAcccessor, setDbAcccessor)

    ##
    # \brief 
    #
    hitCallback = property(getHitCallback, setHitCallback)

    ##
    # \brief 
    #
    progressCallback = property(getProgressCallback, setProgressCallback)

    ##
    # \brief 
    #
    scoringFunction = property(getScoringFunction, setScoringFunction)

    ##
    # \brief 
    #
    hitReportMode = property(getHitReportMode, setHitReportMode)

    ##
    # \brief 
    #
    maxNumOmittedFeatures = property(getMaxNumOmittedFeatures, setMaxNumOmittedFeatures)

    ##
    # \brief FIXME!
    #
    checkXVolumes = property(getCheckXVolumes, setCheckXVolumes)

    ##
    # \brief FIXME!
    #
    bestAlignments = property(getBestAlignments, setBestAlignments)
