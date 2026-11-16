#pragma once

// Coordinates DNS endpoints, bounded jobs, TCP probes, and result collection.
// The first implementation is sequential; the later concurrency session may
// change private strategy while preserving this caller-facing contract.
#include "port_scanner/resolver.hpp"
#include "port_scanner/result.hpp"
#include "port_scanner/scan_results.hpp"
#include "port_scanner/types.hpp"

namespace port_scanner {

// Perform the requested scan after options have been validated and target text
// parsed. This function is the network-work boundary and must honor all limits.
// It does not print; callers receive either collected outcomes or an Error.
[[nodiscard]] Result<ScanResults>
run_scan(const TargetSpec& target, const ScanOptions& options);

} // namespace port_scanner