#include "verticesGraph.h"
#include <fstream>
#include <sstream>
#include <queue>
#include <string>
#include <vector>
#include <climits>
#include <stdlib.h>
#include <time.h>

verticesGraph::verticesGraph(char * fileName)
{
    buildGraph(fileName);
};

verticesGraph::verticesGraph(){};

//verticesGraph::~verticesGraph(){};
//array doesn't need to be destroyed?

void verticesGraph::buildGraph(char * fileName)
{
    milesTraveled = 0;
    std::string firstLine,lines;
    std::string itemArray[20][20];
    int m=0,quantity=0;
    std::ifstream inFile;
    inFile.open(fileName);
    if(inFile.good())
    {
        getline(inFile,firstLine);
        std::stringstream ss1(firstLine);
        std::string items1;
        while(getline(ss1,items1,','))
        {
            quantity+=1;
        }
        quantity-=1;
        while(getline(inFile,lines))
        {
            int n=0;
            std::stringstream ss2(lines);
            std::string items2;
            while(getline(ss2,items2,','))
            {
                itemArray[m][n]=items2;
                n+=1;
            }
            m+=1;
        }
    }

    for(int m=0;m<quantity;m++)
    {
        addVertex(itemArray[m][0]);
    }

    for(int m=0;m<quantity;m++)
    {
        for(int n=0;n<quantity;n++)
        {
            if(itemArray[m][n+1]!="-1"&&itemArray[m][n+1]!="0")
            {
                addEdge(itemArray[m][0],itemArray[n][0],atoi(itemArray[m][n+1].c_str()));
            }
        }
    }
}

void verticesGraph::assignDistricts()
{
    int n=1;
    for(int m=0;m<vertices.size();m++)
    {
        if(vertices[m].district==-1)
        {
            BFTraversalLabel(vertices[m].name,n);
            n+=1;
        }
    }
}

void verticesGraph::BFTraversalLabel(std::string starting,int distID)
{
    std::queue<vertex *> qv;
    vertex * v1=findVertex(starting);
    vertex * v2;
    v1->visited=true;
    qv.push(v1);
    while(!qv.empty())
    {
        v2=qv.front();
        qv.pop();
        for(int m=0;m<v2->adj.size();m++)
        {
            if(v2->adj[m].v->visited==false)
            {
                v2->adj[m].v->visited=true;
                v2->district=distID;
                v2->adj[m].v->district=distID;
                qv.push(v2->adj[m].v);
            }
        }
    }

    for(int m=0;m<vertices.size();m++)
    {
        vertices[m].visited=false;
    }
}

void verticesGraph::displayEverything()
{
    for(int m=0;m<vertices.size();m++)
    {
        std::cout<<vertices[m].district<<": "<<vertices[m].name<<"-->";
        for(int n=0;n<vertices[m].adj.size();n++)
        {
            std::cout<<vertices[m].adj[n].v->name;
            if(n!=vertices[m].adj.size()-1)
            {
                std::cout<<", ";
            }
        }
        std::cout<<std::endl;
    }
}

void verticesGraph::shortestDistance(std::string starting,std::string destination)
{
    if(findVertex(starting)==NULL||findVertex(destination)==NULL)
    {
        std::cout<<"At least one vertex doesn't exist"<<std::endl;
        return;
    }

    vertex * sta=findVertex(starting);
    vertex * des=findVertex(destination);
    if(sta->district!=des->district)
    {
        std::cout<<"No path between two vertices"<<std::endl;
        return;
    }

    if(vertices[0].district==-1)
    {
        std::cout<<"Please assign vertices' districts first"<<std::endl;
        return;
    }

    vertex * startV=findVertex(starting);
    vertex * endV=Dijkstra(starting,destination);
    std::vector<vertex *> path;
    vertex * v1=endV;
    while(v1!=startV)
    {
        path.push_back(v1);
        v1=v1->previous;
    }
    std::cout<<std::endl;
    std::cout<<"Shortest distance: "<<starting<<" >>> "<<destination<<" is "<<endV->distance<<std::endl;
    std::cout<<"Path: ";
    std::cout<<startV->name;
    for(int m=path.size()-1;m>-1;m--)
    {
        std::cout<<" >>> "<<path[m]->name;
    }
    std::cout << std::endl;

    for(int m=0;m<vertices.size();m++)
    {
        vertices[m].visited=false;
    }
}

