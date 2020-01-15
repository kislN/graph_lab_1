
#ifndef LAB1_GRAPHS_ALGO_FIND_BRIDGES_H
#define LAB1_GRAPHS_ALGO_FIND_BRIDGES_H


void dfs_bridges (  vector<vector<vector<UI>>> *adj,
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
    for (UI i=0; i<(*adj)[current].size(); ++i) {
        UI child = (*adj)[current][i][0];
        if (child == parent)  continue;
        if (used[child]) {
            fup[current] = min(fup[current], tin[child]);
        }
        else {
            dfs_bridges (adj, bridges, used, timer, tin, fup, child, current);
            fup[current] = min (fup[current], fup[child]);
//            if (fup[child] > tin[current]){
//                bridges.push_back(child);
//                bridges.push_back(current);
////                cout << child << " - " << current << endl;
//            }
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

void rand_bridges(  vector<vector<vector<UI>>> *adj,
                    const UI &N,
                    vector<bool> &used,
                    const UI &current,
                    const UI &parent )
{
    used[current] = 1;
    UI mark = 0;
    UI parent_coord;
    for (UI i=0; i<(*adj)[current].size(); i++){
        UI child = (*adj)[current][i][0];
        if (child == parent) {
            parent_coord = i;
            continue;
        }
        if (used[child]) {
            if ((*adj)[current][i].size() < 3){
                UI r = rand() % 2147483647;
                (*adj)[current][i].push_back(r);
                (*adj)[child][(*adj)[current][i][1]].push_back(r);
            }
            mark = mark ^ (*adj)[current][i][2];
        }
        else{
            rand_bridges(adj, N, used, child, current);
            mark = mark ^ (*adj)[current][i][2];
        }
    }
    if (parent == N+1) return;
    if ((*adj)[current][parent_coord].size() < 3) {
        (*adj)[current][parent_coord].push_back(mark);
        (*adj)[parent][(*adj)[current][parent_coord][1]].push_back(mark);
    }
    else {
        (*adj)[current][parent_coord][3] = mark;
        (*adj)[parent][(*adj)[current][parent_coord][1]][3] = mark;
    }
}

void find_rand_bridges(Graph &G){
    UI N = G.get_graph_size();
    vector<bool> used(N);

    for (UI current=0; current<N; current++) {
        if (!used[current]) {
            rand_bridges(G.get_adj_list(), N, used, current, N + 1);
        }
    }
//
//    for (UI i = 0; i < N; i++) {
//        for (UI j = i + 1; j < N; j++) {
//            if (used_weights[i][j] == 1){
//                vector<UI> weight{i, j, mark_list[i][j]};
//                list_weights.push_back(weight);
//            }
////            if ((mark_list[i][j] == 0) && (used_weights[i][j] == 1)) cout << i << " - " << j << endl;
//        }
//    }
//    return &list_weights;
}

#endif //LAB1_GRAPHS_ALGO_FIND_BRIDGES_H
