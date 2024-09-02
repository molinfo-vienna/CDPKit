// *************************************************************************
//
// Licensed under the MIT License (see accompanying LICENSE file).
//
// The authors of this code are: Gabriel Studer, Gerardo Tauriello
// 
// Based on mmtf_c developed by Julien Ferte (http://www.julienferte.com/),
// Anthony Bradley, Thomas Holder with contributions from Yana Valasatava,
// Gazal Kalyan, Alexander Rose.
//
// *************************************************************************

#ifndef MMTF_DECODER_H
#define MMTF_DECODER_H

#include "structure_data.hpp"
#include "errors.hpp"
#include "msgpack_decoders.hpp"
#include "map_decoder.hpp"

#include <msgpack.hpp>
#include <fstream>
#include <sstream>
#include <string>

namespace mmtf {

/**
 * @brief Decode an MMTF data structure from a mapDecoder.
 * @param[out] data   MMTF data structure to be filled
 * @param[in]  mapDecoder MapDecoder holding raw mmtf data
 * @throw mmtf::DecodeError if an error occured
 */
inline void decodeFromMapDecoder(StructureData& data, MapDecoder& mapDecoder);

/**
 * @brief Decode an MMTF data structure from a byte buffer.
 * @param[out] data   MMTF data structure to be filled
 * @param[in]  buffer File contents
 * @param[in]  size   Size of buffer
 * @throw mmtf::DecodeError if an error occured
 */
inline void decodeFromBuffer(StructureData& data, const char* buffer,
                             size_t size);

/**
 * @brief Decode an MMTF data structure from a stream.
 *
 * Note that the full stream is read from start to end before decoding it!
 * Use ::decodeFromBuffer if you wish to use just part of the stream.
 *
 * @param[out] data   MMTF data structure to be filled
 * @param[in]  stream Stream that holds mmtf data
 * @tparam Stream Any stream type compatible to std::istream
 * @throw mmtf::DecodeError if an error occured
 */
template <typename Stream>
inline void decodeFromStream(StructureData& data, Stream& stream);

/**
 * @brief Decode an MMTF data structure from an existing file.
 * @param[out] data     MMTF data structure to be filled
 * @param[in]  filename Path to file to load
 * @throw mmtf::DecodeError if an error occured
 */
inline void decodeFromFile(StructureData& data, const std::string& filename);

/**
 * @brief Get a mapDecoder for un-decoded MMTF data
 * @param[out] mapDecoder  MapDecoder to hold raw mmtf data
 *
 * Other parameters and behavior are as in ::decodeFromBuffer, but this doesn't
 * decode the MMTF content.
 */
inline void mapDecoderFromBuffer(MapDecoder& mapDecoder, const char* buffer,
                                 std::size_t size);

/**
 * @brief Get a mapDecoder into an un-decoded MMTF data
 * @param[out] mapDecoder  MapDecoder to hold raw mmtf data
 *
 * Other parameters and behavior are as in ::decodeFromStream, but this doesn't
 * decode the MMTF content.
 */
template <typename Stream>
inline void mapDecoderFromStream(MapDecoder& mapDecoder, Stream& stream);

/**
 * @brief Get a mapDecoder into an un-decoded MMTF data
 * @param[out] mapDecoder  MapDecoder to hold raw mmtf data
 *
 * Other parameters and behavior are as in ::decodeFromFile, but this doesn't
 * decode the MMTF content.
 */
inline void mapDecoderFromFile(MapDecoder& mapDecoder,
                               const std::string& filename);

// *************************************************************************
// IMPLEMENTATION
// *************************************************************************

inline void decodeFromMapDecoder(StructureData& data, MapDecoder& md) {
    mmtf::impl::decodeFromMapDecoder(data, md);
}

inline void decodeFromBuffer(StructureData& data, const char* buffer,
                             size_t size) {
    MapDecoder md;
    mapDecoderFromBuffer(md, buffer, size);
    decodeFromMapDecoder(data, md);
}

template <typename Stream>
inline void decodeFromStream(StructureData& data, Stream& stream) {
    MapDecoder md;
    mapDecoderFromStream(md, stream);
    decodeFromMapDecoder(data, md);
}

inline void decodeFromFile(StructureData& data, const std::string& filename) {
    MapDecoder md;
    mapDecoderFromFile(md, filename);
    decodeFromMapDecoder(data, md);
}

inline void mapDecoderFromBuffer(MapDecoder& mapDecoder, const char* buffer,
                                 std::size_t size) {
    mapDecoder.initFromBuffer(buffer, size);
}

template <typename Stream>
inline void mapDecoderFromStream(MapDecoder& mapDecoder, Stream& stream) {
    // parse straight into string buffer
    std::string buffer;
    stream.seekg(0, std::ios::end);
    buffer.resize(stream.tellg());
    stream.seekg(0, std::ios::beg);
    if (!buffer.empty()) stream.read(&buffer[0], buffer.size());
    mapDecoderFromBuffer(mapDecoder, buffer.data(), buffer.size());
}

inline void mapDecoderFromFile(MapDecoder& mapDecoder,
                               const std::string& filename) {
    // read file as binary
    std::ifstream ifs(filename.c_str(), std::ifstream::in | std::ios::binary);
    if (!ifs.is_open()) {
        throw DecodeError("Could not open file: " + filename);
    }
    mapDecoderFromStream(mapDecoder, ifs);
}

} // mmtf namespace

#endif
