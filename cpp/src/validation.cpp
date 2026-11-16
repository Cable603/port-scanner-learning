// Input validation placeholder (Sessions 4 and 10).
//
// Implement validate_options from validation.hpp here. Convert the raw numeric
// strings without accepting partial parses or overflowing, then enforce:
//   - assigned port range and increasing inclusive bounds
//   - positive, bounded timeout
//   - positive worker count within the project cap
//   - total-probe count within the configured maximum
//
// Return a categorized Error before any DNS lookup or socket operation. Keep
// parsing policy in the CLI and address classification in target_parser.cpp.
#include "port_scanner/validation.hpp"