void verticesGraph::limitedDistancePath(std::string starting,std::string destination,std::string limit)
{
    if(findVertex(starting)==NULL||findVertex(destination)==NULL)
    {
        std::cout<<"At least one vertices doesn't exist"<<std::endl;
        return;
    }

    vertex * sta=findVertex(starting);
    vertex * des=findVertex(destination);
    if(sta->district!=des->district)
    {
        std::cout<<"No path between two vertices"<<std::endl;
        return;
    }

    if(vertices[0].district==-1)
    {
        std::cout<<"Please assign vertices' districts first"<<std::endl;
        return;
    }

    std::stringstream ss(limit);
    int d;
    if(!(ss>>d))
    {
        std::cout<<"Invalid input"<<std::endl;
        return;
    }
    ss>>d;

    if(d<=0)
    {
        std::cout<<"distance must be greater than zero"<<std::endl;
        return;
    }

    int m=vertices.size();

    int previous[m];
    for(int n=0;n<m;n++)
    {
        previous[n]=-1;
        vertices[n].ID=n;
    }

    sta->visited=true;
    vertex * v;
    std::queue<vertex *> qv;
    qv.push(sta);
    while(!qv.empty())
    {
        v=qv.front();
        qv.pop();
        for(int m=0;m<v->adj.size();m++)
        {
            if(v->adj[m].v->visited==false)
            {
                if(v->adj[m].weight<=d)
                {
                    previous[v->adj[m].v->ID]=v->ID;
                    v->adj[m].v->visited=true;
                    qv.push(v->adj[m].v);
                }
            }
        }
    }

    std::vector<vertex *> path;
    int pos=des->ID;
    path.push_back(des);
    while(previous[pos]!=-1)
    {
        pos=previous[pos];
        path.push_back(findVertex(vertices[pos].name));
    }

    if(path[0]!=des||path[path.size()-1]!=sta)
    {
        std::cout<<"No path can be found"<<std::endl;
        return;
    }

    std::cout<<"One path: ";
    for(int m=path.size()-1;m>-1;m--)
    {
        if(m!=0)
        {
            std::cout<<path[m]->name<<" >>> "<<findDistance(path[m]->name,path[m-1]->name)<<" >>> ";

        }
        else
        {
            std::cout<<path[m]->name;
        }
    }
    std::cout << std::endl;

    for(int m=0;m<vertices.size();m++)
    {
        vertices[m].visited=false;
    }
}

void verticesGraph::vertexInformation(std::string v1)
{
    vertex * v=findVertex(v1);
    if (v != NULL){
        std::cout<<"Name: "<<v->name<<std::endl;
        std::cout<<"District: "<<v->district<<std::endl;
        std::cout<<"Number of connected vertices: "<<v->adj.size()<<std::endl;
        std::cout<<"Adjacent vertices: ";
        for(int m=0;m<v->adj.size();m++)
        {
            std::cout<<v->adj[m].v->name;
            if(m!=vertices[m].adj.size()-1)
            {
                std::cout<<" , ";
            }
        }
        std::cout<<std::endl;
    }else{
        std::cout << "This vertex does not exist." << std::endl;
    }
}

void verticesGraph::graphInformation()
{
    std::cout<<"Number of vertices: "<<vertices.size()<<std::endl;
    int maxDistrict=vertices[0].district;
    int maxConnections=vertices[0].adj.size();
    for(int m=0;m<vertices.size();m++)
    {
        if(vertices[m].district>=maxDistrict)
        {
            maxDistrict=vertices[m].district;
        }
        if(vertices[m].adj.size()>=maxDistrict)
        {
            maxConnections=vertices[m].adj.size();
        }
    }
    if(maxDistrict==-1)
    {
        maxDistrict=0;
    }
    std::cout<<"Number of districts: "<<maxDistrict<<std::endl;
    std::vector<vertex> maxV;
    std::cout<<"Vertex with most connections: ";
    for(int m=0;m<vertices.size();m++)
    {
        if(vertices[m].adj.size()==maxConnections)
        {
            maxV.push_back(vertices[m]);
        }
    }
    for(int n=0;n<maxV.size();n++)
    {
        std::cout<<maxV[n].name;
        if(n!=maxV.size()-1)
        {
            std::cout<<" , ";
        }
    }
    std::cout<<std::endl;
    std::cout<<"with "<<maxConnections<<" connections"<<std::endl;
}

