#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#define Width  220
#define Height 65
#define OverY(y) ((y) < 0 || (y) > Width)
#define OverX(x) ((x) < 0 || (x) > Height)
#define Over(x , y) (OverX(x) || OverY(y))
#define WillLife 3
#define WillDead 2
#define Life 1
#define Dead 0
#define InitLife 14000
int map [Height][Width];
void Draw()
{
 int i , j;
 for(i = 0; i < Height; i++)
 {
  for(j = 0; j < Width; j++)
  {
   if(map [i][j] == Life)
    printf("0");
   else
    printf(" ");
  }
  putchar('\n');
 }
}
int Neighbor(int x , int y)
{
 int offsetx , offsety , neigh , count = 0;
 for(offsetx = (-1); offsetx <= 1; offsetx++)
 {
  for(offsety = (-1); offsety <= 1; offsety++)
  {
   if(offsetx != 0 || offsety != 0)
   {
    if(!Over((x + offsetx) , (y + offsety)))
    {
     neigh = map [x + offsetx][y + offsety];
     if(neigh == Life || neigh == WillDead)
     count++;
    }
   }
  }
 }
 return count;
}
void RandLife()
{
 int x , y;
 srand(time(NULL));
 for(int i = 0; i < InitLife; i++)
 {
  x = rand() % Height;
  y = rand() % Width;
  if(map [x][y] != Life)
   map [x][y] = Life;
 }
}
void gotoxy(int x , int y)
{
 COORD point = { x, y };
 HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleCursorPosition(HOutput, point);
}int main()
{
 int i , j , state , neigh_num;
 RandLife();
 for( ; ; )
 {
  gotoxy(0 , 0);
  Draw();
  for(i = 0; i < Height; i++)
  {
   for(j = 0; j < Width; j++)
   {
    state = map [i][j];
    neigh_num = Neighbor(i , j);
    if(state == Life)
    {
     if(neigh_num < 2 || neigh_num > 3)
      map [i][j] = WillDead;
    }
    else
    {
     if(neigh_num == 3)
      map [i][j] = WillLife;
    }
   }
  }
  for(i = 0; i < Height; i++)
   for(j = 0; j < Width; j++)
   {
    if(map [i][j] == WillLife)
     map [i][j] = Life;
    if(map [i][j] == WillDead)
     map [i][j] = Dead;
   }
  Sleep(10);
 }
}