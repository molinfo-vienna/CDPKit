/* 
 * DataIOManager.hpp 
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
 * \brief Definition of the class CDPL::Base::DataIOManager.
 */

#ifndef CDPL_BASE_DATAIOMANAGER_HPP
#define CDPL_BASE_DATAIOMANAGER_HPP

#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <cstddef>

#include "CDPL/Base/APIPrefix.hpp"
#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Base/DataOutputHandler.hpp"
#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Molecule;
		class MolecularGraph;
		class Reaction;
	}

	namespace Pharm
	{

		class Pharmacophore;
		class FeatureContainer;
	}

	namespace Grid
	{

		template <typename T, typename CVT> class RegularGrid;
		template <typename T, typename CVT> class RegularGridSet;
	}

	namespace Base
	{

		/**
		 * \brief A singleton class that serves as a global registry for Base::DataInputHandler and Base::DataOutputHandler
		 *        implementation instances.
		 *
		 * \c %DataIOManager provides static methods for the registration and lookup of Base::DataInputHandler and
		 * Base::DataOutputHandler implementation instances that handle different input and output storage formats
		 * for a specific object type (specified by the template parameter \a T).
		 *
		 * Input and output handlers are registered by the methods registerInputHandler() and registerOutputHandler(). These
		 * methods expect a reference to an instance of the respective handler implementation as an argument (please note that
		 * the registered instance <em>must not be destroyed</em> as long as it is accessible via the \c %DataIOManager interface!).
		 *
		 * For the removal of registered handlers the unregisterInputHandler() and unregisterOutputHandler() family of overloaded
		 * methods is provided. These methods accept a reference to the registered handler instance, the handler index, the
		 * handled data format or an iterator pointing to the handler as an argument.
		 *
		 * Registered input handlers can be queried by the methods getInputHandlerByFormat(), getInputHandlerByName(), 
		 * getInputHandlerByFileExtension() and getInputHandlerByMimeType(), which allow to find a suitable handler for a given
		 * data format, data format name, file extension or mime-type. For the registered output handlers similar methods are
		 * provided.
		 *
		 * I/O handlers for data formats and object types supported by the \e %CDPL are registered in the static library
		 * initialization code. These built-in handlers are accessible by the linking client code as soon as the library
		 * initialization has finished. 
		 *
		 * \tparam T The type of the data objects for which the registered input and output handlers are parameterized.
		 */
		template <typename T>
		class DataIOManager
		{

		public:
			typedef DataInputHandler<T> InputHandlerType;
			typedef DataOutputHandler<T> OutputHandlerType;
	
			typedef typename InputHandlerType::SharedPointer InputHandlerPointer;
			typedef typename OutputHandlerType::SharedPointer OutputHandlerPointer;

		private:
			typedef std::vector<InputHandlerPointer> InputHandlerList;
			typedef std::vector<OutputHandlerPointer> OutputHandlerList;

		public:
			/**
			 * \brief An iterator used to iterate over the list of registered input handlers.
			 */
			typedef typename InputHandlerList::iterator InputHandlerIterator;

			/**
			 * \brief An iterator used to iterate over the list of registered output handlers.
			 */
			typedef typename OutputHandlerList::iterator OutputHandlerIterator;

			/**
			 * \brief Registers the specified Base::DataInputHandler implementation instance as an input handler.
			 * \param handler The Base::DataInputHandler implementation instance to register.
			 */
			static void registerInputHandler(const InputHandlerPointer& handler);

			/**
			 * \brief Registers the specified Base::DataOutputHandler implementation instanceas an output handler.
			 * \param handler The Base::DataOutputHandler implementation instance to register.
			 */
			static void registerOutputHandler(const OutputHandlerPointer& handler);

			/**
			 * \brief Unregisters the input handler for the specified data format.
			 *
			 * Only one handler at a time will be unregistered (in a first in - first out manner). If more than one handler has
			 * been registered for the given data format, the method has to be called multiple times to unregister all handlers.
			 *
			 * \param fmt Specifies the data format that is associated with the handler to unregister.
			 * \return \c true if a handler for the specified data format was found and has been unregistered,
			 *         and \c false otherwise.
			 */
			static bool unregisterInputHandler(const DataFormat& fmt);

			/**
			 * \brief Unregisters the output handler for the specified data format.
			 *
			 * Only one handler at a time will be unregistered (in a first in - first out manner). If more than one handler has
			 * been registered for the given data format, the method has to be called multiple times to unregister all handlers.
			 *
			 * \param fmt Specifies the data format that is associated with the handler to unregister.
			 * \return \c true if a handler for the specified data format was found and has been unregistered,
			 *         and \c false otherwise.
			 */
			static bool unregisterOutputHandler(const DataFormat& fmt);

			/**
			 * \brief Unregisters the specified Base::DataInputHandler implementation instance.
			 * \param handler The Base::DataInputHandler implementation instance to unregister.
			 * \return \c true if the handler was found and has been unregistered, and \c false otherwise.
			 */
			static bool unregisterInputHandler(const InputHandlerPointer& handler);

			/**
			 * \brief Unregisters the specified Base::DataOutputHandler implementation instance.
			 * \param handler The Base::DataOutputHandler implementation instance to unregister.
			 * \return \c true if the handler was found and has been unregistered, and \c false otherwise.
			 */
			static bool unregisterOutputHandler(const OutputHandlerPointer& handler);

			/**
			 * \brief Unregisters the input handler with the specified index.
			 * \param idx The zero-based index of the input handler to unregister.
			 * \throw Base::IndexError if \a idx is out of bounds.
			 */
			static void unregisterInputHandler(std::size_t idx);

			/**
			 * \brief Unregisters the output handler with the specified index.
			 * \param idx The zero-based index of the output handler to unregister.
			 * \throw Base::IndexError if \a idx is out of bounds.
			 */
			static void unregisterOutputHandler(std::size_t idx);

			/**
			 * \brief Unregisters the input handler pointed to by the iterator \a it.
			 * \param it An iterator pointing to the input handler to unregister.
			 * \throw Base::RangeError if \a it is not in the range [getInputHandlersBegin(), getInputHandlersEnd() - 1].
			 */
			static InputHandlerIterator unregisterInputHandler(const InputHandlerIterator& it);

			/**
			 * \brief Unregisters the output handler implementation instance pointed to by the iterator \a it.
			 * \param it An iterator pointing to the output handler to unregister.
			 * \throw Base::RangeError if \a it is not in the range [getOutputHandlersBegin(), getOutputHandlersEnd() - 1].
			 */
			static OutputHandlerIterator unregisterOutputHandler(const OutputHandlerIterator& it);

			/**
			 * \brief Returns the number of registered input handlers.
			 * \return The number of registered input handlers.
			 */
			static std::size_t getNumInputHandlers();

			/**
			 * \brief Returns the number of registered output handlers.
			 * \return The number of registered output handlers.
			 */
			static std::size_t getNumOutputHandlers();

			/**
			 * \brief Returns a reference to the registered input handler with the specified index.
			 * \param idx The zero-based index of the input handler to return.
			 * \return A reference to the input handler at the specified index.
			 * \throw Base::IndexError if \a idx is out of bounds.
			 */
			static const InputHandlerPointer& getInputHandler(std::size_t idx);

			/**
			 * \brief Returns a reference to the registered output handler with the specified index.
			 * \param idx The zero-based index of the output handler to return.
			 * \return A reference to the output handler with the specified index.
			 * \throw Base::IndexError if \a idx is out of bounds.
			 */
			static const OutputHandlerPointer& getOutputHandler(std::size_t idx);

			/**
			 * \brief Returns an iterator pointing to the beginning of the list of registered input handlers.
			 * \return An iterator pointing to the beginning of the list of registered input handlers.
			 */
			static InputHandlerIterator getInputHandlersBegin();

			/**
			 * \brief Returns an iterator pointing to the end of the list of registered input handlers.
			 * \return An iterator pointing to the end of the list of registered input handlers.
			 */
			static InputHandlerIterator getInputHandlersEnd();

			/**
			 * \brief Returns an iterator pointing to the beginning of the list of registered output handlers.
			 * \return An iterator pointing to the beginning of the list of registered output handlers.
			 */
			static OutputHandlerIterator getOutputHandlersBegin();

			/**
			 * \brief Returns an iterator pointing to the end of the list of registered output handlers.
			 * \return An iterator pointing to the end of the list of registered output handlers.
			 */
			static OutputHandlerIterator getOutputHandlersEnd();

			/**
			 * \brief Returns a pointer to a registered input handler for the specified data format.
			 * \param fmt Specifies the data format that is associated with the requested input handler.
			 * \return A pointer to an input handler for the specified data format, or \e null if a suitable handler is not available.
			 */
			static InputHandlerPointer getInputHandlerByFormat(const DataFormat& fmt);

			/**
			 * \brief Returns a pointer to a registered input handler for the data format with the specified name.
			 * \param name Specifies the name of the data format that is associated with the requested input handler.
			 * \return A pointer to an input handler for the data format with the specified name, or \e null if
			 *         a suitable handler is not available.
			 * \note The matching of the name is not case-sensitive.
			 */
			static InputHandlerPointer getInputHandlerByName(const std::string& name);

			/**
			 * \brief Returns a pointer to a registered input handler for the data format with the specified file extension.
			 * \param file_ext Specifies the file extension of the data format that is associated with the
			 *                 requested input handler.
			 * \return A pointer to an input handler for the data format with the specified file extension, or \e null if a
			 *         suitable handler is not available.
			 * \note The matching of the file extension is not case-sensitive.
			 */
			static InputHandlerPointer getInputHandlerByFileExtension(const std::string& file_ext);

			/**
			 * \brief Returns a pointer to a registered input handler for the data format with the specified mime-type.
			 * \param mime_type Specifies the mime-type of the data format that is associated with the
			 *                  requested input handler.
			 * \return A pointer to an input handler for the data format with the specified mime-type, or \e null if a
			 *         suitable handler is not available.
			 * \note The matching of the mime-type is not case-sensitive.
			 */
			static InputHandlerPointer getInputHandlerByMimeType(const std::string& mime_type);

			/**
			 * \brief Returns a pointer to a registered output handler for the specified data format.
			 * \param fmt Specifies the data format that is associated with the requested output handler.
			 * \return A pointer to an output handler for the specified data format, or \e null if a suitable handler is not available.
			 */
			static OutputHandlerPointer getOutputHandlerByFormat(const DataFormat& fmt);

			/**
			 * \brief Returns a pointer to a registered output handler for the data format with the specified name.
			 * \param name Specifies the name of the data format that is associated with the requested output handler.
			 * \return A pointer to an output handler for the data format with the specified name, or \e null if
			 *         a suitable handler is not available.
			 * \note The matching of the name is not case-sensitive.
			 */
			static OutputHandlerPointer getOutputHandlerByName(const std::string& name);

			/**
			 * \brief Returns a pointer to a registered output handler for the data format with the specified file extension.
			 * \param file_ext Specifies the file extension of the data format that is associated with the
			 *                 requested output handler.
			 * \return A pointer to an output handler for the data format with the specified file extension, or \e null if a
			 *         suitable handler is not available.
			 * \note The matching of the file extension is not case-sensitive.
			 */	
			static OutputHandlerPointer getOutputHandlerByFileExtension(const std::string& file_ext);

			/**
			 * \brief Returns a pointer to a registered output handler for the data format with the specified mime-type.
			 * \param mime_type Specifies the mime-type of the data format that is associated with the
			 *                  requested output handler.
			 * \return A pointer to an output handler for the data format with the specified mime-type, or \e null if a
			 *         suitable handler is not available.
			 * \note The matching of the mime-type is not case-sensitive.
			 */
			static OutputHandlerPointer getOutputHandlerByMimeType(const std::string& mime_type);

		private:
			DataIOManager() {}
			~DataIOManager() {}

			static DataIOManager& getInstance();

			InputHandlerList  inputHandlers;
			OutputHandlerList outputHandlers;
		};

		// \cond DOC_IMPL_DETAILS

		extern template
		class CDPL_BASE_API DataIOManager<Chem::Molecule>;
		
		extern template
		class CDPL_BASE_API DataIOManager<Chem::MolecularGraph>;
		
		extern template
		class CDPL_BASE_API DataIOManager<Chem::Reaction>;

		extern template
		class CDPL_BASE_API DataIOManager<Pharm::Pharmacophore>;

		extern template
		class CDPL_BASE_API DataIOManager<Pharm::FeatureContainer>;

		extern template
		class CDPL_BASE_API DataIOManager<Grid::RegularGrid<double, double> >;

		extern template
		class CDPL_BASE_API DataIOManager<Grid::RegularGridSet<double, double> >;

		// \endcond
	}
}


