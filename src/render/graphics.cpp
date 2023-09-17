/*
  GRAPHICS.CPP
  Renders the game using SDL
*/

#define FADE_SPEED 0.002f
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

  // Init Map stuff
  if(rm == RM_Game){
    mapXOff = 0;
    mapYOff = 0;
    viewX = 0;
    viewY = 0;
    SCALE = 11;
  }
  
  // Init fonts
  TTF_Init();
  if(fontPath){
    gFont = TTF_OpenFont(fontPath->c_str(), 28);
  }else{
    gFont = TTF_OpenFont("game/basegame/data/fonts/bot.ttf", 28);
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
  if(e.type == SDL_WINDOWEVENT){
    switch (e.window.event) {
      case SDL_WINDOWEVENT_CLOSE:   // exit game
          exit(0);
          break;

      default:
          break;
    }
  }
  switch(e.type){
    case SDL_KEYDOWN:
        switch(e.key.keysym.sym){
          case SDLK_UP:
            if(rm == RM_Game){
              mapYOff--;
            }
            break;
          case SDLK_DOWN:
            if(rm == RM_Game){
              mapYOff++;
            }
            break;
          case SDLK_LEFT:
            if(rm == RM_Game){
              mapXOff--;
            }
            break;
          case SDLK_RIGHT:
            if(rm == RM_Game){
              mapXOff++;
            }
            break;
          case SDLK_EQUALS:
            if(rm == RM_Game){
              SCALE++;
            }
            break;
          case SDLK_MINUS:
            if(rm == RM_Game){
              SCALE--;
            }
            break;
        }
        break;
  }
  viewX = mapXOff; // T M
  viewY = mapYOff; // E P
  if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
    int x, y;
    SDL_GetMouseState(&x, &y);
    switch(e.type){
      case SDL_MOUSEBUTTONDOWN:
        //MENU_buttons[indexOfButton((x + y)/2,MENU_buttons)].onClick();
        if(rm == RM_Menu){
          for(int i = 0; i < MENU_buttons.size(); i++){
            if(
              x > MENU_buttons[i].x && x < MENU_buttons[i].x + MENU_buttons[i].width &&
              y > MENU_buttons[i].y && y < MENU_buttons[i].y + MENU_buttons[i].height + MENU_buttons[i].yoffset
              ) MENU_buttons[i].onClick();
          }
        }
        break;
      case SDL_MOUSEMOTION:
        if(rm == RM_Menu){
          
        }
        break;
    }
  }
}

float alpha = 0.0f;
float alphaCalc = 0.0f;
/*
  Puts text on the load screen with a background
  Call this before calling display during a loading screen
*/
void Renderer::initLoadScreen(std::string bgPath, std::string loadText, bool noBg = false){
  if(!noBg){
    background = SDL_LoadBMP(bgPath.c_str());
    SDL_BlitSurface(background, NULL, surface, NULL );
    if(background == NULL){
      printf("BG_LOADERROR\n");
      exit(-1);
    }
  }
  if(gFont != NULL){
    SDL_Color blackTmp = {255,255,255};
    if(noBg) blackTmp = {255, 255, 255};
    loadTextSurface = TTF_RenderText_Blended(gFont, loadText.c_str(), blackTmp);
    SDL_BlitSurface(loadTextSurface, NULL, surface, NULL);
  }else{
    printf("\nFONT NOT LOADED ERROR\nCHECK INTEGRITY OF GAME FILES\n");
    exit(-1);
  }
}

/*
  Displays the window based on the current
  render mode
*/
void Renderer::display(std::vector<std::vector<Tile>> *tiles = nullptr, bool noLoadImage = false){
  procEvents();
  SDL_FillRect(surface, NULL, 0x000000);

  // Switch this to a "switch" statment at
  // some point, i think its better practice
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
    if(background != NULL && noLoadImage == false){
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
    // Render Tiles
    if(tiles != nullptr){

      // We need view box code so that I can make a good looking map because if the dimentions are as small as they are right now it will always be horrible
      
      
      // Render the tile
      //std::vector<std::vector<Tile>>& defRef = *tiles;
      for(int y = 0; y < tiles->size(); y++){
        for(int x = 0; x < (tiles)[0].size(); x++) {// No more render p2
          // No more render (sadge)
          if((*tiles)[y].size() < 500 && (*tiles)[y].size() > 0){
          // it kinda works now  I dont think ti works now im gonna be honest
          // pretty cool
          // still segfaults at some areas though
          //printf("currently at: %d, %d\n", x, y);
          
          SDL_Rect srcrect;
          //Tile tmp = (*tiles)[y][x]; // sometimes it segfaults here 
          srcrect.x = (((*tiles)[y][x].x * SCALE) + (mapXOff * SCALE));
          srcrect.y = ((*tiles)[y][x].y * SCALE) + (mapYOff * SCALE);
          srcrect.w = /*(width / 50 ) * */SCALE; // tiles on this row
          // Did you not like me trying to render a full sized map
          srcrect.h = /*(height / (*tiles).size()) * */ SCALE; // amount of y's
// and| wha| d|death to the heratics|id you | |he menu does| render | no toucho |  nvm | it was some goof| replit |ssue
          //printf("X = %d\nY = %d\nW = %d\n H= %d\n, TILESY = %d\n TILESX = %d\n", srcrect.x, srcrect.y, srcrect.w, srcrect.h, (*tiles)[0].size(), (*tiles).size());
          //getchar();
          //SDL_Color color = {defRef[y][x].rgb.r, defRef[y][x].rgb.g, defRef[y][x].rgb.b};
          
          SDL_BlitSurface(surface, &srcrect, NULL, &srcrect);
          SDL_FillRect(surface, &srcrect, SDL_MapRGB(surface->format, (*tiles)[y][x].rgb.r, (*tiles)[y][x].rgb.g, (*tiles)[y][x].rgb.b));
          }
        }
      }
    }
    // Render UI Panels (these prob will be loaded from scripts)
  }
  SDL_UpdateWindowSurface(window);
}

/*
  Kill the window
*/
void Renderer::endWindow(){
  SDL_DestroyWindow(window);
}