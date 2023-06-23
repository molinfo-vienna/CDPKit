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


#ifndef CDPL_BIOMOL_STATICINIT_HPP
#define CDPL_BIOMOL_STATICINIT_HPP

#ifdef CDPL_BIOMOL_STATIC_LINK


namespace CDPL
{

    namespace Biomol
    {

        void initAtomProperties();
        void initMolecularGraphProperties();
        void initAtomPropertyDefaults();
        void initMolecularGraphPropertyDefaults();
        void initControlParameters();
        void initControlParameterDefaults();
        void initDataFormats();
    }
}

namespace
{

    struct CDPLBiomolInit
    {

        CDPLBiomolInit() {
            CDPL::Biomol::initAtomProperties();
            CDPL::Biomol::initAtomPropertyDefaults();
            CDPL::Biomol::initMolecularGraphProperties();
            CDPL::Biomol::initMolecularGraphPropertyDefaults();
            CDPL::Biomol::initControlParameters();
            CDPL::Biomol::initControlParameterDefaults();
            CDPL::Biomol::initDataFormats();
        }

    } cdplBiomolInit;
}

#endif // CDPL_BIOMOL_STATIC_LINK

#endif // CDPL_BIOMOL_STATICINIT_HPP
