#include <kamek.hpp>
typedef struct lex_header_t
{
    char	magic[4];	// always LEX_BIN_MAGIC
    u16		major_version;	// usually LEX_MAJOR_VERSION
    u16		minor_version;	// usually LEX_MINOR_VERSION
    u32		size;		// size of this file (header+streams)
    u32		element_off;	// offset of first lex_element_t, 32-bit aligned
}
__attribute__ ((packed)) lex_header_t;
