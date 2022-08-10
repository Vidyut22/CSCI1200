#pragma once
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <set>
#include "utilities.h"
using namespace std;
class Polygon
{
public:
	Polygon(string name, vector<Point> points)
	{
		this->name = name;
		this->points = points;
		if (points.size() < 3)
		{
			throw 1;
		}
	}
	virtual ~Polygon() {};

	string getName()
	{
		return name;
	}

	bool HasAllEqualSides()
	{
		assert(points.size() > 1);
		int dist = DistanceBetween(points[0], points[1]);
		for (int i = 1; i < points.size() - 1; i++)
		{
			if (DistanceBetween(points[i], points[i + 1]) != dist)
			{
				return false;
			}
		}
		if (DistanceBetween(points[points.size() - 1], points[0]) != dist)
		{
			return false;
		}
		return true;
	}
private:
	string name;
	vector<Point> points;
};

class Triangle : public Polygon
{
public:
	Triangle(string name, vector<Point> points) :Polygon(name,points)
	{
		this->name = name;
		if (points.size() != 3)
		{
			throw  1;
		}
	}
	string getName()
	{
		return name;
	}
private:
	string name;
};

class IsoscelesTriangle: public Triangle
{
public:
	IsoscelesTriangle(string name, vector<Point> points) :Triangle(name, points)
	{
		this->name = name;
		set<double>angles;
		angles.insert(Angle(points[1], points[0], points[2]));
		angles.insert(Angle(points[0], points[1], points[2]));
		angles.insert(Angle(points[0], points[2], points[1]));
		double tmp = *angles.begin();
		int count = 0;
		for (set<double>::iterator itr = angles.begin(); itr != angles.end(); itr++)
		{
			if (*itr == tmp)
			{
				count++;
			}
			else
			{
				count = 1;
			}
			if (count == 2)
			{
				break;
			}
			tmp = *itr;
		}
		if (count != 2)
		{
			throw 1;
		}

	}
	string getName()
	{
		return name;
	}
private:
	string name;
};

class EquilateralTriangle: public IsoscelesTriangle
{
public:
	EquilateralTriangle(string name, vector<Point> points) :IsoscelesTriangle(name, points)
	{
		this->name = name;
		set<double>angles;
		angles.insert(Angle(points[1], points[0], points[2]));
		angles.insert(Angle(points[0], points[1], points[2]));
		angles.insert(Angle(points[0], points[2], points[1]));
		double tmp = *angles.begin();
		for (set<double>::iterator itr = angles.begin(); itr != angles.end(); itr++)
		{
			if (*itr != tmp)
			{
				throw 1;
			}
		}
	}
	string getName()
	{
		return name;
	}
private:
	string name;
};

class Quadrilateral: public Polygon
{
public:
	Quadrilateral(string name, vector<Point> points) :Polygon(name, points)
	{
		this->name = name;
		if (points.size() != 4)
		{
			throw  1;
		}
	}
	string getName()
	{
		return name;
	}
private:
	string name;
};

class Rectangle :public Quadrilateral
{
public:
	Rectangle(string name, vector<Point> points) :Quadrilateral(name, points)
	{
		this->name = name;
		vector<double>angles;
		double angle;
		angle = Angle(points[3], points[0], points[1]);
		if (angle != 90.0) throw 1;
		angle = Angle(points[0], points[1], points[2]);
		if (angle != 90.0) throw 1;
		angle = Angle(points[1], points[2], points[3]);
		if (angle != 90.0) throw 1;
		angle = Angle(points[2], points[3], points[0]);
		if (angle != 90.0) throw 1;
	}
	string getName()
	{
		return name;
	}
private:
	string name;
};

class Square :public Rectangle
{
public: 
	Square(string name, vector<Point> points) :Rectangle(name, points)
	{
		this->name = name;
		double dist = DistanceBetween(points[0], points[1]);
		if(DistanceBetween(points[0], points[3])!=dist) throw 1;
		if(DistanceBetween(points[3], points[2]) != dist) throw 1;
		if (DistanceBetween(points[2], points[1]) != dist) throw 1;
	}
	string getName()
	{
		return name;
	}
private:
	string name;
};