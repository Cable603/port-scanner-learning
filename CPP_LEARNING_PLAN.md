# Port Scanner Project Roadmap: Stages and Sessions

## Purpose and project outcome

This file is the single course roadmap and the source of truth for lesson order, session timing, and assignment progression. We will work one session at a time. At the end of each lesson, the learner implements that session's assignment in the project; the next lesson begins from the completed work and connects it to the next module.

The cumulative project is a small, documented C++20 command-line TCP connect scanner for Linux/WSL. It accepts one explicitly supplied hostname or IP address and a bounded port range, attempts TCP connections with conservative timeouts and resource limits, and reports open, refused, timed-out, or other outcomes. It is a learning project, not a production security tool.

Use the scanner only against loopback, systems you own, or systems for which you have explicit authorization. The project excludes stealth, evasion, exploitation, credential testing, and denial-of-service behavior. It will not scan arbitrary ranges or run unbounded probes.

## Working rhythm

Each session follows the same loop:

1. Review the relevant ideas using the current code and module contract.
2. Discuss design choices and trace how data will travel between modules.
3. Implement only that session's assignment. The learner writes the code; coaching explains the next function or small group of functions, what each contract means, and how to connect modules.
4. Build or inspect behavior only when the lesson reaches the build/debug stage. Verification activities are introduced in their own lessons.
5. Record what changed and any questions before moving on.

Scaffold files provide commented contracts. They are intentionally incomplete until their assigned lesson. Header definitions are reserved for templates and small value-only operations where the definition must be visible to callers; platform calls and substantial behavior belong in source files.
Make no
## Project boundaries

- Platform: Linux/WSL with POSIX sockets.
- Language target: C++20, allowing later use of standard threading facilities.
- Network operation: TCP connect attempts only; no packet crafting or raw sockets.
- Target: one user-supplied hostname or address, resolved to its applicable endpoints.
- Scope: a validated, bounded port interval, maximum probe count, timeout, and later a small configured worker limit.
- Output: a clear summary and one outcome per attempted endpoint/port.
- Error policy: reject invalid input before network activity; preserve useful error categories and system error details.
- Data structures: standard-library storage behind project ADTs where that abstraction teaches a useful contract.

## Course map

Estimated lesson time is about 29–32 hours across 23 sessions. Each assignment is expected to take another 30–90 minutes, with larger integration tasks sometimes taking longer. The pace is flexible: a session is complete when its assignment and explanation are understood, not when a calendar estimate expires.

| Stage | Sessions | Focus | Project checkpoint |
|---|---:|---|---|
| A. C++ and project foundations | 1–4 | Toolchain orientation, fundamentals skim, functions, translation units, domain types | Buildable project shape and explicit data contracts |
| B. ADTs, STL, and resource management | 5–9 | Classes, ADTs, containers, algorithms, templates, RAII, errors | Safe in-memory model and validated scan options |
| C. CLI and build workflow | 10–12 | Makefile, compiler/linker, debugging, command-line interface | User can request a validated scan |
| D. Network and socket core | 13–17 | Name resolution, POSIX descriptors, TCP connect, timeouts, sequential orchestration | First bounded end-to-end scan |
| E. Results, verification, and concurrency | 18–22 | Results ADT, reporting, boundary checks, queue/threading, integration limits | Reliable bounded scanner with controlled parallel work |
| F. Finish and explain | 23 | Final integration and review | Documented project and learner-led walkthrough |

## Session-by-session plan and assignments

### Stage A — C++ and project foundations

#### Session 1 — Project orientation and development setup (60 minutes)
**Learn:** project goal and safety boundary; source tree; compiler, linker, executable, and editor roles; compile/run/debug as separate steps. Review the scaffold without filling in future modules.
**Assignment (30–45 minutes):** inspect the folder tree, annotate cpp/README.md with local compiler/editor details and project scope, and create a short checklist of what a successful final run should display. Do not implement networking yet.

#### Session 2 — C++ fundamentals skim (75 minutes)
**Learn:** declarations, built-in types, initialization, expressions, conditions, loops, std::string, std::vector, input/output, and reading compiler diagnostics. Focus on enough syntax to work on this project rather than a broad language survey.
**Assignment (45–60 minutes):** implement a tiny temporary or project-local practice routine that prints a bounded sequence of sample port numbers and labels; explain the loop bounds and types in comments. Keep it separate from scanner behavior so it can be removed after the lesson.

#### Session 3 — Functions, headers, source files, and the ODR (75 minutes)
**Learn:** function declarations/definitions, parameters, return values, scope, include guards or pragma once, translation units, linking, and the One Definition Rule. Review the scaffold's header/source policy.
**Assignment (45–75 minutes):** implement one small pure helper in its assigned .cpp file from its header contract, include and call it from a second translation unit, and record why its declaration belongs in the header while its definition belongs in the source file.

