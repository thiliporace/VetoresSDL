//
//  Vector2D.hpp
//  VetoresSDL
//
//  Created by Thiago Liporace on 19/05/25.
//

#ifndef Vector2D_hpp
#define Vector2D_hpp

#include <stdio.h>

//Poderia usar uma struct aqui, a diferença é que os membros da struct são públicos por padrão
class Vector2D{
public:
    float x, y;
    
    Vector2D(float x = 0.0,float y = 0.0);
    
    const float getMagnitude();
    
    float dotProduct(const Vector2D &obj);
    float angleBetween(Vector2D& obj);
    
    Vector2D negateOperator();
    Vector2D normalized();
    
    Vector2D operator+(Vector2D const& obj);
    Vector2D operator-(Vector2D const& obj);
    Vector2D operator*(float scalar);
    Vector2D operator/(float scalar);
};

#endif /* Vector2D_hpp */
