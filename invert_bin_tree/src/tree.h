class Node {
public:
    Node *left;
    Node *right;
    int value;

    Node();
    Node(int);
    Node(Node &&) = default;
    Node(const Node &) = default;
    ~Node();

    void printValue();
    void invert();
    void printInOrder();

private:
    void innerInvert(Node *);
    void printInOrderInner(Node *);
};

