/* 
 * IcosahedronMesh3D.cpp 
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

#include <cmath>

#include "CDPL/Vis/IcosahedronMesh3D.hpp"


using namespace CDPL;


Vis::IcosahedronMesh3D::IcosahedronMesh3D(double radius)
{
    //////////////////////////////////////////////////////////
    // Generate unit vertices using 3 orthogonal rectangles //
    //                                                      //
    //                    /|  - R1                          //
    //                   / |                                //
    //                  /  |                                //
    //                 /   |                                //
    //                |    |                                //
    //               _|    |_______                         //
    //      ________/_|   _|______/__                       //
    //     |          |  |           |                      //
    //     |      ____|  |______     |                      //
    //     |     /    | /      /     |                      //
    //     |____/     |/      /______|  - R2                //
    //         /             /                              //
    //        /_____________/                               //
    //                |    |                                //
    //         ^      |    /                                //
    //        R3      |   /                                 //
    //                |  /                                  //
    //                | /                                   //
    //                |/                                    //
    //                                                      //
    //////////////////////////////////////////////////////////

    getVertices().reserve(12);
    getVertexNormals().reserve(12);
    getFaces().reserve(20);
    
    // The golden ratio
    auto t = (1.0 + std::sqrt(5.0)) / 2.0;
    auto hd = std::sqrt(1.0 + t * t);
    auto c1 = t / hd;
    auto c2 = 1.0 / hd;
    auto c1s = c1 * radius;
    auto c2s = c2 * radius;

    // Add vertices
    // 4 vertices of Golden rectangle [R1]
    addVertex(-c2s, c1s, 0);
    addVertex(c2s, c1s, 0);
    addVertex(-c2s, -c1s, 0);
    addVertex(c2s, -c1s, 0);

    // 4 verices of the Golden rectangle orthagonal to the last [R2]
    addVertex(0, -c2s, c1s);
    addVertex(0, c2s, c1s);
    addVertex(0, -c2s, -c1s);
    addVertex(0, c2s, -c1s);

    // 4 verices of the Golden rectangle orthagonal to the last two [R3]
    addVertex(c1s, 0, -c2s);
    addVertex(c1s, 0, c2s);
    addVertex(-c1s, 0, -c2s);
    addVertex(-c1s, 0, c2s);

    // Add corr. vertex normals
    addVertexNormal(-c2, c1, 0);
    addVertexNormal(c2, c1, 0);
    addVertexNormal(-c2, -c1, 0);
    addVertexNormal(c2, -c1, 0);
    addVertexNormal(0, -c2, c1);
    addVertexNormal(0, c2, c1);
    addVertexNormal(0, -c2, -c1);
    addVertexNormal(0, c2, -c1);
    addVertexNormal(c1, 0, -c2);
    addVertexNormal(c1, 0, c2);
    addVertexNormal(-c1, 0, -c2);
    addVertexNormal(-c1, 0, c2);

    // Add faces
    // 5 faces around point 0
    addFace(0, 11, 5);
    addFace(0, 5, 1);
    addFace(0, 1, 7);
    addFace(0, 7, 10);
    addFace(0, 10, 11);

    // 5 adjacent faces
    addFace(1, 5, 9);
    addFace(5, 11, 4);
    addFace(11, 10, 2);
    addFace(10, 7, 6);
    addFace(7, 1, 8);

    // 5 faces around point 3
    addFace(3, 9, 4);
    addFace(3, 4, 2);
    addFace(3, 2, 6);
    addFace(3, 6, 8);
    addFace(3, 8, 9);

    // 5 adjacent faces
    addFace(4, 9, 5);
    addFace(2, 4, 11);
    addFace(6, 2, 10);
    addFace(8, 6, 7);
    addFace(9, 8, 1);

    setClosed();
}
