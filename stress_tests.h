#ifndef LAB1_GRAPHS_ALGO_STRESS_TESTS_H
#define LAB1_GRAPHS_ALGO_STRESS_TESTS_H


/// Test DBS with N=1000, M=0, 10000 iterations.
void stress_test1(ofstream &f, UI N, UI dens_index, UI iterations){
    UI M;
    switch(dens_index){
        case 1:
            M = 0;
            break;
        case 2:
            M = N/2;
            break;
        case 3:
            M = N;
            break;
        case 4:
            M = N*2;
            break;
        case 5:
            M = N*N;
            break;
    }
    UI count_fails = 0;
    UI count_all = 0;
    UI edges_num = 0;

    for (UI iter=0; iter<iterations; iter++) {
        float probabil = M/((N*(N-1))/2.);
        Graph<US> G(N);
        G.generate_rand(probabil);
        edges_num += G.get_edges_num();
        vector<UI> bridges;
        DBS(G, bridges);
        for (UI i = 0; i < bridges.size(); i+=2) {
            count_fails += (!check_one_bridge(G, bridges[i], bridges[i+1]));
            count_all++;
        }
    }
    f << N << "," << edges_num/iterations << "," << iterations << "," << count_fails << "," << count_all - count_fails << "," << count_all << endl;

};

void stress_DBS(){
    ofstream out_stress_DBS("../data/stress_DBS.csv");
    out_stress_DBS << "NumVert,MeanNumEdges,Iterations,Wrong bridges,Right bridges,All bridges" << endl;
    stress_test1(out_stress_DBS, 100, 1, 100);
    stress_test1(out_stress_DBS, 100, 2, 100);
    stress_test1(out_stress_DBS, 100, 3, 100);
    stress_test1(out_stress_DBS, 100, 4, 100);
    stress_test1(out_stress_DBS, 100, 5, 100);
    out_stress_DBS.close();
}

template <typename T>
void stress_test6(ofstream &f, UI N=100, UI dens_index=1, UI iterations=10, UI sort_index=1){    /// test rand with unsigned char type, N=1000, M=4N, 10000 iterations
    vector<string> sorts{"std::sort", "radix", "bucket"};
    UI M;
    switch(dens_index){
        case 1:
            M = N/2;
            break;
        case 2:
            M = N;
            break;
        case 3:
            M = N*2;
            break;
        case 4:
            M = N*4;
            break;
        case 5:
            M = N*N;
            break;
    }

    float probabil = M/((N*(N-1))/2.);
    UI one_bridge_fails = 0;
    UI one_bridge_all = 0;
    UI two_bridge_fails = 0;
    UI two_bridges_all = 0;
    UI edges_num = 0;
    UI edg_pairs = 0;

    for (UI iter=0; iter<iterations; iter++) {
        Graph<T> G(N);
        G.generate_rand(probabil);
        edges_num += G.get_edges_num();
        edg_pairs += (G.get_edges_num()*(G.get_edges_num()-1))/2;

        RBS(G);
        vector<EDGE<T>> &wei = G.get_edges_list();
        switch(sort_index){
            case 1:
                sort(wei.begin(), wei.end(), comp<T>);
                break;
            case 2:
                radix_sort(wei);
                break;
            case 3:
                bucket_sort(wei, wei.size() / 20 + 1);
                break;
        }


        UI len = wei.size();   /// It is necessary because &wei.size() changes after adding an edge.
        UI iter_bri = 0;
        while(wei[iter_bri].weight==0){
            one_bridge_fails += (!check_one_bridge(G, wei[iter_bri].vertex_a, wei[iter_bri].vertex_b));
            one_bridge_all++;
            iter_bri++;
        }
        while(iter_bri<len){
            UI range = 1;
            if(iter_bri+range<len) {
                while (wei[iter_bri].weight == wei[iter_bri + range].weight) {
                    two_bridge_fails += (!check_two_bridge(G, wei[iter_bri].vertex_a, wei[iter_bri].vertex_b,
                                                        wei[iter_bri + range].vertex_a,
                                                        wei[iter_bri + range].vertex_b));
                    two_bridges_all++;
                    range++;
                    if (iter_bri + range >= len) break;
                }
            }
            iter_bri++;
        }
    }

    f << N << "," << edges_num/iterations << "," << iterations << "," << sorts[sort_index-1] << "," << sizeof(T)*8 << ","
    << one_bridge_fails << "," << one_bridge_all - one_bridge_fails << "," << two_bridge_fails << "," << two_bridges_all - two_bridge_fails
    << "," << float(one_bridge_fails)/(edges_num - (one_bridge_all - one_bridge_fails)) << ","
    << float(two_bridge_fails)/(edg_pairs - (two_bridges_all - two_bridge_fails)) << "," << pow(0.5, sizeof(T)*8) << endl;

};


void stress_RBS(){
    ofstream out_stress_RBS("../data/stress_RBS.csv");
    out_stress_RBS << "NumVert,MeanNumEdg,Iter,Sort,Type(bits),Wrong 1-br,Right 1-br,Wrong 2-br,"
                      "Right 2-br,Wrong 1-br/(NumEdg-Right 1-br),Wrong 2-br/(All pairs-Right 2-br),1/2^bits"
                       << endl;
    stress_test6<UC>(out_stress_RBS, 10, 2, 10, 1);
    stress_test6<UC>(out_stress_RBS, 10, 2, 10, 2);
    stress_test6<UC>(out_stress_RBS, 10, 4, 10, 3);
    stress_test6<US>(out_stress_RBS, 10, 2, 10, 1);
    stress_test6<US>(out_stress_RBS, 10, 4, 10, 2);
    stress_test6<US>(out_stress_RBS, 10, 4, 10, 3);
    stress_test6<UI>(out_stress_RBS, 10, 2, 10, 1);
    stress_test6<UI>(out_stress_RBS, 10, 4, 10, 2);
    stress_test6<UI>(out_stress_RBS, 10, 4, 10, 3);
    stress_test6<UL>(out_stress_RBS, 10, 2, 10, 1);
    stress_test6<UL>(out_stress_RBS, 10, 4, 10, 2);
    stress_test6<UL>(out_stress_RBS, 10, 4, 10, 3);
    out_stress_RBS.close();
}



#endif //LAB1_GRAPHS_ALGO_STRESS_TESTS_H
