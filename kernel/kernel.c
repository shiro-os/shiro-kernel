void load() {
    int a = 200;
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'X';
}