// Implementation

template <typename T>
CDPL::Base::DataIOManager<T>& CDPL::Base::DataIOManager<T>::getInstance() 
{
	static DataIOManager<T> instance;

    return instance;
}

template <typename T>
void CDPL::Base::DataIOManager<T>::registerInputHandler(const InputHandlerPointer& handler)
{
	getInstance().inputHandlers.push_back(handler);
}

template <typename T>
void CDPL::Base::DataIOManager<T>::registerOutputHandler(const OutputHandlerPointer& handler)
{
	getInstance().outputHandlers.push_back(handler);
}

template <typename T>
bool CDPL::Base::DataIOManager<T>::unregisterInputHandler(const DataFormat& fmt)
{
	InputHandlerList& handlers = getInstance().inputHandlers;

	typename InputHandlerList::iterator it = std::find_if(handlers.begin(), handlers.end(),
														  std::bind(std::equal_to<DataFormat>(), std::ref(fmt),
																	std::bind(&DataInputHandler<T>::getDataFormat, std::placeholders::_1)));
	if (it != handlers.end()) {
		handlers.erase(it);
		return true;
	}

	return false;
}

template <typename T>
bool CDPL::Base::DataIOManager<T>::unregisterOutputHandler(const DataFormat& fmt)
{
	OutputHandlerList& handlers = getInstance().outputHandlers;

	typename OutputHandlerList::iterator it = std::find_if(handlers.begin(), handlers.end(),
														   std::bind(std::equal_to<DataFormat>(), std::ref(fmt),
																	 std::bind(&DataOutputHandler<T>::getDataFormat, std::placeholders::_1)));
	if (it != handlers.end()) {
		handlers.erase(it);
		return true;
	}

	return false;
}

