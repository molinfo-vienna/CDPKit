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
# \brief Reader for molecule data in the <em>IUPAC International Chemical Identifier (InChI)</em> [\ref INCHI] format.
# 
# <tt>INCHIMoleculeReader</tt> implements the conversion of <em>InChI</em> strings (or strings with auxiliary <em>InChI</em> information) to corresponding Chem.Molecule objects. The input data are read by means of a <tt>std::istream</tt> object that was provided to the <tt>INCHIMoleculeReader</tt> constructor.
# 
# For the actual decoding of the <em>InChI</em> input, <tt>INCHIMoleculeReader</tt> uses an appropriate function (<tt>GetStructFromINCHI()</tt> for <em>InChI</em> strings and <tt>Get_inchi_Input_FromAuxInfo()</tt> for auxiliary <em>InChI</em> information) of the <em>InChI C-API</em>. The return value of the called function provides information about the status of the performed operation (see Chem.INCHIReturnCode) and can be accessed by the method getReturnCode(). Produced error and log messages are accessible via the methods getMessage() and getLogOutput(), respectively.
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
    def __init__(is: Base.IStream) -> None: pass

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