void verticesGraph::addVertex(std::string name)
{
    bool found=false;
    for(int m=0;m<vertices.size();m++)
    {
        if(vertices[m].name==name)
        {
            found=true;
            std::cout<<vertices[m].name<<" is found"<<std::endl;
        }
    }
    if(found==false)
    {
        vertex v;
        v.name=name;
        v.district=-1;
        v.visited=false;
        vertices.push_back(v);
    }
}

void verticesGraph::addEdge(std::string v1,std::string v2,int weight)
{
    for(int m=0;m<vertices.size();m++)
    {
        if(vertices[m].name==v1)
        {
            for(int n=0;n<vertices.size();n++)
            {
                if(vertices[n].name==v2&&m!=n)
                {
                    adjVertex av;
                    av.v=&vertices[n];
                    av.weight=weight;
                    vertices[m].adj.push_back(av);
                }
            }
        }
    }
}

int verticesGraph::findDistance(std::string v1,std::string v2)
{
    if(findVertex(v1)==NULL||findVertex(v2)==NULL)
    {
        return -1;
    }

    vertex * sta=findVertex(v1);
    vertex * des=findVertex(v2);
    if(sta->district!=des->district)
    {
        return 0;
    }
    int distance;
    for(int m=0;m<vertices.size();m++)
    {
        if(sta->adj[m].v==des)
        {
            distance=sta->adj[m].weight;
        }
    }
    return distance;
}

vertex * verticesGraph::findVertex(std::string name)
{
    for(int m=0;m<vertices.size();m++)
    {
        if(vertices[m].name==name)
        {
            return &vertices[m];
        }
    }
    return NULL;
}

vertex * verticesGraph::Dijkstra(std::string starting,std::string destination)
{
    vertex * startV=findVertex(starting);
    vertex * endV=findVertex(destination);
    startV->visited=true;
    startV->distance=0;
    std::vector<vertex *> solved;
    solved.push_back(startV);

    int minDistance,dist;
    vertex * solvedV, *s, *parent;
    while(endV->visited==false)
    {
        minDistance=INT_MAX;
        solvedV=NULL;
        for(int m=0;m<solved.size();m++)
        {
            s=solved[m];
            for(int n=0;n<s->adj.size();n++)
            {
                if(s->adj[n].v->visited==false)
                {
                    dist=s->distance+s->adj[n].weight;
                    if(dist<minDistance)
                    {
                        solvedV=s->adj[n].v;
                        minDistance=dist;
                        parent=s;
                    }
                }
            }
        }
        solvedV->distance=minDistance;
        solvedV->previous=parent;
        solvedV->visited=true;
        solved.push_back(solvedV);
    }

    for(int m=0;m<vertices.size();m++)
    {
        vertices[m].visited=false;
    }

    return endV;
}

void verticesGraph::displayServices(){
    for (int i=0; i<vertices.size();i++){
        //std::cout << vertices[i].services.size() << std::endl;
        if (vertices[i].services.size() > 0){
            std::cout << vertices[i].district <<": "<<vertices[i].name<<"-->"<<std::endl;
            for (int j=0; j<vertices[i].services.size(); j++){
                if(j==vertices[i].services.size()-1){
                    std::cout<<vertices[i].services[j].type<<": "<<vertices[i].services[j].name<<" - "<<"$"<<vertices[i].services[j].cost<<std::endl;
                }else{
                    std::cout<<vertices[i].services[j].type<<": "<<vertices[i].services[j].name<<" - "<<"$"<<vertices[i].services[j].cost<<std::endl;
                }
            }
            std::cout<<std::endl;
        }else{
            //std::cout << "No active services to display." << std::endl;
        }
    }
}

