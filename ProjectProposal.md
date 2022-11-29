## Leading Question 
<br>

(we accidentally submitted the wrong leading question last time, here is the updated)
Given datasets of a road network and public transport network, we want to create a trip planning program that can minimize our total travel time. The program should take into account travel speeds depending on travel type (ie: road network vs public transit). The user will input longitude/latitude coordinates of their start and end, and the trip planner will create a route and give a rough estimate of travel time.

For example, if we use the given data sets of all California intersections as the first data set, the list of California airports as the 2nd, we can generate trips between famous landmarks and cities given their coordinates by the user. To do this, we will use Kruskal’s Minimum Spanning Tree algorithm, which gives us the minimum road/transportation network which connects all of our points of interest. This may give us a short path (that uses the minimum network), but we will additionally use A* algorithm to find a weighted shortest path, where the weights represent travel time between two nodes. This will help us find the shortest time path. This idea can be applied to other places and datasets. For example, we could use the Champaign-Urbana intersections/roads as our first data set and then have the CU MTD bus stations as our 2nd dataset, and finally user input of UIUC buildings as coordinates to help students plan out the most efficient trip. 

## Dataset Acquisition

## Data Format

We will use the California Road Network and Points of Interest as our dataset, as well as the OpenFlights dataset for California airports. The Road Network data will contain Nodes with a NodeID, as well as longitude and latitude data. These nodes represent intersections or endpoints of roads. Also, it will contain Edges with an EdgeID as well as startNode and endNode. This means we will assume roads run straight between two intersections. Moreover, we will use only part of the flight dataset that involves a destination and departure location both within California. To solve the issue of “What is the ideal travel plan between two locations in California,” we will use the road network dataset to calculate the total shortest path through driving, as well as the distances between nearby airports to calculate the alternate route using airplanes. 

California Road Network Data: 
https://www.cs.utah.edu/~lifeifei/SpatialDataset.htm
Nodes, each line represents: (NodeID, 0, 0, longitude, latitude) 
https://www.cs.utah.edu/~lifeifei/research/tpq/cal.cnode
Edges, each line represents: (EdgeID, 0, startNodeID, endID, direct-distance)
https://www.cs.utah.edu/~lifeifei/research/tpq/cal.cedge
OpenFlights Plane Data, each line represents: (AirportID, 1, Name, Longitude, Latitude)
https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat
We will create our own new dataset of Flight edges, where we assume each airport connects to each other airport. Each line in this flight edge dataset represents: (FlightID, 1, startAirport, endAirport, direct-distance)

i.e For our nodes we will format it as (ID, transportType[0=road, 1=flight], name, longitude, latitude)
For our edges we will format it as (ID, transportType[0=road, 1=flight], startID, endID, direct-distance)


## Data Correction

For Data Correction, if an edge connects to a nonexistent vertex, we get rid of the edge. Additionally, if we get multiple edges connecting to the same two vertices then we choose the shorter of the two; if they are the same length, then we can just arbitrarily choose either one. For our vertex, if there are any missing entries (or negative lengths) then we can log an error file and have the user correct it manually or to not add the vertex with missing details. Additionally, for our 2nd data set of airports for example, we would have to find the closest coordinates of the first data set by naive search and then have an edge of distance 0 connect to the airport so that we can create seamless connections from roads to airports or other types of data sets given user input. 

## Data Storage

Our graph will be made up of three data structures: Nodes, Edges, and a Data table. Our graph will contain a vector of Nodes where each Node represents a location with it holding a unique ID, Lat/Long coordinates, and an Adjacency List which will be another vector of pointers to the connected edges. The Edges will be another data structure that will contain a unique ID, a start and end Node ID, the distance between the two nodes, and a Route Type ID (given as unsigned integers) dictating whether we are a plane route, railway, road etc… Finally, we have the Data Table; this will be a vector that stores another vector that contains our path speed and fixed cost given in time. As a result given the Route Type ID, we can access the data table vector and then access its vector for the speed or fixed cost depending on the given scenario

