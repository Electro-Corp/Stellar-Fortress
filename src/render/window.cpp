#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <termios.h>
#include <random>



Window::Window(char* title, int width, int height, int x, int y){
  this->title = title;
  this->width = width;
  this->height = height;
  this->x = x;
  this->y = y;
  //
  this->xViewPortMin = 0;
  this->xViewPortMax = 100;
  this->yViewPortMin = 0;
  this->yViewPortMax = 50;
}

void Window::SetMapViewport(int xViewPortMin, int xViewPortMax, int yViewPortMin, int yViewPortMax){
  this->xViewPortMin = xViewPortMin;
  this->xViewPortMax = xViewPortMax;
  this->yViewPortMin = yViewPortMin;
  this->yViewPortMax = yViewPortMax;
}

void Window::RenderMap(std::vector<std::vector<Tile>> tiles){
  int c = 0;
  for(int y = 0; y < tiles.size(); y++){
    for(int x = 0; x < tiles[y].size(); x++){
      //if((tiles[y][x].x > xViewPortMin && tiles[y][x].x < xViewPortMax) && (tiles[y][x].y > yViewPortMin && tiles[y][x].y < yViewPortMax)){
        renderTile(tiles[y][x]);
       
      //}
       c++;
    }
  }
  //printf("dimentsions(x,y) = %d %d (rendered %d) (expected %d)\n",tiles[0].size(),tiles.size(),c,tiles[0].size()*tiles.size());
}

void Window::renderTile(Tile t){
  //if((t.x - yViewPortMin)+x < width + x && (t.x - xViewPortMin)+y < height + y){
  printf("\033[%d;%dH", (t.y - yViewPortMin) + y , (t.x - xViewPortMin)+ x);
  printf("\033[48;2;%d;%d;%dm %c ",(int)t.rgb.r,(int)t.rgb.g,(int)t.rgb.b,' ');
  //printf("\033[48;2;%d;%d;%dm %c ",255,0,0,' ');
  //}else{
  //  printf("unable to print\n");
  //}
}



// hola. 
// RENDER UI
void Window::RenderPanel(UI* ui){
  printf("\033[48;2;0;0;0m");
  // Print Title of window
  printf("\033[%d;%dH",this->y - 1, this->x);
  printf("%s",this->title);
  for(int yDraw = this->y; yDraw < this->height + this->y; yDraw++){
    for(int xDraw = this->x; xDraw < this->width + this->x; xDraw++){
      printf("\033[%d;%dH",yDraw, xDraw);
      printf("\033[48;2;%d;%d;%dm %c  \033[48;2;0;0;0m",100,100,100,' ');
    }
  }
  for(int i = 0; i < ui->texts.size(); i++){
    printf("\033[%d;%dH",this->y + i + 1, this->x);
    printf("%s",ui->texts[i].text);
  }
}