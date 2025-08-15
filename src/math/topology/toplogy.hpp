#pragma once
#include "topological-space&doubleDS.hpp"

class topology : public topological_space {
public:
    topology(int numPoints, const OpenSetCollection& openSets);

    std::set<int> neighborhood(int p);
    std::set<int> closure(const std::set<int>& A);
    std::set<int> interior(const std::set<int>& A);
    bool isConnected();

private:
    void ensureAdjacency();
    void dfs(int v, std::set<int>& visited);
};
