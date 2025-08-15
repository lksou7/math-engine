#include "Topology.hpp"

Topology::Topology(int numPoints, const OpenSetCollection& openSets) {
    points.resize(numPoints);
    this->openSets = openSets;
}

std::set<int> Topology::neighborhood(int p) {
    ensureAdjacency();
    return adjacency[p];
}

std::set<int> Topology::closure(const std::set<int>& A) {
    ensureAdjacency();
    std::set<int> result = A;
    for (int a : A) {
        result.insert(adjacency[a].begin(), adjacency[a].end());
    }
    return result;
}

std::set<int> Topology::interior(const std::set<int>& A) {
    ensureAdjacency();
    std::set<int> result;
    for (int a : A) {
        bool allNeighborsInside = true;
        for (int neighbor : adjacency[a]) {
            if (!A.count(neighbor)) {
                allNeighborsInside = false;
                break;
            }
        }
        if (allNeighborsInside) {
            result.insert(a);
        }
    }
    return result;
}

bool Topology::isConnected() {
    ensureAdjacency();
    std::set<int> visited;
    dfs(0, visited);
    return visited.size() == points.size();
}

void Topology::ensureAdjacency() {
    if (!adjacencyBuilt) {
        buildAdjacencyFromOpenSets();
    }
}

void Topology::dfs(int v, std::set<int>& visited) {
    visited.insert(v);
    for (int u : adjacency[v]) {
        if (!visited.count(u)) {
            dfs(u, visited);
        }
    }
}
