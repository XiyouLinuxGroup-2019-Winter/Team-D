#include <iostream>
#include <ncurses.h>

WINDOW *create_newwin(int height, int width, int starty, int startx) {
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0); // 在已经定义的窗口外围画上边框
    wrefresh(local_win);
    return local_win;
}

int main()
{
    initscr(); // 初始化进入NCURSES模式
    printw("Hello World!"); // 在虚拟屏上打印Hello World!
    printw("string");
    mvprintw(1, 20, "string");
    refresh(); // 将虚拟屏幕上的内容写到显示器上, 并刷新
    WINDOW *local_win = create_newwin(20, 20, 2, 2);
    wprintw(local_win, "string"); 
    mvwprintw(local_win, 3, 3, "string");
    refresh();
    getch();
    endwin(); // 退出NCURSES模式
    return 0;
}

