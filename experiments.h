
#ifndef LAB1_GRAPHS_ALGO_EXPERIMENTS_H
#define LAB1_GRAPHS_ALGO_EXPERIMENTS_H


template <typename T>
void experim(ofstream &f, UI iter, UI step, UI aver, UI power, UI coef){
    UI N = 0;
    for (UI i=0; i<iter; i++){    //loop for N (10-1000)

        UI M = pow(N/2, power)  * coef;
        float p = M/((N*(N-1))/2.);
        UI time_dfs = 0, time_rand = 0, time_radix = 0, time_bucket = 0, time_sort = 0;

        for (UI j=0; j<aver; j++) { //loop for average time
            Graph<T> Gr(N);
            Gr.generate_rand(p);

            UI start_time = clock();
            vector<UI> bri;
            DBS(Gr, bri);
            time_dfs += (clock() - start_time);

            start_time = clock();
            RBS(Gr);
            time_rand += (clock() - start_time);

            vector<EDGE<T>> wei1 = Gr.get_edges_list();
            vector<EDGE<T>> wei2 = wei1;
            vector<EDGE<T>> wei3 = wei1;

            start_time = clock();
            if (wei1.size()) radix_sort(wei1);
            time_radix += (clock() - start_time) + time_rand;

            start_time = clock();
            if (wei2.size()) bucket_sort(wei2, wei2.size() / 20 + 1);
            time_bucket += (clock() - start_time) + time_rand;

            start_time = clock();
            if (wei3.size()) sort(wei3.begin(), wei3.end(), comp<T>);
            time_sort += (clock() - start_time) + time_rand;
        }

        f << N << "," << M << ","<< time_dfs / aver*1000000.0 << "," << time_rand / aver*1000000.0 << "," << time_radix / aver*1000000.0 << "," << time_bucket / aver*1000000.0 << "," << time_sort / aver*1000000.0 <<  endl;
        N += step;
    }
}

template <typename T>
bool do_experim(string file_name, UI iter, UI step, UI aver){
    ofstream out(file_name);
    if (!out.is_open()) return 0;
    cout << "File is open " << endl;
    out << "NumVert,NumEdges,DFS,Rand,Rand_Radix,Rand_Bucket,Rand_Sort" << endl;
    vector<pair<UI, UI>> coef{pair<UI,UI>{1,1}, pair<UI,UI>{1,2}, pair<UI,UI>{1,16}, pair<UI,UI>{2,1}};     //sorry for that naming, I cant create anymore
    /// Vector coef is necessary for edges amount (M=N/2, M=N, M=8N, M=(N/2)^2)

    for (UI i=0; i<coef.size(); i++) {
        experim<T>(out, iter, step, aver, coef[i].first, coef[i].second);
    }
    out.close();
    return 1;
}

#endif //LAB1_GRAPHS_ALGO_EXPERIMENTS_H
