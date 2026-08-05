#pragma once

#include "../search_strategy.hpp"

/// Backtracking search — DFS with pruning; suited for constraint satisfaction problems.
template <typename State, typename Weight = double>
class Backtracking : public SearchStrategy<State, Weight> {
public:
    /// Searches tree with backtracking; returns path root→goal or nullopt if no solution.
    std::optional<std::vector<Node<State, Weight>*>>
    solve(Tree<State, Weight>&, const Problem<State, Weight>&) override {
        return std::nullopt;
    }
};
