/* 
 * DataIOBase.hpp 
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
 * \brief Definition of the class CDPL::Base::DataIOBase.
 */

#ifndef CDPL_BASE_DATAIOBASE_HPP
#define CDPL_BASE_DATAIOBASE_HPP

#include <vector>
#include <utility>
#include <cstddef>
#include <functional>

#include "CDPL/Base/APIPrefix.hpp"
#include "CDPL/Base/ControlParameterContainer.hpp"


namespace CDPL 
{

    namespace Base
    {

        /**
         * \brief Provides infrastructure for the registration of I/O callback functions.
         *
         * The purpose of \c %DataIOBase is to provide methods for the registration of I/O callback functions
         * to subclasses implementing the input and output of data objects (see Base::DataReader and Base::DataWriter).
         * I/O callbacks allow client code to be notified whenever a data object was read, written or skipped. I/O callbacks are
         * registered by calling the method registerIOCallback() with an argument of type DataIOBase::IOCallbackFunction.
         * DataIOBase::IOCallbackFunction is a generic functor implementation that is able to wrap any compatible (in terms
         * of return and argument type) function pointer or function object. Therefore, no special requirements beside return and
         * argument types are imposed on the type of the used I/O callback target function.
         */
        class CDPL_BASE_API DataIOBase : public ControlParameterContainer
        {

        public:
            /**
             * \brief A functor class used to wrap I/O callback target functions.
             *
             * \c %IOCallbackFunction allows to wrap any function pointer or function object compatible with a return type
             * of \c void and two arguments of type <tt>const %DataIOBase&</tt> and <tt>double</tt> (see [\ref FUNWRP]).
             */
            typedef std::function<void(const DataIOBase&, double)> IOCallbackFunction;
    
            /**
             * \brief Registers an I/O callback target function.
             * \param func A DataIOBase::IOCallbackFunction instance wrapping the target function.
             * \return An identifier for the registered callback.
             */
            std::size_t registerIOCallback(const IOCallbackFunction& func);

            /**
             * \brief Unregisters the I/O callback function specified by \a id.
             *
             * If a registered callback with the identifier \a id does not exist, the method has no effect.
             *
             * \param id The identifier of the callback function to unregister.
             */
            void unregisterIOCallback(std::size_t id);

            /**
             * \brief Invokes all registered I/O callback functions with the argument \c *this.
             * \param progress An indicator for the progress of the current I/O operation in the range [0, 1].
             */
            void invokeIOCallbacks(double progress) const;

            /**
             * \brief Clears all registered I/O callback functions.
             */
            void clearIOCallbacks();

        protected:
            /**
             * \brief Default constructor.
             */
            DataIOBase() {}

            /**
             * \brief Copy constructor.
             * \param io_base The \c %DataIOBase instance to copy.
             * \note I/O callbacks registered on \a io_base are not copied.
             */
            DataIOBase(const DataIOBase& io_base): ControlParameterContainer(io_base) {}

            /**
             * \brief Destructor.
             */
            ~DataIOBase() {}

            /**
             * \brief Assignment operator.
             * \param io_base The \c %DataIOBase instance to copy.
             * \return A reference to itself.
             * \note I/O callbacks registered on \a io_base are not copied.
             */
            DataIOBase& operator=(const DataIOBase& io_base);

        private:
            typedef std::pair<std::size_t, IOCallbackFunction> CallbackListEntry;
            typedef std::vector<CallbackListEntry> CallbackList;

            CallbackList callbacks;
        };
    }
}

#endif // CDPL_BASE_DATAIOBASE_HPP
