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
 * \brief Provides I/O-streams capable of performing compression and decompression.
 */

#ifndef CDPL_UTIL_COMPRESSIONSTREAMS_HPP
#define CDPL_UTIL_COMPRESSIONSTREAMS_HPP

#include <fstream>

#include <boost/filesystem.hpp>
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

        enum CompressionAlgo
        {

          GZIP,
          BZIP2
        };

        template <CompressionAlgo CompAlgo>
        struct CompressionAlgoTraits;

        template <>
        struct CompressionAlgoTraits<GZIP>
        {

            typedef boost::iostreams::gzip_decompressor DecompFilter;
            typedef boost::iostreams::gzip_compressor CompFilter;
        };

        template <>
        struct CompressionAlgoTraits<BZIP2>
        {

            typedef boost::iostreams::bzip2_decompressor DecompFilter;
            typedef boost::iostreams::bzip2_compressor CompFilter;
        };

        template <CompressionAlgo CompAlgo, typename StreamType>
        class CompressionStreamBase : public StreamType {

        public:
            typedef typename StreamType::char_type             char_type;
            typedef typename StreamType::traits_type           traits_type;
            typedef typename StreamType::int_type                int_type;
            typedef typename StreamType::pos_type                pos_type;
            typedef typename StreamType::off_type                off_type;
            typedef std::basic_istream<char_type, traits_type> IStreamType;
            typedef std::basic_ostream<char_type, traits_type> OStreamType;

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

        template <CompressionAlgo CompAlgo, typename CharT = char, typename TraitsT = std::char_traits<CharT> >
        class DecompressionIStream : public CompressionStreamBase<CompAlgo, std::basic_istream<CharT, TraitsT> > {

        public:
            typedef typename std::basic_istream<CharT, TraitsT>  StreamType;
            typedef typename StreamType::char_type               char_type;
            typedef typename StreamType::traits_type             traits_type;
            typedef typename StreamType::int_type                  int_type;
            typedef typename StreamType::pos_type                  pos_type;
            typedef typename StreamType::off_type                  off_type;

            DecompressionIStream();
            DecompressionIStream(StreamType& stream);

            void open(StreamType& stream);
            void close();
        };

        template <CompressionAlgo CompAlgo, typename CharT = char, typename TraitsT = std::char_traits<CharT> >
        class CompressionOStream : public CompressionStreamBase<CompAlgo, std::basic_ostream<CharT, TraitsT> > {

        public:
            typedef typename std::basic_ostream<CharT, TraitsT>  StreamType;
            typedef typename StreamType::char_type               char_type;
            typedef typename StreamType::traits_type             traits_type;
            typedef typename StreamType::int_type                  int_type;
            typedef typename StreamType::pos_type                  pos_type;
            typedef typename StreamType::off_type                  off_type;

            CompressionOStream();
            CompressionOStream(StreamType& stream);

            ~CompressionOStream();

            void open(StreamType& stream);
            void close();

        private:
            StreamType* stream; 
            off_type    outPos;
        };

        template <CompressionAlgo CompAlgo, typename CharT = char, typename TraitsT = std::char_traits<CharT> >
        class CompressedIOStream : public CompressionStreamBase<CompAlgo, std::basic_iostream<CharT, TraitsT> > {

        public:
            typedef typename std::basic_iostream<CharT, TraitsT> StreamType;
            typedef typename StreamType::char_type               char_type;
            typedef typename StreamType::traits_type             traits_type;
            typedef typename StreamType::int_type                  int_type;
            typedef typename StreamType::pos_type                  pos_type;
            typedef typename StreamType::off_type                  off_type;

            CompressedIOStream();
            CompressedIOStream(StreamType& stream);

            ~CompressedIOStream();

            void open(StreamType& stream);
            void close();

        private:
            StreamType* stream; 
            off_type    outPos;
        };

        typedef DecompressionIStream<GZIP>  GZipIStream;
        typedef DecompressionIStream<BZIP2> BZip2IStream;
        typedef CompressionOStream<GZIP>    GZipOStream;
        typedef CompressionOStream<BZIP2>   BZip2OStream;
        typedef CompressedIOStream<GZIP>    GZipIOStream;
        typedef CompressedIOStream<BZIP2>   BZip2IOStream;
    }
}


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
CDPL::Util::DecompressionIStream<CompAlgo, CharT, TraitsT>::DecompressionIStream() {}

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
CDPL::Util::CompressionOStream<CompAlgo, CharT, TraitsT>::CompressionOStream(): stream(0) {}

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
CDPL::Util::CompressionOStream<CompAlgo, CharT, TraitsT>::CompressionOStream(StreamType& stream): stream(0)
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
CDPL::Util::CompressedIOStream<CompAlgo, CharT, TraitsT>::CompressedIOStream(): stream(0) {}

template <CDPL::Util::CompressionAlgo CompAlgo, typename CharT, typename TraitsT>
CDPL::Util::CompressedIOStream<CompAlgo, CharT, TraitsT>::CompressedIOStream(StreamType& stream): stream(0)
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
