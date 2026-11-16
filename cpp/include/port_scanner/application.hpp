#pragma once

// Top-level orchestration boundary. This module connects CLI, validation,
// target parsing, scan execution, and reporting while keeping main minimal.
namespace port_scanner {

// Run the application using process arguments. Returns zero after a successful
// help display or completed scan; nonzero denotes a reported application error.
// This declaration does not perform any work.
int run_application(int argc, char* argv[]);

} // namespace port_scanner