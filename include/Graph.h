#ifndef GRAPH_H
#define GRAPH_H

#include <Edge.h>
#include <vector>
#include <limits>
#include <iostream>




class Graph
{

private:
    sf::Vector2f center;
    std::vector <Node*> Nodes;
    std::vector <Edge*> Edges;
    std::vector <std::vector <int>> Matrix;
    sf::Color color;
public:
    // Constructors
    Graph();
    Graph(std::vector <std::vector <int>> M, double x, double y, double R, sf::Color color);

    //Destructor
    ~Graph();

    // Draw a Graph
    void draw(sf::RenderTarget* rt);

    // Algorithms
    // Minimal Spanning Tree
    std::vector<std::vector<int>> Prim(sf::RenderTarget *rt);

    std::vector<std::vector<int>> Dijkstra(sf::RenderTarget *rt, int begin, int end);

    // Getters
    std::vector <Node*> getNodes();
    std::vector <Edge*> getEdges();
    int getSize();

    // Setters
    void setMatrix(std::vector <std::vector <int>> M);
};

#endif