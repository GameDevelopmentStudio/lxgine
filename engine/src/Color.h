#ifndef __COLOR_H__
#define __COLOR_H__

#include "TypeDefinitions.h"

template<class ValueType, u8 redBitCount, u8 greenBitCount, u8 blueBitCount, u8 alphaBitCount>
class Color {
public:
    Color(const float fR, const float fG, const float fB, const float fA = 1.f);
    Color(const ValueType uR, const ValueType uG, const ValueType uB, const ValueType a = ((1 << alphaBitCount) - 1));
    ~Color();
    
    __inline float getRf() const;
    __inline float getGf() const;
    __inline float getBf() const;
    __inline float getAf() const;
    
    __inline ValueType getRu() const;
    __inline ValueType getGu() const;
    __inline ValueType getBu() const;
    __inline ValueType getAu() const;
    
    __inline void set(const float fR, const float fG, const float fB, const float fA = 1.f);
    __inline void set(const ValueType uR, const ValueType uG, const ValueType uB, const ValueType uA = ((1 << alphaBitCount) - 1));
    
protected:
    ValueType color;
};


/*******************
 * Implementation
 ******************/

#include "Color.inl"

typedef Color<u32, 8, 8, 8, 8> Col32;
typedef Color<u16, 5, 5, 5, 1> Col16;
typedef Color<u8, 2, 3, 2, 1> Col8;

typedef Col32 Col;

#endif