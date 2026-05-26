/* 
 * CompressionStreams.hpp 
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
 * \brief Definition of I/O-stream classes capable of performing compression and decompression.
 */

#ifndef CDPL_UTIL_COMPRESSIONSTREAMS_HPP
#define CDPL_UTIL_COMPRESSIONSTREAMS_HPP

#include <fstream>

#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>

#include "CDPL/Util/FileRemover.hpp"
#include "CDPL/Util/FileFunctions.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief Identifiers for the compression algorithms supported by the Util compression-stream wrappers.
         */
        enum CompressionAlgo
        {

            /** \brief Identifier for the gzip compression algorithm. */
            GZIP,
            /** \brief Identifier for the bzip2 compression algorithm. */
            BZIP2
        };

        /**
         * \brief Traits-style template selecting the boost::iostreams compression/decompression filters that implement
         *        a given Util::CompressionAlgo. Specialized for each supported algorithm.
         * \tparam CompAlgo The compression algorithm identifier.
         */
        template <CompressionAlgo CompAlgo>
        struct CompressionAlgoTraits;

        /**
         * \brief Util::CompressionAlgoTraits specialization for the gzip algorithm.
         */
        template <>
        struct CompressionAlgoTraits<GZIP>
        {

            /** \brief Decompression filter type (gzip). */
            typedef boost::iostreams::gzip_decompressor DecompFilter;
            /** \brief Compression filter type (gzip). */
            typedef boost::iostreams::gzip_compressor   CompFilter;
        };

        /**
         * \brief Util::CompressionAlgoTraits specialization for the bzip2 algorithm.
         */
        template <>
        struct CompressionAlgoTraits<BZIP2>
        {

            /** \brief Decompression filter type (bzip2). */
            typedef boost::iostreams::bzip2_decompressor DecompFilter;
            /** \brief Compression filter type (bzip2). */
            typedef boost::iostreams::bzip2_compressor   CompFilter;
        };

        /**
         * \brief %Base class for stream wrappers that buffer (de)compressed data through a temporary file.
         *
         * Subclasses inherit a hidden \c std::basic_filebuf and use it as the working buffer while transparently
         * compressing/decompressing data on open/close.
         *
         * \tparam CompAlgo The compression algorithm identifier (see Util::CompressionAlgo).
         * \tparam StreamType The standard stream type (std::basic_istream/ostream/iostream) to derive from.
         */
        template <CompressionAlgo CompAlgo, typename StreamType>
        class CompressionStreamBase : public StreamType
        {

          public:
            typedef typename StreamType::char_type             char_type;
            typedef typename StreamType::traits_type           traits_type;
            typedef typename StreamType::int_type              int_type;
            typedef typename StreamType::pos_type              pos_type;
            typedef typename StreamType::off_type              off_type;
            typedef std::basic_istream<char_type, traits_type> IStreamType;
            typedef std::basic_ostream<char_type, traits_type> OStreamType;

            /**
             * \brief Constructs the \c %CompressionStreamBase instance and installs the temporary-file buffer.
             */
            CompressionStreamBase();

          protected:
            virtual ~CompressionStreamBase() {}

            void closeTmpFile();
            void openTmpFile();

            void decompInput(IStreamType& is);
            void compOutput(OStreamType& os);

          private:
            typedef std::basic_filebuf<char_type, traits_type> FileBufType;

            FileBufType tmpFileBuf;
        };

        /**
         * \brief Input stream wrapper that transparently decompresses data read from an underlying compressed source stream.
         *
         * \tparam CompAlgo The compression algorithm identifier (see Util::CompressionAlgo).
         * \tparam CharT The character type of the stream.
         * \tparam TraitsT The character traits type of the stream.
         */
        template <CompressionAlgo CompAlgo, typename CharT = char, typename TraitsT = std::char_traits<CharT> >
        class DecompressionIStream : public CompressionStreamBase<CompAlgo, std::basic_istream<CharT, TraitsT> >
        {

          public:
            typedef typename std::basic_istream<CharT, TraitsT> StreamType;
            typedef typename StreamType::char_type              char_type;
            typedef typename StreamType::traits_type            traits_type;
            typedef typename StreamType::int_type               int_type;
            typedef typename StreamType::pos_type               pos_type;
            typedef typename StreamType::off_type               off_type;

            /**
             * \brief Constructs the \c %DecompressionIStream instance without an associated source stream.
             */
            DecompressionIStream();

            /**
             * \brief Constructs the \c %DecompressionIStream instance and immediately opens it on \a stream.
             * \param stream The compressed source stream to read from.
             */
            DecompressionIStream(StreamType& stream);

            /**
             * \brief Opens the decompression stream on \a stream.
             * \param stream The compressed source stream to read from.
             */
            void open(StreamType& stream);

            /**
             * \brief Closes the decompression stream and releases the temporary buffer.
             */
            void close();
        };

        /**
         * \brief Output stream wrapper that transparently compresses data and writes it to an underlying sink stream
         *        when the wrapper is closed or destroyed.
         *
         * \tparam CompAlgo The compression algorithm identifier (see Util::CompressionAlgo).
         * \tparam CharT The character type of the stream.
         * \tparam TraitsT The character traits type of the stream.
         */
        template <CompressionAlgo CompAlgo, typename CharT = char, typename TraitsT = std::char_traits<CharT> >
        class CompressionOStream : public CompressionStreamBase<CompAlgo, std::basic_ostream<CharT, TraitsT> >
        {

          public:
            typedef typename std::basic_ostream<CharT, TraitsT> StreamType;
            typedef typename StreamType::char_type              char_type;
            typedef typename StreamType::traits_type            traits_type;
            typedef typename StreamType::int_type               int_type;
            typedef typename StreamType::pos_type               pos_type;
            typedef typename StreamType::off_type               off_type;

            /**
             * \brief Constructs the \c %CompressionOStream instance without an associated sink stream.
             */
            CompressionOStream();

            /**
             * \brief Constructs the \c %CompressionOStream instance and immediately opens it on \a stream.
             * \param stream The sink stream that will receive the compressed output.
             */
            CompressionOStream(StreamType& stream);

            /**
             * \brief Destructor. Flushes any buffered data to the sink stream as compressed output.
             */
            ~CompressionOStream();

            /**
             * \brief Opens the compression stream on \a stream.
             * \param stream The sink stream that will receive the compressed output.
             */
            void open(StreamType& stream);

            /**
             * \brief Closes the compression stream and writes the compressed output to the sink stream.
             */
            void close();

          private:
            StreamType* stream;
            off_type    outPos;
        };

        /**
         * \brief Bidirectional stream wrapper that decompresses data read from \a stream into a temporary buffer and
         *        re-compresses the (possibly modified) buffer back to \a stream on close.
         *
         * \tparam CompAlgo The compression algorithm identifier (see Util::CompressionAlgo).
         * \tparam CharT The character type of the stream.
         * \tparam TraitsT The character traits type of the stream.
         */
        template <CompressionAlgo CompAlgo, typename CharT = char, typename TraitsT = std::char_traits<CharT> >
        class CompressedIOStream : public CompressionStreamBase<CompAlgo, std::basic_iostream<CharT, TraitsT> >
        {

          public:
            typedef typename std::basic_iostream<CharT, TraitsT> StreamType;
            typedef typename StreamType::char_type               char_type;
            typedef typename StreamType::traits_type             traits_type;
            typedef typename StreamType::int_type                int_type;
            typedef typename StreamType::pos_type                pos_type;
            typedef typename StreamType::off_type                off_type;

            /**
             * \brief Constructs the \c %CompressedIOStream instance without an associated source/sink stream.
             */
            CompressedIOStream();

            /**
             * \brief Constructs the \c %CompressedIOStream instance and immediately opens it on \a stream.
             * \param stream The compressed source/sink stream.
             */
            CompressedIOStream(StreamType& stream);

            /**
             * \brief Destructor. Flushes any pending modifications back to the sink stream as compressed output.
             */
            ~CompressedIOStream();

            /**
             * \brief Opens the bidirectional compression stream on \a stream.
             * \param stream The compressed source/sink stream.
             */
            void open(StreamType& stream);

            /**
             * \brief Closes the stream and writes any pending modifications back as compressed output.
             */
            void close();

          private:
            StreamType* stream;
            off_type    outPos;
        };

        /** \brief Input stream that transparently decompresses gzip-compressed data. */
        typedef DecompressionIStream<GZIP>  GZipIStream;
        /** \brief Input stream that transparently decompresses bzip2-compressed data. */
        typedef DecompressionIStream<BZIP2> BZip2IStream;
        /** \brief Output stream that transparently writes gzip-compressed data. */
        typedef CompressionOStream<GZIP>    GZipOStream;
        /** \brief Output stream that transparently writes bzip2-compressed data. */
        typedef CompressionOStream<BZIP2>   BZip2OStream;
        /** \brief Bidirectional stream that transparently (de)compresses gzip data. */
        typedef CompressedIOStream<GZIP>    GZipIOStream;
        /** \brief Bidirectional stream that transparently (de)compresses bzip2 data. */
        typedef CompressedIOStream<BZIP2>   BZip2IOStream;
    } // namespace Util
} // namespace CDPL


