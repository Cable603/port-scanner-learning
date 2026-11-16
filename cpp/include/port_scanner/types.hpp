#pragma once

// Stable value types shared across modules. This header has no POSIX dependency;
// operating-system address structures are isolated in resolver.hpp.
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>

namespace port_scanner {

using Port = std::uint16_t;

// An inclusive TCP port interval. Port zero is excluded because this project
// scans assigned service ports, not the special bind-time meaning of zero.
struct PortRange {
    Port first{};
    Port last{};

    // This tiny deterministic check is intentionally header-defined so callers
    // can validate a value without linking platform code.
    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return first != 0 && first <= last;
    }

    // Number of values in the inclusive interval; zero denotes invalid input.
    [[nodiscard]] constexpr std::size_t count() const noexcept {
        return is_valid()
            ? static_cast<std::size_t>(last) - static_cast<std::size_t>(first) + 1U
            : 0U;
    }
};

// A coarse classification made by the target parser before DNS resolution.
enum class TargetKind {
    hostname,
    ipv4_literal,
    ipv6_literal
};

// Parsed target text. The original spelling is kept for messages; the resolver
// turns it into one or more owned numeric endpoints in a later lesson.
struct TargetSpec {
    std::string original_text;
    TargetKind kind{TargetKind::hostname};
};

// Raw CLI fields remain strings until validation checks their syntax and bounds.
struct CliArguments {
    bool show_help{false};
    std::string target_text;
    std::string first_port_text;
    std::string last_port_text;
    std::string timeout_ms_text;
    std::string worker_count_text;
};

// Validated settings shared by the resolver, engine, and reporting layers.
struct ScanOptions {
    std::string target_text;
    PortRange ports;
    std::chrono::milliseconds timeout{500};
    std::size_t maximum_probe_count{256};
    std::size_t worker_count{1};
};

// One connection attempt's ordinary outcome. These are not whole-program errors.
enum class ProbeStatus {
    connected,
    refused,
    timed_out,
    failed
};

// Data recorded for one endpoint/port attempt. system_error is optional because
// not every outcome has a useful errno value; elapsed time supports summaries.
struct ProbeResult {
    std::string numeric_address;
    Port port{};
    ProbeStatus status{ProbeStatus::failed};
    std::chrono::milliseconds elapsed{0};
    std::optional<int> system_error;
};

} // namespace port_scanner