<br>
n = |V| (number of vertex/nodes)<br>
m = |E| (number of edges)
<br>
Nodes: stored in vector - O(n*m) space <br>
ID - O(1) space <br>
Lat/Long - O(1) space <br>
Adjacency List (vector of pointers to edge object) - O(m) space <br>
<br> 
Edge: stored in vector<br> 
ID - O(1) space <br>
Start Node ID - O(1) space <br>
End Node ID - O(1) space <br>
Distance - O(1) space <br>
Route Type ID (road or plane route in our datasets) - O(1) space <br>
<br>
Data table - O(number of route types) space:<br>
Route Type ID to variable cost (in our version speed) + fixed cost (time) - O(1) space<br>
vector<std::vector<int/double>>, vector instead of pair for extensibility<br>
<br>

## Algorithm 

For our graph traversal, we will be using a BFS Traversal. Our graph will be undirected to represent the concept that we can fly or drive in each direction between two intersections or two airports. Edges will be weighted according to the distance between the two nodes, as a representation of travel time. Distances will be calculated as straight-line distance between the two nodes, based on their latitude and longitude.

For our Graph Algorithms, we plan to use Kruskal’s Minimum Spanning Tree algorithm. This algorithm offers us the minimum amount of edges required to connect all of our nodes, this would be useful for our user as it would give the user a completed route that would be able to visit all the points of interest given. This Algorithm would take in our graph data structure and that graph would have all the relevant information needed for the algorithm. Once completed, the algorithm would output a Sub-Graph that contains all the connected Nodes and their min amount Edges. Finally, for our run time, we are hoping to have it take O(n+m+mlog(m) time where n are nodes and m are edges; additionally, we expect this to take O(n+m) space. 

For our 2nd algorithm, we wish to use the A* algorithm. This algorithm would give a short path, but not necessarily the shortest path, given a start and ending Node. This would be incredibly important to our user as this would be what gives the user one of the shortest paths to take for their destination and then compare if the first data set’s method of transportation is more efficient or if the 2nd one is better. A* will take in our Graph with its vector of nodes and edges, but it will also take in a starting and destination node. It will then output the total trip cost and a subgraph of the original with the nodes and edges with one of the most efficient paths. A* also has an additional Heuristic of where we could calculate distance based on GPS coordinates, but we would have to assume flat land as a more complex algorithm would be needed. Finally, A* would take O(n*logn +m) time and O(n+m) space. 


MST Alg (Kruskal’s) - O(n+m + mlog(m)) time - O(n+m) space:<br>
Input:<br>
Graph<br>
List of vertex/nodes (graph) w/ edge list<br>
Edge set<br>
Returns:<br>
Sub-Graph<br>
Nodes (need it for edge set)<br>
Edge set (min amount)<br>

<br>
A* - O(n*logn + m) time (bad time) - O(n+m) space:<br>
Input:<br>
List of vertex/nodes<br>
Location<br>
Edge list<br>
Starting Node<br>
Destination Node<br>
Output:<br>
Graph with nodes and edges showing efficient path (subgraph of original)<br>
Total trip cost<br>
Heuristic:<br>
Distance based on GPS coordinates (could be distance formula treating coords as flat surface, could be a more complex algorithm to get real distance, etc.).<br>
<br>

## Timeline

Week 1 (Oct-Nov 5): 
Group Meet-up, introductions, discuss interests
Brainstorm and finalize our plan. Write up the proposal, schedules, and study the algorithms we will be implementing, thorough video watching on Youtube. 
Divide and assign the various tasks to individuals, and decide on future meetings

Week 2 (Nov 6 - Nov 12): 
By Sunday Nov 13th, figure out the data formatting and have our parsed data.
Afterwards, Begin to write and test algorithms and functions. 
Hold a weekly	meeting to check-in on each others’ progress, help each other out if anyone is left behind.

Week 3 (Nov 13 - Nov 19): 
write and test algorithms and functions
Present what we have for these functions and datasets to our advisor for mid-project deliverable
Mid-Project Dues: Nov 14-18th

Week 4 (Nov 19 - Nov 26) Thanksgiving Break: 

Week 5 (Nov 27 - Dec 4): 
After Thanksgiving, we will tidy up and finish all algorithms and begin work on the presentation, readme, report, and video.
Complete final deliverables and fix any errors. Finalize and complete the project.
Deadline: Dec 8th
