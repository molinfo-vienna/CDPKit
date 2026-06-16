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

        /**
         * \brief Returns the value of the Biomol::ControlParameter::STRICT_ERROR_CHECKING parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         */
        CDPL_BIOMOL_API bool getStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::STRICT_ERROR_CHECKING parameter of \a cntnr to \a strict.
         * \param cntnr The control-parameter container.
         * \param strict \c true to enable strict error checking, and \c false to disable it.
         */
        CDPL_BIOMOL_API void setStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr, bool strict);

        /**
         * \brief Tells whether the Biomol::ControlParameter::STRICT_ERROR_CHECKING parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::STRICT_ERROR_CHECKING parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_BIOMOL_API void clearStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::CHECK_LINE_LENGTH parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         */
        CDPL_BIOMOL_API bool getCheckLineLengthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::CHECK_LINE_LENGTH parameter of \a cntnr to \a check.
         * \param cntnr The control-parameter container.
         * \param check \c true to enable line-length checking, and \c false to disable it.
         */
        CDPL_BIOMOL_API void setCheckLineLengthParameter(Base::ControlParameterContainer& cntnr, bool check);

        /**
         * \brief Tells whether the Biomol::ControlParameter::CHECK_LINE_LENGTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasCheckLineLengthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::CHECK_LINE_LENGTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_BIOMOL_API void clearCheckLineLengthParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::RESIDUE_DICTIONARY parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return A \c const shared pointer to the residue dictionary.
         * \since 1.2
         */
        CDPL_BIOMOL_API const ResidueDictionary::SharedPointer& getResidueDictionaryParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::RESIDUE_DICTIONARY parameter of \a cntnr to \a dict.
         * \param cntnr The control-parameter container.
         * \param dict The new residue dictionary.
         * \since 1.2
         */
        CDPL_BIOMOL_API void setResidueDictionaryParameter(Base::ControlParameterContainer& cntnr, const ResidueDictionary::SharedPointer& dict);

        /**
         * \brief Tells whether the Biomol::ControlParameter::RESIDUE_DICTIONARY parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool hasResidueDictionaryParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::RESIDUE_DICTIONARY parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_BIOMOL_API void clearResidueDictionaryParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::APPLY_DICT_FORMAL_CHARGES parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getApplyDictFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::APPLY_DICT_FORMAL_CHARGES parameter of \a cntnr to \a apply.
         * \param cntnr The control-parameter container.
         * \param apply \c true to apply dictionary-derived formal charges, and \c false if not.
         * \since 1.2
         */
        CDPL_BIOMOL_API void setApplyDictFormalChargesParameter(Base::ControlParameterContainer& cntnr, bool apply);

        /**
         * \brief Tells whether the Biomol::ControlParameter::APPLY_DICT_FORMAL_CHARGES parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool hasApplyDictFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::APPLY_DICT_FORMAL_CHARGES parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_BIOMOL_API void clearApplyDictFormalChargesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::APPLY_DICT_ATOM_TYPES parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getApplyDictAtomTypesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::APPLY_DICT_ATOM_TYPES parameter of \a cntnr to \a apply.
         * \param cntnr The control-parameter container.
         * \param apply \c true to apply dictionary-derived atom types, and \c false if not.
         * \since 1.2
         */
        CDPL_BIOMOL_API void setApplyDictAtomTypesParameter(Base::ControlParameterContainer& cntnr, bool apply);

        /**
         * \brief Tells whether the Biomol::ControlParameter::APPLY_DICT_ATOM_TYPES parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool hasApplyDictAtomTypesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::APPLY_DICT_ATOM_TYPES parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_BIOMOL_API void clearApplyDictAtomTypesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::CALC_MISSING_FORMAL_CHARGES parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getCalcMissingFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::CALC_MISSING_FORMAL_CHARGES parameter of \a cntnr to \a calc.
         * \param cntnr The control-parameter container.
         * \param calc \c true to calculate missing formal charges, and \c false to leave them unset.
         * \since 1.2
         */
        CDPL_BIOMOL_API void setCalcMissingFormalChargesParameter(Base::ControlParameterContainer& cntnr, bool calc);

        /**
         * \brief Tells whether the Biomol::ControlParameter::CALC_MISSING_FORMAL_CHARGES parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool hasCalcMissingFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::CALC_MISSING_FORMAL_CHARGES parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_BIOMOL_API void clearCalcMissingFormalChargesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PERCEIVE_MISSING_BOND_ORDERS parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getPerceiveMissingBondOrdersParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PERCEIVE_MISSING_BOND_ORDERS parameter of \a cntnr to \a perceive.
         * \param cntnr The control-parameter container.
         * \param perceive \c true to perceive missing bond orders, and \c false to leave them unset.
         * \since 1.2
         */
        CDPL_BIOMOL_API void setPerceiveMissingBondOrdersParameter(Base::ControlParameterContainer& cntnr, bool perceive);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PERCEIVE_MISSING_BOND_ORDERS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool hasPerceiveMissingBondOrdersParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PERCEIVE_MISSING_BOND_ORDERS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_BIOMOL_API void clearPerceiveMissingBondOrdersParameter(Base::ControlParameterContainer& cntnr);
        
        /**
         * \brief Returns the value of the Biomol::ControlParameter::COMBINE_INTERFERING_RESIDUE_COORDINATES parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         */
        CDPL_BIOMOL_API bool getCombineInterferingResidueCoordinatesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::COMBINE_INTERFERING_RESIDUE_COORDINATES parameter of \a cntnr to \a comb.
         * \param cntnr The control-parameter container.
         * \param comb \c true to merge interfering residue conformers, and \c false to keep them separate.
         */
        CDPL_BIOMOL_API void setCombineInterferingResidueCoordinatesParameter(Base::ControlParameterContainer& cntnr, bool comb);

        /**
         * \brief Tells whether the Biomol::ControlParameter::COMBINE_INTERFERING_RESIDUE_COORDINATES parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasCombineInterferingResidueCoordinatesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::COMBINE_INTERFERING_RESIDUE_COORDINATES parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_BIOMOL_API void clearCombineInterferingResidueCoordinatesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         */
        CDPL_BIOMOL_API bool getPDBApplyDictAtomBondingToStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES parameter of \a cntnr to \a apply.
         * \param cntnr The control-parameter container.
         * \param apply \c true to apply dictionary-derived atom-bonding information to standard residues, and \c false if not.
         */
        CDPL_BIOMOL_API void setPDBApplyDictAtomBondingToStdResiduesParameter(Base::ControlParameterContainer& cntnr, bool apply);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasPDBApplyDictAtomBondingToStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_BIOMOL_API void clearPDBApplyDictAtomBondingToStdResiduesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         */
        CDPL_BIOMOL_API bool getPDBApplyDictAtomBondingToNonStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES parameter of \a cntnr to \a apply.
         * \param cntnr The control-parameter container.
         * \param apply \c true to apply dictionary-derived atom-bonding information to non-standard residues, and \c false if not.
         */
        CDPL_BIOMOL_API void setPDBApplyDictAtomBondingToNonStdResiduesParameter(Base::ControlParameterContainer& cntnr, bool apply);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasPDBApplyDictAtomBondingToNonStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_BIOMOL_API void clearPDBApplyDictAtomBondingToNonStdResiduesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PDB_APPLY_DICT_BOND_ORDERS_TO_STD_RESIDUES parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         */
        CDPL_BIOMOL_API bool getPDBApplyDictBondOrdersToStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PDB_APPLY_DICT_BOND_ORDERS_TO_STD_RESIDUES parameter of \a cntnr to \a apply.
         * \param cntnr The control-parameter container.
         * \param apply \c true to apply dictionary-derived bond order information to standard residues, and \c false if not.
         */
        CDPL_BIOMOL_API void setPDBApplyDictBondOrdersToStdResiduesParameter(Base::ControlParameterContainer& cntnr, bool apply);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PDB_APPLY_DICT_BOND_ORDERS_TO_STD_RESIDUES parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasPDBApplyDictBondOrdersToStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PDB_APPLY_DICT_BOND_ORDERS_TO_STD_RESIDUES parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_BIOMOL_API void clearPDBApplyDictBondOrdersToStdResiduesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         */
        CDPL_BIOMOL_API bool getPDBApplyDictBondOrdersToNonStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES parameter of \a cntnr to \a apply.
         * \param cntnr The control-parameter container.
         * \param apply \c true to apply dictionary-derived bond order information to non-standard residues, and \c false if not.
         */
        CDPL_BIOMOL_API void setPDBApplyDictBondOrdersToNonStdResiduesParameter(Base::ControlParameterContainer& cntnr, bool apply);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasPDBApplyDictBondOrdersToNonStdResiduesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_BIOMOL_API void clearPDBApplyDictBondOrdersToNonStdResiduesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PDB_IGNORE_CONECT_RECORDS parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         * \since 1.3
         */
        CDPL_BIOMOL_API bool getPDBIgnoreCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PDB_IGNORE_CONECT_RECORDS parameter of \a cntnr to \a ignore.
         * \param cntnr The control-parameter container.
         * \param ignore \c true to ignore \c CONECT records during \e PDB data input, and \c false to process them.
         * \since 1.3
         */
        CDPL_BIOMOL_API void setPDBIgnoreCONECTRecordsParameter(Base::ControlParameterContainer& cntnr, bool ignore);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PDB_IGNORE_CONECT_RECORDS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.3
         */
        CDPL_BIOMOL_API bool hasPDBIgnoreCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PDB_IGNORE_CONECT_RECORDS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.3
         */
        CDPL_BIOMOL_API void clearPDBIgnoreCONECTRecordsParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         */
        CDPL_BIOMOL_API bool getPDBDeduceBondOrdersFromCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS parameter of \a cntnr to \a deduce.
         * \param cntnr The control-parameter container.
         * \param deduce \c true to deduce bond orders from the duplication pattern of bonded atom pairs in \c CONECT records, and \c false to skip the deduction.
         */
        CDPL_BIOMOL_API void setPDBDeduceBondOrdersFromCONECTRecordsParameter(Base::ControlParameterContainer& cntnr, bool deduce);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasPDBDeduceBondOrdersFromCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_BIOMOL_API void clearPDBDeduceBondOrdersFromCONECTRecordsParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PDB_IGNORE_FORMAL_CHARGE_FIELD parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         */
        CDPL_BIOMOL_API bool getPDBIgnoreFormalChargeFieldParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PDB_IGNORE_FORMAL_CHARGE_FIELD parameter of \a cntnr to \a ignore.
         * \param cntnr The control-parameter container.
         * \param ignore \c true to ignore the formal charge field of <tt>ATOM/HETATM</tt> records, and \c false to honor it.
         */
        CDPL_BIOMOL_API void setPDBIgnoreFormalChargeFieldParameter(Base::ControlParameterContainer& cntnr, bool ignore);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PDB_IGNORE_FORMAL_CHARGE_FIELD parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasPDBIgnoreFormalChargeFieldParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PDB_IGNORE_FORMAL_CHARGE_FIELD parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_BIOMOL_API void clearPDBIgnoreFormalChargeFieldParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PDB_EVALUATE_MASTER_RECORD parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         */
        CDPL_BIOMOL_API bool getPDBEvaluateMASTERRecordParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PDB_EVALUATE_MASTER_RECORD parameter of \a cntnr to \a eval.
         * \param cntnr The control-parameter container.
         * \param eval \c true to verify record counts against the \e PDB \c MASTER record, and \c false to skip the verification.
         */
        CDPL_BIOMOL_API void setPDBEvaluateMASTERRecordParameter(Base::ControlParameterContainer& cntnr, bool eval);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PDB_EVALUATE_MASTER_RECORD parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasPDBEvaluateMASTERRecordParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PDB_EVALUATE_MASTER_RECORD parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_BIOMOL_API void clearPDBEvaluateMASTERRecordParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PDB_TRUNCATE_LINES parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         */
        CDPL_BIOMOL_API bool getPDBTruncateLinesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PDB_TRUNCATE_LINES parameter of \a cntnr to \a trunc.
         * \param cntnr The control-parameter container.
         * \param trunc \c true to truncate output \e PDB data lines exceeding the maximum allowed line length, and \c false to not truncate them.
         */
        CDPL_BIOMOL_API void setPDBTruncateLinesParameter(Base::ControlParameterContainer& cntnr, bool trunc);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PDB_TRUNCATE_LINES parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasPDBTruncateLinesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PDB_TRUNCATE_LINES parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_BIOMOL_API void clearPDBTruncateLinesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PDB_OUTPUT_FORMAL_CHARGES parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getPDBOutputFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PDB_OUTPUT_FORMAL_CHARGES parameter of \a cntnr to \a output.
         * \param cntnr The control-parameter container.
         * \param output \c true to write the formal charge field of <tt>ATOM/HETATM</tt> records, and \c false to leave it blank.
         * \since 1.2
         */
        CDPL_BIOMOL_API void setPDBOutputFormalChargesParameter(Base::ControlParameterContainer& cntnr, bool output);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PDB_OUTPUT_FORMAL_CHARGES parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool hasPDBOutputFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PDB_OUTPUT_FORMAL_CHARGES parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_BIOMOL_API void clearPDBOutputFormalChargesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PDB_OUTPUT_CONECT_RECORDS parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getPDBOutputCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PDB_OUTPUT_CONECT_RECORDS parameter of \a cntnr to \a output.
         * \param cntnr The control-parameter container.
         * \param output \c true to write \c CONECT records, and \c false if not.
         * \since 1.2
         */
        CDPL_BIOMOL_API void setPDBOutputCONECTRecordsParameter(Base::ControlParameterContainer& cntnr, bool output);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PDB_OUTPUT_CONECT_RECORDS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool hasPDBOutputCONECTRecordsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PDB_OUTPUT_CONECT_RECORDS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_BIOMOL_API void clearPDBOutputCONECTRecordsParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PDB_OUTPUT_CONECT_RECORDS_FOR_ALL_BONDS parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getPDBOutputCONECTRecordsForAllBondsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PDB_OUTPUT_CONECT_RECORDS_FOR_ALL_BONDS parameter of \a cntnr to \a output.
         * \param cntnr The control-parameter container.
         * \param output \c true to write \c CONECT records for all bonds (and not only for non-standard residue ones),
         *               and \c false to write them only for non-standard residue bonds.
         * \since 1.2
         */
        CDPL_BIOMOL_API void setPDBOutputCONECTRecordsForAllBondsParameter(Base::ControlParameterContainer& cntnr, bool output);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PDB_OUTPUT_CONECT_RECORDS_FOR_ALL_BONDS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool hasPDBOutputCONECTRecordsForAllBondsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PDB_OUTPUT_CONECT_RECORDS_FOR_ALL_BONDS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_BIOMOL_API void clearPDBOutputCONECTRecordsForAllBondsParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PDB_OUTPUT_CONECT_RECORDS_REFLECTING_BOND_ORDER parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getPDBOutputCONECTRecordsReflectingBondOrderParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PDB_OUTPUT_CONECT_RECORDS_REFLECTING_BOND_ORDER parameter of \a cntnr to \a output.
         * \param cntnr The control-parameter container.
         * \param output \c true to encode the bond order via the duplication count of bonded atom pairs in \c CONECT records, and \c false to emit each pair only once.
         * \since 1.2
         */
        CDPL_BIOMOL_API void setPDBOutputCONECTRecordsReflectingBondOrderParameter(Base::ControlParameterContainer& cntnr, bool output);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PDB_OUTPUT_CONECT_RECORDS_REFLECTING_BOND_ORDER parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool hasPDBOutputCONECTRecordsReflectingBondOrderParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PDB_OUTPUT_CONECT_RECORDS_REFLECTING_BOND_ORDER parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_BIOMOL_API void clearPDBOutputCONECTRecordsReflectingBondOrderParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::PDB_FORMAT_VERSION parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The \e PDB format version (see Biomol::PDBFormatVersion).
         */
        CDPL_BIOMOL_API unsigned int getPDBFormatVersionParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::PDB_FORMAT_VERSION parameter of \a cntnr to \a ver.
         * \param cntnr The control-parameter container.
         * \param ver The new \e PDB format version (see Biomol::PDBFormatVersion).
         */
        CDPL_BIOMOL_API void setPDBFormatVersionParameter(Base::ControlParameterContainer& cntnr, unsigned int ver);

        /**
         * \brief Tells whether the Biomol::ControlParameter::PDB_FORMAT_VERSION parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasPDBFormatVersionParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::PDB_FORMAT_VERSION parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_BIOMOL_API void clearPDBFormatVersionParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::MMCIF_APPLY_DICT_ATOM_BONDING parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getMMCIFApplyDictAtomBondingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::MMCIF_APPLY_DICT_ATOM_BONDING parameter of \a cntnr to \a apply.
         * \param cntnr The control-parameter container.
         * \param apply \c true to apply dictionary-derived atom-bonding information during \e mmCIF input, and \c false if not.
         * \since 1.2
         */
        CDPL_BIOMOL_API void setMMCIFApplyDictAtomBondingParameter(Base::ControlParameterContainer& cntnr, bool apply);

        /**
         * \brief Tells whether the Biomol::ControlParameter::MMCIF_APPLY_DICT_ATOM_BONDING parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool hasMMCIFApplyDictAtomBondingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::MMCIF_APPLY_DICT_ATOM_BONDING parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_BIOMOL_API void clearMMCIFApplyDictAtomBondingParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::MMCIF_APPLY_DICT_BOND_ORDERS parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getMMCIFApplyDictBondOrdersParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::MMCIF_APPLY_DICT_BOND_ORDERS parameter of \a cntnr to \a apply.
         * \param cntnr The control-parameter container.
         * \param apply \c true to apply dictionary-derived bond order information during \e mmCIF input, and \c false if not.
         * \since 1.2
         */
        CDPL_BIOMOL_API void setMMCIFApplyDictBondOrdersParameter(Base::ControlParameterContainer& cntnr, bool apply);

        /**
         * \brief Tells whether the Biomol::ControlParameter::MMCIF_APPLY_DICT_BOND_ORDERS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool hasMMCIFApplyDictBondOrdersParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::MMCIF_APPLY_DICT_BOND_ORDERS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_BIOMOL_API void clearMMCIFApplyDictBondOrdersParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The value of the parameter.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool getMMCIFOutputBiopolymersAsChemCompParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP parameter of \a cntnr to \a output.
         * \param cntnr The control-parameter container.
         * \param output \c true if explicit residue structures shall be emitted as \c chem_comp category data, and \c false if not.
         * \since 1.2
         */
        CDPL_BIOMOL_API void setMMCIFOutputBiopolymersAsChemCompParameter(Base::ControlParameterContainer& cntnr, bool output);

        /**
         * \brief Tells whether the Biomol::ControlParameter::MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool hasMMCIFOutputBiopolymersAsChemCompParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_BIOMOL_API void clearMMCIFOutputBiopolymersAsChemCompParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Biomol::ControlParameter::MMCIF_OUTPUT_DATA_POSTPROC_FUNCTION parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return A \c const reference to the \e mmCIF output data postprocessing function.
         * \since 1.2
         */
        CDPL_BIOMOL_API const MMCIFDataProcessingFunction& getMMCIFOutputDataPostprocFunctionParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Biomol::ControlParameter::MMCIF_OUTPUT_DATA_POSTPROC_FUNCTION parameter of \a cntnr to \a func.
         * \param cntnr The control-parameter container.
         * \param func The new \e mmCIF output data postprocessing function.
         * \since 1.2
         */
        CDPL_BIOMOL_API void setMMCIFOutputDataPostprocFunctionParameter(Base::ControlParameterContainer& cntnr, const MMCIFDataProcessingFunction& func);

        /**
         * \brief Tells whether the Biomol::ControlParameter::MMCIF_OUTPUT_DATA_POSTPROC_FUNCTION parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_BIOMOL_API bool hasMMCIFOutputDataPostprocFunctionParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Biomol::ControlParameter::MMCIF_OUTPUT_DATA_POSTPROC_FUNCTION parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_BIOMOL_API void clearMMCIFOutputDataPostprocFunctionParameter(Base::ControlParameterContainer& cntnr);

    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_CONTROLPARAMETERFUNCTIONS_HPP
