// src/main.cpp
#include <iostream>
#include <memory>
#include "figures.h"
#include "array.h"

using namespace std;

int main() {
    Array<shared_ptr<Figure<int>>> figures;
    
    // Create square
    auto square = make_shared<Square<int>>();
    cout << "Enter 4 points for square (x y) in order:" << "\n";
    cin >> *square;
    figures.push_back(square);
    
    // Create rectangle
    auto rectangle = make_shared<Rectangle<int>>();
    cout << "Enter 4 points for rectangle (x y) in order:" << "\n";
    cin >> *rectangle;
    figures.push_back(rectangle);
    
    // Create trapezoid
    auto trapezoid = make_shared<Trapezoid<int>>();
    cout << "Enter 4 points for trapezoid (x y) in order:" << "\n";
    cin >> *trapezoid;
    figures.push_back(trapezoid);
    
    // Output information about figures
    cout << "\nFigures information:" << "\n";
    double total_area = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        cout << "Figure " << i + 1 << ":" << "\n";
        cout << *figures[i];
        double area = static_cast<double>(*figures[i]);
        cout << "Area: " << area << "\n";
        auto center = figures[i]->center();
        cout << "Center: (" << center.getX() << ", " << center.getY() << ")" << "\n\n";
        total_area += area;
    }
    
    cout << "Total area of all figures: " << total_area << "\n";
    
    return 0;
}