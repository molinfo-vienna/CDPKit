/* 
 * CMLDataReader.hpp 
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


#ifndef CDPL_CHEM_CMLDATAREADER_HPP
#define CDPL_CHEM_CMLDATAREADER_HPP

#include <iosfwd>
#include <string>

#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "RapidXML/rapidxml.hpp"


namespace CDPL
{

    namespace Base
    {

        class DataIOBase;
    }

    namespace Chem
    {

        class Molecule;
        
        class CMLDataReader
        {

          public:
            CMLDataReader(const Base::DataIOBase& io_base):
                ioBase(io_base) {}

            bool readMolecule(std::istream& is, Molecule& mol);
            bool skipMolecule(std::istream& is);
            bool hasMoreData(std::istream& is);

          private:
            typedef rapidxml::xml_document<char>  XMLDocument;
            typedef rapidxml::xml_node<char>      XMLNode;
            typedef rapidxml::xml_attribute<char> XMLAttribute;
            typedef Internal::XMLTagInfo          XMLTagInfo;

            void init(std::istream& is);

            void readMoleculeCMLData(std::istream& is, bool save_data);

            const Base::DataIOBase& ioBase;
            bool                    strictErrorChecking;
            XMLTagInfo              tagInfo;
            std::string             molData;
            XMLDocument             molDocument;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CMLDATAREADER_HPP
