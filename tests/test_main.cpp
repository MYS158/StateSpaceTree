#include <cassert>
#include <memory>
#include <optional>
#include "node.hpp"

int main() {
    // Root node — no parent, no cost, depth 0
    Node<int> root(42);
    assert(root.state() == 42);
    assert(root.parent() == nullptr);
    assert(root.depth() == 0);
    assert(!root.cost().has_value());
    assert(root.children().empty());

    // Child node — linked to root, with edge cost
    Node<int>* child = root.add_child(
        std::make_unique<Node<int>>(7, &root, std::optional<double>{1.5})
    );
    assert(child->state() == 7);
    assert(child->parent() == &root);
    assert(child->depth() == 1);
    assert(child->cost().has_value());
    assert(*child->cost() == 1.5);
    assert(root.children().size() == 1);

    return 0;
}
