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
# \brief A writer for molecular graph data in the <em>IUPAC International Chemical Identifier (InChI)</em> [\ref INCHI] format.
# 
# <tt>INCHIMolecularGraphWriter</tt> implements the generation of <em>InChI</em> strings from Chem.MolecularGraph objects. The output data are written by means of a <tt>std::ostream</tt> object that was provided to the <tt>INCHIMolecularGraphWriter</tt> constructor.
# 
# For the generation of the <em>InChI</em> output, <tt>INCHIMolecularGraphWriter</tt> uses the function <tt>GetINCHI()</tt> of the <em>InChI C-API</em>. The return value of the function provides information about the status of the performed operation (see Chem.INCHIReturnCode) and can be accessed by the method getReturnCode(). Produced error and log messages are accessible via the methods getMessage() and getLogOutput(), respectively.
# 
# The generation of <em>InChI</em> strings requires values of the following Chem.Atom and Chem.Bond properties:
# 
# <table>
#  <tr><th>Chem.Atom Property</th><th>Description</th><th>Notes</th></tr>
#  <tr><td>Chem.AtomProperty.COORDINATES_2D</td><td>Specifies the 2D position of the atom</td><td>Only required if 2D atom coordinates are written</td></tr>
#  <tr><td>Chem.AtomProperty.COORDINATES_3D</td><td>Specifies the 3D-coordinates of the atom</td><td>Only required if 3D atom coordinates are written</td></tr>
#  <tr><td>Chem.AtomProperty.SYMBOL</td><td>Specifies the symbol of the atom's element</td><td>-</td></tr>
#  <tr><td>Chem.AtomProperty.ISOTOPE</td><td>Specifies the isotopic mass of the atom</td><td>-</td></tr>
#  <tr><td>Chem.AtomProperty.FORMAL_CHARGE</td><td>Specifies the formal charge of the atom</td><td>-</td></tr>
#  <tr><td>Chem.AtomProperty.RADICAL_TYPE</td><td>Specifies the radical type (see Chem.RadicalType)</td><td>-</td></tr>
#  <tr><td>Chem.AtomProperty.STEREO_DESCRIPTOR</td><td>Specifies the atom stereo descriptor (see Chem.AtomConfiguration, Chem.StereoDescriptor)</td><td>Only required if no atom coordinates are written</td></tr>
# </table>
# 
# <table>
#  <tr><th>Chem.Bond Property</th><th>Description</th><th>Notes</th></tr>
#  <tr><td>Chem.BondProperty.ORDER</td><td>Specifies the order of the bond</td><td>-</td></tr>
#  <tr><td>Chem.BondProperty.STEREO_2D_FLAG</td><td>Specifies the 2D stereo bond type (see Chem.BondStereoFlag)</td><td>Only required if 2D or 3D atom coordinates are written</td></tr>
#  <tr><td>Chem.BondProperty.STEREO_DESCRIPTOR</td><td>Specifies the stereo descriptor of the bond (see Chem.BondConfiguration, Chem.StereoDescriptor)</td><td>Only required if no atom coordinates are written</td></tr>
# </table>
# 
# <tt>INCHIMolecularGraphWriter</tt> can be configured with the following control-parameters:
# 
# <table>
#  <tr><th>Control-Parameter</th><th>Default Value (see Chem.ControlParameterDefault)</th><th>Description</th></tr>
#  <tr><td>Chem.ControlParameter.COORDINATES_DIMENSION</td><td><tt>1</tt></td><td>Specifies the dimension of the atom coordinates (a value of <em>2</em> specifies 2D, a value of <em>3</em> specifies 3D, a value of zero specifies that no atom coordinates shall be written; any other value specifies that 3D-coordinates shall be written if they are available, and no coordinates otherwise)</td></tr>
#  <tr><td>Chem.ControlParameter.STRICT_ERROR_CHECKING</td><td><tt>False</tt></td><td>Specifies whether non-fatal recoverable errors should be ignored or cause a write operation to fail</td></tr>
#  <tr><td>Chem.ControlParameter.RECORD_SEPARATOR</td><td><tt>"\n"</tt></td><td>Specifies the data record separator</td></tr>
#  <tr><td>Chem.ControlParameter.INCHI_OUTPUT_OPTIONS</td><td><tt>"/WarnOnEmptyStructure /AuxNone /NEWPSOFF"</tt></td><td>Specifies options for <em>InChI</em> generation</td></tr>
# </table>
# 
class INCHIMolecularGraphWriter(MolecularGraphWriterBase):

    ##
    # \brief Constructs a <tt>INCHIMolecularGraphWriter</tt> instance that will write data of molecular graphs to the output stream <em>os</em>.
    # 
    # \param os The output stream to write to.
    # 
    def __init__(os: Base.OStream) -> None: pass

    ##
    # \brief Returns the error code of the last write operation.
    # 
    # Possible return values are defined in namespace Chem.INCHIReturnCode.
    # 
    # \return The error code of the last write operation.
    # 
    def getReturnCode() -> int: pass

    ##
    # \brief Returns the error message associated with the last write operation.
    # 
    # \return The error message associated with the last write operation.
    # 
    def getMessage() -> str: pass

    ##
    # \brief Returns the log output that was generated for the last write operation.
    # 
    # \return The log output that was generated for the last write operation.
    # 
    def getLogOutput() -> str: pass

    returnCode = property(getReturnCode)

    message = property(getMessage)

    logOutput = property(getLogOutput)
