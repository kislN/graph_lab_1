#ifndef LAB1_GRAPHS_ALGO_STRESS_TESTS_H
#define LAB1_GRAPHS_ALGO_STRESS_TESTS_H



void stress_test1(){    /// test DFS with unsigned char type, N=1000, M=8N, 10000 iterations
    UI N = 100;
    UI M = 1000;
    UI count_fails = 0;
    UI count_all = 0;

    for (UI iter=0; iter<1000; iter++) {
        float p = M/((N*(N-1))/2.);
        Graph<UC> G(N);
        G.generate_rand(p);
        vector<UI> bri;
        find_dfs_bridges(G, bri);
        for (UI i = 0; i < bri.size(); i+=2) {
            count_fails += (!check_one_bridge(G, bri[i], bri[i+1]));
            count_all++;
        }
        N++;
    }
    cout << "fails = " << count_fails << " right = " << count_all - count_fails << " all = " << count_all << endl;


};



void stress_test2(){    /// test rand with unsigned char type, N=1000, M=4N, 10000 iterations
    UI N = 100;
    UI M = N*4;
    float p = M/((N*(N-1))/2.);
    for (UI iter=0; iter<2; iter++) {
        Graph<UL> G(N);
        G.generate_rand(p);

        UI all = find_rand_bridges(G);
        vector<EDGE<UL>> &wei = G.get_edges_list();
        sort(wei.begin(), wei.end(), comp<UL>);

        UI count_fails = 0;

        UI len = wei.size();   /// it is necessary because &wei.size() changes after adding an edge
        UI iter_bri = 0;
        while(wei[iter_bri].weight==0){
            count_fails += (!check_one_bridge(G, wei[iter_bri].vertex_a, wei[iter_bri].vertex_b));
            iter_bri++;
        }

        while(iter_bri<len){
            UI blocks = 0;
            UI k = 0;
            /// Выделим блок ребер с одинаковыми весами
            while (wei[iter_bri].weight == wei[iter_bri + k].weight) {
                k++;
                if (iter_bri + k >= len) break;
            }
            /// Протестируем каждую пару ребер из данного блока
            for (UI i=iter_bri; i<iter_bri+k; i++){
                bool flag = 1;
                for (UI j=iter_bri; j<iter_bri+k; j++){
                    if (i!=j){
                        if (check_double_bridge(G, wei[i].vertex_a, wei[i].vertex_b, wei[j].vertex_a,
                                                wei[j].vertex_b)) {
                            if (i>j) count_fails++;
                            flag = 0;
                            break;
                        }
                    }
                }
                if (flag) count_fails++;
            }

            if (k == 1) count_fails--;
            iter_bri+=k;

        }

        cout << "fails = " << count_fails << " all = " << all << " del = " << float(count_fails)/all << endl;
    }

};

void stress_test3(){    /// test rand with unsigned char type, N=1000, M=4N, 10000 iterations
    UI N = 1000;
    UI M = N*2;
    float p = M/((N*(N-1))/2.);
    for (UI iter=0; iter<10; iter++) {
        Graph<UC> G(N);
        G.generate_rand(p);

        UI all = find_rand_bridges(G);
        vector<EDGE<UC>> &wei = G.get_edges_list();
        sort(wei.begin(), wei.end(), comp<UC>);

        UI count_1_fails = 0;
        UI count_2_fails = 0;
        UI count_1_all = 0;
        UI count_2_all = 0;
        UI fails = 0;
        UI len = wei.size();   /// it is necessary because &wei.size() changes after adding an edge
        UI iter_bri = 0;
        while(wei[iter_bri].weight==0){
            count_1_fails += (!check_one_bridge(G, wei[iter_bri].vertex_a, wei[iter_bri].vertex_b));
            iter_bri++;
            count_1_all++;
        }

        while(iter_bri<len){
            UI k = 1;
            if(iter_bri+k<len) {
                while (wei[iter_bri].weight == wei[iter_bri + k].weight) {
                    count_2_fails += (!check_double_bridge(G, wei[iter_bri].vertex_a, wei[iter_bri].vertex_b, wei[iter_bri + k].vertex_a,
                                                           wei[iter_bri+k].vertex_b));
                    k++;
                    count_2_all++;
                    if (iter_bri + k >= len) break;
                }
            }
            iter_bri++;
        }
        cout << count_1_fails+count_2_fails << endl;
        cout << "fails 1 = " << count_1_fails << " all 1 = " << count_1_all << " fails 2 = " << count_2_fails << " all 2 = " << count_2_all << " del = " << float(count_1_fails+count_2_fails)/(count_1_all+count_2_all) << endl;
    }

};


