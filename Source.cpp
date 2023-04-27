#include <iostream>
#include <vector>
#include <cmath>
#define PI 3.1415926535
using namespace std;


class Square;
class Circle;
class Rectangle;

class Visitor 
{
public:

    virtual void Visit(Square& square)       = 0;
    virtual void Visit(Circle& circle)       = 0;
    virtual void Visit(Rectangle& rectangle) = 0;
};

class Shape 
{
public:

    virtual void Accept(Visitor& visitor) = 0;
};

class Square : public Shape 
{
public:

    Square(double Side) : side(Side) {}

    double Area() const { return side * side; }

    void Accept(Visitor& visitor) override { visitor.Visit(*this); }

    double GetSide() { return side; }

private:
    double side;
};

class Circle : public Shape 
{
public:

    Circle(double Rad) : rad(Rad) {}

    double Area() const { return PI * rad * rad; }

    void Accept(Visitor& visitor) override { visitor.Visit(*this); }

    double GetRadius() { return rad; }

private:

    double rad;
};

class Rectangle : public Shape 
{
public:

    Rectangle(double Width, double Height) : width(Width), height(Height) {}

    double area() const { return width * height; }

    void Accept(Visitor& visitor) override { visitor.Visit(*this); }

    double GetWidth() { return width; }

    double getHeight() { return height; }

private:

    double width;
    double height;
};

class PerimeterVisitor : public Visitor
{
public:

    void Visit(Square& square) override { perimeter += 4 * square.GetSide(); }

    void Visit(Circle& circle) override { perimeter += 2 * PI * circle.GetRadius(); }

    void Visit(Rectangle& rectangle) override { perimeter += 2 * (rectangle.GetWidth() + rectangle.getHeight()); }

    double Perimeter() const { return perimeter; }

private:

    double perimeter = 0;
};
class DrawVisitor : public Visitor
{
public:

    void Visit(Square& square) override
    {
        textToPrint = "Drawing Square\n";
        height = round(square.GetSide());
        width  = round(square.GetSide());
    }

    void Visit(Circle& circle) override
    {
        textToPrint = "Drawing Circle\n";
        height = 0;
        width  = 0;
    }

    void Visit(Rectangle& rectangle) override
    {
        textToPrint = "Drawing Rectangle\n";
        height      = round(rectangle.getHeight());
        width       = round(rectangle.GetWidth());
    }

    void Show() const
    {
        cout << textToPrint;

        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
                cout << " * ";
            cout << "\n";
        }
        cout << endl;
    }

private:

    int height = 0;
    int width = 0;
    string textToPrint;
};

int main()
{
    std::vector<Shape*> shapes 
    { 
        new Square(3.4),
        new Circle(2), 
        new Rectangle(8, 5) 
    };

    PerimeterVisitor perimeterVisitor;
    for (auto shape : shapes)
        shape->Accept(perimeterVisitor);

    cout << "Total perimeter: " << perimeterVisitor.Perimeter() << "\n\n";

    DrawVisitor drawVisitor;

    for (auto shape : shapes)
    {
        shape->Accept(drawVisitor);
        drawVisitor.Show();
    }

    for (auto shape : shapes)
        delete shape;
}