/* 
 * AtomTypeExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Chem/AtomType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct AtomType {};
}


void CDPLPythonChem::exportAtomTypes()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<AtomType, boost::noncopyable>("AtomType", python::no_init)
        .def_readonly("UNKNOWN", &Chem::AtomType::UNKNOWN)
        .def_readonly("MAX_ATOMIC_NO", &Chem::AtomType::MAX_ATOMIC_NO)
        .def_readonly("MAX_TYPE", &Chem::AtomType::MAX_TYPE)
        .def_readonly("R", &Chem::AtomType::R)
        .def_readonly("A", &Chem::AtomType::A)
        .def_readonly("AH", &Chem::AtomType::AH)
        .def_readonly("ANY", &Chem::AtomType::ANY)
        .def_readonly("HET", &Chem::AtomType::HET)
        .def_readonly("Ac", &Chem::AtomType::Ac)
        .def_readonly("Ag", &Chem::AtomType::Ag)
        .def_readonly("Al", &Chem::AtomType::Al)
        .def_readonly("Am", &Chem::AtomType::Am)
        .def_readonly("Ar", &Chem::AtomType::Ar)
        .def_readonly("As", &Chem::AtomType::As)
        .def_readonly("At", &Chem::AtomType::At)
        .def_readonly("Au", &Chem::AtomType::Au)
        .def_readonly("B", &Chem::AtomType::B)
        .def_readonly("Ba", &Chem::AtomType::Ba)
        .def_readonly("Be", &Chem::AtomType::Be)
        .def_readonly("Bh", &Chem::AtomType::Bh)
        .def_readonly("Bi", &Chem::AtomType::Bi)
        .def_readonly("Bk", &Chem::AtomType::Bk)
        .def_readonly("Br", &Chem::AtomType::Br)
        .def_readonly("C", &Chem::AtomType::C)
        .def_readonly("Ca", &Chem::AtomType::Ca)
        .def_readonly("Cd", &Chem::AtomType::Cd)
        .def_readonly("Ce", &Chem::AtomType::Ce)
        .def_readonly("Cf", &Chem::AtomType::Cf)
        .def_readonly("Cl", &Chem::AtomType::Cl)
        .def_readonly("Cm", &Chem::AtomType::Cm)
        .def_readonly("Cn", &Chem::AtomType::Cn)
        .def_readonly("Co", &Chem::AtomType::Co)
        .def_readonly("Cr", &Chem::AtomType::Cr)
        .def_readonly("Cs", &Chem::AtomType::Cs)
        .def_readonly("Cu", &Chem::AtomType::Cu)
        .def_readonly("D", &Chem::AtomType::D)
        .def_readonly("Db", &Chem::AtomType::Db)
        .def_readonly("Ds", &Chem::AtomType::Ds)
        .def_readonly("Dy", &Chem::AtomType::Dy)
        .def_readonly("Er", &Chem::AtomType::Er)
        .def_readonly("Es", &Chem::AtomType::Es)
        .def_readonly("Eu", &Chem::AtomType::Eu)
        .def_readonly("F", &Chem::AtomType::F)
        .def_readonly("Fe", &Chem::AtomType::Fe)
        .def_readonly("Fm", &Chem::AtomType::Fm)
        .def_readonly("Fr", &Chem::AtomType::Fr)
        .def_readonly("Ga", &Chem::AtomType::Ga)
        .def_readonly("Gd", &Chem::AtomType::Gd)
        .def_readonly("Ge", &Chem::AtomType::Ge)
        .def_readonly("H", &Chem::AtomType::H)
        .def_readonly("He", &Chem::AtomType::He)
        .def_readonly("Hf", &Chem::AtomType::Hf)
        .def_readonly("Hg", &Chem::AtomType::Hg)
        .def_readonly("Ho", &Chem::AtomType::Ho)
        .def_readonly("Hs", &Chem::AtomType::Hs)
        .def_readonly("I", &Chem::AtomType::I)
        .def_readonly("In", &Chem::AtomType::In)
        .def_readonly("Ir", &Chem::AtomType::Ir)
        .def_readonly("K", &Chem::AtomType::K)
        .def_readonly("Kr", &Chem::AtomType::Kr)
        .def_readonly("La", &Chem::AtomType::La)
        .def_readonly("Li", &Chem::AtomType::Li)
        .def_readonly("Lr", &Chem::AtomType::Lr)
        .def_readonly("Lu", &Chem::AtomType::Lu)
        .def_readonly("M", &Chem::AtomType::M)
        .def_readonly("MH", &Chem::AtomType::MH)
        .def_readonly("Md", &Chem::AtomType::Md)
        .def_readonly("Mg", &Chem::AtomType::Mg)
        .def_readonly("Mn", &Chem::AtomType::Mn)
        .def_readonly("Mo", &Chem::AtomType::Mo)
        .def_readonly("Mt", &Chem::AtomType::Mt)
        .def_readonly("N", &Chem::AtomType::N)
        .def_readonly("Na", &Chem::AtomType::Na)
        .def_readonly("Nb", &Chem::AtomType::Nb)
        .def_readonly("Nd", &Chem::AtomType::Nd)
        .def_readonly("Ne", &Chem::AtomType::Ne)
        .def_readonly("Nh", &Chem::AtomType::Nh)
        .def_readonly("Ni", &Chem::AtomType::Ni)
        .def_readonly("No", &Chem::AtomType::No)
        .def_readonly("Np", &Chem::AtomType::Np)
        .def_readonly("O", &Chem::AtomType::O)
        .def_readonly("Os", &Chem::AtomType::Os)
        .def_readonly("P", &Chem::AtomType::P)
        .def_readonly("Pa", &Chem::AtomType::Pa)
        .def_readonly("Pb", &Chem::AtomType::Pb)
        .def_readonly("Pd", &Chem::AtomType::Pd)
        .def_readonly("Pm", &Chem::AtomType::Pm)
        .def_readonly("Po", &Chem::AtomType::Po)
        .def_readonly("Pr", &Chem::AtomType::Pr)
        .def_readonly("Pt", &Chem::AtomType::Pt)
        .def_readonly("Pu", &Chem::AtomType::Pu)
        .def_readonly("Q", &Chem::AtomType::Q)
        .def_readonly("QH", &Chem::AtomType::QH)
        .def_readonly("Ra", &Chem::AtomType::Ra)
        .def_readonly("Rb", &Chem::AtomType::Rb)
        .def_readonly("Re", &Chem::AtomType::Re)
        .def_readonly("Rf", &Chem::AtomType::Rf)
        .def_readonly("Rg", &Chem::AtomType::Rg)
        .def_readonly("Rh", &Chem::AtomType::Rh)
        .def_readonly("Rn", &Chem::AtomType::Rn)
        .def_readonly("Ru", &Chem::AtomType::Ru)
        .def_readonly("S", &Chem::AtomType::S)
        .def_readonly("Sb", &Chem::AtomType::Sb)
        .def_readonly("Sc", &Chem::AtomType::Sc)
        .def_readonly("Se", &Chem::AtomType::Se)
        .def_readonly("Sg", &Chem::AtomType::Sg)
        .def_readonly("Si", &Chem::AtomType::Si)
        .def_readonly("Sm", &Chem::AtomType::Sm)
        .def_readonly("Sn", &Chem::AtomType::Sn)
        .def_readonly("Sr", &Chem::AtomType::Sr)
        .def_readonly("T", &Chem::AtomType::T)
        .def_readonly("Ta", &Chem::AtomType::Ta)
        .def_readonly("Tb", &Chem::AtomType::Tb)
        .def_readonly("Tc", &Chem::AtomType::Tc)
        .def_readonly("Te", &Chem::AtomType::Te)
        .def_readonly("Th", &Chem::AtomType::Th)
        .def_readonly("Ti", &Chem::AtomType::Ti)
        .def_readonly("Tl", &Chem::AtomType::Tl)
        .def_readonly("Tm", &Chem::AtomType::Tm)
        .def_readonly("U", &Chem::AtomType::U)
        .def_readonly("V", &Chem::AtomType::V)
        .def_readonly("W", &Chem::AtomType::W)
        .def_readonly("X", &Chem::AtomType::X)
        .def_readonly("XH", &Chem::AtomType::XH)
        .def_readonly("Xe", &Chem::AtomType::Xe)
        .def_readonly("Y", &Chem::AtomType::Y)
        .def_readonly("Yb", &Chem::AtomType::Yb)
        .def_readonly("Zn", &Chem::AtomType::Zn)
        .def_readonly("Zr", &Chem::AtomType::Zr);
}
