/* 
 * INCHIMolecularGraphWriter.hpp 
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
 * \brief Definition of class CDPL::Chem::INCHIMolecularGraphWriter.
 */

#ifndef CDPL_CHEM_INCHIMOLECULARGRAPHWRITER_HPP
#define CDPL_CHEM_INCHIMOLECULARGRAPHWRITER_HPP

#include <vector>
#include <string>
#include <cstddef>
#include <iosfwd>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


typedef struct tagInchiAtom     inchi_Atom;
typedef struct tagINCHIStereo0D inchi_Stereo0D;


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Atom;

        /**
         * \brief Writer for molecular graph data in the <em>IUPAC International Chemical Identifier (InChI)</em>
         *        [\ref INCHI] format.
         *
         * \c %INCHIMolecularGraphWriter implements the generation of \e InChI strings from Chem::MolecularGraph objects. The output data
         * are written by means of a \c std::ostream object that was provided to the \c %INCHIMolecularGraphWriter constructor.
         *
         * For the generation of the \e InChI output, \c %INCHIMolecularGraphWriter uses the function \c GetINCHI() of the
         * <em>InChI C-API</em>. The return value of the function provides information about the status of the performed
         * operation (see Chem::INCHIReturnCode) and can be accessed by the method getReturnCode().
         * Produced error and log messages are accessible via the methods getMessage() and getLogOutput(), respectively.
         *
         * \c %INCHIMolecularGraphWriter can be configured with the following control-parameters:
         *
         * <table bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
         *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
         *   <th>Control-Parameter</th> <th>Default Value (see Chem::ControlParameterDefault)</th> <th>Description</th>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::COORDINATES_DIMENSION</td>
         *   <td align="center">\c 1</td>
         *   <td>Specifies the dimension of the atom coordinates to use for output generation. A value of \e 2 specifies 2D, a value of \e 3 specifies 3D,
         *       other values specify that any availables coordinates shall be used (3D takes precedence over 2D), and no coordinates otherwise</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::STRICT_ERROR_CHECKING</td>
         *   <td align="center">\c false</td>
         *   <td>Specifies whether non-fatal recoverable errors should be ignored or cause a write operation to fail</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::RECORD_SEPARATOR</td>
         *   <td align="center">\c "\n"</td>
         *   <td>Specifies the data record separator</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::INCHI_OUTPUT_OPTIONS</td>
         *   <td align="center">\c "/WarnOnEmptyStructure /AuxNone /NEWPSOFF"</td>
         *   <td>Specifies options for \e InChI generation</td>
         *  </tr>
         * </table>
         */
        class CDPL_CHEM_API INCHIMolecularGraphWriter : public Base::DataWriter<MolecularGraph>
        {

          public:
            /**
             * \brief Constructs a \c %INCHIMolecularGraphWriter instance that will write data of molecular graphs to the output
             *        stream \a os.
             * \param os The output stream to write to.
             */
            INCHIMolecularGraphWriter(std::ostream& os);

            INCHIMolecularGraphWriter(const INCHIMolecularGraphWriter&) = delete;
            
            /**
             * \brief Destructor.
             */
            ~INCHIMolecularGraphWriter();

            INCHIMolecularGraphWriter& operator=(const INCHIMolecularGraphWriter&) = delete;

            /**
             * \brief Writes data of the molecular graph \a molgraph to the output stream specified in the constructor.
             * \param molgraph The molecular graph to write.
             * \return A reference to itself.
             */
            Base::DataWriter<MolecularGraph>& write(const MolecularGraph& molgraph);

            /**
             * \brief Returns the error code of the last write operation.
             *
             * Possible return values are defined in namespace Chem::INCHIReturnCode.
             *
             * \return The error code of the last write operation.
             */
            int getReturnCode() const;

            /**
             * \brief Returns the error message associated with the last write operation.
             * \return The error message associated with the last write operation.
             */
            const std::string& getMessage() const;

            /**
             * \brief Returns the log output that was generated for the last write operation.
             * \return The log output that was generated for the last write operation.
             */
            const std::string& getLogOutput() const;

            /**
             * \brief Returns a pointer that is non-null while the writer is in a good state and \c nullptr after a failed write.
             * \return A non-null pointer in a good state, \c nullptr otherwise.
             */
            operator const void*() const;

            /**
             * \brief Tells whether a previous write operation has failed.
             * \return \c true if the writer is in a failed state, and \c false otherwise.
             */
            bool operator!() const;

          private:
            void writeMolGraph(const MolecularGraph&);

            void setupAtomTable(const MolecularGraph&, std::size_t);

            std::size_t getCoordsDimension(const MolecularGraph&) const;

            void setBondingInfo(const MolecularGraph&, const Atom&, inchi_Atom&, std::size_t) const;
            void setElementSymbol(const Atom&, inchi_Atom&) const;
            void setIsotope(const Atom&, inchi_Atom&) const;
            void setFormalCharge(const Atom&, inchi_Atom&) const;
            void setCoordinates(const Atom&, inchi_Atom&, std::size_t) const;
            void setRadicalType(const Atom&, inchi_Atom&) const;
            void setImplicitHCounts(inchi_Atom&) const;

            void setup0DStereoInfo(const MolecularGraph&);

            void setup0DAtomStereoInfo(const MolecularGraph&);
            void setup0DBondStereoInfo(const MolecularGraph&);

            typedef std::vector<inchi_Atom>     InChIAtomTable;
            typedef std::vector<inchi_Stereo0D> InChIStereoInfoList;
            typedef std::vector<char>           StringData;

            std::ostream&       output;
            InChIAtomTable      inchiAtomTable;
            InChIStereoInfoList inchiStereoInfo;
            StringData          inchiOptions;
            bool                strictErrorChecking;
            int                 returnCode;
            std::string         message;
            std::string         logOutput;
            bool                state;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_INCHIMOLECULARGRAPHWRITER_HPP
