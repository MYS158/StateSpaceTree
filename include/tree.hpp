#pragma once

#include <algorithm>
#include <memory>
#include <optional>
#include <utility>
#include <vector>
#include "node.hpp"

/// A state-space tree that owns all nodes and provides expansion and path reconstruction.
template <typename State, typename Weight = double>
class Tree {
public:
    using NodeT = Node<State, Weight>;

    /// Constructs a tree with a single root node holding the given state.
    explicit Tree(State root_state)
        : root_(std::make_unique<NodeT>(std::move(root_state))) {}

    /// Returns a non-owning pointer to the root node.
    NodeT* root() const { return root_.get(); }

    /// Expands a node by attaching children for each (state, optional cost) successor.
    std::vector<NodeT*> expand(NodeT* node,
                               std::vector<std::pair<State, std::optional<Weight>>> successors) {
        std::vector<NodeT*> children;
        children.reserve(successors.size());
        for (auto& [state, cost] : successors) {
            children.push_back(
                node->add_child(std::make_unique<NodeT>(std::move(state), node, std::move(cost)))
            );
        }
        return children;
    }

    /// Returns the path from the root to the given node, inclusive.
    std::vector<NodeT*> path_to(NodeT* node) const {
        std::vector<NodeT*> path;
        NodeT* current = node;
        while (current != nullptr) {
            path.push_back(current);
            current = current->parent();
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    /// Returns cumulative edge cost from root to node; nullopt if any edge lacks a cost.
    std::optional<Weight> cost_to(NodeT* node) const {
        Weight total{};
        NodeT* current = node;
        while (current != nullptr && current->parent() != nullptr) {
            if (!current->cost().has_value()) return std::nullopt;
            total += *current->cost();
            current = current->parent();
        }
        return total;
    }

private:
    std::unique_ptr<NodeT> root_;
};
