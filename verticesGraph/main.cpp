#include <iostream>
#include <climits>
#include "verticesGraph.h"

using namespace std;

int main(int argc, char * argv[])
{
    if(argc!=2) {
        cout << "please provide input file data2.txt in the command line" << endl;
        return 0;
    }
    char * fileName=argv[1];
    verticesGraph cg(fileName);

    string option="-1";
    cg.addService("Boulder","PDQ","Gas Station",3);
    cg.addService("Boulder","Best Western Plus","Hotel",400);
    cg.addService("Boulder","Golden Sun","Food",20);
    cg.addService("Boulder","Red Robin","Food",35);

    cg.addService("Boston","Change for the Road","Gas Station",2);
    cg.addService("Boston","Our House, Su House Too","Hotel",350);
    cg.addService("Boston","East Coast Fish N Fry","Food",45);

    cg.addService("Chicago","Windy Eats","Food",18);
    cg.addService("Chicago","High-Rise Hotel 5 Stars","Hotel",750);
    cg.addService("Chicago","Frank's Refill","Gas Station",4);

    cg.addService("Disneyland","Fairy Island BrunchHouse", "Food",45);
    cg.addService("Disneyland","Disney Gas and Oil Stop","Gas Station",4);
    cg.addService("Disneyland","Magic Castle Hotel","Hotel",600);

    cg.addService("Miami","Sun Set Diner","Food",25);
    cg.addService("Miami","Florida Gas","Gas Station",3);
    cg.addService("Miami","Palm Tree Plus Inn","Hotel",650);

    cg.addService("New Orleans","City Down By the Bay","Hotel",500);
    cg.addService("New Orleans","Louisiana Livin","Food",30);
    cg.addService("New Orleans","Oil from the Gulf","Gas Station",3);

    cg.addService("New York","Manhattan House","Hotel",500);
    cg.addService("New York","City Escape Cafe and Grill","Food",25);
    cg.addService("New York","NY Oil and Gas Stop","Gas Station",3);

    cg.addService("Portland","Night Owls Inn","Hotel",550);
    cg.addService("Portland","Food N Stuff","Food",30);
    cg.addService("Portland","Buenas Noches","Hotel",350);
    cg.addService("Portland","$2 a Barrel","Gas Station",2);

    cg.addService("San Francisco","Seafood by the Bay","Food",37);
    cg.addService("San Francisco","West Coast In and Suites","Hotel",525);
    cg.addService("San Francisco","Shell and Co.","Gas Station",3);

    cg.addService("Seattle","Fish Mart","Food",40);
    cg.addService("Seattle","Hawkeye Suites","Hotel",490);
    cg.addService("Seattle","Seattle Gas Experts","Gas Station",3);


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
            int check = cg.findDistance(starting,destination);
            if (check > 0){
                cout<<check<<endl;
            }else{
                if (check == -1){
                    cout<<"At least one vertex doesn't exist."<<endl;
                }else if (check == 0){
                    cout<<"Cities are not in the same district"<<endl;
                }
            }
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
            string starting,destination,limit;
            cin.ignore();
            cout<<"Enter a starting vertex: "<<endl;
            getline(cin,starting);
            cout<<"Enter a destination vertex: "<<endl;
            getline(cin,destination);
            cout<<"Enter distance limit: "<<endl;
            getline(cin,limit);
            cg.limitedDistancePath(starting,destination,limit);
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
                cout<<"3. Plan a Trip"<<endl;
                cout<<"0. Quit"<<endl;
                cin>>option2;

                if (option2 == "1"){
                    string name, service, type;
                    int cost;
                    cin.ignore();
                    cout <<"Enter the city name: "<<endl;
                    getline(cin,name);
                    cout <<"Enter the name of the service: "<<endl;
                    getline(cin,service);
                    cout <<"Enter the type of service: "<<endl;
                    getline(cin,type);
                    while (0==0)
                    {
                        cout <<"Enter the cost: "<<endl;
                        cin>>cost;
                        if(cost>0&&cost<INT_MAX)
                        {
                            cg.addService(name,service,type,cost);
                            break;
                        }
                        else
                        {
                            std::cout<<"Invalid input"<<std::endl;
                            cin.clear();
                            cin.ignore(1000,'\n');
                        }
                    }
                    option2 = "-1";
                }else if (option2 == "2"){
                    cg.displayServices();
                    option2 = "-1";
                }else if (option2 == "3"){
                    cin.ignore();
                    string starting,ending;
                    cout <<"Enter starting city name: "<<endl;
                    getline(cin,starting);
                    cout <<"Enter ending city name: "<<endl;
                    getline(cin,ending);
                    cg.assignDistricts();
                    int distance = 1500;
                    cg.planYourPath(starting,ending,distance);
                }
            }
            option = "-1";
        }else if(option=="0"){
            return 0;
        }
    }
    return 0;
}
