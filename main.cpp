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
typedef unsigned char UC;  // 1 byte [0; 255]

mt19937 gen(time(0));
uniform_int_distribution<> uid(0, 4294967295);

#include <fstream>
#include<string>
#include <iomanip>



int main() {

    Graph G(10);
    G.generate_rand(0.1);



    cout << G.get_graph_size() << " " << G.get_edges_num() << " " << G.get_edges_dens() << endl;
    cout << "conn_comp " << connect_comp(G) << endl;
//    G.add_edge(7,6);
//    G.add_edge(2,7);
//    G.delete_edge(6,4);
    G.print_adj_list();

//    G.print_edges_list();

//    G.print_adj_with_index();


    vector<UI> br;
    find_dfs_bridges(G, br);

    if(br.size()){
    for (UI i=0; i<br.size()-1; i+=2){
//        cout << br[i] << " - " << br[i+1] << " : " << check_one_bridge(G, br[i], br[i+1]) << endl;
    }}

    find_rand_bridges(G);

    G.print_edges_list();

    vector<vector<UI>> weights = G.get_edges_list();                //copy vec to vec, not link
//    radix_sort(G.get_edges_list());
//    bucket_sort(G.get_edges_list(), 3);
    sort(weights.begin(), weights.end(), comp);

//    G.print_edges_list();



return 0;


//    cout << "sdgdg" << endl;
//    for (UI i=0; i<wei.size(); i++){
//
//        if(wei[i][2]!=0) {
//            UI k = 1;
//            if (i+k < wei.size()) {
//                while (wei[i][2] == wei[i + k][2]) {
//                    cout << wei[i][0] << " - " << wei[i][1] << " and " << wei[i + k][0] << " - " << wei[i + k][1] << endl;
//                    cout << check_double_bridge(Gr, wei[i][0], wei[i][1], wei[i + k][0], wei[i + k][1]) << endl;
//                    k++;
//                    if (i+k >= wei.size()) break;
//
//                }
//            }
//        }
//        else{
//            cout << check_one_bridge(Gr, wei[i][0], wei[i][1]) << endl;
//        }
//    }




    ofstream outdata("Out.csv");
    outdata << "NumVert,EdgeDens,DFS,Rand" << endl;//prompt user for numbers
    cout << "File is open " <<  outdata.is_open() << endl;

    UI N = 1000;

    for (UI i=0; i<3; i++){
        UI M = N;
        float p = M/((N*(N-1))/2.);
        cout << p << endl;
        for (UI j=0; j<1; j++){
            cout << i << " Creating" << endl;
            Graph Gr(N);
            Gr.generate_rand(p);
            cout << "Done" << endl;
            UI avtime1 = 0;
            UI avtime2 = 0;
            for (UI k=0; k<1; k++) {
                UI start_time = clock();
                cout << "Dfs" << endl;
                vector<UI> bri;
                find_dfs_bridges(Gr, bri);
                cout << "Done" << endl;
                avtime1 += (clock() - start_time);
                start_time = clock();
                cout << "Rand" << endl;
                vector<vector<UI>> wei;
                find_rand_bridges(Gr);
                cout << "Done" << endl;
                avtime2 += (clock() - start_time);

            }
            outdata << N << "," << p << "," << avtime1 / 1000000.0 << "," << avtime2 / 1000000.0 << endl;
            p *= 10;
        }
        N += 20000;
    }


    return 0;

//
//
//    for (UI i=0; i<10; i++){
//        cout << i << " ";
//        float p = 0.01;
//        for (UI j=0; j<1; j++){
//            Graph G(N);
//            G.generate_rand(p);
//            UI avtime1 = 0;
//            UI avtime2 = 0;
//            for (UI k=0; k<3; k++) {
//                UI start_time = clock();
//                vector<vector<UI>> wei;
////                find_rand_bridges(G, wei);
//                avtime1 += (clock() - start_time);
//                avtime2 += (clock() - start_time);
//                vector<vector<UI>> wei2 = wei;
//                start_time = clock();
//                radix_sort(wei);
//                avtime1 += (clock() - start_time);
//                start_time = clock();
//                sort(wei2.begin(), wei2.end(), comp);
//                avtime2 += (clock() - start_time);
//
//            }
//            outdata << N << "," << p << "," << avtime1 / 3000000.0 << "," << avtime2 / 3000000.0 << endl;
//            p *= 10;
//        }
//        N += 1000;
//    }
//
//    return 0;

//    for (UI i=0; i<wei.size(); i++){
//        cout << wei[i][0] << " - " << wei[i][1] << ": " << wei[i][2] << endl;
//    }
//    find_dfs_bridges(&Gr, M);
//    Gr.print_adj_list();


//    vector<vector<UI>> sin = find_dfs_bridges(Gr);

//    for(UI i=0; i<sin.size(); i++){
//        cout << check_one_bridge(Gr, sin[i][0], sin[i][1]) << endl;
//    }
//    for (UI i=0; i<wei.size(); i++){
//        cout << wei[i][0] << " - " << wei[i][1] << ": " << wei[i][2] << endl;
//    }

//    cout << "sdgdg" << endl;
//    for (UI i=0; i<wei.size(); i++){
//
//        if(wei[i][2]!=0) {
//            UI k = 1;
//            if (i+k < wei.size()) {
//                while (wei[i][2] == wei[i + k][2]) {
//                    cout << wei[i][0] << " - " << wei[i][1] << " and " << wei[i + k][0] << " - " << wei[i + k][1] << endl;
//                    cout << check_double_bridge(Gr, wei[i][0], wei[i][1], wei[i + k][0], wei[i + k][1]) << endl;
//                    k++;
//                    if (i+k >= wei.size()) break;
//
//                }
//            }
//        }
//        else{
//            cout << check_one_bridge(Gr, wei[i][0], wei[i][1]) << endl;
//        }
//    }
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