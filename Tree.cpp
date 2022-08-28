#include <iostream>
using namespace std;
#include "Tree.h"
template <class T>
Tree<T>::Tree()
{
    root = nullptr;
}
template <class T>
Tree<T>::~Tree()
{
    root = makeEmpty(root);
}
template <class T>
void Tree<T>::insert(T data)
{
    root = insert(data, root);
}
template <class T>
void Tree<T>::remove(T data)
{
    root = remove(data, root);
}
template <class T>
void Tree<T>::display()
{
    inorder(root);
}
template <class T>
nodeTree<T> *Tree<T>::search(T data)
{
    return search(data, root);
}
template <class T>
T Tree<T>::findMin()
{
    return findMin(root)->data;
}
template <class T>
T Tree<T>::findMax()
{
    return findMax(root)->data;
}

template <class T>
void Tree<T>::makeEmpty()
{
    root = makeEmpty(root);
}
template <class T>
T Tree<T>::sum()
{
    return sum(root);
}
template <class T>
int Tree<T>::count()
{
    return count(root);
}
template <class T>
int Tree<T>::countLeaves()
{
    return countLeaves(root);
}
template <class T>
int Tree<T>::countOneChild()
{
    return countOneChild(root);
}
template <class T>
int Tree<T>::height()
{
    return height(root);
}
template <class T>
T Tree<T>::minimum()
{
    return minimum(root);
}
template <class T>
void Tree<T>::copy(Tree &dst)
{
    copy(root, dst.root);
}
template <class T>
bool Tree<T>::isBst()
{
    return isBst(root);
}
template <class T>
bool Tree<T>::isTherePath(T sum)
{
    return isTherePath(root, sum);
}

template <class T>
T Tree<T>::sum(nodeTree<T> *t)
{
    if (t == NULL)
    {
        return 0;
    }
    else
    {
        return t->data + sum(t->left) + sum(t->right);
    }
}

template <class T>
nodeTree<T> *Tree<T>::makeEmpty(nodeTree<T> *t)
{
    if (t == NULL)
    {
        return NULL;
    }
    else
    {
        t->left = makeEmpty(t->left);
        t->right = makeEmpty(t->right);
        delete t;
    }
    return NULL;
}
template <class T>
nodeTree<T> *Tree<T>::insert(T data, nodeTree<T> *t)
{
    if (t == NULL)
    {
        t = new nodeTree<T>;
        t->data = data;
        t->left = t->right = NULL;
    }
    else if (data < t->data)
    {
        t->left = insert(data, t->left);
    }
    else
    {
        t->right = insert(data, t->right);
    }
    return t;
}
template <class T>
nodeTree<T> *Tree<T>::remove(T data, nodeTree<T> *t)
{
    nodeTree<T> *temp;
    if (t == NULL)
        return NULL;
    else if (data < t->data)
    {
        t->left = remove(data, t->left);
    }
    else if (data > t->data)
    {
        t->right = remove(data, t->right);
    }
    else if (t->left != NULL && t->right != NULL)
    {
        temp = findMax(t->left);
        t->data = temp->data;
        t->left = remove(temp->data, t->left);
    }
    else
    {
        temp = t;
        if (t->left == NULL)
            t = t->right;
        else if (t->right == NULL)
            t = t->left;
        delete temp;
    }
    return t;
}
template <class T>
void Tree<T>::inorder(nodeTree<T> *t)
{
    if (t == NULL)
    {
        return;
    }
    else
    {
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }
}
template <class T>
nodeTree<T> *Tree<T>::search(T data, nodeTree<T> *t)
{
    if (t == NULL)
    {
        return NULL;
    }
    else if (data == t->data)
    {
        return t;
    }
    else if (data < t->data)
    {
        return search(data, t->left);
    }
    else
    {
        return search(data, t->right);
    }
}
template <class T>
nodeTree<T> *Tree<T>::findMin(nodeTree<T> *t)
{
    while (t->left != NULL)
        t = t->left;
    return t;
}
template <class T>
nodeTree<T> *Tree<T>::findMax(nodeTree<T> *t)
{
    while (t->right != NULL)
        t = t->right;
    return t;
}
template <class T>
int Tree<T>::count(nodeTree<T> *t)
{
    if (t == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + count(t->left) + count(t->right);
    }
}

template <class T>
int Tree<T>::countLeaves(nodeTree<T> *t)
{
    if (t == NULL)
    {
        return 0;
    }
    else if (t->left == NULL && t->right == NULL)
    {
        return 1;
    }
    else
    {
        return countLeaves(t->left) + countLeaves(t->right);
    }
}
template <class T>
int Tree<T>::countOneChild(nodeTree<T> *t)
{
    if (t == NULL || t->left == NULL && t->right == NULL)
    {
        return 0;
    }
    else if (t->right == NULL)
    {
        return 1 + countOneChild(t->left);
    }
    else if (t->left == NULL)
    {
        return 1 + countOneChild(t->right);
    }
    else
    {
        return countOneChild(t->left) + countOneChild(t->right);
    }
}
template <class T>
int Tree<T>::height(nodeTree<T> *t)
{
    int hl, hr;
    if (t == NULL || t->left == NULL && t->right == NULL)
    {
        return 0;
    }
    else
    {
        hl = 1 + height(t->left);
        hr = 1 + height(t->right);
        return hl > hr ? hl : hr;
    }
}
/*
template <class T>
T Tree<T>::minimum(nodeTree<T> * t){
    int m,ml, mr;
    if(t->left==NULL && t->right==NULL){
        return t->data;
    }else if(t->right==NULL){
        ml=minimum(t->left);
        return ml<t->data? ml:t->data;
    }else if(t->left==NULL){
        mr=minimum(t->right);
        return mr<t->data? mr:t->data;
    }else{
        ml=minimum(t->left);
        mr=minimum(t->right);
        m=mr<ml? mr:ml;
        return m<t->data? m:t->data;
    }
}*/
template <class T>
T Tree<T>::minimum(nodeTree<T> *t)
{
    static T m = t->data;
    if (t != NULL)
    {
        if (t->data < m)
            m = t->data;
        return minimum(t->left);
        return minimum(t->right);
    }
    return m;
}
template <class T>
void Tree<T>::copy(nodeTree<T> *src, nodeTree<T> *&dst)
{
    nodeTree<T> *p;
    if (src == NULL)
    {
        dst = NULL;
        return;
    }
    else
    {
        p = new nodeTree<T>;
        p->data = src->data;
        p->left = p->right = NULL;
        dst = p;
        copy(src->left, dst->left);
        copy(src->right, dst->right);
    }
}

template <class T>
bool Tree<T>::isTherePath(nodeTree<T> *t, T sum)
{
    if (t == NULL)
    {
        if (sum == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return isTherePath(t->left, sum - t->data) || isTherePath(t->right, sum - t->data);
    }
}
template <class T>
nodeTree<T>::~nodeTree()
{
    makeEmpty(this);
}
template <class T>
void nodeTree<T>::makeEmpty(nodeTree<T> *t)
{
    if (t == NULL)
    {
        return;
    }
    else
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
}
