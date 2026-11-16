// WorkQueue ADT implementation placeholder (Sessions 20 and 21).
//
// Implement the bounded, thread-safe operations declared in work_queue.hpp.
// Define the locking boundaries for push/pop/size/close, wait on predicates,
// notify the appropriate condition variable after state changes, and make
// close idempotent so blocked workers can drain accepted work and exit.
//
// Keep synchronization inside this class. Do not launch threads here; worker
// creation and joining belong to the scan-engine lesson.
#include "port_scanner/work_queue.hpp"