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
#include <string_view>
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <utility>

#include "CDPL/Chem/Fragment.hpp"
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
            typedef rapidxml::xml_node<char> XMLNode;

            void init();

            void readMoleculeData(std::istream& is, bool save_data);

            void readMolecule(const XMLNode* mol_node, Molecule& mol, bool top_level);

            void readAtoms(const XMLNode* atom_arr_node, Molecule& mol);
            void readArrayStyleAtoms(const XMLNode* atom_arr_node, Molecule& mol);
            void addAtom(const XMLNode* atom_node, Molecule& mol);
            
            void readBonds(const XMLNode* bond_arr_node, Molecule& mol);
            bool readArrayStyleBonds(const XMLNode* bond_arr_node, Molecule& mol) const;
            bool addBond(const XMLNode* bond_node, Molecule& mol);
            
            void setName(const XMLNode* name_node, Molecule& mol) const;
            void addProperty(const XMLNode* prop_node, Molecule& mol) const;
        
            void postprocStereoAtoms(Molecule& mol) const;
            void postprocStereoBonds(Molecule& mol) const;
            void postprocStereoBond(const XMLNode* stereo_node, Bond& bond, Molecule& mol) const;
            void perceiveBondOrders(Molecule& mol, std::size_t bond_offs);
            
            const XMLNode* getChildNode(const XMLNode* prnt_node, const std::string& name) const;

            typedef rapidxml::xml_document<char>                      XMLDocument;
            typedef rapidxml::xml_attribute<char>                     XMLAttribute;
            typedef Internal::XMLTagInfo                              XMLTagInfo;
            typedef std::pair<std::size_t, const XMLNode*>            IndexNodePair;
            typedef std::vector<IndexNodePair>                        IndexNodePairList;
            typedef std::unordered_map<std::string_view, std::size_t> AtomIDToIndexMap;

            const Base::DataIOBase& ioBase;
            bool                    strictErrorChecking;
            XMLTagInfo              tagInfo;
            std::string             molData;
            XMLDocument             molDocument;
            AtomIDToIndexMap        atomIDtoIndexMap;
            IndexNodePairList       stereoAtoms;
            IndexNodePairList       stereoBonds;
            Fragment                readMolGraph;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CMLDATAREADER_HPP
