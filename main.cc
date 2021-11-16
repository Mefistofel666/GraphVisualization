#include <iostream>
#include <Graph.h>



int main()
{
    const unsigned width = 1500;
    const unsigned height = 1000;
    sf::RenderWindow window(sf::VideoMode(width, height), "Window");

    sf::RenderTexture rt;

    double W_width = window.getSize().x;
    double W_height = window.getSize().y;

    rt.create(width, height);

    // Symmetric matrix for Prim Algorithm
    std::vector <std::vector <int> > M =
    {
        {0, 0, 2,  8, 1, 1, 0},
        {0, 0, 0, 4, 0, 1, 0},
        {2, 0, 0, 9, 0, 0, 0},
        {8, 4, 9, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 9},
        {0, 0, 0, 0, 1, 9, 0}
    };
	
    Graph* graph = new Graph(M, W_width / 4, W_height / 2, 300, sf::Color::Black);

    graph->draw(&rt);
    std::vector<std::vector<int>> primMatrix = graph->Prim(&rt);


    Graph* graph2 = new Graph(primMatrix, W_width * 3 / 4, W_height / 2, 300, sf::Color::Red);

    std::vector<std::vector<int>> dijkstraMatrix = graph->Dijkstra(&rt, 0, 3);


    Graph* graph3 = new Graph(dijkstraMatrix, W_width * 3 / 4, W_height / 2, 300, sf::Color::Blue);

    std::cout << "\n Prim Matrix: \n";

    for(int i = 0; i < primMatrix.size(); i++)
    {
        for(int j = 0; j < primMatrix.size(); j++)
        {
            std::cout << primMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nDijkstra Matrix: \n";
    for(int i = 0; i < dijkstraMatrix.size(); i++)
    {
        for(int j = 0; j < dijkstraMatrix.size(); j++)
        {
            std::cout << dijkstraMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    rt.display();
    sf::Sprite sprite(rt.getTexture());
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
            {
                graph2->draw(&rt);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
            {
                graph3->draw(&rt);
            }
        }
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }


    return 0;
}