void stress_test4(){    /// test rand with unsigned char type, N=1000, M=4N, 10000 iterations
    UI N = 10;
    UI M = N*2;
    float p = M/((N*(N-1))/2.);
    for (UI iter=0; iter<10; iter++) {
        Graph<bool> G(N);
        G.generate_rand(p);

        UI all = find_rand_bridges(G);
        vector<EDGE<bool>> &wei = G.get_edges_list();
        sort(wei.begin(), wei.end(), comp<bool>);
        UI edg_pairs = (G.get_edges_num()*(G.get_edges_num()-1))/2;
        UI count_1_fails = 0;
        UI count_2_fails = 0;
        UI count_1_all = 0;
        UI count_2_all = 0;
        UI fails = 0;
        UI len = wei.size();   /// it is necessary because &wei.size() changes after adding an edge
        UI iter_bri = 0;
        while(wei[iter_bri].weight==0){
//            count_1_fails += (!check_one_bridge(G, wei[iter_bri].vertex_a, wei[iter_bri].vertex_b));
            iter_bri++;
//            count_1_all++;
        }

        while(iter_bri<len){
            UI k = 1;
            if(iter_bri+k<len) {
                while (wei[iter_bri].weight == wei[iter_bri + k].weight) {
                    count_2_fails += (!check_double_bridge(G, wei[iter_bri].vertex_a, wei[iter_bri].vertex_b, wei[iter_bri + k].vertex_a,
                                                           wei[iter_bri+k].vertex_b));
                    k++;
                    count_2_all++;
                    if (iter_bri + k >= len) break;
                }
            }
            iter_bri++;
        }

        cout << float(count_2_fails)/(edg_pairs-(count_2_all-count_2_fails)) << endl;
        cout << "fails 1 = " << count_1_fails << " all 1 = " << count_1_all << " fails 2 = " << count_2_fails << " all 2 = " << count_2_all << " del = " << float(count_1_fails+count_2_fails)/(count_1_all+count_2_all) << endl;
    }

};


void stress_test5(){    /// test rand with unsigned char type, N=1000, M=4N, 10000 iterations
    UI N = 10;
    UI M = N*2;
    float p = M/((N*(N-1))/2.);
    UI count_2_fails = 0;
    UI count_2_all = 0;
    UI count_1_fails = 0;
    UI count_1_all = 0;
    UI edg_pairs = 0;
    UI edg = 0;
    for (UI iter=0; iter<100; iter++) {
        Graph<bool> G(N);
        G.generate_rand(p);

        find_rand_bridges(G);
        vector<EDGE<bool>> &wei = G.get_edges_list();
        sort(wei.begin(), wei.end(), comp<bool>);
        edg_pairs += (G.get_edges_num()*(G.get_edges_num()-1))/2;
        edg += G.get_edges_num();

        UI len = wei.size();   /// it is necessary because &wei.size() changes after adding an edge
        UI iter_bri = 0;
        while(wei[iter_bri].weight==0){
            count_1_fails += (!check_one_bridge(G, wei[iter_bri].vertex_a, wei[iter_bri].vertex_b));
            iter_bri++;
            count_1_all++;
        }

        while(iter_bri<len){
            UI k = 1;
            if(iter_bri+k<len) {
                while (wei[iter_bri].weight == wei[iter_bri + k].weight) {
                    count_2_fails += (!check_double_bridge(G, wei[iter_bri].vertex_a, wei[iter_bri].vertex_b, wei[iter_bri + k].vertex_a,
                                                           wei[iter_bri+k].vertex_b));
                    k++;
                    count_2_all++;
                    if (iter_bri + k >= len) break;
                }
            }
            iter_bri++;
        }


    }
    cout << float(count_2_fails)/(edg_pairs-(count_2_all - count_2_fails)) << endl;
    cout << float(count_1_fails)/(edg-(count_1_all - count_1_fails)) << endl;
    cout << (float(count_2_fails)/(edg_pairs-(count_2_all - count_2_fails)) + float(count_1_fails)/(edg-(count_1_all - count_1_fails))) / 2<< endl;

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
