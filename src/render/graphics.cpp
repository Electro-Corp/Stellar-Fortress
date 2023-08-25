Renderer::Renderer(int width, int height){
  renderWindow = new sf::RenderWindow(sf::VideoMode(width, height), "Stellar Fortress"); 
}

void Renderer::procEvents(){
  sf::Event event;
}

void Renderer::display(){
  renderWindow->clear();
  renderWindow->display();
}