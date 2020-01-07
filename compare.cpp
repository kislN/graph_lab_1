//
// Created by maxim on 07.01.2020.
//


#include <vector>

using namespace std;
typedef unsigned int UI;  // 4 bytes [0; 4 294 967 295]

bool compareThirds(const vector<int>& first, const vector<int>& sec)
{
    return first[2] < sec[2];
}


//int main() {
//    vector<vector<int>> adj_list;
//
//    for (int i=0; i<5; i++) {
//            vector<int> values{rand() % 100, rand() % 100, rand() % 100};
//            adj_list.push_back(values);
//    }
//    sort(adj_list.begin(), adj_list.end(), compareThirds);
//    cout << "stop";
//}
