#ifndef EDGE_H
#define EDGE_H

#include <SFML/Graphics.hpp>
#include <Node.h>
#include <cmath>

class Edge : public sf::RectangleShape
{
private:

    Node* First;
    Node* Second;
    int weight;
    bool isDrawed;
    sf::Color edgeColor;

public:
    //Constructors
    Edge();
    Edge(Node* a, Node* b, int val, sf::Color clr, bool is_drawed = false);
    // Destructor
    ~Edge();

    // Draw An Edge
    void drawWeights(sf::RenderTarget* rt, int size = 15, sf::Color color = sf::Color::Black);
    void drawLineWithThickness(sf::RenderTarget *rt, double angle, double dist);
    void drawTriangle(sf::RenderTarget*rt, double angle, double rad = 10);
    void draw(sf::RenderTarget* rt);

    // Getters
    Node* getFirst();
    Node* getSecond();
    int getWeight();

    // Setters
    void setFirst(Node* a);
    void setSecond(Node* b);
    void setWeight();
};

#endif
