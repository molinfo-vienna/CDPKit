/* 
 * STLObject3DWriter.hpp 
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
 * \brief Definition of the class CDPL::Vis::STLObject3DWriter.
 */

#ifndef CDPL_VIS_STLOBJECT3DWRITER_HPP
#define CDPL_VIS_STLOBJECT3DWRITER_HPP

#include <iosfwd>
#include <vector>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Shape3DVisitor.hpp"
#include "CDPL/Base/DataWriter.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Vis
    {

        class Object3D;

        /**
         * \brief Outputs 3D visualization data represented by Vis::Object3D instances in the <em>STL</em> [\ref STLFMT] format. 
         * \since 1.3
         */
        class CDPL_VIS_API STLObject3DWriter : public Base::DataWriter<Object3D>, private Shape3DVisitor
        {

          public:
            /**
             * \brief Constructs a \c %STLObject3DWriter instance that will write Vis::Object3D data to the output stream \a os.
             * \param os The output stream to write to.
             */
            STLObject3DWriter(std::ostream& os);

            STLObject3DWriter(const STLObject3DWriter&) = delete;

            ~STLObject3DWriter();
            
            /**
             * \brief Outputs the Vis::Object3D instance \a obj.
             * \param obj The Vis::Object3D instance to output.
             * \return A reference to itself.
             */
            Base::DataWriter<Object3D>& write(const Object3D& obj);

            operator const void*() const;
            bool operator!() const;

            STLObject3DWriter& operator=(const STLObject3DWriter&) = delete;

            void close();
            
          private:
            void process(const Object3D& obj);
            void visitTriangleMesh(const TriangleMesh3D& mesh);

            typedef std::vector<Math::Vector3D> VertexArray;

            std::ostream&  output;
            bool           state;
            bool           headerWritten;
            Math::Matrix4D vtxTransform;
            VertexArray    transVertices;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_STLOBJECT3DWRITER_HPP
