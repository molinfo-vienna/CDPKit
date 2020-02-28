/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HelperFunctions.hpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef APP_UTILS_HELPERFUNCTIONS_HPP
#define APP_UTILS_HELPERFUNCTIONS_HPP

#include <string>
#include <cstddef>

#include <boost/filesystem.hpp>

#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Base/DataIOManager.hpp"


namespace AppUtils
{

	template <typename T, typename OutIter>
	void getSupportedInputFormats(OutIter out)
	{
		using namespace CDPL;

		std::string format_str;

		for (typename Base::DataIOManager<T>::InputHandlerIterator it = Base::DataIOManager<T>::getInputHandlersBegin(),
				 end = Base::DataIOManager<T>::getInputHandlersEnd(); it != end; ++it, ++out) {

			const Base::DataFormat& fmt_desc = (*it)->getDataFormat();

			format_str.clear();
			format_str.append(fmt_desc.getDescription());
			format_str.append(" (");

			for (std::size_t i = 0; i < fmt_desc.getNumFileExtensions(); i++) {
				if (i > 0)
					format_str.append(", ");

				format_str.append("*.").append(fmt_desc.getFileExtension(i));
			}

			format_str.push_back(')');

			*out = format_str;
		}
	}

	template <typename T, typename OutIter>
	void getSupportedOutputFormats(OutIter out)
	{
		using namespace CDPL;

		std::string format_str;

		for (typename Base::DataIOManager<T>::OutputHandlerIterator it = Base::DataIOManager<T>::getOutputHandlersBegin(),
				 end = Base::DataIOManager<T>::getOutputHandlersEnd(); it != end; ++it, ++out) {

			const Base::DataFormat& fmt_desc = (*it)->getDataFormat();

			format_str.clear();
			format_str.append(fmt_desc.getDescription());
			format_str.append(" (");

			for (std::size_t i = 0; i < fmt_desc.getNumFileExtensions(); i++) {
				if (i > 0)
					format_str.append(", ");

				format_str.append("*.").append(fmt_desc.getFileExtension(i));
			}

			format_str.push_back(')');

			*out = format_str;
		}
	}

	template <typename T>
	typename CDPL::Base::DataInputHandler<T>::SharedPointer getInputHandler(const std::string& path)
	{
		using namespace CDPL;

		std::string file_name = boost::filesystem::path(path).filename().string();

		for (std::size_t pos = file_name.find('.'); pos != std::string::npos; pos = file_name.find('.', pos + 1)) {
			std::string file_ext = file_name.substr(pos + 1);
			
			typename Base::DataInputHandler<T>::SharedPointer handler = Base::DataIOManager<T>::getInputHandlerByFileExtension(file_ext);

			if (handler)
				return handler;
		}

		return typename CDPL::Base::DataInputHandler<T>::SharedPointer();
	}

	template <typename T>
	typename CDPL::Base::DataOutputHandler<T>::SharedPointer getOutputHandler(const std::string& path)
	{
		using namespace CDPL;

		std::string file_name = boost::filesystem::path(path).filename().string();

		for (std::size_t pos = file_name.find('.'); pos != std::string::npos; pos = file_name.find('.', pos + 1)) {
			std::string file_ext = file_name.substr(pos + 1);
			
			typename Base::DataOutputHandler<T>::SharedPointer handler = Base::DataIOManager<T>::getOutputHandlerByFileExtension(file_ext);

			if (handler)
				return handler;
		}

		return typename CDPL::Base::DataOutputHandler<T>::SharedPointer();
	}

	std::string formatTimeDuration(std::size_t secs);
}

#endif // APP_UTILS_HELPERFUNCTIONS_HPP
