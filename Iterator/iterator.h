#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <experimental/coroutine>
#include <experimental/generator>

using namespace std;

#include "../Iterator/recursive_generator.h"


template<typename T>
struct BinaryTree;

// todo: 引用父书代替引用整棵树
template<typename T>
struct Node
{
    T value_ = T();
    Node<T>* left_ = nullptr;
    Node<T>* right_ = nullptr;
    Node<T>* parent_ = nullptr;
    BinaryTree<T>* tree_ = nullptr;

    explicit Node(const T& value) : value_(value) {}

    // 添加左右节点，引用树
    Node(const T& value, Node<T>* const left, Node<T>* const right)
        : value_(value),
        left_(left),
        right_(right)
    {
        this->left_->tree_ = this->right_->tree_ = tree_;
        this->left_->parent_ = this->right_->parent_ = this;
    }

    ~Node()
    {
        if (left_) delete left_;
        if (right_) delete right_;
    }

    void set_tree(BinaryTree<T>* t)
    {
        tree_ = t;
        if (left_) left_->set_tree(t);
        if (right_) right_->set_tree(t);
    }
};


template<typename T>
struct BinaryTree
{
    Node<T>* root_ = nullptr;

    explicit BinaryTree(Node<T>* const root) : root_{root}, pre_order_{*this}
    {
        root_->set_tree(this);
    }

    ~BinaryTree()
    {
        if (root_)
            delete root_;
    }

    template<typename U>
    struct PreOrderIterator
    {
        Node<U>* current_;
        explicit PreOrderIterator(Node<U>* current) : current_(current) {}

        bool operator !=(const PreOrderIterator<U>& other)
        {
            return current_ != other.current_;
        }

        Node<U>& operator *()
        {
            return *current_;
        }

        // 什么玩意？
        PreOrderIterator<U>& operator ++()
        {
            if (current_->right_) {
                current_ = current_->right_;
                while (current_->left_)
                    current_ = current_->left_;
            } else {
                Node<T>* p = current_->parent_;
                while (p && current_ == p->right_) {
                    current_ = p;
                    p = p->parent_;
                }
                current_ = p;
            }
            return *this;
        }
    };

    typedef PreOrderIterator<T> iterator;

    iterator end()
    {
        return iterator{nullptr};
    }

    // 最左边
    iterator begin()
    {
        Node<T>* n = root_;

        if (n) {
            while (n->left_) {
                n = n->left_;
            }
        }
        return iterator{n};
    }

    class pre_order_traversal
    {
        BinaryTree<T>& tree;
    public:
        pre_order_traversal(BinaryTree<T>& tree) : tree{tree} {}
        iterator begin() { return tree.begin(); }
        iterator end() { return tree.end(); }
    } pre_order_;

    experimental::generator<Node<T>*> post_order()
    {
        return post_order_impl(root_);
    }

private:
    // or use a recursive_generator
    experimental::generator<Node<T>*> post_order_impl(Node<T>* node)
    {
        if (node) {
            for (auto x : post_order_impl(node->left_))
                co_yield x;
            for (auto y : post_order_impl(node->right_))
                co_yield y;
            co_yield node;
        }
    }

};


void test()
{
    //         me
    //        /  \
    //   mother   father
    //      / \
    //   m'm   m'f

    BinaryTree<string> family{
      new Node<string>{"me",
        new Node<string>{"mother",
          new Node<string>{"mother's mother"},
          new Node<string>{"mother's father"}
        },
        new Node<string>{"father"}
      }
    };

    for (auto it = family.begin(); it != family.end(); ++it) {
        cout << (*it).value_ << "\n";
    }
    
    std::cout << "-------------------------------" << std::endl;

    for (const auto& it : family.pre_order_) {
        cout << it.value_ << "\n";
    }

    std::cout << "-------------------------------" << std::endl;

    // use coroutines (yields pointers!)
    // postorder: m'm, m'f m f me
    for (auto it : family.post_order()) {
        cout << it->value_ << endl;
    }
}