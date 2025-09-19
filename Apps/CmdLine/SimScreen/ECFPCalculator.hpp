/* 
 * ECFPCalculator.hpp
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


#ifndef SIMSCREEN_ECFPCALCULATOR_HPP
#define SIMSCREEN_ECFPCALCULATOR_HPP

#include <cstddef>
#include <memory>

#include "DescriptorCalculator.hpp"


namespace CDPL
{

    namespace Descr
    {

        class CircularFingerprintGenerator;
    }
}


namespace SimScreen
{

    class ECFPCalculator : public DescriptorCalculator
    {

      public:
        ECFPCalculator();

        ~ECFPCalculator();
    
        void addOptions(CmdLineLib::CmdLineBase& cl_base);

        DescriptorCalculator* clone() const;

        void prepare(CDPL::Chem::Molecule& mol);
        
        void calculate(const CDPL::Chem::MolecularGraph& molgraph, CDPL::Util::BitSet& fp);

      private:
        typedef std::unique_ptr<CDPL::Descr::CircularFingerprintGenerator> ECFPGeneratorImplPtr;

        std::size_t          radius{2};
        std::size_t          size{8192};
        ECFPGeneratorImplPtr ecfpGenImpl;
    };
} // namespace SimScreen

#endif // SIMSCREEN_ECFPCALCULATOR_HPP
