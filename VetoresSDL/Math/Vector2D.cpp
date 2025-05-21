//
//  Vector2D.cpp
//  VetoresSDL
//
//  Created by Thiago Liporace on 19/05/25.
//

#include "Vector2D.hpp"
#include <cmath>
#include <algorithm>

Vector2D::Vector2D(float x,float y): x(x), y(y) {}

Vector2D Vector2D::negateOperator(){
    return Vector2D(-x,-y);
}

const float Vector2D::getMagnitude() {
    return std::sqrt(x * x + y * y);
}

float Vector2D::dotProduct(const Vector2D &obj){
    return (x * obj.x) + (y * obj.y);
}

float Vector2D::angleBetween(Vector2D &obj){
    float mag1 = this->getMagnitude();
    float mag2 = obj.getMagnitude();
    if (mag1 == 0 || mag2 == 0) return 0;
    
    float dotProduct = this->dotProduct(obj);
    float theta = acos(dotProduct/(mag1 * mag2));
    return theta;
}

Vector2D Vector2D::normalized(){
    if (this->getMagnitude() > 0)
        return Vector2D(x,y)/(this->getMagnitude());
    return Vector2D(0,0);
}

Vector2D Vector2D::operator*(float scalar){
    return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(float scalar){
    return Vector2D(x / scalar,y / scalar);
}

Vector2D Vector2D::operator+(const Vector2D &obj){
    return Vector2D(x + obj.x,y + obj.y);
}

Vector2D Vector2D::operator-(const Vector2D &obj){
    return Vector2D(x - obj.x,y - obj.y);
}
