//
// Created by fishy on 26-1-25.
//
#include "gfx.h"
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265358979323846
void draw_Triangle( int x1, int y1, int x2, int y2, int x3, int y3 );
void draw_square(int x, int y,int SIZE);
void draw_snow(int x, int y, double SIZE, double rotation);
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 );
void shrinkingSquare(int x,int y ,int size);
void snowFlake(int x, int y, double SIZE, double base_rotation);
void circularLace(int center_x, int center_y, int radius, int depth, float size_ratio);
void tree(int start_x, int start_y, double length, double angle, int depth);
void Fern(int x, int y, double trunk_length, double angle, int depth);

int main(){
    int width = 700, height = 700, mrgn = 20;
    gfx_open(width, height, "Sierpinski's Triangle");
    while(1) {
        gfx_clear();
        //sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
        //shrinkingSquare(width/2,height/2,400);
        //snowFlake(width/2, height/2, 200,0);  // 画海星分形
        //tree(350, 680, 180, PI/2, 12);
        //circularLace(350, 350, 150, 4, 0.4);
        Fern(350, 680, 500, PI/2, 4);
        if ( gfx_wait() == 'q' ) break;
    }
}



void draw_Triangle( int x1, int y1, int x2, int y2, int x3, int y3 )
{
    gfx_line(x1,y1,x2,y2);
    gfx_line(x2,y2,x3,y3);
    gfx_line(x3,y3,x1,y1);
}
void draw_square(int x, int y,int SIZE){
    int half = SIZE / 2;
    gfx_line(x - half, y - half, x + half, y - half);
    gfx_line(x + half, y - half, x + half, y + half);
    gfx_line(x + half, y + half, x - half, y + half);
    gfx_line(x - half, y + half, x - half, y - half);
}
void draw_circle(int x, int y, int SIZE)
{
    gfx_circle(x, y, SIZE / 2);
}
void draw_polygon(int x, int y, int sides,int SIZE)
{
    if (sides < 3) return;
    double radius = SIZE / 2.0;
    for (int i = 0; i < sides; i++)
    {
        double angle1 = 2 * PI * i / sides;
        double angle2 = 2 * PI * (i + 1) / sides;

        int x1 = x + radius * cos(angle1);
        int y1 = y + radius * sin(angle1);
        int x2 = x + radius * cos(angle2);
        int y2 = y + radius * sin(angle2);
        gfx_line(x1, y1, x2, y2);
    }
}
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
    // Base case.
    if( abs(x2-x1) < 5 ) return;
    // Draw a triangle
    draw_Triangle( x1, y1, x2, y2, x3, y3 );
    // Recursive calls
    sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
    sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
    sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}
