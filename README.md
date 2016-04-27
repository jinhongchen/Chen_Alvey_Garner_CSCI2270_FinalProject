# Chen_Alvey_Garner_CSCI2270_FinalProject
Final project
Team members: Jinhong Chen, Justin Eric Alvey , Patrick Micheal Garner


Project Description: Our project will use Graph data structure to implement "Trip-Planning" functionality for tourists or vacationers. From the main menu, the user can plan a trip where they would like to go. The viability of a trip (say the shortest distance) can be checked, based on the services available at each city (say stopping for gas - is there a gas station in town? If not, where do we fill up before we reach our destination.) The user can also choose to add services, if a local restaurant or hotel chain is not in the district listings. Our project is to allow users to plan an entertaining and relaxing vacation anywhere in the United States.


How to Run: Open verticesGraph.cbp in Code::Blocks. Build and run the Project. The project driver file is named main.cpp and houses all user interface functionality. The program starts with the following menu options:

"----------"
"Main Menu"
"----------"
"1.  Assign districts"
"2.  Display"
"3.  Find distance"
"4.  Find shortest distance"
"5.  Find a path with limited signals"
"6.  Vertex information"
"7.  Graph information"
"8.  Add vertex"
"9.  Add edge"
"10. Plan a Trip"
"0. Quit"

When the program runs, it reads in the data2.txt file as a command line argument. With this data file, a graph is built from the cities and locations. The initial district for every city is -1. To assign all linking cities to their respective districts, choose option 1. To display all cities in the graph and their linking cities, choose option 2 to display. To find the scalar total distance between two cities, choose option 3. For option 4, the user can find the sortest distance between two cities, and the path required to make this shortest distance. To find a more in-depth look at this limited path, choose option 5, which breaks down the path city by city and the individual distances between them. For information about a specific vertex, choose option 6, which shows the linking cities and district of this vertex. Option 7 displays information for the entire graph to the user. Option 8 allows the user to add a new vertex, to add a new city. Option 9 adds an edge to the graph, which will link two cities together by a specified distance. Option 10 is the main functionality of our project, which allows a user to plan a trip or vacation to a place of their choosing. This option opens up a new menu seen below.

"----------"
"Main Menu"
"----------"
"1. Add a service"
"2. Display services"
"3. Plan a Trip"
"0. Quit"

From this new menu, a user can plan their trip. Option 1 allows a user to add a new service to a specific city, such a mom and pop shop that is known to locals but not in the main database. A service is often either a hotel, restaurant, or gas station - all services needed to plan a successful vacation. Option 2 allows the user to display all services in the database, city by city. Option 3 provides the user with a unique travel route, from their starting location to their ending location. The program provides the user with key service stops along the way, based on the services available at each city. After about 300 miles, stop for food and gas, and if the user has to travel about 800 miles, stop at a hotel for the night. 

Option 0 backs the user out to the original menu, and Option 0 from there terminates the program.


Dependencies: No third-party libraries


System Requirements: Works best and developed on a Windows machine


Contributors:


Bugs: None to report on.

