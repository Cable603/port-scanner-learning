# C++ Port Scanner Learning Project

This directory contains the C++ learning project. The original Python `test.py` at the project root is separate and is left unchanged.

## Project goal

Build a command-line TCP connect scanner for WSL/Linux. It will accept one explicitly supplied hostname or IP address and a bounded port range, resolve the target, attempt TCP connections with a timeout, and summarize the outcomes.

Use it only against loopback, systems you own, or systems for which you have explicit authorization. The learning project is limited to ordinary TCP connection attempts. It does not include stealth, evasion, exploitation, credential testing, or denial-of-service behavior.

## Learning workflow

Read `../CPP_LEARNING_PLAN.md` for the single ordered session plan. We will cover one session at a time. Each assignment adds a small part of this program; the learner writes and connects the implementation.

The code is organized into public headers under `include/port_scanner/` and matching implementation files under `src/`. Headers document contracts and define only small value helpers or templates that need a visible definition. POSIX socket behavior and other substantial operations belong in `.cpp` files.

## Planned build

The `Makefile` is a commented placeholder until the build-system lesson. No build recipe or scanner implementation is supplied as part of this scaffold. The interfaces describe what each module will eventually provide.
