
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
//                cout << child << " - " << current << endl;
            }
        }
    }
}

void find_dfs_bridges(Graph &G, vector<UI> &bridges) {
    UI N = G.get_graph_size();
    vector<bool> used(N);
    vector<UI> tin(N);
    vector<UI> fup(N);
    UI timer = 0;
    for (UI i=0; i<N; ++i) {
        if (!used[i]) {
            dfs_bridges(G.get_adj_list(), bridges, used, timer, tin, fup, i, N + 1);
        }
    }
}

void rand_bridges(  vector<vector<vector<UI>>> &adj,
                    vector<vector<UI>> &edges,
                    const UI &N,
                    vector<bool> &used,
                    const UI &current,
                    const UI &parent )
{
    used[current] = 1;
    UI mark = 0;
    UI parent_coord;
    for (UI i=0; i<adj[current].size(); i++){
        UI child = adj[current][i][0];
        if (child == parent) {
            parent_coord = i;
            continue;
        }
        if (used[child]) {
            if (edges[adj[current][i][1]].size() < 3){
                UI r = rand() % 2147483647;
                edges[adj[current][i][1]].push_back(r);
            }
            mark = mark ^ edges[adj[current][i][1]][2];
        }
        else{
            rand_bridges(adj, edges, N, used, child, current);
            mark = mark ^ edges[adj[current][i][1]][2];
        }
    }
    if (parent == N+1) return;
    if (edges[adj[current][parent_coord][1]].size() < 3) {
        edges[adj[current][parent_coord][1]].push_back(mark);
    }
    else {
        edges[adj[current][parent_coord][1]][2] = mark;
    }
}

void find_rand_bridges(Graph &G){
    UI N = G.get_graph_size();
    vector<bool> used(N);

    for (UI current=0; current<N; current++) {
        if (!used[current]) {
            rand_bridges(G.get_adj_list(), G.get_edges_list(), N, used, current, N + 1);
        }
    }
}

#endif //LAB1_GRAPHS_ALGO_FIND_BRIDGES_H
