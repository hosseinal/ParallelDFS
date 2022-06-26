#include <bits/stdc++.h>
#include "time.h"
using namespace std;

//in this algorithm we parallelize the process
//that we want to do in each vertex.


//this is class of graph contains a map for visited
//nodes and adj map for list of edges per node.
class Graph {
public:
    map<int, bool> visited;
    map<int, list<int> > adj;
    stack<int> m_stack;
    void addEdge(int v, int w);
    void DFS(int v);
};

//This function is the process that we want to
//do in each node in this algorithm we want to parallelize
//this section also cout is in critical section because of
//that it's I/O work, and it needs to be atomic.
void Execute(int v){
    #pragma omp critical
    {
        cout<<v<<"-------------"<<endl;
    }
}

//In this part we add the edges
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

//This function starts the graph traversal
//And we do this by iterating over the stack and
//we parallel the process that we do in each vertex.
void Graph::DFS(int v)
{
    m_stack.push(v);
    while (!m_stack.empty()){
        int item = m_stack.top();
        m_stack.pop();
        if(visited[item])
            continue;
        visited[item] = true;

        #pragma omp parallel
        {
            Execute(item );
        }
        list<int>::reverse_iterator i;
        for (i = adj[item].rbegin(); i != adj[item].rend(); ++i)
            m_stack.push(*i);
    }
}

// Driver code
int main()
{
    Graph g;

    ifstream fin;

    // in this part program is opening a file contain a graph
    //each line is edges of that line number vertex
    //consider that vertex numbers start  from 0
    fin.open("/home/hossein/CLionProjects/untitled/graph.txt");
    string line ;
    int counter = 0;
    while (fin) {
        // Read a Line from File
        getline(fin, line);

        size_t pos = 0;
        std::string token;
        string delimiter = " ";
        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            int number = stoi(token);
            g.addEdge(counter,number);
            line.erase(0, pos + delimiter.length());
        }
        counter++;
    }

    // Close the file
    fin.close();
    //start clock to calculate the duration of execution
    clock_t start = clock();

    //start point is node that the algorithm start from
    int startPoint = 297;

    //start the algorithm
    g.DFS(startPoint);

    clock_t stop = clock();

    //printing the duration of execution of the algorithm
    double e = (double)(stop-start)/CLOCKS_PER_SEC;
    cout<<e;
    return 0;
}