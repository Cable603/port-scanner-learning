# Architecture and data flow

## Scope

The program is a small POSIX TCP connect scanner for Linux/WSL. It examines one explicitly supplied host and a bounded port range. It reports whether a TCP connection succeeded, was refused, timed out, or failed for another reason. A result describes the connection attempt; it does not identify the software behind a port.

Only scan loopback, systems you own, or systems for which you have explicit authorization. The application will keep conservative limits and will not add stealth, evasion, exploitation, credential testing, or denial-of-service features.

## Module flow

`main.cpp` forwards the process arguments to the application boundary. The application asks the CLI module to parse them, then validates the resulting options before performing network work.

The resolver converts the host name or address into one or more numeric endpoints. The scan engine combines those endpoints with the validated port range. For each endpoint and port it asks the TCP probe module to perform one bounded connection attempt through the RAII socket handle. The engine gathers each outcome in the results ADT. The report module formats the final data for the user.

`main -> application -> CLI and validation -> resolver -> scan engine -> TCP probe and socket handle -> results -> report`

## Responsibility boundaries

- `types.hpp` owns simple domain values: port ranges, scan options, and probe outcomes.
- `target_parser.hpp` and `validation.hpp` separate reading strings from enforcing project rules.
- `resolver.hpp` owns hostname and address resolution. It does not probe ports.
- `socket_handle.hpp` owns descriptor lifetime. It does not decide scan policy.
- `tcp_probe.hpp` describes one TCP connection attempt and its timeout.
- `scan_engine.hpp` coordinates a bounded sequence of probes; concurrency is added only in its later lesson.
- `scan_results.hpp` offers an ADT so reporting does not depend on the collection representation.
- `report.hpp` converts stored results to output; it does not open sockets.

## Error path

Invalid command-line input is reported before DNS or socket work starts. Resolution and socket failures retain an error category and, when relevant, the POSIX system error code. A failed probe should become a result when it is a normal scan outcome, such as refusal or timeout; setup failures that prevent the whole scan should be returned as an application-level error. The lessons will refine this distinction as the implementation grows.

## Data structures

A `std::vector` is the initial representation for a bounded port list and results because it is simple to traverse and sort. The `ScanResults` ADT hides that choice. The later worker queue is a queue abstraction around standard-library storage, introduced to teach ADTs and synchronization. We will choose each structure from the operations the project actually needs rather than implementing containers for their own sake.

## Header and source policy

Headers declare public interfaces and include only the types needed to describe those interfaces. Small value-only checks and templates may be defined in headers when their definitions must be visible to callers. Non-template parsing, DNS, socket, scanning, and reporting behavior belongs in `.cpp` files. This keeps platform details private, reduces unnecessary recompilation, and avoids multiple-definition problems.
