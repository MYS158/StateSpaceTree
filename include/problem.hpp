#pragma once

#include <optional>
#include <utility>
#include <vector>

/// Abstract interface for a state-space problem. Subclass per problem domain.
/// Weight must be default-constructible and support operator+= for weighted search.
template <typename State, typename Weight = double>
class Problem {
public:
    virtual ~Problem() = default;

    /// Returns the initial state from which search begins.
    virtual State initial_state() const = 0;

    /// Returns true if state satisfies the goal condition.
    virtual bool is_goal(const State& state) const = 0;

    /// Returns (successor state, optional edge cost) pairs reachable from state.
    virtual std::vector<std::pair<State, std::optional<Weight>>>
    successors(const State& state) const = 0;
};
