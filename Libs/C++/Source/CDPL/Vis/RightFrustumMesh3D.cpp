/* 
 * RightFrustumMesh3D.cpp 
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

#include "CDPL/Vis/RightFrustumMesh3D.hpp"
#include "CDPL/Vis/TriangleMesh3DFunctions.hpp"


using namespace CDPL;


Vis::RightFrustumMesh3D::RightFrustumMesh3D(double radius1, double radius2, double height, std::size_t num_sides,
                                            bool close_btm, bool close_top)
{
    if (num_sides < 2)
        return;

    getVertices().reserve(2 * num_sides + 2);
    getFaces().reserve(4 * num_sides);

    auto ang_inc = M_PI * 2.0 / num_sides;
    
    if (radius1 == 0.0) {
        addVertex(0.0, 0.0, 0.0);

        for (std::size_t i = 0; i < num_sides; i++) {
            auto a = ang_inc * i;

            addVertex(radius2 * std::cos(a), radius2 * std::sin(a), height);
            addFace(0, ((i + 1) % num_sides) + 1, i + 1);
        }

        if (close_top) {
            switch (num_sides) {

                case 4:
                    addFace(1, 3, 4);
                    
                case 3:
                    addFace(1, 2, 3);

                case 2:
                    break;
                    
                default:
                    addVertex(0.0, 0.0, height);
                    
                    for (std::size_t i = 0; i < num_sides; i++)
                        addFace(num_sides + 1, i + 1, ((i + 1) % num_sides) + 1);
            }
        }
        
    } else if (radius2 == 0.0) {
        addVertex(0.0, 0.0, height);

        for (std::size_t i = 0; i < num_sides; i++) {
            auto a = ang_inc * i;

            addVertex(radius1 * std::cos(a), radius1 * std::sin(a), 0.0);
            addFace(0, i + 1, ((i + 1) % num_sides) + 1);
        }

        if (close_btm) {
            switch (num_sides) {

                case 4:
                    addFace(1, 4, 3);
                    
                case 3:
                    addFace(1, 3, 2);

                case 2:
                    break;
                    
                default:
                    addVertex(0.0, 0.0, 0.0);
                    
                    for (std::size_t i = 0; i < num_sides; i++)
                        addFace(num_sides + 1, ((i + 1) % num_sides) + 1, i + 1);
            }
        }
        
    } else {
        for (std::size_t i = 0; i < num_sides; i++) {
            auto a = ang_inc * i;
            auto cos_a = std::cos(a);
            auto sin_a = std::sin(a);

            addVertex(radius1 * cos_a, radius1 * sin_a, 0.0);
            addVertex(radius2 * cos_a, radius2 * sin_a, height);
            
            addFace(i * 2, ((i + 1) % num_sides) * 2, ((i + 1) % num_sides) * 2 + 1);
            addFace(i * 2, ((i + 1) % num_sides) * 2 + 1, i * 2 + 1);
        }

        if (close_top || close_btm) {
            switch (num_sides) {

                case 4:
                    if (close_btm)
                        addFace(0, 6, 4);

                    if (close_top)
                        addFace(1, 5, 7);
                          
                case 3:
                    if (close_btm)
                        addFace(0, 4, 2);

                    if (close_top)
                        addFace(1, 3, 5);

                case 2:
                    break;

                default:
                    if (close_btm) {
                        addVertex(0.0, 0.0, 0.0);

                        for (std::size_t i = 0; i < num_sides; i++)
                            addFace(num_sides * 2, ((i + 1) % num_sides) * 2, i * 2);
                    }

                    if (close_top) {
                        addVertex(0.0, 0.0, height);

                        for (std::size_t i = 0; i < num_sides; i++)
                            addFace(num_sides * 2 + (close_btm ? 1 : 0), i * 2 + 1, ((i + 1) % num_sides) * 2 + 1);
                    }
            }
        }
    }

    calcVertexFromFaceNormals(*this);
    setClosed(((radius1 <= 0.0) || close_btm) && ((radius2 <= 0.0) || close_top));
}
