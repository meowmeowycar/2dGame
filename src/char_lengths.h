#pragma once

const float arial_char_lengths[128] = {
    /* 0 - 31 */ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

    0.28f, // 32 = 'Space'

    /* 33 - 47 */ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

    0.56f, 0.49f, 0.56f, 0.56f, 0.56f, 0.56f, 0.56f, 0.56f, 0.56f, 0.56f, // 48-57 = '0' to '9'

    /* 58 - 64 */ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

    0.67f, 0.67f, 0.72f, 0.73f, 0.67f, 0.61f, 0.78f, 0.72f, 0.27f, 0.50f, 0.66f, 0.55f, 0.83f, 0.72f, 0.78f, 0.67f,
    0.78f, 0.72f, 0.66f, 0.61f, 0.72f, 0.67f, 0.94f, 0.67f, 0.66f, 0.61f, // 65-90 = 'A'-'Z'

    /* 91 - 96 */ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

    0.56f, 0.56f, 0.50f, 0.56f, 0.56f, 0.263f, 0.56f, 0.55f, 0.22f, 0.215f, 0.50f, 0.22f, 0.83f, 0.56f, 0.56f, 0.56f,
    0.56f, 0.34f, 0.50f, 0.28f, 0.56f, 0.50f, 0.72f, 0.50f, 0.50f, 0.50f,  // 97-122 = 'a'-'z'

    /* 123-127 */ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
};

inline float calculate_string_length(std::string font, std::string text, float text_size) {
    float length = 0;

    for (unsigned char character : text) {
        if (font == "arial") {
            length += arial_char_lengths[character] * text_size;
        } else {
            // default is also Arial
            length += arial_char_lengths[character] * text_size;
        }
    }

    return length;
}

inline float calculate_string_length(std::string font, std::string text) {
   return calculate_string_length(font, text, 1);
}

/*
char_lengths[32] = 0.28;  // Space

char_lengths[48] = 0.56;  // 0
char_lengths[49] = 0.49;  // 1
char_lengths[50] = 0.56;  // 2
char_lengths[51] = 0.56;  // 3
char_lengths[52] = 0.56;  // 4
char_lengths[53] = 0.56;  // 5
char_lengths[54] = 0.56;  // 6
char_lengths[55] = 0.56;  // 7
char_lengths[56] = 0.56;  // 8
char_lengths[57] = 0.56;  // 9

char_lengths[65] = 0.67;  // A
char_lengths[66] = 0.67;  // B
char_lengths[67] = 0.72;  // C
char_lengths[68] = 0.73;  // D
char_lengths[69] = 0.67;  // E
char_lengths[70] = 0.61;  // F
char_lengths[71] = 0.78;  // G
char_lengths[72] = 0.72;  // H
char_lengths[73] = 0.27;  // I
char_lengths[74] = 0.50;  // J
char_lengths[75] = 0.66;  // K
char_lengths[76] = 0.55;  // L
char_lengths[77] = 0.83;  // M
char_lengths[78] = 0.72;  // N
char_lengths[79] = 0.78;  // O
char_lengths[80] = 0.67;  // P
char_lengths[81] = 0.78;  // Q
char_lengths[82] = 0.72;  // R
char_lengths[83] = 0.66;  // S
char_lengths[84] = 0.61;  // T
char_lengths[85] = 0.72;  // U
char_lengths[86] = 0.67;  // V
char_lengths[87] = 0.94;  // W
char_lengths[88] = 0.67;  // X
char_lengths[89] = 0.66;  // Y
char_lengths[90] = 0.61;  // Z

char_lengths[97] = 0.56;   // a
char_lengths[98] = 0.56;   // b
char_lengths[99] = 0.50;   // c
char_lengths[100] = 0.56;  // d
char_lengths[101] = 0.56;  // e
char_lengths[102] = 0.263; // f
char_lengths[103] = 0.56;  // g
char_lengths[104] = 0.55;  // h
char_lengths[105] = 0.22;  // i
char_lengths[106] = 0.215; // j
char_lengths[107] = 0.50;  // k
char_lengths[108] = 0.22;  // l
char_lengths[109] = 0.83;  // m
char_lengths[110] = 0.56;  // n
char_lengths[111] = 0.56;  // o
char_lengths[112] = 0.56;  // p
char_lengths[113] = 0.56;  // q
char_lengths[114] = 0.34;  // r
char_lengths[115] = 0.50;  // s
char_lengths[116] = 0.28;  // t
char_lengths[117] = 0.56;  // u
char_lengths[118] = 0.50;  // v
char_lengths[119] = 0.72;  // w
char_lengths[120] = 0.50;  // x
char_lengths[121] = 0.50;  // y
char_lengths[122] = 0.50;  // z
*/