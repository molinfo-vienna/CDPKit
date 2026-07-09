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
# \brief Writer for molecular graph data in the <em>IUPAC International Chemical Identifier (InChI)</em> [\ref INCHI] format.
# 
# <tt>INCHIMolecularGraphWriter</tt> implements the generation of <em>InChI</em> strings from Chem.MolecularGraph objects. The output data are written by means of a <tt>std::ostream</tt> object that was provided to the <tt>INCHIMolecularGraphWriter</tt> constructor.
# 
# For the generation of the <em>InChI</em> output, <tt>INCHIMolecularGraphWriter</tt> uses the function <tt>GetINCHI()</tt> of the <em>InChI C-API</em>. The return value of the function provides information about the status of the performed operation (see Chem.INCHIReturnCode) and can be accessed by the method getReturnCode(). Produced error and log messages are accessible via the methods getMessage() and getLogOutput(), respectively.
# 
# <tt>INCHIMolecularGraphWriter</tt> can be configured with the following control-parameters:
# 
# <table>
#  <tr><th>Control-Parameter</th><th>Default Value (see Chem.ControlParameterDefault)</th><th>Description</th></tr>
#  <tr><td>Chem.ControlParameter.COORDINATES_DIMENSION</td><td><tt>1</tt></td><td>Specifies the dimension of the atom coordinates to use for output generation. A value of <em>2</em> specifies 2D, a value of <em>3</em> specifies 3D, other values specify that any availables coordinates shall be used (3D takes precedence over 2D), and no coordinates otherwise</td></tr>
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
