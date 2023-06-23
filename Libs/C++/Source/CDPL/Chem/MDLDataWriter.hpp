/* 
 * MDLDataWriter.hpp 
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


#ifndef CDPL_CHEM_MDLDATAWRITER_HPP
#define CDPL_CHEM_MDLDATAWRITER_HPP

#include <cstddef>
#include <string>
#include <iosfwd>

#include "CDPL/Math/VectorArray.hpp"


namespace CDPL 
{

	namespace Base
	{

		class DataIOBase;
	}

	namespace Chem
	{

		class Reaction;
		class MolecularGraph;
		class Atom;
		class Bond;
		class MatchConstraintList;

		class MDLDataWriter
		{

		public:
			MDLDataWriter(const Base::DataIOBase& io_base): ioBase(io_base), rdfHeaderWritten(false) {}
		
			bool writeMOLFile(std::ostream&, const MolecularGraph&);
			bool writeSDFileRecord(std::ostream&, const MolecularGraph&);

			bool writeRXNFile(std::ostream&, const Reaction&);
			bool writeRDFileRecord(std::ostream&, const Reaction&);

		private:
			bool writeMolecularGraph(std::ostream&, const MolecularGraph&, bool);

			void init(std::ostream&, bool);

			void getAtomCoordsDim(const MolecularGraph&);

			void writeMOLHeaderBlock(std::ostream&, const MolecularGraph&, std::size_t = 0) const;
			void writeMOLCTab(std::ostream&, const MolecularGraph&);
			void writeMOLEndTag(std::ostream&) const;

			void writeCTabCountsLine(std::ostream&) const;
			void setupCTabCountsLine(const MolecularGraph&);

			void writeCTabV2000(std::ostream&, const MolecularGraph&) const;

			void writeCTabV2000AtomBlock(std::ostream&, const MolecularGraph&) const;
			void writeCTabV2000BondBlock(std::ostream&, const MolecularGraph&) const;
			void writeCTabV2000PropertyBlock(std::ostream&, const MolecularGraph&) const;

			void writeCTabV2000Atom(std::ostream&, const MolecularGraph&, const Atom&) const;
			void writeCTabV2000AtomCoords(std::ostream&, const MolecularGraph&, const Atom&) const;
			void writeCTabV2000AtomSymbol(std::ostream&, const Atom&) const;
			void writeCTabV2000AtomMass(std::ostream&, const Atom&) const;
			void writeCTabV2000AtomCharge(std::ostream&, const Atom&) const;
			void writeCTabV2000AtomParity(std::ostream&, const MolecularGraph&, const Atom&) const;
			void writeCTabV2000AtomQueryHCount(std::ostream&, const MolecularGraph&, const Atom&) const;
			void writeCTabV2000AtomStereoBoxFlag(std::ostream&, const MolecularGraph&, const Atom&) const;
			void writeCTabV2000AtomValence(std::ostream&, const MolecularGraph&, const Atom&) const;
			void writeCTabV2000AtomRxnInfo(std::ostream&, const Atom&) const;

			void writeCTabV2000Bond(std::ostream&, const MolecularGraph&, const Bond&) const;
			void writeCTabV2000BondAtomIndices(std::ostream&, const MolecularGraph&, const Bond&, bool) const;
			void writeCTabV2000BondType(std::ostream&, std::size_t, const MatchConstraintList&) const;
			void writeCTabV2000BondStereo(std::ostream&, unsigned int, std::size_t) const;
			void writeCTabV2000BondQueryTopology(std::ostream&, const MolecularGraph&, const Bond&, 
												 const MatchConstraintList&) const;
			void writeCTabV2000BondRxnCenterStatus(std::ostream&, const Bond&) const;

			void writeCTabV2000ChargeProperties(std::ostream&, const MolecularGraph&) const;
			void writeCTabV2000RadicalProperties(std::ostream&, const MolecularGraph&) const;
			void writeCTabV2000IsotopeProperties(std::ostream&, const MolecularGraph&) const;
			void writeCTabV2000RingBndCountProperties(std::ostream&, const MolecularGraph&) const;
			void writeCTabV2000SubstCountProperties(std::ostream&, const MolecularGraph&) const;
			void writeCTabV2000UnsaturationProperties(std::ostream&, const MolecularGraph&) const;
			void writeCTabV2000AtomListProperties(std::ostream&, const MolecularGraph&) const;
			void writeCTabV2000AtomList(std::ostream&, const MolecularGraph&, const Atom&, 
										const MatchConstraintList&, bool) const;
			void writeCTabV2000RegistryNumberProperty(std::ostream&, const MolecularGraph&) const;

			void writeSDFData(std::ostream&, const MolecularGraph&) const;

			void setRXNFileVersion(const Reaction&);

			void writeRXNHeaderBlock(std::ostream&, const Reaction&) const;
			void writeRXNReaction(std::ostream&, const Reaction&);

			void writeRXNV2000Reaction(std::ostream&, const Reaction&);
			void writeRXNV2000CountsLine(std::ostream&, const Reaction&) const;
			void writeRXNV2000ReactionComponent(std::ostream&, const MolecularGraph&);

			void writeRDFHeaderBlock(std::ostream&);
			void writeRDFReaction(std::ostream&, const Reaction&);
			void writeRDFData(std::ostream&, const Reaction&) const;

			void writeRDFLine(std::ostream&, const std::string&, std::size_t, bool) const;

			void writeCTabV3000(std::ostream&, const MolecularGraph&, bool = false) const;

			void writeCTabV3000CountsLine(std::ostream&, const MolecularGraph&, bool = false) const;
			void writeCTabV3000AtomBlock(std::ostream&, const MolecularGraph&) const;
			void writeCTabV3000BondBlock(std::ostream&, const MolecularGraph&) const;

			void writeCTabV3000Atom(std::ostream&, const MolecularGraph&, const Atom&) const;
			void writeCTabV3000AtomIndex(std::ostream&, const MolecularGraph&, const Atom&) const;
			void writeCTabV3000AtomType(std::ostream&, const Atom&, const MatchConstraintList&) const;
			bool writeCTabV3000AtomList(std::ostream&, const Atom&, const MatchConstraintList&) const;
			bool writeCTabV3000AtomList(std::ostream&, const Atom&, const MatchConstraintList&, bool) const;
			void writeCTabV3000AtomCoords(std::ostream&, const MolecularGraph&, const Atom&) const;
			void writeCTabV3000AtomRxnAAMNumber(std::ostream&, const Atom&) const;
			void writeCTabV3000AtomCharge(std::ostream&, const Atom&) const;
			void writeCTabV3000AtomRadicalType(std::ostream&, const Atom&) const;
			void writeCTabV3000AtomStereoParity(std::ostream&, const MolecularGraph&, const Atom&) const;
			void writeCTabV3000AtomMass(std::ostream&, const Atom&) const;
			void writeCTabV3000AtomValence(std::ostream&, const MolecularGraph&, const Atom&) const;
			void writeCTabV3000AtomQueryHCount(std::ostream&, const MolecularGraph&, const Atom&, 
											   const MatchConstraintList&) const;
			void writeCTabV3000AtomRxnInfo(std::ostream&, const Atom&) const;
			void writeCTabV3000AtomQuerySubstCount(std::ostream&, const MolecularGraph&, const Atom&, 
												   const MatchConstraintList&) const;
			void writeCTabV3000AtomQueryUnsaturationFlag(std::ostream&, const MolecularGraph&, const Atom&, 
														 const MatchConstraintList&) const;
			void writeCTabV3000AtomQueryRingBondCount(std::ostream&, const MolecularGraph&, const Atom&, 
													  const MatchConstraintList&) const;

			void writeCTabV3000Bond(std::ostream&, const MolecularGraph&, const Bond&) const;
			void writeCTabV3000BondIndex(std::ostream&, const MolecularGraph&, const Bond&) const;
			void writeCTabV3000BondType(std::ostream&, std::size_t, const MatchConstraintList&) const;
			void writeCTabV3000BondAtomIndices(std::ostream&, const MolecularGraph&, const Bond&, bool) const;
			void writeCTabV3000BondStereo(std::ostream&, unsigned int) const;
			void writeCTabV3000BondQueryTopology(std::ostream&, const MolecularGraph&, const Bond&, 
												 const MatchConstraintList&) const;
			void writeCTabV3000BondRxnCenterStatus(std::ostream&, const Bond&) const;
			void writeCTabV3000BondQueryStereoBoxFlag(std::ostream&, std::size_t, const MatchConstraintList&) const;

			void writeCTabV3000PropertyStringValue(std::ostream&, const std::string&) const;

			void writeRXNV3000Reaction(std::ostream&, const Reaction&);
			void writeRXNV3000CountsLine(std::ostream&, const Reaction&) const;
			void writeRXNV3000ReactionComponent(std::ostream&, const MolecularGraph&);

			void writeV3000BlockBegin(std::ostream&, const std::string&) const;
			void writeV3000BlockEnd(std::ostream&, const std::string&) const;

			void writeV3000DataLine(std::ostream&, const std::string&) const;

			unsigned int getBondStereo(const Bond&) const;
			bool isReverseStereo(unsigned int) const;

			const Base::DataIOBase& ioBase;
			std::size_t             coordsDim;
			std::size_t             atomCount;
			std::size_t             bondCount;
			std::size_t             atomListCount;
			std::size_t             sTextEntryCount;
			std::size_t             propertyCount;
			unsigned int            chiralFlag;
			unsigned int            ctabVersion;
			unsigned int            rxnVersion;
			bool                    strictErrorChecking;
			bool                    bondMemberSwapStereoFix;
			bool                    ignoreParity;
			bool                    trimStrings;
			bool                    truncateStrings;
			bool                    trimLines;
			bool                    truncateLines;
			bool                    checkLineLength;
			bool                    rdfHeaderWritten;
			bool                    multiConfExport;
			bool                    writeConfEnergySDEntry;
			bool                    writeConfEnergyComment;
			bool                    writeConfEnergyField;
			std::string             confEnergySDTag;
			std::string             confIdxSuffixPattern;
			double                  confEnergy;
			Math::Vector3DArray     confCoordinates;
		};
	}
}

#endif // CDPL_CHEM_MDLDATAWRITER_HPP
