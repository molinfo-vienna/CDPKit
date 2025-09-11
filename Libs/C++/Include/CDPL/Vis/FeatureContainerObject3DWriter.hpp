/* 
 * FeatureContainerObject3DWriter.hpp 
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
 * \brief Definition of class CDPL::Vis::FeatureContainerObject3DWriter.
 */

#ifndef CDPL_VIS_FEATURECONTAINEROBJECT3DWRITER_HPP
#define CDPL_VIS_FEATURECONTAINEROBJECT3DWRITER_HPP

#include <iosfwd>
#include <functional>

#include "CDPL/Vis/FeatureContainerObject3DFactory.hpp"
#include "CDPL/Base/DataWriter.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Vis
    {

        template <typename WriterImpl>
        class FeatureContainerObject3DWriter : public Base::DataWriter<Pharm::FeatureContainer>
        {

          public:
            /**
             * \brief Constructs a \c %FeatureContainerObject3DWriter instance that will write 3D models of Pharm::FeatureContainer objects to the output stream \a os.
             * \param os The output stream to write to.
             */
            FeatureContainerObject3DWriter(std::ostream& os);
            FeatureContainerObject3DWriter(const FeatureContainerObject3DWriter&) = delete;

            ~FeatureContainerObject3DWriter();

            Base::DataWriter<Pharm::FeatureContainer>& write(const Pharm::FeatureContainer& cntnr);

            operator const void*() const;
            bool operator!() const;

            FeatureContainerObject3DWriter& operator=(const FeatureContainerObject3DWriter&) = delete;

            void close();

          private:
            FeatureContainerObject3DFactory o3dFactory;
            WriterImpl                      o3dWriter;
        };
    } // namespace Vis
} // namespace CDPL


// Implementation

template <typename WriterImpl>
CDPL::Vis::FeatureContainerObject3DWriter<WriterImpl>::FeatureContainerObject3DWriter(std::ostream& os):
    o3dWriter(os)
{
    o3dFactory.setParent(this);

    o3dWriter.setParent(this);
    o3dWriter.registerIOCallback(std::bind(&Base::DataIOBase::invokeIOCallbacks, this, std::placeholders::_2));
}

template <typename WriterImpl>
CDPL::Vis::FeatureContainerObject3DWriter<WriterImpl>::~FeatureContainerObject3DWriter()
{
    close();
}

template <typename WriterImpl>
CDPL::Base::DataWriter<CDPL::Pharm::FeatureContainer>& CDPL::Vis::FeatureContainerObject3DWriter<WriterImpl>::write(const Pharm::FeatureContainer& cntnr)
{
    try {
        auto obj = o3dFactory.create(cntnr);
        
        o3dWriter.write(*obj);

    } catch (const std::exception& e) {
        throw Base::IOError(std::string("FeatureContainerObject3DWriter: ") + e.what());
    }

    return *this;
}

template <typename WriterImpl>
CDPL::Vis::FeatureContainerObject3DWriter<WriterImpl>::operator const void*() const
{
    return o3dWriter.operator const void*();
}

template <typename WriterImpl>
bool CDPL::Vis::FeatureContainerObject3DWriter<WriterImpl>::operator!() const
{
    return o3dWriter.operator!();
}

template <typename WriterImpl>
void CDPL::Vis::FeatureContainerObject3DWriter<WriterImpl>::close()
{
    o3dWriter.close();
}

#endif // CDPL_VIS_FEATURECONTAINEROBJECT3DWRITER_HPP