// CompressionStreamBase Implementation

template <CDPL::Util::CompressionAlgo CompAlgo, typename StreamType>
CDPL::Util::CompressionStreamBase<CompAlgo, StreamType>::CompressionStreamBase():
    StreamType(&tmpFileBuf)
{}

template <CDPL::Util::CompressionAlgo CompAlgo, typename StreamType>
void CDPL::Util::CompressionStreamBase<CompAlgo, StreamType>::closeTmpFile()
{
    if (!tmpFileBuf.close())
        this->setstate(std::ios_base::failbit);
    else
        this->clear();
}

template <CDPL::Util::CompressionAlgo CompAlgo, typename StreamType>
void CDPL::Util::CompressionStreamBase<CompAlgo, StreamType>::openTmpFile()
{
    FileRemover tmp_file_rem(genCheckedTempFilePath());

    if (!tmpFileBuf.open(tmp_file_rem.getPath().c_str(),
                         std::ios_base::in | std::ios_base::out |
                             std::ios_base::trunc | std::ios_base::binary))
        this->setstate(std::ios_base::failbit);
    else
        this->clear(std::ios_base::goodbit);
}

template <CDPL::Util::CompressionAlgo CompAlgo, typename StreamType>
void CDPL::Util::CompressionStreamBase<CompAlgo, StreamType>::decompInput(IStreamType& is)
{
    off_type rpos = is.tellg();

    is.seekg(0, std::ios_base::end);

    off_type rend = is.tellg();

    if (!is.good()) {
        this->setstate(std::ios_base::failbit);
        return;
    }

    if (rpos == rend)
        return;

    is.seekg(rpos);

    boost::iostreams::filtering_stream<boost::iostreams::input, char_type, traits_type> fs;

    fs.push(typename CDPL::Util::CompressionAlgoTraits<CompAlgo>::DecompFilter());
    fs.push(is);

    boost::iostreams::copy(fs, *this->rdbuf());

    if (this->tmpFileBuf.pubseekpos(0, std::ios_base::in | std::ios_base::out) != 0)
        this->setstate(std::ios_base::failbit);

    this->setstate(is.rdstate() | fs.rdstate());
}

