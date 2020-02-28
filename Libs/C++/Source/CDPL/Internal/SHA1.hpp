/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SHA1.hpp 
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

#ifndef CDPL_INTERNAL_SHA1_HPP
#define CDPL_INTERNAL_SHA1_HPP

#include <cstddef>

#include "CDPL/Base/IntegerTypes.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL 
{

	namespace Internal
	{

		/**
		 * \brief Implementation of the Secure Hashing Algorithm 1 [\ref WSHA]
		 *        as defined in FIPS PUB 180-1 published on April 17, 1995.
		 *
		 * The typical procedure to calculate and retrieve a message digest
		 * is as follows:
		 * \code
		 * SHA1 sha1;
		 * std::string str1("The quick brown fox "); // portion 1 of the message
		 * std::string str2("jumps over the ...");   // portion 2 of the message
		 *
		 * sha1.input(str1.begin(), str1.end()); // input portion 1 of the message
		 * sha1.input(str2.begin(), str2.end()); // input portion 2 of the message
		 *
		 * std::vector<unsigned char> digest;    // the final message digest will be stored here
		 *
		 * sha1.getResult(std::back_inserter(digest)); // copies the 160-bit hash into 'digest'
		 * \endcode
		 */
		class SHA1
		{

		public:
			static const std::size_t HASH_SIZE = 20; /**< The size of the SHA-1 message digest in bytes. */ 

			/**
			 * \brief Default constructor. 
			 */
			SHA1();

			/**
			 * \brief Resets the internal state and prepares for a new message digest 
			 *        calculation cycle.
			 */
			void reset();

			/**
			 * \brief Accepts arbitrary data as the next portion of the message.
			 *
			 * The value type of the data elements is limited to one of the built-in integral
			 * C++ types (char, int, long, ...). Furthermore, the data elements are copied bytewise
			 * with the least significant byte of a data element coming first. If input() is 
			 * called after getResult(), reset() is called automatically.
			 *
			 * \param start An iterator pointing to the beginning of the data.
			 * \param end An iterator pointing one past the last element of the data.
			 */
			template <typename InputIter>
			void input(InputIter start, InputIter end);

			/**
			 * \brief Copies the 160 bit message digest in octet chunks to a
			 *        destination specified by the output iterator \a out. 
			 * \param out An output iterator specifying the destination.
			 */
			template <typename OutputIter>
			void getResult(OutputIter out);

		private:
			void padMessage();
			void processMessageBlock();

			Base::uint32  intermediateHash[HASH_SIZE / 4]; // Message Digest
			Base::uint64  length;                          // Message length in b_its 
			Base::uint32  messageBlockIndex;               // Index into message block array 
			Base::uint8   messageBlock[64];                // 512-b_it message blocks
			bool          digestComputed;                  // Tells whether the message digest has been computed
		};
	}
}


// Implementation of template members

template <typename InputIter>
void CDPL::Internal::SHA1::input(InputIter in, InputIter end)
{
	if (digestComputed)
		reset();

	for ( ; in != end; ++in) {
		typename InputIter::value_type v = *in;

		for (std::size_t i = 0; i < sizeof(typename InputIter::value_type); i++) {
			messageBlock[messageBlockIndex++] = Base::uint8((v >> (i * 8)) & 0xff);
			length += 8;

			if (messageBlockIndex == 64)
				processMessageBlock();
		}
	}
}

template <typename OutputIter>
void CDPL::Internal::SHA1::getResult(OutputIter out)
{
	if (!digestComputed) {
		padMessage();

		for(std::size_t i = 0; i < 64; ++i)	// message may be sensitive, clear it out 
			messageBlock[i] = 0; 

		length   = 0;						// and clear length 
		digestComputed = true;
	}

	for (std::size_t i = 0; i < HASH_SIZE; i++, ++out)
		*out = (intermediateHash[i >> 2] >> (8 * (3 - (i & 0x03)))) & 0xff;
}

#endif // CDPL_INTERNAL_SHA1_HPP
