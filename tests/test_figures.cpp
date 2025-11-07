// tests/test_figures.cpp
#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <cmath>
#include "../src/point.h"
#include "../src/array.h"
#include "../src/figure.h"
#include "../src/figures.h"

// ==================== ТЕСТЫ ДЛЯ POINT ====================

TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.getX(), 0);
    EXPECT_EQ(p.getY(), 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 4.2);
    EXPECT_DOUBLE_EQ(p.getX(), 3.5);
    EXPECT_DOUBLE_EQ(p.getY(), 4.2);
}

TEST(PointTest, AdditionOperator) {
    Point<int> p1(2, 3);
    Point<int> p2(4, 5);
    Point<int> result = p1 + p2;
    EXPECT_EQ(result.getX(), 6);
    EXPECT_EQ(result.getY(), 8);
}

TEST(PointTest, DivisionOperator) {
    Point<double> p(6.0, 8.0);
    Point<double> result = p / 2.0;
    EXPECT_DOUBLE_EQ(result.getX(), 3.0);
    EXPECT_DOUBLE_EQ(result.getY(), 4.0);
}

// ==================== ТЕСТЫ ДЛЯ ARRAY ====================

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 0);
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, PushBackAndSize) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_FALSE(arr.empty());
}

TEST(ArrayTest, AccessOperator) {
    Array<std::string> arr;
    arr.push_back("hello");
    arr.push_back("world");
    EXPECT_EQ(arr[0], "hello");
    EXPECT_EQ(arr[1], "world");
}

TEST(ArrayTest, OutOfRangeAccess) {
    Array<int> arr;
    arr.push_back(1);
    EXPECT_THROW(arr[1], std::out_of_range);
    EXPECT_THROW(arr[100], std::out_of_range);
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    Array<int> arr2(arr1);
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    Array<int> arr2(std::move(arr1));
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr1.size(), 0);
}

TEST(ArrayTest, AssignmentOperator) {
    Array<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    Array<int> arr2;
    arr2 = arr1;
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
}

TEST(ArrayTest, MoveAssignmentOperator) {
    Array<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    Array<int> arr2;
    arr2 = std::move(arr1);
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr1.size(), 0);
}

TEST(ArrayTest, ReserveAndCapacity) {
    Array<int> arr;
    arr.reserve(10);
    EXPECT_GE(arr.capacity(), 10);
    arr.push_back(1);
    arr.push_back(2);
    EXPECT_EQ(arr.size(), 2);
}

TEST(ArrayTest, Clear) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.clear();
    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, PopBack) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.pop_back();
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[1], 2);
}

TEST(ArrayTest, Resize) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.resize(5);
    EXPECT_EQ(arr.size(), 5);
    arr.resize(1);
    EXPECT_EQ(arr.size(), 1);
}

// ==================== ТЕСТЫ ДЛЯ POINT CONTAINER ====================

TEST(PointContainerTest, AddAndAccessPoints) {
    PointContainer<Point<int>> container;
    container.push_back(std::make_unique<Point<int>>(1, 2));
    container.push_back(std::make_unique<Point<int>>(3, 4));
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0].getX(), 1);
    EXPECT_EQ(container[0].getY(), 2);
    EXPECT_EQ(container[1].getX(), 3);
    EXPECT_EQ(container[1].getY(), 4);
}

TEST(PointContainerTest, OutOfRangeAccess) {
    PointContainer<Point<int>> container;
    container.push_back(std::make_unique<Point<int>>(1, 2));
    EXPECT_THROW(container[1], std::out_of_range);
}

TEST(PointContainerTest, MoveConstructor) {
    PointContainer<Point<int>> container1;
    container1.push_back(std::make_unique<Point<int>>(1, 2));
    PointContainer<Point<int>> container2(std::move(container1));
    EXPECT_EQ(container2.size(), 1);
    EXPECT_EQ(container1.size(), 0);
}

