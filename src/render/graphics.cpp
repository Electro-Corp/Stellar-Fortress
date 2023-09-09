/*
  GRAPHICS.CPP
  Renders the game using SDL
*/

#define FADE_SPEED 0.0007f
//#define BUTTON_DEBUG
// COnstructiort
Renderer::Renderer(int width, int height, renderMode rm, std::string *fontPath = nullptr){
  this->rm = rm;
  this->width = width;
  this->height = height;
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("SDL INIT FAILURE ( %s )\n", SDL_GetError());
    exit(-1);
  }
  window = SDL_CreateWindow("Stellar Fortress", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  surface = SDL_GetWindowSurface(window);

  
  // Init fonts
  TTF_Init();
  if(fontPath){
    gFont = TTF_OpenFont(fontPath->c_str(), 28);
  }else{
    gFont = TTF_OpenFont("game/basegame/data/fonts/lazy.ttf", 28);
  }
  if(!gFont){printf("FONT_ERROR: %s\n",TTF_GetError());}
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
  if(rm != RM_LoadScreen)
    display();

  l.log("Renderer.Renderer", "Logging init. Renderer in mode " + std::to_string(rm));
}

// Initilze the menu 
void Renderer::initMenu(std::string logoPath, std::string bgPath){
  //logo = IMG_LoadTexture(logoPath);
  SDL_Rect stretchRect;
  background = SDL_LoadBMP(bgPath.c_str());
  SDL_BlitSurface(background, NULL, surface, NULL );
  if(background == NULL){
    printf("BG_LOADERROR\n");
    exit(-1);
  }

  logo = SDL_LoadBMP(logoPath.c_str());
  
  stretchRect.x = 0;
  stretchRect.y = 0;
  stretchRect.w = width;
  stretchRect.h = height / 2;
  SDL_BlitScaled(logo, NULL, surface, &stretchRect);

  // Load buttons
  for(int i = 0; i < MENU_buttons.size(); i++){
    stretchRect.x = MENU_buttons[i].x;
    stretchRect.y = MENU_buttons[i].y;
    stretchRect.w = width / 2;
    stretchRect.h = height / 4;
    MENU_buttons[i].width = 200;
    MENU_buttons[i].height = 30;
    #ifdef DEBUG
    printf("Button Debug:\nX = %d\nY = %d\nW = %d\nH = %d\n",stretchRect.x,stretchRect.y,stretchRect.w,stretchRect.h);
    #endif
    SDL_BlitScaled(MENU_buttons[i].buttonSurface, NULL, surface, &stretchRect);
  }
  // Order the buttons
  bubbleSortButton(&MENU_buttons);
}
void bubbleSortButton(std::vector<Button>* MENU_buttons){
  bool isBad = false;
  for(int i = 0; i < MENU_buttons->size() - 1; i++){
    if((MENU_buttons->operator[](i).x + MENU_buttons->operator[](i).y / 2) > (MENU_buttons->operator[](i+1).x + MENU_buttons->operator[](i+1).y / 2)){
      Button tmp = MENU_buttons->operator[](i);
      MENU_buttons->operator[](i) = MENU_buttons->operator[](i + 1);
      MENU_buttons->operator[](i + 1) = tmp;
      isBad = true;
    }
  }
  if(isBad) bubbleSortButton(MENU_buttons);
}
#include <cmath>
int indexOfButton(float avg, std::vector<Button> buttons){
  int m = buttons.size() / 2;
  int L = 0;
  int R = buttons.size() - 1;
  while(L <= R){
    float thatAvg = (buttons[m].x + buttons[m].y) / 2;
    m = floor((L + R) / 2);
    if(thatAvg < avg - 10){
      L = m + 1;
    }
    else if(thatAvg > avg){
      R = m -1;
    }
    else{
      return m;
    }
  }
  return -1;
}
void Renderer::addButton(Button b){
  this->MENU_buttons.push_back(b);
}
void Renderer::procEvents(){
  SDL_Event e;
  SDL_PollEvent(&e);
  /*while( != 0){
    
  }*/
  if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
    int x, y;
    SDL_GetMouseState(&x, &y);
    switch(e.type){
      case SDL_MOUSEBUTTONDOWN:
        //MENU_buttons[indexOfButton((x + y)/2,MENU_buttons)].onClick();
        for(int i = 0; i < MENU_buttons.size(); i++){
          if(
            x > MENU_buttons[i].x && x < MENU_buttons[i].x + MENU_buttons[i].width &&
            y > MENU_buttons[i].y && y < MENU_buttons[i].y + MENU_buttons[i].height + MENU_buttons[i].yoffset
            ) MENU_buttons[i].onClick();
        }
        break;
      case SDL_MOUSEMOTION:
        if(rm == RM_Menu){
          SDL_Rect stretchRect;
          stretchRect.x = x / 9.0f;
          stretchRect.y = y / 9.0f ;
          stretchRect.w = 100000;
          stretchRect.h = 100000;
          SDL_BlitScaled(background, NULL, surface, &stretchRect);
        }
        break;
    }
  }
}
float alpha = 0.0f;
float alphaCalc = 0.0f;

