/* 
 * DescriptorCalculator.hpp
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


#ifndef SIMSCREEN_DESCRIPTORCALCULATOR_HPP
#define SIMSCREEN_DESCRIPTORCALCULATOR_HPP

#include <string>

#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Molecule;
    }
}

namespace CmdLineLib
{

    class CmdLineBase;
}


namespace SimScreen
{

    class DescriptorCalculator
    {

      public:
        enum DescriptorType
        {

            BITSET,
            VECTOR
        };

        DescriptorCalculator(const std::string& id, DescriptorType descr_type, bool req_3d_coords):
            id(id), descrType(descr_type), req3DCoords(req_3d_coords) {}

        virtual ~DescriptorCalculator() {}

        virtual void addOptions(CmdLineLib::CmdLineBase& cl_base) {}

        virtual void processOptions(CmdLineLib::CmdLineBase& cl_base) {}

        virtual void getOptionSummary(std::string& summary) const {}
        
        virtual DescriptorCalculator* clone() const = 0;

        virtual void prepare(CDPL::Chem::Molecule& mol);
        
        virtual void calculate(const CDPL::Chem::MolecularGraph& molgraph, CDPL::Util::BitSet& fp) {}

        virtual void calculate(const CDPL::Chem::MolecularGraph& molgraph, CDPL::Math::DVector& descr) {}
        
        const std::string& getID() const
        {
            return id;
        }

        virtual std::string getDisplayName() const
        {
            return id;
        }

        DescriptorType getDescriptorType() const
        {
            return descrType;
        }

        bool requires3DCoordinates() const
        {
            return req3DCoords;
        }

      private:
        std::string    id;
        DescriptorType descrType;
        bool           req3DCoords;
    };
} // namespace SimScreen

#endif // SIMSCREEN_DESCRIPTORCALCULATOR_HPP
