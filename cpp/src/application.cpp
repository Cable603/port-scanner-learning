// Application orchestration placeholder.
//
// Session 12 introduces the application boundary. Later lessons will connect:
// argv parsing -> option validation -> target parsing -> scan engine -> report.
// Keep the program entry point thin and let each module own its stated contract.
//
// The implementation is deliberately absent. Do not put CLI parsing, resolver
// calls, socket logic, or output formatting here; add them during their lesson.
#include "port_scanner/application.hpp"