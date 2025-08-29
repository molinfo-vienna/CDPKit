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
#include "CDPL/Vis/DefaultFeatureColorTable.hpp"
#include "CDPL/Vis/Material.hpp"
#include "CDPL/Vis/TriangleMesh3DFunctions.hpp"
#include "CDPL/Vis/Object3DFunctions.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/AffineTransform.hpp"
#include "CDPL/Util/BitSet.hpp"


using namespace CDPL;


namespace
{

    std::once_flag initTriangleMeshesFlag;

    Vis::TriangleMesh3D::SharedPointer sphereMesh;
    Vis::TriangleMesh3D::SharedPointer icosahedronMesh;
    Vis::TriangleMesh3D::SharedPointer nonDirectedDonorAceptorFeatureMesh;
    Vis::TriangleMesh3D::SharedPointer directedAromaticFeatureMesh;
    Vis::TriangleMesh3D::SharedPointer ionizableFeatureMesh;
    Vis::TriangleMesh3D::SharedPointer arrowShaftMesh;
    Vis::TriangleMesh3D::SharedPointer upArrowHeadMesh;
    Vis::TriangleMesh3D::SharedPointer downArrowHeadMesh;
    
    void initTriangleMeshes()
    {
        using namespace Vis;

        icosahedronMesh.reset(new IcosahedronMesh3D());
        
        // ---        

        sphereMesh.reset(new IcosahedronMesh3D());

        for (std::size_t i = 0; i < 2; i++) {
            subdivideSpherical(*sphereMesh);
            removeVertexDuplicates(*sphereMesh);
        }
    
        // ---

        nonDirectedDonorAceptorFeatureMesh.reset(new TriangleMesh3D());

        nonDirectedDonorAceptorFeatureMesh->addVertex(0.0, 0.0, 1.0);
        nonDirectedDonorAceptorFeatureMesh->addVertexNormal(0.0, 0.0, 1.0);
        nonDirectedDonorAceptorFeatureMesh->addVertex(1.0, 0.0, 0.0);
        nonDirectedDonorAceptorFeatureMesh->addVertexNormal(1.0, 0.0, 0.0);
        nonDirectedDonorAceptorFeatureMesh->addVertex(0.0, 1.0, 0.0);
        nonDirectedDonorAceptorFeatureMesh->addVertexNormal(0.0, 1.0, 0.0);
        nonDirectedDonorAceptorFeatureMesh->addFace(0, 1, 2);

        for (std::size_t i = 0; i < 3; i++) {
            subdivideSpherical(*nonDirectedDonorAceptorFeatureMesh);
            removeVertexDuplicates(*nonDirectedDonorAceptorFeatureMesh);
        }

        auto num_prev_verts = nonDirectedDonorAceptorFeatureMesh->getNumVertices();

        *nonDirectedDonorAceptorFeatureMesh += *nonDirectedDonorAceptorFeatureMesh;

        rotateY(*nonDirectedDonorAceptorFeatureMesh, M_PI, num_prev_verts);

        num_prev_verts = nonDirectedDonorAceptorFeatureMesh->getNumVertices();

        *nonDirectedDonorAceptorFeatureMesh += *nonDirectedDonorAceptorFeatureMesh;

        rotateX(*nonDirectedDonorAceptorFeatureMesh, M_PI, num_prev_verts);

        // ---

        directedAromaticFeatureMesh.reset(new TorusMesh3D(0.5, 0.5, 36, 11, M_PI / 2.0, M_PI));

        scale(*directedAromaticFeatureMesh, 1.0, 1.0, 0.4);
        translate(*directedAromaticFeatureMesh, 0.0, 0.0, 0.4);

        num_prev_verts = directedAromaticFeatureMesh->getNumVertices();
    
        *directedAromaticFeatureMesh += *directedAromaticFeatureMesh;

        rotateX(*directedAromaticFeatureMesh, M_PI, num_prev_verts);

        RightFrustumMesh3D cyl_mesh(0.1, 0.1, 0.8, 10, true, true);

        translate(cyl_mesh, 0.0, 0.0, -0.4);

        *directedAromaticFeatureMesh += cyl_mesh;

        RightFrustumMesh3D cone_mesh1(0.15, 0.0, 0.35, 5, true);

        translate(cone_mesh1, 0.0, 0.0, 0.9);

        *directedAromaticFeatureMesh += cone_mesh1;

        rotateX(cone_mesh1, M_PI);

        *directedAromaticFeatureMesh += cone_mesh1;
 
        // ---

        RightFrustumMesh3D cone_mesh2(0.0, 0.15, 1.0, 12, false, true);
        
        ionizableFeatureMesh.reset(new TriangleMesh3D());

        for (std::size_t i = 0; i < 12; i++) {
            auto ico_vtx = icosahedronMesh->getVertices()[i].getData();

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

        ionizableFeatureMesh->setSolid();
        
        // ---

        arrowShaftMesh.reset(new RightFrustumMesh3D(0.1, 0.1, 1.0, 20, true, true));
        upArrowHeadMesh.reset(new RightFrustumMesh3D(0.2, 0.0, 0.25, 20, true, false));
        downArrowHeadMesh.reset(new RightFrustumMesh3D(0.0, 0.2, 0.25, 20, false, true));
    }

    void calcZAxisAlignmentTransform(const Math::Vector3D& dir, Math::Matrix4D& rot_mtx)
    {
        auto r = std::sqrt(dir[0] * dir[0] + dir[1] * dir[1]);

        if (r == 0.0) {
            rot_mtx = Math::IdentityMatrix<double>(4, 4);
            return;
        }

        auto z_rot = (dir[1] >= 0.0 ? 1.0 : -1.0) * std::acos(dir[0] / r);
        auto y_rot = std::acos(dir[2]);

        rot_mtx = Math::RotationMatrix<double>(4, z_rot, 0.0, 0.0, 1.0) * Math::RotationMatrix<double>(4, y_rot, 0.0, 1.0, 0.0);
    }

    constexpr double MAT_SPEC_COLOR_RGB_INCREMENT = 0.5;
    constexpr double MAT_SHININESS                = 0.1;
    constexpr double MAT_AMBIENT_FACTOR           = 0.35;
}


Vis::Object3D::SharedPointer Vis::FeatureContainerObject3DFactory::create(const Pharm::FeatureContainer& cntnr)
{
    std::call_once(initTriangleMeshesFlag, &initTriangleMeshes);

    colorTable = getFeatureColorTableParameter(*this);
    
    Object3D::SharedPointer obj_ptr(new Object3D());

    auto num_ftrs = cntnr.getNumFeatures();

    Util::BitSet dual_hb_ftr_mask(num_ftrs);
    
    for (std::size_t i = 0; i < num_ftrs; i++) {
        if (dual_hb_ftr_mask.test(i))
            continue;
        
        auto& ftr1 = cntnr.getFeature(i);

        if (!has3DCoordinates(ftr1))
            continue;

        if (!hasOrientation(ftr1))
            continue;
     
        auto ftr1_type = getType(ftr1);
        auto& ftr1_pos = get3DCoordinates(ftr1);
        auto& ftr1_orient = getOrientation(ftr1);
        
        if ((ftr1_type != Pharm::FeatureType::H_BOND_DONOR) && (ftr1_type != Pharm::FeatureType::H_BOND_ACCEPTOR))
            continue;

        for (std::size_t j = i + 1; j < num_ftrs; j++) {
            if (dual_hb_ftr_mask.test(j))
                continue;

            auto& ftr2 = cntnr.getFeature(j);

            if (!has3DCoordinates(ftr2))
                continue;

            if (!hasOrientation(ftr2))
                continue;
        
            auto ftr2_type = getType(ftr2);

            if ((ftr2_type != Pharm::FeatureType::H_BOND_DONOR) && (ftr2_type != Pharm::FeatureType::H_BOND_ACCEPTOR))
                continue;

            if (ftr1_type == ftr2_type)
                continue;

            if (ftr1_pos != get3DCoordinates(ftr2))
                continue;

            if (ftr1_orient != (getOrientation(ftr2) * -1.0))
                continue;

            dual_hb_ftr_mask.set(i);
            dual_hb_ftr_mask.set(j);
            break;
        }
    }
      
    for (std::size_t i = 0; i < num_ftrs; i++) {
        auto& ftr = cntnr.getFeature(i);

        if (!has3DCoordinates(ftr))
            continue;

        auto ftr_type = getType(ftr);
        
        switch (ftr_type) {

            case Pharm::FeatureType::POSITIVE_IONIZABLE:
            case Pharm::FeatureType::NEGATIVE_IONIZABLE:
                createSphericalFeatureRepr(*obj_ptr, ftr, ftr_type, ionizableFeatureMesh);
                continue;

            case Pharm::FeatureType::H_BOND_DONOR:
                createHBondDonorFeatureRepr(*obj_ptr, ftr, ftr_type, dual_hb_ftr_mask.test(i));
                continue;

            case Pharm::FeatureType::H_BOND_ACCEPTOR:
                createHBondAcceptorFeatureRepr(*obj_ptr, ftr, ftr_type, dual_hb_ftr_mask.test(i));
                continue;

            case Pharm::FeatureType::HALOGEN_BOND_ACCEPTOR:
                createHalogenBondAcceptorFeatureRepr(*obj_ptr, ftr, ftr_type);
                continue;

            case Pharm::FeatureType::HALOGEN_BOND_DONOR:
                createHalogenBondDonorFeatureRepr(*obj_ptr, ftr, ftr_type);
                continue;

            case Pharm::FeatureType::AROMATIC:
                createAromaticFeatureRepr(*obj_ptr, ftr, ftr_type);
                continue;

            default:
                createSphericalFeatureRepr(*obj_ptr, ftr, ftr_type, sphereMesh);
        }
    }
    
    return obj_ptr;
}

void Vis::FeatureContainerObject3DFactory::createHBondDonorFeatureRepr(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type, bool dual) const
{
    if (!hasOrientation(ftr)) {
        createSphericalFeatureRepr(parent_obj, ftr, ftr_type, nonDirectedDonorAceptorFeatureMesh, M_PI / 2.0);
        return;
    }

    createArrowFeatureRepr(parent_obj, ftr, ftr_type, true, dual);
}

void Vis::FeatureContainerObject3DFactory::createHBondAcceptorFeatureRepr(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type, bool dual) const
{
    if (!hasOrientation(ftr)) {
        createSphericalFeatureRepr(parent_obj, ftr, ftr_type, nonDirectedDonorAceptorFeatureMesh);
        return;
    }

    createArrowFeatureRepr(parent_obj, ftr, ftr_type, false, dual);
}

void Vis::FeatureContainerObject3DFactory::createHalogenBondDonorFeatureRepr(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type) const
{
    if (!hasOrientation(ftr)) {
        createSphericalFeatureRepr(parent_obj, ftr, ftr_type, nonDirectedDonorAceptorFeatureMesh);
        return;
    }

    createArrowFeatureRepr(parent_obj, ftr, ftr_type, true);
}

void Vis::FeatureContainerObject3DFactory::createHalogenBondAcceptorFeatureRepr(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type) const
{
    if (!hasOrientation(ftr)) {
        createSphericalFeatureRepr(parent_obj, ftr, ftr_type, icosahedronMesh);
        return;
    }

    createArrowFeatureRepr(parent_obj, ftr, ftr_type, false);
}

void Vis::FeatureContainerObject3DFactory::createAromaticFeatureRepr(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type) const
{
    if (!hasOrientation(ftr)) {
        createSphericalFeatureRepr(parent_obj, ftr, ftr_type, sphereMesh);
        return;
    }
    
    Object3D::SharedPointer obj_ptr(new Object3D());
    auto& pos = get3DCoordinates(ftr);
    auto tol = getTolerance(ftr);
    Math::Matrix4D rot_mtx;
    
    calcZAxisAlignmentTransform(getOrientation(ftr), rot_mtx);

    setTransformationMatrix(*obj_ptr, Math::TranslationMatrix<double>(4, pos[0], pos[1], pos[2]) * rot_mtx *
                            Math::ScalingMatrix<double>(4, tol, tol, tol));
     
    setShape(*obj_ptr, directedAromaticFeatureMesh);
    setMaterialProperty(*obj_ptr, ftr_type);
    
    parent_obj.addSubObject(obj_ptr);
}

void Vis::FeatureContainerObject3DFactory::createSphericalFeatureRepr(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type,
                                                                      const Shape3D::SharedPointer& shape, double z_rot) const
{
    Object3D::SharedPointer obj_ptr(new Object3D());
    auto& pos = get3DCoordinates(ftr);
    auto tol = getTolerance(ftr);

    if (z_rot != 0.0)
        setTransformationMatrix(*obj_ptr, Math::TranslationMatrix<double>(4, pos[0], pos[1], pos[2]) *
                                Math::ScalingMatrix<double>(4, tol, tol, tol) *
                                Math::RotationMatrix<double>(4, z_rot, 0.0, 0.0, 1.0));
    else
        setTransformationMatrix(*obj_ptr, Math::TranslationMatrix<double>(4, pos[0], pos[1], pos[2]) *
                                Math::ScalingMatrix<double>(4, tol, tol, tol));
    
    setShape(*obj_ptr, shape);
    setMaterialProperty(*obj_ptr, ftr_type);
    
    parent_obj.addSubObject(obj_ptr);
}

void Vis::FeatureContainerObject3DFactory::createArrowFeatureRepr(Object3D& parent_obj, const Pharm::Feature& ftr, unsigned int ftr_type,
                                                                  bool outgoing, bool dual) const
{
    Object3D::SharedPointer arrow_head_obj_ptr(new Object3D());
    Object3D::SharedPointer arrow_shaft_obj_ptr(new Object3D());

    if (outgoing) {
        setTransformationMatrix(*arrow_head_obj_ptr, Math::TranslationMatrix<double>(4, 0.0, 0.0, 0.75));
        setTransformationMatrix(*arrow_shaft_obj_ptr, Math::ScalingMatrix<double>(4, 1.0, 1.0, 0.77));

        setShape(*arrow_head_obj_ptr, upArrowHeadMesh);

    } else {
        setTransformationMatrix(*arrow_shaft_obj_ptr, Math::TranslationMatrix<double>(4, 0.0, 0.0, 0.23) *
                                Math::ScalingMatrix<double>(4, 1.0, 1.0, 0.77));

        setShape(*arrow_head_obj_ptr, downArrowHeadMesh);    
    }
    
    setShape(*arrow_shaft_obj_ptr, arrowShaftMesh);
 
    Object3D::SharedPointer arrow_obj_ptr(new Object3D());
    auto& pos = get3DCoordinates(ftr);
    Math::Matrix4D rot_mtx;
    
    calcZAxisAlignmentTransform(getOrientation(ftr) * (outgoing ? 1.0 : -1.0), rot_mtx);

    if (outgoing && dual) {
        auto half_length = getLength(ftr) * 0.5;
        
        setTransformationMatrix(*arrow_obj_ptr, Math::TranslationMatrix<double>(4, pos[0], pos[1], pos[2]) * rot_mtx *
                                Math::TranslationMatrix<double>(4, 0.0, 0.0, half_length) *
                                Math::ScalingMatrix<double>(4, 1.0, 1.0, half_length));
    } else
        setTransformationMatrix(*arrow_obj_ptr, Math::TranslationMatrix<double>(4, pos[0], pos[1], pos[2]) * rot_mtx *
                                Math::ScalingMatrix<double>(4, 1.0, 1.0, getLength(ftr) * (dual ? 0.5 : 1.0)));

    arrow_obj_ptr->addSubObject(arrow_head_obj_ptr);
    arrow_obj_ptr->addSubObject(arrow_shaft_obj_ptr);

    setMaterialProperty(*arrow_obj_ptr, ftr_type);
        
    parent_obj.addSubObject(arrow_obj_ptr);
}

void Vis::FeatureContainerObject3DFactory::setMaterialProperty(Object3D& obj, unsigned int ftr_type) const
{
    static const DefaultFeatureColorTable DEF_FTR_COLORS;

    const Color* color = nullptr;
    
    if (colorTable) {
        auto it = colorTable->getEntry(ftr_type);

        if (it != colorTable->end())
            color = &it->second;
    }

    if (!color) {
        auto it = DEF_FTR_COLORS.getEntry(ftr_type);

        if (it != DEF_FTR_COLORS.end())
            color = &it->second;
    }

    if (!color)
        color = &DEF_FTR_COLORS[Pharm::FeatureType::UNKNOWN];
                             
    setMaterial(obj, Material(MAT_AMBIENT_FACTOR, *color,
                              Color(color->getRed() + MAT_SPEC_COLOR_RGB_INCREMENT,
                                    color->getGreen() + MAT_SPEC_COLOR_RGB_INCREMENT,
                                    color->getBlue() + MAT_SPEC_COLOR_RGB_INCREMENT,
                                    color->getAlpha()),
                              MAT_SHININESS, 1.0 - color->getAlpha()));
}
