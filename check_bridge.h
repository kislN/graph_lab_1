
#ifndef LAB1_GRAPHS_ALGO_CHECK_BRIDGE_H
#define LAB1_GRAPHS_ALGO_CHECK_BRIDGE_H

void dfs_connected ( UI &current,
                     vector<vector<vector<UI>>> & adj,
                     vector<bool> &used,
                     vector<UI> &comp )
{
    used[current] = 1;
    comp.push_back(current);
    for (UI i=0; i<adj[current].size(); ++i) {
        UI child = adj[current][i][0];
        if (!used[child])
            dfs_connected (child, adj, used, comp);
    }
}

template <typename T>
UI connected_comp_num(Graph<T> &G) {    // Return amount of connected components.
    UI N = G.get_graph_size();
    UI comp_amount = 0;
    vector<bool> used(N);
    vector<UI> comp;
    for (UI vert=0; vert<N; vert++)
        if (! used[vert]) {
            comp_amount++;
            comp.clear();
            dfs_connected (vert, G.get_adj_list(), used, comp);
        }
    return comp_amount;
}

template <typename T>
bool check_one_bridge(Graph<T> &G, UI a, UI b) {    // Check a-b is bridge.
    UI start_amount_comp = connected_comp_num(G);
    G.delete_edge(a, b);
    UI last_amount_comp = connected_comp_num(G);
    G.add_edge(a, b);
    return last_amount_comp == (start_amount_comp + 1);
}

template <typename T>
bool check_two_bridge(Graph<T> &G, UI a, UI b, UI c, UI d) {    // Check {a-b, c-d} is two-bridge.
    UI start_amount_comp = connected_comp_num(G);
    G.delete_edge(a, b);
    G.delete_edge(c, d);
    UI last_amount_comp = connected_comp_num(G);
    G.add_edge(a, b);
    G.add_edge(c, d);
    return last_amount_comp == (start_amount_comp + 1);
}

#endif //LAB1_GRAPHS_ALGO_CHECK_BRIDGE_H