// ==================== ТЕСТЫ ДЛЯ SQUARE ====================

TEST(SquareTest, AddPoints) {
    Square<int> square;
    square.add_point(Point<int>(0, 0));
    square.add_point(Point<int>(2, 0));
    square.add_point(Point<int>(2, 2));
    square.add_point(Point<int>(0, 2));
    EXPECT_EQ(square.get_points_count(), 4);
}

TEST(SquareTest, CenterCalculation) {
    Square<int> square;
    square.add_point(Point<int>(0, 0));
    square.add_point(Point<int>(4, 0));
    square.add_point(Point<int>(4, 4));
    square.add_point(Point<int>(0, 4));
    Point<int> center = square.center();
    EXPECT_EQ(center.getX(), 2);
    EXPECT_EQ(center.getY(), 2);
}

TEST(SquareTest, AreaCalculation) {
    Square<int> square;
    square.add_point(Point<int>(0, 0));
    square.add_point(Point<int>(3, 0));
    square.add_point(Point<int>(3, 3));
    square.add_point(Point<int>(0, 3));
    double area = static_cast<double>(square);
    EXPECT_DOUBLE_EQ(area, 9.0);
}


TEST(SquareTest, StreamInput) {
    Square<int> square;
    std::stringstream ss("1 1 3 1 3 3 1 3");
    ss >> square;
    EXPECT_EQ(square.get_points_count(), 4);
}

TEST(SquareTest, CopyConstructor) {
    Square<int> square1;
    square1.add_point(Point<int>(0, 0));
    square1.add_point(Point<int>(2, 0));
    Square<int> square2(square1);
    EXPECT_EQ(square2.get_points_count(), 2);
}

// ==================== ТЕСТЫ ДЛЯ RECTANGLE ====================

TEST(RectangleTest, AddPoints) {
    Rectangle<int> rect;
    rect.add_point(Point<int>(0, 0));
    rect.add_point(Point<int>(4, 0));
    rect.add_point(Point<int>(4, 2));
    rect.add_point(Point<int>(0, 2));
    EXPECT_EQ(rect.get_points_count(), 4);
}

TEST(RectangleTest, CenterCalculation) {
    Rectangle<int> rect;
    rect.add_point(Point<int>(0, 0));
    rect.add_point(Point<int>(6, 0));
    rect.add_point(Point<int>(6, 3));
    rect.add_point(Point<int>(0, 3));
    Point<int> center = rect.center();
    EXPECT_EQ(center.getX(), 3);
    EXPECT_EQ(center.getY(), 1);
}


TEST(RectangleTest, CopyConstructor) {
    Rectangle<int> rect1;
    rect1.add_point(Point<int>(0, 0));
    rect1.add_point(Point<int>(2, 0));
    Rectangle<int> rect2(rect1);
    EXPECT_EQ(rect2.get_points_count(), 2);
}

// ==================== ТЕСТЫ ДЛЯ TRAPEZOID ====================

TEST(TrapezoidTest, AddPoints) {
    Trapezoid<int> trapezoid;
    trapezoid.add_point(Point<int>(0, 0));
    trapezoid.add_point(Point<int>(4, 0));
    trapezoid.add_point(Point<int>(3, 2));
    trapezoid.add_point(Point<int>(1, 2));
    EXPECT_EQ(trapezoid.get_points_count(), 4);
}

TEST(TrapezoidTest, CenterCalculation) {
    Trapezoid<int> trapezoid;
    trapezoid.add_point(Point<int>(0, 0));
    trapezoid.add_point(Point<int>(4, 0));
    trapezoid.add_point(Point<int>(3, 3));
    trapezoid.add_point(Point<int>(1, 3));
    Point<int> center = trapezoid.center();
    EXPECT_EQ(center.getX(), 2);
    EXPECT_EQ(center.getY(), 1);
}

TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid<int> trapezoid;
    trapezoid.add_point(Point<int>(0, 0));
    trapezoid.add_point(Point<int>(4, 0));
    trapezoid.add_point(Point<int>(3, 3));
    trapezoid.add_point(Point<int>(1, 3));
    double area = static_cast<double>(trapezoid);
    EXPECT_NEAR(area, 9.0, 0.1);
}

TEST(TrapezoidTest, StreamInput) {
    Trapezoid<int> trapezoid;
    std::stringstream ss("0 0 4 0 3 3 1 3");
    ss >> trapezoid;
    EXPECT_EQ(trapezoid.get_points_count(), 4);
}

TEST(TrapezoidTest, CopyConstructor) {
    Trapezoid<int> trapezoid1;
    trapezoid1.add_point(Point<int>(0, 0));
    trapezoid1.add_point(Point<int>(2, 0));
    Trapezoid<int> trapezoid2(trapezoid1);
    EXPECT_EQ(trapezoid2.get_points_count(), 2);
}

// ==================== ТЕСТЫ ДЛЯ FIGURE CONTAINER ====================

TEST(FigureContainerTest, StoreDifferentFigures) {
    Array<std::shared_ptr<Figure<int>>> figures;
    auto square = std::make_shared<Square<int>>();
    square->add_point(Point<int>(0, 0));
    auto rect = std::make_shared<Rectangle<int>>();
    rect->add_point(Point<int>(0, 0));
    figures.push_back(square);
    figures.push_back(rect);
    EXPECT_EQ(figures.size(), 2);
}

TEST(FigureContainerTest, PolymorphicBehavior) {
    Array<std::shared_ptr<Figure<int>>> figures;
    auto square = std::make_shared<Square<int>>();
    square->add_point(Point<int>(0, 0));
    square->add_point(Point<int>(2, 0));
    square->add_point(Point<int>(2, 2));
    square->add_point(Point<int>(0, 2));
    figures.push_back(square);
    
    // Используем переменные чтобы избежать предупреждений
    double area = static_cast<double>(*figures[0]);
    Point<int> center = figures[0]->center();
    
    EXPECT_GT(area, 0);
    EXPECT_EQ(center.getX(), 1);
    EXPECT_EQ(center.getY(), 1);
}

TEST(FigureContainerTest, TotalAreaCalculation) {
    Array<std::shared_ptr<Figure<int>>> figures;
    auto square = std::make_shared<Square<int>>();
    square->add_point(Point<int>(0, 0));
    square->add_point(Point<int>(2, 0));
    square->add_point(Point<int>(2, 2));
    square->add_point(Point<int>(0, 2));
    auto rect = std::make_shared<Rectangle<int>>();
    rect->add_point(Point<int>(0, 0));
    rect->add_point(Point<int>(3, 0));
    rect->add_point(Point<int>(3, 2));
    rect->add_point(Point<int>(0, 2));
    figures.push_back(square);
    figures.push_back(rect);
    double total_area = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_area += static_cast<double>(*figures[i]);
    }
    EXPECT_DOUBLE_EQ(total_area, 4.0 + 6.0);
}

// ==================== ИНТЕГРАЦИОННЫЕ ТЕСТЫ ====================

TEST(IntegrationTest, CompleteWorkflow) {
    Array<std::shared_ptr<Figure<int>>> figures;
    auto square = std::make_shared<Square<int>>();
    square->add_point(Point<int>(0, 0));
    square->add_point(Point<int>(2, 0));
    square->add_point(Point<int>(2, 2));
    square->add_point(Point<int>(0, 2));
    auto rect = std::make_shared<Rectangle<int>>();
    rect->add_point(Point<int>(0, 0));
    rect->add_point(Point<int>(4, 0));
    rect->add_point(Point<int>(4, 3));
    rect->add_point(Point<int>(0, 3));
    figures.push_back(square);
    figures.push_back(rect);
    EXPECT_EQ(figures.size(), 2);
    
    for (size_t i = 0; i < figures.size(); ++i) {
        // Используем переменные в проверках
        auto center = figures[i]->center();
        double area = static_cast<double>(*figures[i]);
        
        EXPECT_GT(area, 0);
        // Проверяем что центр находится в разумных пределах
        EXPECT_GE(center.getX(), 0);
        EXPECT_GE(center.getY(), 0);
    }
}

