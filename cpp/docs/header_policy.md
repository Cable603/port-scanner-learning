# Header and source implementation policy

## Guiding rule

Headers describe contracts. Source files own platform calls and substantial behavior. A definition belongs in a header only when callers need to see it to compile a template, or when it is a tiny, stable value-only operation whose body is part of the type's contract.

This split supports incremental compilation, keeps POSIX details out of most interfaces, avoids accidental multiple definitions, and gives each lesson a focused implementation target.

## Decisions for this project

| Item | Location | Reason |
|---|---|---|
| Public function and class declarations | Header | Other modules need a stable contract to compile against. |
| Include guard using pragma once | Header | Keeps repeated inclusion harmless in this learning project and is supported by the chosen toolchain. |
| Simple constexpr checks on PortRange | Header, if they remain tiny | A caller may evaluate these value-only checks at compile time; the body has no I/O or platform dependency. |
| Generic Result<T> operations | Header | A template definition generally must be visible where callers instantiate it. Keep the template minimal and documented. |
| SocketHandle valid/native_handle accessors | Header, if they are simple field reads | They do not perform resource operations. Construction, destruction, move, and close behavior remain in socket_handle.cpp. |
| DNS, address conversion, POSIX socket calls, timeout polling | Source | These use operating-system APIs and should not leak platform implementation details into unrelated modules. |
| CLI parsing, validation rules with nontrivial diagnostics, scan orchestration, formatting | Source | These are substantive behaviors that are easier to teach, debug, and change when compiled once. |
| WorkQueue synchronization | Source | Mutex, condition-variable, queue state transitions, and shutdown behavior are implementation details of the ADT. |
| Standard-library container representation | Private class members or private implementation | Callers should use the ADT operations, not rely on vector or queue representation. |

## One Definition Rule and inline behavior

A non-template function defined in a header can be included by many translation units. If those definitions are not permitted inline definitions, the linker may report duplicate symbols. Template definitions need to be available at the point of instantiation, which is why their implementation commonly stays in the header or in an included implementation file.

A small function declared inline in a class definition is implicitly inline. A standalone function defined in a header should be explicitly marked inline or constexpr as appropriate. Do not mark a substantial function inline just to make a linker error disappear. Move its definition into one source file instead.

## Header hygiene

- Each header starts with a short purpose comment and pragma once.
- Include the standard or project headers needed by the declarations in that header; do not depend on another file including them first.
- Prefer forward declarations where they are sufficient and safe.
- Keep includes minimal to reduce rebuilds and coupling.
- Use the port_scanner namespace consistently.
- Use const references for read-only complex inputs where that matches the lifetime contract; pass small scalar values such as ports by value.
- Avoid using directives in headers because they affect every file that includes the header.
- Document ownership, error behavior, bounds, and thread-safety where callers need those guarantees.
- Do not put using namespace std in a header.
- Avoid exposing raw file descriptors or sockaddr layout unless a caller genuinely needs those details.

## Learning sequence and implementation ownership

The learner implements each function in the session where it is assigned in CPP_LEARNING_PLAN.md. A declared contract is not permission to implement future modules early. During a lesson, first trace callers and data flow, then implement the narrowest function that advances the current milestone, compile or verify only when the roadmap reaches that activity, and record decisions that change the architecture.

The scaffold intentionally contains no network implementation, Makefile recipe, or hidden helper behavior. Comments should explain intent and contracts without quietly supplying the implementation.
