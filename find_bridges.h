
#ifndef LAB1_GRAPHS_ALGO_FIND_BRIDGES_H
#define LAB1_GRAPHS_ALGO_FIND_BRIDGES_H


/// Deterministic bridge search.
/// --------------------------------------------------------------------------------------------- ///

void DBS_algo (vector<vector<vector<UI>>> &adj,
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
            DBS_algo(adj, bridges, used, timer, tin, fup, child, current);
            fup[current] = min (fup[current], fup[child]);
            if (fup[child] > tin[current]){
                bridges.push_back(child);
                bridges.push_back(current);
            }
        }
    }
}

template <typename T>
void DBS (Graph<T> &G, vector<UI> &bridges) {
    UI N = G.get_graph_size();
    vector<bool> used(N);
    vector<UI> tin(N);
    vector<UI> fup(N);
    UI timer = 0;

    for (UI vert=0; vert<N; ++vert) {
        if (!used[vert]) {
            DBS_algo(G.get_adj_list(), bridges, used, timer, tin, fup, vert, N + 1);
        }
    }
}

/// --------------------------------------------------------------------------------------------- ///



/// Randomized bridge search.
/// --------------------------------------------------------------------------------------------- ///


template <typename T>
void RBS_algo(vector<vector<vector<UI>>> &adj,
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
            RBS_algo(adj, edges, N, used, child, current, uid);
            mark = mark ^ edges[adj[current][i][1]].weight;
        }
    }
    if (parent == N+1) return;
    edges[adj[current][parent_coord][1]].weight_flag = 1;
    edges[adj[current][parent_coord][1]].weight = mark;
}


template <typename T>
void RBS (Graph<T> &G){
    UI N = G.get_graph_size();
    vector<bool> used(N);
    uniform_int_distribution<> uid(0, numeric_limits<T>::max());

    for (UI vert=0; vert<N; vert++) {
        if (!used[vert]) {
            RBS_algo(G.get_adj_list(), G.get_edges_list(), N, used, vert, N + 1, uid);
        }
    }
}

/// --------------------------------------------------------------------------------------------- ///

#endif //LAB1_GRAPHS_ALGO_FIND_BRIDGES_H
