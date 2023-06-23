/* 
 * Exceptions.hpp 
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
 * \brief Definition of exception classes.
 */

#ifndef CDPL_BASE_EXCEPTIONS_HPP
#define CDPL_BASE_EXCEPTIONS_HPP

#include <string>
#include <exception>

#include "CDPL/Base/APIPrefix.hpp"


namespace CDPL 
{

	namespace Base
	{

		/**
		 * \brief The root of the \e %CDPL exception hierarchy.
		 */
		class CDPL_BASE_API Exception : public std::exception
		{

		public:
			/**
			 * \brief Constructs an \c %Exception object with the error message set to \a msg.
			 * \param msg A message describing the cause of the exception and/or the location where the error occurred.
			 */
			Exception(const std::string& msg = "");

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~Exception() throw();

			/**
			 * \brief Returns the message describing the cause of the exception and/or the location where the error occurred.
			 * \return The message describing the cause of the exception and/or the location where the error occurred.
			 */
			const char* what() const throw();

		private:
			std::string message;
		};

		/**
		 * \brief Thrown to indicate errors caused by some invalid value.
		 */
		class CDPL_BASE_API ValueError : public Exception
		{

		public:
			/**
			 * \brief Constructs a \c %ValueError object with the error message set to \a msg.
			 * \param msg A message describing the cause of the exception and/or the location where the error occurred.
			 */
			ValueError(const std::string& msg = "");

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~ValueError() throw();
		};

		/**
		 * \brief Thrown when an operation requires or expects a valid pointer but a \e null pointer was provided.
		 */
		class CDPL_BASE_API NullPointerException : public ValueError
		{

		public:
			/**
			 * \brief Constructs a \c %NullPointerException object with the error message set to \a msg.
			 * \param msg A message describing the cause of the exception and/or the location where the error occurred.
			 */
			NullPointerException(const std::string& msg = "");

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~NullPointerException() throw();
		};

		/**
		 * \brief Thrown to indicate that a value is out of range.
		 */
		class CDPL_BASE_API RangeError : public ValueError
		{

		public:
			/**
			 * \brief Constructs a \c %RangeError object with the error message set to \a msg.
			 * \param msg A message describing the cause of the exception and/or the location where the error occurred.
			 */
			RangeError(const std::string& msg = "");

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~RangeError() throw();
		};
	
		/**
		 * \brief Thrown to indicate that the size of a (multidimensional) array is not correct.
		 */
		class CDPL_BASE_API SizeError : public ValueError
		{

		public:
			/**
			 * \brief Constructs a \c %SizeError object with the error message set to \a msg.
			 * \param msg A message describing the cause of the exception and/or the location where the error occurred.
			 */
			SizeError(const std::string& msg = "");

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~SizeError() throw();
		};
	
		/**
		 * \brief Thrown to indicate that an index is out of range.
		 */
		class CDPL_BASE_API IndexError : public RangeError
		{

		public:
			/**
			 * \brief Constructs an \c %IndexError object with the error message set to \a msg.
			 * \param msg A message describing the cause of the exception and/or the location where the error occurred.
			 */
			IndexError(const std::string& msg = "");

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~IndexError() throw();
		};

		/**
		 * \brief Thrown to indicate that some requested data item could not be found.
		 */
		class CDPL_BASE_API ItemNotFound : public Exception
		{

		public:
			/**
			 * \brief Constructs an \c %ItemNotFound object with the error message set to \a msg.
			 * \param msg A message describing the cause of the exception and/or the location where the error occurred.
			 */
			ItemNotFound(const std::string& msg = "");

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~ItemNotFound() throw();
		};

		/**
		 * \brief Thrown to indicate that a cast or conversion from a given source type to a requested target type is
		 *        not possible.
		 */
		class CDPL_BASE_API BadCast : public Exception
		{

		public:
			/**
			 * \brief Constructs a \c %BadCast object with the error message set to \a msg.
			 * \param msg A message describing the cause of the exception and/or the location where the error occurred.
			 */
			BadCast(const std::string& msg = "");

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~BadCast() throw();
		};

		/**
		 * \brief Thrown to indicate that some requested operation has failed (e.g. due to unfulfilled preconditions or
		 *        other errors).
		 */
		class CDPL_BASE_API OperationFailed : public Exception
		{

		public:
			/**
			 * \brief Constructs an \c %OperationFailed object with the error message set to \a msg.
			 * \param msg A message describing the cause of the exception and/or the location where the error occurred.
			 */
			OperationFailed(const std::string& msg = "");

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~OperationFailed() throw();
		};
	
		/**
		 * \brief Thrown to indicate that some requested calculation has failed.
		 */
		class CDPL_BASE_API CalculationFailed : public OperationFailed
		{

		public:
			/**
			 * \brief Constructs a \c %CalaculationFailed object with the error message set to \a msg.
			 * \param msg A message describing the cause of the exception and/or the location where the error occurred.
			 */
			CalculationFailed(const std::string& msg = "");

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~CalculationFailed() throw();
		};

		/**
		 * \brief Thrown to indicate that an I/O operation has failed because of physical (e.g. broken pipe) or
		 *        logical (e.g. invalid file format) errors.
		 */
		class CDPL_BASE_API IOError : public OperationFailed
		{

		public:
			/**
			 * \brief Constructs an \c %IOError object with the error message set to \a msg.
			 * \param msg A message describing the cause of the exception and/or the location where the error occurred.
			 */
			IOError(const std::string& msg = "");

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~IOError() throw();
		};
	}
}

#endif // CDPL_BASE_EXCEPTIONS_HPP
