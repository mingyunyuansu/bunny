//
// Created by ByteDance on 2022/4/24.
//

#include "InputFromSTL.h"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

//Ϊһ��model�������
void InputFromSTL::init(OptimizedModel &model) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        std::cout << "open file failed, path: " << path << std::endl;
        exit(-1);
    }
    std::cout << "open " << path << " ok" << std::endl;
    std::string line, tmp;
    std::getline(ifs, line); // file name
    std::istringstream iss;
    double x, y, z;
    int cnt = 0;
    while (std::getline(ifs, line)) {
//        facet normal -0.060604 0.997443 -0.037878
//        outer loop
//        vertex -0.00110000 0.13140000 0.01460000
//        vertex -0.00160000 0.13110000 0.00750000
//        vertex -0.00410000 0.13110000 0.01150000
//        endloop
//        endfacet
        iss.str(line);
        iss >> tmp;
        // �����ļ���β
        if (tmp == ENDSOLID) {
            break;
        }
        // ��һ���Ի�ȡ�������������
        std::getline(ifs, line); // ��ȥ��������
        std::getline(ifs, line);
        iss.str(line);
        //iss >> std::fixed >> std::setprecision(6) >> tmp >> x >> y >> z;
        iss >> tmp >> x >> y >> z;
        Point a(x, y, z);

        std::getline(ifs, line);
        iss.str(line);
        iss >> tmp >> x >> y >> z;
        Point b(x, y, z);

        std::getline(ifs, line);
        iss.str(line);
        iss >> tmp >> x >> y >> z;
        Point c(x, y, z);

        std::getline(ifs, line); // ��ȥ��β����
        std::getline(ifs, line);

        int i1 = model.points.size();
        int i2 = i1 + 1; int i3 = i1 + 2; // ����������

        Facet facet{};
        int ni1 = isDupPoint(model, a, i1);
        int ni2 = isDupPoint(model, b, i2);
        int ni3 = isDupPoint(model, c, i3);

        if (ni1 != ni2 && ni1 != ni3 && ni2 != ni3) {
            // ������������û���ظ�������������Ч
            model.facets.emplace_back(ni1, ni2, ni3);
        }
    }
    std::cout << "finish parsing " << path << std::endl;
}

int InputFromSTL::isDupPoint(OptimizedModel &model, Point &point, int idx) {
    // �ж�һ�����Ƿ������ظ���
    size_t h = model.hasher(point);
    int ret = idx;
    if (model.indexMap.find(h) == model.indexMap.end()) {
        model.indexMap[h].push_back(idx); // �ù�ϣֵ������û�е�
    } else {
        for (int i = 0; i < model.indexMap[h].size(); ++i) {
            int old_point_idx = model.indexMap[h][i];
            if (distance(model, model.points[old_point_idx], point) < model.epsilon) {
                // ��������������߾���ͬһ���㣩
                ret = old_point_idx;
                break;
            } else {
                // ��ϣ��ɸͨ�������ǻ���Ҫ�ȶ�ʣ�µ����е㣬�Ա����ϣ��ͻ
                for (int j = 0; j < model.points.size(); ++j) {
                    if (distance(model, model.points[j], point) < model.epsilon) {
                        ret = j;
                        break;
                    }
                }
            }
        }
    }
    if (idx == ret) {
        // �õ���Ҫ���룬û�г�ͻ
        model.points.push_back(point);
    }
    return ret;
}

int InputFromSTL::distance(OptimizedModel& model,  Point&p1, Point &p2) {
    // ���������ľ���
    int dx = round(p1.x * model.ratio) - round(p2.x * model.ratio);
    int dy = round(p1.y * model.ratio) - round(p2.y * model.ratio);
    int dz = round(p1.z * model.ratio) - round(p2.z * model.ratio);
    return round(sqrt(dx * dx + dy * dy + dz * dz));
}