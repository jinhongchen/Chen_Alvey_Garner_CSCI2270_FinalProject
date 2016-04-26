#ifndef VERTICESGRAPH_H
#define VERTICESGRAPH_H
#include <vector>
#include <iostream>

struct vertex;

struct service;

struct adjVertex
{
    vertex *v;
    int weight;
};

struct service
{
    std::string name;
    std::string type;
    int cost;
};

struct vertex
{
    std::string name;
    int district;
    int distance;
    int ID;
    int position;
    bool visited;
    vertex *previous;
    std::vector<adjVertex> adj;
    std::vector<service> services;

};

class verticesGraph
{
    private:
        std::vector<vertex> vertices;
        int milesTraveled;
    public:
        verticesGraph(char * fileName);
        verticesGraph();
        //~verticesGraph();
        //array doesn't need to be destroyed?
        void buildGraph(char * fileName);
        void assignDistricts();
        void BFTraversalLabel(std::string starting,int distID);
        void displayEverything();
        void shortestDistance(std::string starting,std::string destination);
        void limitedDistancePath(std::string starting,std::string destination,int distance);
        void vertexInformation(std::string v1);
        void graphInformation();
        void addVertex(std::string name);
        void addEdge(std::string v1,std::string v2,int weight);
        void snakesAndLadders();
        void addService(std::string name,std::string service,std::string type, int cost);
        service *findService(vertex *city, std::string type);
        void displayServices();
        void planYourPath(std::string name,std::string endname, int distance);
        int findDistance(std::string v1,std::string v2);
        vertex * findVertex(std::string name);
        vertex * Dijkstra(std::string starting,std::string destination);
};

#endif
