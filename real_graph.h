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
bool create_NY_graph(Graph<T> &G) {
    ifstream f("NYgraph.csv");
    if (!f.is_open()) return 0;
    else{
        string line;
        while (getline(f, line)){
            vector<string> spl = split(line, ',');
            vector<int> c{stoi(spl[0]), stoi(spl[1])};
            G.add_edge(c[0]-1, c[1]-1);
        }
    }
    f.close();
    return 1;
}

#endif //LAB1_GRAPHS_ALGO_REAL_GRAPH_H
