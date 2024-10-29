/* 
 * PMLDataWriter.hpp 
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


#ifndef CDPL_PHARM_PMLDATAWRITER_HPP
#define CDPL_PHARM_PMLDATAWRITER_HPP

#include <iosfwd>
#include <string>
#include <cstddef>


namespace CDPL
{

    namespace Base
    {

        class DataIOBase;
    }

    namespace Pharm
    {

        class FeatureContainer;
        class Feature;

        class PMLDataWriter
        {

          public:
            PMLDataWriter(const Base::DataIOBase& io_base);

            bool writeFeatureContainer(std::ostream& os, const FeatureContainer& pharm);

            void close(std::ostream& os);

          private:
            void init(std::ostream& os);

            void writeHeader(std::ostream& os) const;
            void writeFooter(std::ostream& os) const;

            void startAlignmentElement(std::ostream& os, const FeatureContainer& cntnr);
            void endAlignmentElement(std::ostream& os) const;

            void startPharmacophore(std::ostream& os, const FeatureContainer& cntnr) const;
            void endPharmacophore(std::ostream& os) const;

            void writeFeatures(std::ostream& os, const FeatureContainer& cntnr);

            void writeXVolume(std::ostream& os, const Feature& ftr, std::size_t id);
            void writePointFeature(std::ostream& os, const Feature& ftr, const std::string& name, std::size_t id);
            void writeVectorFeature(std::ostream& os, const Feature& ftr, const std::string& name, std::size_t id, bool points_to_lig);
            void writePlaneFeature(std::ostream& os, const Feature& ftr, const std::string& name, std::size_t id);

            void writeDefaultFeatureAttributes(std::ostream& os, const Feature& ftr, const std::string& name, std::size_t id, bool close);

            template <typename VE>
            void writePositionAndTolerance(std::ostream& os, const std::string& tag, const VE& pos, double tol) const;

            const Base::DataIOBase& ioBase;
            bool                    wrtHeader;
            bool                    strictErrorChecking;
            std::size_t             alignElemID;
            std::size_t             featureID;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PMLDATAWRITER_HPP
