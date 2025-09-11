/* 
 * PLYObject3DWriter.hpp 
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
 * \brief Definition of class CDPL::Vis::PLYObject3DWriter.
 */

#ifndef CDPL_VIS_PLYOBJECT3DWRITER_HPP
#define CDPL_VIS_PLYOBJECT3DWRITER_HPP

#include <sstream>
#include <cstddef>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Shape3DVisitor.hpp"
#include "CDPL/Base/DataWriter.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace Vis
    {

        class Object3D;
        class Material;

        /**
         * \brief Outputs 3D visualization data represented by Vis::Object3D instances in the <em>Polygon File Format</em> [\ref PLYFMT]. 
         * \since 1.3
         */
        class CDPL_VIS_API PLYObject3DWriter : public Base::DataWriter<Object3D>, private Shape3DVisitor
        {

          public:
            /**
             * \brief Constructs a \c %PLYObject3DWriter instance that will write Vis::Object3D data to the output stream \a os.
             * \param os The output stream to write to.
             */
            PLYObject3DWriter(std::ostream& os);

            PLYObject3DWriter(const PLYObject3DWriter&) = delete;

            ~PLYObject3DWriter();
            
            /**
             * \brief Outputs the Vis::Object3D instance \a obj.
             * \param obj The Vis::Object3D instance to output.
             * \return A reference to itself.
             */
            Base::DataWriter<Object3D>& write(const Object3D& obj);

            operator const void*() const;
            bool operator!() const;

            PLYObject3DWriter& operator=(const PLYObject3DWriter&) = delete;
 
            void close();
            
          private:
            void process(const Object3D& obj);
            void visitTriangleMesh(const TriangleMesh3D& mesh);

            std::ostream&       output;
            std::ostringstream  vtxOStream;
            std::ostringstream  faceOStream;
            bool                state;
            bool                closed;
            Math::Matrix4D      vtxTransform;
            Math::Vector3DArray calcVtxNormals;
            const Material*     material;
            std::size_t         vtxCount;
            std::size_t         faceCount;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_PLYOBJECT3DWRITER_HPP
