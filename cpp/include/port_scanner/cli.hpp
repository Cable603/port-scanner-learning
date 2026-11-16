#pragma once

// Command-line boundary: interpret argv shape and option names, but keep numeric
// bounds and project policy in validation.cpp.
#include "port_scanner/result.hpp"
#include "port_scanner/types.hpp"

#include <string>
#include <string_view>

namespace port_scanner {

// Expected form: program --target HOST --start PORT --end PORT
//               [--timeout-ms N] [--workers N]
// --help returns CliArguments with show_help set. Malformed syntax returns an
// invalid-argument Error before resolver or socket modules are called.
[[nodiscard]] Result<CliArguments>
parse_command_line(int argc, char* argv[]);

// Build concise usage text using the executable name supplied by the caller.
[[nodiscard]] std::string usage_text(std::string_view program_name);

} // namespace port_scanner