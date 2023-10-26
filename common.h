#define FROM_BCD16(a)  (((a) >> 8) * 10 + ((a) & 0xff))
#define FROM_ASCII(a)  (((((a) >> 8) - 0x30) * 10) | (((a) & 0xff) - 0x30))

#define UINT32_0B(a)  ((a) & 0xff)
#define UINT32_1B(a)  (((a) >> 8) & 0xff)
#define UINT32_2B(a)  (((a) >> 16) & 0xff)
#define UINT32_3B(a)  (((a) >> 24) & 0xff)

#define UINT16_BE_TO_LE(a)  ((((a) & 0xff) << 8) | (((a) >> 8) & 0xff))
#define UINT32_BE_TO_LE(a)   \
		((((a) & 0xff) << 24) |  \
		(((a) & 0xff00) << 8) |	 \
		(((a) >> 8) & 0xff00) |  \
		(((a) >> 24) & 0xff))

#define UINT16_FROM_LE_BYTES(a0, a1)          (((a1) << 8) | (a0))
#define UINT16_FROM_BE_BYTES(a1, a0)          (((a1) << 8) | (a0))
#define UINT32_FROM_LE_BYTES(a0, a1, a2, a3)  (((a3) << 24) | ((a2) << 16) | ((a1) << 8) | (a0))
#define UINT32_FROM_BE_BYTES(a3, a2, a1, a0)  (((a3) << 24) | ((a2) << 16) | ((a1) << 8) | (a0))

#define GET_BIT(byte, bit_nr)  ((byte) >> (bit_nr) & 0x01U)
#define SET_BIT(byte, bit_nr)  ((byte) | (1U << (bit_nr)))
#define CLR_BIT(byte, bit_nr)  ((byte) & ~(1U << (bit_nr)))

#define SWAP_NIBBLE(a) ((((a) >> 4) & 0x0f) | (((a) << 4) & 0xf0))

#define ROUND_TO_2(a) (((a) / 2) * 2)

#define max(a,b)           \
({                         \
	__typeof__ (a) _a = (a); \
	__typeof__ (b) _b = (b); \
	_a > _b ? _a : _b;       \
})

#define min(a,b)           \
({                         \
	__typeof__ (a) _a = (a); \
	__typeof__ (b) _b = (b); \
	_a < _b ? _a : _b;       \
})

#define xchange(a, b, tmp) \
({                         \
	tmp = a;                 \
	a = b;                   \
	b = tmp;                 \
})

extern void debug_string(char *s, int max_string);
