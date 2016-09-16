//
//  Resource free tree serialization (DFS)
//  given a node has a single node * storage
//

#include <stdio.h>
#include <cassert>

struct node {
    node * left = nullptr;
    node * right = nullptr;
    node * next = nullptr; // extra node for stack
    int data;
    node(int data, node * left = nullptr, node * right = nullptr) :
        data(data), left(left), right(right) {}
    void print() {
        printf("%d ", data);
    }
};

//  reusing a node right pointer from the parent node
//  to store a null node in the stack
static node * null_node = reinterpret_cast<node*>(1);

struct stack {
    node * top = nullptr;
    void push(node * n) {
        assert( n != nullptr );
        if (top == nullptr) {
            top = n;
            top->next = nullptr;
        } else {
            auto old_top = top;
            top = n;
            top->next = old_top;
        }
    }
    node * pop() {
        assert( top != nullptr );
        auto n = top;
        top = top->next;
        return n;
    }
    bool empty() {
        return top == nullptr;
    }
};

void print_null()
{
    printf(". ");
}

void print_tree(node * root)
{
    if (nullptr == root) {
        print_null();
        printf("\n");
        return;
    }
    stack s;
    s.push( root );
    while (!s.empty()) {
        auto n = s.pop();
        if (null_node == n->right) {
            print_null();
            n->right = nullptr;
        } else {
            n->print();
            if (nullptr == n->right) {
                n->right = null_node;
                s.push( n );
            } else {
                s.push( n->right );
            }
            if (nullptr == n->left) {
                print_null();
            } else {
                s.push( n->left );
            }
        }
    }
    printf("\n");
}

int main()
{
    print_tree( nullptr );
    print_tree( new node(1) );
    print_tree( new node(1,
                         new node(2,
                                  nullptr,
                                  new node(5)),
                         new node(3,
                                  new node(4)) ) );
    return 0;
}

