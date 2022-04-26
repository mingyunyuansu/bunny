#include <iostream>

#include "InputFromSTL.h"
#include "OptimizedModel.h"
#include "STL2VTK.h"

int main() {
    InputFromSTL inp;
    OptimizedModel model;
    inp.init(model);
    std::cout << "ʵ�ʵ�����" << model.points.size() << std::endl;
    std::cout << "ʵ������������" << model.facets.size() << std::endl;

    STL2VTK vtk;
    vtk.generate(model);
}
