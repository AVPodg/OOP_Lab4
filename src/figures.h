#pragma once
#include "figure.h"

// Квадрат
template<class T>
class Square : public Figure<T> {
public:
    Square() { std::cout << "Enter points for square (4 points in order):\n"; }
    
    Square(const Square<T>& other) : Figure<T>() {  
        for (size_t i = 0; i < other.get_points_count(); ++i) {
            this->add_point(other.get_point(i));
        }
    }

    Point<T> center() const override {
        T sum_x = 0, sum_y = 0;
        size_t count = this->get_points_count();
        
        for (size_t i = 0; i < count; ++i) {
            sum_x += this->get_point(i).getX();
            sum_y += this->get_point(i).getY();
        }
        
        return Point<T>(sum_x / count, sum_y / count);
    }

    operator double() override {
        // Для квадрата вычисляем площадь как квадрат длины стороны
        const auto& p1 = this->get_point(0);
        const auto& p2 = this->get_point(1);
        
        T side = std::abs(p2.getX() - p1.getX()); // длина стороны
        return static_cast<double>(side * side);
    }

    friend std::ostream& operator<<(std::ostream& os, const Square<T>& figure) {
        os << "Square with " << figure.get_points_count() << " points:\n";
        for (size_t i = 0; i < figure.get_points_count(); ++i) {
            const auto& p = figure.get_point(i);
            os << "Point " << i << ": (" << p.getX() << ", " << p.getY() << ")\n";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Square<T>& square) {
        for (int i = 0; i < 4; ++i) {
            T x, y;
            if (!(is >> x >> y)) break;
            square.add_point(Point<T>(x, y));
        }
        return is;
    }
};

// Прямоугольник
template<class T>
class Rectangle : public Figure<T> {
public:
    Rectangle() { std::cout << "Enter points for rectangle (4 points in order):\n"; }
    
    Rectangle(const Rectangle<T>& other) : Figure<T>() {  
        for (size_t i = 0; i < other.get_points_count(); ++i) {
            this->add_point(other.get_point(i));
        }
    }

    Point<T> center() const override {
        T sum_x = 0, sum_y = 0;
        size_t count = this->get_points_count();
        
        for (size_t i = 0; i < count; ++i) {
            sum_x += this->get_point(i).getX();
            sum_y += this->get_point(i).getY();
        }
        
        return Point<T>(sum_x / count, sum_y / count);
    }

    operator double() override {
        // Для прямоугольника вычисляем площадь как длина * ширина
        const auto& p1 = this->get_point(0);
        const auto& p2 = this->get_point(1);
        const auto& p3 = this->get_point(2);
        
        T length = std::abs(p2.getX() - p1.getX()); // длина
        T width = std::abs(p3.getY() - p2.getY());  // ширина
        
        return static_cast<double>(length * width);
    }

    friend std::ostream& operator<<(std::ostream& os, const Rectangle<T>& figure) {
        os << "Rectangle with " << figure.get_points_count() << " points:\n";
        for (size_t i = 0; i < figure.get_points_count(); ++i) {
            const auto& p = figure.get_point(i);
            os << "Point " << i << ": (" << p.getX() << ", " << p.getY() << ")\n";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Rectangle<T>& rectangle) {
        for (int i = 0; i < 4; ++i) {
            T x, y;
            if (!(is >> x >> y)) break;
            rectangle.add_point(Point<T>(x, y));
        }
        return is;
    }
};

// Трапеция
template<class T>
class Trapezoid : public Figure<T> {
public:
    Trapezoid() { std::cout << "Enter points for trapezoid (4 points in order):\n"; }
    
    Trapezoid(const Trapezoid<T>& other) : Figure<T>() {  
        for (size_t i = 0; i < other.get_points_count(); ++i) {
            this->add_point(other.get_point(i));
        }
    }

    Point<T> center() const override {
        T sum_x = 0, sum_y = 0;
        size_t count = this->get_points_count();
        
        for (size_t i = 0; i < count; ++i) {
            sum_x += this->get_point(i).getX();
            sum_y += this->get_point(i).getY();
        }
        
        return Point<T>(sum_x / count, sum_y / count);
    }

    operator double() override {
        // Для трапеции используем формулу площади через координаты (метод гаусса)
        const size_t n = this->get_points_count();
        double sum = 0.0;
        
        for (size_t i = 0; i < n; ++i) {
            const auto &p = this->get_point(i);
            const auto &q = this->get_point((i + 1) % n);
            double xi = static_cast<double>(p.getX());
            double yi = static_cast<double>(p.getY());
            double xj = static_cast<double>(q.getX());
            double yj = static_cast<double>(q.getY());
            sum += xi * yj - xj * yi;
        }
        
        return std::abs(sum) * 0.5;
    }

    friend std::ostream& operator<<(std::ostream& os, const Trapezoid<T>& figure) {
        os << "Trapezoid with " << figure.get_points_count() << " points:\n";
        for (size_t i = 0; i < figure.get_points_count(); ++i) {
            const auto& p = figure.get_point(i);
            os << "Point " << i << ": (" << p.getX() << ", " << p.getY() << ")\n";
        }
        return os;
}

    friend std::istream& operator>>(std::istream& is, Trapezoid<T>& trapezoid) {
        for (int i = 0; i < 4; ++i) {
            T x, y;
            if (!(is >> x >> y)) break;
            trapezoid.add_point(Point<T>(x, y));
        }
        return is;
    }
};