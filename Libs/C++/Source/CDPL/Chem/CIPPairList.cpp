/* 
 * CIPPairList.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * Code based on a Java implementation of the CIP sequence rules by John Mayfield
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


#include "CDPL/Chem/CIPDescriptor.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CIPPairList.hpp"


using namespace CDPL;


Chem::CIPPairList::CIPPairList(unsigned int ref)
{
    add(ref);
}

unsigned int Chem::CIPPairList::getRefDescriptor() const
{
    if (descriptors.empty())
        return CIPDescriptor::NONE;

    return ref(descriptors[0]);
}

bool Chem::CIPPairList::add(unsigned int descriptor)
{
    using namespace CIPDescriptor;

    switch (descriptor) {

        case R:
        case S:
        case M:
        case P:
        case seqTrans:
        case seqCis:
            descriptors.push_back(ref(descriptor));
            return true;

        default:
            return false;
    }
}

void Chem::CIPPairList::clear()
{
    descriptors.clear();
}

unsigned int Chem::CIPPairList::ref(unsigned int descriptor)
{
    using namespace CIPDescriptor;

    switch (descriptor) {

        case R:
        case M:
        case seqCis:
            return R;

        case S:
        case P:
        case seqTrans:
            return S;

        default:
            return CIPDescriptor::NONE;
    }
}

int Chem::CIPPairList::compareTo(const CIPPairList& that) const
{
    if (descriptors.size() != that.descriptors.size())
        throw Base::SizeError("CIPPairList: descriptor lists must be of same length");

    if (!descriptors.empty()) {
        auto this_ref = descriptors[0];
        auto that_ref = that.descriptors[0];

        for (std::size_t i = 1; i < descriptors.size(); i++) {
            if (this_ref == descriptors[i] && that_ref != that.descriptors[i])
                return +1;

            if (this_ref != descriptors[i] && that_ref == that.descriptors[i])
                return -1;
        }
    }

    return 0;
}
