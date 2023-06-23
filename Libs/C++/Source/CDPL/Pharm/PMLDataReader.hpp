/* 
 * PMLDataReader.hpp 
 *
 * This file is part of the Pharmical Data Processing Toolkit
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


#ifndef CDPL_PHARM_PMLDATAREADER_HPP
#define CDPL_PHARM_PMLDATAREADER_HPP

#include <iosfwd>
#include <string>

#include "RapidXML/rapidxml.hpp"

#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

    namespace Base
    {

        class DataIOBase;
    }

    namespace Pharm
    {

        class Pharmacophore;
        class Feature;

        class PMLDataReader
        {

        public:
            PMLDataReader(const Base::DataIOBase& io_base);

            virtual ~PMLDataReader() {}

            bool readPharmacophore(std::istream& is, Pharmacophore& pharm);

            bool skipPharmacophore(std::istream& is);

            bool hasMoreData(std::istream& is);

        private:
            typedef rapidxml::xml_document<char> XMLDocument;
            typedef rapidxml::xml_node<char> XMLNode;
            typedef rapidxml::xml_attribute<char> XMLAttribute;

            void init(); 

            void getPharmacophoreProperties(const XMLNode* pharm_node, Pharmacophore& pharm) const;

            void extractFeatures(const XMLNode* pharm_node, Pharmacophore& pharm) const;

            void addPointFeature(const XMLNode* ftr_node, Pharmacophore& pharm) const;
            void addPlaneFeature(const XMLNode* ftr_node, Pharmacophore& pharm) const;
            void addVectorFeature(const XMLNode* ftr_node, Pharmacophore& pharm) const;
            void addVolumeFeature(const XMLNode* ftr_node, Pharmacophore& pharm) const;

            Feature* createFeature(const XMLNode* ftr_node, Pharmacophore& pharm) const;

            void getDefaultFeatureProperties(const XMLNode* ftr_node, Feature& ftr) const;

            bool getPosition(const XMLNode* ftr_node, const std::string& tag, Math::Vector3D& vec) const; 
            bool getTolerance(const XMLNode* ftr_node, const std::string& tag, double& tol) const; 

            const Base::DataIOBase& ioBase;    
            bool                    strictErrorChecking;
            std::string             pharmData;
            XMLDocument             pharmDocument;
        };
    }
}

#endif // CDPL_PHARM_PMLDATAREADER_HPP
