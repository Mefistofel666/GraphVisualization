#include <SFML/Graphics.hpp>
#include <string>


class Node : public sf::CircleShape
{
private:
    std::string name;
    sf::Vector2f center;
    sf::Color color;
public:
    // Constructors
    Node();
    Node(double a, double b, std::string n, sf::Color color);
    Node(sf::Vector2f c, std::string n, sf::Color clr) : center(c), name(n), color(clr) {}

    // Drawing A Node
    void drawText(sf::RenderTarget *rt, int size = 20, sf::Color color = sf::Color::White);
    void drawCircle(sf::RenderTarget *rt, double radius=15);
    void draw(sf::RenderTarget* rt);

    // Getters
    std::string getName();
    double getX();
    double getY();
    sf::Vector2f getCenter();

    // Setters
    void setName(std::string n);
};