template <typename T>
bool CDPL::Base::DataIOManager<T>::unregisterInputHandler(const InputHandlerPointer& handler)
{
	InputHandlerList& handlers = getInstance().inputHandlers;

	typename InputHandlerList::iterator it = std::find(handlers.begin(), handlers.end(), handler);

	if (it != handlers.end()) {
		handlers.erase(it);
		return true;
	}

	return false;
}

template <typename T>
bool CDPL::Base::DataIOManager<T>::unregisterOutputHandler(const OutputHandlerPointer& handler)
{
	OutputHandlerList& handlers = getInstance().outputHandlers;

	typename OutputHandlerList::iterator it = std::find(handlers.begin(), handlers.end(), handler);

	if (it != handlers.end()) {
		handlers.erase(it);
		return true;
	}

	return false;
}

template <typename T>
void CDPL::Base::DataIOManager<T>::unregisterInputHandler(std::size_t idx)
{
	InputHandlerList& handlers = getInstance().inputHandlers;

	if (idx >= handlers.size())
		throw IndexError("DataIOManager: handler index out of bounds");

	handlers.erase(handlers.begin() + idx);
}

template <typename T>
void CDPL::Base::DataIOManager<T>::unregisterOutputHandler(std::size_t idx)
{
	using namespace std::placeholders;
	
	OutputHandlerList& handlers = getInstance().outputHandlers;

	if (idx >= handlers.size())
		throw IndexError("DataIOManager: handler index out of bounds");

	handlers.erase(handlers.begin() + idx);
}