template <CDPL::Util::CompressionAlgo CompAlgo, typename StreamType>
void CDPL::Util::CompressionStreamBase<CompAlgo, StreamType>::compOutput(OStreamType& os)
{
    if (tmpFileBuf.pubseekpos(0, std::ios_base::in) != 0) {
        this->setstate(std::ios_base::failbit);
        return;
    }

    boost::iostreams::filtering_stream<boost::iostreams::output, char_type, traits_type> fs;

    fs.push(typename CDPL::Util::CompressionAlgoTraits<CompAlgo>::CompFilter());
    fs.push(os);

    boost::iostreams::copy(*this->rdbuf(), fs);

    this->setstate(os.rdstate() | fs.rdstate());
}

// DecompressionIStream Implementation

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
CDPL::Util::DecompressionIStream<CompAlgo, CharT, TraitsT>::DecompressionIStream()
{}

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
CDPL::Util::DecompressionIStream<CompAlgo, CharT, TraitsT>::DecompressionIStream(StreamType& stream)
{
    open(stream);
}

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
void CDPL::Util::DecompressionIStream<CompAlgo, CharT, TraitsT>::open(StreamType& stream)
{
    this->openTmpFile();

    if (this->good())
        this->decompInput(stream);
}

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
void CDPL::Util::DecompressionIStream<CompAlgo, CharT, TraitsT>::close()
{
    this->closeTmpFile();
}

