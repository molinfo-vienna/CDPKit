/* 
 * MutableBondSequenceExport.hpp 
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


#ifndef CDPL_PYTHON_CHEM_MUTABLEBONDSEQUENCEEXPORT_HPP
#define CDPL_PYTHON_CHEM_MUTABLEBONDSEQUENCEEXPORT_HPP

#include "BondSequenceExport.hpp"


namespace
{

    template <typename T>
    struct MutableBondSequence : public BondSequence<T>
    {

        MutableBondSequence(T& cntnr):
            BondSequence<T>(cntnr) {}

        void removeBond(std::size_t idx)
        {
            BondSequence<T>::container.removeBond(idx);
        }
    };

    template <typename T>
    MutableBondSequence<T> createMutableBondSequence(T& molgraph)
    {
        return MutableBondSequence<T>(molgraph);
    }

    template <typename T>
    struct MutableBondSequenceExport
    {

        MutableBondSequenceExport(const char* name)
        {
            using namespace boost;

            python::class_<MutableBondSequence<T> >(name, python::no_init)
                .def("__len__", &BondSequence<T>::getNumBonds, python::arg("self"))
                .def("__getitem__", &BondSequence<T>::getBond, (python::arg("self"), python::arg("idx")),
                     python::return_internal_reference<1>())
                .def("__delitem__", &MutableBondSequence<T>::removeBond, (python::arg("self"), python::arg("idx")))
                .def("__contains__", &BondSequence<T>::containsBond, (python::arg("self"), python::arg("bond")));
        }
    };
} // namespace

#endif // CDPL_PYTHON_CHEM_MUTABLEBONDSEQUENCEEXPORT_HPP
