#ifndef __BITSET_H__
#define __BITSET_H__

#include "TypeDefinitions.h"

template<u8 bitCount>
class BitSet {
public:
    
    BitSet();
    ~BitSet();
    
    void reset();
    
    template<class MaskType>
    void set(MaskType mask);

    template<class MaskType>
    void set(MaskType mask, bool value);
    
    template<class MaskType>
    MaskType get(MaskType mask);

protected:
    
    u8 mask[bitCount / 8];
    
};

/*******************
 * Implementation
 ******************/

#include "BitSet.inl"

typedef BitSet<32> BitSet32;
typedef BitSet<16> BitSet16;
typedef BitSet<8> BitSet8;

#endif
