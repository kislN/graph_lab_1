//#include <stdint.h>
#include "Graph.h"
#include "check_bridge.h"
#include "find_bridges.h"
#include "weights_sort.h"
#include "real_graph.h"
#include "stress_tests.h"
#include <cmath>
#include <limits>


template <typename T>
void experim(ofstream &f, UI iter, UI step, UI aver, UI dens){
    UI N = 0;
    for (UI i=0; i<iter; i++){    //loop for N (10-1000)
        N += step;
        UI M = N/2 * dens;
        float p = M/((N*(N-1))/2.);
        UI time_dfs = 0, time_rand = 0, time_radix = 0, time_bucket = 0, time_sort = 0;

        for (UI j=0; j<aver; j++) { //loop for average time
            Graph<T> Gr(N);
            Gr.generate_rand(p);

            UI start_time = clock();
            vector<UI> bri;
            find_dfs_bridges(Gr, bri);
            time_dfs += (clock() - start_time);

            start_time = clock();
            find_rand_bridges(Gr);
            time_rand += (clock() - start_time);

            vector<EDGE<T>> wei1 = Gr.get_edges_list();
            vector<EDGE<T>> wei2 = wei1;
            vector<EDGE<T>> wei3 = wei1;

            start_time = clock();
            radix_sort(wei1);
            time_radix += (clock() - start_time) + time_rand;

            start_time = clock();
            bucket_sort(wei2, wei2.size() / 20);
            time_bucket += (clock() - start_time) + time_rand;

            start_time = clock();
            sort(wei3.begin(), wei3.end(), comp<T>);
            time_sort += (clock() - start_time) + time_rand;
        }

        f << N << "," << M << ","<< time_dfs / aver*1000000.0 << "," << time_rand / aver*1000000.0 << "," << time_radix / aver*1000000.0 << "," << time_bucket / aver*1000000.0 << "," << time_sort / aver*1000000.0 <<  endl;
    }
}

template <typename T>
bool do_experim(string file_name){
    ofstream out(file_name);
    if (!out.is_open()) return 0;
    cout << "File is open " << endl;
    out << "NumVert,NumEdges,DFS,Rand,Rand_Radix,Rand_Bucket,Rand_Sort" << endl;
    for (UI i=1; i<9; i*=2) {
        experim<T>(out, 10, 100, 3, i);
    }
    out.close();
    return 1;
}

int main() {

//    Graph<UI> NY_graph(264346);
//    create_NY_graph(NY_graph);

//    do_experim<UC>("./data/Out_8b.csv");
//    do_experim<US>("./data/Out_16b.csv");
//    do_experim<UI>("./data/Out_32b.csv");
    do_experim<UL>("./data/Out_64b.csv");



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