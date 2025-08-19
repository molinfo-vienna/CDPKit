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


using namespace CDPL;


namespace
{

    std::once_flag initTriangleMeshesFlag;

    Vis::TriangleMesh3D::SharedPointer sphereMesh;
    Vis::TriangleMesh3D::SharedPointer nonDirectedHBFeatureMesh;
    Vis::TriangleMesh3D::SharedPointer directedARFeatureMesh;
    Vis::TriangleMesh3D::SharedPointer ionizableFeatureMesh;
    Vis::TriangleMesh3D::SharedPointer nonDirectedXBFeatureMesh;
    Vis::TriangleMesh3D::SharedPointer arrowShaftMesh;
    Vis::TriangleMesh3D::SharedPointer arrowHeadMesh;
    
    void initTriangleMeshes()
    {
        using namespace Vis;

        sphereMesh.reset(new IcosahedronMesh3D());

        for (std::size_t i = 0; i < 2; i++) {
            subdivideSpherical(*sphereMesh);
            removeVertexDuplicates(*sphereMesh);
        }
    
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

        RightFrustumMesh3D cone_mesh1(0.15, 0.0, 0.35, 5, true);

        translate(cone_mesh1, 0.0, 0.0, 0.9);

        *directedARFeatureMesh += cone_mesh1;

        rotateX(cone_mesh1, M_PI);

        *directedARFeatureMesh += cone_mesh1;

        // ---

        nonDirectedXBFeatureMesh.reset(new IcosahedronMesh3D());

        // ---

        RightFrustumMesh3D cone_mesh2(0.0, 0.15, 1.0, 12, false, true);
        
        ionizableFeatureMesh.reset(new TriangleMesh3D());

        for (std::size_t i = 0; i < 12; i++) {
            auto ico_vtx = nonDirectedXBFeatureMesh->getVertices()[i].getData();

            num_prev_verts = ionizableFeatureMesh->getNumVertices();

            *ionizableFeatureMesh += cone_mesh2;

            auto r = std::sqrt(ico_vtx[0] * ico_vtx[0] + ico_vtx[1] * ico_vtx[1]);

            if (r == 0.0)
                continue;

            auto z_rot = (ico_vtx[1] >= 0.0 ? 1.0 : -1.0) * std::acos(ico_vtx[0] / r);
            auto y_rot = std::acos(ico_vtx[2]);
            
            rotateY(*ionizableFeatureMesh, y_rot, num_prev_verts);
            rotateZ(*ionizableFeatureMesh, z_rot, num_prev_verts);
        }

        // ---

        arrowShaftMesh.reset(new RightFrustumMesh3D(0.15, 0.15, 1.0, 20, true, true));
    
        // ---        

        arrowHeadMesh.reset(new RightFrustumMesh3D(0.3, 0.0, 0.25, 20, true, false));
    }
}


Vis::Object3D::SharedPointer Vis::FeatureContainerObject3DFactory::create(const Pharm::FeatureContainer& cntnr)
{
    std::call_once(initTriangleMeshesFlag, &initTriangleMeshes);
    
    Object3D::SharedPointer obj_ptr(new Object3D());

    return obj_ptr;
}
