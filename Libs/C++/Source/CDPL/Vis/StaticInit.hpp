/* 
 * StaticInit.hpp 
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


#ifndef CDPL_VIS_STATICINIT_HPP
#define CDPL_VIS_STATICINIT_HPP

#ifdef CDPL_VIS_STATIC_LINK


namespace CDPL
{

    namespace Vis
    {

        void initAtomProperties();
        void initBondProperties();
        void initMolecularGraphProperties();
        void initReactionProperties();
        void initObject3DProperties();
        void initAtomPropertyDefaults();
        void initBondPropertyDefaults();
        void initMolecularGraphPropertyDefaults();
        void initReactionPropertyDefaults();
        void initObject3DPropertyDefaults();
        void initControlParameters();
        void initControlParameterDefaults();
        void initDataFormats();
    } // namespace Vis
} // namespace CDPL

namespace
{

    struct CDPLVisInit
    {

        CDPLVisInit()
        {
            CDPL::Vis::initAtomProperties();
            CDPL::Vis::initBondProperties();
            CDPL::Vis::initMolecularGraphProperties();
            CDPL::Vis::initReactionProperties();
            CDPL::Vis::initAtomPropertyDefaults();
            CDPL::Vis::initBondPropertyDefaults();
            CDPL::Vis::initMolecularGraphPropertyDefaults();
            CDPL::Vis::initReactionPropertyDefaults();
            CDPL::Vis::initControlParameters();
            CDPL::Vis::initControlParameterDefaults();
            CDPL::Vis::initDataFormats();
        }

    } cdplVisInit;
} // namespace

#endif // CDPL_VIS_STATIC_LINK

#endif // CDPL_VIS_STATICINIT_HPP
