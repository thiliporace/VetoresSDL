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
    
    Vector2D auxVector = this->rotatedVector(90 * (M_PI/180));
    
    return auxVector.dotProduct(obj) > 0 ? theta : -theta;
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

//Operações de transformação de coordenada:

Vector2D Vector2D::rotatedVector(float angleRad){
    //Multiplicando pela matriz de transformação em 2D
    return Vector2D(
        x * std::cos(angleRad) - y * std::sin(angleRad),
        x * std::sin(angleRad) + y * std::cos(angleRad)
    );
}

Vector2D Vector2D::transformObjectToUpright(Vector2D &obj){
    return rotatedVector(this->angleBetween(obj));
}

Vector2D Vector2D::transformUprightToWorld(Vector2D& obj){
    return Vector2D(x + obj.x,y + obj.y);
}

Vector2D Vector2D::transformObjectToWorld(Vector2D &obj){
    Vector2D vec1 = transformObjectToUpright(obj);
    Vector2D vec2 = transformUprightToWorld(vec1);
    return vec2;
}

Vector2D Vector2D::transformWorldToUpright(Vector2D &obj){
    return Vector2D(x - obj.x, y - obj.x);
}

Vector2D Vector2D::transformUprightToObject(Vector2D &obj){
    return rotatedVector(this->angleBetween(obj));
}

Vector2D Vector2D::transformWorldToObject(Vector2D &obj){
    Vector2D vec1 = transformWorldToUpright(obj);
    Vector2D vec2 = transformUprightToObject(vec1);
    return vec2;
}
