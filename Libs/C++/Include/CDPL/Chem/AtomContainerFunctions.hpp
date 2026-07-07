/* 
 * AtomContainerFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::AtomContainer instances.
 */

#ifndef CDPL_CHEM_ATOMCONTAINERFUNCTIONS_HPP
#define CDPL_CHEM_ATOMCONTAINERFUNCTIONS_HPP

#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomPredicate.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        class AtomContainer;
        class Fragment;
        class Molecule;


        /**
         * \brief Tells whether all atoms of \a cntnr carry coordinates of the given dimensionality.
         * \param cntnr The atom container.
         * \param dim The coordinate dimensionality (\e 2 or \e 3).
         * \return \c true if all atoms have the requested coordinates, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasCoordinates(const AtomContainer& cntnr, std::size_t dim);


        /**
         * \brief Extracts the 2D coordinates of all atoms in \a cntnr into \a coords.
         * \param cntnr The atom container.
         * \param coords The output 2D-coordinate array.
         * \param append If \c true, the coordinates are appended to \a coords. Otherwise, \a coords is cleared first.
         */
        CDPL_CHEM_API void get2DCoordinates(const AtomContainer& cntnr, Math::Vector2DArray& coords, bool append = false);

        /**
         * \brief Writes the 2D coordinates in \a coords back to the corresponding atoms of \a cntnr.
         * \param cntnr The atom container.
         * \param coords The 2D coordinates to assign (must contain at least one entry per atom).
         */
        CDPL_CHEM_API void set2DCoordinates(AtomContainer& cntnr, const Math::Vector2DArray& coords);

        /**
         * \brief Transforms the 2D coordinates of all atoms in \a cntnr by the affine <em>3&times;3</em> matrix \a mtx.
         * \param cntnr The atom container.
         * \param mtx The 2D affine transformation matrix.
         */
        CDPL_CHEM_API void transform2DCoordinates(AtomContainer& cntnr, const Math::Matrix3D& mtx);


        /**
         * \brief Extracts the 3D coordinates of all atoms in \a cntnr into \a coords using the per-atom coordinate lookup function \a coords_func.
         * \param cntnr The atom container.
         * \param coords The output 3D-coordinate array.
         * \param coords_func The function returning the 3D coordinates of an atom.
         * \param append If \c true, the coordinates are appended to \a coords. Otherwise, \a coords is cleared first.
         */
        CDPL_CHEM_API void get3DCoordinates(const AtomContainer& cntnr, Math::Vector3DArray& coords, const Atom3DCoordinatesFunction& coords_func, bool append = false);


        /**
         * \brief Removes all stored conformations from the atoms of \a cntnr.
         * \param cntnr The atom container.
         */
        CDPL_CHEM_API void clearConformations(AtomContainer& cntnr);

        /**
         * \brief Returns the number of conformations stored on the atoms of \a cntnr.
         * \param cntnr The atom container.
         * \return The conformation count.
         */
        CDPL_CHEM_API std::size_t getNumConformations(const AtomContainer& cntnr);

        /**
         * \brief Promotes the stored conformation at index \a conf_idx to the active per-atom 3D coordinates.
         * \param cntnr The atom container.
         * \param conf_idx The zero-based conformation index.
         */
        CDPL_CHEM_API void applyConformation(AtomContainer& cntnr, std::size_t conf_idx);

        /**
         * \brief Extracts the conformation at index \a conf_idx into \a coords.
         * \param cntnr The atom container.
         * \param conf_idx The zero-based conformation index.
         * \param coords The output 3D-coordinate array.
         * \param append If \c true, the coordinates are appended to \a coords. Otherwise, \a coords is cleared first.
         */
        CDPL_CHEM_API void getConformation(const AtomContainer& cntnr, std::size_t conf_idx, Math::Vector3DArray& coords, bool append = false);

        /**
         * \brief Overwrites the conformation at index \a conf_idx with the supplied 3D coordinates.
         * \param cntnr The atom container.
         * \param conf_idx The zero-based conformation index.
         * \param coords The 3D coordinates of the conformation.
         */
        CDPL_CHEM_API void setConformation(AtomContainer& cntnr, std::size_t conf_idx, const Math::Vector3DArray& coords);

        /**
         * \brief Appends a new conformation built from the supplied 3D coordinates to the atoms of \a cntnr.
         * \param cntnr The atom container.
         * \param coords The 3D coordinates of the new conformation.
         */
        CDPL_CHEM_API void addConformation(AtomContainer& cntnr, const Math::Vector3DArray& coords);

        /**
         * \brief Transforms the conformation at index \a conf_idx by the homogeneous <em>4&times;4</em> matrix \a mtx.
         * \param cntnr The atom container.
         * \param conf_idx The zero-based conformation index.
         * \param mtx The homogeneous <em>4&times;4</em> transformation matrix.
         */
        CDPL_CHEM_API void transformConformation(AtomContainer& cntnr, std::size_t conf_idx, const Math::Matrix4D& mtx);

        /**
         * \brief Transforms every stored conformation of the atoms in \a cntnr by the homogeneous <em>4&times;4</em> matrix \a mtx.
         * \param cntnr The atom container.
         * \param mtx The homogeneous <em>4&times;4</em> transformation matrix.
         */
        CDPL_CHEM_API void transformConformations(AtomContainer& cntnr, const Math::Matrix4D& mtx);

        /**
         * \brief Aligns each stored conformation of \a cntnr onto the supplied reference coordinates using
         *        the atoms flagged in \a ref_atoms as alignment anchors.
         * \param cntnr The atom container holding the conformations to be aligned.
         * \param ref_atoms Bit mask selecting the atoms of \a cntnr used as alignment anchors.
         * \param ref_coords Reference 3D coordinates of the alignment-anchor atoms.
         * \return \c true if the alignment succeeded for every conformation, and \c false otherwise.
         * \since 1.1
         */
        CDPL_CHEM_API bool alignConformations(AtomContainer& cntnr, const Util::BitSet& ref_atoms, const Math::Vector3DArray& ref_coords);

        /**
         * \brief Aligns each stored conformation of \a cntnr onto the supplied reference coordinates using
         *        the atoms of \a ref_atoms as alignment anchors.
         * \param cntnr The atom container holding the conformations to be aligned.
         * \param ref_atoms The atoms used as alignment anchors (must all be members of \a cntnr).
         * \param ref_coords Reference 3D coordinates of the alignment-anchor atoms.
         * \return \c true if the alignment succeeded for every conformation, and \c false otherwise.
         * \since 1.1
         */
        CDPL_CHEM_API bool alignConformations(AtomContainer& cntnr, const AtomContainer& ref_atoms, const Math::Vector3DArray& ref_coords);

        /**
         * \brief Aligns each stored conformation of \a cntnr to the first conformation using the atoms flagged
         *        in \a ref_atoms as alignment anchors.
         * \param cntnr The atom container holding the conformations to be aligned.
         * \param ref_atoms Bit mask selecting the atoms of \a cntnr used as alignment anchors.
         * \return \c true if the alignment succeeded for every conformation, and \c false otherwise.
         * \since 1.1
         */
        CDPL_CHEM_API bool alignConformations(AtomContainer& cntnr, const Util::BitSet& ref_atoms);

        /**
         * \brief Aligns each stored conformation of \a cntnr to the first conformation using the atoms of
         *        \a ref_atoms as alignment anchors.
         * \param cntnr The atom container holding the conformations to be aligned.
         * \param ref_atoms The atoms used as alignment anchors (must all be members of \a cntnr).
         * \return \c true if the alignment succeeded for every conformation, and \c false otherwise.
         * \since 1.1
         */
        CDPL_CHEM_API bool alignConformations(AtomContainer& cntnr, const AtomContainer& ref_atoms);


        /**
         * \brief Returns the largest component-group ID assigned to any atom of \a cntnr.
         * \param cntnr The atom container.
         * \return The largest component-group ID (zero if no atom carries a component-group ID).
         */
        CDPL_CHEM_API std::size_t getMaxComponentGroupID(const AtomContainer& cntnr);

        /**
         * \brief Returns the largest atom-mapping ID assigned to any atom of \a cntnr.
         * \param cntnr The atom container.
         * \return The largest atom-mapping ID (zero if no atom carries an atom-mapping ID).
         */
        CDPL_CHEM_API std::size_t getMaxAtomMappingID(const AtomContainer& cntnr);


        /**
         * \brief Sets bits in \a mask corresponding to atoms of \a cntnr whose atom type matches \a type.
         * \param cntnr The atom container.
         * \param mask The output bit mask (bit \e i is set if atom \e i of \a cntnr has the requested type).
         * \param type The query atom type (Chem::AtomType value, possibly a generic class such as Chem::AtomType::HET).
         * \param reset If \c true, \a mask is reset before processing. Otherwise, existing bits are preserved.
         * \param strict If \c true, only exact type matches are accepted. If \c false, generic-class matches also set the bit.
         * \return The number of atoms whose bit was set.
         */
        CDPL_CHEM_API std::size_t createAtomTypeMask(const AtomContainer& cntnr, Util::BitSet& mask, unsigned int type, bool reset = true, bool strict = true);


        /**
         * \brief Copies every atom of \a cntnr that satisfies \a pred into the molecule \a mol.
         * \param cntnr The source atom container.
         * \param mol The target molecule.
         * \param pred The predicate evaluated for each atom. Only atoms for which it returns \c true are copied.
         * \param append If \c true, atoms are appended to \a mol. Otherwise, \a mol is cleared first.
         */
        CDPL_CHEM_API void copyAtomsIf(const AtomContainer& cntnr, Molecule& mol, const AtomPredicate& pred, bool append = false);

        /**
         * \brief Copies every atom of \a cntnr that satisfies \a pred into the fragment \a frag.
         * \param cntnr The source atom container.
         * \param frag The target fragment.
         * \param pred The predicate evaluated for each atom. Only atoms for which it returns \c true are copied.
         * \param append If \c true, atoms are appended to \a frag. Otherwise, \a frag is cleared first.
         */
        CDPL_CHEM_API void copyAtomsIf(const AtomContainer& cntnr, Fragment& frag, const AtomPredicate& pred, bool append = false);

        /**
         * \brief Copies every atom of \a cntnr that does \e not satisfy \a pred into the molecule \a mol.
         * \param cntnr The source atom container.
         * \param mol The target molecule.
         * \param pred The predicate evaluated for each atom. Only atoms for which it returns \c false are copied.
         * \param append If \c true, atoms are appended to \a mol. Otherwise, \a mol is cleared first.
         */
        CDPL_CHEM_API void copyAtomsIfNot(const AtomContainer& cntnr, Molecule& mol, const AtomPredicate& pred, bool append = false);

        /**
         * \brief Copies every atom of \a cntnr that does \e not satisfy \a pred into the fragment \a frag.
         * \param cntnr The source atom container.
         * \param frag The target fragment.
         * \param pred The predicate evaluated for each atom. Only atoms for which it returns \c false are copied.
         * \param append If \c true, atoms are appended to \a frag. Otherwise, \a frag is cleared first.
         */
        CDPL_CHEM_API void copyAtomsIfNot(const AtomContainer& cntnr, Fragment& frag, const AtomPredicate& pred, bool append = false);


        /**
         * \brief Computes the mass-weighted center of mass of the atoms in \a cntnr.
         * \param cntnr The atom container.
         * \param coords_func The function returning the 3D coordinates of an atom.
         * \param ctr The output center-of-mass coordinates.
         * \return \c true if the center of mass could be computed (at least one atom with non-zero mass), and \c false otherwise.
         */
        CDPL_CHEM_API bool calcCenterOfMass(const AtomContainer& cntnr, const Atom3DCoordinatesFunction& coords_func, Math::Vector3D& ctr);

        /**
         * \brief Computes the unweighted centroid (arithmetic mean of atom coordinates) of \a cntnr.
         * \param cntnr The atom container.
         * \param coords_func The function returning the 3D coordinates of an atom.
         * \param ctr The output centroid coordinates.
         * \return \c true if the centroid could be computed (\a cntnr is non-empty), and \c false otherwise.
         */
        CDPL_CHEM_API bool calcCentroid(const AtomContainer& cntnr, const Atom3DCoordinatesFunction& coords_func, Math::Vector3D& ctr);

        /**
         * \brief Computes the axis-aligned bounding box enclosing the atoms of \a cntnr.
         * \param cntnr The atom container.
         * \param min The output lower-left corner of the bounding box.
         * \param max The output upper-right corner of the bounding box.
         * \param coords_func The function returning the 3D coordinates of an atom.
         * \param reset If \c true, the bounding box is reset to the first atom. Otherwise, \a min and \a max are extended in place.
         */
        CDPL_CHEM_API void calcBoundingBox(const AtomContainer& cntnr, Math::Vector3D& min, Math::Vector3D& max, const Atom3DCoordinatesFunction& coords_func, bool reset = true);

        /**
         * \brief Tells whether every atom of \a cntnr lies inside the axis-aligned bounding box defined by \a min and \a max.
         * \param cntnr The atom container.
         * \param min The lower-left corner of the bounding box.
         * \param max The upper-right corner of the bounding box.
         * \param coords_func The function returning the 3D coordinates of an atom.
         * \return \c true if all atoms are inside the box, and \c false otherwise.
         */
        CDPL_CHEM_API bool insideBoundingBox(const AtomContainer& cntnr, const Math::Vector3D& min, const Math::Vector3D& max, const Atom3DCoordinatesFunction& coords_func);

        /**
         * \brief Tells whether at least one atom of \a cntnr lies inside the axis-aligned bounding box defined by \a min and \a max.
         * \param cntnr The atom container.
         * \param min The lower-left corner of the bounding box.
         * \param max The upper-right corner of the bounding box.
         * \param coords_func The function returning the 3D coordinates of an atom.
         * \return \c true if at least one atom is inside the box, and \c false otherwise.
         */
        CDPL_CHEM_API bool intersectsBoundingBox(const AtomContainer& cntnr, const Math::Vector3D& min, const Math::Vector3D& max, const Atom3DCoordinatesFunction& coords_func);
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ATOMCONTAINERFUNCTIONS_HPP
