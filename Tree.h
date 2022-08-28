#ifndef TREE_H
#define TREE_H
template <class T>
struct nodeTree
{
    T data;
    nodeTree<T> *left;
    nodeTree<T> *right;
    virtual ~nodeTree();
    void makeEmpty(nodeTree<T> *t);
};
template <class T>
class Tree
{

public:
    Tree();
    virtual ~Tree();
    void insert(T data);
    void remove(T data);
    void display();
    nodeTree<T> *search(T data);
    void makeEmpty(); // left as an exercise
    T findMin();
    T findMax();
    T sum();                 // for any general tree
    int count();             // for any general tree
    int countLeaves();       // for any general tree
    int countOneChild();     // for any general tree
    int height();            // for any general tree
    bool isBst();            // for any general tree left as an exercise
    bool isTherePath(T sum); // for any general tree
    T minimum();             // for any general tree
    void copy(Tree &dst);
    nodeTree<T> *root;

protected:
private:
    nodeTree<T> *makeEmpty(nodeTree<T> *t);
    nodeTree<T> *insert(T data, nodeTree<T> *t);
    nodeTree<T> *findMin(nodeTree<T> *t);
    nodeTree<T> *findMax(nodeTree<T> *t);
    nodeTree<T> *remove(T data, nodeTree<T> *t);
    void inorder(nodeTree<T> *t);
    nodeTree<T> *search(T data, nodeTree<T> *t);
    T sum(nodeTree<T> *t);
    int count(nodeTree<T> *t);
    int countLeaves(nodeTree<T> *t);
    int countOneChild(nodeTree<T> *t);
    int height(nodeTree<T> *t);
    T minimum(nodeTree<T> *t);
    void copy(nodeTree<T> *t, nodeTree<T> *&dst);
    bool isBst(nodeTree<T> *t);
    bool isTherePath(nodeTree<T> *t, T val);
};

#endif // TREE_H
