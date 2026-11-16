// POSIX socket-descriptor ownership placeholder (Sessions 9 and 15).
//
// Implement SocketHandle's destructor, move constructor, move assignment,
// release, and reset as declared in socket_handle.hpp. Preserve single-owner
// semantics, leave moved-from instances empty, and make cleanup non-throwing.
//
// Use close only for a descriptor this object owns. This file does not create
// sockets or connect; those actions belong to tcp_probe.cpp.
#include "port_scanner/socket_handle.hpp"