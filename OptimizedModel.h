//
// Created by ByteDance on 2022/4/24.
//

#ifndef NEO_OPTIMIZEDMODEL_H
#define NEO_OPTIMIZEDMODEL_H


#include <map>
#include <vector>

#include "Point.h"
#include "Facet.h"

class OptimizedModel {
public:
    int ratio = 10000; // 取点时的精度
    int epsilon = 20; // 判断两个点的距离是否过近
    std::map<size_t, std::vector<int>> indexMap; // 存储相同哈希值的点下标，方便快速查找
    std::vector<Point> points; // 所有不重复地点，顺序是有意义的
    std::vector<Facet> facets; // 所有入选的三角面（有的会因为间隙太小而不push进来）
    size_t hasher(Point& p);
};


#endif //NEO_OPTIMIZEDMODEL_H
