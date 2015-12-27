#include "Color.h"
#include <math.h>

template<class ValueType, u8 redBitCount, u8 greenBitCount, u8 blueBitCount, u8 alphaBitCount>
Color<ValueType, redBitCount, greenBitCount, blueBitCount, alphaBitCount>::Color(const float fR, const float fG, const float fB, const float fA) {
    set(fR, fG, fB, fA);
}

template<class ValueType, u8 redBitCount, u8 greenBitCount, u8 blueBitCount, u8 alphaBitCount>
Color<ValueType, redBitCount, greenBitCount, blueBitCount, alphaBitCount>::Color(const ValueType uR, const ValueType uG, const ValueType uB, const ValueType uA) {
    set(uR, uG, uB, uA);
}

template<class ValueType, u8 redBitCount, u8 greenBitCount, u8 blueBitCount, u8 alphaBitCount>
Color<ValueType, redBitCount, greenBitCount, blueBitCount, alphaBitCount>::~Color() {
}

template<class ValueType, u8 redBitCount, u8 greenBitCount, u8 blueBitCount, u8 alphaBitCount>
float Color<ValueType, redBitCount, greenBitCount, blueBitCount, alphaBitCount>::getRf() const {
    const ValueType uR = getRu();
    return (float) uR/ ((1 << redBitCount) - 1);
}

template<class ValueType, u8 redBitCount, u8 greenBitCount, u8 blueBitCount, u8 alphaBitCount>
float Color<ValueType, redBitCount, greenBitCount, blueBitCount, alphaBitCount>::getGf() const {
    const ValueType uG = getGu();
    return (float) uG / ((1 << greenBitCount) - 1);
}

template<class ValueType, u8 redBitCount, u8 greenBitCount, u8 blueBitCount, u8 alphaBitCount>
float Color<ValueType, redBitCount, greenBitCount, blueBitCount, alphaBitCount>::getBf() const {
    const ValueType uB = getBu();
    return (float) uB / ((1 << blueBitCount) - 1);
}

template<class ValueType, u8 redBitCount, u8 greenBitCount, u8 blueBitCount, u8 alphaBitCount>
float Color<ValueType, redBitCount, greenBitCount, blueBitCount, alphaBitCount>::getAf() const {
    const ValueType uA = getAu();
    return (float) uA / ((1 << alphaBitCount) - 1);
}

template<class ValueType, u8 redBitCount, u8 greenBitCount, u8 blueBitCount, u8 alphaBitCount>
ValueType Color<ValueType, redBitCount, greenBitCount, blueBitCount, alphaBitCount>::getRu() const {
    const ValueType uRedMask = (1 << redBitCount) - 1;
    return (color >> (greenBitCount + blueBitCount + alphaBitCount)) & uRedMask;
}

template<class ValueType, u8 redBitCount, u8 greenBitCount, u8 blueBitCount, u8 alphaBitCount>
ValueType Color<ValueType, redBitCount, greenBitCount, blueBitCount, alphaBitCount>::getGu() const {
    const ValueType uGreenMask = (1 << greenBitCount) - 1;
    return (color >> (blueBitCount + alphaBitCount)) & uGreenMask;
}

template<class ValueType, u8 redBitCount, u8 greenBitCount, u8 blueBitCount, u8 alphaBitCount>
ValueType Color<ValueType, redBitCount, greenBitCount, blueBitCount, alphaBitCount>::getBu() const {
    const ValueType uBlueMask = (1 << blueBitCount) - 1;
    return (color >> (alphaBitCount)) & uBlueMask;
}

template<class ValueType, u8 redBitCount, u8 greenBitCount, u8 blueBitCount, u8 alphaBitCount>
ValueType Color<ValueType, redBitCount, greenBitCount, blueBitCount, alphaBitCount>::getAu() const {
    const ValueType uAlphaMask = (1 << alphaBitCount) - 1;
    return color & uAlphaMask;
}

template<class ValueType, u8 redBitCount, u8 greenBitCount, u8 blueBitCount, u8 alphaBitCount>
void Color<ValueType, redBitCount, greenBitCount, blueBitCount, alphaBitCount>::set(const float fR, const float fG, const float fB, const float fA) {
    
    const ValueType uR = (ValueType)roundf(fR * ((1 << redBitCount) - 1));
    const ValueType uG = (ValueType)roundf(fG * ((1 << greenBitCount) - 1));
    const ValueType uB = (ValueType)roundf(fB * ((1 << blueBitCount) - 1));
    const ValueType uA = (ValueType)roundf(fA * ((1 << alphaBitCount) - 1));
    set(uR, uG, uB, uA);
}

template<class ValueType, u8 redBitCount, u8 greenBitCount, u8 blueBitCount, u8 alphaBitCount>
void Color<ValueType, redBitCount, greenBitCount, blueBitCount, alphaBitCount>::set(const ValueType uR, const ValueType uG, const ValueType uB, const ValueType uA) {
    color = (uR << (greenBitCount + blueBitCount + alphaBitCount)) + (uG << (blueBitCount + alphaBitCount)) + (uB << (alphaBitCount)) + uA;
}