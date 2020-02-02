#ifndef LAB1_GRAPHS_ALGO_STRESS_TESTS_H
#define LAB1_GRAPHS_ALGO_STRESS_TESTS_H



void stress_test1(){
    UI N = 1000;
    UI M = N;
    float p = M/((N*(N-1))/2.);


        Graph<UC> G(N);
        G.generate_rand(p);

        find_rand_bridges(G);
        vector<EDGE<UC>> &wei = G.get_edges_list();
        sort(wei.begin(), wei.end(), comp<UC>);
        G.print_edges_list();
        cout << "here" << endl;
        UI count_fails = 0;
        UI count_all = 0;
        UI len = wei.size();   //necessary
        for (UI i=0; i<len; i++){
            if(wei[i].weight != 0) {
                UI k = 1;
                UI l = 0;
                if (i+k < len) {
                    while (wei[i].weight == wei[i + k].weight) {
                        l += (check_double_bridge(G, wei[i].edge_a, wei[i].edge_b, wei[i + k].edge_a, wei[i + k].edge_b));
                        count_all++;
                        k++;
                        if (i+k >= len) break;
                    }
                }
                if (l) count_fails++;
            }
            else{
                count_fails += (!check_one_bridge(G, wei[i].edge_a, wei[i].edge_b));
                count_all++;
            }
        }

        cout << "fails = " << count_fails << " right = " << count_all - count_fails << " all = " << count_all << endl;


};

//bool stress_for_dfs(){
//    for (UI i=3; i<=1000; i++){
//        Graph G(i);
//        UI M = i;
//        float p = M / ((i * (i - 1)) / 2.);
//        G.generate_rand(p);
//        vector<UI> v;
//        find_dfs_bridges(G, v);
//        if(v.size()){
//            for (UI k=0; k<v.size()-1; k+=2){
//                if(!check_one_bridge(G, v[k], v[k+1])) {
//                    return 0;
//                }
//            }
//        }
//    }
//    return 1;
//}
//
//float stress_for_rand(){
//    UI count_fails = 0;
//    UI count_all = 0;
//    for (UI i=3; i<=1000; i++){
//        Graph G(i);
//        UI M = i;
//        float p = M / ((i * (i - 1)) / 2.);
//        G.generate_rand(p);
////        find_rand_bridges(G);
//        vector<vector<UI>> wei = G.get_edges_list();
//        radix_sort(wei);
//
//        for (UI i=0; i<wei.size(); i++){
//            if(wei[i][2]!=0) {
//                UI k = 1;
//                if (i+k < wei.size()) {
//                    while (wei[i][2] == wei[i + k][2]) {
//                        count_fails += (!check_double_bridge(G, wei[i][0], wei[i][1], wei[i + k][0], wei[i + k][1]));
//                        count_all++;
//                        k++;
//                        if (i+k >= wei.size()) break;
//
//                    }
//                }
//            }
//            else{
//                count_fails += (!check_one_bridge(G, wei[i][0], wei[i][1]));
//                count_all++;
//            }
//        }
//    }
//    return count_fails/count_all;
//}

#endif //LAB1_GRAPHS_ALGO_STRESS_TESTS_H