TEST(IntegrationTest, MoveSemantics) {
    Array<std::shared_ptr<Figure<int>>> figures1;
    auto square = std::make_shared<Square<int>>();
    square->add_point(Point<int>(0, 0));
    figures1.push_back(square);
    Array<std::shared_ptr<Figure<int>>> figures2 = std::move(figures1);
    EXPECT_EQ(figures2.size(), 1);
    EXPECT_EQ(figures1.size(), 0);
}

// ==================== ТЕСТЫ ГРАНИЧНЫХ СЛУЧАЕВ ====================

TEST(EdgeCaseTest, SinglePointFigure) {
    Square<int> square;
    square.add_point(Point<int>(5, 5));
    EXPECT_EQ(square.get_points_count(), 1);
    Point<int> center = square.center();
    EXPECT_EQ(center.getX(), 5);
    EXPECT_EQ(center.getY(), 5);
}

TEST(EdgeCaseTest, LargeArray) {
    Array<int> arr;
    for (int i = 0; i < 1000; ++i) {
        arr.push_back(i);
    }
    EXPECT_EQ(arr.size(), 1000);
    EXPECT_EQ(arr[999], 999);
}

TEST(EdgeCaseTest, SelfAssignment) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr = arr;
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

// ==================== ТЕСТЫ РАЗНЫХ ТИПОВ ДАННЫХ ====================

TEST(TypeTest, DoublePoints) {
    Point<double> p(1.5, 2.5);
    EXPECT_DOUBLE_EQ(p.getX(), 1.5);
    EXPECT_DOUBLE_EQ(p.getY(), 2.5);
}

TEST(TypeTest, FloatFigures) {
    Square<float> square;
    square.add_point(Point<float>(0.5f, 0.5f));
    square.add_point(Point<float>(2.5f, 0.5f));
    square.add_point(Point<float>(2.5f, 2.5f));
    square.add_point(Point<float>(0.5f, 2.5f));
    Point<float> center = square.center();
    EXPECT_FLOAT_EQ(center.getX(), 1.5f);
    EXPECT_FLOAT_EQ(center.getY(), 1.5f);
}

// ==================== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ====================

TEST(AdditionalTest, ArrayOfFiguresAreaSum) {
    Array<std::shared_ptr<Figure<int>>> figures;
    
    auto square = std::make_shared<Square<int>>();
    square->add_point(Point<int>(0, 0));
    square->add_point(Point<int>(1, 0));
    square->add_point(Point<int>(1, 1));
    square->add_point(Point<int>(0, 1));
    
    auto rectangle = std::make_shared<Rectangle<int>>();
    rectangle->add_point(Point<int>(0, 0));
    rectangle->add_point(Point<int>(2, 0));
    rectangle->add_point(Point<int>(2, 1));
    rectangle->add_point(Point<int>(0, 1));
    
    figures.push_back(square);
    figures.push_back(rectangle);
    
    double total = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total += static_cast<double>(*figures[i]);
    }
    
    EXPECT_DOUBLE_EQ(total, 1.0 + 2.0); // 1 (квадрат) + 2 (прямоугольник)
}

TEST(AdditionalTest, PointContainerSize) {
    PointContainer<Point<int>> container;
    EXPECT_EQ(container.size(), 0);
    
    container.push_back(std::make_unique<Point<int>>(1, 1));
    EXPECT_EQ(container.size(), 1);
    
    container.push_back(std::make_unique<Point<int>>(2, 2));
    EXPECT_EQ(container.size(), 2);
}