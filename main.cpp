#include <iostream>
#include <vector>
#include <iterator>
#include <ctime>
#include <random>
#include <algorithm>
#include "Graph.h"
#include "check_bridge.h"
#include "find_bridges.h"
#include "weights_sort.h"

using namespace std;

typedef unsigned int UI;  // 4 bytes [0; 4 294 967 295]
typedef unsigned short US;  // 2 bytes [0; 65 535]

mt19937 gen(time(0));
uniform_int_distribution<> uid(0, 9999);


int main() {
    UI M = 10;
    Graph Gr(M);
    Gr.generate_rand(0.1);
    vector<vector<UI>> wei;
    find_rand_bridges(Gr, wei);
    cout << Gr.get_edges_num() << endl;

//    for (UI i=0; i<wei.size(); i++){
//        cout << wei[i][0] << " - " << wei[i][1] << ": " << wei[i][2] << endl;
//    }
//    find_dfs_bridges(&Gr, M);
//    Gr.print_adj_list();

    radix_sort(&wei, wei, wei.size());
    vector<vector<UI>> sin = find_dfs_bridges(Gr);

    for(UI i=0; i<sin.size(); i++){
        cout << check_one_bridge(Gr, sin[i][0], sin[i][1]) << endl;
    }
//    for (UI i=0; i<wei.size(); i++){
//        cout << wei[i][0] << " - " << wei[i][1] << ": " << wei[i][2] << endl;
//    }

    cout << "sdgdg" << endl;
    for (UI i=0; i<wei.size(); i++){

        if(wei[i][2]!=0) {
            UI k = 1;
            if (i+k < wei.size()) {
                while (wei[i][2] == wei[i + k][2]) {
                    cout << wei[i][0] << " - " << wei[i][1] << " and " << wei[i + k][0] << " - " << wei[i + k][1] << endl;
                    cout << check_double_bridge(Gr, wei[i][0], wei[i][1], wei[i + k][0], wei[i + k][1]) << endl;
                    k++;
                    if (i+k >= wei.size()) break;

                }
            }
        }
        else{
            cout << check_one_bridge(Gr, wei[i][0], wei[i][1]) << endl;
        }
    }
//    cout << "start" << endl;
//    vector<float> density;
//    vector<float> times;
//    float a = 100.;
//    for (float i=0; i<100; i+=5){
//        density.push_back(i/a);
//    }
//    copy(density.begin(), density.end(), ostream_iterator<float>(cout," "));
//    UI start_time;
//    UI M = 6000;
//    for (UI i=0; i<density.size(); i++) {
//        start_time = clock();
//        Graph G(M);
//        G.generate_rand(density[i]);
//        vector<int> marks = find_rand_bridges(&G, M);
//        sort(marks.begin(), marks.end());
//        times.push_back((clock() - start_time) / 1000000.0 );
//    }

//    Graph G(M);
//    G.generate_rand(0.03);
//
//    start_time = clock();
//    vector<int> marks = find_rand_bridges(&G, M);
//    sort(marks.begin(), marks.end());
//    cout << "\n" << (clock() - start_time) / 1000000.0  << endl;
//
//    start_time = clock();
//    vector<int> marks1 = find_rand_bridges(&G, M);
//    cout << endl;
//    radix_sort(&marks1, marks1, marks1.size());
//    cout << "\n" << (clock() - start_time) / 1000000.0  << endl;

//    start_time = clock();
//    //G.print_adj_list();
//    //cout << "edg: " << G.get_edges_num() << endl;
//    cout << connect_comp(&G) << endl;
//    cout << "done too" << endl;
//    cout << (clock() - start_time)/1000000.0 << endl;
//    start_time = clock();
//    //G.add_edge(4,1);
//    //G.print_adj_list();
//    //connect_comp(&G);
//   // find_dfs_bridges(&G);
//    find_rand_bridges(&G);
//
//    cout << "research is done" << endl;
//    cout << (clock() - start_time)/1000000.0 << endl;
//    start_time = clock();
//    cout << "k " << k << endl;
//    for (int i=0; i<N; i++){
//        for (int j=i+1; j<N; j++){
//            if (mark_list[i][j] == 0)
//                cout << check_bridge(&G, i, j) << endl;
//        }
//    }
//    cout << (clock() - start_time)/1000000.0 << endl;
//    cout << "runtime = " << clock()/1000000.0 << endl;
//    return 0;
}