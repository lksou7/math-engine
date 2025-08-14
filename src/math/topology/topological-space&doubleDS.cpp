#include <topological-space&doubleDS.hpp>
#include <algorithm>

void topological_space::buildAdjacencyFromOpenSets() {
   size_t n = points.size();
   adjacency.assign(n, {});
   std::vector<std::unordered_set<int>> adjSet(n); //just to avoid duplicates for now 

    for (const auto& openSet : openSets) {
// this should connect all points within an openset or the opensets dunno depends on the input
        for (auto it1 = openSet.begin(); it1 != openSet.end(); ++it1) {
            for (auto it2 = std::next(it1); it2 != openSet.end(); ++it2) {
                int u = *it1;
                int v = *it2;
                adjSet[u].insert(v);
                adjSet[v].insert(u);
            }
        }
    }
   
//this converts the unordered set to a vector for establishing the final adjanecy list   
    for (size_t i = 0; i < n; ++i) {
        adjacency[i] = std::vector<int>(adjSet[i].begin(), adjSet[i].end());
   } 
} 

void topological_space::buildOpenSetsFromAdjacency() {
    openSets.clear();
    size_t n = adjacency.size();
//the adjanecy forms an openset with the node
     for (size_t i = 0; i < n; ++i) {
        std::set<int> openSet;
        openSet.insert((int)i);
        for (int a  : adjacency[i]) {
            openSet.insert(a);
        }
        openSets.push_back(openSet);
    }
}

// testih bilehi ya safa 
