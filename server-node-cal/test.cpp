#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        v.push_back(val);
    }
    int k;
    cin >> k;
    sort(v.begin(), v.end());

    if (n > k) {
        cout << "n>=k " << v[n-k] << endl;
    } else {
        cout<<"Inside else"<<endl;
        int maxi = n - 1;
        int mini = v[0];
        for (int i = 0; i < (k - n); i++) {
            int val = v[maxi] / 2;
            v[maxi] = val;
            maxi--;
            v.push_back(val);
            mini = min(mini, val);
            cout << "Changing mini" << endl;
        }
        cout << "mini " << mini << endl;
    }

    return 0;
}
