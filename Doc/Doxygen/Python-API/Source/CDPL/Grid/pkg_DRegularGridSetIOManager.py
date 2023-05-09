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
# \brief 
#
class DRegularGridSetIOManager(Boost.Python.instance):

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
        def __getitem__(idx: int) -> DRegularGridSetInputHandler: pass

        ##
        # \brief 
        # \param fmt 
        # \return 
        #
        @staticmethod
        def __getitem__(fmt: CDPL.Base.DataFormat) -> DRegularGridSetInputHandler: pass

        ##
        # \brief 
        # \param name 
        # \return 
        #
        @staticmethod
        def __getitem__(name: str) -> DRegularGridSetInputHandler: pass

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
        def __delitem__(fmt: CDPL.Base.DataFormat) -> bool: pass

        ##
        # \brief 
        # \param handler 
        # \return 
        #
        @staticmethod
        def __delitem__(handler: DRegularGridSetInputHandler) -> bool: pass

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
        def __getitem__(idx: int) -> DRegularGridSetOutputHandler: pass

        ##
        # \brief 
        # \param fmt 
        # \return 
        #
        @staticmethod
        def __getitem__(fmt: CDPL.Base.DataFormat) -> DRegularGridSetOutputHandler: pass

        ##
        # \brief 
        # \param name 
        # \return 
        #
        @staticmethod
        def __getitem__(name: str) -> DRegularGridSetOutputHandler: pass

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
        def __delitem__(fmt: CDPL.Base.DataFormat) -> bool: pass

        ##
        # \brief 
        # \param handler 
        # \return 
        #
        @staticmethod
        def __delitem__(handler: DRegularGridSetOutputHandler) -> bool: pass

        ##
        # \brief 
        # \param  
        # \return 
        #
        @staticmethod
        def __len__(: ) -> int: pass

    ##
    # \brief FIXME!
    #
    inputHandlers = _UNKNOWN_VALUE_

    ##
    # \brief 
    #
    numInputHandlers = 3

    ##
    # \brief FIXME!
    #
    outputHandlers = _UNKNOWN_VALUE_

    ##
    # \brief 
    #
    numOutputHandlers = 3

    ##
    # \brief 
    # \param handler 
    #
    @staticmethod
    def registerInputHandler(handler: DRegularGridSetInputHandler) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    @staticmethod
    def getInputHandler(idx: int) -> DRegularGridSetInputHandler: pass

    ##
    # \brief 
    # \param fmt 
    # \return 
    #
    @staticmethod
    def getInputHandlerByFormat(fmt: CDPL.Base.DataFormat) -> DRegularGridSetInputHandler: pass

    ##
    # \brief 
    # \param name 
    # \return 
    #
    @staticmethod
    def getInputHandlerByName(name: str) -> DRegularGridSetInputHandler: pass

    ##
    # \brief 
    # \param file_ext 
    # \return 
    #
    @staticmethod
    def getInputHandlerByFileExtension(file_ext: str) -> DRegularGridSetInputHandler: pass

    ##
    # \brief 
    # \param mime_type 
    # \return 
    #
    @staticmethod
    def getInputHandlerByMimeType(mime_type: str) -> DRegularGridSetInputHandler: pass

    ##
    # \brief 
    # \param fmt 
    # \return 
    #
    @staticmethod
    def unregisterInputHandler(fmt: CDPL.Base.DataFormat) -> bool: pass

    ##
    # \brief 
    # \param idx 
    #
    @staticmethod
    def unregisterInputHandler(idx: int) -> None: pass

    ##
    # \brief 
    # \param handler 
    # \return 
    #
    @staticmethod
    def unregisterInputHandler(handler: DRegularGridSetInputHandler) -> bool: pass

    ##
    # \brief 
    # \param  
    # \return 
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
    # \brief 
    # \param handler 
    #
    @staticmethod
    def registerOutputHandler(handler: DRegularGridSetOutputHandler) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    @staticmethod
    def getOutputHandler(idx: int) -> DRegularGridSetOutputHandler: pass

    ##
    # \brief 
    # \param fmt 
    # \return 
    #
    @staticmethod
    def getOutputHandlerByFormat(fmt: CDPL.Base.DataFormat) -> DRegularGridSetOutputHandler: pass

    ##
    # \brief 
    # \param name 
    # \return 
    #
    @staticmethod
    def getOutputHandlerByName(name: str) -> DRegularGridSetOutputHandler: pass

    ##
    # \brief 
    # \param file_ext 
    # \return 
    #
    @staticmethod
    def getOutputHandlerByFileExtension(file_ext: str) -> DRegularGridSetOutputHandler: pass

    ##
    # \brief 
    # \param mime_type 
    # \return 
    #
    @staticmethod
    def getOutputHandlerByMimeType(mime_type: str) -> DRegularGridSetOutputHandler: pass

    ##
    # \brief 
    # \param fmt 
    # \return 
    #
    @staticmethod
    def unregisterOutputHandler(fmt: CDPL.Base.DataFormat) -> bool: pass

    ##
    # \brief 
    # \param idx 
    #
    @staticmethod
    def unregisterOutputHandler(idx: int) -> None: pass

    ##
    # \brief 
    # \param handler 
    # \return 
    #
    @staticmethod
    def unregisterOutputHandler(handler: DRegularGridSetOutputHandler) -> bool: pass

    ##
    # \brief 
    # \param  
    # \return 
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
