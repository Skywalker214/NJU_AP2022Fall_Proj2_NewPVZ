#ifndef HELPER_H
#define HELPER_H
#include <vector>
struct MapInfo
{
    int x;
    int y;
    std::vector<std::vector<int>> map;
    std::vector<std::pair<int, int>> zombie_birthplace;
    std::vector<std::pair<int, int>> home;
    std::vector<std::vector<std::pair<int, int>>> routes;
};

#endif // HELPER_H