#### Session 4 — Values, enums, and domain modeling (75 minutes)
**Learn:** const, references, std::optional, scoped enums, aggregate/value types, invariants, and choosing names/types that make invalid states harder to express.
**Assignment (45–75 minutes):** define and implement the simple port-range and scan-option value rules in types.hpp and validation.cpp according to their comments. Include boundary examples in a written checklist.

### Stage B — ADTs, STL, and resource management

#### Session 5 — Classes and encapsulation (90 minutes)
**Learn:** constructors, access control, member functions, const-correctness, invariants, and the difference between a class's interface and representation.
**Assignment (60–90 minutes):** implement the small value-oriented class or struct contracts from types.hpp. Keep state private when callers should not mutate it directly; add concise comments that explain each invariant.

#### Session 6 — Abstract data types (ADTs) (90 minutes)
**Learn:** an ADT is defined by operations and guarantees, not by its storage container; public/private boundaries; designing collection operations around actual callers.
**Assignment (60–90 minutes):** implement the ScanResults interface so the rest of the program can add, count, and inspect results without depending on the chosen container. Document the complexity of its main operations.

#### Session 7 — STL containers and complexity (90 minutes)
**Learn:** std::vector, std::array, std::map/std::unordered_map, iterators, invalidation, and practical Big-O reasoning. Select a container from required operations and bounded input size.
**Assignment (45–75 minutes):** choose and document the initial storage for parsed ports and scan results. Add only the operations required by current interfaces; explain why a custom container is not useful here.

#### Session 8 — Algorithms, templates, and inline definitions (75 minutes)
**Learn:** standard algorithms, iterator ranges, callable predicates, simple templates, constexpr, and when a definition must be in a header. Discuss compile-time visibility and multiple-definition risks.
**Assignment (45–75 minutes):** implement one small header-only value check or template already declared in the scaffold, and use a standard algorithm for one in-memory operation. Add a note explaining why this definition is safe in a header.

#### Session 9 — Lifetime, ownership, and RAII (90 minutes)
**Learn:** object lifetime, references versus pointers, ownership, RAII, destructors, move-only types, std::unique_ptr, and exception-safe cleanup. Relate descriptor ownership to ordinary resource ownership.
**Assignment (60–90 minutes):** implement the SocketHandle ownership interface, including its move operations and cleanup contract, without adding socket creation or connection behavior yet. Explain how copying is prevented and how ownership transfers.

### Stage C — CLI and build workflow

#### Session 10 — Errors, validation, and debugging workflow (90 minutes)
**Learn:** input validation boundaries, error categories, exceptions versus explicit result values, preserving system error details, debugger breakpoints, and reading a failing call stack.
**Assignment (60–90 minutes):** implement Result<T>/error plumbing assigned to this lesson and connect validation failures to useful messages. Write a manual input/error checklist; do not start network activity for invalid options.

#### Session 11 — Makefile, compiler, and linker (90 minutes)
**Learn:** compiler flags, include paths, compile versus link, object files, Make targets, dependencies, debug symbols, and incremental builds.
**Assignment (60–90 minutes):** author the Makefile from the comments-only placeholder. Add a debug build target and a normal executable target, list the source files explicitly or through a clear source list, and write down how a missing definition differs from a compile error. Build the currently implemented modules.

#### Session 12 — Command-line interface (75 minutes)
**Learn:** argc/argv, command syntax, usage/help output, parsing versus validation, user-facing errors, and keeping main small.
**Assignment (45–75 minutes):** implement cli.cpp and the minimal main/application connection needed to accept a target, starting port, ending port, and documented timeout. Reject missing, malformed, and extra arguments before any resolver or socket call.

### Stage D — Network and socket core

#### Session 13 — Target parsing and numeric addresses (75 minutes)
**Learn:** distinguish raw user text from validated target data; IPv4/IPv6 textual forms; avoid hand-written address parsing when the platform provides appropriate routines.
**Assignment (45–75 minutes):** implement target_parser.cpp to convert the CLI target into a clear domain representation while keeping hostname resolution in the resolver module. Add examples to the manual checklist.

#### Session 14 — DNS and endpoint resolution (90 minutes)
**Learn:** hostname resolution, getaddrinfo, address families, service/port fields, returned linked lists, error reporting, and freeing resolver-owned memory safely.
**Assignment (60–90 minutes):** implement resolver.cpp to produce owned numeric endpoints for the one requested target. Handle resolver failure cleanly and do not probe during this assignment.

