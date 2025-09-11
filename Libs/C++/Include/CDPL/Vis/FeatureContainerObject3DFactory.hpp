/* 
 * FeatureContainerObject3DFactory.hpp 
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
 * \brief Definition of class CDPL::Vis::FeatureContainerObject3DFactory.
 */

#ifndef CDPL_VIS_FEATURECONTAINEROBJECT3DFACTORY_HPP
#define CDPL_VIS_FEATURECONTAINEROBJECT3DFACTORY_HPP

#include <memory>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Object3DFactory.hpp"
#include "CDPL/Vis/Shape3D.hpp"
#include "CDPL/Vis/ColorTable.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class FeatureContainer;
        class Feature;
    }
    
    namespace Vis
    {

        /**
         * \brief Class implementing the creation of Vis::Object3D instances providing a 
         *        3D representation of Pharm::FeatureContainer data objects for visualization purposes.
         * \since 1.3
         */
        class CDPL_VIS_API FeatureContainerObject3DFactory : public Object3DFactory<Pharm::FeatureContainer>
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FeatureContainerObject3DFactory instances.
             */
            typedef std::shared_ptr<FeatureContainerObject3DFactory> SharedPointer;

            Object3D::SharedPointer create(const Pharm::FeatureContainer& cntnr);

          private:
            void createHBondDonorFeatureRepr(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type, bool dual) const;
            void createHBondAcceptorFeatureRepr(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type, bool dual) const;
            void createHalogenBondDonorFeatureRepr(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type) const;
            void createHalogenBondAcceptorFeatureRepr(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type) const;
            void createAromaticFeatureRepr(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type) const;
            void createSphericalFeatureRepr(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type,
                                            const Shape3D::SharedPointer& shape, double z_rot = 0.0) const;
            void createArrowFeatureRepr(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type, bool outgoing, bool dual = false) const;

            void createFeatureCenterSphere(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type) const;

            void setMaterialProperty(Object3D& obj, unsigned int ftr_type, bool ftr_disabled, double col_alpha = -1.0) const;
            
            ColorTable::SharedPointer colorTable;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_FEATURECONTAINEROBJECT3DFACTORY_HPP
