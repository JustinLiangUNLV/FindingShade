#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

struct vertexType // create a struct called vertexType
{
    string destination; // create a string to hold the destination node
    int distance; // create an int to hold the distance between 2 nodes
};

// dfs function that traverses through the graph and returns a boolean if there was a valid path
// given the right circumstances. passes in the currentNode/startNode, endNode to mark the ending at
// the SU. passes in the current stamina which will be updated within the function. adjList, predecessor,
// and visited are used to keep track of valid paths and they are used to manipulate data.

bool dfs(string currentNode, string endNode, int stamina, unordered_map<string,list<vertexType>> adjList,
unordered_map<string,string>& predecessor, unordered_map<string, int>& visited); 

int main()
{
    unordered_map<string, list<vertexType>> adjList; // create a map that maps to a linkedlist
    unordered_map<string, string> predecessor; // create a map to hold all predecessor nodes to the current one
    unordered_map<string, int> visited; // create a map to holds the visited nodes and sees if that node can be revisited
    string startNode; // create a temp string for the start node
    string endNode; // create a temp string for the end node
    string fromVertex; // fromVertex to populate adjList
    string toVertex; // toVertex to popoulate adjList
    int distance; // temp variable to hold the distance input from file
    int stamina; // temp variable to hold the stamina input from file
    string data; // temp variable to get the entire line of the input file
    while(true) // infinite loop
    {
        cin >> startNode >> endNode >> stamina; // read the first line
        break; // break once we read the first line
    }
    while(getline(cin, data)) // while we are able to read in lines
    {
        if(data.empty()) // if it comes across a blank line
        {
            continue; // continue to next line
        }
        stringstream dataObject(data); // create a stringstream object and pass in the line read from data
        dataObject >> fromVertex >> toVertex >> distance; // store into correct variables
        adjList[fromVertex].push_back({toVertex, distance}); // pushback correct variables into adjList which maps to a linked list
    }

    bool path = dfs(startNode, endNode, stamina, adjList, predecessor, visited); // call dfs and store it into a bool variable called path
    if(path) // if there is a valid path
    {
        cout << "Time to cool off!" << endl; // output according to pdf
        cout << "Path: "; // output according to pdf
        vector<string> pathNodes; // create a temp vector to store the nodes from the predecessor map
        string current = endNode; // get the end node
        while(current != startNode) // while the temp current node doesn't hit the start node
        {
            pathNodes.push_back(current); // pushback into the vector
            current = predecessor[current]; // iterate to next position in the map
        }
        pathNodes.push_back(startNode); // pushback the startNode
        for(int i = pathNodes.size() - 1; i >= 0; i--) // iterate backwards from the temp vector
        {
            cout << pathNodes[i] << " "; // output the correct path
        }
        cout << endl;

    }
    else
    {
        cout << "This is going to be a long summer..." << endl; // otherwise if a path was not found, output according to pdf
    }

    return 0;
}

bool dfs(string currentNode, string endNode, int stamina, unordered_map<string,list<vertexType>> adjList,
unordered_map<string,string>& predecessor, unordered_map<string, int>& visited)
{
    if(currentNode == endNode && stamina > 0) // if the current node hits the end node and there is still stamina left
    {
        return true; // return true because this is our base case
    }
    
    // if the current stamina is less than the previous node's stamina then we should not visit this path again and return false
    if(visited[currentNode] >= stamina)
    {
        return false;
    }

    visited[currentNode] = stamina; // now update the visited map with the most current stamina for that currentNode in the visited map

    for(auto& neighbor : adjList[currentNode]) // iterate through the adjList with a neighbor
    {
        int updatedStamina = stamina - neighbor.distance; // calculate the updatedStamina
        if(updatedStamina > 0) // if the updatedStamina is greater than 0 meaning, it can move to next neighbor
        {
            if(dfs(neighbor.destination, endNode, updatedStamina, adjList, predecessor, visited)) // recurisve call to it passing it next node in LL, and new updated stamina
            {
                predecessor[neighbor.destination] = currentNode; // set the neighbor's predecessor to be the current node
                return true; // return true
            }
        }
    }
    
    return false; // otherwise return false
}