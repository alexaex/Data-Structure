#ifndef CONTAINER_GRAPH_H
#define CONTAINER_GRAPH_H
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

constexpr int INF = 0x3f3f3f;

namespace container {

    template<typename T, size_t Capacity>
    struct adj_mat {
        T data[Capacity];
        int edges[Capacity][Capacity];
        int v;
        int e;
        void create_adj_mat() {
            std::cin >> this->v >> this->e;
            int i, j, u, w;
            for (i = 0; i < v; i++)
                std::cin >> data[i];
            for (i = 0; i < v; i++)
                for (j = 0; j < v; j++)
                    edges[i][j] = INF;
            for (i = 0; i < e; i++)
                std::cin >> u >> j >> w;
            edges[u][j] = w;
            edges[j][u] = w;
        }
    };

    struct vertex {
        int u;
        int w;
        vertex* next;
        vertex(int i = 0, int weight = 0) :u(i), w(weight), next(nullptr) {};
    };

    template<typename T, size_t Capacity>
    struct adj_linked_list_node {
        T storage[Capacity];
        vertex* edges[Capacity];
        int v, e;
        adj_linked_list_node() :v(0), e(0) {
            for (int i = 0; i < Capacity; i++)
                edges[i] = NULL;
        }
    };
    template<typename T, size_t Capacity>
    using adj_linked_list = adj_linked_list_node<T, Capacity>*;


    template<typename T, size_t Capacity>
    void add_edge(adj_linked_list<T, Capacity>& g, int u, int v, int w) {
        vertex* cur = new vertex(v, w);
        if (g->edges[u] == nullptr) {
            g->edges[u] = new vertex;
        }
        cur->next = g->edges[u]->next;
        g->edges[u]->next = cur;
    }

    template<typename T, size_t Capacity>
    void create_adj_linked_list(adj_linked_list<T, Capacity>& g)
    {
        if (g == nullptr)
            g = new adj_linked_list_node<T, Capacity>;
        std::cin >> g->v >> g->e;
        int u, v, w;
        for (int i = 0; i < g->e; i++)
            std::cin >> u >> v >> w;
        add_edge(g, u, v, w);
        add_edge(g, v, u, w);
    }



    class edge {
    private:
        int u;
        int w;
    public:
        edge(int i = 0, int j = 0) : u(0), w(0) {};

    };

    // the graph implemented by adj_list with data storage.
    template<typename T, size_t Capacity>
    class adj_list {
    private:
        std::vector<edge> edges[Capacity];
        T storage[Capacity];
        int V, E;
    public:
        adj_list(int v, int e) :V(v), E(e) {
            int U, V, W;
            for (int i = 0; i < E; i++) {
                std::cin >> U >> V >> W;
                edges[U].push_back(edge(V, W));
                edges[V].push_back(edge(U, W));
            }
        }

        void add_edge(int i, int j, int w) {
            edges[i].push_back(edge(j, w));
            edges[j].push_back(edge(i, w));
        }
    };

    // DAG implement
    template<typename T, size_t Capacity>
    class dag {
    private:
        using edges = std::vector<edge>[Capacity];
        edges e;
        std::vector<T> storage;
        int v_nums, e_nums;
    public:
        dag(int _vnums, int _enums) :v_nums(_vnums), e_nums(_enums) {
            int i = 0;

            for (i; i < v_nums; i++)
            {
                T tmp;
                std::cin >> tmp;
                storage.push_back(tmp);
            }
            int u, v, w;
            for (i = 0; i < e_nums; i++) {
                std::cin >> u >> v >> w;
                e[u].push_back(edge(v, w));
            }
            memset(vis, 0, sizeof(vis));
        }

        bool vis[Capacity];

        void add_vertex(T val) {
            storage.push_back(val);
            v_nums++;
        }

        void add_edge(int u, int v, int w) {
            e[u].push_back(edge(v, w));
            e_nums++;
        }

        void DFS(int cur)
        {
            vis[cur] = true;
            std::cout << storage[cur] << ' ';
            for (auto item : e[cur]) {
                if (!vis[item.u])
                    DFS(item.u);
            }
        }

        std::vector<int> DFS_STACK(int u) {
            std::stack<int> stk;
            std::vector<int> res;
            stk.push(u);
            while (!stk.empty()) {
                int tmp = stk.top();
                stk.pop();
                if (!vis[tmp])
                {
                    res.push_back(tmp);
                    std::cout << storage[tmp] << ' ';
                    vis[tmp] = false;
                }

                for (auto item : e[u]) {
                    if (!vis[item.u]) {
                        stk.push(item.u);
                    }
                }

            }

        }
    };


}

#endif //CONTAINER_GRAPH_H
