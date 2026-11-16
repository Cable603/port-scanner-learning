#pragma once

// Converts raw command-line fields into bounded settings. This module validates
// user-controlled values before DNS or socket activity can begin.
#include "port_scanner/result.hpp"
#include "port_scanner/types.hpp"

namespace port_scanner {

// Parse numeric fields and enforce the project's port, timeout, worker, and
// total-probe limits. The target string is kept for the target parser.
// Invalid input returns ErrorCode::invalid_argument or resource_limit.
[[nodiscard]] Result<ScanOptions> validate_options(const CliArguments& arguments);

} // namespace port_scanner