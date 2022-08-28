#include <iostream>
using namespace std;
#include "tree.cpp"
int main(){
    Tree<int> t, ct;
    t.insert(30);
    t.insert(20);
    t.insert(20);
    t.copy(ct);


    cout << "isbst: "<<t.isTherePath(70)<<endl;
    /*
    p=t.search(40);
    cout<<t.findMin()<< endl;
    cout<<t.findMax()<< endl;
    cout << p->data<<endl;
    t.display();*/

}