// CompressionOStream Implementation

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
CDPL::Util::CompressionOStream<CompAlgo, CharT, TraitsT>::CompressionOStream():
    stream(0)
{}

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
CDPL::Util::CompressionOStream<CompAlgo, CharT, TraitsT>::CompressionOStream(StreamType& stream):
    stream(0)
{
    open(stream);
}

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
CDPL::Util::CompressionOStream<CompAlgo, CharT, TraitsT>::~CompressionOStream()
{
    if (stream) {
        try {
            stream->seekp(outPos);
            this->compOutput(*stream);
        } catch (...) {}
    }
}

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
void CDPL::Util::CompressionOStream<CompAlgo, CharT, TraitsT>::open(StreamType& stream)
{
    this->openTmpFile();

    if (!this->good())
        return;

    outPos = stream.tellp();
    this->setstate(stream.rdstate());

    if (this->good())
        this->stream = &stream;
}

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
void CDPL::Util::CompressionOStream<CompAlgo, CharT, TraitsT>::close()
{
    if (stream) {
        stream->seekp(outPos);
        this->compOutput(*stream);

        if (!this->good())
            return;

        stream = 0;
    }

    this->closeTmpFile();
}

// CompressedIOStream Implementation

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
CDPL::Util::CompressedIOStream<CompAlgo, CharT, TraitsT>::CompressedIOStream():
    stream(0)
{}

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
CDPL::Util::CompressedIOStream<CompAlgo, CharT, TraitsT>::CompressedIOStream(StreamType& stream):
    stream(0)
{
    open(stream);
}

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
CDPL::Util::CompressedIOStream<CompAlgo, CharT, TraitsT>::~CompressedIOStream()
{
    if (stream) {
        try {
            stream->seekp(outPos);
            this->compOutput(*stream);
        } catch (...) {}
    }
}

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
void CDPL::Util::CompressedIOStream<CompAlgo, CharT, TraitsT>::open(StreamType& stream)
{
    this->openTmpFile();

    if (!this->good())
        return;

    outPos = stream.tellp();
    this->setstate(stream.rdstate());

    if (!this->good())
        return;

    this->decompInput(stream);

    if (this->good())
        this->stream = &stream;
}

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
void CDPL::Util::CompressedIOStream<CompAlgo, CharT, TraitsT>::close()
{
    if (stream) {
        stream->seekp(outPos);
        this->compOutput(*stream);

        if (!this->good())
            return;

        stream = 0;
    }

    this->closeTmpFile();
}

#endif // CDPL_UTIL_COMPRESSIONSTREAMS_HPP
