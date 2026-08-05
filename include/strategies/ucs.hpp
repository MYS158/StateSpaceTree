#pragma once

#include "../search_strategy.hpp"

/// Uniform-cost search — expands lowest-cost node first; optimal for weighted trees.
template <typename State, typename Weight = double>
class UCS : public SearchStrategy<State, Weight> {
public:
    /// Searches tree by cumulative cost; returns minimum-cost path root→goal or nullopt.
    std::optional<std::vector<Node<State, Weight>*>>
    solve(Tree<State, Weight>&, const Problem<State, Weight>&) override {
        return std::nullopt;
    }
};
