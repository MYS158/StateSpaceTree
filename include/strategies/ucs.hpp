#pragma once

#include "../search_strategy.hpp"

/// Uniform-cost search — expands lowest-cost node first; optimal for weighted trees.
template <typename State, typename Weight = double>
class UCS : public SearchStrategy<State, Weight> {
public:
    /// Searches tree by cumulative cost; returns minimum-cost path root→goal or nullopt.
    std::optional<std::vector<Node<State, Weight>*>>
    solve([[maybe_unused]] Tree<State, Weight>& tree,
          [[maybe_unused]] const Problem<State, Weight>& problem) override {
        return std::nullopt;
    }
};
