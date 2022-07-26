#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
class DRegularGridIOManager(Boost.Python.instance):

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
        def __getitem__(idx: int) -> DRegularGridInputHandler: pass

        ##
        # \brief 
        # \param fmt 
        # \return 
        #
        @staticmethod
        def __getitem__(fmt: CDPL.Base.DataFormat) -> DRegularGridInputHandler: pass

        ##
        # \brief 
        # \param name 
        # \return 
        #
        @staticmethod
        def __getitem__(name: str) -> DRegularGridInputHandler: pass

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
        def __delitem__(handler: DRegularGridInputHandler) -> bool: pass

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
        def __getitem__(idx: int) -> DRegularGridOutputHandler: pass

        ##
        # \brief 
        # \param fmt 
        # \return 
        #
        @staticmethod
        def __getitem__(fmt: CDPL.Base.DataFormat) -> DRegularGridOutputHandler: pass

        ##
        # \brief 
        # \param name 
        # \return 
        #
        @staticmethod
        def __getitem__(name: str) -> DRegularGridOutputHandler: pass

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
        def __delitem__(handler: DRegularGridOutputHandler) -> bool: pass

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
    def registerInputHandler(handler: DRegularGridInputHandler) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    @staticmethod
    def getInputHandler(idx: int) -> DRegularGridInputHandler: pass

    ##
    # \brief 
    # \param fmt 
    # \return 
    #
    @staticmethod
    def getInputHandlerByFormat(fmt: CDPL.Base.DataFormat) -> DRegularGridInputHandler: pass

    ##
    # \brief 
    # \param name 
    # \return 
    #
    @staticmethod
    def getInputHandlerByName(name: str) -> DRegularGridInputHandler: pass

    ##
    # \brief 
    # \param file_ext 
    # \return 
    #
    @staticmethod
    def getInputHandlerByFileExtension(file_ext: str) -> DRegularGridInputHandler: pass

    ##
    # \brief 
    # \param mime_type 
    # \return 
    #
    @staticmethod
    def getInputHandlerByMimeType(mime_type: str) -> DRegularGridInputHandler: pass

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
    def unregisterInputHandler(handler: DRegularGridInputHandler) -> bool: pass

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
    def registerOutputHandler(handler: DRegularGridOutputHandler) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    @staticmethod
    def getOutputHandler(idx: int) -> DRegularGridOutputHandler: pass

    ##
    # \brief 
    # \param fmt 
    # \return 
    #
    @staticmethod
    def getOutputHandlerByFormat(fmt: CDPL.Base.DataFormat) -> DRegularGridOutputHandler: pass

    ##
    # \brief 
    # \param name 
    # \return 
    #
    @staticmethod
    def getOutputHandlerByName(name: str) -> DRegularGridOutputHandler: pass

    ##
    # \brief 
    # \param file_ext 
    # \return 
    #
    @staticmethod
    def getOutputHandlerByFileExtension(file_ext: str) -> DRegularGridOutputHandler: pass

    ##
    # \brief 
    # \param mime_type 
    # \return 
    #
    @staticmethod
    def getOutputHandlerByMimeType(mime_type: str) -> DRegularGridOutputHandler: pass

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
    def unregisterOutputHandler(handler: DRegularGridOutputHandler) -> bool: pass

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
