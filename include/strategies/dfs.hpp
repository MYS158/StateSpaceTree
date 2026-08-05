#pragma once

#include "../search_strategy.hpp"

/// Depth-first search — expands deepest nodes first; not guaranteed optimal.
template <typename State, typename Weight = double>
class DFS : public SearchStrategy<State, Weight> {
public:
    /// Searches tree depth-first; returns path root→goal or nullopt if no solution.
    std::optional<std::vector<Node<State, Weight>*>>
    solve(Tree<State, Weight>&, const Problem<State, Weight>&) override {
        return std::nullopt;
    }
};
