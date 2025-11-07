#pragma once
#include <iostream>
#include "point.h"

template<class T>
class Figure {
public:
    using P = Point<T>;

    Figure() = default;
    virtual ~Figure() noexcept = default;

    Figure(const Figure<T>& other) {
        for (size_t i = 0; i < other.get_points_count(); ++i) {
            points.push_back(std::make_unique<P>(other.get_point(i)));
        }
    }

    Figure<T>& operator=(const Figure<T>& other) {
        if (this == &other) return *this;
        PointContainer<Point<T>> tmp;
        for (size_t i = 0; i < other.get_points_count(); ++i) {
            tmp.push_back(std::make_unique<P>(other.get_point(i)));
        }
        this->points = std::move(tmp);
        return *this;
    }

    Figure(Figure<T>&& other) noexcept = default;

    void add_point(const P& point) {
        points.push_back(std::make_unique<P>(point));
    }

    size_t get_points_count() const {
        return points.size();
    }

    const P& get_point(size_t index) const {
        return points[index];
    }

    virtual P center() const = 0;
    virtual operator double() = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& figure) {
        os << "Figure with " << figure.points.size() << " points:\n";
        for (size_t i = 0; i < figure.points.size(); ++i) {
            const P& p = figure.points[i];
            os << "Point " << i << ": (" << p.getX() << ", " << p.getY() << ")\n";
        }
        return os;
}

protected:
    PointContainer<P> points;
};