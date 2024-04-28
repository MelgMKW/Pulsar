#include <kamek.hpp>

typedef struct lex_element_t
{
    u32		magic;		// identification of section
    u32		size;		// size of 'data' (this header excluded)
    u8		data[];		// section data, 32-bit aligned
}
__attribute__ ((packed)) lex_element_t;

