
#ifndef LAB1_GRAPHS_ALGO_CHECK_BRIDGE_H
#define LAB1_GRAPHS_ALGO_CHECK_BRIDGE_H

void dfs_connected (UI &current, vector<vector<vector<UI>>> & adj, vector<bool> &used, vector<UI> &comp) {
    used[current] = 1;
    comp.push_back(current);
    for (UI i=0; i<adj[current].size(); ++i) {
        UI child = adj[current][i][0];
        if (!used[child])
            dfs_connected (child, adj, used, comp);
    }
}

UI connect_comp(Graph &G) {    //return amount of connected components
    UI N = G.get_graph_size();
    UI comp_amount = 0;
    vector<bool> used(N);
    vector<UI> comp;
    for (UI vert=0; vert<N; ++vert)
        if (! used[vert]) {
            comp_amount++;
            comp.clear();
            dfs_connected (vert, G.get_adj_list(), used, comp);

            /*cout << "Component:";
            for (size_t j=0; j<comp.size(); ++j)
                cout << ' ' << comp[j];
            cout << endl;*/
        }
    return comp_amount;
}

bool check_one_bridge(Graph &G, UI a, UI b){    //check a-b bridge
    UI fir_amount_comp = connect_comp(G);
    G.delete_edge(a, b);
    UI last_amount_comp = connect_comp(G);
    G.add_edge(a, b);
    return last_amount_comp == (fir_amount_comp + 1);
}

bool check_double_bridge(Graph &G, UI a, UI b, UI c, UI d){
    UI fir_amount_comp = connect_comp(G);
    G.delete_edge(a, b);
    G.delete_edge(c, d);
    UI last_amount_comp = connect_comp(G);
    G.add_edge(a, b);
    G.add_edge(c, d);
    return last_amount_comp == (fir_amount_comp + 1);
}

#endif //LAB1_GRAPHS_ALGO_CHECK_BRIDGE_H
