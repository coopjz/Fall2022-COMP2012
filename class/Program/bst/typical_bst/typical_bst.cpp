template <typename T>
class BST
{
public:
    BST();                 // default constructor
    BST(const BST &other); // copy constructor
    BST(BST &&other);      // move constructor
    ~BST();                // destructor
    const T &findMin() const;
    const T &findMax() const;
    bool isEmpty() const;
    bool isContain(const t &) const;
    void insert(const T &) const;
    void insert(T &&) const;
    void remove(const T &);
    void print(ostream &out = out) const;
    BST &operator=(const BST &other);
    BST &operator=(BST &&other);

private:
    struct BSTNode
    {
        T element;
        BSTNode *right;
        BSTNode *left;
        BSTNode(const T &element_, BSTNode *right_, BSTNode *left_)
            : element(element_), right(right_), left(left_) {}
        BSTNode(T &&element_, BSTNode *right_, BSTNode *left_)
            : element(std::move(element_)), left(left_), right(right_)
        {
        }
    };
    void insert(const T &x, BSTNode *&t);
    void insert(T &&x, BSTNode *&t);
    void remove(const T &x, BSTNode *&t);
    BSTNode *findMin(BSTNode *t) const;
    BSTNode *findMax(BSTNode *t) const;
    bool contains(const T &x, BSTNode *t) const;
    void makeEmpty(BSTNode *&t);
    void printTree(BSTNode *t, ostream &out) const;
    BSTNode *clone(BSTNode *t) const;
};