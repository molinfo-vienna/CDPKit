/* 
 * AtomType.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::AtomType.
 */

#ifndef CDPL_CHEM_ATOMTYPE_HPP
#define CDPL_CHEM_ATOMTYPE_HPP


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides constants for the specification of the chemical element or generic type of an atom.
         *
         * For constants with a name equal to the symbol of a chemical element, the value of the constant
         * corresponds to the atomic number of the respective element. %Atom types with a value higher
         * than AtomType::MAX_ATOMIC_NO are generic atom types that represent a set of chemical elements. 
         */
        namespace AtomType
        {

            /**
             * \brief Specifies an atom with an unknown or undefined atom type.
             */
            constexpr unsigned int UNKNOWN = 0;

            /**
             * \brief Specifies \e Hydrogen.
             */
            constexpr unsigned int H = 1;

            /**
             * \brief Specifies <em>Hydrogen (Deuterium)</em>.
             */
            constexpr unsigned int D = 1;

            /**
             * \brief Specifies <em>Hydrogen (Tritium)</em>.
             */
            constexpr unsigned int T = 1;

            /**
             * \brief Specifies \e Helium.
             */
            constexpr unsigned int He = 2;

            /**
             * \brief Specifies \e Lithium.
             */
            constexpr unsigned int Li = 3;

            /**
             * \brief Specifies \e Beryllium.
             */
            constexpr unsigned int Be = 4;

            /**
             * \brief Specifies \e Boron.
             */
            constexpr unsigned int B = 5;

            /**
             * \brief Specifies \e Carbon.
             */
            constexpr unsigned int C = 6;

            /**
             * \brief Specifies \e Nitrogen.
             */
            constexpr unsigned int N = 7;

            /**
             * \brief Specifies \e Oxygen.
             */
            constexpr unsigned int O = 8;

            /**
             * \brief Specifies \e Fluorine.
             */
            constexpr unsigned int F = 9;

            /**
             * \brief Specifies \e Neon.
             */
            constexpr unsigned int Ne = 10;

            /**
             * \brief Specifies \e Sodium.
             */
            constexpr unsigned int Na = 11;

            /**
             * \brief Specifies \e Magnesium.
             */
            constexpr unsigned int Mg = 12;

            /**
             * \brief Specifies \e Aluminium.
             */
            constexpr unsigned int Al = 13;

            /**
             * \brief Specifies \e Silicon.
             */
            constexpr unsigned int Si = 14;

            /**
             * \brief Specifies \e Phosphorus.
             */
            constexpr unsigned int P = 15;

            /**
             * \brief Specifies \e Sulfur.
             */
            constexpr unsigned int S = 16;

            /**
             * \brief Specifies \e Chlorine.
             */
            constexpr unsigned int Cl = 17;

            /**
             * \brief Specifies \e Argon.
             */
            constexpr unsigned int Ar = 18;

            /**
             * \brief Specifies \e Potassium.
             */
            constexpr unsigned int K = 19;

            /**
             * \brief Specifies \e Calcium.
             */
            constexpr unsigned int Ca = 20;

            /**
             * \brief Specifies \e Scandium.
             */
            constexpr unsigned int Sc = 21;

            /**
             * \brief Specifies \e Titanium.
             */
            constexpr unsigned int Ti = 22;

            /**
             * \brief Specifies \e Vanadium.
             */
            constexpr unsigned int V = 23;

            /**
             * \brief Specifies \e Chromium.
             */
            constexpr unsigned int Cr = 24;

            /**
             * \brief Specifies \e Manganese.
             */
            constexpr unsigned int Mn = 25;

            /**
             * \brief Specifies \e Iron.
             */
            constexpr unsigned int Fe = 26;

            /**
             * \brief Specifies \e Cobalt.
             */
            constexpr unsigned int Co = 27;

            /**
             * \brief Specifies \e Nickel.
             */
            constexpr unsigned int Ni = 28;

            /**
             * \brief Specifies \e Copper.
             */
            constexpr unsigned int Cu = 29;

            /**
             * \brief Specifies \e Zinc.
             */
            constexpr unsigned int Zn = 30;

            /**
             * \brief Specifies \e Gallium.
             */
            constexpr unsigned int Ga = 31;

            /**
             * \brief Specifies \e Germanium.
             */
            constexpr unsigned int Ge = 32;

            /**
             * \brief Specifies \e Arsenic.
             */
            constexpr unsigned int As = 33;

            /**
             * \brief Specifies \e Selenium.
             */
            constexpr unsigned int Se = 34;

            /**
             * \brief Specifies \e Bromine.
             */
            constexpr unsigned int Br = 35;

            /**
             * \brief Specifies \e Krypton.
             */
            constexpr unsigned int Kr = 36;

            /**
             * \brief Specifies \e Rubidium.
             */
            constexpr unsigned int Rb = 37;

            /**
             * \brief Specifies \e Strontium.
             */
            constexpr unsigned int Sr = 38;

            /**
             * \brief Specifies \e Yttrium.
             */
            constexpr unsigned int Y = 39;

            /**
             * \brief Specifies \e Zirconium.
             */
            constexpr unsigned int Zr = 40;

            /**
             * \brief Specifies \e Niobium.
             */
            constexpr unsigned int Nb = 41;

            /**
             * \brief Specifies \e Molybdenum.
             */
            constexpr unsigned int Mo = 42;

            /**
             * \brief Specifies \e Technetium.
             */
            constexpr unsigned int Tc = 43;

            /**
             * \brief Specifies \e Ruthenium.
             */
            constexpr unsigned int Ru = 44;

            /**
             * \brief Specifies \e Rhodium.
             */
            constexpr unsigned int Rh = 45;

            /**
             * \brief Specifies \e Palladium.
             */
            constexpr unsigned int Pd = 46;

            /**
             * \brief Specifies \e Silver.
             */
            constexpr unsigned int Ag = 47;

            /**
             * \brief Specifies \e Cadmium.
             */
            constexpr unsigned int Cd = 48;

            /**
             * \brief Specifies \e Indium.
             */
            constexpr unsigned int In = 49;

            /**
             * \brief Specifies \e Tin.
             */
            constexpr unsigned int Sn = 50;

            /**
             * \brief Specifies \e Antimony.
             */
            constexpr unsigned int Sb = 51;

            /**
             * \brief Specifies \e Tellurium.
             */
            constexpr unsigned int Te = 52;

            /**
             * \brief Specifies \e Iodine.
             */
            constexpr unsigned int I = 53;

            /**
             * \brief Specifies \e Xenon.
             */
            constexpr unsigned int Xe = 54;

            /**
             * \brief Specifies \e Caesium.
             */
            constexpr unsigned int Cs = 55;

            /**
             * \brief Specifies \e Barium.
             */
            constexpr unsigned int Ba = 56;

            /**
             * \brief Specifies \e Lanthanum.
             */
            constexpr unsigned int La = 57;

            /**
             * \brief Specifies \e Cerium.
             */
            constexpr unsigned int Ce = 58;

            /**
             * \brief Specifies \e Praseodymium.
             */
            constexpr unsigned int Pr = 59;

            /**
             * \brief Specifies \e Neodymium.
             */
            constexpr unsigned int Nd = 60;

            /**
             * \brief Specifies \e Promethium.
             */
            constexpr unsigned int Pm = 61;

            /**
             * \brief Specifies \e Samarium.
             */
            constexpr unsigned int Sm = 62;

            /**
             * \brief Specifies \e Europium.
             */
            constexpr unsigned int Eu = 63;

            /**
             * \brief Specifies \e Gadolinium.
             */
            constexpr unsigned int Gd = 64;

            /**
             * \brief Specifies \e Terbium.
             */
            constexpr unsigned int Tb = 65;

            /**
             * \brief Specifies \e Dysprosium.
             */
            constexpr unsigned int Dy = 66;

            /**
             * \brief Specifies \e Holmium.
             */
            constexpr unsigned int Ho = 67;

            /**
             * \brief Specifies \e Erbium.
             */
            constexpr unsigned int Er = 68;

            /**
             * \brief Specifies \e Thulium.
             */
            constexpr unsigned int Tm = 69;

            /**
             * \brief Specifies \e Ytterbium.
             */
            constexpr unsigned int Yb = 70;

            /**
             * \brief Specifies \e Lutetium.
             */
            constexpr unsigned int Lu = 71;

            /**
             * \brief Specifies \e Hafnium.
             */
            constexpr unsigned int Hf = 72;

            /**
             * \brief Specifies \e Tantalum.
             */
            constexpr unsigned int Ta = 73;

            /**
             * \brief Specifies \e Tungsten.
             */
            constexpr unsigned int W = 74;

            /**
             * \brief Specifies \e Rhenium.
             */
            constexpr unsigned int Re = 75;

            /**
             * \brief Specifies \e Osmium.
             */
            constexpr unsigned int Os = 76;

            /**
             * \brief Specifies \e Iridium.
             */
            constexpr unsigned int Ir = 77;

            /**
             * \brief Specifies \e Platinum.
             */
            constexpr unsigned int Pt = 78;

            /**
             * \brief Specifies \e Gold.
             */
            constexpr unsigned int Au = 79;

            /**
             * \brief Specifies \e Mercury.
             */
            constexpr unsigned int Hg = 80;

            /**
             * \brief Specifies \e Thallium.
             */
            constexpr unsigned int Tl = 81;

            /**
             * \brief Specifies \e Lead.
             */
            constexpr unsigned int Pb = 82;

            /**
             * \brief Specifies \e Bismuth.
             */
            constexpr unsigned int Bi = 83;

            /**
             * \brief Specifies \e Polonium.
             */
            constexpr unsigned int Po = 84;

            /**
             * \brief Specifies \e Astatine.
             */
            constexpr unsigned int At = 85;

            /**
             * \brief Specifies \e Radon.
             */
            constexpr unsigned int Rn = 86;

            /**
             * \brief Specifies \e Francium.
             */
            constexpr unsigned int Fr = 87;

            /**
             * \brief Specifies \e Radium.
             */
            constexpr unsigned int Ra = 88;

            /**
             * \brief Specifies \e Actinium.
             */
            constexpr unsigned int Ac = 89;

            /**
             * \brief Specifies \e Thorium.
             */
            constexpr unsigned int Th = 90;

            /**
             * \brief Specifies \e Protactinium.
             */
            constexpr unsigned int Pa = 91;

            /**
             * \brief Specifies \e Uranium.
             */
            constexpr unsigned int U = 92;

            /**
             * \brief Specifies \e Neptunium.
             */
            constexpr unsigned int Np = 93;

            /**
             * \brief Specifies \e Plutonium.
             */
            constexpr unsigned int Pu = 94;

            /**
             * \brief Specifies \e Americium.
             */
            constexpr unsigned int Am = 95;

            /**
             * \brief Specifies \e Curium.
             */
            constexpr unsigned int Cm = 96;

            /**
             * \brief Specifies \e Berkelium.
             */
            constexpr unsigned int Bk = 97;

            /**
             * \brief Specifies \e Californium.
             */
            constexpr unsigned int Cf = 98;

            /**
             * \brief Specifies \e Einsteinium.
             */
            constexpr unsigned int Es = 99;

            /**
             * \brief Specifies \e Fermium.
             */
            constexpr unsigned int Fm = 100;

            /**
             * \brief Specifies \e Mendelevium.
             */
            constexpr unsigned int Md = 101;

            /**
             * \brief Specifies \e Nobelium.
             */
            constexpr unsigned int No = 102;

            /**
             * \brief Specifies \e Lawrencium.
             */
            constexpr unsigned int Lr = 103;

            /**
             * \brief Specifies \e Rutherfordium.
             */
            constexpr unsigned int Rf = 104;

            /**
             * \brief Specifies \e Dubnium.
             */
            constexpr unsigned int Db = 105;

            /**
             * \brief Specifies \e Seaborgium.
             */
            constexpr unsigned int Sg = 106;

            /**
             * \brief Specifies \e Bohrium.
             */
            constexpr unsigned int Bh = 107;

            /**
             * \brief Specifies \e Hassium.
             */
            constexpr unsigned int Hs = 108;

            /**
             * \brief Specifies \e Meitnerium.
             */
            constexpr unsigned int Mt = 109;

            /**
             * \brief Specifies \e Darmstadtium.
             */
            constexpr unsigned int Ds = 110;

            /**
             * \brief Specifies \e Roentgenium.
             */
            constexpr unsigned int Rg = 111;

            /**
             * \brief Specifies \e Copernicium.
             */
            constexpr unsigned int Cn = 112;

            /**
             * \brief Specifies \e Nihonium.
             */
            constexpr unsigned int Nh = 112;

            /**
             * \brief Marks the end of the supported chemical elements.
             */
            constexpr unsigned int MAX_ATOMIC_NO = Nh;

            /**
             * \brief A generic type that covers any element except hydrogen.
             */
            constexpr unsigned int A = MAX_ATOMIC_NO + 1;

            /**
             * \brief A generic type that covers any element.
             */
            constexpr unsigned int AH = MAX_ATOMIC_NO + 2;

            /**
             * \brief A generic type that covers any element except hydrogen and carbon.
             */
            constexpr unsigned int Q = MAX_ATOMIC_NO + 3;

            /**
             * \brief A generic type that covers any element except carbon.
             */
            constexpr unsigned int QH = MAX_ATOMIC_NO + 4;

            /**
             * \brief A generic type that covers any element that is a metal.
             */
            constexpr unsigned int M = MAX_ATOMIC_NO + 5;

            /**
             * \brief A generic type that covers hydrogen and any element that is a metal.
             */
            constexpr unsigned int MH = MAX_ATOMIC_NO + 6;

            /**
             * \brief A generic type that covers any element that is a halogen.
             */
            constexpr unsigned int X = MAX_ATOMIC_NO + 7;

            /**
             * \brief A generic type that covers hydrogen and any element that is a halogen.
             */
            constexpr unsigned int XH = MAX_ATOMIC_NO + 8;

            /**
             * \brief A generic type that covers any element (equivalent to AtomType::AH).
             */
            constexpr unsigned int ANY = MAX_ATOMIC_NO + 9;

            /**
             * \brief A generic type for heteroatoms (N, O, S or P).
             */
            constexpr unsigned int HET = MAX_ATOMIC_NO + 10;

            /**
             * \brief Marks the end of all supported atom types.
             */
            constexpr unsigned int MAX_TYPE = HET;
        } // namespace AtomType
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ATOMTYPE_HPP
