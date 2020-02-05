//#include <stdint.h>
#include "Graph.h"
#include "check_bridge.h"
#include "find_bridges.h"
#include "weights_sort.h"
#include "real_graph.h"
#include "stress_tests.h"
#include "experiments.h"
#include <cmath>
#include <limits>



void dfs_bri (  vector<vector<vector<UI>>> &adj,
                vector<bool> &used,
                UI &current,
                UI &parent )
{
//    cout << "current = " << current << endl;
    used[current] = 1;
//    k++;
//    cout << k << endl;
    for (UI i=0; i<adj[current].size(); ++i) {
        UI child = adj[current][i][0];
        if (child == parent)  continue;
        if (used[child]) {
//            cout<< "child if = " << child << endl;
        }
        else {
//            cout << "child else = " << child << endl;
            dfs_bri (adj, used, child, current);
//            k--;
//            cout << "exit2" << endl;
        }
    }
}

template <typename T>
void find_dfs_bri(Graph<T> &G) {
    UI N = G.get_graph_size();
    vector<bool> used(N);

    for (UI vert=0; vert<N; ++vert) {
        if (!used[vert]) {
            dfs_bri(G.get_adj_list(), used, vert, N);
            cout << "exit" << endl;
        }
    }
}


int main() {

//    Graph<UI> NY_graph(264346);
//    create_NY_graph(NY_graph);

//    do_experim<UC>("../data/Out_8b.csv", 5, 10, 1);
//    do_experim<US>("./data/Out_16b.csv", 21, 500, 3);
//    do_experim<UI>("./data/Out_32b.csv", 21, 500, 3);
//    do_experim<UL>("./data/Out_64b.csv", 21, 500, 3);



    UI N = 10;
    UI M = N;
    float p = M/((N*(N-1))/2.);
    Graph<US> G(N);
    cout << "Graph is done" << endl;
    G.generate_rand(p);
    cout << "Gen" << endl;
    G.print_adj_with_indexes();
    cout << endl;
    G.print_adj_list();
    vector<UI> v;
    DBS(G, v);
    cout << "dfs" << endl;


//    stress_test2();
    stress_test5();
//    vector<EDGE<US>> wei1 = G.get_edges_list();
//    vector<EDGE<US>> wei2 = wei1;
//    vector<EDGE<US>> wei3 = wei1;
//    G.print_edges_list();
//    if (wei2.size()) bucket_sort(wei2, wei2.size() / 20 + 1);




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
//        DBS(Gr, bri);
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
//    DBS(&Gr, M);
//    Gr.print_adj_list();


//    vector<vector<UI>> sin = DBS(Gr);

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
//                    cout << check_two_bridge(Gr, wei[i][0], wei[i][1], wei[i + k][0], wei[i + k][1]) << endl;
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
//        vector<int> marks = RBS(&G, M);
//        sort(marks.begin(), marks.end());
//        times.push_back((clock() - start_time) / 1000000.0 );
//    }




}