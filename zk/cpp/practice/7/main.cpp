#include <iostream>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

// 得到一个(min, max)区间的随机整数
int getrand(int min, int max) {
    return (min+rand() % (max - min + 1));
}

class Piece {
public:
    int score;
    int shape; // 表示当前方块的形状
    int next_shape; // 表示下一个方块的形状
    
    int head_x; // 当前方块首个box的位置, 标记位置
    int head_y;
    
    int size_h; // 当前方块的size
    int size_w;

    int next_size_h; // 下一个方块的size
    int next_size_w;

    int box_shape[4][4]; // 当前方块的shape数组 4 * 4
    int next_box_shape[4][4];

    int box_map[30][45]; // 用来标记游戏框内的每个box

    bool game_over; // 游戏结束的标志
public:
    void initial(); // 初始化函数
    void set_shape(int &cshape, int box_shape[][4], int &size_w, int &size_h); // 设置方块形状
    
    void score_next(); // 显示下一个方块的形状和分数
    void judge(); // 判断是否层满
    void move(); // 移动函数, 通过<- -> 控制
    void rotate(); // 旋转函数
    bool isaggin(); // 判断下一次行动是否会越界或者重合
    bool exsqr(int row); // 判断当前行是否空
};

void Piece::set_shape(int &cshape, int shape[][4], int &size_w, int &size_h) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            shape[i][j] = 0;
        }
    }
    
    // 设置7种初始形状并设置它们的size
    switch(cshape) {
        case 0:
            size_h = 1;
            size_w = 4;
            shape[0][0] = 1;
            shape[0][1] = 1;
            shape[0][2] = 1;
            shape[0][3] = 1;
            break;
        case 1:
            size_h = 2;
            size_w = 3;
            shape[0][0] = 1;
            shape[1][0] = 1;
            shape[1][1] = 1;
            shape[1][2] = 1;
            break;
        case 2:
            size_h = 2;
            size_w = 3;
            shape[0][2] = 1;
            shape[1][0] = 1;
            shape[1][1] = 1;
            shape[1][2] = 1;
            break;
        case 3:
            size_h = 2;
            size_w = 3;
            shape[0][1] = 1;
            shape[0][2] = 1;
            shape[1][0] = 1;
            shape[1][1] = 1;
            break;
        case 4:
            size_h = 2;
            size_w = 3;
            shape[0][0] = 1;
            shape[0][1] = 1;
            shape[1][1] = 1;
            shape[1][2] = 1;
            break;
        case 5:
            size_h = 2;
            size_w = 2;
            shape[0][0] = 1;
            shape[0][1] = 1;
            shape[1][0] = 1;
            shape[1][1] = 1;
            break;
        case 6:
            size_h = 2;
            size_w = 3;
            shape[0][1] = 1;
            shape[1][0] = 1;
            shape[1][1] = 1;
            shape[1][2] = 1;
            break;
    }

    // 设置完形状以后初始化方块的起始位置
    head_x = game_win_width / 2;
    head_y = 1;

    // 如果刚初始化就重合了, 游戏结束
    if (isaggin()) {
        game_over = true;
    }
}

void Piece::rotate() {
    int temp[4][4] = {0}; // 临时变量
    int temp_piece[4][4] = {0}; // 备份用的数组
    int i, j, tmp_size_h, tmp_size_w;

    tmp_size_w = size_w;
    tmp_size_h = size_h;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // 备份一下当前的方块, 如果旋转失败, 则返回当前的形状
            temp_piece[i][j] = box_shape[i][j];
        }
    }
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            temp[j][i] = box_shape[i][j];
        }
    }
    i = size_h;
    size_h = size_w;
    size_w = i;
    for (i = 0; i < size_h; i++) {
        for (j = 0; j < size_w; j++) {
            box_shape[i][size_w-1-j] = temp[i][j];
        }
    }

    if(isaggin()){
            for(int i=0; i<4;i++)
                for(int j=0;j<4;j++)
                    box_shape[i][j]=temp_piece[i][j];
            size_w=tmp_size_w;    //记得size也要变回原来的size
            size_h=tmp_size_h;
    }

    /*如果旋转成功，那么在屏幕上进行显示*/
    else{
        for(int i=0; i<4;i++)
            for(int j=0;j<4;j++){
                if(temp_piece[i][j]==1){
                    mvwaddch(game_win,head_y+i,head_x+j,' ');    //移动到game_win窗口的某个坐标处打印字符
                    wrefresh(game_win);
                }
            }
        for(int i=0; i<size_h;i++)
            for(int j=0;j<size_w;j++){
                if(this->box_shape[i][j]==1){
                    mvwaddch(game_win,head_y+i,head_x+j,'#');
                    wrefresh(game_win);
                }
            }

    }
}

int main()
{
    return 0;
}