template <typename T>
typename CDPL::Base::DataIOManager<T>::InputHandlerIterator 
CDPL::Base::DataIOManager<T>::unregisterInputHandler(const InputHandlerIterator& it)
{	
	InputHandlerList& handlers = getInstance().inputHandlers;

	if (it < handlers.begin() || it >= handlers.end())
		throw RangeError("DataIOManager: input-handler iterator out of valid range");

	return handlers.erase(it);
}

template <typename T>
typename CDPL::Base::DataIOManager<T>::OutputHandlerIterator
CDPL::Base::DataIOManager<T>::unregisterOutputHandler(const OutputHandlerIterator& it)
{
	OutputHandlerList& handlers = getInstance().outputHandlers;

	if (it < handlers.begin() || it >= handlers.end())
		throw RangeError("DataIOManager: output-handler iterator out of valid range");

	return handlers.erase(it);
}

template <typename T>
std::size_t CDPL::Base::DataIOManager<T>::getNumInputHandlers()
{
	return getInstance().inputHandlers.size();
}

template <typename T>
std::size_t CDPL::Base::DataIOManager<T>::getNumOutputHandlers()
{
	return getInstance().outputHandlers.size();
}

template <typename T>
const typename CDPL::Base::DataInputHandler<T>::SharedPointer& CDPL::Base::DataIOManager<T>::getInputHandler(std::size_t idx)
{
	const InputHandlerList& handlers = getInstance().inputHandlers;

	if (idx >= handlers.size())
		throw IndexError("DataIOManager: handler index out of bounds");

	return handlers[idx];
}

