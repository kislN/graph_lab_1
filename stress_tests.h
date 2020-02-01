

#ifndef LAB1_GRAPHS_ALGO_STRESS_TESTS_H
#define LAB1_GRAPHS_ALGO_STRESS_TESTS_H


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
