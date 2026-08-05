# StateSpaceTree — AI Context

C++17 generalized state-space tree engine. CMake build, STL-only, no third-party libraries.

## Directory Layout

```
include/        # Engine headers (templated — state type + optional weight)
src/            # Engine implementation
cli/            # Console interface — menu + CLI flags, isolated from engine
examples/
  nqueens/      # Backtracking example
  8puzzle/      # BFS/DFS example
  tsp/          # UCS weighted example
tests/          # Unit + integration tests
docs/           # Project documentation
.claude/agents/ # AI agent definitions
```

## Key Design Decisions

- **Strategy pattern for traversals:** abstract `SearchStrategy` base; BFS, DFS, backtracking, UCS built-in; programmers subclass for custom strategies — all interchangeable
- **Edge weights:** `std::optional<Weight>` — unweighted problems pass nothing; engine degrades gracefully
- **Engine templated** on state type and weight type — knows nothing about problem internals
- **Problem adapters** in `examples/` implement a common interface: initial state, goal test, successor function, optional edge cost
- **Path reconstruction:** returns ordered node list from root to goal; accumulates cumulative cost when weights present
- **ANSI console output:** tree structure and solution path rendered with color-coded nodes, edges, and solution path; Windows VT mode enabled via `SetConsoleMode` at startup
- **CLI layer** in `cli/` — interactive numbered menu when run with no args; `--problem` and `--strategy` flags for scripting; both modes produce identical output

## Build

```bash
cmake -B build
cmake --build build
```

## Test

```bash
ctest --test-dir build
```

For AddressSanitizer (GCC/Clang):

```bash
cmake -B build -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined"
cmake --build build && ctest --test-dir build
```

## Conventions

- C++17, `-Wall -Wextra -Wpedantic -Werror`, zero warnings on MSVC (`/W4 /WX`) and GCC
- One-line doc comment on every public class/function
- No raw owning pointers (`std::unique_ptr` / `std::shared_ptr`)
- Max line length: 100 characters
- Conventional Commits: `feat:` / `fix:` / `test:` / `docs:` / `refactor:`
- Branch naming: `feat/short-desc`, `fix/short-desc`, etc.
- Scrum workflow — see CONTRIBUTING.md

## Algorithms in Scope

| Algorithm | Weighted | Located |
|-----------|----------|---------|
| BFS | No | engine |
| DFS | No | engine |
| Backtracking | No | engine |
| UCS | Yes | engine |
| Custom (user-defined) | Optional | subclass `SearchStrategy` |

A* and greedy search are explicitly out of scope.

## Non-Goals

- No windowed GUI — console only; ANSI colors permitted (Windows VT mode enabled via `SetConsoleMode` at startup)
- No heuristic/informed search — A* and greedy are out of scope; UCS is allowed (no heuristic required)
- No third-party libraries
- No runtime plugin loading
