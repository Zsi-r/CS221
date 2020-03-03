#include <iostream>

using namespace std;

int main()
{
    int T, n ,p,q,max=0;
    int tmp;
    cin >> T >> n;

    int *elem = new int[n];
    int *query = new int[T];

    for (int i = 0; i < n;i++)
    {
        cin >> elem[i];
    }

    for (int i = 0; i < T;i++)
    {
        cin >> query[i];
        if(query[i] >max){
            max = query[i];
        }
    }

    for (int N = n; N > 0 ; N--)
    {   
        for (p = n ; p > n-N ; p--)
        {
            q = p - 1;
            if (elem[q] < elem[p])
            {
                tmp = elem[p];
                elem[p] = elem[q];
                elem[q] = tmp;
            }
            if (N == (n+1)-max)
                break;
        }
        if (N == (n+1)-max) break;
    }

    for (int i = 0; i < T;i++)
    {
        int sum=0;
        for (int j = 0; j < query[i];j++)
            sum += elem[j];
        cout << sum <<endl;
    }

    cout << endl;
    cout << max << endl;
    for (int i = 0; i < n;i++)
    {
        cout << elem[i] <<endl;
    }
    return 0;
}