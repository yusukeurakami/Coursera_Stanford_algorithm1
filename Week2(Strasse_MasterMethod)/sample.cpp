#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>       // std::numeric_limits


using namespace std;

long long mergeAndCount(vector<int>& vec, int p, int q, int r) {
    long long count = 0;

    vector<int> L, R;
    for (int i = p; i <= q; ++i) L.push_back(vec[i]);
    for (int j = q + 1; j <= r; ++j) R.push_back(vec[j]);

    L.push_back(numeric_limits<int>::max()); //sentinel element
    R.push_back(numeric_limits<int>::max());

    int i = 0, j = 0;

    for (int k = p; k <= r; ++k) {
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            ++i;
        } else {
            vec[k] = R[j];
            ++j;
            if (L[i] != L.back() && R[j] != R.back())
                count += q - p + 1 - i;
        }
    }
    return count;
}

long long inversion(vector<int>& vec, int p, int r) {
    long long count = 0;

    if (p < r) {
        int q = (p + r) / 2;
        count = inversion(vec, p, q);
        count += inversion(vec, q + 1, r);
        count += mergeAndCount(vec, p, q, r);
    }

    return count;
} 

int main() {
    ifstream infile("IntegerArray.txt"); 
    int a;
    vector<int> vec;

    while (infile >> a)
        vec.push_back(a);

    cout << inversion(vec, 0, vec.size()-1) << endl;
    return 0;
}