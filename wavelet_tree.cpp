#include<bits/stdc++.h>

using namespace std;

struct wavelet_tree{
    int low, high, mid, cnt, only;
    bool leaf;
    wavelet_tree *left, *right;
    vector<int> *mapLeft, *mapRight;

    wavelet_tree(){
        low = high = mid = cnt = 0;
        leaf = false;
    }

    wavelet_tree(int l, int h, vector<int> &v){
        low = l, high = h;
        mid = (low + high)/2;
        cnt = (int)v.size();
        left = new wavelet_tree;
        right = new wavelet_tree;
        leaf = false;
        mapLeft = new vector<int>;
        mapRight = new vector<int>;

        if ((int)v.size() == 1){
            leaf = true;
            only = v[0];
        }
        else if (low != high){
            for (auto &ele: v){
                if (ele > mid){
                    mapRight->push_back(ele);
                }
                else {
                    mapLeft->push_back(ele);
                }
            }

            if (!mapLeft->empty()){
                *left = wavelet_tree(low, mid, *mapLeft);
            }
            if (!mapRight->empty()){
                *right = wavelet_tree(mid + 1, high, *mapRight);
            }

            mapLeft->clear();
            mapRight->clear();
            mapLeft->push_back(0);
            mapRight->push_back(0);
            for (auto &ele: v){
                mapLeft->push_back(mapLeft->back() + (ele <= mid));
                mapRight->push_back(mapRight->back() + (ele > mid));
            }
        }
    }

    int quantile(int k, int i, int j){
        if (low == high){
            return low;
        }
        if (leaf){
            return only;
        }

        int c = (*mapLeft)[j] - (*mapLeft)[i - 1];
        if (k <= c){
            return left->quantile(k, (*mapLeft)[i - 1] + 1, (*mapLeft)[j]);
        }
        else{
            return right->quantile(k - c, (*mapRight)[i - 1] + 1, (*mapRight)[j]);
        }
    }

    int range(int x, int y, int i, int j){
        if (low > y || high < x) return 0;
        if (leaf) {
            return (only <= y && only >= x);
        }

        if (low >= x && high <= y) return j - i + 1;
        return left->range(x, y, (*mapLeft)[i - 1] + 1, (*mapLeft)[j]) + right->range(x, y, (*mapRight)[i - 1] + 1, (*mapRight)[j]);
    }
};

int main(){
    ios::sync_with_stdio(false), cin.tie(nullptr);

    
    return 0;
}