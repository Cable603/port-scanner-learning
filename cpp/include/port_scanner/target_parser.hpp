#pragma once

// Converts a non-empty target string into a classified domain value. It does
// not perform DNS lookup or open sockets; those responsibilities belong to the
// resolver and probe modules respectively.
#include "port_scanner/result.hpp"
#include "port_scanner/types.hpp"

#include <string_view>

namespace port_scanner {

// Recognize IPv4/IPv6 literals and hostnames while preserving the original
// spelling for later diagnostics. Malformed or unsupported input is an error.
[[nodiscard]] Result<TargetSpec> parse_target(std::string_view target_text);

} // namespace port_scanner