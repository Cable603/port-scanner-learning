#pragma once

// Error vocabulary shared by the CLI, validation, resolver, probe, and application
// layers. This header records error data only; it performs no reporting or I/O.
#include <optional>
#include <string>

namespace port_scanner {

// Stable categories let callers react to failures without parsing message text.
enum class ErrorCode {
    invalid_argument, // User input is missing, malformed, or outside project limits.
    resolution_failed, // The requested host could not be resolved.
    socket_failed, // A socket setup or operating-system operation failed.
    resource_limit, // A configured bound would be exceeded.
    internal_error // An unexpected failure prevented a meaningful result.
};

// A value describing an operation-level failure.
// system_error is populated only when a relevant POSIX errno value was captured.
// Normal probe outcomes such as refusal and timeout belong in ProbeResult instead.
struct Error {
    ErrorCode code{ErrorCode::internal_error};
    std::string message;
    std::optional<int> system_error;
};

} // namespace port_scanner