void shrinkingSquare(int x, int y, int size) {
    if (size<8) return ;
    draw_square(x,y,size);
    int ed = size/2;
    shrinkingSquare(x-ed,y-ed,(int)(ed*0.93));
    shrinkingSquare(x+ed,y-ed,(int)(ed*0.93));
    shrinkingSquare(x-ed,y+ed,(int)(ed*0.93));
    shrinkingSquare(x+ed,y+ed,(int)(ed*0.93));
}
void draw_snow(int x, int y, double SIZE, double rotation)
{
    // 5条射线，每条相隔72度
    for (int i = 0; i < 5; i++)
    {
        // 计算每条臂的角度（加上旋转参数）
        double base_angle = rotation + (36.0 + i * 72.0) * (PI / 180.0);
        double math_angle = (PI/2) - base_angle;

        double x_end = x + SIZE * cos(math_angle);
        double y_end = y - SIZE * sin(math_angle);

        gfx_line(x, y, x_end, y_end);
    }
}
void snowFlake(int x, int y, double SIZE, double base_rotation)
{
    if (SIZE < 1)
    {
        return;
    }

    // 画旋转后的海星
    // 这里需要修改draw_snow函数支持旋转角度
    // 暂时用简单版本
    draw_snow(x, y, SIZE, base_rotation);

    // 子海星的5个方向（相对于父海星的臂方向）
    double child_angles[5];
    child_angles[0] = base_rotation + 36.0 * (PI / 180.0);
    child_angles[1] = base_rotation + 108.0 * (PI / 180.0);
    child_angles[2] = base_rotation + 180.0 * (PI / 180.0);
    child_angles[3] = base_rotation + 252.0 * (PI / 180.0);
    child_angles[4] = base_rotation + 324.0 * (PI / 180.0);

    for (int i = 0; i < 5; i++)
    {
        double math_angle = (PI/2) - child_angles[i];

        int child_x = x + SIZE * cos(math_angle);
        int child_y = y - SIZE * sin(math_angle);

        // 递归，子海星保持父臂的方向
        snowFlake(child_x, child_y, SIZE / 2.7, child_angles[i]);
    }
}
void circularLace(int center_x, int center_y, int radius, int depth, float size_ratio) {
    if (radius < 3 || depth == 0) return;

    draw_circle(center_x, center_y, radius * 2);

    for (int i = 0; i < 6; i++) {
        double angle = 2 * PI * i / 6;
        int child_x = center_x + radius * cos(angle);
        int child_y = center_y - radius * sin(angle);

        // 使用自定义的比例因子，比如0.4让子圆更小
        circularLace(child_x, child_y, radius * size_ratio, depth - 1, size_ratio);
    }
}
void tree(int start_x, int start_y, double length, double angle, int depth) {
    if (depth == 0) return;

    // 计算树枝终点坐标
    int end_x = start_x + length * cos(angle);
    int end_y = start_y - length * sin(angle);  // Y轴向下，所以用减

    // 绘制当前树枝
    gfx_line(start_x, start_y, end_x, end_y);

    // 计算两个分支的长度（主干的70%）
    double branch_length = length * 0.7;

    // 计算两个分支的角度（相对于当前树枝±45度）
    double left_angle = angle - 45.0 * (PI / 180.0);   // 左分支：逆时针45度
    double right_angle = angle + 45.0 * (PI / 180.0);  // 右分支：顺时针45度

    // 递归绘制左右分支
    tree(end_x, end_y, branch_length, left_angle, depth - 1);
    tree(end_x, end_y, branch_length, right_angle, depth - 1);
}
void Fern(int x, int y, double trunk_length, double angle, int depth) {
    // 基础情况：递归深度为0时停止
    if (depth == 0) return;

    // 1. 画当前树干（从起点到终点）
    int trunk_end_x = x + trunk_length * cos(angle);
    int trunk_end_y = y - trunk_length * sin(angle);
    gfx_line(x, y, trunk_end_x, trunk_end_y);

    // 2. 树枝长度是树干的1/3
    double branch_length = trunk_length / 3.0;

    // 3. 在树干的4个等分点（1/4, 2/4, 3/4, 4/4）处分叉
    //    注意：4/4是树干的顶端
    for (int i = 1; i <= 4; i++) {
        // 计算分叉点在树干上的位置比例：0.25, 0.50, 0.75, 1.00
        double split_ratio = i * 0.25;

        // 分叉点坐标
        int split_x = x + (trunk_length * split_ratio) * cos(angle);
        int split_y = y - (trunk_length * split_ratio) * sin(angle);

        // 左右分支角度（35度）
        double left_angle = angle - 35.0 * (PI / 180.0);
        double right_angle = angle + 35.0 * (PI / 180.0);

        // 左右分支终点
        int left_end_x = split_x + branch_length * cos(left_angle);
        int left_end_y = split_y - branch_length * sin(left_angle);
        int right_end_x = split_x + branch_length * cos(right_angle);
        int right_end_y = split_y - branch_length * sin(right_angle);

        // 画左右分支
        gfx_line(split_x, split_y, left_end_x, left_end_y);
        gfx_line(split_x, split_y, right_end_x, right_end_y);

        // 4. 递归：分支终点成为下一层树干的起点
        //    深度减1，继续相同的分叉模式
        Fern(split_x, split_y, branch_length, left_angle, depth - 1);
        Fern(split_x, split_y, branch_length, right_angle, depth - 1);
    }
}
