#ifndef LAB1_GRAPHS_ALGO_REAL_GRAPH_H
#define LAB1_GRAPHS_ALGO_REAL_GRAPH_H


vector<string> & split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    return split(s, delim, elems);
}

template <typename T>
void experiment_with_real(ofstream &f, Graph<T> & Gr){

        UI time_dfs = 0, time_rand = 0, time_radix = 0, time_bucket = 0, time_sort = 0;

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

        f << Gr.get_graph_size() << "," << Gr.get_edges_num() << ","<< time_dfs / 1000000.0 << "," << time_rand / 1000000.0 << ","
          << time_radix / 1000000.0 << "," << time_bucket / 1000000.0 << "," << time_sort / 1000000.0 << endl;

}





template <typename T>
bool create_real_graph(string filename, Graph<T> &G) {
    ifstream f(filename);
    if (!f.is_open()) return 0;
    string line;
        while (getline(f, line)){
            vector<string> spl = split(line, ',');
            vector<int> new_edge{stoi(spl[0]), stoi(spl[1])};
            G.add_edge(new_edge[0]-1, new_edge[1]-1);
        }
    f.close();
        return 1;
}


void experim_with_real(){

    ofstream out_NY("../data/NY_graph_experiments.csv");
    if (out_NY.is_open()) cout << "File is open " << endl;
    out_NY << "NumVert,NumEdges,DFS,Rand,Rand_Radix,Rand_Bucket,Rand_Sort" << endl;

    Graph<UC> NY_graph1(264346);
    create_real_graph<UC>("../data/NYgraph.csv", NY_graph1);
    experiment_with_real<UC>(out_NY, NY_graph1);

    Graph<US> NY_graph2(264346);
    create_real_graph<US>("../data/NYgraph.csv", NY_graph2);
    experiment_with_real<US>(out_NY, NY_graph2);

    Graph<UI> NY_graph3(264346);
    create_real_graph<UI>("../data/NYgraph.csv", NY_graph3);
    experiment_with_real<UI>(out_NY, NY_graph3);

    Graph<UL> NY_graph4(264346);
    create_real_graph<UL>("../data/NYgraph.csv", NY_graph4);
    experiment_with_real<UL>(out_NY, NY_graph4);

    out_NY.close();

    ofstream out_CA("../data/CA_graph_experiments.csv");
    if (out_NY.is_open()) cout << "File is open " << endl;
    out_NY << "NumVert,NumEdges,DFS,Rand,Rand_Radix,Rand_Bucket,Rand_Sort" << endl;

    Graph<UC> CA_graph1(264346);
    create_real_graph<UC>("../data/California.csv", NY_graph1);
    experiment_with_real<UC>(out_NY, NY_graph1);

    Graph<US> CA_graph2(264346);
    create_real_graph<US>("../data/California.csv", NY_graph2);
    experiment_with_real<US>(out_NY, NY_graph2);

    Graph<UI> CA_graph3(264346);
    create_real_graph<UI>("../data/California.csv", NY_graph3);
    experiment_with_real<UI>(out_NY, NY_graph3);

    Graph<UL> CA_graph4(264346);
    create_real_graph<UL>("../data/California.csv", NY_graph4);
    experiment_with_real<UL>(out_NY, NY_graph4);

    out_NY.close();

}





#endif //LAB1_GRAPHS_ALGO_REAL_GRAPH_H
