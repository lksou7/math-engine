#pragma once 
#include <vector>
#include <set>
#include <unordered-set>

struct point {
    double x, y, z;
}//the points use is optional 

// The topological space is represented using two main data structures:
struct topological_space {
   std::vector<Point> points;  //the coordinates are still optional
   std::vector<std::set<int>> openSets; // 1. openSets – defines the topology
   std::vector<std::vector<int>> adjacency; // 2. adjacency/edges – captures connectivity between points

   bool coordinatesAvailable = false;
   bool adjacencyBuilt = false;

   void buildAdjacencyFromOpenSets();
   void buildOpenSetsFromAdjacency();
}



