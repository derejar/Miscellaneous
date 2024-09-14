#include <iostream>
#include <fstream>
#include <iomanip>
#include "graph.h"

void print(const Graph& graph)
{
    std::vector<int> colors = graph.getColors();
    for(std::size_t i = 0; i < graph.size(); ++i)
    {
        for(std::size_t j = 0; j < graph[i].size(); ++j)
            std::cout << std::setw(2) << std::setfill('0') << graph[i][j] << " ";
        std::cout << std::setw(3) << std::setfill(' ') << colors[i] << "\n";
    }
}

Graph prim(const Graph& graph)
{
    matrix_t minimumSpanningTree(graph.size(), std::vector<int>(graph.size()));
    for(std::size_t i = 0; i < minimumSpanningTree.size(); ++i)
        for(std::size_t j = 0; j < minimumSpanningTree.size(); ++j)
            minimumSpanningTree[i][j] = 0;
    std::vector<bool> selected(graph.size(), false);
    selected[0] = true;
    std::size_t edge = 0;
    while(edge < graph.size() - 1)
    {
        int min = 0b1111111111111111111111111111111;
;       int x = 0; int y = 0;
        for(std::size_t i = 0; i < graph.size(); ++i)
        {
            for(std::size_t j = 0; j < graph.size() && selected[i]; ++j)
            {
                if(!selected[j] && graph[i][j] && min > graph[i][j])
                {
                    min = graph[i][j];
                    x = i; y = j;
                }
            }
        }
        minimumSpanningTree[x][y] = min;
        minimumSpanningTree[y][x] = min;
        selected[y] = true;
        ++edge;
    }
    return Graph(minimumSpanningTree);
}

int main()
{
    int c = 1;
    while(c)
    {
        std::cout << "\n\n\n\n\n\n\n\n\n\n";
        std::ifstream ifile("matrix.txt");
        Graph graph;
        ifile >> graph;
        print(graph);
        std::cout << "---------------------------------------\n";
        print(prim(graph));
        std::cin >> c;
    }
}
