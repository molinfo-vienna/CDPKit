/* 
 * SHA1.cpp 
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
 *
 *  Description:
 *	  This file implements the Secure Hashing Algorithm 1 as
 *	  defined in FIPS PUB 180-1 published April 17, 1995.
 *
 *	  The SHA-1, produces a 160-b_it message digest for a given
 *	  data stream.  It should take about 2**n steps to find a
 *	  message with the same digest as a given message and
 *	  2**(n/2) to find any two messages with the same digest,
 *	  when n is the digest size in b_its.  Therefore, this
 *	  algorithm can serve as a means of providing a
 *	  "FingerPrint" for a message.
 *
 *  Caveats:
 *	  SHA-1 is designed to work with messages less than 2^64 b_its
 *	  long. Although SHA-1 allows a message digest to be generated
 *	  for messages of any number of b_its less than 2^64, this
 *	  implementation only works with messages with a length that is
 *	  a multiple of the size of an 8-b_it character.
 */


#include "SHA1.hpp"

#define SHA1_CIRCULAR_SHIFT(b_its,word) (((word) << (b_its)) | ((word) >> (32-(b_its))))


using namespace CDPL;


const std::size_t Internal::SHA1::HASH_SIZE;


Internal::SHA1::SHA1()
{
	reset();
}

void Internal::SHA1::reset()
{
	length              = 0;
	messageBlockIndex   = 0;
	digestComputed      = false;

	intermediateHash[0] = 0x67452301;
	intermediateHash[1] = 0xEFCDAB89;
	intermediateHash[2] = 0x98BADCFE;
	intermediateHash[3] = 0x10325476;
	intermediateHash[4] = 0xC3D2E1F0;
}
			
void Internal::SHA1::processMessageBlock()
{
	static const std::uint32_t K[] = {   // Constants defined in SHA-1   
		0x5A827999,
		0x6ED9EBA1,
		0x8F1BBCDC,
		0xCA62C1D6
	};

	std::uint32_t temp;			 // Temporary word value		
	std::uint32_t W[80];			 // Word sequence			   
	std::uint32_t A, B, C, D, E;	 // Word buffers				

	// Initialize the first 16 words in the array W

	for(std::size_t t = 0; t < 16; t++) {
		W[t] =  messageBlock[t * 4] << 24;
		W[t] |= messageBlock[t * 4 + 1] << 16;
		W[t] |= messageBlock[t * 4 + 2] << 8;
		W[t] |= messageBlock[t * 4 + 3];
	}

	for(std::size_t t = 16; t < 80; t++) {
		W[t] = SHA1_CIRCULAR_SHIFT(1, W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16]);
	}

	A = intermediateHash[0];
	B = intermediateHash[1];
	C = intermediateHash[2];
	D = intermediateHash[3];
	E = intermediateHash[4];

	for(std::size_t t = 0; t < 20; t++) {
		temp = SHA1_CIRCULAR_SHIFT(5, A) + ((B & C) | ((~B) & D)) + E + W[t] + K[0];
		E = D;
		D = C;
		C = SHA1_CIRCULAR_SHIFT(30, B);

		B = A;
		A = temp;
	}

	for(std::size_t t = 20; t < 40; t++) {
		temp = SHA1_CIRCULAR_SHIFT(5, A) + (B ^ C ^ D) + E + W[t] + K[1];
		E = D;
		D = C;
		C = SHA1_CIRCULAR_SHIFT(30, B);
		B = A;
		A = temp;
	}

	for(std::size_t t = 40; t < 60; t++) {
		temp = SHA1_CIRCULAR_SHIFT(5, A) + ((B & C) | (B & D) | (C & D)) + E + W[t] + K[2];
		E = D;
		D = C;
		C = SHA1_CIRCULAR_SHIFT(30, B);
		B = A;
		A = temp;
	}

	for(std::size_t t = 60; t < 80; t++) {
		temp = SHA1_CIRCULAR_SHIFT(5, A) + (B ^ C ^ D) + E + W[t] + K[3];
		E = D;
		D = C;
		C = SHA1_CIRCULAR_SHIFT(30, B);
		B = A;
		A = temp;
	}

	intermediateHash[0] += A;
	intermediateHash[1] += B;
	intermediateHash[2] += C;
	intermediateHash[3] += D;
	intermediateHash[4] += E;

	messageBlockIndex = 0;
}

void Internal::SHA1::padMessage()
{
	// Check to see if the current message block is too small to hold
	// the initial padding bits and length.  If so, we will pad the
	// block, process it, and then continue padding into a second
	// block. 

	if (messageBlockIndex > 55) {
		messageBlock[messageBlockIndex++] = 0x80;

		while(messageBlockIndex < 64)
			messageBlock[messageBlockIndex++] = 0; 

		processMessageBlock();

		while(messageBlockIndex < 56)
			messageBlock[messageBlockIndex++] = 0; 

	} else {
		messageBlock[messageBlockIndex++] = 0x80;

		while(messageBlockIndex < 56)
			messageBlock[messageBlockIndex++] = 0; 
	}

	// Store the message length as the last 8 octets

	messageBlock[56] = std::uint8_t((length >> 56) & 0xff);
	messageBlock[57] = std::uint8_t((length >> 48) & 0xff);
	messageBlock[58] = std::uint8_t((length >> 40) & 0xff);
	messageBlock[59] = std::uint8_t((length >> 32) & 0xff);
	messageBlock[60] = std::uint8_t((length >> 24) & 0xff);
	messageBlock[61] = std::uint8_t((length >> 16) & 0xff);
	messageBlock[62] = std::uint8_t((length >> 8) & 0xff);
	messageBlock[63] = std::uint8_t(length & 0xff);

	processMessageBlock();
}
