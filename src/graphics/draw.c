#include "draw.h"

int duckgraph_drawline() {
    int gd = DETECT, gm;
    /* initialization of graphic mode */
    initgraph(&gd, &gm, "C:\\TC\\BGI"); 
    line(100,100,200, 200);
    getch();
    closegraph();
    return 0;
}

