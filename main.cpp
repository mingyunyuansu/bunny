#include <iostream>

#include "InputFromSTL.h"
#include "OptimizedModel.h"
#include "STL2VTK.h"

int main() {
    InputFromSTL inp;
    OptimizedModel model;
    inp.init(model);
    std::cout << "实际点数：" << model.points.size() << std::endl;
    std::cout << "实际三角面数：" << model.facets.size() << std::endl;

    STL2VTK vtk;
    vtk.generate(model);
}
