#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <ctime>
#include <random>
#include <stdint.h>

#ifndef LAB1_GRAPHS_ALGO_GRAPH_H
#define LAB1_GRAPHS_ALGO_GRAPH_H

typedef uint64_t UL;        // 8 bytes [0; 18 446 744 073 709 551 615]
typedef unsigned int UI;    // 4 bytes [0; 4 294 967 295]
typedef unsigned short US;  // 2 bytes [0; 65 535]
typedef uint8_t UC;         // 1 byte [0; 255] don't print because it's a character type (like unsigned char)
using namespace std;

UI tolerance = 100000000;

mt19937 gen(time(0));   /// Mersenne twister
uniform_int_distribution<> uid(0, tolerance-1);

template <class T>
struct EDGE{
    UI vertex_a;
    UI vertex_b;
    T weight;
    bool weight_flag;   //  It changes after defining random weight.
};

template <typename T>
class Graph {
private:
    UI graph_size;
    UI edges_num;
    float edges_density;
    vector<EDGE<T>> edges_list;             // List of edges where edge (a,b) == edge (b,a).
    vector<vector<vector<UI>>> adj_list;    // Adjacency list includes all vertexes,
                                            // each vertex A has list of pairs (B, index)
                                            // where (A,B) is the edge of graph and
                                            // index is the index of this edge in edges_list.
public:
    Graph(UI num){
        graph_size = num;
        edges_num = 0;
        edges_density = 0;
        for (UI i=0; i<graph_size; i++){
            adj_list.push_back(vector<vector<UI>>{});
        }
    }

    void generate_rand(float probabil){
        UI p = probabil * tolerance;
        for(UI i=0; i<graph_size; i++){
            for(UI j=i+1; j<graph_size; j++){
//                if (p > (rand() % tolerance)) {
                if (p > (uid(gen))){
                    EDGE<T> edge;
                    edge.vertex_a = i;
                    edge.vertex_b = j;
                    edge.weight_flag = 0;
                    edges_list.push_back(edge);
                    adj_list[i].push_back(vector<UI>{j, edges_num});
                    adj_list[j].push_back(vector<UI>{i, edges_num});
                    edges_num++;
                }
            }
        }
        edges_density = edges_num / ((graph_size * (graph_size - 1)) / 2.);
    }

    bool add_edge(UI a, UI b){
        if((a==b) || (a>=graph_size) || (b>=graph_size)) return 0;
        for (UI i; i<adj_list[a].size(); i++) {
            if (b == adj_list[a][i][0]) return 0;
        }
        EDGE<T> edge;
        edge.vertex_a = min(a, b);
        edge.vertex_b = max(a, b);
        edge.weight_flag = 0;
        edges_list.push_back(edge);
        adj_list[a].push_back(vector<UI>{b, edges_num});
        adj_list[b].push_back(vector<UI>{a, edges_num});
        edges_num++;
        edges_density = edges_num / ((graph_size * (graph_size - 1)) / 2.);
        return 1;
    }


    void delete_edge(UI a, UI b){
    /// ATTENTION
    /// if we delete edge we should change all indexes which connect adj_list and edges_list
    /// but we don't do that because it is expensive operation and it isn't necessary for us
    /// that's why we can't use find_rand_bridges after deleting any edges
        for (UI i=0; i<adj_list[a].size(); i++){
            if (b == adj_list[a][i][0]) {
//                edges_list.erase(edges_list.begin() + adj_list[a][i][1]);
                adj_list[a].erase(adj_list[a].begin()+i);
                break;

            }
        }
        for (UI i=0; i<adj_list[b].size(); i++){
            if (a == adj_list[b][i][0]) {
                adj_list[b].erase(adj_list[b].begin() + i);
                break;
            }
        }
        edges_num--;
        edges_density = edges_num / ((graph_size * (graph_size - 1)) / 2.);
    }

    UI get_edges_num(){
        return edges_num;
    }

    UI get_graph_size(){
        return graph_size;
    }

    float get_edges_dens(){
        return edges_density;
    }

    vector<vector<vector<UI>>> & get_adj_list(){
        return adj_list;
    }

    vector<EDGE<T>> & get_edges_list(){
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

//               copy(edges_list[i].begin(), edges_list[i].end(), ostream_iterator<UI>(cout," "));
                cout << edges_list[i].edge_a << " - " << edges_list[i].edge_b << ": " << edges_list[i].weight << " " << edges_list[i].weight_flag << endl;
//                cout << endl;
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
