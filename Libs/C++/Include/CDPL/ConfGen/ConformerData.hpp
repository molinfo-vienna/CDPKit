/* 
 * ConformerData.hpp 
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
 * \brief Definition of class CDPL::ConfGen::ConformerData.
 */

#ifndef CDPL_CONFGEN_CONFORMERDATA_HPP
#define CDPL_CONFGEN_CONFORMERDATA_HPP

#include <algorithm>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        class CDPL_CONFGEN_API ConformerData : public Math::Vector3DArray
        {

          public:
            typedef std::shared_ptr<ConformerData> SharedPointer;

            ConformerData():
                energy(0.0) {}

            ConformerData(const Math::Vector3DArray& coords, double energy = 0.0):
                Math::Vector3DArray(coords), energy(energy) {}

            void setEnergy(double energy)
            {
                this->energy = energy;
            }

            double getEnergy() const
            {
                return energy;
            }

            void swap(ConformerData& data)
            {
                Math::Vector3DArray::swap(data);
                std::swap(energy, data.energy);
            }

          private:
            const char* getClassName() const
            {
                return "ConformerData";
            }

            double energy;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_CONFORMERDATA_HPP
