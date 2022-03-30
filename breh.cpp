#include<iostream>
#include<vector>
using namespace std;

// vector<int*> vect;
class A
{
    public:
        vector<int*> vect;
        void fun()
        {
            int a=3;
            int*b=&a;
            vect.push_back(b);
            return;
        }
};

int main(void)
{
    A a;
    a.fun();
    cout << *(a.vect[0]);
    return 0;
}