
#ifndef LAB1_GRAPHS_ALGO_GRAPH_H
#define LAB1_GRAPHS_ALGO_GRAPH_H

using namespace std;

typedef unsigned int UI;  // 4 bytes [0; 4 294 967 295]

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

    UI get_graph_size(){
        return graph_size;
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


#endif //LAB1_GRAPHS_ALGO_GRAPH_H
