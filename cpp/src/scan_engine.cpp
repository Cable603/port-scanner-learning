// Bounded scan orchestration placeholder (Sessions 17 and 21-22).
//
// Implement run_scan from scan_engine.hpp. Begin with the sequential flow:
// resolve endpoints -> enumerate the validated inclusive port interval ->
// enforce maximum_probe_count -> probe each job -> collect one result per job.
// The later worker-pool lesson may replace the scheduling strategy while
// preserving the public contract and all configured limits.
//
// This module coordinates work but does not parse CLI strings or print reports.
// Verify invalid options are rejected before reaching this boundary.
#include "port_scanner/scan_engine.hpp"