#### Session 15 — POSIX sockets and descriptor lifecycle (90 minutes)
**Learn:** socket descriptors, address structures, socket, connect, close, errno, blocking behavior, and how RAII makes cleanup reliable. Trace a connection attempt on paper first.
**Assignment (60–90 minutes):** implement the synchronous TCP probe path for one endpoint and one port, using SocketHandle. Keep the attempt outcome distinct from a whole-application setup error.

#### Session 16 — Timeouts and connection outcomes (90 minutes)
**Learn:** why a blocking connect may exceed a desired timeout; nonblocking sockets, poll/select, completion checks, timeout conversion, and platform error interpretation.
**Assignment (60–90 minutes):** add a bounded timeout to the single-probe interface and distinguish connected, refused, timed-out, and other-error outcomes. Verify against loopback services you control.

#### Session 17 — Sequential scan engine and first integration (90 minutes)
**Learn:** orchestration, dependency boundaries, nested endpoint/port iteration, probe count limits, cancellation/early failure policy, and keeping the application layer separate from socket mechanics.
**Assignment (60–90 minutes):** implement a sequential scan_engine.cpp that uses the resolver, validates the maximum work, invokes the probe for each endpoint/port, and stores outcomes. Connect the application flow end to end with a deliberately small port range.

### Stage E — Results, verification, and concurrency

#### Session 18 — Result presentation (75 minutes)
**Learn:** separating stored results from presentation; stable ordering; useful summaries; output streams; avoiding claims that connection state identifies a particular service.
**Assignment (45–75 minutes):** implement the report module to print the target, attempted endpoint/port, outcome, and a compact summary. Keep formatting out of the scanner and socket modules.

#### Session 19 — Verification and edge-case review (90 minutes)
**Learn:** unit versus integration checks, deterministic tests, loopback fixtures, boundary values, failure injection concepts, and regression checks. Verification is introduced here so the early lessons can focus on concepts and interfaces.
**Assignment (60–90 minutes):** add focused checks for range boundaries, invalid CLI values, result counts, and loopback outcomes. Record expected versus observed behavior and fix defects in the corresponding modules.

#### Session 20 — Concurrency foundations and work-queue ADT (90 minutes)
**Learn:** threads, data races, mutexes, condition variables, queue state, worker lifetime, std::jthread, and why synchronization belongs behind a narrow interface. Discuss bounded queues and shutdown behavior.
**Assignment (60–90 minutes):** implement and verify the WorkQueue ADT independently of network calls. Define how workers learn that no more work remains and how queue capacity is bounded.

#### Session 21 — Bounded worker pool (90 minutes)
**Learn:** worker-pool responsibilities, shared result ownership, synchronization boundaries, exception propagation, limiting concurrency, and avoiding one thread per port.
**Assignment (60–90 minutes):** add a small configurable worker limit to the scan engine and distribute probe jobs through the queue. Ensure each result is recorded exactly once and cleanup joins all workers.

#### Session 22 — Network integration, limits, and robustness (90 minutes)
**Learn:** end-to-end error flow, DNS returning multiple endpoints, IPv4/IPv6 handling, timeout and concurrency interactions, resource limits, repeatable output, and safe behavior under partial failures.
**Assignment (60–90 minutes):** integrate the complete pipeline, enforce conservative maximum-port, timeout, and worker limits, and exercise authorized loopback/owned-host cases. Update architecture notes for any justified design changes.

### Stage F — Finish and explain

#### Session 23 — Final review and learner-led walkthrough (75 minutes)
**Learn:** trace a CLI request through parsing, validation, resolution, scan scheduling, socket ownership, results, and reporting; review tradeoffs and remaining limitations.
**Assignment (45–90 minutes):** finish the README with build/use instructions, examples limited to authorized targets, known limitations, and the module map. Then give a short walkthrough explaining one function you implemented, its contract, and how ownership/error handling flows through it.

## Completion checklist

The project is complete when the learner can:

- Explain the data flow and responsibility of each module.
- Build the program from the documented Makefile and diagnose a simple compile/link error.
- Parse and validate a single target, bounded port interval, timeout, and worker limit before network activity.
- Resolve a hostname/address and own the returned endpoint data safely.
- Perform bounded TCP connect attempts and report their outcomes accurately.
- Store and report results through the results ADT.
- Run a bounded worker pool without leaking descriptors, losing results, or exceeding configured limits.
- Describe the ethical-use boundary, design tradeoffs, and known limitations.

## Progress tracking

After each lesson, record the date, assignment status, files changed, concepts to revisit, and the next session number here or in a short progress note. Do not skip ahead: each later assignment depends on earlier contracts and behavior.
