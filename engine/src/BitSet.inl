#include <fstream>

template<u8 bitCount>
BitSet<bitCount>::BitSet() {
    reset();
}

template<u8 bitCount>
BitSet<bitCount>::~BitSet() {
}

template<u8 bitCount>
void BitSet<bitCount>::reset() {    
    std::memset(mask, 0, sizeof(mask));
}

template<u8 bitCount>
template<class MaskType>
void BitSet<bitCount>::set(MaskType mask) {
    *((MaskType*) (&this->mask)) |= mask;
}

template<u8 bitCount>
template<class MaskType>
void BitSet<bitCount>::set(MaskType mask, bool value) {
    
    MaskType& innerMask = *((MaskType*) (&this->mask));
    innerMask = (MaskType)(innerMask ^ (-(MaskType)value ^ innerMask) & mask);
}

template<u8 bitCount>
template<class MaskType>
MaskType BitSet<bitCount>::get(MaskType mask) {
    return *((MaskType*) (&this->mask)) & mask;
}

