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
# \brief A reader for molecule data in the <em>IUPAC International Chemical Identifier (InChI)</em> [\ref INCHI] format.
# 
# <tt>INCHIMoleculeReader</tt> implements the conversion of <em>InChI</em> strings (or strings with auxiliary <em>InChI</em> information) to corresponding Chem.Molecule objects. The input data are read by means of a <tt>std::istream</tt> object that was provided to the <tt>INCHIMoleculeReader</tt> constructor.
# 
# For the actual decoding of the <em>InChI</em> input, <tt>INCHIMoleculeReader</tt> uses an appropriate function (<tt>GetStructFromINCHI()</tt> for <em>InChI</em> strings and <tt>Get_inchi_Input_FromAuxInfo()</tt> for auxiliary <em>InChI</em> information) of the <em>InChI C-API</em>. The return value of the called function provides information about the status of the performed operation (see Chem.INCHIReturnCode) and can be accessed by the method getReturnCode(). Produced error and log messages are accessible via the methods getMessage() and getLogOutput(), respectively.
# 
# Atom and bond attributes of a read input molecule are stored as properties of allocated Chem.Atom and Chem.Bond objects. The affected properties are summarized in the tables below:
# 
# <table>
#  <tr><th>Chem.Atom Property</th><th>Description</th><th>Notes</th></tr>
#  <tr><td>Chem.AtomProperty.COORDINATES_2D</td><td>Specifies the 2D position of the atom</td><td>Only set if auxiliary information with 2D-coordinates is available</td></tr>
#  <tr><td>Chem.AtomProperty.COORDINATES_3D</td><td>Specifies the 3D-coordinates of the atom</td><td>Only set if auxiliary information with 3D-coordinates is available</td></tr>
#  <tr><td>Chem.AtomProperty.SYMBOL</td><td>Specifies the symbol of the atom's element</td><td>-</td></tr>
#  <tr><td>Chem.AtomProperty.ISOTOPE</td><td>Specifies the isotopic mass of the atom</td><td>-</td></tr>
#  <tr><td>Chem.AtomProperty.FORMAL_CHARGE</td><td>Specifies the formal charge of the atom</td><td>Only set if the charge is different from zero</td></tr>
#  <tr><td>Chem.AtomProperty.RADICAL_TYPE</td><td>Specifies the radical type (see Chem.RadicalType)</td><td>Only set if the atom is a radical</td></tr>
#  <tr><td>Chem.AtomProperty.STEREO_DESCRIPTOR</td><td>Specifies the atom stereo descriptor (see Chem.AtomConfiguration, Chem.StereoDescriptor)</td><td>Only set if 0D stereo information is available and the atom is a tetrahedral stereogenic center</td></tr>
# </table>
# 
# <table>
#  <tr><th>Chem.Bond Property</th><th>Description</th><th>Notes</th></tr>
#  <tr><td>Chem.BondProperty.ORDER</td><td>Specifies the order of the bond</td><td>-</td></tr>
#  <tr><td>Chem.BondProperty.STEREO_2D_FLAG</td><td>Specifies the 2D stereo bond type (see Chem.BondStereoFlag)</td><td>Only set if auxiliary information with 2D stereo information is available</td></tr>
#  <tr><td>Chem.BondProperty.STEREO_DESCRIPTOR</td><td>Specifies the bond stereo descriptor (see Chem.BondConfiguration, Chem.StereoDescriptor)</td><td>Only set if 0D stereo information is available and the bond is stereogenic center</td></tr>
# </table>
# 
# <tt>INCHIMoleculeReader</tt> can be configured with the following control-parameters:
# 
# <table>
#  <tr><th>Control-Parameter</th><th>Default Value (see Chem.ControlParameterDefault)</th><th>Description</th></tr>
#  <tr><td>Chem.ControlParameter.STRICT_ERROR_CHECKING</td><td><tt>False</tt></td><td>Specifies whether non-fatal recoverable errors should be ignored or cause a read operation to fail</td></tr>
#  <tr><td>Chem.ControlParameter.INCHI_INPUT_OPTIONS</td><td><tt>""</tt></td><td>Specifies options for <em>InChI</em> input</td></tr>
# </table>
# 
class INCHIMoleculeReader(MoleculeReaderBase):

    ##
    # \brief Constructs a <tt>INCHIMoleculeReader</tt> instance that will read the molecule data from the input stream <em>is</em>.
    # 
    # \param is The input stream to read from.
    # 
    def __init__(is: CDPL.Base.IStream) -> None: pass

    ##
    # \brief Returns the error code of the last read operation.
    # 
    # Possible return values are defined in namespace Chem.INCHIReturnCode.
    # 
    # \return The error code of the last read operation.
    # 
    def getReturnCode() -> int: pass

    ##
    # \brief Returns the error message associated with the last read operation.
    # 
    # \return The error message associated with the last read operation.
    # 
    def getMessage() -> str: pass

    ##
    # \brief Returns the log output that was generated for the last read operation.
    # 
    # \return The log output that was generated for the last read operation.
    # 
    def getLogOutput() -> str: pass

    returnCode = property(getReturnCode)

    message = property(getMessage)

    logOutput = property(getLogOutput)
