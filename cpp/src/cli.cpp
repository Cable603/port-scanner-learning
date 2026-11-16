// Command-line parsing placeholder (Session 12).
//
// This source will implement parse_command_line and usage_text from cli.hpp.
// It owns option names, required/optional argument shape, and help behavior.
// Numeric conversion and port/timeout/worker limits belong to validation.cpp.
//
// Keep parser errors descriptive and return them as Result values. Do not resolve
// hostnames or open sockets from this module.
#include "port_scanner/cli.hpp"