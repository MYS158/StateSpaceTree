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

- **Strategy pattern for traversals:** abstract `SearchStrategy` base; BFS, DFS, backtracking, UCS built-in; programmers subclass for custom strategies
- **Edge weights:** `std::optional` — unweighted problems pass nothing; engine degrades gracefully
- **Engine is templated** on state type and optional weight type — knows nothing about problem internals
- **Problem adapters** in `examples/` implement a common interface: initial state, goal test, successor function, optional edge cost
- **CLI layer** in `cli/` owns menu and arg parsing; never touches engine internals directly

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

- C++17, `-Wall -Wextra`, zero warnings on MSVC and GCC
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

- No GUI — console only (ANSI colors permitted)
- No A* / greedy (heuristic-based) search
- No third-party libraries
- No runtime plugin loading
