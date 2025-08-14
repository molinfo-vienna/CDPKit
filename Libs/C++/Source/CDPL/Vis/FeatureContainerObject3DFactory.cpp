/* 
 * FeatureContainerObject3DFactory.cpp 
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

 
#include "StaticInit.hpp"

#include <mutex>
#include <cmath>

#include "CDPL/Vis/FeatureContainerObject3DFactory.hpp"
#include "CDPL/Vis/IcosahedronMesh3D.hpp"
#include "CDPL/Vis/TorusMesh3D.hpp"
#include "CDPL/Vis/RightFrustumMesh3D.hpp"
#include "CDPL/Vis/TriangleMesh3DFunctions.hpp"

//#include <fstream>
using namespace CDPL;


namespace
{
/*
    void dumpSTL(const Vis::TriangleMesh3D& mesh, const std::string& fname)
    {
        std::ofstream ofs(fname);

        ofs << "solid name\n";

        for (std::size_t i = 0; i < mesh.getNumFaces(); i++) {
            auto& f = mesh.getFaces()[i];
            auto& v1 = mesh.getVertices()[f[0]];
            auto& v2 = mesh.getVertices()[f[1]];
            auto& v3 = mesh.getVertices()[f[2]];
            
            Math::Vector3D n = crossProd(v2 - v1, v3 - v1);

            ofs << " facet normal " << n[0] << ' ' << n[1] << ' ' << n[2] << '\n';
            ofs << "  outer loop\n";
            ofs << "   vertex " << v1[0] << ' ' << v1[1] << ' ' << v1[2] << '\n';
            ofs << "   vertex "  << v2[0] << ' ' << v2[1] << ' ' << v2[2] << '\n';
            ofs << "   vertex "  << v3[0] << ' ' << v3[1] << ' ' << v3[2] << '\n';
            ofs << "  endloop\n";
            ofs << " endfacet\n";
        }
        
        ofs << "endsolid name\n";
    }
*/
    std::once_flag initTriangleMeshesFlag;

    Vis::TriangleMesh3D::SharedPointer sphereMesh;
    Vis::TriangleMesh3D::SharedPointer nonDirectedHBFeatureMesh;
    Vis::TriangleMesh3D::SharedPointer directedARFeatureMesh;
    
    void initTriangleMeshes()
    {
        using namespace Vis;

        sphereMesh.reset(new IcosahedronMesh3D());

        for (std::size_t i = 0; i < 2; i++) {
            subdivideSpherical(*sphereMesh);
            removeVertexDuplicates(*sphereMesh);
        }

        //dumpSTL(*sphereMesh, "/home/tseidel/data/sphereMesh.stl");
    
        // ---

        nonDirectedHBFeatureMesh.reset(new TriangleMesh3D());

        nonDirectedHBFeatureMesh->addVertex(0.0, 0.0, 1.0);
        nonDirectedHBFeatureMesh->addVertexNormal(0.0, 0.0, 1.0);
        nonDirectedHBFeatureMesh->addVertex(1.0, 0.0, 0.0);
        nonDirectedHBFeatureMesh->addVertexNormal(1.0, 0.0, 0.0);
        nonDirectedHBFeatureMesh->addVertex(0.0, 1.0, 0.0);
        nonDirectedHBFeatureMesh->addVertexNormal(0.0, 1.0, 0.0);
        nonDirectedHBFeatureMesh->addFace(0, 1, 2);

        for (std::size_t i = 0; i < 3; i++) {
            subdivideSpherical(*nonDirectedHBFeatureMesh);
            removeVertexDuplicates(*nonDirectedHBFeatureMesh);
        }

        auto num_prev_verts = nonDirectedHBFeatureMesh->getNumVertices();

        *nonDirectedHBFeatureMesh += *nonDirectedHBFeatureMesh;

        rotateY(*nonDirectedHBFeatureMesh, M_PI, num_prev_verts);

        num_prev_verts = nonDirectedHBFeatureMesh->getNumVertices();

        *nonDirectedHBFeatureMesh += *nonDirectedHBFeatureMesh;

        rotateX(*nonDirectedHBFeatureMesh, M_PI, num_prev_verts);
        
        //dumpSTL(*nonDirectedHBFeatureMesh, "/home/tseidel/data/nonDirectedHBFeatureMesh.stl");

        // ---

        directedARFeatureMesh.reset(new TorusMesh3D(0.5, 0.5, 36, 11, M_PI / 2.0, M_PI));

        scale(*directedARFeatureMesh, 1.0, 1.0, 0.4);
        translate(*directedARFeatureMesh, 0.0, 0.0, 0.4);

        num_prev_verts = directedARFeatureMesh->getNumVertices();
    
        *directedARFeatureMesh += *directedARFeatureMesh;

        rotateX(*directedARFeatureMesh, M_PI, num_prev_verts);

        RightFrustumMesh3D cyl_mesh(0.1, 0.1, 0.8, 10, true, true);

        translate(cyl_mesh, 0.0, 0.0, -0.4);

        *directedARFeatureMesh += cyl_mesh;

        RightFrustumMesh3D cone_mesh(0.15, 0.0, 0.35, 5, true);

        translate(cone_mesh, 0.0, 0.0, 0.9);

        *directedARFeatureMesh += cone_mesh;

        rotateX(cone_mesh, M_PI);

        *directedARFeatureMesh += cone_mesh;
        
        //dumpSTL(*directedARFeatureMesh, "/home/tseidel/data/directedARFeatureMesh.stl");

        // ---

        

    }
}


Vis::Object3D::SharedPointer Vis::FeatureContainerObject3DFactory::create(const Pharm::FeatureContainer& cntnr)
{
    std::call_once(initTriangleMeshesFlag, &initTriangleMeshes);
    
    Object3D::SharedPointer obj_ptr(new Object3D());

    return obj_ptr;
}
