#define IS_DATA_NULL(struct)  !(struct.data[0]||struct.data[1]||struct.data[2]||struct.data[3]||struct.data[4]||struct.data[5]||struct.data[6]||struct.data[7]) 


const char keys[] = {
    0x0, 0x0, 0x0, 0x0,
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '\n', 0x0, 0x0, // DEL
    0x0, // TAB
    ' ', // SPACE
    '-', '=', '[', ']', '\\', 0x0, ';', '\'', '`', ',', '.', '/', 
    0x0, // CAPS LOCK
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4f, // R_ARROW
    0x0, // L_ARROW
    0x0, // D_ARROW
    0x0, // U_ARROW
    0x0, // NUM LOCK
};

const char shift_keys[] = {
    0x0, 0x0, 0x0, 0x0,
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
    '\n', 0x0, 0x0, // DEL
    0x0, // TAB
    ' ', // SPACE
    '_', '+', '{', '}', '|', 0x0, ':', '"', '~', '<', '>', '?', 
    0x0, // CAPS LOCK
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4f, // R_ARROW
    0x0, // L_ARROW
    0x0, // D_ARROW
    0x0, // U_ARROW
    0x0, // NUM LOCK
};