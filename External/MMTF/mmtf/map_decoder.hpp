// *************************************************************************
//
// Licensed under the MIT License (see accompanying LICENSE file).
//
// The authors of this code are: Gabriel Studer, Gerardo Tauriello, and
// Daniel Farrell.
// 
// Based on mmtf_c developed by Julien Ferte (http://www.julienferte.com/),
// Anthony Bradley, Thomas Holder with contributions from Yana Valasatava,
// Gazal Kalyan, Alexander Rose.
//
// *************************************************************************

#ifndef MMTF_MAP_DECODER_H
#define MMTF_MAP_DECODER_H

#include "structure_data.hpp"
#include "binary_decoder.hpp"
#include "errors.hpp"

#include <msgpack.hpp>
#include <map>
#include <iostream>

namespace mmtf {

/**
 * @brief Helper class to decode msgpack maps into object fields.
 * Class cannot be copied as it contains unique pointers to msgpack data.
 */
class MapDecoder {
public:

    /**
     * @brief Construct empty decoder. Use init-functions to fill it.
     */
    MapDecoder() {}

    /**
     * @brief Construct decoder given a msgpack::object.
     * Reads out all key-value pairs and converts key to string if possible
     * (warns otherwise).
     * @throw mmtf::DecodeError if obj is not a map.
     */
    MapDecoder(const msgpack::object& obj);

    /**
     * @brief Construct decoder given a string to msgpack::object map.
     * Reads out all key-value pairs and converts key to string if possible
     * (warns otherwise).
     */
    MapDecoder(const std::map<std::string, msgpack::object>& map_in);

    /**
     * @brief Initialize given a msgpack::object.
     * Clears internal data and has same effect as
     * MapDecoder::MapDecoder(const msgpack::object&).
     */
    void initFromObject(const msgpack::object& obj);
    /**
     * @brief Initialize from byte buffer of given size.
     * Unpacks data and then same effect as MapDecoder::initFromObject.
     */
    void initFromBuffer(const char* buffer, size_t size);

    /**
     * @brief Extract value from map and decode into target.
     *
     * @param[in]  key      Key into msgpack map.
     * @param[in]  required True if field is required by MMTF specs.
     * @param[out] target   Store decoded value into this field.
     *
     * If msgpack type is not as expected, we write a warning to stderr.
     * If conversion to the target type fails, msgpack throws an exception.
     * If a required field is missing in the map or if binary decoding fails,
     * we throw an mmtf::DecodeError.
     */
    template<typename T>
    void decode(const std::string& key, bool required, T& target) const;

    /**
     * @brief Don't decode, but instead just copy map-contents onto a zone
     *        for later decoding/processing you should use this when you have
     *        nested msgpack objects.
     *        Note: There is some copy overhead here. If speed becomes an issue
     *              we should come up with a way to keep the original handle alive.
     * @param[in]  key      Key into msgpack map.
     * @param[in]  required True if field is required by MMTF specs or you
     * @param[out] target   std::map<std::string, msgpack::object> that holds access to data on zone.
     * @param[in]  zone     msgpack::zone to copy data onto
     *
     * If msgpack type is not as expected, we write a warning to stderr.
     * If conversion to the target type fails, msgpack throws an exception.
     * If a required field is missing in the map or if binary decoding fails,
     * we throw an mmtf::DecodeError.
     */
    void
    copy_decode(const std::string& key, bool required,
                std::map<std::string, msgpack::object>& target,
                msgpack::zone& zone) const;

    /**
     * @brief Check if there are any keys, that were not decoded.
     * This is to be called after all expected fields have been decoded.
     * A warning is written to stderr for each non-decoded key.
     */
    void checkExtraKeys() const;

private:
    // when constructed with byte buffer, we keep unpacked object
    // NOTE: this contains a unique pointer to msgpack data (cannot copy)
    msgpack::object_handle object_handle_;
    // key-value pairs extracted from msgpack map
    typedef std::map<std::string, const msgpack::object*> data_map_type_;
    data_map_type_ data_map_;
    // set of keys that were successfully decoded
    mutable std::set<std::string> decoded_keys_;

    /**
     * @brief Initialize object given an object
     * helper function used by constructors
     */
    void init_from_msgpack_obj(const msgpack::object& obj);