void verticesGraph::addService(std::string name,std::string serV,std::string type, int cost){
    service newServ;

    vertex *temp = findVertex(name);
    if (temp != NULL){
        newServ.name = serV;
        newServ.cost = cost;
        newServ.type = type;
        temp->services.push_back(newServ);
    }else{
        std::cout << "This vertex does not exist." << std::endl;
    }
}

service *verticesGraph::findService(vertex *city,std::string name){
    for (int i=0; i<city->services.size();i++){
        if (city->services[i].type == name){
            return &city->services[i];
        }
    }
}

void verticesGraph::planYourPath(std::string starting,std::string destination,int distance)
{
    int totalMiles = 0;
    if(findVertex(starting)==NULL||findVertex(destination)==NULL)
    {
        std::cout<<"At least one vertices doesn't exist"<<std::endl;
        return;
    }

    vertex * sta=findVertex(starting);
    vertex * des=findVertex(destination);
    if(sta->district!=des->district)
    {
        std::cout<<"No path between two vertices"<<std::endl;
        return;
    }

    if(vertices[0].district==-1)
    {
        std::cout<<"Please assign vertices' districts first"<<std::endl;
        return;
    }

    if(distance<=0)
    {
        std::cout<<"distance must be greater than zero"<<std::endl;
        return;
    }

    int m=vertices.size();

    int previous[m];
    for(int n=0;n<m;n++)
    {
        previous[n]=-1;
        vertices[n].ID=n;
    }

    sta->visited=true;
    vertex * v;
    std::queue<vertex *> qv;
    qv.push(sta);
    while(!qv.empty())
    {
        v=qv.front();
        qv.pop();
        for(int m=0;m<v->adj.size();m++)
        {
            if(v->adj[m].v->visited==false)
            {
                if(v->adj[m].weight<=distance)
                {
                    previous[v->adj[m].v->ID]=v->ID;
                    v->adj[m].v->visited=true;
                    qv.push(v->adj[m].v);
                }
            }
        }
    }

    std::vector<vertex *> path;
    int pos=des->ID;
    path.push_back(des);
    while(previous[pos]!=-1)
    {
        pos=previous[pos];
        path.push_back(findVertex(vertices[pos].name));
    }

    if(path[0]!=des||path[path.size()-1]!=sta)
    {
        std::cout<<"No path can be found"<<std::endl;
        return;
    }
    std::cout <<std::endl;
    std::cout<<"Trip: ";
    for(int m=path.size()-1;m>-1;m--)
    {
        if(m!=0)
        {
            std::cout<<path[m]->name<<" >>> "<<findDistance(path[m]->name,path[m-1]->name)<<" >>> ";
            milesTraveled = milesTraveled + findDistance(path[m]->name,path[m-1]->name);
            totalMiles = totalMiles + milesTraveled;
            if (milesTraveled >= 500){

                service *stop = findService(path[m],"Gas Station");
                std::cout << "Stop for Gas at: "<<stop->name<<", Cost: $"<< stop->cost<<" per Gallon"<<" >>> ";
                service *food = findService(path[m],"Food");
                std::cout << "Stop for Food at: "<<food->name<<", Cost: $"<< food->cost<<" for full meal."<<" >>> ";


                if (milesTraveled >= 1500){
                    service *hotel = findService(path[m],"Hotel");
                    std::cout << "Stay the Night at: "<<hotel->name<<", Cost: $"<<hotel->cost<<" per night."<<" >>> ";
                }else if (totalMiles >= 1500){
                    service *hotel = findService(path[m],"Hotel");
                    std::cout << "Stay the Night at: "<<hotel->name<<", Cost: $"<<hotel->cost<<" per night."<<" >>> ";
                    totalMiles = 0;
                }

                milesTraveled = 0;
            }
        }
        else
        {
            std::cout<<path[m]->name;
        }
    }
    std::cout << std::endl;

    for(int m=0;m<vertices.size();m++)
    {
        vertices[m].visited=false;
    }
}
