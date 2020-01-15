
#ifndef LAB1_GRAPHS_ALGO_GRAPH_H
#define LAB1_GRAPHS_ALGO_GRAPH_H

using namespace std;

typedef unsigned int UI;  // 4 bytes [0; 4 294 967 295]

class Graph {
private:
    UI graph_size;
    UI edges_num;
    float edges_dens;
    vector<vector<UI>> edges_list;
    vector<vector<vector<UI>>> adj_list;
public:
    Graph(UI num){
        graph_size = num;
        edges_num = 0;
        edges_dens = 0;
        for (int i=0; i<graph_size; i++){
            vector<vector<UI>> vec;
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
                    edges_list.push_back(vector<UI>{i, j});
                    adj_list[i].push_back(vector<UI>{j, edges_num});
                    adj_list[j].push_back(vector<UI>{i, edges_num});
                    edges_num++;
                }
            }
        }
        edges_dens = edges_num / ((graph_size * (graph_size - 1)) / 2.);
    }

    bool add_edge(UI a, UI b){
        if((a==b) || (a>=graph_size) || (b>=graph_size)) return 0;
        for (UI i; i<adj_list[a].size(); i++) {
            if (b == adj_list[a][i][0]) return 0;
        }
        edges_list.push_back(vector<UI>{min(a,b), max(a,b)});                         //// ATTENTION we dont add edge to edges_list
                                                                                        //// because we didnt remove edge from
        adj_list[a].push_back(vector<UI>{b, edges_num});
        adj_list[b].push_back(vector<UI>{a, edges_num});
        edges_num++;
        edges_dens = edges_num / ((graph_size * (graph_size - 1)) / 2.);
        return 1;
    }

    void delete_edge(UI a, UI b){
        for (UI i=0; i<adj_list[a].size(); i++){
            if (b == adj_list[a][i][0]) {
                edges_list.erase(edges_list.begin() + adj_list[a][i][1]);
                adj_list[a].erase(adj_list[a].begin()+i);

            }
        }
        for (UI i=0; i<adj_list[b].size(); i++){
            if (a == adj_list[b][i][0]) adj_list[b].erase(adj_list[b].begin()+i);
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

    vector<vector<vector<UI>>> & get_adj_list(){
        return adj_list;
    }

    vector<vector<UI>> & get_edges_list(){
        return edges_list;
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
                cout << "vert " << i << ": ";
//                copy(adj_list[i].begin(), adj_list[i].end(), ostream_iterator<UI>(cout," "));
                for(UI j=0; j<adj_list[i].size(); j++){
                    cout << adj_list[i][j][0] << " " ;
                }
                cout << endl;
            }
    }

    void print_edges_list(){
        if (this->is_empty())
            cout << "List is empty" << endl;
        else {
            for (UI i=0; i<edges_num; i++){
               copy(edges_list[i].begin(), edges_list[i].end(), ostream_iterator<UI>(cout," "));
               cout << endl;
            }
        }
    }

    void print_adj_with_index(){
        if (this->is_empty())
            cout << "List is empty" << endl;
        else
            for (UI i=0; i<graph_size; i++){
                cout << "vert " << i << ": ";
//                copy(adj_list[i].begin(), adj_list[i].end(), ostream_iterator<UI>(cout," "));
                for(UI j=0; j<adj_list[i].size(); j++){
                    cout << "(" << adj_list[i][j][0] << ", " << adj_list[i][j][1] << ") " ;
                }
                cout << endl;
            }
    }
};


#endif //LAB1_GRAPHS_ALGO_GRAPH_H
