#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <ctime>
#include <random>
#include <algorithm>


using namespace std;

typedef unsigned int UI;  // 4 bytes [0; 4 294 967 295]
typedef unsigned short US;  // 2 bytes [0; 65 535]

const UI N = 10;  //number of nodes
bool used[N];
UI timer, tin[N], fup[N];
vector<UI> comp;
//vector<set<UI>> bridges;

mt19937 gen(time(0));
uniform_int_distribution<> uid(0, 9999);

class Graph {
private:
    UI graph_size;
    UI edges_num;
    float edges_dens;
    vector<vector<UI>> adj_list;
public:
    Graph(UI num){
        graph_size = num;
        edges_num = 0;
        edges_dens = 0;
        for (int i=0; i<graph_size; i++){
            vector<UI> vec;
            adj_list.push_back(vec);
        }
    }

    void generate_rand(float probabil){
        UI tolerance = 100000;
        UI p = probabil * tolerance;
        for(UI i=0; i<graph_size; i++){
            for(UI j=i+1; j<graph_size; j++){
                if (p > (rand() % tolerance)) {
//                if (p > (uid(gen))){
                    adj_list[i].push_back(j);
                    adj_list[j].push_back(i);
                    edges_num++;
                }
            }
        }
        edges_dens = edges_num / ((graph_size * (graph_size - 1)) / 2.);
    }

    bool add_edge(UI a, UI b){
        for (UI i; i<adj_list[a].size(); i++) {
            if (b == adj_list[a][i]) return 0;
        }
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
        edges_num++;
        edges_dens = edges_num / ((graph_size * (graph_size - 1)) / 2.);
        return 1;
    }

    void delete_edge(UI a, UI b){
        for (UI i=0; i<adj_list[a].size(); i++){
            if (b == adj_list[a][i]) adj_list[a].erase(adj_list[a].begin()+i);
        }
        for (UI i=0; i<adj_list[b].size(); i++){
            if (a == adj_list[b][i]) adj_list[b].erase(adj_list[b].begin()+i);
        }
        edges_num--;
        edges_dens = edges_num / ((graph_size * (graph_size - 1)) / 2.);
    }

    UI get_edges_num(){
        return edges_num;
    }

    float get_edges_dens(){
        return edges_dens;
    }

    vector<vector<UI>> * get_adj_list(){
        return &adj_list;
    }

    bool is_empty(){
        for (UI i=0; i<graph_size; i++){
            if (!adj_list[i].empty())
                return 0;
        }
        return 1;
    }

    void print_adj_list(){
        if (this->is_empty())
            cout << "List is empty" << endl;
        else
            for (UI i=0; i<graph_size; i++){
                cout << "vert: " << i << ": ";
                copy(adj_list[i].begin(), adj_list[i].end(), ostream_iterator<int>(cout," "));
                cout << endl;
            }
    }
};

void dfs_connected (UI current, vector<vector<UI>> * adj) {
    used[current] = true;
    comp.push_back (current);
    for (UI i=0; i<(*adj)[current].size(); ++i) {
        UI child = (*adj)[current][i];
        if (! used[child])
            dfs_connected (child, adj);
    }
}

UI connect_comp(Graph &G) {    //return amount of connected components
    UI comp_amount = 0;
    for (UI i=0; i<N; ++i)
        used[i] = false;
    for (UI i=0; i<N; ++i)
        if (! used[i]) {
            comp_amount++;
            comp.clear();
            dfs_connected (i, G.get_adj_list());

            /*cout << "Component:";
            for (size_t j=0; j<comp.size(); ++j)
                cout << ' ' << comp[j];
            cout << endl;*/
        }
    return comp_amount;
}

bool check_bridge(Graph &G, UI a, UI b){    //check a-b bridge
    UI fir_amount_comp = connect_comp(G);
    G.delete_edge(a, b);
    UI last_amount_comp = connect_comp(G);
    return last_amount_comp == (fir_amount_comp + 1);
}

void dfs_bridges (vector<vector<UI>> * adj, vector<vector<UI>> * bridges, vector<bool> * used, UI current, int parent=-1) {
    (*used)[current] = true;
    tin[current] = fup[current] = timer++;
    for (UI i=0; i<(*adj)[current].size(); ++i) {
        UI child = (*adj)[current][i];
        if (child == parent)  continue;
        if ((*used)[child])
            fup[current] = min (fup[current], tin[child]);
        else {
            dfs_bridges (adj, bridges, used, child, current);
            fup[current] = min (fup[current], fup[child]);
            if (fup[child] > tin[current]){
                vector<UI> br_set;
                br_set.push_back(child);
                br_set.push_back(current);
                (*bridges).push_back(br_set);
                cout << child << " - " << current << endl;
            }
        }
    }
}

