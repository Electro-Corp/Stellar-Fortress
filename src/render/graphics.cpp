Renderer::Renderer(int width, int height, renderMode rm){
  this->rm = rm;
  this->width = width;
  this->height = height;
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("SDL INIT FAILURE ( %s )\n", SDL_GetError());
    exit(-1);
  }
  window = SDL_CreateWindow("Stellar Fortress", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  surface = SDL_GetWindowSurface(window);
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
  display();
}
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

void Renderer::addButton(Button b){
  this->MENU_buttons.push_back(b);
}
void Renderer::procEvents(){
  SDL_Event e;
  while(SDL_PollEvent(&e) != 0){
    
  }
  if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
    int x, y;
    SDL_GetMouseState(&x, &y);
    switch(e.type){
      case SDL_MOUSEBUTTONUP:
      break;
    }
  }
}

void Renderer::display(){
  procEvents();
  if(rm = RM_Menu){
    
  }
  
  SDL_UpdateWindowSurface(window);
}