// *************************************************************************
//
// Licensed under the MIT License (see accompanying LICENSE file).
//
// The author of this code is: Daniel Farrell
// 
// Based on mmtf_python, adapted to c++ standards 2018
//
// *************************************************************************
//
#ifndef MMTF_OBJECT_ENCODERS_H
#define MMTF_OBJECT_ENCODERS_H

#include "structure_data.hpp"
#include <msgpack.hpp>

namespace msgpack {
MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
namespace adaptor {

/* *
 * @brief encode a mmtf::GroupType to a msgpack map type.
 *
 * We must use this method for packing because 'char' is treated as an int
 * by msgpack.  We cannot use the prepackaged intrusive method.
 */
template <>
struct object_with_zone<mmtf::GroupType> {
    void operator()(msgpack::object::with_zone& o, mmtf::GroupType const& v) const {
        o.type = type::MAP;
        o.via.map.size = 8;
        o.via.map.ptr = static_cast<msgpack::object_kv*>(o.zone.allocate_align(sizeof(msgpack::object_kv)*8, MSGPACK_ZONE_ALIGNOF(msgpack::object_kv)));
        o.via.map.ptr[0].key = msgpack::object("formalChargeList", o.zone);
        o.via.map.ptr[0].val = msgpack::object(v.formalChargeList, o.zone);
        o.via.map.ptr[1].key = msgpack::object("atomNameList", o.zone);
        o.via.map.ptr[1].val = msgpack::object(v.atomNameList, o.zone);
        o.via.map.ptr[2].key = msgpack::object("elementList", o.zone);
        o.via.map.ptr[2].val = msgpack::object(v.elementList, o.zone);
        o.via.map.ptr[3].key = msgpack::object("bondAtomList", o.zone);
        o.via.map.ptr[3].val = msgpack::object(v.bondAtomList, o.zone);
        o.via.map.ptr[4].key = msgpack::object("bondOrderList", o.zone);
        o.via.map.ptr[4].val = msgpack::object(v.bondOrderList, o.zone);
        o.via.map.ptr[5].key = msgpack::object("groupName", o.zone);
        o.via.map.ptr[5].val = msgpack::object(v.groupName, o.zone);
        o.via.map.ptr[6].key = msgpack::object("singleLetterCode", o.zone);
        o.via.map.ptr[6].val = msgpack::object(std::string(1,v.singleLetterCode), o.zone);
        o.via.map.ptr[7].key = msgpack::object("chemCompType", o.zone);
        o.via.map.ptr[7].val = msgpack::object(v.chemCompType, o.zone);
    }
};

} // namespace adaptor
} // MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
} // namespace msgpack

#endif
