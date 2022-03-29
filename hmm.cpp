// #include <iostream>
// #include <vector>
// #include <queue>
// #include <string>
// #include <algorithm>
// #include <numeric>
// #include <set>
// #include <cstdlib>
// #include <map>
// #include <iomanip>
// #include <cmath>

// using namespace std;

// typedef long long int ll;
// typedef long double ld;
// typedef pair<ll, ll> pl;
// typedef tuple<ll, ll, ll> tl;
// typedef vector<ll> vl;
// typedef vector<pl> vpl;
// typedef vector<ld> vld;
// typedef vector<tl> vtl;
// typedef queue<ll> ql;
// typedef queue<pl> qpl;
// typedef queue<tl> qtl;
// typedef priority_queue<ll> pql;
// typedef priority_queue<pl> pqpl;
// typedef priority_queue<tl> pqtl;

// #define all(v) (v).begin(), (v).end()
// #define mp make_pair
// #define mt make_tuple
// #define pb push_back
// #define mod 998244353

// const int MOD = 1e9+7;
// const ld PI = acos(-1);
// const ld EPS = 1e-9;
// const ll INF = 1e18;

// class A
// {
//     public:
//         int a;
//         string classname()
//         {
//             return "A";
//         }
// };
// class B: public A
// {
//     public:
//         int b;
//         B(ll x)
//         {
//             a = x;
//             cout << "a loda" << endl;
//         }
// };
// int main()
// {
//     //A a;
//     B b = B(3);
//     cout << b.a << endl;
// }



#include <iostream>
#include <stdexcept>

using namespace std;

int AddPositiveIntegers(int a, int b)
{
    if (a < 0 || b < 0)
        throw std::invalid_argument("AddPositiveIntegers arguments must be positive");

    return (a + b);
}

int main()
{
    try
    {
        cout << AddPositiveIntegers(-1, 2); //exception
    }

    catch (std::invalid_argument& e)
    {
        cerr << e.what() << endl;
        return -1;
    }

    return 0;
}