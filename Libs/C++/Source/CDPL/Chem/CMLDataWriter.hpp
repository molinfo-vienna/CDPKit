/* 
 * CMLDataWriter.hpp 
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


#ifndef CDPL_CHEM_CMLDATAWRITER_HPP
#define CDPL_CHEM_CMLDATAWRITER_HPP

#include <iosfwd>
#include <cstddef>
#include <string>


namespace CDPL
{

    namespace Base
    {

        class DataIOBase;
    }

    namespace Chem
    {

        class MolecularGraph;
        class Atom;
        class Bond;

        class CMLDataWriter
        {

          public:
            CMLDataWriter(const Base::DataIOBase& io_base);

            bool writeMolecularGraph(std::ostream& os, const MolecularGraph& molgraph);

            void close(std::ostream& os);
            
          private:
            void startDocument(std::ostream& os) const;
            void endDocument(std::ostream& os) const;

            void startMoleculeElement(std::ostream& os, const MolecularGraph& molgraph);
            void endMoleculeElement(std::ostream& os) const;
            
            void writeName(std::ostream& os, const MolecularGraph& molgraph);

            void writeAtoms(std::ostream& os, const MolecularGraph& molgraph);
            bool writeAtomParity(std::ostream& os, const Atom& atom, const MolecularGraph& molgraph);
                
            void writeBonds(std::ostream& os, const MolecularGraph& molgraph);
            bool writeBondStereo(std::ostream& os, const Bond& bond, const MolecularGraph& molgraph, bool write_sf);
                
            void writeProperties(std::ostream& os, const MolecularGraph& molgraph);

            const std::string& getAtomId(const Atom& atom, const MolecularGraph& molgraph, std::string& id_str) const;
            
            const Base::DataIOBase& ioBase;
            bool                    startDoc;
            std::size_t             molId;
            std::string             tmpString[2];
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CMLDATAWRITER_HPP