template <typename T>
const typename CDPL::Base::DataOutputHandler<T>::SharedPointer& CDPL::Base::DataIOManager<T>::getOutputHandler(std::size_t idx)
{
	const OutputHandlerList& handlers = getInstance().outputHandlers;

	if (idx >= handlers.size())
		throw IndexError("DataIOManager: handler index out of bounds");

	return handlers[idx];
}

template <typename T>
typename CDPL::Base::DataIOManager<T>::InputHandlerIterator CDPL::Base::DataIOManager<T>::getInputHandlersBegin()
{
	return getInstance().inputHandlers.begin();
}

template <typename T>
typename CDPL::Base::DataIOManager<T>::InputHandlerIterator CDPL::Base::DataIOManager<T>::getInputHandlersEnd()
{
	return getInstance().inputHandlers.end();
}

template <typename T>
typename CDPL::Base::DataIOManager<T>::OutputHandlerIterator CDPL::Base::DataIOManager<T>::getOutputHandlersBegin()
{
	return getInstance().outputHandlers.begin();
}

template <typename T>
typename CDPL::Base::DataIOManager<T>::OutputHandlerIterator CDPL::Base::DataIOManager<T>::getOutputHandlersEnd()
{
	return getInstance().outputHandlers.end();
}

template <typename T>
typename CDPL::Base::DataInputHandler<T>::SharedPointer CDPL::Base::DataIOManager<T>::getInputHandlerByFormat(const DataFormat& fmt)
{
	const InputHandlerList& handlers = getInstance().inputHandlers;

	typename InputHandlerList::const_iterator it = std::find_if(handlers.begin(), handlers.end(),
																std::bind(std::equal_to<DataFormat>(), std::ref(fmt),
																		  std::bind(&DataInputHandler<T>::getDataFormat, std::placeholders::_1)));
	return (it == handlers.end() ? InputHandlerPointer() : *it);
}

template <typename T>
typename CDPL::Base::DataInputHandler<T>::SharedPointer CDPL::Base::DataIOManager<T>::getInputHandlerByFileExtension(const std::string& file_ext)
{
	const InputHandlerList& handlers = getInstance().inputHandlers;

	typename InputHandlerList::const_iterator it = std::find_if(handlers.begin(), handlers.end(),
																std::bind(&DataFormat::matchesFileExtension, 
																		  std::bind(&DataInputHandler<T>::getDataFormat, std::placeholders::_1),
																		  std::ref(file_ext)));
	return (it == handlers.end() ? InputHandlerPointer() : *it);
}

