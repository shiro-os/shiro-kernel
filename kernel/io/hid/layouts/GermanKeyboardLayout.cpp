#include "GermanKeyboardLayout.hpp"
#include "Keys.h"
#include "../../../utils/string.hpp"

GermanKeyboardLayout* GermanKeyboardLayout::instance;

GermanKeyboardLayout* GermanKeyboardLayout::getInstance() {
    if(GermanKeyboardLayout::instance) {
        return GermanKeyboardLayout::instance;
    }

    return GermanKeyboardLayout::instance = new GermanKeyboardLayout();
}

GermanKeyboardLayout::GermanKeyboardLayout() {
    this->mappings = new KeyMapping[84];
    this->mappedKeys = 84;
    this->mappings[0]  = KeyMapping(0x53, KEY_NUMBLOCK_COMMA,    new String("NUMBLOCK_COMMA"));
    this->mappings[1]  = KeyMapping(0x01, KEY_ESCAPE,            new String("ESCAPE"));
    this->mappings[2]  = KeyMapping(0x3B, KEY_F1,                new String("F1"));
    this->mappings[3]  = KeyMapping(0x3C, KEY_F2,                new String("F2"));
    this->mappings[4]  = KeyMapping(0x3D, KEY_F3,                new String("F3"));
    this->mappings[5]  = KeyMapping(0x3E, KEY_F4,                new String("F4"));
    this->mappings[6]  = KeyMapping(0x3F, KEY_F5,                new String("F5"));
    this->mappings[7]  = KeyMapping(0x40, KEY_F6,                new String("F6"));
    this->mappings[8]  = KeyMapping(0x41, KEY_F7,                new String("F7"));
    this->mappings[9]  = KeyMapping(0x42, KEY_F8,                new String("F8"));
    this->mappings[10] = KeyMapping(0x43, KEY_F9,                new String("F9"));
    this->mappings[11] = KeyMapping(0x44, KEY_F10,               new String("F10"));
    this->mappings[12] = KeyMapping(0x45, KEY_F11,               new String("F11"));
    this->mappings[13] = KeyMapping(0x57, KEY_F12,               new String("F12"));
    this->mappings[14] = KeyMapping(0x54, KEY_PRNT,              new String("PRNT"));
    this->mappings[15] = KeyMapping(0x46, KEY_SCROLL,            new String("SCROLL"));
    this->mappings[16] = KeyMapping(0x39, KEY_SPACE,             new String("SPACE"));
    this->mappings[17] = KeyMapping(0x3A, KEY_CAPSLOCK,          new String("CAPSLOCK"));
    this->mappings[18] = KeyMapping(0x2A, KEY_LSHIFT,            new String("LSHIFT"));
    this->mappings[19] = KeyMapping(0x1D, KEY_LCTRL,             new String("LCTRL"));
    this->mappings[20] = KeyMapping(0x38, KEY_LALT,              new String("LALT"));
    this->mappings[21] = KeyMapping(0x0F, KEY_TAB,               new String("TAB"));
    this->mappings[22] = KeyMapping(0x1A, KEY_OEM1,              new String("OEM1"));
    this->mappings[23] = KeyMapping(0x2B, KEY_OEM2,              new String("OEM2"));
    this->mappings[24] = KeyMapping(0x27, KEY_OEM3,              new String("OEM3"));
    this->mappings[25] = KeyMapping(0x0C, KEY_OEM4,              new String("OEM4"));
    this->mappings[26] = KeyMapping(0x29, KEY_OEM5,              new String("OEM5"));
    this->mappings[27] = KeyMapping(0x0D, KEY_OEM6,              new String("OEM6"));
    this->mappings[28] = KeyMapping(0x28, KEY_OEM7,              new String("OEM7"));
    this->mappings[29] = KeyMapping(0x56, KEY_OEM10,             new String("OEM10"));
    this->mappings[30] = KeyMapping(0x1B, KEY_OEM_PL,            new String("OEM_PL"));
    this->mappings[31] = KeyMapping(0x35, KEY_OEM_MI,            new String("OEM_MI"));
    this->mappings[32] = KeyMapping(0x0B, KEY_NUM_0,             new String("0"));
    this->mappings[33] = KeyMapping(0x02, KEY_NUM_1,             new String("1"));
    this->mappings[34] = KeyMapping(0x03, KEY_NUM_2,             new String("2"));
    this->mappings[35] = KeyMapping(0x04, KEY_NUM_3,             new String("3"));
    this->mappings[36] = KeyMapping(0x05, KEY_NUM_4,             new String("4"));
    this->mappings[37] = KeyMapping(0x06, KEY_NUM_5,             new String("5"));
    this->mappings[38] = KeyMapping(0x07, KEY_NUM_6,             new String("6"));
    this->mappings[39] = KeyMapping(0x08, KEY_NUM_7,             new String("7"));
    this->mappings[40] = KeyMapping(0x09, KEY_NUM_8,             new String("8"));
    this->mappings[41] = KeyMapping(0x0A, KEY_NUM_9,             new String("9"));
    this->mappings[42] = KeyMapping(0x1E, KEY_A,                 new String("A"));
    this->mappings[43] = KeyMapping(0x30, KEY_B,                 new String("B"));
    this->mappings[44] = KeyMapping(0x2E, KEY_C,                 new String("C"));
    this->mappings[45] = KeyMapping(0x20, KEY_D,                 new String("D"));
    this->mappings[46] = KeyMapping(0x12, KEY_E,                 new String("E"));
    this->mappings[47] = KeyMapping(0x21, KEY_F,                 new String("F"));
    this->mappings[48] = KeyMapping(0x22, KEY_G,                 new String("G"));
    this->mappings[49] = KeyMapping(0x23, KEY_H,                 new String("H"));
    this->mappings[50] = KeyMapping(0x17, KEY_I,                 new String("I"));
    this->mappings[51] = KeyMapping(0x24, KEY_J,                 new String("J"));
    this->mappings[52] = KeyMapping(0x25, KEY_K,                 new String("K"));
    this->mappings[53] = KeyMapping(0x26, KEY_L,                 new String("L"));
    this->mappings[54] = KeyMapping(0x32, KEY_M,                 new String("M"));
    this->mappings[55] = KeyMapping(0x31, KEY_N,                 new String("N"));
    this->mappings[56] = KeyMapping(0x18, KEY_O,                 new String("O"));
    this->mappings[57] = KeyMapping(0x19, KEY_P,                 new String("P"));
    this->mappings[58] = KeyMapping(0x10, KEY_Q,                 new String("Q"));
    this->mappings[59] = KeyMapping(0x13, KEY_R,                 new String("R"));
    this->mappings[60] = KeyMapping(0x1F, KEY_S,                 new String("S"));
    this->mappings[61] = KeyMapping(0x14, KEY_T,                 new String("T"));
    this->mappings[62] = KeyMapping(0x16, KEY_U,                 new String("U"));
    this->mappings[63] = KeyMapping(0x2F, KEY_V,                 new String("V"));
    this->mappings[64] = KeyMapping(0x11, KEY_W,                 new String("W"));
    this->mappings[65] = KeyMapping(0x2D, KEY_X,                 new String("X"));
    this->mappings[66] = KeyMapping(0x2C, KEY_Y,                 new String("Y"));
    this->mappings[67] = KeyMapping(0x15, KEY_Z,                 new String("Z"));
    this->mappings[68] = KeyMapping(0x34, KEY_OEM_PE,            new String("OEM_PE"));
    this->mappings[69] = KeyMapping(0x33, KEY_OEM_CC,            new String("OEM_CC"));
    this->mappings[70] = KeyMapping(0x45, KEY_NUMBLOCK_LOCK,     new String("NUMBLOCK_LOCK"));
    this->mappings[71] = KeyMapping(0x37, KEY_NUMBLOCK_MULTIPLY, new String("NUMBLOCK_MULTIPLY"));
    this->mappings[72] = KeyMapping(0x4A, KEY_NUMBLOCK_SUBTRACT, new String("NUMBLOCK_SUBTRACT"));
    this->mappings[73] = KeyMapping(0x52, KEY_NUMBLOCK_0,        new String("NUMBLOCK_0"));
    this->mappings[74] = KeyMapping(0x4F, KEY_NUMBLOCK_1,        new String("NUMBLOCK_1"));
    this->mappings[75] = KeyMapping(0x50, KEY_NUMBLOCK_2,        new String("NUMBLOCK_2"));
    this->mappings[76] = KeyMapping(0x51, KEY_NUMBLOCK_3,        new String("NUMBLOCK_3"));
    this->mappings[77] = KeyMapping(0x4B, KEY_NUMBLOCK_4,        new String("NUMBLOCK_4"));
    this->mappings[78] = KeyMapping(0x4C, KEY_NUMBLOCK_5,        new String("NUMBLOCK_5"));
    this->mappings[79] = KeyMapping(0x4D, KEY_NUMBLOCK_6,        new String("NUMBLOCK_6"));
    this->mappings[80] = KeyMapping(0x47, KEY_NUMBLOCK_7,        new String("NUMBLOCK_7"));
    this->mappings[81] = KeyMapping(0x48, KEY_NUMBLOCK_8,        new String("NUMBLOCK_8"));
    this->mappings[82] = KeyMapping(0x49, KEY_NUMBLOCK_9,        new String("NUMBLOCK_9"));
    this->mappings[83] = KeyMapping(0x4E, KEY_NUMBLOCK_ADD,      new String("NUMBLOCK_ADD"));
}
