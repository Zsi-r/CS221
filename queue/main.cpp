#include "seqQueue.cpp"
#include "linkQueue.cpp"

int main()
{   
    cout<< endl;
    cout<< "seqQueue test: "<<endl;
    seqQueue<char> a2;
    a2.enQueue('a');
    a2.enQueue('n');
    cout << a2.isEmpty()<<endl;
    cout << a2.getHead()<<endl;
    cout << a2.deQueue()<<endl;
    cout << a2.getHead()<<endl;
    cout << a2.deQueue()<<endl;
    cout << a2.isEmpty()<<endl;

    cout<< endl;
    cout<< "linkQueue test: "<<endl;
    linkQueue<int> a1;
    a1.enQueue(3);
    cout << a1.getHead()<<endl;
    cout << a1.isEmpty()<<endl;
    cout << a1.deQueue()<<endl;
    cout << a1.isEmpty()<<endl;
    return 0;
}