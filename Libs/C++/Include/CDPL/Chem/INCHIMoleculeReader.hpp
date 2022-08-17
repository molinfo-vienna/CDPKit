/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * INCHIMoleculeReader.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Chem::INCHIMoleculeReader.
 */

#ifndef CDPL_CHEM_INCHIMOLECULEREADER_HPP
#define CDPL_CHEM_INCHIMOLECULEREADER_HPP

#include <string>
#include <vector>
#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/StreamDataReader.hpp"


typedef struct tagInchiAtom inchi_Atom;
typedef struct tagINCHIStereo0D inchi_Stereo0D;


namespace CDPL 
{

	namespace Chem
	{

		class Molecule;
		class Atom;

		/**
		 * \brief A reader for molecule data in the <em>IUPAC International Chemical Identifier (InChI)</em>
		 *        [\ref INCHI] format.
		 *
		 * \c %INCHIMoleculeReader implements the conversion of \e InChI strings (or strings with auxiliary \e InChI information)
		 * to corresponding Chem::Molecule objects. The input data are read by means of a \c std::istream object that was provided
		 * to the \c %INCHIMoleculeReader constructor.
		 *
		 * For the actual decoding of the \e InChI input, \c %INCHIMoleculeReader uses an appropriate function (\c GetStructFromINCHI()
		 * for \e InChI strings and \c Get_inchi_Input_FromAuxInfo() for auxiliary \e InChI information) of the <em>InChI C-API</em>.
		 * The return value of the called function provides information about the status of the performed operation (see
		 * Chem::INCHIReturnCode) and can be accessed by the method getReturnCode().
		 * Produced error and log messages are accessible via the methods getMessage() and getLogOutput(), respectively.
		 *
		 * %Atom and bond attributes of a read input molecule are stored as properties of allocated Chem::Atom and Chem::Bond
		 * objects. The affected properties are summarized in the tables below:
		 *
		 * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Chem::Atom Property</th> <th>Description</th> <th>Notes</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomProperty::COORDINATES_2D</td>
		 *   <td>Specifies the 2D position of the atom</td>
		 *   <td>Only set if auxiliary information with 2D-coordinates is available</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomProperty::COORDINATES_3D</td>
		 *   <td>Specifies the 3D-coordinates of the atom</td>
		 *   <td>Only set if auxiliary information with 3D-coordinates is available</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomProperty::SYMBOL</td>
		 *   <td>Specifies the symbol of the atom's element</td>
		 *   <td align="center">-</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomProperty::ISOTOPE</td>
		 *   <td>Specifies the isotopic mass of the atom</td>
		 *   <td align="center">-</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomProperty::FORMAL_CHARGE</td>
		 *   <td>Specifies the formal charge of the atom</td>
		 *   <td>Only set if the charge is different from zero</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomProperty::RADICAL_TYPE</td>
		 *   <td>Specifies the radical type (see Chem::RadicalType)</td>
		 *   <td>Only set if the atom is a radical</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::AtomProperty::STEREO_DESCRIPTOR</td>
		 *   <td>Specifies the atom stereo descriptor (see Chem::AtomConfiguration, Chem::StereoDescriptor)</td>
		 *   <td>Only set if 0D stereo information is available and the atom is a tetrahedral stereogenic center</td>
		 *  </tr>
		 * </table>
		 *
		 * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Chem::Bond Property</th> <th>Description</th> <th>Notes</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::BondProperty::ORDER</td>
		 *   <td>Specifies the order of the bond</td>
		 *   <td align="center">-</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::BondProperty::STEREO_2D_FLAG</td>
		 *   <td>Specifies the 2D stereo bond type (see Chem::BondStereoFlag)</td>
		 *   <td>Only set if auxiliary information with 2D stereo information is available</td></td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::BondProperty::STEREO_DESCRIPTOR</td>
		 *   <td>Specifies the bond stereo descriptor (see Chem::BondConfiguration, Chem::StereoDescriptor)</td>
		 *   <td>Only set if 0D stereo information is available and the bond is stereogenic center</td>
		 *  </tr>
		 * </table>
		 *
		 * \c %INCHIMoleculeReader can be configured with the following control-parameters:
		 *
		 * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Control-Parameter</th> <th>Default Value (see Chem::ControlParameterDefault)</th> <th>Description</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::STRICT_ERROR_CHECKING</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether non-fatal recoverable errors should be ignored or cause a read operation to fail</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::INCHI_INPUT_OPTIONS</td>
		 *   <td align="center">\c ""</td>
		 *   <td>Specifies options for \e InChI input</td>
		 *  </tr>
		 * </table>
		 */
		class CDPL_CHEM_API INCHIMoleculeReader : public Util::StreamDataReader<Molecule, INCHIMoleculeReader>
		{

		public:
			/**
			 * \brief Constructs a \c %INCHIMoleculeReader instance that will read the molecule data from the input
			 *        stream \a is.
			 * \param is The input stream to read from.
			 */
			INCHIMoleculeReader(std::istream& is);

			/**
			 * \brief Returns the error code of the last read operation.
			 *
			 * Possible return values are defined in namespace Chem::INCHIReturnCode.
			 *
			 * \return The error code of the last read operation.
			 */
			int getReturnCode() const;

			/**
			 * \brief Returns the error message associated with the last read operation.
			 * \return The error message associated with the last read operation.
			 */
			const std::string& getMessage() const;

			/**
			 * \brief Returns the log output that was generated for the last read operation.
			 * \return The log output that was generated for the last read operation.
			 */
			const std::string& getLogOutput() const;

		private:
			friend class Util::StreamDataReader<Molecule, INCHIMoleculeReader>;

			INCHIMoleculeReader(const INCHIMoleculeReader&);

			INCHIMoleculeReader& operator=(const INCHIMoleculeReader&);

			bool readData(std::istream&, Molecule&, bool overwrite);
			bool skipData(std::istream&);
			bool moreData(std::istream&);

			bool readMolecule(std::istream&, Molecule&);
			bool skipMolecule(std::istream&);

			void buildMolecule(Molecule&, const inchi_Atom*, std::size_t, const inchi_Stereo0D*, std::size_t) const;

			void setElement(Atom&, const inchi_Atom&) const;
			void setIsotope(Atom&, const inchi_Atom&) const;
			void setFormalCharge(Atom&, const inchi_Atom&) const;
			void setRadicalType(Atom&, const inchi_Atom&) const;
			void setImplicitHCounts(Atom&, const inchi_Atom&) const;
			void createBonds(Molecule&, Atom&, const inchi_Atom&, std::size_t) const;

			void set2DCoordinates(Molecule&, const inchi_Atom*, std::size_t) const;
			void set3DCoordinates(Molecule&, const inchi_Atom*, std::size_t) const;

			void process0DStereoInfo(Molecule&, const inchi_Stereo0D*, std::size_t, std::size_t) const;

			void process0DAtomStereoInfo(Molecule&, const inchi_Stereo0D&, std::size_t) const;
			void process0DBondStereoInfo(Molecule&, const inchi_Stereo0D&, std::size_t) const;

			typedef std::vector<char> StringData;

			std::string  inputToken;
			StringData   inputData;
			StringData   inchiOptions;
			bool         strictErrorChecking;
			int          returnCode;
			std::string  message;
			std::string  logOutput;
		};
	}
}

#endif // CDPL_CHEM_INCHIMOLECULEREADER_HPP