    // type checking (note: doesn't check array elements)
    // -> only writes warning to cerr
    // -> exception thrown by msgpack if conversion fails
    void checkType_(const std::string& key, msgpack::type::object_type type,
                    const float& target) const;
    void checkType_(const std::string& key, msgpack::type::object_type type,
                    const int32_t& target) const;
    void checkType_(const std::string& key, msgpack::type::object_type type,
                    const char& target) const;
    void checkType_(const std::string& key, msgpack::type::object_type type,
                    const std::string& target) const;
    template <typename T>
    void checkType_(const std::string& key, msgpack::type::object_type type,
                    const std::vector<T>& target) const;
    template <typename T>
    void checkType_(const std::string& key, msgpack::type::object_type type,
                    const T& target) const;
};

// *************************************************************************
// IMPLEMENTATION
// *************************************************************************

inline MapDecoder::MapDecoder(const msgpack::object& obj) {
    init_from_msgpack_obj(obj);
}

inline MapDecoder::MapDecoder(const std::map<std::string, msgpack::object>& map_in) {
    std::map<std::string, msgpack::object>::const_iterator it;
    for (it = map_in.begin(); it != map_in.end(); ++it) {
        data_map_[it->first] = &(it->second);
    }
}

inline void MapDecoder::initFromObject(const msgpack::object& obj) {
    data_map_.clear();
    decoded_keys_.clear();
    init_from_msgpack_obj(obj);
}

inline void MapDecoder::initFromBuffer(const char* buffer, std::size_t size) {
    msgpack::unpack(object_handle_, buffer, size);
    initFromObject(object_handle_.get());
}

void
inline MapDecoder::copy_decode(const std::string& key, bool required,
                               std::map<std::string, msgpack::object>& target,
                               msgpack::zone & zone) const {
    // note: cost of O(M*log(N)) string comparisons (M parsed, N in map)
    data_map_type_::const_iterator it = data_map_.find(key);
    if (it != data_map_.end()) {
        decoded_keys_.insert(key);
        // expensive copy here
        msgpack::object tmp_object(*it->second, zone);
        tmp_object.convert(target);
    }
    else if (required) {
        throw DecodeError("MsgPack MAP does not contain required entry "
                          + key);
    }
}

template<typename T>
inline void MapDecoder::decode(const std::string& key, bool required, T& target) const {
    // note: cost of O(M*log(N)) string comparisons (M parsed, N in map)
    data_map_type_::const_iterator it = data_map_.find(key);
    if (it != data_map_.end()) {
        checkType_(key, it->second->type, target);
        if (it->second->type == msgpack::type::BIN) {
            BinaryDecoder bd(*it->second, key);
            bd.decode(target);
        } else {
            it->second->convert(target);
        }
        decoded_keys_.insert(key);
    }
    else if (required) {
        throw DecodeError("MsgPack MAP does not contain required entry "
                          + key);
    }
}


inline void MapDecoder::checkExtraKeys() const {
    // note: cost of O(N*log(M))) string comparisons (M parsed, N in map)
    // simple set difference algorithm
    data_map_type_::const_iterator map_it;
    std::set<std::string>::const_iterator parsed_it;
    for (map_it = data_map_.begin(); map_it != data_map_.end(); ++map_it) {
         parsed_it = decoded_keys_.find(map_it->first);
         if (parsed_it == decoded_keys_.end()) {
            std::cerr << "Warning: Found non-parsed key " << map_it->first
                      << " in MsgPack MAP.\n";
         }
    }
}

inline void MapDecoder::init_from_msgpack_obj(const msgpack::object& obj) {
    // sanity checks
    if (obj.type != msgpack::type::MAP) {
        throw DecodeError("Expected msgpack type to be MAP");
    }
    // get data
    msgpack::object_kv* current_key_value = obj.via.map.ptr;
    msgpack::object_kv* last_key_value = current_key_value + obj.via.map.size;
    for (; current_key_value != last_key_value; ++current_key_value) { 
        msgpack::object* key = &(current_key_value->key); 
        msgpack::object* value = &(current_key_value->val); 
        if (key->type == msgpack::type::STR) {        
            std::string data_map_key(key->via.str.ptr, key->via.str.size);
            data_map_[data_map_key] = value;
        } else {
            std::cerr << "Warning: Found non-string key type " << key->type
                      << "! Skipping..." << std::endl;
        }
    }
}

inline void MapDecoder::checkType_(const std::string& key,
                                   msgpack::type::object_type type,
                                   const float&) const {
    if (type != msgpack::type::FLOAT32 && type != msgpack::type::FLOAT64) {
        std::cerr << "Warning: Non-float type " << type << " found for "
                     "entry " << key << std::endl;
    }
}
inline void MapDecoder::checkType_(const std::string& key,
                                   msgpack::type::object_type type,
                                   const int32_t&) const {
    if (   type != msgpack::type::POSITIVE_INTEGER
        && type != msgpack::type::NEGATIVE_INTEGER) {
        std::cerr << "Warning: Non-int type " << type << " found for "
                     "entry " << key << std::endl;
    }
}
inline void MapDecoder::checkType_(const std::string& key,
                                   msgpack::type::object_type type,
                                   const char&) const {
    if (type != msgpack::type::STR) {
        std::cerr << "Warning: Non-string type " << type << " found for "
                     "entry " << key << std::endl;
    }
}
inline void MapDecoder::checkType_(const std::string& key,
                                   msgpack::type::object_type type,
                                   const std::string&) const {
    if (type != msgpack::type::STR) {
        std::cerr << "Warning: Non-string type " << type << " found for "
                     "entry " << key << std::endl;
    }
}

template <typename T>
void MapDecoder::checkType_(const std::string& key,
                            msgpack::type::object_type type,
                            const std::vector<T>&) const {
    if (type != msgpack::type::ARRAY && type != msgpack::type::BIN) {
        std::cerr << "Warning: Non-array type " << type << " found for "
                     "entry " << key << std::endl;
    }
}


template <typename T>
void MapDecoder::checkType_(const std::string&,
                            msgpack::type::object_type,
                            const T &) const {
    // Do nothing -- allow all through
}

} // mmtf namespace

#endif
