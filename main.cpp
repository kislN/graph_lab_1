#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;
typedef uint64_t UL;        // 8 bytes [0; 18 446 744 073 709 551 615]
typedef unsigned int UI;    // 4 bytes [0; 4 294 967 295]
typedef unsigned short US;  // 2 bytes [0; 65 535]
typedef uint8_t UC;   // 1 byte [0; 255] don't use because it's a character type (like unsigned char)

mt19937 gen(time(0));


#include "Graph.h"
#include "check_bridge.h"
#include "find_bridges.h"
#include "weights_sort.h"
#include "real_graph.h"
#include "stress_tests.h"
#include <cmath>
#include <limits>



int main() {
    Graph<UI> NY_graph(264346);
    create_NY_graph(NY_graph);



    UI N = 20;
    Graph<US> G(N);
    G.generate_rand(0.2);

    cout << "Graph_size = " << G.get_graph_size() << endl <<
    "Edges_num = " << G.get_edges_num() << endl << "Edges_dens = " << G.get_edges_dens() << endl;

    cout << "Connect_num = " << connect_comp(G) << endl;

    G.print_adj_list();
//    G.print_adj_with_index();
//    G.print_edges_list();

    G.print_adj_with_index();
    G.print_edges_list();

    vector<UI> br;
    find_dfs_bridges(G, br);
    copy(br.begin(), br.end(), ostream_iterator<UI>(cout," "));

    find_rand_bridges(G);
    cout << endl;
    vector<EDGE<US>> &w = G.get_edges_list();
    bucket_sort(w, 3);
    G.print_edges_list();



//    cout << stress_for_dfs() << endl;
//    cout << stress_for_rand() << endl;
//
//    ofstream outdata("Out.csv");
//    outdata << "NumVert,DFS,Rand,Rand_Radix,Rand_Bucket,Rand_Sort" << endl;
//    cout << "File is open " <<  outdata.is_open() << endl;
//
//
//    UI N = 100;
//    UI k = 1;
//    for (UI i=0; i<14; i++){
//        UI M = 0;
//        float p = M/((N*(N-1))/2.);
//        cout << i << " " << p << endl;
//        UI avtime1 = 0;
//        UI avtime2 = 0;
//        UI avtime3 = 0;
//        UI avtime4 = 0;
//        UI avtime5 = 0;
//        for (UI j=0; j<k; j++){
//            Graph Gr(N+1);
//            Gr.generate_rand(p);
//
//            UI start_time = clock();
//            vector<UI> bri;
//            find_dfs_bridges(Gr, bri);
//            avtime1 += (clock() - start_time);
//
//            start_time = clock();
//            vector<UI> bri2;
//            find_rand_bridges(Gr, bri2);
//            avtime2 += (clock() - start_time);
//
//            vector<vector<UI>> wei1 = Gr.get_edges_list();
//            vector<vector<UI>> wei2 = wei1;
//            vector<vector<UI>> wei3 = wei1;
//
//            start_time = clock();
//            radix_sort(wei1);
//            avtime3 += (clock() - start_time) + avtime2;
//
//            start_time = clock();
////        bucket_sort(wei2, wei2.size()/20);
//            avtime4 += (clock() - start_time) + avtime2;
//
//            start_time = clock();
//            sort(wei3.begin(), wei3.end(), comp);
//            avtime5 += (clock() - start_time) + avtime2;
//        }
//
//        outdata << N << "," << avtime1 / k*1000000.0 << "," << avtime2 / k*1000000.0 << "," << avtime3 / k*1000000.0 << "," << avtime4 / k*1000000.0 << "," << avtime5 / k*1000000.0 <<  endl;
//
//        N += 2000;
//
//
//    }

    return 0;

//    ofstream outdata("Out.csv");
//    outdata << "NumVert,DFS,Rand,Rand_Radix,Rand_Bucket,Rand_Sort" << endl;//prompt user for numbers
//    cout << "File is open " <<  outdata.is_open() << endl;
//
//    UI N = 1000;

//    for (UI i=0; i<30; i++){
//        UI M = N;
//        float p = M/((N*(N-1))/2.);
//        cout << p << endl;
//        Graph Gr(N);
//        Gr.generate_rand(p);
//        UI avtime1 = 0;
//        UI avtime2 = 0;
//        UI avtime3 = 0;
//        UI avtime4 = 0;
//        UI avtime5 = 0;
//        UI start_time = clock();
//        vector<UI> bri;
//        find_dfs_bridges(Gr, bri);
//        avtime1 += (clock() - start_time);
//
//        start_time = clock();
////        find_rand_bridges(Gr);
//        avtime2 += (clock() - start_time);
//        vector<vector<UI>> wei1 = Gr.get_edges_list();
//        vector<vector<UI>> wei2 = wei1;
//        vector<vector<UI>> wei3 = wei1;
//        start_time = clock();
//        radix_sort(wei1);
//        avtime3 += (clock() - start_time) + avtime2;
//        start_time = clock();
////        bucket_sort(wei2, wei2.size()/20);
//        avtime4 += (clock() - start_time) + avtime2;
//        start_time = clock();
//        sort(wei3.begin(), wei3.end(), comp);
//        avtime5 += (clock() - start_time) + avtime2;
//
//        outdata << N << "," << avtime1 / 1000000.0 << "," << avtime2 / 1000000.0 << "," << avtime3 / 1000000.0 << "," << avtime4 / 1000000.0 << "," << avtime5 / 1000000.0 <<  endl;
//        N += 1000;
//    }




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




}