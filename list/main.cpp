#include "seqList.cpp"
#include "linkList.cpp"

int main()
{
    cout << "seqList test: " << endl;
    seqList<int> a(6),b(6);
    for(int i=0 ;i<6;i++)
    {
        a.insert(i,i);
        b.insert(i,2*i);
    }
    cout << a.length();
    a.remove(5);
    a.traverse();
    cout << endl;
    cout << a.visit(0) << endl;
    cout << b.search(4) << endl;
    a.clear();
    a.traverse();
    b.traverse();

    cout << endl;
    cout << "sLinkList test: " << endl;
    sLinkList<char> a2, b2;
    int count=0;
    for (char j = 'A'; j <='Z';j++)
    {   
        a2.insert(count,j);
        b2.insert(count,j + 32);
        count++;
    }
    cout << a2.length();
    b2.traverse();
    cout << a2.visit(10) << endl ;
    cout << b2.search('h')<<endl;
    b2.remove(3);
    b2.traverse();
    b2.clear();

    cout << endl;
    cout << "dLinkList test: " << endl;
    dLinkList<double> a3, b3;
    dLinkList<char> c3;
    double listdata = 0.03;
    for (int k = 0; k < 5;k++)
    {   
        a3.insert(k,listdata);
        b3.insert(k,listdata+0.8);
        c3.insert(k, 'A' + k);
        listdata = listdata + 2;
    }
    cout << a3.length();
    b3.traverse();
    cout << a3.visit(0) << endl;
    cout << a3.visit(4) << endl;
    c3.traverse();
    cout << c3.search('C') << endl;
    b3.remove(3);
    b3.traverse();
    b3.clear();
}
