#pragma once

#include <optional>
#include <vector>
#include "node.hpp"
#include "problem.hpp"
#include "tree.hpp"

/// Abstract base for traversal strategies. Subclass to define custom or built-in strategies.
/// All strategies are interchangeable — the caller selects one at runtime without touching engine code.
template <typename State, typename Weight = double>
class SearchStrategy {
public:
    virtual ~SearchStrategy() = default;

    /// Searches tree for a goal node defined by problem.
    /// tree must be constructed with problem.initial_state() as root before calling.
    /// Returns path root→goal (inclusive) or nullopt if no solution exists.
    virtual std::optional<std::vector<Node<State, Weight>*>>
    solve(Tree<State, Weight>& tree, const Problem<State, Weight>& problem) = 0;
};
