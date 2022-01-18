/*
 * Copyright (C) 2013-2021 Canonical, Ltd.
 * Copyright (C) 2021-2022 Colin Ian King
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */
#include "stress-ng.h"

static const stress_help_t help[] = {
	{ NULL,	"branch N",	"start N workers that force branch misprediction" },
	{ NULL,	"branch-ops N",	"stop after N branch misprediction branches" },
	{ NULL,	NULL,		NULL }
};

#if defined(HAVE_LABEL_AS_VALUE) &&		\
    !defined(__PCC__)

#define RESEED_JMP				\
		seed = (a * seed + c);		\
		idx = (seed >> 22);		\
		goto *labels[idx];

#define J(n) L ## n:	RESEED_JMP

/*
 *  stress_branch()
 *	stress instruction branch prediction
 */
static int OPTIMIZE3 stress_branch(const stress_args_t *args)
{
	register uint32_t const a = 16843009;
	register uint32_t const c = 826366247;
	register uint32_t seed = 123456789;
	register uint32_t idx;

	static const void ALIGN64 *labels[] = {
		&&L0x000, &&L0x001, &&L0x002, &&L0x003, &&L0x004, &&L0x005, &&L0x006, &&L0x007,
		&&L0x008, &&L0x009, &&L0x00a, &&L0x00b, &&L0x00c, &&L0x00d, &&L0x00e, &&L0x00f,
		&&L0x010, &&L0x011, &&L0x012, &&L0x013, &&L0x014, &&L0x015, &&L0x016, &&L0x017,
		&&L0x018, &&L0x019, &&L0x01a, &&L0x01b, &&L0x01c, &&L0x01d, &&L0x01e, &&L0x01f,
		&&L0x020, &&L0x021, &&L0x022, &&L0x023, &&L0x024, &&L0x025, &&L0x026, &&L0x027,
		&&L0x028, &&L0x029, &&L0x02a, &&L0x02b, &&L0x02c, &&L0x02d, &&L0x02e, &&L0x02f,
		&&L0x030, &&L0x031, &&L0x032, &&L0x033, &&L0x034, &&L0x035, &&L0x036, &&L0x037,
		&&L0x038, &&L0x039, &&L0x03a, &&L0x03b, &&L0x03c, &&L0x03d, &&L0x03e, &&L0x03f,

		&&L0x040, &&L0x041, &&L0x042, &&L0x043, &&L0x044, &&L0x045, &&L0x046, &&L0x047,
		&&L0x048, &&L0x049, &&L0x04a, &&L0x04b, &&L0x04c, &&L0x04d, &&L0x04e, &&L0x04f,
		&&L0x050, &&L0x051, &&L0x052, &&L0x053, &&L0x054, &&L0x055, &&L0x056, &&L0x057,
		&&L0x058, &&L0x059, &&L0x05a, &&L0x05b, &&L0x05c, &&L0x05d, &&L0x05e, &&L0x05f,
		&&L0x060, &&L0x061, &&L0x062, &&L0x063, &&L0x064, &&L0x065, &&L0x066, &&L0x067,
		&&L0x068, &&L0x069, &&L0x06a, &&L0x06b, &&L0x06c, &&L0x06d, &&L0x06e, &&L0x06f,
		&&L0x070, &&L0x071, &&L0x072, &&L0x073, &&L0x074, &&L0x075, &&L0x076, &&L0x077,
		&&L0x078, &&L0x079, &&L0x07a, &&L0x07b, &&L0x07c, &&L0x07d, &&L0x07e, &&L0x07f,

		&&L0x080, &&L0x081, &&L0x082, &&L0x083, &&L0x084, &&L0x085, &&L0x086, &&L0x087,
		&&L0x088, &&L0x089, &&L0x08a, &&L0x08b, &&L0x08c, &&L0x08d, &&L0x08e, &&L0x08f,
		&&L0x090, &&L0x091, &&L0x092, &&L0x093, &&L0x094, &&L0x095, &&L0x096, &&L0x097,
		&&L0x098, &&L0x099, &&L0x09a, &&L0x09b, &&L0x09c, &&L0x09d, &&L0x09e, &&L0x09f,
		&&L0x0a0, &&L0x0a1, &&L0x0a2, &&L0x0a3, &&L0x0a4, &&L0x0a5, &&L0x0a6, &&L0x0a7,
		&&L0x0a8, &&L0x0a9, &&L0x0aa, &&L0x0ab, &&L0x0ac, &&L0x0ad, &&L0x0ae, &&L0x0af,
		&&L0x0b0, &&L0x0b1, &&L0x0b2, &&L0x0b3, &&L0x0b4, &&L0x0b5, &&L0x0b6, &&L0x0b7,
		&&L0x0b8, &&L0x0b9, &&L0x0ba, &&L0x0bb, &&L0x0bc, &&L0x0bd, &&L0x0be, &&L0x0bf,

		&&L0x0c0, &&L0x0c1, &&L0x0c2, &&L0x0c3, &&L0x0c4, &&L0x0c5, &&L0x0c6, &&L0x0c7,
		&&L0x0c8, &&L0x0c9, &&L0x0ca, &&L0x0cb, &&L0x0cc, &&L0x0cd, &&L0x0ce, &&L0x0cf,
		&&L0x0d0, &&L0x0d1, &&L0x0d2, &&L0x0d3, &&L0x0d4, &&L0x0d5, &&L0x0d6, &&L0x0d7,
		&&L0x0d8, &&L0x0d9, &&L0x0da, &&L0x0db, &&L0x0dc, &&L0x0dd, &&L0x0de, &&L0x0df,
		&&L0x0e0, &&L0x0e1, &&L0x0e2, &&L0x0e3, &&L0x0e4, &&L0x0e5, &&L0x0e6, &&L0x0e7,
		&&L0x0e8, &&L0x0e9, &&L0x0ea, &&L0x0eb, &&L0x0ec, &&L0x0ed, &&L0x0ee, &&L0x0ef,
		&&L0x0f0, &&L0x0f1, &&L0x0f2, &&L0x0f3, &&L0x0f4, &&L0x0f5, &&L0x0f6, &&L0x0f7,
		&&L0x0f8, &&L0x0f9, &&L0x0fa, &&L0x0fb, &&L0x0fc, &&L0x0fd, &&L0x0fe, &&L0x0ff,

		&&L0x100, &&L0x101, &&L0x102, &&L0x103, &&L0x104, &&L0x105, &&L0x106, &&L0x107,
		&&L0x108, &&L0x109, &&L0x10a, &&L0x10b, &&L0x10c, &&L0x10d, &&L0x10e, &&L0x10f,
		&&L0x110, &&L0x111, &&L0x112, &&L0x113, &&L0x114, &&L0x115, &&L0x116, &&L0x117,
		&&L0x118, &&L0x119, &&L0x11a, &&L0x11b, &&L0x11c, &&L0x11d, &&L0x11e, &&L0x11f,
		&&L0x120, &&L0x121, &&L0x122, &&L0x123, &&L0x124, &&L0x125, &&L0x126, &&L0x127,
		&&L0x128, &&L0x129, &&L0x12a, &&L0x12b, &&L0x12c, &&L0x12d, &&L0x12e, &&L0x12f,
		&&L0x130, &&L0x131, &&L0x132, &&L0x133, &&L0x134, &&L0x135, &&L0x136, &&L0x137,
		&&L0x138, &&L0x139, &&L0x13a, &&L0x13b, &&L0x13c, &&L0x13d, &&L0x13e, &&L0x13f,

		&&L0x140, &&L0x141, &&L0x142, &&L0x143, &&L0x144, &&L0x145, &&L0x146, &&L0x147,
		&&L0x148, &&L0x149, &&L0x14a, &&L0x14b, &&L0x14c, &&L0x14d, &&L0x14e, &&L0x14f,
		&&L0x150, &&L0x151, &&L0x152, &&L0x153, &&L0x154, &&L0x155, &&L0x156, &&L0x157,
		&&L0x158, &&L0x159, &&L0x15a, &&L0x15b, &&L0x15c, &&L0x15d, &&L0x15e, &&L0x15f,
		&&L0x160, &&L0x161, &&L0x162, &&L0x163, &&L0x164, &&L0x165, &&L0x166, &&L0x167,
		&&L0x168, &&L0x169, &&L0x16a, &&L0x16b, &&L0x16c, &&L0x16d, &&L0x16e, &&L0x16f,
		&&L0x170, &&L0x171, &&L0x172, &&L0x173, &&L0x174, &&L0x175, &&L0x176, &&L0x177,
		&&L0x178, &&L0x179, &&L0x17a, &&L0x17b, &&L0x17c, &&L0x17d, &&L0x17e, &&L0x17f,

		&&L0x180, &&L0x181, &&L0x182, &&L0x183, &&L0x184, &&L0x185, &&L0x186, &&L0x187,
		&&L0x188, &&L0x189, &&L0x18a, &&L0x18b, &&L0x18c, &&L0x18d, &&L0x18e, &&L0x18f,
		&&L0x190, &&L0x191, &&L0x192, &&L0x193, &&L0x194, &&L0x195, &&L0x196, &&L0x197,
		&&L0x198, &&L0x199, &&L0x19a, &&L0x19b, &&L0x19c, &&L0x19d, &&L0x19e, &&L0x19f,
		&&L0x1a0, &&L0x1a1, &&L0x1a2, &&L0x1a3, &&L0x1a4, &&L0x1a5, &&L0x1a6, &&L0x1a7,
		&&L0x1a8, &&L0x1a9, &&L0x1aa, &&L0x1ab, &&L0x1ac, &&L0x1ad, &&L0x1ae, &&L0x1af,
		&&L0x1b0, &&L0x1b1, &&L0x1b2, &&L0x1b3, &&L0x1b4, &&L0x1b5, &&L0x1b6, &&L0x1b7,
		&&L0x1b8, &&L0x1b9, &&L0x1ba, &&L0x1bb, &&L0x1bc, &&L0x1bd, &&L0x1be, &&L0x1bf,

		&&L0x1c0, &&L0x1c1, &&L0x1c2, &&L0x1c3, &&L0x1c4, &&L0x1c5, &&L0x1c6, &&L0x1c7,
		&&L0x1c8, &&L0x1c9, &&L0x1ca, &&L0x1cb, &&L0x1cc, &&L0x1cd, &&L0x1ce, &&L0x1cf,
		&&L0x1d0, &&L0x1d1, &&L0x1d2, &&L0x1d3, &&L0x1d4, &&L0x1d5, &&L0x1d6, &&L0x1d7,
		&&L0x1d8, &&L0x1d9, &&L0x1da, &&L0x1db, &&L0x1dc, &&L0x1dd, &&L0x1de, &&L0x1df,
		&&L0x1e0, &&L0x1e1, &&L0x1e2, &&L0x1e3, &&L0x1e4, &&L0x1e5, &&L0x1e6, &&L0x1e7,
		&&L0x1e8, &&L0x1e9, &&L0x1ea, &&L0x1eb, &&L0x1ec, &&L0x1ed, &&L0x1ee, &&L0x1ef,
		&&L0x1f0, &&L0x1f1, &&L0x1f2, &&L0x1f3, &&L0x1f4, &&L0x1f5, &&L0x1f6, &&L0x1f7,
		&&L0x1f8, &&L0x1f9, &&L0x1fa, &&L0x1fb, &&L0x1fc, &&L0x1fd, &&L0x1fe, &&L0x1ff,

		&&L0x200, &&L0x201, &&L0x202, &&L0x203, &&L0x204, &&L0x205, &&L0x206, &&L0x207,
		&&L0x208, &&L0x209, &&L0x20a, &&L0x20b, &&L0x20c, &&L0x20d, &&L0x20e, &&L0x20f,
		&&L0x210, &&L0x211, &&L0x212, &&L0x213, &&L0x214, &&L0x215, &&L0x216, &&L0x217,
		&&L0x218, &&L0x219, &&L0x21a, &&L0x21b, &&L0x21c, &&L0x21d, &&L0x21e, &&L0x21f,
		&&L0x220, &&L0x221, &&L0x222, &&L0x223, &&L0x224, &&L0x225, &&L0x226, &&L0x227,
		&&L0x228, &&L0x229, &&L0x22a, &&L0x22b, &&L0x22c, &&L0x22d, &&L0x22e, &&L0x22f,
		&&L0x230, &&L0x231, &&L0x232, &&L0x233, &&L0x234, &&L0x235, &&L0x236, &&L0x237,
		&&L0x238, &&L0x239, &&L0x23a, &&L0x23b, &&L0x23c, &&L0x23d, &&L0x23e, &&L0x23f,

		&&L0x240, &&L0x241, &&L0x242, &&L0x243, &&L0x244, &&L0x245, &&L0x246, &&L0x247,
		&&L0x248, &&L0x249, &&L0x24a, &&L0x24b, &&L0x24c, &&L0x24d, &&L0x24e, &&L0x24f,
		&&L0x250, &&L0x251, &&L0x252, &&L0x253, &&L0x254, &&L0x255, &&L0x256, &&L0x257,
		&&L0x258, &&L0x259, &&L0x25a, &&L0x25b, &&L0x25c, &&L0x25d, &&L0x25e, &&L0x25f,
		&&L0x260, &&L0x261, &&L0x262, &&L0x263, &&L0x264, &&L0x265, &&L0x266, &&L0x267,
		&&L0x268, &&L0x269, &&L0x26a, &&L0x26b, &&L0x26c, &&L0x26d, &&L0x26e, &&L0x26f,
		&&L0x270, &&L0x271, &&L0x272, &&L0x273, &&L0x274, &&L0x275, &&L0x276, &&L0x277,
		&&L0x278, &&L0x279, &&L0x27a, &&L0x27b, &&L0x27c, &&L0x27d, &&L0x27e, &&L0x27f,

		&&L0x280, &&L0x281, &&L0x282, &&L0x283, &&L0x284, &&L0x285, &&L0x286, &&L0x287,
		&&L0x288, &&L0x289, &&L0x28a, &&L0x28b, &&L0x28c, &&L0x28d, &&L0x28e, &&L0x28f,
		&&L0x290, &&L0x291, &&L0x292, &&L0x293, &&L0x294, &&L0x295, &&L0x296, &&L0x297,
		&&L0x298, &&L0x299, &&L0x29a, &&L0x29b, &&L0x29c, &&L0x29d, &&L0x29e, &&L0x29f,
		&&L0x2a0, &&L0x2a1, &&L0x2a2, &&L0x2a3, &&L0x2a4, &&L0x2a5, &&L0x2a6, &&L0x2a7,
		&&L0x2a8, &&L0x2a9, &&L0x2aa, &&L0x2ab, &&L0x2ac, &&L0x2ad, &&L0x2ae, &&L0x2af,
		&&L0x2b0, &&L0x2b1, &&L0x2b2, &&L0x2b3, &&L0x2b4, &&L0x2b5, &&L0x2b6, &&L0x2b7,
		&&L0x2b8, &&L0x2b9, &&L0x2ba, &&L0x2bb, &&L0x2bc, &&L0x2bd, &&L0x2be, &&L0x2bf,

		&&L0x2c0, &&L0x2c1, &&L0x2c2, &&L0x2c3, &&L0x2c4, &&L0x2c5, &&L0x2c6, &&L0x2c7,
		&&L0x2c8, &&L0x2c9, &&L0x2ca, &&L0x2cb, &&L0x2cc, &&L0x2cd, &&L0x2ce, &&L0x2cf,
		&&L0x2d0, &&L0x2d1, &&L0x2d2, &&L0x2d3, &&L0x2d4, &&L0x2d5, &&L0x2d6, &&L0x2d7,
		&&L0x2d8, &&L0x2d9, &&L0x2da, &&L0x2db, &&L0x2dc, &&L0x2dd, &&L0x2de, &&L0x2df,
		&&L0x2e0, &&L0x2e1, &&L0x2e2, &&L0x2e3, &&L0x2e4, &&L0x2e5, &&L0x2e6, &&L0x2e7,
		&&L0x2e8, &&L0x2e9, &&L0x2ea, &&L0x2eb, &&L0x2ec, &&L0x2ed, &&L0x2ee, &&L0x2ef,
		&&L0x2f0, &&L0x2f1, &&L0x2f2, &&L0x2f3, &&L0x2f4, &&L0x2f5, &&L0x2f6, &&L0x2f7,
		&&L0x2f8, &&L0x2f9, &&L0x2fa, &&L0x2fb, &&L0x2fc, &&L0x2fd, &&L0x2fe, &&L0x2ff,

		&&L0x300, &&L0x301, &&L0x302, &&L0x303, &&L0x304, &&L0x305, &&L0x306, &&L0x307,
		&&L0x308, &&L0x309, &&L0x30a, &&L0x30b, &&L0x30c, &&L0x30d, &&L0x30e, &&L0x30f,
		&&L0x310, &&L0x311, &&L0x312, &&L0x313, &&L0x314, &&L0x315, &&L0x316, &&L0x317,
		&&L0x318, &&L0x319, &&L0x31a, &&L0x31b, &&L0x31c, &&L0x31d, &&L0x31e, &&L0x31f,
		&&L0x320, &&L0x321, &&L0x322, &&L0x323, &&L0x324, &&L0x325, &&L0x326, &&L0x327,
		&&L0x328, &&L0x329, &&L0x32a, &&L0x32b, &&L0x32c, &&L0x32d, &&L0x32e, &&L0x32f,
		&&L0x330, &&L0x331, &&L0x332, &&L0x333, &&L0x334, &&L0x335, &&L0x336, &&L0x337,
		&&L0x338, &&L0x339, &&L0x33a, &&L0x33b, &&L0x33c, &&L0x33d, &&L0x33e, &&L0x33f,

		&&L0x340, &&L0x341, &&L0x342, &&L0x343, &&L0x344, &&L0x345, &&L0x346, &&L0x347,
		&&L0x348, &&L0x349, &&L0x34a, &&L0x34b, &&L0x34c, &&L0x34d, &&L0x34e, &&L0x34f,
		&&L0x350, &&L0x351, &&L0x352, &&L0x353, &&L0x354, &&L0x355, &&L0x356, &&L0x357,
		&&L0x358, &&L0x359, &&L0x35a, &&L0x35b, &&L0x35c, &&L0x35d, &&L0x35e, &&L0x35f,
		&&L0x360, &&L0x361, &&L0x362, &&L0x363, &&L0x364, &&L0x365, &&L0x366, &&L0x367,
		&&L0x368, &&L0x369, &&L0x36a, &&L0x36b, &&L0x36c, &&L0x36d, &&L0x36e, &&L0x36f,
		&&L0x370, &&L0x371, &&L0x372, &&L0x373, &&L0x374, &&L0x375, &&L0x376, &&L0x377,
		&&L0x378, &&L0x379, &&L0x37a, &&L0x37b, &&L0x37c, &&L0x37d, &&L0x37e, &&L0x37f,

		&&L0x380, &&L0x381, &&L0x382, &&L0x383, &&L0x384, &&L0x385, &&L0x386, &&L0x387,
		&&L0x388, &&L0x389, &&L0x38a, &&L0x38b, &&L0x38c, &&L0x38d, &&L0x38e, &&L0x38f,
		&&L0x390, &&L0x391, &&L0x392, &&L0x393, &&L0x394, &&L0x395, &&L0x396, &&L0x397,
		&&L0x398, &&L0x399, &&L0x39a, &&L0x39b, &&L0x39c, &&L0x39d, &&L0x39e, &&L0x39f,
		&&L0x3a0, &&L0x3a1, &&L0x3a2, &&L0x3a3, &&L0x3a4, &&L0x3a5, &&L0x3a6, &&L0x3a7,
		&&L0x3a8, &&L0x3a9, &&L0x3aa, &&L0x3ab, &&L0x3ac, &&L0x3ad, &&L0x3ae, &&L0x3af,
		&&L0x3b0, &&L0x3b1, &&L0x3b2, &&L0x3b3, &&L0x3b4, &&L0x3b5, &&L0x3b6, &&L0x3b7,
		&&L0x3b8, &&L0x3b9, &&L0x3ba, &&L0x3bb, &&L0x3bc, &&L0x3bd, &&L0x3be, &&L0x3bf,

		&&L0x3c0, &&L0x3c1, &&L0x3c2, &&L0x3c3, &&L0x3c4, &&L0x3c5, &&L0x3c6, &&L0x3c7,
		&&L0x3c8, &&L0x3c9, &&L0x3ca, &&L0x3cb, &&L0x3cc, &&L0x3cd, &&L0x3ce, &&L0x3cf,
		&&L0x3d0, &&L0x3d1, &&L0x3d2, &&L0x3d3, &&L0x3d4, &&L0x3d5, &&L0x3d6, &&L0x3d7,
		&&L0x3d8, &&L0x3d9, &&L0x3da, &&L0x3db, &&L0x3dc, &&L0x3dd, &&L0x3de, &&L0x3df,
		&&L0x3e0, &&L0x3e1, &&L0x3e2, &&L0x3e3, &&L0x3e4, &&L0x3e5, &&L0x3e6, &&L0x3e7,
		&&L0x3e8, &&L0x3e9, &&L0x3ea, &&L0x3eb, &&L0x3ec, &&L0x3ed, &&L0x3ee, &&L0x3ef,
		&&L0x3f0, &&L0x3f1, &&L0x3f2, &&L0x3f3, &&L0x3f4, &&L0x3f5, &&L0x3f6, &&L0x3f7,
		&&L0x3f8, &&L0x3f9, &&L0x3fa, &&L0x3fb, &&L0x3fc, &&L0x3fd, &&L0x3fe, &&L0x3ff,
	};

	stress_set_proc_state(args->name, STRESS_STATE_RUN);

	for (;;) {
L0x000:
		inc_counter(args);
		if (!keep_stressing(args))
			break;
		RESEED_JMP

			 J(0x001) J(0x002) J(0x003) J(0x004) J(0x005) J(0x006) J(0x007)
		J(0x008) J(0x009) J(0x00a) J(0x00b) J(0x00c) J(0x00d) J(0x00e) J(0x00f)
		J(0x010) J(0x011) J(0x012) J(0x013) J(0x014) J(0x015) J(0x016) J(0x017)
		J(0x018) J(0x019) J(0x01a) J(0x01b) J(0x01c) J(0x01d) J(0x01e) J(0x01f)
		J(0x020) J(0x021) J(0x022) J(0x023) J(0x024) J(0x025) J(0x026) J(0x027)
		J(0x028) J(0x029) J(0x02a) J(0x02b) J(0x02c) J(0x02d) J(0x02e) J(0x02f)
		J(0x030) J(0x031) J(0x032) J(0x033) J(0x034) J(0x035) J(0x036) J(0x037)
		J(0x038) J(0x039) J(0x03a) J(0x03b) J(0x03c) J(0x03d) J(0x03e) J(0x03f)

		J(0x040) J(0x041) J(0x042) J(0x043) J(0x044) J(0x045) J(0x046) J(0x047)
		J(0x048) J(0x049) J(0x04a) J(0x04b) J(0x04c) J(0x04d) J(0x04e) J(0x04f)
		J(0x050) J(0x051) J(0x052) J(0x053) J(0x054) J(0x055) J(0x056) J(0x057)
		J(0x058) J(0x059) J(0x05a) J(0x05b) J(0x05c) J(0x05d) J(0x05e) J(0x05f)
		J(0x060) J(0x061) J(0x062) J(0x063) J(0x064) J(0x065) J(0x066) J(0x067)
		J(0x068) J(0x069) J(0x06a) J(0x06b) J(0x06c) J(0x06d) J(0x06e) J(0x06f)
		J(0x070) J(0x071) J(0x072) J(0x073) J(0x074) J(0x075) J(0x076) J(0x077)
		J(0x078) J(0x079) J(0x07a) J(0x07b) J(0x07c) J(0x07d) J(0x07e) J(0x07f)

		J(0x080) J(0x081) J(0x082) J(0x083) J(0x084) J(0x085) J(0x086) J(0x087)
		J(0x088) J(0x089) J(0x08a) J(0x08b) J(0x08c) J(0x08d) J(0x08e) J(0x08f)
		J(0x090) J(0x091) J(0x092) J(0x093) J(0x094) J(0x095) J(0x096) J(0x097)
		J(0x098) J(0x099) J(0x09a) J(0x09b) J(0x09c) J(0x09d) J(0x09e) J(0x09f)
		J(0x0a0) J(0x0a1) J(0x0a2) J(0x0a3) J(0x0a4) J(0x0a5) J(0x0a6) J(0x0a7)
		J(0x0a8) J(0x0a9) J(0x0aa) J(0x0ab) J(0x0ac) J(0x0ad) J(0x0ae) J(0x0af)
		J(0x0b0) J(0x0b1) J(0x0b2) J(0x0b3) J(0x0b4) J(0x0b5) J(0x0b6) J(0x0b7)
		J(0x0b8) J(0x0b9) J(0x0ba) J(0x0bb) J(0x0bc) J(0x0bd) J(0x0be) J(0x0bf)

		J(0x0c0) J(0x0c1) J(0x0c2) J(0x0c3) J(0x0c4) J(0x0c5) J(0x0c6) J(0x0c7)
		J(0x0c8) J(0x0c9) J(0x0ca) J(0x0cb) J(0x0cc) J(0x0cd) J(0x0ce) J(0x0cf)
		J(0x0d0) J(0x0d1) J(0x0d2) J(0x0d3) J(0x0d4) J(0x0d5) J(0x0d6) J(0x0d7)
		J(0x0d8) J(0x0d9) J(0x0da) J(0x0db) J(0x0dc) J(0x0dd) J(0x0de) J(0x0df)
		J(0x0e0) J(0x0e1) J(0x0e2) J(0x0e3) J(0x0e4) J(0x0e5) J(0x0e6) J(0x0e7)
		J(0x0e8) J(0x0e9) J(0x0ea) J(0x0eb) J(0x0ec) J(0x0ed) J(0x0ee) J(0x0ef)
		J(0x0f0) J(0x0f1) J(0x0f2) J(0x0f3) J(0x0f4) J(0x0f5) J(0x0f6) J(0x0f7)
		J(0x0f8) J(0x0f9) J(0x0fa) J(0x0fb) J(0x0fc) J(0x0fd) J(0x0fe) J(0x0ff)

		J(0x100) J(0x101) J(0x102) J(0x103) J(0x104) J(0x105) J(0x106) J(0x107)
		J(0x108) J(0x109) J(0x10a) J(0x10b) J(0x10c) J(0x10d) J(0x10e) J(0x10f)
		J(0x110) J(0x111) J(0x112) J(0x113) J(0x114) J(0x115) J(0x116) J(0x117)
		J(0x118) J(0x119) J(0x11a) J(0x11b) J(0x11c) J(0x11d) J(0x11e) J(0x11f)
		J(0x120) J(0x121) J(0x122) J(0x123) J(0x124) J(0x125) J(0x126) J(0x127)
		J(0x128) J(0x129) J(0x12a) J(0x12b) J(0x12c) J(0x12d) J(0x12e) J(0x12f)
		J(0x130) J(0x131) J(0x132) J(0x133) J(0x134) J(0x135) J(0x136) J(0x137)
		J(0x138) J(0x139) J(0x13a) J(0x13b) J(0x13c) J(0x13d) J(0x13e) J(0x13f)

		J(0x140) J(0x141) J(0x142) J(0x143) J(0x144) J(0x145) J(0x146) J(0x147)
		J(0x148) J(0x149) J(0x14a) J(0x14b) J(0x14c) J(0x14d) J(0x14e) J(0x14f)
		J(0x150) J(0x151) J(0x152) J(0x153) J(0x154) J(0x155) J(0x156) J(0x157)
		J(0x158) J(0x159) J(0x15a) J(0x15b) J(0x15c) J(0x15d) J(0x15e) J(0x15f)
		J(0x160) J(0x161) J(0x162) J(0x163) J(0x164) J(0x165) J(0x166) J(0x167)
		J(0x168) J(0x169) J(0x16a) J(0x16b) J(0x16c) J(0x16d) J(0x16e) J(0x16f)
		J(0x170) J(0x171) J(0x172) J(0x173) J(0x174) J(0x175) J(0x176) J(0x177)
		J(0x178) J(0x179) J(0x17a) J(0x17b) J(0x17c) J(0x17d) J(0x17e) J(0x17f)

		J(0x180) J(0x181) J(0x182) J(0x183) J(0x184) J(0x185) J(0x186) J(0x187)
		J(0x188) J(0x189) J(0x18a) J(0x18b) J(0x18c) J(0x18d) J(0x18e) J(0x18f)
		J(0x190) J(0x191) J(0x192) J(0x193) J(0x194) J(0x195) J(0x196) J(0x197)
		J(0x198) J(0x199) J(0x19a) J(0x19b) J(0x19c) J(0x19d) J(0x19e) J(0x19f)
		J(0x1a0) J(0x1a1) J(0x1a2) J(0x1a3) J(0x1a4) J(0x1a5) J(0x1a6) J(0x1a7)
		J(0x1a8) J(0x1a9) J(0x1aa) J(0x1ab) J(0x1ac) J(0x1ad) J(0x1ae) J(0x1af)
		J(0x1b0) J(0x1b1) J(0x1b2) J(0x1b3) J(0x1b4) J(0x1b5) J(0x1b6) J(0x1b7)
		J(0x1b8) J(0x1b9) J(0x1ba) J(0x1bb) J(0x1bc) J(0x1bd) J(0x1be) J(0x1bf)

		J(0x1c0) J(0x1c1) J(0x1c2) J(0x1c3) J(0x1c4) J(0x1c5) J(0x1c6) J(0x1c7)
		J(0x1c8) J(0x1c9) J(0x1ca) J(0x1cb) J(0x1cc) J(0x1cd) J(0x1ce) J(0x1cf)
		J(0x1d0) J(0x1d1) J(0x1d2) J(0x1d3) J(0x1d4) J(0x1d5) J(0x1d6) J(0x1d7)
		J(0x1d8) J(0x1d9) J(0x1da) J(0x1db) J(0x1dc) J(0x1dd) J(0x1de) J(0x1df)
		J(0x1e0) J(0x1e1) J(0x1e2) J(0x1e3) J(0x1e4) J(0x1e5) J(0x1e6) J(0x1e7)
		J(0x1e8) J(0x1e9) J(0x1ea) J(0x1eb) J(0x1ec) J(0x1ed) J(0x1ee) J(0x1ef)
		J(0x1f0) J(0x1f1) J(0x1f2) J(0x1f3) J(0x1f4) J(0x1f5) J(0x1f6) J(0x1f7)
		J(0x1f8) J(0x1f9) J(0x1fa) J(0x1fb) J(0x1fc) J(0x1fd) J(0x1fe) J(0x1ff)

		J(0x200) J(0x201) J(0x202) J(0x203) J(0x204) J(0x205) J(0x206) J(0x207)
		J(0x208) J(0x209) J(0x20a) J(0x20b) J(0x20c) J(0x20d) J(0x20e) J(0x20f)
		J(0x210) J(0x211) J(0x212) J(0x213) J(0x214) J(0x215) J(0x216) J(0x217)
		J(0x218) J(0x219) J(0x21a) J(0x21b) J(0x21c) J(0x21d) J(0x21e) J(0x21f)
		J(0x220) J(0x221) J(0x222) J(0x223) J(0x224) J(0x225) J(0x226) J(0x227)
		J(0x228) J(0x229) J(0x22a) J(0x22b) J(0x22c) J(0x22d) J(0x22e) J(0x22f)
		J(0x230) J(0x231) J(0x232) J(0x233) J(0x234) J(0x235) J(0x236) J(0x237)
		J(0x238) J(0x239) J(0x23a) J(0x23b) J(0x23c) J(0x23d) J(0x23e) J(0x23f)

		J(0x240) J(0x241) J(0x242) J(0x243) J(0x244) J(0x245) J(0x246) J(0x247)
		J(0x248) J(0x249) J(0x24a) J(0x24b) J(0x24c) J(0x24d) J(0x24e) J(0x24f)
		J(0x250) J(0x251) J(0x252) J(0x253) J(0x254) J(0x255) J(0x256) J(0x257)
		J(0x258) J(0x259) J(0x25a) J(0x25b) J(0x25c) J(0x25d) J(0x25e) J(0x25f)
		J(0x260) J(0x261) J(0x262) J(0x263) J(0x264) J(0x265) J(0x266) J(0x267)
		J(0x268) J(0x269) J(0x26a) J(0x26b) J(0x26c) J(0x26d) J(0x26e) J(0x26f)
		J(0x270) J(0x271) J(0x272) J(0x273) J(0x274) J(0x275) J(0x276) J(0x277)
		J(0x278) J(0x279) J(0x27a) J(0x27b) J(0x27c) J(0x27d) J(0x27e) J(0x27f)

		J(0x280) J(0x281) J(0x282) J(0x283) J(0x284) J(0x285) J(0x286) J(0x287)
		J(0x288) J(0x289) J(0x28a) J(0x28b) J(0x28c) J(0x28d) J(0x28e) J(0x28f)
		J(0x290) J(0x291) J(0x292) J(0x293) J(0x294) J(0x295) J(0x296) J(0x297)
		J(0x298) J(0x299) J(0x29a) J(0x29b) J(0x29c) J(0x29d) J(0x29e) J(0x29f)
		J(0x2a0) J(0x2a1) J(0x2a2) J(0x2a3) J(0x2a4) J(0x2a5) J(0x2a6) J(0x2a7)
		J(0x2a8) J(0x2a9) J(0x2aa) J(0x2ab) J(0x2ac) J(0x2ad) J(0x2ae) J(0x2af)
		J(0x2b0) J(0x2b1) J(0x2b2) J(0x2b3) J(0x2b4) J(0x2b5) J(0x2b6) J(0x2b7)
		J(0x2b8) J(0x2b9) J(0x2ba) J(0x2bb) J(0x2bc) J(0x2bd) J(0x2be) J(0x2bf)

		J(0x2c0) J(0x2c1) J(0x2c2) J(0x2c3) J(0x2c4) J(0x2c5) J(0x2c6) J(0x2c7)
		J(0x2c8) J(0x2c9) J(0x2ca) J(0x2cb) J(0x2cc) J(0x2cd) J(0x2ce) J(0x2cf)
		J(0x2d0) J(0x2d1) J(0x2d2) J(0x2d3) J(0x2d4) J(0x2d5) J(0x2d6) J(0x2d7)
		J(0x2d8) J(0x2d9) J(0x2da) J(0x2db) J(0x2dc) J(0x2dd) J(0x2de) J(0x2df)
		J(0x2e0) J(0x2e1) J(0x2e2) J(0x2e3) J(0x2e4) J(0x2e5) J(0x2e6) J(0x2e7)
		J(0x2e8) J(0x2e9) J(0x2ea) J(0x2eb) J(0x2ec) J(0x2ed) J(0x2ee) J(0x2ef)
		J(0x2f0) J(0x2f1) J(0x2f2) J(0x2f3) J(0x2f4) J(0x2f5) J(0x2f6) J(0x2f7)
		J(0x2f8) J(0x2f9) J(0x2fa) J(0x2fb) J(0x2fc) J(0x2fd) J(0x2fe) J(0x2ff)

		J(0x300) J(0x301) J(0x302) J(0x303) J(0x304) J(0x305) J(0x306) J(0x307)
		J(0x308) J(0x309) J(0x30a) J(0x30b) J(0x30c) J(0x30d) J(0x30e) J(0x30f)
		J(0x310) J(0x311) J(0x312) J(0x313) J(0x314) J(0x315) J(0x316) J(0x317)
		J(0x318) J(0x319) J(0x31a) J(0x31b) J(0x31c) J(0x31d) J(0x31e) J(0x31f)
		J(0x320) J(0x321) J(0x322) J(0x323) J(0x324) J(0x325) J(0x326) J(0x327)
		J(0x328) J(0x329) J(0x32a) J(0x32b) J(0x32c) J(0x32d) J(0x32e) J(0x32f)
		J(0x330) J(0x331) J(0x332) J(0x333) J(0x334) J(0x335) J(0x336) J(0x337)
		J(0x338) J(0x339) J(0x33a) J(0x33b) J(0x33c) J(0x33d) J(0x33e) J(0x33f)

		J(0x340) J(0x341) J(0x342) J(0x343) J(0x344) J(0x345) J(0x346) J(0x347)
		J(0x348) J(0x349) J(0x34a) J(0x34b) J(0x34c) J(0x34d) J(0x34e) J(0x34f)
		J(0x350) J(0x351) J(0x352) J(0x353) J(0x354) J(0x355) J(0x356) J(0x357)
		J(0x358) J(0x359) J(0x35a) J(0x35b) J(0x35c) J(0x35d) J(0x35e) J(0x35f)
		J(0x360) J(0x361) J(0x362) J(0x363) J(0x364) J(0x365) J(0x366) J(0x367)
		J(0x368) J(0x369) J(0x36a) J(0x36b) J(0x36c) J(0x36d) J(0x36e) J(0x36f)
		J(0x370) J(0x371) J(0x372) J(0x373) J(0x374) J(0x375) J(0x376) J(0x377)
		J(0x378) J(0x379) J(0x37a) J(0x37b) J(0x37c) J(0x37d) J(0x37e) J(0x37f)

		J(0x380) J(0x381) J(0x382) J(0x383) J(0x384) J(0x385) J(0x386) J(0x387)
		J(0x388) J(0x389) J(0x38a) J(0x38b) J(0x38c) J(0x38d) J(0x38e) J(0x38f)
		J(0x390) J(0x391) J(0x392) J(0x393) J(0x394) J(0x395) J(0x396) J(0x397)
		J(0x398) J(0x399) J(0x39a) J(0x39b) J(0x39c) J(0x39d) J(0x39e) J(0x39f)
		J(0x3a0) J(0x3a1) J(0x3a2) J(0x3a3) J(0x3a4) J(0x3a5) J(0x3a6) J(0x3a7)
		J(0x3a8) J(0x3a9) J(0x3aa) J(0x3ab) J(0x3ac) J(0x3ad) J(0x3ae) J(0x3af)
		J(0x3b0) J(0x3b1) J(0x3b2) J(0x3b3) J(0x3b4) J(0x3b5) J(0x3b6) J(0x3b7)
		J(0x3b8) J(0x3b9) J(0x3ba) J(0x3bb) J(0x3bc) J(0x3bd) J(0x3be) J(0x3bf)

		J(0x3c0) J(0x3c1) J(0x3c2) J(0x3c3) J(0x3c4) J(0x3c5) J(0x3c6) J(0x3c7)
		J(0x3c8) J(0x3c9) J(0x3ca) J(0x3cb) J(0x3cc) J(0x3cd) J(0x3ce) J(0x3cf)
		J(0x3d0) J(0x3d1) J(0x3d2) J(0x3d3) J(0x3d4) J(0x3d5) J(0x3d6) J(0x3d7)
		J(0x3d8) J(0x3d9) J(0x3da) J(0x3db) J(0x3dc) J(0x3dd) J(0x3de) J(0x3df)
		J(0x3e0) J(0x3e1) J(0x3e2) J(0x3e3) J(0x3e4) J(0x3e5) J(0x3e6) J(0x3e7)
		J(0x3e8) J(0x3e9) J(0x3ea) J(0x3eb) J(0x3ec) J(0x3ed) J(0x3ee) J(0x3ef)
		J(0x3f0) J(0x3f1) J(0x3f2) J(0x3f3) J(0x3f4) J(0x3f5) J(0x3f6) J(0x3f7)
		J(0x3f8) J(0x3f9) J(0x3fa) J(0x3fb) J(0x3fc) J(0x3fd) J(0x3fe) J(0x3ff)
	}
	stress_set_proc_state(args->name, STRESS_STATE_DEINIT);

	return EXIT_SUCCESS;
}

stressor_info_t stress_branch_info = {
	.stressor = stress_branch,
	.class = CLASS_CPU,
	.help = help
};
#else
stressor_info_t stress_branch_info = {
	.stressor = stress_not_implemented,
	.class = CLASS_CPU,
	.help = help
};
#endif
