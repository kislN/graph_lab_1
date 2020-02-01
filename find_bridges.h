
#ifndef LAB1_GRAPHS_ALGO_FIND_BRIDGES_H
#define LAB1_GRAPHS_ALGO_FIND_BRIDGES_H

void dfs_bridges (  vector<vector<vector<UI>>> &adj,
                    vector<UI>  &bridges,
                    vector<bool> &used,
                    UI &timer,
                    vector<UI> &tin,
                    vector<UI> &fup,
                    UI &current,
                    UI parent )
{
    used[current] = 1;
    tin[current] = fup[current] = timer++;
    for (UI i=0; i<adj[current].size(); ++i) {
        UI child = adj[current][i][0];
        if (child == parent)  continue;
        if (used[child]) {
            fup[current] = min(fup[current], tin[child]);
        }
        else {
            dfs_bridges (adj, bridges, used, timer, tin, fup, child, current);
            fup[current] = min (fup[current], fup[child]);
            if (fup[child] > tin[current]){
                bridges.push_back(child);
                bridges.push_back(current);
            }
        }
    }
}

template <typename T>
void find_dfs_bridges(Graph<T> &G, vector<UI> &bridges) {
    UI N = G.get_graph_size();
    vector<bool> used(N);
    vector<UI> tin(N);
    vector<UI> fup(N);
    UI timer = 0;

    for (UI vert=0; vert<N; ++vert) {
        if (!used[vert]) {
            dfs_bridges(G.get_adj_list(), bridges, used, timer, tin, fup, vert, N + 1);
        }
    }
}

template <typename T>
void rand_bridges(  vector<vector<vector<UI>>> &adj,
                    vector<EDGE<T>> &edges,
                    const UI &N,
                    vector<bool> &used,
                    const UI &current,
                    const UI &parent,
                    uniform_int_distribution<> &uid)
{
    used[current] = 1;
    T mark = 0;
    UI parent_coord;
    for (UI i=0; i<adj[current].size(); i++){
        UI child = adj[current][i][0];
        if (child == parent) {
            parent_coord = i;
            continue;
        }
        if (used[child]) {
            if (!edges[adj[current][i][1]].weight_flag){
                edges[adj[current][i][1]].weight_flag = 1;
//                edges[adj[current][i][1]].weight = rand() % 4294967296;
              edges[adj[current][i][1]].weight = uid(gen);
            }
            mark = mark ^ edges[adj[current][i][1]].weight;
        }
        else{
            rand_bridges(adj, edges, N, used, child, current, uid);
            mark = mark ^ edges[adj[current][i][1]].weight;
        }
    }
    if (parent == N+1) return;
    edges[adj[current][parent_coord][1]].weight_flag = 1;
    edges[adj[current][parent_coord][1]].weight = mark;
}


template <typename T>
void find_rand_bridges(Graph<T> &G){
    UI N = G.get_graph_size();
    vector<bool> used(N);
    uniform_int_distribution<> uid(0, numeric_limits<T>::max());
    for (UI current=0; current<N; current++) {
        if (!used[current]) {
            rand_bridges(G.get_adj_list(), G.get_edges_list(), N, used, current, N + 1, uid);
        }
    }
}





#endif //LAB1_GRAPHS_ALGO_FIND_BRIDGES_H
