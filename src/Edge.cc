#include <Edge.h>

// Constructors
Edge::Edge()
{
    First = nullptr;
    Second = nullptr;
    setPosition(0, 0);
    isDrawed = false;
    edgeColor = sf::Color::Blue;
}

Edge::Edge(Node* a, Node* b, int val, sf::Color clr, bool is_drawed)
{
    First = a;
    Second = b;
    weight = val;
    isDrawed = is_drawed;
    edgeColor = clr;
}

//Destructor
Edge::~Edge()
{
    delete First;
    delete Second;
}


// Draw weights
void Edge::drawWeights(sf::RenderTarget* rt, int size , sf::Color clr)
{
    Node* left = (First->getX() <= Second->getX() ? First : Second);
	Node* right = (First->getX() > Second->getX() ? First : Second);

    sf::Text text;
    sf::Font font;
    font.loadFromFile("IBMPlexSans-Medium.ttf");
    text.setFont(font);
    text.setCharacterSize(size);
    text.setString(std::to_string(weight));
    text.setFillColor(clr);

    sf::FloatRect rect = text.getLocalBounds();
    double width = rect.width;
    double height = rect.height;


    text.setOrigin(width / 2.0, height / 2.0);

    sf::CircleShape circle;
    double radius = (width > height ? width / 1.5 : height / 1.5);
    circle.setRadius(radius);
    circle.setOrigin(radius, radius);
    circle.setFillColor(sf::Color::White);
    circle.setPosition(Second->getX() + (First->getX() - Second->getX()) /(4), Second->getY() + (First->getY() - Second->getY()) / (4));
    rt->draw(circle);

    text.setPosition(Second->getX() + (First->getX() - Second->getX()) / (4), Second->getY() + (First->getY() - Second->getY()) /  (4) - height / 2.0);
    rt->draw(text);
}

// Draw line with thickness
void Edge::drawLineWithThickness(sf::RenderTarget *rt, double angle, double dist)
{
    Node* left = (First->getX() <= Second->getX() ? First : Second);
	Node* right = (First->getX() > Second->getX() ? First : Second);
    sf::RectangleShape line(sf::Vector2f(dist, 4.f));
    line.setOrigin(dist / 2.0, 2);
    
    angle = (left->getY() < right->getY() ? angle : -angle);
    angle = (left->getY() == right->getY() ? 0 : angle);
    
    line.rotate(angle);
	
    line.setPosition((right->getX() + left->getX()) / 2.0, (right->getY() + left->getY()) / 2.0);
    line.setFillColor(edgeColor);

    rt->draw(line);
}


// Draw triangle
void Edge::drawTriangle(sf::RenderTarget* rt, double angle, double rad)
{
    Node* left = (First->getX() <= Second->getX() ? First : Second);
	Node* right = (First->getX() > Second->getX() ? First : Second);

    sf::CircleShape  triangle(rad, 3);
    triangle.setFillColor(edgeColor);
    triangle.setOrigin(rad, rad);
    double newAngle = 0;
    newAngle = (First->getY() <= Second->getY() ? 180.0 : -180.0);
    newAngle += (left->getY() <= right->getY() ? angle : -angle);
    newAngle += (left == First ? 30.0 : -30.0);
    triangle.rotate(newAngle);
    triangle.setPosition(Second->getX() + (First->getX() - Second->getX()) / 6, Second->getY() + (First->getY() - Second->getY()) / 6);
    rt->draw(triangle);
}

void Edge::draw(sf::RenderTarget* rt)
{
    double dist = sqrt(pow(First->getX() - Second->getX(), 2) + pow(First->getY() - Second->getY(), 2));
    double katetX = abs(First->getX() - Second->getX());
    double angle = acos(katetX / dist);
    angle = 180.0 / M_PI * angle;
    
    // Draw Line with thickness
    if(!isDrawed)
        drawLineWithThickness(rt, angle, dist);
    // Draw weights
    drawWeights(rt);
    // Draw Arrow
    drawTriangle(rt, angle);
}

// Getters

Node* Edge::getFirst()
{
    return First;
}

Node* Edge::getSecond()
{
    return Second;
}

// Setters

void Edge::setFirst(Node* a)
{
    First = a;
}

void Edge::setSecond(Node* b)
{
    Second = b;
}
