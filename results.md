Shiv Gohil, Binh Minh Nguyen, Nuoyan Wang, Andrew Zhao<br>
Carl Evans, Brad Solomon, Thierry Ramais<br>
CS 225<br>
12 December 2022<br>
# CS225 Final Project Report <br>
## Introduction <br>
Throughout the process of this project, we aimed to answer the fundamental question: Using a dataset of road intersections and edges and a dataset of airport locations, how can we best implement a “Shortest-Route Finder” using a graph data structure and algorithms? Ultimately, we represented intersections and airports as nodes in our graph, with road connections and air flights as the edges. Moreover, having decided on using California as our map area, we needed to complete the following stages: data cleaning and parsing, a graph implementation, as well as graph algorithms (BFS, Kruskal’s and A-star). 
## Data Cleaning
First, we need to retrieve the data from our online datasets, and convert its format in the following way, keeping the pertinent information for our routeFinder application: 

    Nodes: (NodeID, transportType[0=road, 1=flight], name, longitude, latitude)
    Edges: (EdgeID, transportType[0=road, 1=flight], startID, endID, direct-distance)

In this manner, we can later create weighted edges, where the weight is determined by distance multiplied by different factors for air and ground travel. Here, distance is the euclidean distance between two points, measured in units of “degrees of longitude-latitude.” We later omit the curvature of the Earth when converting from these degrees into units of miles or km. <br>

Having decided on this format, we begin data cleaning within the “getCleanedData.cpp” file. Our function takes input filenames for the 3 datasets containing the California intersections, California road edges, and the World airports. For each of these three datasets, we iterate through the .dat file line by line, separating each line into vectors of strings depending on the comma-separated or space-separated nature of the original data file. As we iterate through, we need to omit erroneous data, such as duplicating edges, self-looping edges, as well as all non-commercial and non-California airports. The data we want within each individual line-by-line vector is then selected and output into output nodes.txt and edges.txt files, according to the formats in bold above. <br>

Now, our output nodes.txt file contains the road intersection and airport nodes, while our edges.txt file contains the road edges between select intersections. We still need to create flight edges between airports. To do this, we make the assumption that each of our selected airports has a flight to-and-from every other airport. We want to append these flights as edges in our output edges.txt files. To accomplish this, we need to add a portion of code within the airport data cleaning, allowing us to store a vector of just the airport nodes we want. Then, we simply use a nested for loop to create edges between every pair of airports, which are then appended to our edges.txt file as strings on each line.
