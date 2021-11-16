#include <Graph.h>



sf::Vector2f getCirclePoint(double radius, double angle) {
    return {
        static_cast<float>(radius * std::sin(angle)),
        static_cast<float>(-1. * radius * std::cos(angle))
    };
}


// Destructor
Graph::~Graph()
{
    for (auto& node : Nodes)
    {
        delete node;
    }
    delete& Nodes;
    for (auto& edge : Edges)
    {
        delete edge;
    }
    delete& Edges;
}

// Constructors


// Graph::Graph()
// {
//     center = sf::Vector2f(0,0);
//     std::vector <Node*> *Nodes = new std::vector<Node*>;
//     std::vector <Edge*> Edges = {};
//     std::vector <std::vector <int>> Matrix = {};
// }

Graph::Graph(std::vector<std::vector <int>> M, double x, double y, double R, sf::Color clr)
{
    color = clr;
    center = sf::Vector2f(x, y);
    int n = M.size();
    Matrix = M;
    for (int i = 0; i < n; i++)
    {
        sf::Vector2f point = sf::Vector2f(x, y) + getCirclePoint(R, i * 2 * M_PI / n);
        Node* tmp = new Node(point.x, point.y, std::to_string(i + 1), color);
        Nodes.push_back(tmp);
    }
    bool** isDrawed = new bool*[n];
    for(int i = 0; i < n; i++)
    {
        isDrawed[i] = new bool[n];
        for(int j = 0; j < n; j++)
        {
            isDrawed[i][j] = false;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (M[i][j] != 0)
            {
                isDrawed[i][j] = true;
                if (isDrawed[j][i])
                {
                    Edge* tmp = new Edge(Nodes[i], Nodes[j], M[i][j], color, true);
                    Edges.push_back(tmp);
                }
                else
                {
                    Edge* tmp = new Edge(Nodes[i], Nodes[j], M[i][j], color);
                    Edges.push_back(tmp);
                }
            }
        }
    }
}

// Draw a Graph
void Graph::draw(sf::RenderTarget* rt)
{
    for (auto& edge : Edges)
        edge->draw(rt);
    for (auto& node : Nodes)
        node->draw(rt);
   
}


// Algorithms
// Minimum Spanning Tree
std::vector<std::vector<int>> Graph::Prim(sf::RenderTarget* rt)
{
    int n = Matrix.size();
        const int INF = std::numeric_limits<int>::max();

    std::vector<std::vector<int>> tmpMatr(n, std::vector<int>(n));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if (Matrix[i][j] != 0)
                tmpMatr[i][j] = Matrix[i][j];
            else
                tmpMatr[i][j] = INF;
        }
    }
    std::vector<bool> used(n);
    std::vector<int> min_e(n, INF);
    std::vector<int> sel_e(n, -1);
    min_e[0] = 0;
    std::vector<std::vector<int>> res(n, std::vector<int>(n));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            res[i][j] = 0;
        }
    }
    for(int i = 0; i < n; i++)
    {
        int v = -1;
        for(int j = 0; j < n; j++)
        {
            if ( !used[j] && (v == -1 || min_e[j] < min_e[v]) )
            {
                v = j;
            }
        }
        if (min_e[v] == INF)
        {
            std::cout << "NO MST!\n";
            exit(0);
        }
        used[v] = true;
        if (sel_e[v] != -1)
        {
            std::cout << v << " " << sel_e[v] << "\n";
            res[v][sel_e[v]] = tmpMatr[v][sel_e[v]];
        }
        for(int to = 0; to < n; to++)
        {
            if (tmpMatr[v][to] < min_e[to])
            {
                min_e[to] = tmpMatr[v][to];
                sel_e[to] = v;
            }
        }
    }
    return res;
}



std::vector<std::vector<int>> Graph::Dijkstra(sf::RenderTarget *rt, int begin , int end_ )
{
    int n = Matrix.size();
    std::vector<int> dist(n);
    std::vector<int> v(n);
    int tmp, minIndex, min;
    int beginIndex = begin; // 0
    for(int i = 0; i < n; i++)
    {
        dist[i] = std::numeric_limits<int>::max();
        v[i] = 1;
    }
    dist[beginIndex] = 0;
    do
    {
        minIndex = std::numeric_limits<int>::max();
        min = std::numeric_limits<int>::max();
        for(int i = 0; i < n; i++)
        {
            if ( (v[i] == 1) && (dist[i]< min) )
            {
                min = dist[i];
                minIndex = i;
            }
        }
        if (minIndex != std::numeric_limits<int>::max())
        {
            for(int i = 0; i < n; i++)
            {
                if (Matrix[minIndex][i] > 0)
                {
                    tmp = min + Matrix[minIndex][i];
                    if (tmp < dist[i])
                    {
                        dist[i] = tmp;
                    }
                }
            }
            v[minIndex] = 0;
        }
    } while (minIndex < std::numeric_limits<int>::max());

    std::vector<int> ver(n);
    int end = end_; // 4 // index of last node
    ver[0] = end + 1;
    int k = 1;
    int weight = dist[end];

    while (end != beginIndex)
    {
        for(int i = 0; i < n; i++)
        {
            if (Matrix[i][end] != 0)
            {
                int tmp = weight - Matrix[i][end];
                if (tmp == dist[i])
                {
                    weight = tmp;
                    end = i;
                    ver[k] = i + 1;
                    k++;
                }
            }
        }
    }

    std::cout << "\nPath: \n";

    for(int i = k-1; i >= 0; i--)
    {
        std::cout << ver[i] << " -> ";
    }
    std::cout << "\n";
    std::vector<std::vector<int>> res(n, std::vector<int>(n));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            res[i][j] = 0;
        }
    }
    for (int i = k - 1; i > 0; i--)
    {
        int first = ver[i] - 1;
        int second = ver[i - 1] - 1;
        res[first][second] = Matrix[first][second];
    }

    return res;
    
}
