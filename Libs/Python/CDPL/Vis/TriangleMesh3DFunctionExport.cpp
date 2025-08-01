/* 
 * TriangleMesh3DFunctionExport.cpp 
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

#include "CDPL/Vis/TriangleMesh3D.hpp"
#include "CDPL/Vis/TriangleMesh3DFunctions.hpp"

#include "FunctionExports.hpp"


void CDPLPythonVis::exportTriangleMesh3DFunctions()
{
    using namespace boost;
    using namespace CDPL;

    python::def("subdivideSpherical", &Vis::subdivideSpherical, python::arg("mesh"));
    python::def("removeVertexDuplicates", &Vis::removeVertexDuplicates,
                (python::arg("mesh"), python::arg("check_vn") = true, python::arg("tol") = 0.0));
    python::def("calcVertexFromFaceNormals", &Vis::calcVertexFromFaceNormals,
                (python::arg("mesh"), python::arg("weight_face_size") = false));
    python::def("translate", &Vis::translate,
                (python::arg("mesh"), python::arg("trans_x"), python::arg("trans_y"), python::arg("trans_z"),
                 python::arg("vtx_offs") = 0, python::arg("vtx_count") = 0));
    python::def("scale", &Vis::scale,
                (python::arg("mesh"), python::arg("scale_x"), python::arg("scale_y"), python::arg("scale_z"),
                 python::arg("vtx_offs") = 0, python::arg("vtx_count") = 0));
    python::def("rotateX", &Vis::rotateX,
                (python::arg("mesh"), python::arg("angle"), python::arg("vtx_offs") = 0, python::arg("vtx_count") = 0));
    python::def("rotateY", &Vis::rotateY,
                (python::arg("mesh"), python::arg("angle"), python::arg("vtx_offs") = 0, python::arg("vtx_count") = 0));
    python::def("rotateZ", &Vis::rotateZ,
                (python::arg("mesh"), python::arg("angle"), python::arg("vtx_offs") = 0, python::arg("vtx_count") = 0));
    python::def("transform", &Vis::transform,
                (python::arg("mesh"), python::arg("mtx"), python::arg("vtx_offs") = 0, python::arg("vtx_count") = 0));
}
