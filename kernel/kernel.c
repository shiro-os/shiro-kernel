#define BYTE unsigned char
#define DWORD unsigned long 
#define VIDMEM (BYTE*)0xb8000

void _entry();
void init();
void setForegroundColor(BYTE color);
void cls();
void print(char * msg);
int strlen(char * str);

void _entry() {
    init();
    while(1);
}

void init() {
    cls();
    setForegroundColor(4);
    // TODO: .DATA SECTION STILL NEEDS FIXING!
    // char pointers don't get initialized correctly
    char * msg = "oof";
    for(int i = 0; i < strlen(msg); i++) {
        *(VIDMEM + i*2) = '_';
    }
    
    setForegroundColor(2);
}

void print(char * msg) {
    BYTE* video_memory = VIDMEM;
    int index = 0;
    while(msg[index] != '_') {
        *video_memory = msg[index];
        video_memory = video_memory + 2;
        index = index + 1;
    }
}

int strlen(char * str) {
    int len = 0;
    while(str[len] != 0) {
        len++;
    }
    return len;
}

void cls() {
   BYTE* video_memory = VIDMEM;
   for(int i = 0; i < 2000; i++) {
       *video_memory = '.';
       video_memory = (BYTE*)(video_memory + 2);
   } 
}

void setForegroundColor(BYTE color) {
   BYTE* video_memory = (BYTE*)(VIDMEM + 1);
   for(int i = 0; i < 2000; i++) {
       *video_memory = color;
       video_memory = video_memory + 2;
   } 
}
