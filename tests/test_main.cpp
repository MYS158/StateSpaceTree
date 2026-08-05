#include <cassert>
#include <memory>
#include <optional>
#include <string>
#include "node.hpp"

int main() {
    // Root node — no parent, no cost, depth 0
    Node<int> root(42);
    assert(root.state() == 42);
    assert(root.parent() == nullptr);
    assert(root.depth() == 0);
    assert(!root.cost().has_value());
    assert(root.children().empty());

    // Child node — linked to root with edge cost
    Node<int>* child = root.add_child(
        std::make_unique<Node<int>>(7, &root, std::optional<double>{1.5})
    );
    assert(child->state() == 7);
    assert(child->parent() == &root);
    assert(child->depth() == 1);
    assert(child->cost().has_value());
    assert(*child->cost() == 1.5);
    assert(root.children().size() == 1);

    // Multiple children
    root.add_child(std::make_unique<Node<int>>(8, &root));
    root.add_child(std::make_unique<Node<int>>(9, &root));
    assert(root.children().size() == 3);

    // Depth chain — grandchild depth = 2
    Node<int>* grandchild = child->add_child(
        std::make_unique<Node<int>>(99, child)
    );
    assert(grandchild->depth() == 2);
    assert(grandchild->parent() == child);
    assert(!grandchild->cost().has_value());

    // Non-trivial state type
    Node<std::string> str_root("start");
    assert(str_root.state() == "start");
    Node<std::string>* str_child = str_root.add_child(
        std::make_unique<Node<std::string>>("goal", &str_root, std::optional<double>{3.0})
    );
    assert(str_child->state() == "goal");
    assert(str_child->depth() == 1);

    return 0;
}
