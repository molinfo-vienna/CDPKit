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
# \brief A singleton class that serves as a global registry for Pharm.FeatureContainerInputHandler and Pharm.FeatureContainerOutputHandler implementation instances.
# 
# <tt>DataIOManager</tt> provides static methods for the registration and lookup of Pharm.FeatureContainerInputHandler and Pharm.FeatureContainerOutputHandler implementation instances that handle different input and output storage formats.
# 
# Input and output handlers are registered by the methods registerInputHandler() and registerOutputHandler(). These methods expect a reference to an instance of the respective handler implementation as an argument (please note that the registered instance <em>must not be destroyed</em> as long as it is accessible via the <tt>DataIOManager</tt> interface!).
# 
# For the removal of registered handlers the unregisterInputHandler() and unregisterOutputHandler() family of overloaded methods is provided. These methods accept a reference to the registered handler instance, the handler index, the handled data format or an iterator pointing to the handler as an argument.
# 
# Registered input handlers can be queried by the methods getInputHandlerByFormat(), getInputHandlerByName(), getInputHandlerByFileExtension() and getInputHandlerByMimeType(), which allow to find a suitable handler for a given data format, data format name, file extension or mime-type. For the registered output handlers similar methods are provided.
# 
# I/O handlers for data formats and object types supported by the <em>CDPL</em> are registered in the static library initialization code. These built-in handlers are accessible by the linking client code as soon as the library initialization has finished.
# 
class FeatureContainerIOManager(Boost.Python.instance):

    ##
    # \brief 
    #
    class InputHandlerSequence(Boost.Python.instance):

        ##
        # \brief 
        # \param idx 
        # \return 
        #
        @staticmethod
        def __getitem__(idx: int) -> object: pass

        ##
        # \brief 
        # \param fmt 
        # \return 
        #
        @staticmethod
        def __getitem__(fmt: Base.DataFormat) -> object: pass

        ##
        # \brief 
        # \param name 
        # \return 
        #
        @staticmethod
        def __getitem__(name: str) -> object: pass

        ##
        # \brief 
        # \param idx 
        #
        @staticmethod
        def __delitem__(idx: int) -> None: pass

        ##
        # \brief 
        # \param fmt 
        # \return 
        #
        @staticmethod
        def __delitem__(fmt: Base.DataFormat) -> bool: pass

        ##
        # \brief 
        # \param handler 
        # \return 
        #
        @staticmethod
        def __delitem__(handler: object) -> bool: pass

        ##
        # \brief 
        # \param  
        # \return 
        #
        @staticmethod
        def __len__(: ) -> int: pass

    ##
    # \brief 
    #
    class OutputHandlerSequence(Boost.Python.instance):

        ##
        # \brief 
        # \param idx 
        # \return 
        #
        @staticmethod
        def __getitem__(idx: int) -> FeatureContainerOutputHandler: pass

        ##
        # \brief 
        # \param fmt 
        # \return 
        #
        @staticmethod
        def __getitem__(fmt: Base.DataFormat) -> FeatureContainerOutputHandler: pass

        ##
        # \brief 
        # \param name 
        # \return 
        #
        @staticmethod
        def __getitem__(name: str) -> FeatureContainerOutputHandler: pass

        ##
        # \brief 
        # \param idx 
        #
        @staticmethod
        def __delitem__(idx: int) -> None: pass

        ##
        # \brief 
        # \param fmt 
        # \return 
        #
        @staticmethod
        def __delitem__(fmt: Base.DataFormat) -> bool: pass

        ##
        # \brief 
        # \param handler 
        # \return 
        #
        @staticmethod
        def __delitem__(handler: FeatureContainerOutputHandler) -> bool: pass

        ##
        # \brief 
        # \param  
        # \return 
        #
        @staticmethod
        def __len__(: ) -> int: pass

    ##
    # \brief 
    #
    inputHandlers = _HIDDEN_VALUE_

    ##
    # \brief 
    #
    numInputHandlers = 0

    ##
    # \brief 
    #
    outputHandlers = _HIDDEN_VALUE_

    ##
    # \brief 
    #
    numOutputHandlers = 8

    ##
    # \brief Registers the specified Pharm.FeatureContainerInputHandler implementation instance.
    # 
    # \param handler The Pharm.FeatureContainerInputHandler implementation instance to register.
    # 
    @staticmethod
    def registerInputHandler(handler: object) -> None: pass

    ##
    # \brief Returns a reference to the registered Pharm.FeatureContainerInputHandler implementation instance with the specified index.
    # 
    # \param idx The zero-based index of the Pharm.FeatureContainerInputHandler implementation instance to return.
    # 
    # \return A reference to the Pharm.FeatureContainerInputHandler implementation instance with the specified index. 
    # 
    # \throw Base.IndexError if <em>idx</em> is out of bounds.
    # 
    @staticmethod
    def getInputHandler(idx: int) -> object: pass

    ##
    # \brief Returns a reference to a Pharm.FeatureContainerInputHandler implementation instance registered for the specified data format.
    # 
    # \param fmt Specifies the data format that is associated with the requested Pharm.FeatureContainerInputHandler implementation instance.
    # 
    # \return A reference to a Pharm.FeatureContainerInputHandler implementation instance registered for the specified data format, or <em>None</em> if not available.
    # 
    @staticmethod
    def getInputHandlerByFormat(fmt: Base.DataFormat) -> object: pass

    ##
    # \brief Returns a reference to a Pharm.FeatureContainerInputHandler implementation instance registered for the data format with the specified name.
    # 
    # \param name Specifies the name of the data format that is associated with the requested Pharm.FeatureContainerInputHandler implementation instance.
    # 
    # \return A reference to a Pharm.FeatureContainerInputHandler implementation instance registered for the data format with the specified name, or <em>None</em> if not available. 
    # 
    # \note The matching of the name is not case-sensitive.
    # 
    @staticmethod
    def getInputHandlerByName(name: str) -> object: pass

    ##
    # \brief Returns a reference to a Pharm.FeatureContainerInputHandler implementation instance registered for the data format with the specified file extension.
    # 
    # \param file_ext Specifies the file extension of the data format that is associated with the requested Pharm.FeatureContainerInputHandler implementation instance.
    # 
    # \return A reference to a Pharm.FeatureContainerInputHandler implementation instance registered for the data format with the specified file extension, or <em>None</em> if not available. 
    # 
    # \note The matching of the file extension is not case-sensitive.
    # 
    @staticmethod
    def getInputHandlerByFileExtension(file_ext: str) -> object: pass

    ##
    # \brief Returns a reference to a Pharm.FeatureContainerInputHandler implementation instance registered for the data format matching the extension of <em>file_name</em>.
    # 
    # \param file_name Specifies the file name for which to search for a data format that matches its extension.
    # 
    # \return A reference to a Pharm.FeatureContainerInputHandler implementation instance registered for the data format matching the extension of <em>file_name</em>, or <em>None</em> if not available. 
    # 
    # \note The matching of the file extension is not case-sensitive.
    # 
    @staticmethod
    def getInputHandlerByFileName(file_name: str) -> object: pass

    ##
    # \brief Returns a reference to a Pharm.FeatureContainerInputHandler implementation instance registered for the data format with the specified mime-type.
    # 
    # \param mime_type Specifies the mime-type of the data format that is associated with the requested Pharm.FeatureContainerInputHandler implementation instance.
    # 
    # \return A reference to a Pharm.FeatureContainerInputHandler implementation instance registered for the data format with the specified mime-type, or <em>None</em> if not available. 
    # 
    # \note The matching of the mime-type is not case-sensitive.
    # 
    @staticmethod
    def getInputHandlerByMimeType(mime_type: str) -> object: pass

    ##
    # \brief Unregisters the Pharm.FeatureContainerInputHandler implementation instance for the specified data format.
    # 
    # Only one handler instance at a time will be unregistered (in a first in - first out manner). If more than one handler instance has been registered for the given data format, the method has to be called multiple times to unregister all instances.
    # 
    # \param fmt Specifies the data format that is associated with the handler instance to unregister.
    # 
    # \return <tt>True</tt> if a handler instance for the specified data format was found and has been unregistered, and <tt>False</tt> otherwise.
    # 
    @staticmethod
    def unregisterInputHandler(fmt: Base.DataFormat) -> bool: pass

    ##
    # \brief Unregisters the Pharm.FeatureContainerInputHandler implementation instance with the specified index.
    # 
    # \param idx The zero-based index of the Pharm.FeatureContainerInputHandler implementation instance to unregister.
    # 
    # \throw Base.IndexError if <em>idx</em> is out of bounds.
    # 
    @staticmethod
    def unregisterInputHandler(idx: int) -> None: pass

    ##
    # \brief Unregisters the specified Pharm.FeatureContainerInputHandler implementation instance.
    # 
    # \param handler The Pharm.FeatureContainerInputHandler implementation instance to unregister.
    # 
    # \return <tt>True</tt> if the handler instance was found and has been unregistered, and <tt>False</tt> otherwise.
    # 
    @staticmethod
    def unregisterInputHandler(handler: object) -> bool: pass

    ##
    # \brief Returns the number of registered Pharm.FeatureContainerInputHandler implementation instances.
    # 
    # \return The number of registered Pharm.FeatureContainerInputHandler implementation instances.
    # 
    @staticmethod
    def getNumInputHandlers(: ) -> int: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def getInputHandlers(: ) -> InputHandlerSequence: pass

    ##
    # \brief Registers the specified Pharm.FeatureContainerOutputHandler implementation instance.
    # 
    # \param handler The Pharm.FeatureContainerOutputHandler implementation instance to register.
    # 
    @staticmethod
    def registerOutputHandler(handler: FeatureContainerOutputHandler) -> None: pass

    ##
    # \brief Returns a reference to the registered Pharm.FeatureContainerOutputHandler implementation instance with the specified index.
    # 
    # \param idx The zero-based index of the Pharm.FeatureContainerOutputHandler implementation instance to return.
    # 
    # \return A reference to the Pharm.FeatureContainerOutputHandler implementation instance with the specified index. 
    # 
    # \throw Base.IndexError if <em>idx</em> is out of bounds.
    # 
    @staticmethod
    def getOutputHandler(idx: int) -> FeatureContainerOutputHandler: pass

    ##
    # \brief Returns a reference to a Pharm.FeatureContainerOutputHandler implementation instance registered for the specified data format.
    # 
    # \param fmt Specifies the data format that is associated with the requested Pharm.FeatureContainerOutputHandler implementation instance.
    # 
    # \return A reference to a Pharm.FeatureContainerOutputHandler implementation instance registered for the specified data format, or <em>None</em> if not available.
    # 
    @staticmethod
    def getOutputHandlerByFormat(fmt: Base.DataFormat) -> FeatureContainerOutputHandler: pass

    ##
    # \brief Returns a reference to a Pharm.FeatureContainerOutputHandler implementation instance registered for the data format with the specified name.
    # 
    # \param name Specifies the name of the data format that is associated with the requested Pharm.FeatureContainerOutputHandler implementation instance.
    # 
    # \return A reference to a Pharm.FeatureContainerOutputHandler implementation instance registered for the data format with the specified name, or <em>None</em> if not available. 
    # 
    # \note The matching of the name is not case-sensitive.
    # 
    @staticmethod
    def getOutputHandlerByName(name: str) -> FeatureContainerOutputHandler: pass

    ##
    # \brief Returns a reference to a Pharm.FeatureContainerOutputHandler implementation instance registered for the data format with the specified file extension.
    # 
    # \param file_ext Specifies the file extension of the data format that is associated with the requested Pharm.FeatureContainerOutputHandler implementation instance.
    # 
    # \return A reference to a Pharm.FeatureContainerOutputHandler implementation instance registered for the data format with the specified file extension, or <em>None</em> if not available. 
    # 
    # \note The matching of the file extension is not case-sensitive.
    # 
    @staticmethod
    def getOutputHandlerByFileExtension(file_ext: str) -> FeatureContainerOutputHandler: pass

    ##
    # \brief Returns a reference to a Pharm.FeatureContainerOutputHandler implementation instance registered for the data format matching the extension of <em>file_name</em>.
    # 
    # \param file_name Specifies the file name for which to search for a data format that matches its extension.
    # 
    # \return A reference to a Pharm.FeatureContainerOutputHandler implementation instance registered for the data format matching the extension of <em>file_name</em>, or <em>None</em> if not available. 
    # 
    # \note The matching of the file extension is not case-sensitive.
    # 
    @staticmethod
    def getOutputHandlerByFileName(file_name: str) -> FeatureContainerOutputHandler: pass

    ##
    # \brief Returns a reference to a Pharm.FeatureContainerOutputHandler implementation instance registered for the data format with the specified mime-type.
    # 
    # \param mime_type Specifies the mime-type of the data format that is associated with the requested Pharm.FeatureContainerOutputHandler implementation instance.
    # 
    # \return A reference to a Pharm.FeatureContainerOutputHandler implementation instance registered for the data format with the specified mime-type, or <em>None</em> if not available. 
    # 
    # \note The matching of the mime-type is not case-sensitive.
    # 
    @staticmethod
    def getOutputHandlerByMimeType(mime_type: str) -> FeatureContainerOutputHandler: pass

    ##
    # \brief Unregisters the Pharm.FeatureContainerOutputHandler implementation instance for the specified data format.
    # 
    # Only one handler instance at a time will be unregistered (in a first in - first out manner). If more than one handler instance has been registered for the given data format, the method has to be called multiple times to unregister all instances.
    # 
    # \param fmt Specifies the data format that is associated with the handler instance to unregister.
    # 
    # \return <tt>True</tt> if a handler instance for the specified data format was found and has been unregistered, and <tt>False</tt> otherwise.
    # 
    @staticmethod
    def unregisterOutputHandler(fmt: Base.DataFormat) -> bool: pass

    ##
    # \brief Unregisters the Pharm.FeatureContainerOutputHandler implementation instance with the specified index.
    # 
    # \param idx The zero-based index of the Pharm.FeatureContainerOutputHandler implementation instance to unregister.
    # 
    # \throw Base.IndexError if <em>idx</em> is out of bounds.
    # 
    @staticmethod
    def unregisterOutputHandler(idx: int) -> None: pass

    ##
    # \brief Unregisters the specified Pharm.FeatureContainerOutputHandler implementation instance.
    # 
    # \param handler The Pharm.FeatureContainerOutputHandler implementation instance to unregister.
    # 
    # \return <tt>True</tt> if the handler instance was found and has been unregistered, and <tt>False</tt> otherwise.
    # 
    @staticmethod
    def unregisterOutputHandler(handler: FeatureContainerOutputHandler) -> bool: pass

    ##
    # \brief Returns the number of registered Pharm.FeatureContainerOutputHandler implementation instances.
    # 
    # \return The number of registered Pharm.FeatureContainerOutputHandler implementation instances.
    # 
    @staticmethod
    def getNumOutputHandlers(: ) -> int: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def getOutputHandlers(: ) -> OutputHandlerSequence: pass
