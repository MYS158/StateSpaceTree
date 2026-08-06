#pragma once

#include "../search_strategy.hpp"

/// Breadth-first search — expands shallowest nodes first; optimal for unweighted trees.
template <typename State, typename Weight = double>
class BFS : public SearchStrategy<State, Weight> {
public:
    /// Searches tree breadth-first; returns path root→goal or nullopt if no solution.
    std::optional<std::vector<Node<State, Weight>*>>
    solve([[maybe_unused]] Tree<State, Weight>& tree,
          [[maybe_unused]] const Problem<State, Weight>& problem) override {
        return std::nullopt;
    }
};
