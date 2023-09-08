/* 
 * RegularGridSetExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Grid/RegularGridSet.hpp"
#include "CDPL/Grid/CDFDRegularGridSetWriter.hpp"
#include "CDPL/Grid/CDFDRegularGridSetReader.hpp"

#include "Base/CDFPickleSuite.hpp"
#include "Util/ArrayVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    template <typename GridSetType, typename GridSetWriter, typename GridSetReader>
    struct AddPickleSupport
    {

        template <typename Class>
        static void add(Class& cls)
        {
            cls.def_pickle(CDPLPythonBase::CDFPickleSuite<GridSetType, GridSetWriter, GridSetReader>());
        }
    };

    template <typename GridSetType>
    struct AddPickleSupport<GridSetType, void, void>
    {
        
       template <typename Class>
       static void add(Class& cls) {}
    };
     
    template <typename GridSetType, typename GridSetWriter = void, typename GridSetReader = void>
    void doExportRegularGridSet(const char* name)
    {
        using namespace boost;
        using namespace CDPL;

        python::class_<GridSetType, typename GridSetType::SharedPointer> cls(name, python::no_init);

        cls
            .def(python::init<>(python::arg("self")))
            .def(python::init<const GridSetType&>((python::arg("self"), python::arg("set"))))
            .def(CDPLPythonUtil::ArrayVisitor<GridSetType, python::return_value_policy<python::return_by_value>,
                                              python::default_call_policies, python::default_call_policies,
                                              python::default_call_policies>())
            .def("__eq__", &Util::operator==<typename GridSetType::BaseType::ElementType>, (python::arg("self"), python::arg("set")))
            .def("__ne__", &Util::operator!=<typename GridSetType::BaseType::ElementType>, (python::arg("self"), python::arg("set")));

        AddPickleSupport<GridSetType, GridSetWriter, GridSetReader>::add(cls);
    }

} // namespace


void CDPLPythonGrid::exportRegularGridSet()
{
    using namespace CDPL;

    doExportRegularGridSet<Grid::FRegularGridSet>("FRegularGridSet");
    doExportRegularGridSet<Grid::DRegularGridSet, Grid::CDFDRegularGridSetWriter,
                           Grid::CDFDRegularGridSetReader>("DRegularGridSet");
}
