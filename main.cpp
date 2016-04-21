#include <iostream>
#include "verticesGraph.h"

using namespace std;

int main(int argc, char * argv[])
{
    char * fileName=argv[1];
    verticesGraph cg(fileName);

    string option="-1";

    while(option=="-1")
    {
        cout<<"----------"<<endl;
        cout<<"Main Menu"<<endl;
        cout<<"----------"<<endl;
        cout<<"1.  Assign districts"<<endl;
        cout<<"2.  Display"<<endl;
        cout<<"3.  Find distance"<<endl;
        cout<<"4.  Find shortest distance"<<endl;
        cout<<"5.  Find a path with limited signals"<<endl;
        cout<<"6.  Vertex information"<<endl;
        cout<<"7.  Graph information"<<endl;
        cout<<"8.  Add vertex"<<endl;
        cout<<"9.  Add edge"<<endl;
        cout<<"10. Plan a Trip"<<endl;
        cout<<"0. Quit"<<endl;
        cin>>option;
        if(option=="1")
        {
            cg.assignDistricts();
            option="-1";
        }
        else if(option=="2")
        {

            cg.displayEverything();
            option="-1";
        }
        else if(option=="3")
        {
            string starting,destination;
            cin.ignore();
            cout<<"Enter a starting vertex: "<<endl;
            getline(cin,starting);
            cout<<"Enter an ending vertex: "<<endl;
            getline(cin,destination);
            cout<<cg.findDistance(starting,destination)<<endl;
            option="-1";
        }
        else if(option=="4")
        {
            string starting,destination;
            cin.ignore();
            cout<<"Enter a starting vertex: "<<endl;
            getline(cin,starting);
            cout<<"Enter an ending vertex: "<<endl;
            getline(cin,destination);
            cg.shortestDistance(starting,destination);
            option="-1";
        }
        else if(option=="5")
        {
            string starting,destination;
            int distance;
            cin.ignore();
            cout<<"Enter a starting vertex: "<<endl;
            getline(cin,starting);
            cout<<"Enter a destination vertex: "<<endl;
            getline(cin,destination);
            cout<<"Enter distance limit: "<<endl;
            cin>>distance;
            cg.limitedDistancePath(starting,destination,distance);
            option="-1";
        }
        else if(option=="6")
        {
            string vertex;
            cin.ignore();
            cout<<"Enter a vertex's name: "<<endl;
            getline(cin,vertex);
            cg.vertexInformation(vertex);
            option="-1";
        }
        else if(option=="7")
        {
            cg.graphInformation();
            option="-1";
        }
        else if(option=="8")
        {
            string vertex;
            cin.ignore();
            cout<<"Enter a vertex's name: "<<endl;
            getline(cin,vertex);
            cg.addVertex(vertex);
            option="-1";
        }
        else if(option=="9")
        {
            string v1,v2;
            int weight;
            cin.ignore();
            cout<<"Enter the first vertex's name: "<<endl;
            getline(cin,v1);
            cout<<"Enter the second vertex's name: "<<endl;
            getline(cin,v2);
            cout<<"Enter the distance between them: "<<endl;
            cin>>weight;
            cg.addEdge(v1,v2,weight);
            cg.addEdge(v2,v1,weight);
            option="-1";
        }
        else if(option=="@")
        {
            option="-1";
        }else if (option=="10"){
            string option2 = "-1";
            while (option2 == "-1"){
                cout<<"----------"<<endl;
                cout<<"Main Menu"<<endl;
                cout<<"----------"<<endl;
                cout<<"1. Add a service"<<endl;
                cout<<"2. Display services"<<endl;
                cout<<"0. Quit"<<endl;
                cin>>option2;

                if (option2 == "1"){
                    string name, service;
                    int cost;
                    cin.ignore();
                    cout <<"Enter the city name: "<<endl;
                    getline(cin,name);
                    cout <<"Enter the name of the service: "<<endl;
                    getline(cin,service);
                    cout <<"Enter the cost: "<<endl;
                    cin>>cost;
                    cg.addService(name,service,cost);
                    option2 = "-1";
                }else if (option2 == "2"){
                    cg.displayServices();
                    option2 = "-1";
                }
            }
            option = "-1";
        }else if(option=="0"){
            return 0;
        }
    }
    return 0;
}
