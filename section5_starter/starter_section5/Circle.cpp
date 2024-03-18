#include "Circle.h"
using namespace std;
#include "SimpleTest.h"
#include "gmath.h"
#include "strlib.h"

/**
 * TODO: write a method comment
 */
Circle::Circle(double r) {
    _radius = r;
}


/**
 * TODO: write a method comment
 */
double Circle::area() const {
    return PI * _radius * _radius;
}

/**
 * TODO: write a method comment
 */
double Circle::circumference() const{
    return 2 * PI * _radius;
}

/**
 * TODO: write a method comment
 */
double Circle::getRadius() const{
    return _radius;
}

/**
 * TODO: write a method comment
 */
string Circle::toString() const{
    return string("Circle{radius=") + realToString(_radius) + string("}");
}

/* Provided Tests Below This Line */

PROVIDED_TEST("Simple Example") {
    Circle c(2.5);
    EXPECT_EQUAL(c.getRadius(), 2.5);
    EXPECT_EQUAL(c.circumference(), 2 * PI * 2.5);
    EXPECT_EQUAL(c.area(), PI * 2.5 * 2.5);
    EXPECT_EQUAL(c.toString(), "Circle{radius=2.5}");
}
