#pragma once

const float arial_char_lengths[128] = {
    // ------------------------------
    // ASCII 0–31: Znaki sterujące
    // ------------------------------
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

    // ------------------------------
    // Znaki ogólne i interpunkcyjne
    // ------------------------------
    0.28f, // Space
    0.28f, // !
    0.35f, // "
    0.55f, // #
    0.56f, // $
    0.89f, // %
    0.66f, // &
    0.19f, // '
    0.33f, // (
    0.33f, // )
    0.39f, // *
    0.58f, // +
    0.28f, // ,
    0.33f, // -
    0.28f, // .
    0.28f, // /

    // ------------------------------
    // Cyfry 0–9
    // ------------------------------
    0.56f, // 0
    0.49f, // 1
    0.56f, // 2
    0.56f, // 3
    0.56f, // 4
    0.56f, // 5
    0.56f, // 6
    0.56f, // 7
    0.56f, // 8
    0.56f, // 9

    // ------------------------------
    // Dalsza interpunkcja i symbole
    // ------------------------------
    0.28f, // :
    0.28f, // ;
    0.59f, // <
    0.58f, // =
    0.59f, // >
    0.56f, // ?
    1.01f, // @

    // ------------------------------
    // Wielkie litery A–Z
    // ------------------------------
    0.67f, // A
    0.67f, // B
    0.72f, // C
    0.73f, // D
    0.67f, // E
    0.61f, // F
    0.78f, // G
    0.72f, // H
    0.27f, // I
    0.50f, // J
    0.66f, // K
    0.55f, // L
    0.83f, // M
    0.72f, // N
    0.78f, // O
    0.67f, // P
    0.78f, // Q
    0.72f, // R
    0.66f, // S
    0.61f, // T
    0.72f, // U
    0.67f, // V
    0.94f, // W
    0.67f, // X
    0.66f, // Y
    0.61f, // Z

    // ------------------------------
    // Nawiasy, backslash i underscore
    // ------------------------------
    0.28f, // [
    0.28f, // '\'
    0.28f, // ]
    0.47f, // ^
    0.56f, // _

    // ------------------------------
    // Znaki akcentów i backtick
    // ------------------------------
    0.33f, // `

    // ------------------------------
    // Małe litery a–z
    // ------------------------------
    0.56f,   // a
    0.56f,   // b
    0.50f,   // c
    0.56f,   // d
    0.56f,   // e
    0.263f,  // f
    0.56f,   // g
    0.55f,   // h
    0.22f,   // i
    0.215f,  // j
    0.50f,   // k
    0.22f,   // l
    0.83f,   // m
    0.56f,   // n
    0.56f,   // o
    0.56f,   // p
    0.56f,   // q
    0.34f,   // r
    0.50f,   // s
    0.28f,   // t
    0.56f,   // u
    0.50f,   // v
    0.72f,   // w
    0.50f,   // x
    0.50f,   // y
    0.50f,   // z

    // ------------------------------
    // Znaki klamrowe i tylda
    // ------------------------------
    0.33f, // {
    0.26f, // |
    0.34f, // }
    0.58f, // ~

    // ------------------------------
    // ASCII 127: DEL (niewidoczny)
    // ------------------------------
    0.0f
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
char_lengths[33] = 0.28;  // !
char_lengths[34] = 0.35;  // "
char_lengths[35] = 0.55;  // #
char_lengths[36] = 0.56;  // $
char_lengths[37] = 0.89;  // %
char_lengths[38] = 0.66;  // &
char_lengths[39] = 0.19;  // '
char_lengths[40] = 0.33;  // (
char_lengths[41] = 0.33;  // )
char_lengths[42] = 0.39;  // *
char_lengths[43] = 0.58;  // +
char_lengths[44] = 0.28;  // ,
char_lengths[45] = 0.33;  // -
char_lengths[46] = 0.28;  // .
char_lengths[47] = 0.28;  // /

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

char_lengths[58] = 0.28;  // :
char_lengths[59] = 0.28;  // ;
char_lengths[60] = 0.59;  // <
char_lengths[61] = 0.58;  // =
char_lengths[62] = 0.59;  // >
char_lengths[63] = 0.56;  // ?
char_lengths[64] = 1.01;  // @

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

char_lengths[91] = 0.28;  // [
char_lengths[92] = 0.28;  // \
char_lengths[93] = 0.28;  // ]
char_lengths[94] = 0.47;  // ^
char_lengths[95] = 0.56;  // _
char_lengths[96] = 0.33;  // `

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

char_lengths[123] = 0.33;  // {
char_lengths[124] = 0.26;  // |
char_lengths[125] = 0.34;  // }
char_lengths[126] = 0.58;  // ~
*/