#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

##
# \brief A data structure for the storage and retrieval of stereochemical information about atoms and bonds.
# 
# The stereochemistry of atoms and bonds is definded by an ordered list of reference atoms and an integer constant that describes the spatial configuration of the reference atoms. Requirements on the specification of the reference atom list and the way the associated steric configuration has to be interpreted both depend on the primary type of the stereocenter (if atom or bond) and, for atom centers, also on the number and geometric arrangement of the reference atoms. The following basic types of atom and bond stereocenters are currently supported:
# 
# - <em>Atoms with four neighbors in tetrahedral arrangement:</em><br>
# <br>
#  The four neighbor atoms serve as reference atoms. Their steric configuration is determined by looking along the bond from the center atom (stereocenter) to the <em>4</em>th reference atom. If the direction of travel from reference atom <em>1</em> over atom <em>2</em> to atom <em>3</em> is <em>clockwise</em> (see <em>Fig. 1a</em>), the configuration flag is assigned the value AtomConfiguration.R, and AtomConfiguration.S, if the reference atoms <em>1</em>, <em>2</em> and <em>3</em> are arranged in <em>counterclockwise</em> direction (<em>Fig. 1b</em>).
# 
# <table>
#  <tr><td>\image html tetrahedral_stereo_r.png "Fig. 1a: R-Configuration"</td><td>\image html tetrahedral_stereo_s.png "Fig. 1b: S-Configuration"</td></tr>
# </table>
# 
# - <em>Atoms with three neighbors in pyramidal arrangement:</em><br>
# <br>
#  The neighbor atoms correspond to the first three atoms in the reference atom list. The <em>4</em>th reference atom denotes the central atom. The configuration is determined by looking along the line from the center atom to a projected point (represented by a blue sphere in figure <em>2a</em> and <em>2b</em>) which is obtained by adding the bond vectors from each neighbor atom to the central atom. Like before, if the direction of travel from reference atom <em>1</em> over atom <em>2</em> to atom <em>3</em> is <em>clockwise</em> (see <em>Fig. 2a</em>), the configuration flag is assigned the value AtomConfiguration.R, and AtomConfiguration.S, if the reference atoms <em>1</em>, <em>2</em> and <em>3</em> are arranged in a <em>counterclockwise</em> fashion (<em>Fig. 2b</em>).
# 
# <table>
#  <tr><td>\image html pyramidal_stereo_r.png "Fig. 2a: R-Configuration"</td><td>\image html pyramidal_stereo_s.png "Fig. 2b: S-Configuration"</td></tr>
# </table>
# 
# - <em>Non-terminal double bonds:</em><br>
#  As shown in figure <em>3a</em> and <em>3b</em>, the four reference atoms form a path with three consecutive bonds where atoms <em>2</em> and <em>3</em> are part of the central double bond. Atom <em>1</em> is the connected atom of the first double bond ligand, and atom <em>4</em> the connected atom of the second ligand. If reference atoms <em>1</em> and <em>4</em> lie on the same side of the double bond (see <em>Fig. 3a</em>), the configuration flag is assigned the value BondConfiguration.CIS, and BondConfiguration.TRANS, if they are on opposite sides f the bond (<em>Fig. 3b</em>).
# 
# <table>
#  <tr><td>\image html bond_stereo_cis.png "Fig. 3a: Cis-Configuration"</td><td>\image html bond_stereo_trans.png "Fig. 3b: Trans-Configuration"</td></tr>
# </table>
# 
class StereoDescriptor(Boost.Python.instance):

    ##
    # \brief 
    #
    class ReferenceAtomArray(Boost.Python.instance):

        ##
        # \brief 
        # \return 
        #
        def __len__() -> int: pass

        ##
        # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
        # \param atom The value to test for membership.
        # \return The result of the membership test operation.
        # 
        def __contains__(atom: Atom) -> bool: pass

        ##
        # \brief 
        # \param idx 
        # \return 
        #
        def __getitem__(idx: int) -> Atom: pass

    ##
    # \brief Constructs a <tt>StereoDescriptor</tt> instance that specifies the configuration <em>config</em> but stores no reference atoms.
    # 
    # \param config A constant specifying the configuration of the central atoms.
    # 
    def __init__(config: int) -> None: pass

    ##
    # \brief Constructs a copy of the <tt>StereoDescriptor</tt> instance <em>descr</em>.
    # 
    # \param descr The <tt>StereoDescriptor</tt> instance to copy.
    # 
    def __init__(descr: StereoDescriptor) -> None: pass

    ##
    # \brief Constructs a <tt>StereoDescriptor</tt> instance that specifies a configuration of <em>config</em> for three reference atoms.
    # 
    # \param config A constant specifying the configuration of the reference atoms.
    # \param atom1 The first reference atom.
    # \param atom2 The second reference atom.
    # \param atom3 The third reference atom.
    # 
    def __init__(config: int, atom1: Atom, atom2: Atom, atom3: Atom) -> None: pass

    ##
    # \brief Constructs a <tt>StereoDescriptor</tt> instance that specifies a configuration of <em>config</em> for four reference atoms.
    # 
    # \param config A flag specifying the configuration of the reference atoms.
    # \param atom1 The first reference atom.
    # \param atom2 The second reference atom.
    # \param atom3 The third reference atom.
    # \param atom4 The fourth reference atom.
    # 
    def __init__(config: int, atom1: Atom, atom2: Atom, atom3: Atom, atom4: Atom) -> None: pass

    ##
    # \brief Returns the configuration of the reference atoms.
    # 
    # \return A constant specifying the configuration of the reference atoms.
    # 
    def getConfiguration() -> int: pass

    ##
    # \brief Sets the configuration of the reference atoms to <em>config</em>.
    # 
    # \param config A constant specifying the configuration of the reference atoms.
    # 
    def setConfiguration(config: int) -> None: pass

    ##
    # \brief Returns the number of specified reference atoms.
    # 
    # \return The number of specified reference atoms.
    # 
    def getNumReferenceAtoms() -> int: pass

    ##
    # \brief Returns an array of references to the stored reference atoms.
    # 
    # \return An array of references to the stored reference atoms.
    # 
    def getReferenceAtoms() -> ReferenceAtomArray: pass

    ##
    # \brief Assignment operator.
    # 
    # \param descr The <tt>StereoDescriptor</tt> instance to copy.
    # 
    # \return \a self
    # 
    def assign(descr: StereoDescriptor) -> StereoDescriptor: pass

    ##
    # \brief Tells if an odd or even number of atom transpositions is required to achieve the same ordering of reference and argument atoms.
    # 
    # \param atom1 The first atom.
    # \param atom2 The second atom.
    # \param atom3 The third atom.
    # \param atom4 The fourth atom.
    # 
    # \return <tt>1</tt> if an <em>odd</em> number of transpositions is required, <tt>2</tt> if an <em>even</em> number of transpositions is required and <tt>0</tt> if the argument atoms do not match the stored reference atoms.
    # 
    def getPermutationParity(atom1: Atom, atom2: Atom, atom3: Atom, atom4: Atom) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %StereoDescriptor instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %StereoDescriptor instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Tells wheter this <tt>StereoDescriptor</tt> instance is valid for the specified center atom.
    # 
    # The method checks if the number of reference atoms is at least 3, the reference atoms are distinct and if every reference atom is connected to the argument atom.
    # 
    # \param atom The stereogenic center atom.
    # 
    # \return <tt>True</tt> if valid, <tt>False</tt> otherwise.
    # 
    def isValid(atom: Atom) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %StereoDescriptor instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    objectID = property(getObjectID)

    configuration = property(getConfiguration, setConfiguration)

    numReferenceAtoms = property(getNumReferenceAtoms)

    referenceAtoms = property(getReferenceAtoms)
