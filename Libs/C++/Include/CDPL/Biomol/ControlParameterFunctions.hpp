/* 
 * ControlParameterFunctions.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * \file
 * \brief Declaration of convenience functions for control-parameter handling.
 */

#ifndef CDPL_BIOMOL_CONTROLPARAMETERFUNCTIONS_HPP
#define CDPL_BIOMOL_CONTROLPARAMETERFUNCTIONS_HPP

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Biomol/ResidueDictionary.hpp"
#include "CDPL/Biomol/MMCIFDataProcessingFunction.hpp"


namespace CDPL
{

    namespace Base
    {

        class ControlParameterContainer;
    }

    namespace Biomol
    {

        CDPL_BIOMOL_API bool getStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr, bool strict);

        CDPL_BIOMOL_API bool hasStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr);


        CDPL_BIOMOL_API bool getCheckLineLengthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setCheckLineLengthParameter(Base::ControlParameterContainer& cntnr, bool check);

        CDPL_BIOMOL_API bool hasCheckLineLengthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearCheckLineLengthParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \since 1.2
         */
        CDPL_BIOMOL_API const ResidueDictionary::SharedPointer& getResidueDictionaryParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setResidueDictionaryParameter(Base::ControlParameterContainer& cntnr, const ResidueDictionary::SharedPointer& dict);

        CDPL_BIOMOL_API bool hasResidueDictionaryParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearResidueDictionaryParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getApplyDictFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setApplyDictFormalChargesParameter(Base::ControlParameterContainer& cntnr, bool apply);

        CDPL_BIOMOL_API bool hasApplyDictFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearApplyDictFormalChargesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getApplyDictAtomTypesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setApplyDictAtomTypesParameter(Base::ControlParameterContainer& cntnr, bool apply);

        CDPL_BIOMOL_API bool hasApplyDictAtomTypesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearApplyDictAtomTypesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getCalcMissingFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setCalcMissingFormalChargesParameter(Base::ControlParameterContainer& cntnr, bool calc);

        CDPL_BIOMOL_API bool hasCalcMissingFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearCalcMissingFormalChargesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getPerceiveMissingBondOrdersParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPerceiveMissingBondOrdersParameter(Base::ControlParameterContainer& cntnr, bool perceive);

        CDPL_BIOMOL_API bool hasPerceiveMissingBondOrdersParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPerceiveMissingBondOrdersParameter(Base::ControlParameterContainer& cntnr);

        
        CDPL_BIOMOL_API bool getCombineInterferingResidueCoordinatesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setCombineInterferingResidueCoordinatesParameter(Base::ControlParameterContainer& cntnr, bool comb);

        CDPL_BIOMOL_API bool hasCombineInterferingResidueCoordinatesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearCombineInterferingResidueCoordinatesParameter(Base::ControlParameterContainer& cntnr);

        
        CDPL_BIOMOL_API bool getPDBApplyDictAtomBondingToStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPDBApplyDictAtomBondingToStdResiduesParameter(Base::ControlParameterContainer& cntnr, bool apply);

        CDPL_BIOMOL_API bool hasPDBApplyDictAtomBondingToStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPDBApplyDictAtomBondingToStdResiduesParameter(Base::ControlParameterContainer& cntnr);


        CDPL_BIOMOL_API bool getPDBApplyDictAtomBondingToNonStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPDBApplyDictAtomBondingToNonStdResiduesParameter(Base::ControlParameterContainer& cntnr, bool apply);

        CDPL_BIOMOL_API bool hasPDBApplyDictAtomBondingToNonStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPDBApplyDictAtomBondingToNonStdResiduesParameter(Base::ControlParameterContainer& cntnr);


        CDPL_BIOMOL_API bool getPDBApplyDictBondOrdersToStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPDBApplyDictBondOrdersToStdResiduesParameter(Base::ControlParameterContainer& cntnr, bool apply);

        CDPL_BIOMOL_API bool hasPDBApplyDictBondOrdersToStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPDBApplyDictBondOrdersToStdResiduesParameter(Base::ControlParameterContainer& cntnr);


        CDPL_BIOMOL_API bool getPDBApplyDictBondOrdersToNonStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPDBApplyDictBondOrdersToNonStdResiduesParameter(Base::ControlParameterContainer& cntnr, bool apply);

        CDPL_BIOMOL_API bool hasPDBApplyDictBondOrdersToNonStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPDBApplyDictBondOrdersToNonStdResiduesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \since 1.3
         */
        CDPL_BIOMOL_API bool getPDBIgnoreCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPDBIgnoreCONECTRecordsParameter(Base::ControlParameterContainer& cntnr, bool ignore);

        CDPL_BIOMOL_API bool hasPDBIgnoreCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPDBIgnoreCONECTRecordsParameter(Base::ControlParameterContainer& cntnr);


        CDPL_BIOMOL_API bool getPDBDeduceBondOrdersFromCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPDBDeduceBondOrdersFromCONECTRecordsParameter(Base::ControlParameterContainer& cntnr, bool deduce);

        CDPL_BIOMOL_API bool hasPDBDeduceBondOrdersFromCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPDBDeduceBondOrdersFromCONECTRecordsParameter(Base::ControlParameterContainer& cntnr);


        CDPL_BIOMOL_API bool getPDBIgnoreFormalChargeFieldParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPDBIgnoreFormalChargeFieldParameter(Base::ControlParameterContainer& cntnr, bool ignore);

        CDPL_BIOMOL_API bool hasPDBIgnoreFormalChargeFieldParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPDBIgnoreFormalChargeFieldParameter(Base::ControlParameterContainer& cntnr);


        CDPL_BIOMOL_API bool getPDBEvaluateMASTERRecordParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPDBEvaluateMASTERRecordParameter(Base::ControlParameterContainer& cntnr, bool eval);

        CDPL_BIOMOL_API bool hasPDBEvaluateMASTERRecordParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPDBEvaluateMASTERRecordParameter(Base::ControlParameterContainer& cntnr);


        CDPL_BIOMOL_API bool getPDBTruncateLinesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPDBTruncateLinesParameter(Base::ControlParameterContainer& cntnr, bool trunc);

        CDPL_BIOMOL_API bool hasPDBTruncateLinesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPDBTruncateLinesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getPDBOutputFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPDBOutputFormalChargesParameter(Base::ControlParameterContainer& cntnr, bool output);

        CDPL_BIOMOL_API bool hasPDBOutputFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPDBOutputFormalChargesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getPDBOutputCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPDBOutputCONECTRecordsParameter(Base::ControlParameterContainer& cntnr, bool output);

        CDPL_BIOMOL_API bool hasPDBOutputCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPDBOutputCONECTRecordsParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getPDBOutputCONECTRecordsForAllBondsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPDBOutputCONECTRecordsForAllBondsParameter(Base::ControlParameterContainer& cntnr, bool output);

        CDPL_BIOMOL_API bool hasPDBOutputCONECTRecordsForAllBondsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPDBOutputCONECTRecordsForAllBondsParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getPDBOutputCONECTRecordsReflectingBondOrderParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPDBOutputCONECTRecordsReflectingBondOrderParameter(Base::ControlParameterContainer& cntnr, bool output);

        CDPL_BIOMOL_API bool hasPDBOutputCONECTRecordsReflectingBondOrderParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPDBOutputCONECTRecordsReflectingBondOrderParameter(Base::ControlParameterContainer& cntnr);


        CDPL_BIOMOL_API unsigned int getPDBFormatVersionParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setPDBFormatVersionParameter(Base::ControlParameterContainer& cntnr, unsigned int ver);

        CDPL_BIOMOL_API bool hasPDBFormatVersionParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearPDBFormatVersionParameter(Base::ControlParameterContainer& cntnr);
        
        /**
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getMMCIFApplyDictAtomBondingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setMMCIFApplyDictAtomBondingParameter(Base::ControlParameterContainer& cntnr, bool apply);

        CDPL_BIOMOL_API bool hasMMCIFApplyDictAtomBondingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearMMCIFApplyDictAtomBondingParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getMMCIFApplyDictBondOrdersParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setMMCIFApplyDictBondOrdersParameter(Base::ControlParameterContainer& cntnr, bool apply);

        CDPL_BIOMOL_API bool hasMMCIFApplyDictBondOrdersParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearMMCIFApplyDictBondOrdersParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getMMCIFOutputBiopolymersAsChemCompParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setMMCIFOutputBiopolymersAsChemCompParameter(Base::ControlParameterContainer& cntnr, bool output);

        CDPL_BIOMOL_API bool hasMMCIFOutputBiopolymersAsChemCompParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearMMCIFOutputBiopolymersAsChemCompParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \since 1.2
         */
        CDPL_BIOMOL_API const MMCIFDataProcessingFunction& getMMCIFOutputDataPostprocFunctionParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void setMMCIFOutputDataPostprocFunctionParameter(Base::ControlParameterContainer& cntnr, const MMCIFDataProcessingFunction& func);

        CDPL_BIOMOL_API bool hasMMCIFOutputDataPostprocFunctionParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_BIOMOL_API void clearMMCIFOutputDataPostprocFunctionParameter(Base::ControlParameterContainer& cntnr);

    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_CONTROLPARAMETERFUNCTIONS_HPP
