
#ifndef LAB1_GRAPHS_ALGO_FIND_BRIDGES_H
#define LAB1_GRAPHS_ALGO_FIND_BRIDGES_H

void dfs_bridges (  vector<vector<UI>> *adj,
                    vector<vector<UI>>  &bridges,
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
        UI child = (*adj)[current][i];
        if (child == parent)  continue;
        if (used[child])
            fup[current] = min (fup[current], tin[child]);
        else {
            dfs_bridges (adj, bridges, used, timer, tin, fup, child, current);
            fup[current] = min (fup[current], fup[child]);
            if (fup[child] > tin[current]){
                vector<UI> br_vec;
                br_vec.push_back(child);
                br_vec.push_back(current);
                bridges.push_back(br_vec);
//                cout << child << " - " << current << endl;
            }
        }
    }
}

vector<vector<UI>> find_dfs_bridges(Graph &G) {
    UI N = G.get_graph_size();
    vector<vector<UI>> bridges;
    vector<bool> used(N);
    vector<UI> tin(N);
    vector<UI> fup(N);
    UI timer = 0;
    for (UI i=0; i<N; ++i) {
        if (!used[i])
            dfs_bridges(G.get_adj_list(), bridges, used, timer, tin, fup, i, N+1);
    }
    return bridges;

}

void rand_bridges(  vector<vector<UI>> *adj,
                    const UI &N,
                    vector<bool> &used,
                    vector<vector<bool>> &used_weights,
                    vector<vector<UI>> &mark_list,
                    const UI &current,
                    const UI &parent )
{
    used[current] = 1;
    UI mark = 0;
    for (UI i=0; i<(*adj)[current].size(); i++){
        UI child = (*adj)[current][i];
        if (child == parent) continue;
        if (used[child]) {
            if (!used_weights[current][child]){
                used_weights[current][child] = used_weights[child][current] = 1;
                mark_list[current][child] = mark_list[child][current] = rand() % 2147483647;    //uid(gen)
            }
            mark = mark ^ mark_list[current][child];
        }
        else{
            rand_bridges(adj, N, used, used_weights, mark_list, child, current);
            mark = mark ^ mark_list[current][child];
        }
    }
    if (parent == N+1) return;
    mark_list[current][parent] = mark_list[parent][current] = mark;
    used_weights[current][parent] = used_weights[parent][current] = 1;
}

void find_rand_bridges(Graph &G, vector<vector<UI>> &list_weights){
    UI N = G.get_graph_size();
    vector<bool> used(N);
    vector<vector<bool>> used_weights;
    vector<vector<UI>> mark_list;
    for (UI i=0; i<N; i++){
        vector<UI> vec1;
        vector<bool> vec2;
        mark_list.push_back(vec1);
        used_weights.push_back(vec2);
        for (UI j=0; j<N; j++){
            used_weights[i].push_back(0);
            mark_list[i].push_back(0);            // what should I do with -1 in marks ???
        }
    }

    for (UI current=0; current<N; current++) {
        if (!used[current]) {
            rand_bridges(G.get_adj_list(), N, used, used_weights, mark_list, current, N + 1);
        }
    }

    for (UI i = 0; i < N; i++) {
        for (UI j = i + 1; j < N; j++) {
            if (used_weights[i][j] == 1){
                vector<UI> weight{i, j, mark_list[i][j]};
                list_weights.push_back(weight);
            }
//            if ((mark_list[i][j] == 0) && (used_weights[i][j] == 1)) cout << i << " - " << j << endl;
        }
    }
//    return &list_weights;
}

#endif //LAB1_GRAPHS_ALGO_FIND_BRIDGES_H