vector<vector<UI>> find_dfs_bridges(Graph * G, UI N) {
    vector<vector<UI>> bridges;
    vector<bool> used;
    timer = 0;
    for (UI i=0; i<N; ++i)
        used.push_back(false);
    for (UI i=0; i<N; ++i) {
        if (!used[i])
            dfs_bridges(G->get_adj_list(), &bridges, &used, i);
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

vector<vector<UI>> * find_rand_bridges(Graph &G, const UI &N){
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

    vector<vector<UI>> list_weights;

    for (UI i = 0; i < N; i++) {
        for (UI j = i + 1; j < N; j++) {
            if (used_weights[i][j] == 1){
                vector<UI> weight{i, j, mark_list[i][j]};
                list_weights.push_back(weight);
            }
            if ((mark_list[i][j] == 0) && (used_weights[i][j] == 1)) cout << i << " - " << j << endl;
        }
    }
    return &list_weights;
}

void radix_sort(vector<int> * vec, vector<int> output, size_t n){
    for (int i=0; i<4; i++){
        int count[256] = {0};
        int k = i * 8;
        for (int j = 0; j < n; j++)
        {
            count[static_cast<uint8_t>(((*vec)[j] & (0xff << k)) >> k )]++;
        }

        for (int j = 1; j < 256; j++)
            count[j] += count[j - 1];

        for (int j = n - 1; j >= 0; j--)
        {
            uint8_t a = static_cast<uint8_t>(((*vec)[j] & (0xff << k)) >> k );
            output[count[a] - 1] = (*vec)[j];
            count[a]--;
        }

        for (int j = 0; j < n; j++)
            (*vec)[j] = output[j];
    }
}

#include <cmath>


int main() {
    UI M = 10;
    Graph Gr(M);
    Gr.generate_rand(0.2);
    vector<vector<UI>> * pnt = find_rand_bridges(Gr, M);
//    for (UI i=0; i<(*pnt).size(); i++){
//
//    }
    find_dfs_bridges(&Gr, M);
    Gr.print_adj_list();



//    cout << "start" << endl;
//    vector<float> density;
//    vector<float> times;
//    float a = 100.;
//    for (float i=0; i<100; i+=5){
//        density.push_back(i/a);
//    }
//    copy(density.begin(), density.end(), ostream_iterator<float>(cout," "));
//    UI start_time;
//    UI M = 6000;
//    for (UI i=0; i<density.size(); i++) {
//        start_time = clock();
//        Graph G(M);
//        G.generate_rand(density[i]);
//        vector<int> marks = find_rand_bridges(&G, M);
//        sort(marks.begin(), marks.end());
//        times.push_back((clock() - start_time) / 1000000.0 );
//    }

//    Graph G(M);
//    G.generate_rand(0.03);
//
//    start_time = clock();
//    vector<int> marks = find_rand_bridges(&G, M);
//    sort(marks.begin(), marks.end());
//    cout << "\n" << (clock() - start_time) / 1000000.0  << endl;
//
//    start_time = clock();
//    vector<int> marks1 = find_rand_bridges(&G, M);
//    cout << endl;
//    radix_sort(&marks1, marks1, marks1.size());
//    cout << "\n" << (clock() - start_time) / 1000000.0  << endl;

//    start_time = clock();
//    //G.print_adj_list();
//    //cout << "edg: " << G.get_edges_num() << endl;
//    cout << connect_comp(&G) << endl;
//    cout << "done too" << endl;
//    cout << (clock() - start_time)/1000000.0 << endl;
//    start_time = clock();
//    //G.add_edge(4,1);
//    //G.print_adj_list();
//    //connect_comp(&G);
//   // find_dfs_bridges(&G);
//    find_rand_bridges(&G);
//
//    cout << "research is done" << endl;
//    cout << (clock() - start_time)/1000000.0 << endl;
//    start_time = clock();
//    cout << "k " << k << endl;
//    for (int i=0; i<N; i++){
//        for (int j=i+1; j<N; j++){
//            if (mark_list[i][j] == 0)
//                cout << check_bridge(&G, i, j) << endl;
//        }
//    }
//    cout << (clock() - start_time)/1000000.0 << endl;
//    cout << "runtime = " << clock()/1000000.0 << endl;
//    return 0;
}