#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <vector>

/// A node in a state-space tree, templated on state type and edge weight type.
template <typename State, typename Weight = double>
class Node {
public:
    /// Constructs a root node with no parent and no edge cost.
    explicit Node(State state)
        : state_(std::move(state)), parent_(nullptr), depth_(0) {}

    /// Constructs a child node linked to a parent with an optional edge cost.
    Node(State state, Node* parent, std::optional<Weight> cost = std::nullopt)
        : state_(std::move(state)),
          parent_(parent),
          cost_(std::move(cost)),
          depth_(parent ? parent->depth_ + 1 : 0) {}

    /// Returns the state stored at this node.
    const State& state() const { return state_; }

    /// Returns a non-owning pointer to the parent, or nullptr if this is the root.
    Node* parent() const { return parent_; }

    /// Returns the edge cost from the parent to this node, if present.
    const std::optional<Weight>& cost() const { return cost_; }

    /// Returns the depth of this node (root = 0).
    std::size_t depth() const { return depth_; }

    /// Returns the children owned by this node.
    const std::vector<std::unique_ptr<Node>>& children() const { return children_; }

    /// Appends a child node and returns a non-owning pointer to it.
    Node* add_child(std::unique_ptr<Node> child) {
        children_.push_back(std::move(child));
        return children_.back().get();
    }

private:
    State state_;
    Node* parent_;
    std::optional<Weight> cost_;
    std::size_t depth_;
    std::vector<std::unique_ptr<Node>> children_;
};
