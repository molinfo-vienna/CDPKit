/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterFunctions.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


namespace CDPL 
{

	namespace Base
	{

		class ControlParameterContainer;
	}

	namespace Biomol 
	{
	
		/**
		 * \addtogroup CDPL_BIOMOL_CONTROL_PARAMETER_FUNCTIONS
		 * @{
		 */
		
		CDPL_BIOMOL_API bool getStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr, bool strict);

		CDPL_BIOMOL_API bool hasStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getCheckLineLengthParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setCheckLineLengthParameter(Base::ControlParameterContainer& cntnr, bool check);

		CDPL_BIOMOL_API bool hasCheckLineLengthParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearCheckLineLengthParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API const ResidueDictionary::SharedPointer& getPDBResidueDictionaryParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setPDBResidueDictionaryParameter(Base::ControlParameterContainer& cntnr, const ResidueDictionary::SharedPointer& dict);

		CDPL_BIOMOL_API bool hasPDBResidueDictionaryParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearPDBResidueDictionaryParameter(Base::ControlParameterContainer& cntnr);


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


		CDPL_BIOMOL_API bool getPDBIgnoreConectRecordsParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setPDBIgnoreConectRecordsParameter(Base::ControlParameterContainer& cntnr, bool ignore);

		CDPL_BIOMOL_API bool hasPDBIgnoreConectRecordsParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearPDBIgnoreConectRecordsParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getPDBDeduceBondOrdersFromCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setPDBDeduceBondOrdersFromCONECTRecordsParameter(Base::ControlParameterContainer& cntnr, bool deduce);

		CDPL_BIOMOL_API bool hasPDBDeduceBondOrdersFromCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearPDBDeduceBondOrdersFromCONECTRecordsParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getPDBIgnoreFormalChargeFieldParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setPDBIgnoreFormalChargeFieldParameter(Base::ControlParameterContainer& cntnr, bool ignore);

		CDPL_BIOMOL_API bool hasPDBIgnoreFormalChargeFieldParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearPDBIgnoreFormalChargeFieldParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getPDBApplyDictFormalAtomChargesParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setPDBApplyDictFormalAtomChargesParameter(Base::ControlParameterContainer& cntnr, bool apply);

		CDPL_BIOMOL_API bool hasPDBApplyDictFormalAtomChargesParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearPDBApplyDictFormalAtomChargesParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getPDBApplyDictAtomTypesParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setPDBApplyDictAtomTypesParameter(Base::ControlParameterContainer& cntnr, bool apply);

		CDPL_BIOMOL_API bool hasPDBApplyDictAtomTypesParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearPDBApplyDictAtomTypesParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getPDBCalcMissingFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setPDBCalcMissingFormalChargesParameter(Base::ControlParameterContainer& cntnr, bool calc);

		CDPL_BIOMOL_API bool hasPDBCalcMissingFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearPDBCalcMissingFormalChargesParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getPDBPerceiveMissingBondOrdersParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setPDBPerceiveMissingBondOrdersParameter(Base::ControlParameterContainer& cntnr, bool perceive);

		CDPL_BIOMOL_API bool hasPDBPerceiveMissingBondOrdersParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearPDBPerceiveMissingBondOrdersParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getPDBEvaluateMASTERRecordParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setPDBEvaluateMASTERRecordParameter(Base::ControlParameterContainer& cntnr, bool eval);

		CDPL_BIOMOL_API bool hasPDBEvaluateMASTERRecordParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearPDBEvaluateMASTERRecordParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getPDBTruncateLinesParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setPDBTruncateLinesParameter(Base::ControlParameterContainer& cntnr, bool trunc);

		CDPL_BIOMOL_API bool hasPDBTruncateLinesParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearPDBTruncateLinesParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getPDBWriteFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setPDBWriteFormalChargesParameter(Base::ControlParameterContainer& cntnr, bool write);

		CDPL_BIOMOL_API bool hasPDBWriteFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearPDBWriteFormalChargesParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getPDBWriteCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setPDBWriteCONECTRecordsParameter(Base::ControlParameterContainer& cntnr, bool write);

		CDPL_BIOMOL_API bool hasPDBWriteCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearPDBWriteCONECTRecordsParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getPDBWriteCONECTRecordsForAllBondsParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setPDBWriteCONECTRecordsForAllBondsParameter(Base::ControlParameterContainer& cntnr, bool write);

		CDPL_BIOMOL_API bool hasPDBWriteCONECTRecordsForAllBondsParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearPDBWriteCONECTRecordsForAllBondsParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getPDBWriteCONECTRecordsReflectingBondOrderParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setPDBWriteCONECTRecordsReflectingBondOrderParameter(Base::ControlParameterContainer& cntnr, bool write);

		CDPL_BIOMOL_API bool hasPDBWriteCONECTRecordsReflectingBondOrderParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearPDBWriteCONECTRecordsReflectingBondOrderParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getCombineInterferingResidueCoordinatesParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setCombineInterferingResidueCoordinatesParameter(Base::ControlParameterContainer& cntnr, bool comb);

		CDPL_BIOMOL_API bool hasCombineInterferingResidueCoordinatesParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearCombineInterferingResidueCoordinatesParameter(Base::ControlParameterContainer& cntnr);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_BIOMOL_CONTROLPARAMETERFUNCTIONS_HPP
 
