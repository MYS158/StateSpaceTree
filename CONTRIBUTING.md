# Contributing

## Workflow: Scrum

- **Sprint length:** 1 week
- **Backlog:** GitHub Issues — labels: `feat`, `fix`, `test`, `docs`, `refactor`
- **Sprint board:** GitHub Projects — columns: Backlog → In Progress → In Review → Done
- **Sprint planning:** open a milestone per sprint; assign issues; write sprint goal in milestone description
- **Sprint review:** close milestone; tag a release if a deliverable shipped

## Branches

| Prefix | Use |
|--------|-----|
| `feat/` | New feature |
| `fix/` | Bug fix |
| `test/` | Tests only |
| `docs/` | Documentation |
| `refactor/` | Refactor — no behavior change |

Always branch off `main`. Name: `feat/short-description`.

## Commits

Conventional Commits:

```
feat: add BFS strategy
fix: correct UCS cost comparison
test: add N-Queens integration test
docs: update GOAL.md with weighted support
refactor: extract node expansion into helper
```

Subject ≤ 50 chars. Body only when the "why" is not in the diff.

## Pull Requests

- One PR per issue
- Link issue: `Closes #N` in PR body
- At least one review before merge (human or `/code-review`)
- CI must pass: build + tests + ASan
- Squash-merge to keep `main` history linear

## Definition of Done

A task is done when:

- [ ] Compiles clean on MSVC and GCC (`-Wall -Wextra`, zero warnings)
- [ ] All tests pass
- [ ] No AddressSanitizer errors
- [ ] PR reviewed and merged
- [ ] Issue closed

## Code Style

- Standard: C++17
- Every public class and function has a one-line doc comment
- No raw owning pointers — use `std::unique_ptr` / `std::shared_ptr`
- Max line length: 100 characters
- STL only — no third-party libraries
