#pragma once

// POSIX-specific interface for resolving a validated target into owned numeric
// endpoints. Socket address layouts are kept out of general domain types.
#include "port_scanner/result.hpp"
#include "port_scanner/types.hpp"

#include <sys/socket.h>

#include <string>
#include <vector>

namespace port_scanner {

// Owns a copied address value, independent of the temporary getaddrinfo list.
// The port field in address storage is zero; tcp_probe supplies the requested
// port immediately before connect. numeric_address is for stable user output.
struct ResolvedEndpoint {
    sockaddr_storage address{};
    socklen_t address_length{};
    int family{};
    std::string numeric_address;
};

// Resolve one target to the usable IPv4/IPv6 endpoints returned by the system.
// An empty successful list is treated as a resolution failure by the source.
[[nodiscard]] Result<std::vector<ResolvedEndpoint>>
resolve_target(const TargetSpec& target);

} // namespace port_scanner