template <typename T>
typename CDPL::Base::DataInputHandler<T>::SharedPointer CDPL::Base::DataIOManager<T>::getInputHandlerByName(const std::string& name)
{
	const InputHandlerList& handlers = getInstance().inputHandlers;

	typename InputHandlerList::const_iterator it = std::find_if(handlers.begin(), handlers.end(),
																std::bind(&DataFormat::matchesName, 
																		  std::bind(&DataInputHandler<T>::getDataFormat, std::placeholders::_1),
																		  std::ref(name)));
	return (it == handlers.end() ? InputHandlerPointer() : *it);
}

template <typename T>
typename CDPL::Base::DataInputHandler<T>::SharedPointer CDPL::Base::DataIOManager<T>::getInputHandlerByMimeType(const std::string& mime_type)
{
	const InputHandlerList& handlers = getInstance().inputHandlers;

	typename InputHandlerList::const_iterator it = std::find_if(handlers.begin(), handlers.end(),
																std::bind(&DataFormat::matchesMimeType, 
																		  std::bind(&DataInputHandler<T>::getDataFormat, std::placeholders::_1),
																		  std::ref(mime_type)));
	return (it == handlers.end() ? InputHandlerPointer() : *it);
}

template <typename T>
typename CDPL::Base::DataOutputHandler<T>::SharedPointer CDPL::Base::DataIOManager<T>::getOutputHandlerByFormat(const DataFormat& fmt)
{
	const OutputHandlerList& handlers = getInstance().outputHandlers;

	typename OutputHandlerList::const_iterator it = std::find_if(handlers.begin(), handlers.end(),
																 std::bind(std::equal_to<DataFormat>(), std::ref(fmt),
																		   std::bind(&DataOutputHandler<T>::getDataFormat, std::placeholders::_1)));
	return (it == handlers.end() ? OutputHandlerPointer() : *it);
}

template <typename T>
typename CDPL::Base::DataOutputHandler<T>::SharedPointer CDPL::Base::DataIOManager<T>::getOutputHandlerByName(const std::string& name)
{
	const OutputHandlerList& handlers = getInstance().outputHandlers;

	typename OutputHandlerList::const_iterator it = std::find_if(handlers.begin(), handlers.end(),
																 std::bind(&DataFormat::matchesName, 
																		   std::bind(&DataOutputHandler<T>::getDataFormat, std::placeholders::_1),
																		   std::ref(name)));
	return (it == handlers.end() ? OutputHandlerPointer() : *it);
}

template <typename T>
typename CDPL::Base::DataOutputHandler<T>::SharedPointer CDPL::Base::DataIOManager<T>::getOutputHandlerByFileExtension(const std::string& file_ext)
{
	const OutputHandlerList& handlers = getInstance().outputHandlers;

	typename OutputHandlerList::const_iterator it = std::find_if(handlers.begin(), handlers.end(),
																 std::bind(&DataFormat::matchesFileExtension, 
																		   std::bind(&DataOutputHandler<T>::getDataFormat, std::placeholders::_1),
																		   std::ref(file_ext)));
	return (it == handlers.end() ? OutputHandlerPointer() : *it);
}

template <typename T>
typename CDPL::Base::DataOutputHandler<T>::SharedPointer CDPL::Base::DataIOManager<T>::getOutputHandlerByMimeType(const std::string& mime_type)
{
	const OutputHandlerList& handlers = getInstance().outputHandlers;

	typename OutputHandlerList::const_iterator it = std::find_if(handlers.begin(), handlers.end(),
																 std::bind(&DataFormat::matchesMimeType, 
																		   std::bind(&DataOutputHandler<T>::getDataFormat, std::placeholders::_1),
																		   std::ref(mime_type)));
	return (it == handlers.end() ? OutputHandlerPointer() : *it);
}

#endif // CDPL_BASE_DATAIOMANAGER_HPP
