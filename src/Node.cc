#include <Node.h>

// Constructors

Node::Node()
{
    name = "";
    center = sf::Vector2f(0, 0);
    setPosition(0, 0);
}

Node::Node(double a, double b, std::string n, sf::Color clr)
{
    center = sf::Vector2f(a, b);
    setPosition(a, b);
    name = n;
    color = clr;
}

// Getters

std::string Node::getName()
{
    return name;
}

double Node::getX()
{
    return center.x;
}

double Node::getY()
{
    return center.y;
}

sf::Vector2f Node::getCenter()
{
    return center;
}



// Setters

void Node::setName(std::string n)
{
    name = n;
}

// Draw Node boundaries 
void Node::drawCircle(sf::RenderTarget *rt, double radius)
{
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(getPosition().x, getPosition().y);
    circle.setFillColor(color);
    circle.setOutlineThickness(2.f);
    circle.setOutlineColor(color);
    rt->draw(circle);

}

// Draw text in Node
void Node::drawText(sf::RenderTarget *rt, int size, sf::Color color)
{
    sf::Text text;
    sf::Font font;
    font.loadFromFile("IBMPlexSans-Medium.ttf");
    text.setFont(font);
    text.setCharacterSize(size);
    text.setString(name);
    text.setFillColor(color);

    sf::FloatRect rect = text.getLocalBounds();
    double width = rect.width;
    double height = rect.height;
	
    text.setOrigin(width / 2.0, height / 2.0);
    text.setPosition(getPosition().x, getPosition().y - height / 2.0);
    rt->draw(text);
}



// Drawing a Node at all
void Node::draw(sf::RenderTarget* rt)
{
    drawCircle(rt);
    drawText(rt);   
}

