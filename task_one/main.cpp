#include <iostream>
#include <string>
#include <cmath>
#include <vector>

void Check_param (std::string shape_name, std::string value_name, double value)
{
	if (value <= 0) {
		std::cout << shape_name <<"():Invaild value of "<< value_name
		          <<" = " << value <<". "<< shape_name <<' '<< value_name
		          <<" set a default value = 1" << std::endl;
	}
}

struct IShape
{
	virtual double Area() = 0;
	virtual std::string getName() = 0;
	virtual ~IShape(){};
};

struct Square : IShape
{
private:
	std::string m_name = "Square";
	double m_side_length;
public:
	Square(double side_length = 1.0) : m_side_length(side_length > 0 ? side_length : 1)
	{
		Check_param(m_name, "side_length", side_length);
	};
	double Area() override
	{
		return m_side_length * m_side_length;
	}
	std::string getName () override
	{
		return m_name;
	}
};

struct Rectangle : IShape
{
private:
	std::string m_name = "Rectangle";
	double m_length;
	double m_wide;
public:
	Rectangle(double length = 1.0, double wide = 1.0) : m_length(length > 0 ? length : 1),
	                                                    m_wide(wide > 0 ? wide : 1)
	{
		Check_param(m_name, "length", length);
		Check_param(m_name, "wide", wide);
	}
	double Area() override
	{
		return m_length * m_wide;
	}
	std::string getName() override
	{
		return m_name;
	}
};

struct Triangle : IShape
{
private:
	std::string m_name = "Triangle";
	double m_base;
	double m_height;
public:
	Triangle(double base = 1, double height = 1) : m_base(base > 0 ? base : 1),
	                                               m_height(height > 0 ? height : 1)
	{
		Check_param(m_name, "base", base);
		Check_param(m_name, "height", height);
	}
	double Area() override
	{
		return 0.5 * m_height * m_base;
	}
	std::string getName() override
	{
		return m_name;
	}
};

struct Circle : IShape
{
private:
	std::string m_name = "Circle";
	double m_radius;
public:
	Circle(double radius = 1) : m_radius(radius > 0 ? radius : 1)
	{
		Check_param(m_name, "radius", radius);
	}
	double Area() override
	{
		return m_radius * m_radius * M_PI;
	}
	std::string getName() override
	{
		return m_name;
	}
};

int main()
{

	std::vector<IShape *> vec_shapes;
	/*Square demo*/
	Square square(2.0);
	vec_shapes.push_back(&square);
	std::cout << "square.Area() = " << square.Area() << std::endl;
	/*Rectangel Demo*/
	Rectangle rectangle(3.0, 4.0);
	vec_shapes.push_back(&rectangle);
	std::cout << "rectangle.Area() = " << rectangle.Area() << std::endl;
	/*Triangle Demo*/
	Triangle triangle(5.0, 6.0);
	vec_shapes.push_back(&triangle);
	std::cout << "triangle.Area() = " << triangle.Area() << std::endl;
	/*Circle Demo*/
	Circle circle(7.0);
	vec_shapes.push_back(&circle);
	std::cout << "circle.Area() = " << circle.Area() << std::endl;
	/*IShape Demo*/
	for (auto shape : vec_shapes) {
		std::cout << "shape->getName() = " << shape->getName() <<' '
		          << "shape->Area() = " << shape->Area() << std::endl;
	}
	return 0;
}
