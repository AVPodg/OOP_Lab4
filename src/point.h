#pragma once
#include <type_traits>
#include <cmath>

template<class T>
concept Pointable = std::is_scalar_v<T>;

template<Pointable T>
class Point {
public:
    Point(T x = T(), T y = T()) : _x(x), _y(y) {}

    T getX() const {return _x;}
    T getY() const {return _y;}
    
    // Операции для вычислений
    Point<T> operator+(const Point<T>& other) const {
        return Point<T>(_x + other._x, _y + other._y);
    }
    
    Point<T> operator/(T divisor) const {
        return Point<T>(_x / divisor, _y / divisor);
    }
    
private:
    T _x;
    T _y;
};

template<class P>
class PointContainer {
private:
    struct Node {
        std::unique_ptr<P> point;
        Node* next;
        Node(std::unique_ptr<P> p) : point(std::move(p)), next(nullptr) {}
    };

    Node* head = nullptr;
    size_t _size = 0;

public:
    PointContainer() = default;

    ~PointContainer() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Умные указатели запрещают копирование
    PointContainer(const PointContainer&) = delete;
    PointContainer& operator=(const PointContainer&) = delete;

    // Разрешаем перемещение
    PointContainer(PointContainer&& other) noexcept
        : head(other.head), _size(other._size)
    {
        other.head = nullptr;
        other._size = 0;
    }

    // Перемещающий оператор присваивания
    PointContainer& operator=(PointContainer&& other) noexcept {
        if (this != &other) {
            while (head) { Node* t = head; head = head->next; delete t; }
            head = other.head;
            _size = other._size;
            other.head = nullptr;
            other._size = 0;
        }
        return *this;
    }

    void push_back(std::unique_ptr<P> point) {
        Node* newNode = new Node(std::move(point));
        if (!head) head = newNode;
        else {
            Node* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = newNode;
        }
        ++_size;
    }

    size_t size() const { return _size; }

    P& operator[](size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        Node* cur = head;
        for (size_t i = 0; i < index; ++i) cur = cur->next;
        return *(cur->point);
    }

    const P& operator[](size_t index) const {
        if (index >= _size) throw std::out_of_range("Index out of range");
        Node* cur = head;
        for (size_t i = 0; i < index; ++i) cur = cur->next;
        return *(cur->point);
    }
};