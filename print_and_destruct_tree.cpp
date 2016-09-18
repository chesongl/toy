//
//  destructive tree serialization
//  with minimal space complexity
//  tree nodes are being destructed at the same time
//  usually during finalization phase of the process
//

#include <stdio.h>
#include <cassert>

struct node {
    union {
	node * left;
	node * next;
    };
    node * right;
    int data;

    node(int data,
	 node * left = nullptr,
	 node * right = nullptr) :
        data(data),
	left(left),
	right(right) { }
    
    void print() {
        printf("%d ", data);
    }
};

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

void print_node(node * n)
{
    if (nullptr == n) {
	print_null();
    } else {
	n->print();
    }
}

void print_and_destruct_tree(node * root)
{
    stack s;
    auto n = root;
    while (true) {
	print_node(n);
	if (nullptr == n) {
	    if (s.empty()) {
		break;
	    }
	    auto p = s.pop();
	    n = p->right;
	    delete p;
	} else {
	    auto left = n->left;
	    s.push(n);
	    n = left;
	}
    }
    printf("\n");
}

int main()
{
    // .
    print_tree( nullptr );
    // 1 . . 
    print_tree( new node(1) );    
    // 1 2 . 5 . . 3 4 . . .
    print_tree( new node(1,
                         new node(2,
                                  nullptr,
                                  new node(5)),
                         new node(3,
                                  new node(4)) ) );
    return 0;
}

