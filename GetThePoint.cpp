#include <iostream>
#include <cmath> // Needed for sqrt() and pow()

using namespace std; // Beginners almost always use this globally

class Point
{
private:
    double x;
    double y;

public:
    // Default constructor
    Point()
    {
        this->x = 0.0;
        this->y = 0.0;
    }

    // Constructor with parameters
    Point(double xVal, double yVal)
    {
        this->x = xVal;
        this->y = yVal;
    }

    // Overload - operator to find distance
    double operator-(Point other)
    {
        // d = sqrt((x2 - x1)^2 + (y2 - y1)^2)
        double xDiff = other.x - this->x;
        double yDiff = other.y - this->y;
        
        double xSquared = pow(xDiff, 2);
        double ySquared = pow(yDiff, 2);
        
        double distance = sqrt(xSquared + ySquared);
        return distance;
    }

    // Overload == operator for equality
    bool operator==(Point other)
    {
        if (this->x == other.x && this->y == other.y)
        {
            return true;
        }
        else
        {
            return false; // Beginners love explicit if-else for booleans
        }
    }

    // Overload != operator for inequality
    bool operator!=(Point other)
    {
        if (this->x != other.x || this->y != other.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // Overload / operator to find midpoint
    Point operator/(Point other)
    {
        // p = ((x1 + x2)/2, (y1 + y2)/2)
        double midX = (this->x + other.x) / 2.0;
        double midY = (this->y + other.y) / 2.0;
        
        Point midpoint(midX, midY);
        return midpoint;
    }

    // 1) Prefix ++ increments x coordinate (++point)
    Point& operator++()
    {
        this->x = this->x + 1; // Or this->x++
        return *this;
    }

    // 1) Postfix ++ increments y coordinate (point++)
    Point operator++(int dummy)
    {
        Point temp = *this; // Save original state
        this->y = this->y + 1;
        return temp; // Return original state
    }

    // 2) Prefix -- decrements x coordinate (--point)
    Point& operator--()
    {
        this->x = this->x - 1;
        return *this;
    }

    // 2) Postfix -- decrements y coordinate (point--)
    Point operator--(int dummy)
    {
        Point temp = *this;
        this->y = this->y - 1;
        return temp;
    }

    // 3) Overload [] to access x (index 0) and y (index 1)
    double& operator[](int index)
    {
        if (index == 0)
        {
            return this->x;
        }
        else
        {
            return this->y; // Assuming index 1, or any other number defaults to y
        }
    }

    // Making stream operators friend functions so they can access private data
    friend ostream& operator<<(ostream& output, Point p);
    friend istream& operator>>(istream& input, Point& p);
};

// Overload << operator for output streaming
ostream& operator<<(ostream& output, Point p)
{
    // Formats it neatly as (x, y)
    output << "(" << p.x << ", " << p.y << ")";
    return output;
}

// 4) Overload >> operator to read input in the form (x, y)
istream& operator>>(istream& input, Point& p)
{
    char garbage; // Variable to eat up characters like '(', ',', and ')'
    double tempX;
    double tempY;

    // Expecting user to type something like (5, 10)
    input >> garbage; // Eats '('
    input >> tempX;   // Reads the x coordinate
    input >> garbage; // Eats ','
    input >> tempY;   // Reads the y coordinate
    input >> garbage; // Eats ')'

    p.x = tempX;
    p.y = tempY;

    return input;
}

// Quick main function to test everything out
int main()
{
    Point p1(1.0, 2.0);
    Point p2(4.0, 6.0);

    cout << "Point 1: " << p1 << endl;
    cout << "Point 2: " << p2 << endl;

    // Test Distance (-)
    double dist = p1 - p2;
    cout << "Distance: " << dist << endl;

    // Test Midpoint (/)
    Point mid = p1 / p2;
    cout << "Midpoint: " << mid << endl;

    // Test equality tests
    if (p1 == p2)
    {
        cout << "Points are equal" << endl;
    }
    if (p1 != p2)
    {
        cout << "Points are not equal" << endl;
    }

    // Test increment/decrement
    ++p1; // should change x from 1 to 2
    p1++; // should change y from 2 to 3
    cout << "p1 after increments: " << p1 << endl;

    // Test array subscript operator
    cout << "p1 x coordinate via [0]: " << p1[0] << endl;
    p1[1] = 10.5; // Change y via reference
    cout << "p1 after changing y via [1]: " << p1 << endl;

    // Test input streaming
    Point p3;
    cout << "Enter a point in the format (x, y): ";
    cin >> p3;
    cout << "You entered: " << p3 << endl;

    return 0;
}