void Renderer::initLoadScreen(std::string bgPath, std::string loadText){
  background = SDL_LoadBMP(bgPath.c_str());
  SDL_BlitSurface(background, NULL, surface, NULL );
  if(background == NULL){
    printf("BG_LOADERROR\n");
    exit(-1);
  }
  if(gFont != NULL){
    SDL_Color blackTmp = {0,0,0};
    loadTextSurface = TTF_RenderText_Blended(gFont, loadText.c_str(), blackTmp);
    SDL_BlitSurface(loadTextSurface, NULL, surface, NULL);
  }else{
    printf("\nFONT NOT LOADED ERROR\nCHECK INTEGRITY OF GAME FILES\n");
    exit(-1);
  }
}

void Renderer::display(std::vector<std::vector<Tile>> *tiles = nullptr){
  SDL_FillRect(surface, NULL, 0x000000);
  if(rm == RM_Menu){
        SDL_Rect stretchRect;
        SDL_FillRect(surface, NULL, 0x000000);
        SDL_BlitSurface(background, NULL, surface, NULL );
        // Fade in the menu
        SDL_SetSurfaceAlphaMod(logo, alpha);
        if (alpha < SDL_ALPHA_OPAQUE) {
          
          alphaCalc += FADE_SPEED * (SDL_GetTicks());
          alpha = alphaCalc;
          //printf("alphacalc -> %f\n", alphaCalc);
        }
        // if alpha is above 255 clamp it
        if (alpha >= SDL_ALPHA_OPAQUE) {
            alpha = SDL_ALPHA_OPAQUE;
            alphaCalc = (float)SDL_ALPHA_OPAQUE;


            // ill put this in a fucntion called "draw buttons" orsmthing later
            for(int i = 0; i < MENU_buttons.size(); i++){
              stretchRect.x = MENU_buttons[i].x;
              stretchRect.y = MENU_buttons[i].y;
              stretchRect.w = width / 2;
              stretchRect.h = height / 4;
              MENU_buttons[i].width = stretchRect.w;
              MENU_buttons[i].height = stretchRect.h / 4 + MENU_buttons[i].yoffset;
              SDL_BlitScaled(MENU_buttons[i].buttonSurface, NULL, surface, &stretchRect);

              // DEBUG
              #ifdef BUTTON_DEBUG
              SDL_Rect srcrect;

              srcrect.x = MENU_buttons[i].x;
              srcrect.y = MENU_buttons[i].y + MENU_buttons[i].yoffset;
              srcrect.w = MENU_buttons[i].width;
              srcrect.h = MENU_buttons[i].height;
              
              SDL_BlitSurface(surface, &srcrect, NULL, &srcrect);
              SDL_FillRect(surface, &srcrect, 0xFFFFFA + (i * 50));
              #endif
            }

      }
    // TEMP =====
      
      stretchRect.x = 0;
      stretchRect.y = 0;
      stretchRect.w = width;
      stretchRect.h = height / 2;
      SDL_BlitScaled(logo, NULL, surface, &stretchRect);
    // END TEMP
  }
  if(rm == RM_LoadScreen){
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = width;
    stretchRect.h = height;
    //SDL_BlitSurface(background, NULL, surface, NULL );
    if(background != NULL){
      SDL_BlitScaled(background, NULL, surface, &stretchRect);
    }
    if(loadTextSurface){
     SDL_BlitSurface(loadTextSurface, NULL, surface, NULL);
    } else{
      l.log("Renderer.display", "Text surface does not exist!");
      printf("no text surface\n");
      exit(-1);
    }
  }
  if(rm == RM_Game){
    if(tiles != NULL){
      // Render the tile
      for(int y = 0; y < tiles->size(); y++){
        for(int x = 0; x < tiles[y].size(); x++){
          // 
          SDL_Rect srcrect;

          srcrect.x = (*tiles)[y][x].x;
          srcrect.y = (*tiles)[y][x].y;
          srcrect.w = 10;
          srcrect.h = 10;
          
          SDL_BlitSurface(surface, &srcrect, NULL, &srcrect);
          SDL_FillRect(surface, &srcrect, 0xFFFFFA + (x * 5 * y));
        }
      }
    }
  }
  procEvents();
  SDL_UpdateWindowSurface(window);
}
void Renderer::endWindow(){
  SDL_DestroyWindow(window);
}