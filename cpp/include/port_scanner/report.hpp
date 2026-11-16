#pragma once

// Formats completed scan outcomes for a caller-provided stream. Keeping output
// separate lets the engine be reused without printing or owning the console.
#include "port_scanner/scan_results.hpp"
#include "port_scanner/types.hpp"

#include <iosfwd>

namespace port_scanner {

// Write one record per attempted endpoint/port and a compact totals summary.
// Connection success is reported as reachability, not proof of service identity.
// This function does not resolve names or perform network activity.
void write_report(std::ostream& output,
                  const ScanOptions& options,
                  const ScanResults& results);

} // namespace port_scanner