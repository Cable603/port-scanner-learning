#pragma once

// Describes one bounded TCP connection attempt to a resolved endpoint. Socket
// creation, nonblocking connect, timeout polling, and error mapping belong in
// tcp_probe.cpp, not in this interface.
#include "port_scanner/resolver.hpp"
#include "port_scanner/result.hpp"
#include "port_scanner/types.hpp"

#include <chrono>

namespace port_scanner {

// Attempt one TCP connection to endpoint:port. Refusal and timeout are ordinary
// ProbeStatus values; inability to set up the operation returns an Error.
// The timeout must be positive and within the validated project maximum.
[[nodiscard]] Result<ProbeResult>
probe_tcp(const ResolvedEndpoint& endpoint,
          Port port,
          std::chrono::milliseconds timeout);

} // namespace port_scanner