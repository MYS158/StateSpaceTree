# Project Goal

Develop a generalized C++ library for state-space tree problems, with a clear separation between the generic tree engine and problem-specific implementations.

## Technical Constraints

- **Standard:** C++17
- **Build system:** CMake
- **Dependencies:** STL only — no third-party libraries

## Core Capabilities

The engine must support:

- Tree construction and node expansion
- Pluggable traversal interface — built-ins (BFS, DFS, backtracking, UCS) and programmer-defined strategies implement the same abstract interface and are interchangeable
- Optional edge/node weights — engine treats weight as `std::optional`; unweighted problems pass nothing
- Path reconstruction from goal node to root, with cumulative cost when weights present
- Text-based visualization of tree structure and solution path, with ANSI color highlighting for nodes, edges, and solution path
- Console interface: interactive numbered menu when run with no args; CLI flags (`--problem`, `--strategy`) for scripting — both modes produce identical output
- Memory-safe node lifecycle (RAII, no raw owning pointers)

## Architecture

- Generic tree engine in `include/` and `src/` — templated on state type and optional weight type
- Problem adapters in `examples/` — each implements a common interface (initial state, goal test, successor function, optional edge cost)
- Clean interface between engine and problem domain: engine calls problem functions, knows nothing about problem internals
- Traversal strategies isolated behind an abstract base (`Traversal` or `SearchStrategy`) — programmers subclass to define custom strategies without touching engine internals
- Console interface layer in `cli/` — parses args, drives menu, delegates to engine; isolated from engine and problem adapters

## Example Problems (Course Requirements)

| Problem | Algorithm | Located in |
|---------|-----------|------------|
| N-Queens | Backtracking | `examples/nqueens/` |
| 8-Puzzle | BFS / DFS | `examples/8puzzle/` |
| TSP (Traveling Salesman) | UCS | `examples/tsp/` |

## Testing

- Unit tests per engine component (node, tree, each search strategy)
- Integration test per example problem (known input → known solution path)
- Tests live in `tests/`, built via CMake target

## Non-Goals

- No windowed GUI — console only; ANSI colors permitted (Windows VT mode enabled via `SetConsoleMode` at startup)
- No heuristic/informed search (A*, greedy) — out of scope (UCS is allowed; A* requires a heuristic and is not)
- No external solver libraries
- No runtime plugin loading

## Definition of Done

- All search strategies produce correct, reproducible paths on both example problems
- No memory errors under AddressSanitizer
- Each public class/function has a single-line doc comment
- `cmake --build` succeeds clean on MSVC and GCC with `-Wall -Wextra`
