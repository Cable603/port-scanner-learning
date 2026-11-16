// One TCP connection attempt placeholder (Sessions 15 and 16).
//
// Implement probe_tcp from tcp_probe.hpp. The lesson will add socket creation,
// descriptor ownership, connect completion, and a finite timeout. Map success,
// refusal, timeout, and other per-port outcomes to ProbeStatus; reserve Result
// failure for setup/operation failures that prevent a meaningful attempt.
//
// Keep each call bounded by the validated timeout. Do not add packet crafting,
// stealth behavior, payload exchange, or service identification here.
#include "port_scanner/tcp_probe.hpp"
#include "port_scanner/socket_handle.hpp"