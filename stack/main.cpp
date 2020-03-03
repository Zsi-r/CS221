#include "seqStack.cpp"
#include "linkStack.cpp"
#include <cstring>

bool isReverse1(char *s)
{
    int len = strlen(s),i;
    seqStack<char> st(len);

    for (i=0; i<len; ++i) st.push(s[i]);

    for (i=0; !st.isEmpty();++i)
    {
        if (s[i]!=st.pop()) return false;
    }

    return true;
}

bool isReverse2(char *s)
{
    int len = strlen(s),i;
    linkStack<char> st;

    for (i=0; i<len; ++i) st.push(s[i]);

    for (i=0; !st.isEmpty();++i)
    {
        if (s[i]!=st.pop()) return false;
    }

    return true;
}


int main()
{

    char st[]= "abcba" ;
    cout << st << endl;
    cout<< isReverse1(st)<<endl;
    cout<< isReverse2(st)<<endl;

    cout << endl;
    cout << "seqStack test: "<<endl;
    seqStack<int> a1,b1;
    cout << a1.isEmpty()<<endl;
    for(int i=0;i<5;i++)
    {
        a1.push(2*i);
    }
    b1.push(300);
    cout<< b1.isEmpty()<<endl;
    cout<< a1.top()<<endl;
    cout<< b1.pop()<<endl;
    cout<< b1.isEmpty()<<endl;

    cout << endl;
    cout << "linkStack test: "<<endl;
    linkStack<char> a2,b2;
    cout << a2.isEmpty()<<endl;
    char character = 'A';
    for(int i=0;i<5;i++)
    {
        a2.push(character);
        character +=1 ;
    }
    b2.push('z');
    cout<< b2.isEmpty()<<endl;
    cout<< a2.top()<<endl;
    cout<< b2.pop()<<endl;
    cout<< b2.isEmpty()<<endl;

}
