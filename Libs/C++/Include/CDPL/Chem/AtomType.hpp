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
            const unsigned int UNKNOWN = 0;

            /**
             * \brief Specifies \e Hydrogen.
             */
            const unsigned int H = 1;

            /**
             * \brief Specifies <em>Hydrogen (Deuterium)</em>.
             */
            const unsigned int D = 1;

            /**
             * \brief Specifies <em>Hydrogen (Tritium)</em>.
             */
            const unsigned int T = 1;

            /**
             * \brief Specifies \e Helium.
             */
            const unsigned int He = 2;

            /**
             * \brief Specifies \e Lithium.
             */
            const unsigned int Li = 3;

            /**
             * \brief Specifies \e Beryllium.
             */
            const unsigned int Be = 4;

            /**
             * \brief Specifies \e Boron.
             */
            const unsigned int B = 5;

            /**
             * \brief Specifies \e Carbon.
             */
            const unsigned int C = 6;

            /**
             * \brief Specifies \e Nitrogen.
             */
            const unsigned int N = 7;

            /**
             * \brief Specifies \e Oxygen.
             */
            const unsigned int O = 8;

            /**
             * \brief Specifies \e Fluorine.
             */
            const unsigned int F = 9;

            /**
             * \brief Specifies \e Neon.
             */
            const unsigned int Ne = 10;

            /**
             * \brief Specifies \e Sodium.
             */
            const unsigned int Na = 11;

            /**
             * \brief Specifies \e Magnesium.
             */
            const unsigned int Mg = 12;

            /**
             * \brief Specifies \e Aluminium.
             */
            const unsigned int Al = 13;

            /**
             * \brief Specifies \e Silicon.
             */
            const unsigned int Si = 14;

            /**
             * \brief Specifies \e Phosphorus.
             */
            const unsigned int P = 15;

            /**
             * \brief Specifies \e Sulfur.
             */
            const unsigned int S = 16;

            /**
             * \brief Specifies \e Chlorine.
             */
            const unsigned int Cl = 17;

            /**
             * \brief Specifies \e Argon.
             */
            const unsigned int Ar = 18;

            /**
             * \brief Specifies \e Potassium.
             */
            const unsigned int K = 19;

            /**
             * \brief Specifies \e Calcium.
             */
            const unsigned int Ca = 20;

            /**
             * \brief Specifies \e Scandium.
             */
            const unsigned int Sc = 21;

            /**
             * \brief Specifies \e Titanium.
             */
            const unsigned int Ti = 22;

            /**
             * \brief Specifies \e Vanadium.
             */
            const unsigned int V = 23;

            /**
             * \brief Specifies \e Chromium.
             */
            const unsigned int Cr = 24;

            /**
             * \brief Specifies \e Manganese.
             */
            const unsigned int Mn = 25;

            /**
             * \brief Specifies \e Iron.
             */
            const unsigned int Fe = 26;

            /**
             * \brief Specifies \e Cobalt.
             */
            const unsigned int Co = 27;

            /**
             * \brief Specifies \e Nickel.
             */
            const unsigned int Ni = 28;

            /**
             * \brief Specifies \e Copper.
             */
            const unsigned int Cu = 29;

            /**
             * \brief Specifies \e Zinc.
             */
            const unsigned int Zn = 30;

            /**
             * \brief Specifies \e Gallium.
             */
            const unsigned int Ga = 31;

            /**
             * \brief Specifies \e Germanium.
             */
            const unsigned int Ge = 32;

            /**
             * \brief Specifies \e Arsenic.
             */
            const unsigned int As = 33;

            /**
             * \brief Specifies \e Selenium.
             */
            const unsigned int Se = 34;

            /**
             * \brief Specifies \e Bromine.
             */
            const unsigned int Br = 35;

            /**
             * \brief Specifies \e Krypton.
             */
            const unsigned int Kr = 36;

            /**
             * \brief Specifies \e Rubidium.
             */
            const unsigned int Rb = 37;

            /**
             * \brief Specifies \e Strontium.
             */
            const unsigned int Sr = 38;

            /**
             * \brief Specifies \e Yttrium.
             */
            const unsigned int Y = 39;

            /**
             * \brief Specifies \e Zirconium.
             */
            const unsigned int Zr = 40;

            /**
             * \brief Specifies \e Niobium.
             */
            const unsigned int Nb = 41;

            /**
             * \brief Specifies \e Molybdenum.
             */
            const unsigned int Mo = 42;

            /**
             * \brief Specifies \e Technetium.
             */
            const unsigned int Tc = 43;

            /**
             * \brief Specifies \e Ruthenium.
             */
            const unsigned int Ru = 44;

            /**
             * \brief Specifies \e Rhodium.
             */
            const unsigned int Rh = 45;

            /**
             * \brief Specifies \e Palladium.
             */
            const unsigned int Pd = 46;

            /**
             * \brief Specifies \e Silver.
             */
            const unsigned int Ag = 47;

            /**
             * \brief Specifies \e Cadmium.
             */
            const unsigned int Cd = 48;

            /**
             * \brief Specifies \e Indium.
             */
            const unsigned int In = 49;

            /**
             * \brief Specifies \e Tin.
             */
            const unsigned int Sn = 50;

            /**
             * \brief Specifies \e Antimony.
             */
            const unsigned int Sb = 51;

            /**
             * \brief Specifies \e Tellurium.
             */
            const unsigned int Te = 52;

            /**
             * \brief Specifies \e Iodine.
             */
            const unsigned int I = 53;

            /**
             * \brief Specifies \e Xenon.
             */
            const unsigned int Xe = 54;

            /**
             * \brief Specifies \e Caesium.
             */
            const unsigned int Cs = 55;

            /**
             * \brief Specifies \e Barium.
             */
            const unsigned int Ba = 56;

            /**
             * \brief Specifies \e Lanthanum.
             */
            const unsigned int La = 57;

            /**
             * \brief Specifies \e Cerium.
             */
            const unsigned int Ce = 58;

            /**
             * \brief Specifies \e Praseodymium.
             */
            const unsigned int Pr = 59;

            /**
             * \brief Specifies \e Neodymium.
             */
            const unsigned int Nd = 60;

            /**
             * \brief Specifies \e Promethium.
             */
            const unsigned int Pm = 61;

            /**
             * \brief Specifies \e Samarium.
             */
            const unsigned int Sm = 62;

            /**
             * \brief Specifies \e Europium.
             */
            const unsigned int Eu = 63;

            /**
             * \brief Specifies \e Gadolinium.
             */
            const unsigned int Gd = 64;

            /**
             * \brief Specifies \e Terbium.
             */
            const unsigned int Tb = 65;

            /**
             * \brief Specifies \e Dysprosium.
             */
            const unsigned int Dy = 66;

            /**
             * \brief Specifies \e Holmium.
             */
            const unsigned int Ho = 67;

            /**
             * \brief Specifies \e Erbium.
             */
            const unsigned int Er = 68;

            /**
             * \brief Specifies \e Thulium.
             */
            const unsigned int Tm = 69;

            /**
             * \brief Specifies \e Ytterbium.
             */
            const unsigned int Yb = 70;

            /**
             * \brief Specifies \e Lutetium.
             */
            const unsigned int Lu = 71;

            /**
             * \brief Specifies \e Hafnium.
             */
            const unsigned int Hf = 72;

            /**
             * \brief Specifies \e Tantalum.
             */
            const unsigned int Ta = 73;

            /**
             * \brief Specifies \e Tungsten.
             */
            const unsigned int W = 74;

            /**
             * \brief Specifies \e Rhenium.
             */
            const unsigned int Re = 75;

            /**
             * \brief Specifies \e Osmium.
             */
            const unsigned int Os = 76;

            /**
             * \brief Specifies \e Iridium.
             */
            const unsigned int Ir = 77;

            /**
             * \brief Specifies \e Platinum.
             */
            const unsigned int Pt = 78;

            /**
             * \brief Specifies \e Gold.
             */
            const unsigned int Au = 79;

            /**
             * \brief Specifies \e Mercury.
             */
            const unsigned int Hg = 80;

            /**
             * \brief Specifies \e Thallium.
             */
            const unsigned int Tl = 81;

            /**
             * \brief Specifies \e Lead.
             */
            const unsigned int Pb = 82;

            /**
             * \brief Specifies \e Bismuth.
             */
            const unsigned int Bi = 83;

            /**
             * \brief Specifies \e Polonium.
             */
            const unsigned int Po = 84;

            /**
             * \brief Specifies \e Astatine.
             */
            const unsigned int At = 85;

            /**
             * \brief Specifies \e Radon.
             */
            const unsigned int Rn = 86;

            /**
             * \brief Specifies \e Francium.
             */
            const unsigned int Fr = 87;

            /**
             * \brief Specifies \e Radium.
             */
            const unsigned int Ra = 88;

            /**
             * \brief Specifies \e Actinium.
             */
            const unsigned int Ac = 89;

            /**
             * \brief Specifies \e Thorium.
             */
            const unsigned int Th = 90;

            /**
             * \brief Specifies \e Protactinium.
             */
            const unsigned int Pa = 91;

            /**
             * \brief Specifies \e Uranium.
             */
            const unsigned int U = 92;

            /**
             * \brief Specifies \e Neptunium.
             */
            const unsigned int Np = 93;

            /**
             * \brief Specifies \e Plutonium.
             */
            const unsigned int Pu = 94;

            /**
             * \brief Specifies \e Americium.
             */
            const unsigned int Am = 95;

            /**
             * \brief Specifies \e Curium.
             */
            const unsigned int Cm = 96;

            /**
             * \brief Specifies \e Berkelium.
             */
            const unsigned int Bk = 97;

            /**
             * \brief Specifies \e Californium.
             */
            const unsigned int Cf = 98;

            /**
             * \brief Specifies \e Einsteinium.
             */
            const unsigned int Es = 99;

            /**
             * \brief Specifies \e Fermium.
             */
            const unsigned int Fm = 100;

            /**
             * \brief Specifies \e Mendelevium.
             */
            const unsigned int Md = 101;

            /**
             * \brief Specifies \e Nobelium.
             */
            const unsigned int No = 102;

            /**
             * \brief Specifies \e Lawrencium.
             */
            const unsigned int Lr = 103;

            /**
             * \brief Specifies \e Rutherfordium.
             */
            const unsigned int Rf = 104;

            /**
             * \brief Specifies \e Dubnium.
             */
            const unsigned int Db = 105;

            /**
             * \brief Specifies \e Seaborgium.
             */
            const unsigned int Sg = 106;

            /**
             * \brief Specifies \e Bohrium.
             */
            const unsigned int Bh = 107;

            /**
             * \brief Specifies \e Hassium.
             */
            const unsigned int Hs = 108;

            /**
             * \brief Specifies \e Meitnerium.
             */
            const unsigned int Mt = 109;

            /**
             * \brief Marks the end of the supported chemical elements.
             */
            const unsigned int MAX_ATOMIC_NO = Mt;

            /**
             * \brief A generic type that covers any element except hydrogen.
             */
            const unsigned int A = MAX_ATOMIC_NO + 1;

            /**
             * \brief A generic type that covers any element.
             */
            const unsigned int AH = MAX_ATOMIC_NO + 2;

            /**
             * \brief A generic type that covers any element except hydrogen and carbon.
             */
            const unsigned int Q = MAX_ATOMIC_NO + 3;

            /**
             * \brief A generic type that covers any element except carbon.
             */
            const unsigned int QH = MAX_ATOMIC_NO + 4;

            /**
             * \brief A generic type that covers any element that is a metal.
             */
            const unsigned int M = MAX_ATOMIC_NO + 5;

            /**
             * \brief A generic type that covers hydrogen and any element that is a metal.
             */
            const unsigned int MH = MAX_ATOMIC_NO + 6;

            /**
             * \brief A generic type that covers any element that is a halogen.
             */
            const unsigned int X = MAX_ATOMIC_NO + 7;

            /**
             * \brief A generic type that covers hydrogen and any element that is a halogen.
             */
            const unsigned int XH = MAX_ATOMIC_NO + 8;

            /**
             * \brief A generic type that covers any element (equivalent to AtomType::AH).
             */
            const unsigned int ANY = MAX_ATOMIC_NO + 9;

            /**
             * \brief A generic type for heteroatoms (N, O, S or P).
             */
            const unsigned int HET = MAX_ATOMIC_NO + 10;

            /**
             * \brief Marks the end of all supported atom types.
             */
            const unsigned int MAX_TYPE = HET;
        } // namespace AtomType
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ATOMTYPE_HPP
