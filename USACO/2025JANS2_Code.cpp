#include <bits/stdc++.h>
#ifdef LOCAL
#include "debugging.h"
#endif
#define ll long long
#define ld long double
#define mk make_pair
#define pb push_back
#define alls(x) x.begin(), x.end()
#define sz(x) (int)(x.size())
#define forn(i, n) for (int i = 0; i < int(n); i++)
#define rep(i, n) for (int i = 1; i <= int(n); i++)
#define inc(i, l, r, d) for (int i = l; i <= r; i += d)
#define dec(i, r, l, d) for (int i = r; i >= l; i -= d) 
#define dbg(v) cerr << "Line(" << __LINE__ << ") -> " << #v << " = " << (v) << endl;
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vll vector<ll>
#define endl '\n'
#define ppc __builtin_popcount
const ld eps = 1e-12;
const ll inf = 1e16;
const ll mod1 = 1e9 + 87;
const ll mod2 = 127397154761;
template<typename T> bool chkmin(T &a, T b){ return (b < a) ? a = b, 1 : 0; }
template<typename T> bool chkmax(T &a, T b){ return (b > a) ? a = b, 1 : 0; }
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
#define uid(lef, rig) uniform_int_distribution<int>(lef, rig)(rng)
#define ulld(lef, rig) uniform_int_distribution<ll>(lef, rig)(rng64)
template<class T1, class T2> istream& operator >> (istream& is, pair<T1,T2>& p) { is >> p.first >> p.second; return is; }

void IOS(string name = "") {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    if ((int)name.size()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vi a(n + 1);
    rep(i, n) {
        cin >> a[i];
        a[i] %= m;
    }
    sort(a.begin() + 1, a.end());
    // dbg(a);
    vll s(n + 1, 0);
    s[0] = 0ll;
    rep(i, n) s[i] = s[i - 1] + a[i];

    ll ans = 1ll * n * m;
    
    rep(i, n) {
        if (a[i] == a[i - 1]) continue; 

        // ll check = 0ll;
        // ll x = a[i];
        // rep(j, n) {
        //     ll b = a[j] - x;
        //     b = (b % m + m) % m;
        //     check += min(b, m - b);
        // }

        // we're at the first occurrence of a value:
        ll check = 0ll;
        int x = a[i]; // the optimal case occurs when a[i] is 0 (think about the changes)
        if (x < 0) x = m - 1;
        int bound = m / 2 + x;

        if (a[n] < bound) {
            // from i to n: add (a[j] - a[i]) = a[j] - a[i] to sum
            check += (s[n] - s[i - 1]) - 1ll * x * (n - i + 1);
            int l = 1, r = i - 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (a[mid] + m <= bound) {
                    l = mid + 1;
                }
                else {
                    r = mid - 1;
                }
            }
            l -= 1;
            // from 1 to l: add (a[j] + m - x) to sum
            check += s[l] + 1ll * (m - x) * l;
            // from l + 1 to i - 1: add (m - (a[i] + m - x)) = x - a[i] to sum
            check += 1ll * x * ((i - 1) - (l + 1) + 1) - (s[i - 1] - s[l]);
        }
        else {
            int r = upper_bound(alls(a), bound) - a.begin(); // the first position such that a[r] > bound
            r--; // now a[r] is the last position a[r] <= bound

            // from i to r: add a[i] - x to sum
            check += (s[r] - s[i - 1]) - 1ll * x * (r - i + 1);
            
            // from r + 1 to n: add m - (a[j] - x) = m + x - a[j] to sum
            check += 1ll * (m + x) * (n - r) - (s[n] - s[r]);
            
            // from 1 to i - 1: add m - ((a[j] - x) + m) = x - a[j] to sum
            check += 1ll * x * (i - 1) - s[i - 1];
        }
        chkmin(ans, check);
    }

    cout << ans << endl;
}

int main() {
    IOS();
    int Eureka;
    cin >> Eureka;
    while (Eureka--) {
        solve();
    }
    return 0;
}