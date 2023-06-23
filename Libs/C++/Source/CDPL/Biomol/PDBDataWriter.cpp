/* 
 * PDBDataWriter.cpp 
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


#include "StaticInit.hpp"

#include <algorithm>
#include <cmath>
#include <set>
#include <functional>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/ControlParameterFunctions.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "PDBDataWriter.hpp"
#include "PDBFormatData.hpp"


using namespace CDPL;


namespace
{

    void writePDBLine(std::ostream& os, const std::string& line, const char* err_msg, 
                             bool check_llen, bool trunc, std::size_t max_llen)
    {
        Internal::writeLine(os, line, err_msg, check_llen, false, trunc, max_llen, Biomol::PDB::END_OF_LINE);
    }

    void writePDBEOL(std::ostream& os)
    {
        Internal::writeEOL(os, Biomol::PDB::END_OF_LINE);
    }

    void writeChar(std::ostream& os, char ch)
    {
        os << ch;
    }

    void writePDBRecordPrefix(std::ostream& os, const std::string& prefix)
    {
        Internal::writeString(os, Biomol::PDB::RECORD_NAME_LENGTH, prefix, ("error while writing " + prefix + " record").c_str(), 
                              false, false, false);
    }

    bool isMandatoryRecord(const std::string& prefix)
    {
        using namespace CDPL;
        using namespace Biomol;

        for (std::size_t i = 0; i < sizeof(PDB::MANDATORY_RECORDS) / sizeof(PDB::MANDATORY_RECORDS[0]); i++) {
            if (prefix == PDB::MANDATORY_RECORDS[i][0])
                return true;
        }

        return false;
    }

    const std::string DEF_RESIDUE_CODE = "UNL";
    const std::string DEF_CHAIN_ID     = "A";
}


bool Biomol::PDBDataWriter::writePDBFileRecord(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
    init(os);
    processAtomSequence(molgraph);
    
    writeTitleSection(os, molgraph);
    writePrimaryStructureSection(os, molgraph);
    writeHeterogenSection(os, molgraph);
    writeSecondaryStructureSection(os, molgraph);
    writeConnAnnotationSection(os, molgraph);
    writeMiscSection(os, molgraph);
    writeCrystAndCoordTransformSection(os, molgraph);
    writeCoordinateSection(os);

    perceiveCONECTRecordBonds(molgraph);

    writeConnectivitySection(os, molgraph);
    writeBookkeepingSection(os);

    return true;
}
        
void Biomol::PDBDataWriter::init(std::ostream& os)
{
    strictErrorChecking          = getStrictErrorCheckingParameter(ioBase); 
    checkLineLength              = getCheckLineLengthParameter(ioBase); 
    truncLines                   = getPDBTruncateLinesParameter(ioBase);
    resDictionary                = getPDBResidueDictionaryParameter(ioBase);
    writeFormCharges             = getPDBWriteFormalChargesParameter(ioBase);
    writeConectRecords           = getPDBWriteCONECTRecordsParameter(ioBase);
    writeConectRecsForAllBonds   = getPDBWriteCONECTRecordsForAllBondsParameter(ioBase);
    writeConectRecsRefBondOrders = getPDBWriteCONECTRecordsReflectingBondOrderParameter(ioBase);

    os.imbue(std::locale::classic());

    atomSequence.clear();
    recordHistogram.clear();
    atomToSerialMap.clear();
    atomToResidueSerialMap.clear();
    conectRecordBonds.clear();
    writtenConectAtomPairs.clear();
    connectedResidueLookup.clear();

    //numWrittenModels = 0;
}

void Biomol::PDBDataWriter::processAtomSequence(const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;
    using namespace std::placeholders;
    
    std::set<std::size_t> model_ids;

    for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
        const Atom& atom = *it;

        atomSequence.push_back(&atom);

        std::size_t model_id = getModelNumber(atom);

        if (model_id != 0)
            model_ids.insert(model_id);
    }

    numModels = model_ids.size();

    std::sort(atomSequence.begin(), atomSequence.end(), std::bind(&PDBDataWriter::atomOrderingFunc, this, _1, _2));
    long res_serial = 1;

    for (AtomList::const_iterator it = atomSequence.begin(), end = atomSequence.end(); it != end; res_serial++) {
        const Atom* first_atom = *it;
        long res_id = (getResidueSequenceNumber(*first_atom) << (sizeof(char) * 8)) + getResidueInsertionCode(*first_atom);
        const std::string& res_code = getResidueCode(*first_atom);

        atomToResidueSerialMap[first_atom] = res_serial; 

        for (++it; it != end; ++it) {
            const Atom* next_atom = *it;
            const std::string& next_res_code = getResidueCode(*next_atom);

            if (next_res_code != res_code)
                break;

            long next_res_id = (getResidueSequenceNumber(*next_atom) << (sizeof(char) * 8)) + getResidueInsertionCode(*next_atom);

            if (next_res_id != res_id)
                break;

            atomToResidueSerialMap[next_atom] = res_serial; 
        }
    }

    for (Chem::MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
        const Bond& bond = *it;
        const Atom& atom1 = bond.getBegin();

        if (!molgraph.containsAtom(atom1))
            continue;

        const Atom& atom2 = bond.getEnd();

        if (!molgraph.containsAtom(atom2))
            continue;

        long res_serial1 = atomToResidueSerialMap[&atom1];
        long res_serial2 = atomToResidueSerialMap[&atom2];

        connectedResidueLookup.insert(SerialPair(res_serial1, res_serial2));
        connectedResidueLookup.insert(SerialPair(res_serial2, res_serial1));
    }
}

void Biomol::PDBDataWriter::perceiveCONECTRecordBonds(const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;

    if (!writeConectRecords)
        return;

    ResDictPointer res_dict = (resDictionary ? resDictionary : ResidueDictionary::get());

    for (Chem::MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
        const Bond& bond = *it;
        const Atom& atom1 = bond.getBegin();

        if (!molgraph.containsAtom(atom1))
            continue;

        const Atom& atom2 = bond.getEnd();

        if (!molgraph.containsAtom(atom2))
            continue;

        if (writeConectRecsForAllBonds) {
            conectRecordBonds.insert(&bond);
            continue;
        }

        long res_serial1 = atomToResidueSerialMap[&atom1];
        long res_serial2 = atomToResidueSerialMap[&atom2];

        const std::string& res_code1 = getResidueCode(atom1);
        const std::string& res_code2 = getResidueCode(atom2);

        if ((res_code1 == PDB::WATER_RES_NAME) && (res_code2 == PDB::WATER_RES_NAME)) { 
            if (res_serial1 == res_serial2)
                continue;
        }

        if (getHeteroAtomFlag(atom1) || getHeteroAtomFlag(atom2)) {
            conectRecordBonds.insert(&bond);
            continue;
        }

        if (res_serial1 == res_serial2) {
            MolecularGraph::SharedPointer tmplt = res_dict->getStructure(res_code1);

            if (tmplt && isStandardBond(bond, *tmplt))
                continue;

        } else if (std::abs(res_serial1 - res_serial2) == 1) {
            MolecularGraph::SharedPointer tmplt1 = res_dict->getStructure(res_code1);
            MolecularGraph::SharedPointer tmplt2 = res_dict->getStructure(res_code2);

            if (tmplt1 && tmplt2 && isLinkingAtom(atom1, *tmplt1) && isLinkingAtom(atom2, *tmplt2))
                continue;
        }

        conectRecordBonds.insert(&bond);
    }
}

bool Biomol::PDBDataWriter::isStandardBond(const Chem::Bond& bond, const Chem::MolecularGraph& tmplt) const
{
    using namespace Chem;

    const Atom* tmplt_atom1 = getResTemplateAtom(bond.getBegin(), tmplt);

    if (!tmplt_atom1)
        return false;

    const Atom* tmplt_atom2 = getResTemplateAtom(bond.getEnd(), tmplt);

    if (!tmplt_atom2)
        return false;

    return (tmplt_atom1->findBondToAtom(*tmplt_atom2) != 0);
}

bool Biomol::PDBDataWriter::isLinkingAtom(const Chem::Atom& atom, const Chem::MolecularGraph& tmplt) const
{
    const Chem::Atom* tmplt_atom = getResTemplateAtom(atom, tmplt);

    if (!tmplt_atom)
        return false;

    return getResidueLinkingAtomFlag(*tmplt_atom);
}

const Chem::Atom* Biomol::PDBDataWriter::getResTemplateAtom(const Chem::Atom& atom, const Chem::MolecularGraph& tmplt) const
{
    using namespace Chem;

    const std::string& atom_name = getResidueAtomName(atom);

    for (MolecularGraph::ConstAtomIterator it = tmplt.getAtomsBegin(), end = tmplt.getAtomsEnd(); it != end; ++it) {
        const Atom& tmplt_atom = *it;

        if (getResidueAtomName(tmplt_atom) == atom_name)
            return &tmplt_atom;

        if (getResidueAltAtomName(tmplt_atom) == atom_name)
            return &tmplt_atom;
    }

    return 0;
}

void Biomol::PDBDataWriter::writeTitleSection(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
    writeGenericDataRecord(os, PDBData::HEADER, molgraph, PDB::HEADER_PREFIX, PDB::HEADER_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::OBSLTE, molgraph, PDB::OBSLTE_PREFIX, PDB::OBSLTE_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::TITLE, molgraph, PDB::TITLE_PREFIX, PDB::TITLE_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::SPLIT, molgraph, PDB::SPLIT_PREFIX, PDB::SPLIT_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::CAVEAT, molgraph, PDB::CAVEAT_PREFIX, PDB::CAVEAT_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::COMPND, molgraph, PDB::COMPND_PREFIX, PDB::COMPND_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::SOURCE, molgraph, PDB::SOURCE_PREFIX, PDB::SOURCE_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::KEYWDS, molgraph, PDB::KEYWDS_PREFIX, PDB::KEYWDS_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::EXPDTA, molgraph, PDB::EXPDTA_PREFIX, PDB::EXPDTA_DATA_LENGTH);

    writeNUMMDLRecord(os);

    writeGenericDataRecord(os, PDBData::AUTHOR, molgraph, PDB::AUTHOR_PREFIX, PDB::AUTHOR_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::REVDAT, molgraph, PDB::REVDAT_PREFIX, PDB::REVDAT_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::SPRSDE, molgraph, PDB::SPRSDE_PREFIX, PDB::SPRSDE_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::JRNL, molgraph, PDB::JRNL_PREFIX, PDB::JRNL_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::REMARK, molgraph, PDB::REMARK_PREFIX, PDB::REMARK_DATA_LENGTH);
}

void Biomol::PDBDataWriter::writePrimaryStructureSection(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
    writeGenericDataRecord(os, PDBData::DBREF, molgraph, PDB::DBREF_PREFIX, PDB::DBREF_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::DBREF1, molgraph, PDB::DBREF1_PREFIX, PDB::DBREF1_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::DBREF2, molgraph, PDB::DBREF2_PREFIX, PDB::DBREF2_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::SEQADV, molgraph, PDB::SEQADV_PREFIX, PDB::SEQADV_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::SEQRES, molgraph, PDB::SEQRES_PREFIX, PDB::SEQRES_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::MODRES, molgraph, PDB::MODRES_PREFIX, PDB::MODRES_DATA_LENGTH);
}

void Biomol::PDBDataWriter::writeHeterogenSection(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
    writeGenericDataRecord(os, PDBData::HET, molgraph, PDB::HET_PREFIX, PDB::HET_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::HETNAM, molgraph, PDB::HETNAM_PREFIX, PDB::HETNAM_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::HETSYN, molgraph, PDB::HETSYN_PREFIX, PDB::HETSYN_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::FORMUL, molgraph, PDB::FORMUL_PREFIX, PDB::FORMUL_DATA_LENGTH);
}

void Biomol::PDBDataWriter::writeSecondaryStructureSection(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
    if (!writeGenericDataRecord(os, PDBData::HELIX, molgraph, PDB::HELIX_PREFIX, PDB::HELIX_DATA_LENGTH))
        writeGenericDataRecord(os, PDBData::TURN, molgraph, PDB::TURN_PREFIX, PDB::TURN_DATA_LENGTH); // obsolete

    writeGenericDataRecord(os, PDBData::SHEET, molgraph, PDB::SHEET_PREFIX, PDB::SHEET_DATA_LENGTH);
}

void Biomol::PDBDataWriter::writeConnAnnotationSection(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
    writeGenericDataRecord(os, PDBData::SSBOND, molgraph, PDB::SSBOND_PREFIX, PDB::SSBOND_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::LINK, molgraph, PDB::LINK_PREFIX, PDB::LINK_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::CISPEP, molgraph, PDB::CISPEP_PREFIX, PDB::CISPEP_DATA_LENGTH);
}

void Biomol::PDBDataWriter::writeMiscSection(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
    writeGenericDataRecord(os, PDBData::SITE, molgraph, PDB::SITE_PREFIX, PDB::SITE_DATA_LENGTH);
}

void Biomol::PDBDataWriter::writeCrystAndCoordTransformSection(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
    writeGenericDataRecord(os, PDBData::CRYST1, molgraph, PDB::CRYST1_PREFIX, PDB::CRYST1_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::ORIGX1, molgraph, PDB::ORIGX1_PREFIX, PDB::ORIGX1_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::ORIGX2, molgraph, PDB::ORIGX2_PREFIX, PDB::ORIGX2_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::ORIGX3, molgraph, PDB::ORIGX3_PREFIX, PDB::ORIGX3_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::SCALE1, molgraph, PDB::SCALE1_PREFIX, PDB::SCALE1_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::SCALE2, molgraph, PDB::SCALE2_PREFIX, PDB::SCALE2_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::SCALE3, molgraph, PDB::SCALE3_PREFIX, PDB::SCALE3_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::MTRIX1, molgraph, PDB::MTRIX1_PREFIX, PDB::MTRIX1_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::MTRIX2, molgraph, PDB::MTRIX2_PREFIX, PDB::MTRIX2_DATA_LENGTH);
    writeGenericDataRecord(os, PDBData::MTRIX3, molgraph, PDB::MTRIX3_PREFIX, PDB::MTRIX3_DATA_LENGTH);
}

void Biomol::PDBDataWriter::writeCoordinateSection(std::ostream& os)
{
    using namespace Chem;

    std::size_t last_model_id = 0;
    long next_serial = 1;
    long last_res_serial = 0;
    std::size_t chain_len = 1;

    for (AtomList::const_iterator it = atomSequence.begin(), end = atomSequence.end(); it != end; ++it) {
        const Atom& atom = **it;
        long res_serial = atomToResidueSerialMap[&atom];
        
        if (last_res_serial != 0 && res_serial != last_res_serial) {
            if (connectedResidueLookup.find(SerialPair(last_res_serial, res_serial)) != connectedResidueLookup.end()) 
                chain_len++;

            else {
                if (chain_len > 1) {
                    const Atom& prev_atom = **(it - 1);

                    writeTERRecord(os, next_serial, prev_atom);

                    next_serial++;
                    recordHistogram[PDB::TER_PREFIX]++;
                }

                chain_len = 1;
            } 
        }

        last_res_serial = res_serial;

        if (numModels > 0) {
            std::size_t model_id = getModelNumber(atom);

            if (model_id != last_model_id) {
                if (last_model_id != 0) {
                    writeENDMDLRecord(os);
                    //numWrittenModels++;
                }

                writeMODELRecord(os, model_id);

                last_model_id = model_id;
                next_serial = 1;
            }
        }

        next_serial = writeATOMRecord(os, next_serial, atom);
    }

    if (chain_len > 1) {
        const Atom& prev_atom = *atomSequence.back();

        writeTERRecord(os, next_serial, prev_atom);
        recordHistogram[PDB::TER_PREFIX]++;
    }

    if (last_model_id != 0) 
        writeENDMDLRecord(os);
}

void Biomol::PDBDataWriter::writeConnectivitySection(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;
    using namespace Internal;

    if (!writeConectRecords)
        return;

    BondSet::const_iterator conect_bonds_end = conectRecordBonds.end();

    for (AtomList::const_iterator it = atomSequence.begin(), end = atomSequence.end(); it != end; ++it) {
        const Atom& atom = **it;
        long serial = atomToSerialMap[&atom];

        nbrAtomSerials.clear();
        
        for (Atom::ConstBondIterator nb_it = atom.getBondsBegin(), nb_end = atom.getBondsEnd(); nb_it != nb_end; ++nb_it) {
            const Bond& bond = *nb_it;

            if (conectRecordBonds.find(&bond) == conect_bonds_end)
                continue;

            const Atom& nbr_atom = bond.getNeighbor(atom);
            long nbr_serial = atomToSerialMap[&nbr_atom];

            if (!writtenConectAtomPairs.insert(SerialPair(serial, nbr_serial)).second)
                continue;

            if (writeConectRecsRefBondOrders) {
                for (std::size_t i = 0, order = getOrder(bond); i < order; i++)
                    nbrAtomSerials.push_back(nbr_serial);
            } else
                nbrAtomSerials.push_back(nbr_serial);
        }

        if (nbrAtomSerials.empty())
            continue;

        std::sort(nbrAtomSerials.begin(), nbrAtomSerials.end());

        for (std::size_t i = 0; i < nbrAtomSerials.size(); i++) {
            if ((i % 4) == 0) {
                if (i != 0)
                    writePDBEOL(os);

                writePDBRecordPrefix(os, PDB::CONECT_PREFIX);
                writeIntegerNumber(os, 5, serial, "PDBDataWriter: error while writing atom serial for CONECT record", false);

                recordHistogram[PDB::CONECT_PREFIX]++;
            }

            writeIntegerNumber(os, 5, nbrAtomSerials[i], "PDBDataWriter: error while writing neighbor atom serial for CONECT record", false);
        }

        writePDBEOL(os);
    }
}

void Biomol::PDBDataWriter::writeBookkeepingSection(std::ostream& os)
{
    using namespace Internal;

    writePDBRecordPrefix(os, PDB::MASTER_PREFIX);
    writeWhitespace(os, 4);
    writeIntegerNumber(os, 5, recordHistogram[PDB::REMARK_PREFIX], "PDBDataWriter: error while writing number for REMARK records for MASTER record", false);
    writeIntegerNumber(os, 5, 0, "PDBDataWriter: error while writing zero field of MASTER record", false);
    writeIntegerNumber(os, 5, recordHistogram[PDB::HET_PREFIX], "PDBDataWriter: error while writing number of HET records for MASTER record", false);
    writeIntegerNumber(os, 5, recordHistogram[PDB::HELIX_PREFIX], "PDBDataWriter: error while writing number of HELIX records for MASTER record", false);
    writeIntegerNumber(os, 5, recordHistogram[PDB::SHEET_PREFIX], "PDBDataWriter: error while writing number of SHEET records for MASTER record", false);
    writeIntegerNumber(os, 5, recordHistogram[PDB::TURN_PREFIX], "PDBDataWriter: error while writing number of TURN records for MASTER record", false);
    writeIntegerNumber(os, 5, recordHistogram[PDB::SITE_PREFIX], "PDBDataWriter: error while writing number of SITE records for MASTER record", false);
    writeIntegerNumber(os, 5, (recordHistogram[PDB::ORIGX1_PREFIX] + recordHistogram[PDB::ORIGX2_PREFIX] + recordHistogram[PDB::ORIGX3_PREFIX] +
                               recordHistogram[PDB::SCALE1_PREFIX] + recordHistogram[PDB::SCALE2_PREFIX] + recordHistogram[PDB::SCALE3_PREFIX] +
                               recordHistogram[PDB::MTRIX1_PREFIX] + recordHistogram[PDB::MTRIX2_PREFIX] + recordHistogram[PDB::MTRIX3_PREFIX]), 
                       "PDBDataWriter: error while writing number of coordinate transformation records for MASTER record", false);
    writeIntegerNumber(os, 5, recordHistogram[PDB::ATOM_PREFIX], "PDBDataWriter: error while writing number of atomic coordinate records for MASTER record", false);
    writeIntegerNumber(os, 5, recordHistogram[PDB::TER_PREFIX], "PDBDataWriter: error while writing number of TER records for MASTER record", false);
    writeIntegerNumber(os, 5, recordHistogram[PDB::CONECT_PREFIX], "PDBDataWriter: error while writing number of CONECT records for MASTER record", false);
    writeIntegerNumber(os, 5, recordHistogram[PDB::SEQRES_PREFIX], "PDBDataWriter: error while writing number of SEQRES records for MASTER record", false);
    writePDBEOL(os);

    writePDBRecordPrefix(os, PDB::END_PREFIX);
    writePDBEOL(os);
}

bool Biomol::PDBDataWriter::writeGenericDataRecord(std::ostream& os, PDBData::RecordType type, const Chem::MolecularGraph& molgraph, 
                                                   const std::string& prefix, std::size_t max_llen)
{
    if (!hasPDBData(molgraph)) {
        if (strictErrorChecking)
            throw Base::IOError("PDBDataWriter: no PDB data found");

        return false;
    }

    const PDBData::SharedPointer& data = getPDBData(molgraph);

    if (!data) {
        if (strictErrorChecking)
            throw Base::IOError("PDBDataWriter: invalid PDB data pointer");

        return false;
    }

    if (!data->containsRecord(type)) {
        if (strictErrorChecking && isMandatoryRecord(prefix))
            throw Base::IOError("PDBDataWriter: missing data for mandatory " + prefix + " record");

        return false;
    }

    typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

    const std::string& rec_data = data->getData(type);

    if (rec_data.empty()) {
        if (strictErrorChecking && isMandatoryRecord(prefix))
            throw Base::IOError("PDBDataWriter: empty data entry for mandatory " + prefix + " record");

        return false;
    }

    Tokenizer tokenizer(rec_data, boost::char_separator<char>("\n", ""));

    for (Tokenizer::iterator it = tokenizer.begin(); it != tokenizer.end(); ++it) {
        writePDBRecordPrefix(os, prefix);
        writePDBLine(os, *it, ("error while writing " + prefix + " data record").c_str(), checkLineLength, truncLines, max_llen);

        recordHistogram[prefix]++;
    }

    return true;
}

long Biomol::PDBDataWriter::writeATOMRecord(std::ostream& os, long serial, const Chem::Atom& atom, std::size_t conf_idx)
{
    using namespace Internal;

    const std::string& rec_prefix = getHeteroAtomFlag(atom) ? PDB::HETATM_PREFIX : PDB::ATOM_PREFIX;

    writePDBRecordPrefix(os, rec_prefix);

    serial = std::max(serial, getSerialNumber(atom));
    
    if (conf_idx == 0)
        atomToSerialMap[&atom] = serial;

    writeIntegerNumber(os, 5, checkSerialNumber(serial),
                       ("PDBDataWriter: error while writing serial number for " + rec_prefix + " record").c_str(), false);
    
    std::string symbol = getSymbol(atom);
    const std::string& name = getResidueAtomName(atom);

    if (strictErrorChecking) {
        if (name.empty())
            throw Base::IOError("PDBDataWriter: while writing " + rec_prefix + " record: length of atom name is zero");

        if (symbol.empty())
            throw Base::IOError("PDBDataWriter: while writing " + rec_prefix + " record: length of atom symbol is zero");
    }

    if (symbol.size() <= 1 && name.size() <= 3) {
        writeWhitespace(os, 2);
        writeString(os, 3, name, ("PDBDataWriter: error while writing atom name for " + rec_prefix + " record").c_str());

    } else {
        writeWhitespace(os, 1);
        writeString(os, 4, name, ("PDBDataWriter: error while writing atom name for " + rec_prefix + " record").c_str(), 
                    !strictErrorChecking, !strictErrorChecking);
    }

    const Math::Vector3D* coords_ptr = 0;
    bool more_confs = false;

    if (has3DCoordinatesArray(atom)) {
        const Math::Vector3DArray& coords_array = *get3DCoordinatesArray(atom);

        if (coords_array.getSize() > 1) {
            coords_ptr = &coords_array[conf_idx];
            more_confs = (conf_idx < 25 && (conf_idx + 1) < coords_array.getSize());

            writeChar(os, 'A' + char(conf_idx));
        }
    }

    if (!coords_ptr) {
        coords_ptr = &get3DCoordinates(atom);

        writeWhitespace(os, 1);
    }

    const std::string& res_code = getResidueCode(atom);

    writeString(os, 3, res_code, ("PDBDataWriter: error while writing residue name for " + rec_prefix + " record").c_str(), 
                !strictErrorChecking, !strictErrorChecking);
    writeWhitespace(os, 1);

    const std::string& chain_id = getChainID(atom);

    if (strictErrorChecking && chain_id.length() > 1)
        throw Base::IOError("PDBDataWriter: while writing " + rec_prefix + " record: length of chain id > 1");
    
    writeChar(os, chain_id.length() >= 1 ? chain_id[0] : ' ');
    writeIntegerNumber(os, 4, checkResidueSequenceNumber(getResidueSequenceNumber(atom)),
                       ("PDBDataWriter: error while writing residue sequence number for " + rec_prefix + " record").c_str(), false);

    char ins_code = getResidueInsertionCode(atom);

    writeChar(os, ins_code == 0 ? ' ' : ins_code);
    writeWhitespace(os, 3);
    
    const Math::Vector3D& coords = *coords_ptr;

    writeFloatNumber(os, 8, 3, coords(0), ("PDBDataWriter: error while writing x-coordinate for " + rec_prefix + " record").c_str());
    writeFloatNumber(os, 8, 3, coords(1), ("PDBDataWriter: error while writing y-coordinate for " + rec_prefix + " record").c_str());
    writeFloatNumber(os, 8, 3, coords(2), ("PDBDataWriter: error while writing z-coordinate for " + rec_prefix + " record").c_str());

    writeFloatNumber(os, 6, 2, getOccupancy(atom), ("PDBDataWriter: error while writing occupancy for " + rec_prefix + " record").c_str());
    writeFloatNumber(os, 6, 2, getBFactor(atom), ("PDBDataWriter: error while writing temperature factor for " + rec_prefix + " record").c_str());
    writeWhitespace(os, 10);

    boost::to_upper(symbol);

    writeString(os, 2, symbol, ("PDBDataWriter: error while writing element symbol for " + rec_prefix + " record").c_str(), 
                true, !strictErrorChecking, true);

    if (writeFormCharges) { 
        long charge = getFormalCharge(atom);

        if (charge != 0) {
            writeIntegerNumber(os, 1, std::abs(charge), ("PDBDataWriter: error while writing formal atom charge for " + rec_prefix + " record").c_str());
            writeChar(os, charge < 0 ? '-' : '+');

        } else
            writeWhitespace(os, 2);
    } else
        writeWhitespace(os, 2);

    writePDBEOL(os);

//    if (numWrittenModels < 1)
    recordHistogram[PDB::ATOM_PREFIX]++;
    
    if (more_confs)
        return writeATOMRecord(os, serial + 1, atom, conf_idx + 1);

    return (serial + 1);
}

void Biomol::PDBDataWriter::writeTERRecord(std::ostream& os, long serial, const Chem::Atom& atom) const
{
    using namespace Internal;

    writePDBRecordPrefix(os, PDB::TER_PREFIX);
    writeIntegerNumber(os, 5, checkSerialNumber(serial),
                       "PDBDataWriter: error while writing serial number for TER record", false);
    writeWhitespace(os, 6);
    writeString(os, 3, getResidueCode(atom), "PDBDataWriter: error while writing residue name for TER record", 
                !strictErrorChecking, !strictErrorChecking);
    writeWhitespace(os, 1);

    const std::string& chain_id = getChainID(atom);

    if (strictErrorChecking && chain_id.length() > 1)
        throw Base::IOError("PDBDataWriter: error while writing chain id for TER record: length of chain id > 1");

    writeChar(os, chain_id.length() >= 1 ? chain_id[0] : ' ');
    writeIntegerNumber(os, 4, checkResidueSequenceNumber(getResidueSequenceNumber(atom)),
                       "PDBDataWriter: error while writing residue sequence number for TER record", false);

    char ins_code = getResidueInsertionCode(atom);

    writeChar(os, ins_code == 0 ? ' ' : ins_code);
    writePDBEOL(os);
}

void Biomol::PDBDataWriter::writeNUMMDLRecord(std::ostream& os) const
{
    using namespace Internal;

    if (numModels == 0)
        return;

    writePDBRecordPrefix(os, PDB::NUMMDL_PREFIX);

    writeWhitespace(os, 4);
    writeIntegerNumber(os, 4, numModels, "error while writing number of models for NUMMDL record", true);

    writePDBEOL(os);
}

void Biomol::PDBDataWriter::writeMODELRecord(std::ostream& os, std::size_t model_id) const
{
    using namespace Internal;

    writePDBRecordPrefix(os, PDB::MODEL_PREFIX);

    writeWhitespace(os, 4);
    writeIntegerNumber(os, 4, model_id, "error while writing MODEL record", false);

    writePDBEOL(os);
}

void Biomol::PDBDataWriter::writeENDMDLRecord(std::ostream& os) const
{
    writePDBRecordPrefix(os, PDB::ENDMDL_PREFIX);
    writePDBEOL(os);
}

long Biomol::PDBDataWriter::checkSerialNumber(long serial_no) const
{
    if (serial_no < 0) {
        if (strictErrorChecking && serial_no < -9999)
            throw Base::IOError("PDBDataWriter: atom serial number out of allowed range");

        return -(std::abs(serial_no) % 10000);
    }

    if (strictErrorChecking && serial_no > 99999)
        throw Base::IOError("PDBDataWriter: atom serial number out of allowed range");

    return (serial_no % 100000);
}

long Biomol::PDBDataWriter::checkResidueSequenceNumber(long seq_no) const
{
    if (seq_no < 0) {
        if (strictErrorChecking && seq_no < -999)
            throw Base::IOError("PDBDataWriter: residue sequence number out of allowed range");

        return -(std::abs(seq_no) % 1000);
    }

    if (strictErrorChecking && seq_no > 9999)
        throw Base::IOError("PDBDataWriter: residue sequence number out of allowed range");

    return (seq_no % 10000);
}

bool Biomol::PDBDataWriter::atomOrderingFunc(const Chem::Atom* atom1, const Chem::Atom* atom2) const
{
    std::size_t model_id1 = getModelNumber(*atom1);
    std::size_t model_id2 = getModelNumber(*atom2);

    if (model_id1 < model_id2)
        return true;

    if (model_id1 > model_id2)
        return false;

    return (getSerialNumber(*atom1) < getSerialNumber(*atom2));
}
/*
long Biomol::PDBDataWriter::getSerialNumber(const Chem::Atom& atom) const
{
    try {
        return Biomol::getSerialNumber(atom);

    } catch (const Base::ItemNotFound& e) {
        if (strictErrorChecking)
            throw Base::IOError("PDBDataWriter: serial number property not found for atom");

        return 1;
    }
}

long Biomol::PDBDataWriter::getResidueSequenceNumber(const Chem::Atom& atom) const
{
    try {
        return Biomol::getResidueSequenceNumber(atom);

    } catch (const Base::ItemNotFound& e) {
        if (strictErrorChecking)
            throw Base::IOError("PDBDataWriter: residue sequence number property not found for atom");

        return 1;
    }
}

char Biomol::PDBDataWriter::getResidueInsertionCode(const Chem::Atom& atom) const
{
    try {
        return Biomol::getResidueInsertionCode(atom);

    } catch (const Base::ItemNotFound& e) {
        if (strictErrorChecking)
            throw Base::IOError("PDBDataWriter: residue insertion code property not found for atom");

        return ' ';
    }
}

const std::string& Biomol::PDBDataWriter::getChainID(const Chem::Atom& atom) const
{
    try {
        return Biomol::getChainID(atom);

    } catch (const Base::ItemNotFound& e) {
        if (strictErrorChecking)
            throw Base::IOError("PDBDataWriter: chain-id property not found for atom");

        return DEF_CHAIN_ID;
    }
}

const std::string& Biomol::PDBDataWriter::getResidueCode(const Chem::Atom& atom) const
{
    try {
        return Biomol::getResidueCode(atom);

    } catch (const Base::ItemNotFound& e) {
        if (strictErrorChecking)
            throw Base::IOError("PDBDataWriter: residue code property not found for atom");

        return DEF_RESIDUE_CODE;
    }
}

bool Biomol::PDBDataWriter::getHeteroAtomFlag(const Chem::Atom& atom) const
{
    try {
        return Biomol::getHeteroAtomFlag(atom);

    } catch (const Base::ItemNotFound& e) {
        if (strictErrorChecking)
            throw Base::IOError("PDBDataWriter: hetero atom flag property not found for atom");

        return true;
    }
}

const std::string& Biomol::PDBDataWriter::getResidueAtomName(const Chem::Atom& atom) const
{
    try {
        return Biomol::getResidueAtomName(atom);

    } catch (const Base::ItemNotFound& e) {
        if (strictErrorChecking)
            throw Base::IOError("PDBDataWriter: residue atom name property not found for atom");

        return Chem::getSymbol(atom);
    }
}
*/
