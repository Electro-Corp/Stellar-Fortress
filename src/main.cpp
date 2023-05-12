#include <iostream>
#include <menu.h>
#include <ncurses.h>
#include <stdlib.h>
#include "game.h"
#include <filesystem>

namespace fs = std::filesystem;

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4
int c = 0;
char *choices[] = {
  "Play Stellar Fortress",
  "Mod Menu",
  "Achievements",
  "Settings",
  "Quit"
};

char *game_options[] = {
  "New Game",
  "Load Game",
  "Save Game",
  "Back"
};

char *mod_options[] = {
  "Installed Mods",
  "Add Mod", // Does it open mod folder or a dif menu?
  "Uninstall Mod",
  "Back"
};

char *settings_options[] = {
  "Help", // idk placeholder or smthn
  "Back"
};

int game_menu();
int settings_menu();
int mod_menu();
int view_mods();
std::string readJSON(std::string filename);
int main() {
  int n_choices = sizeof(choices) / sizeof(char*);
  int highlight = 1;
  int c;


  
  // init
  initscr();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);

  mvprintw(2, 2, "Use arrow keys to navigate, press Enter to select:");
  for (int i = 0; i < n_choices; i++) {
    if (i == highlight - 1) {
      attron(A_REVERSE);
    }
    mvprintw(4 + i, 2, "%s", choices[i]);
    if (i == highlight - 1) {
      attroff(A_REVERSE);
    }
  }
  refresh();

  while (1) {
    c = getch();
    switch(c) {
      case KEY_UP:
        if (highlight > 1) {
          highlight--;
        }
        break;
      case KEY_DOWN:
        if (highlight < n_choices) {
          highlight++;
        }
        break;
      case '\n':
        // Im cracked ik (too good)
    //https://docs.google.com/document/d/1_Yi43bByeCOJEtDY150Kx_A0CSBt9PQAB_HWoJLZgiQ/edit
        if (highlight == 1) {
          // Stellar Fortress
          // probably creates a new game class or smhtn idk 
          // yeah i imagne so
          game_menu();
          goto endmenuloop;
        } else if (highlight == 2) {
          // Mod Menu
          mod_menu();  // andrew when he learns about forward decleration (ill tell u later)
          // why cpp act like inheritance without inhertence
        } else if (highlight == 3) {
          // Achievements
        } else if (highlight == 4) {
          // settings
          settings_menu();
        } else if(highlight == 5) {
          // quit
          return 0;
        } 
        
      default:
        break;
    }

    
    clear();
    mvprintw(2, 2, "Use arrow keys to navigate, press Enter to select:");
    for (int i = 0; i < n_choices; i++) {
      if (i == highlight - 1) {
        attron(A_REVERSE);
      }
      mvprintw(4 + i, 2, "%s", choices[i]);
      if (i == highlight - 1) {
        attroff(A_REVERSE);
      }
    }
    refresh();
  }

  endmenuloop:
  return 0;
}

int settings_menu() {
    int set_choices = sizeof(settings_options) / sizeof(char*);
  int s_highlight = 1;
  int c;
  
  // Mod Menu
          clear();
          
          mvprintw(2, 2, "Use arrow keys to navigate, press Enter to select:");
          for (int i = 0; i < set_choices; i++) {
            if (i == s_highlight - 1) {
              attron(A_REVERSE);
            }
            mvprintw(4 + i, 2, "%s", settings_options[i]);
            if (i == s_highlight - 1) {
              attroff(A_REVERSE);
            }
          }
          refresh();
        
          while(1) {
            c = getch();
            switch(c) {
              case KEY_UP:
                if (s_highlight > 1) {
                  s_highlight--;
                }
                break;
              case KEY_DOWN:
                if (s_highlight < set_choices) {
                  s_highlight++;
                }
                break;
              case '\n':
                if(s_highlight == 1) {
                  break;
                } else if(s_highlight == 2) {
                  // Break out to Main menu again ig
                  // might have to make this its own method I think it would be easier
                  return 0;
                }
              default:
                break;
          }
            mvprintw(2, 2, "Use arrow keys to navigate, press Enter to select:");
          for (int i = 0; i < set_choices; i++) {
            if (i == s_highlight - 1) {
              attron(A_REVERSE);
            }
            mvprintw(4 + i, 2, "%s", settings_options[i]);
            if (i == s_highlight - 1) {
              attroff(A_REVERSE);
            }
          }
          refresh();
          }
}

int mod_menu() {
    int mod_choices = sizeof(mod_options) / sizeof(char*);
  int m_highlight = 1;
  int c;
  
  // Mod Menu
          clear();
          
          mvprintw(2, 2, "Use arrow keys to navigate, press Enter to select:");
          for (int i = 0; i < mod_choices; i++) {
            if (i == m_highlight - 1) {
              attron(A_REVERSE);
            }
            mvprintw(4 + i, 2, "%s", mod_options[i]);
            if (i == m_highlight - 1) {
              attroff(A_REVERSE);
            }
          }
          refresh();
        
          while(1) {
            c = getch();
            switch(c) {
              case KEY_UP:
                if (m_highlight > 1) {
                  m_highlight--;
                }
                break;
              case KEY_DOWN:
                if (m_highlight < mod_choices) {
                  m_highlight++;
                }
                break;
              case '\n':
                if(m_highlight == 1) {
                  // Installed Mods
                  view_mods();
                } else if(m_highlight == 2) {
                  
                } else if(m_highlight == 4) {
                  // Back
                  return 0;
                }
              default:
                break;
          }
            mvprintw(2, 2, "Use arrow keys to navigate, press Enter to select:");
          for (int i = 0; i < mod_choices; i++) {
            if (i == m_highlight - 1) {
              attron(A_REVERSE);
            }
            mvprintw(4 + i, 2, "%s", mod_options[i]);
            if (i == m_highlight - 1) {
              attroff(A_REVERSE);
            }
          }
          refresh();
          }
}


int game_menu(){
  int set_choices = sizeof(game_options) / sizeof(char*);
  int s_highlight = 1;
  int c;

  // I feel like you should maybe  (maybe)
          clear();
          
          mvprintw(2, 2, "Use arrow keys to navigate, press Enter to select:");
          for (int i = 0; i < set_choices; i++) {
            if (i == s_highlight - 1) {
              attron(A_REVERSE);
            }
            mvprintw(4 + i, 2, "%s", game_options[i]);
            if (i == s_highlight - 1) {
              attroff(A_REVERSE);
            }
          }
          refresh();
        
          while(1) {
            c = getch();
            switch(c) {
              case KEY_UP:
                if (s_highlight > 1) {
                  s_highlight--;
                }
                break;
              case KEY_DOWN:
                if (s_highlight < set_choices) {
                  s_highlight++;
                }
                break;
              case '\n':
                if(s_highlight == 1) {
                  system("clear");
                  endwin();
                  Game game("game/basegame/info.json","game/config.json");
                } else if(s_highlight == 4) {
                  return 0;
                }
              default:
                break;
          }
            
            mvprintw(2, 2, "Use arrow keys to navigate, press Enter to select:");
          for (int i = 0; i < set_choices; i++) {
            if (i == s_highlight - 1) {
              attron(A_REVERSE);
            }
            mvprintw(4 + i, 2, "%s", game_options[i]);
            if (i == s_highlight - 1) {
              attroff(A_REVERSE);
            }
          }
          refresh();
          }
}

int game_settings() {
  // TODO: Make menu to decide settings world name that type of stuff
  // Maybe the mods 
  return 0;
}



int view_mods() {
  std::vector<std::string> folderNames;

    //definetly not taken from stack overflow
    for (const auto& entry : std::filesystem::directory_iterator("../game/mods")) {
        if (entry.is_directory()) {
            std::filesystem::path infoFilePath = entry.path() / "info.json";
            if (std::filesystem::exists(infoFilePath)) {
                folderNames.push_back(entry.path().filename().string());
            }
        }
    }

    int highlight = 1;
    int choice;
    bool done = false;
    while (!done) {
        clear();
        mvprintw(0, 0, "Select a mod:");
        for (int i = 0; i < folderNames.size(); i++) {
            if (i+1 == highlight) {
                attron(A_REVERSE);
            }
            mvprintw(i+2, 0, "%s", folderNames[i].c_str());
            if (i+1 == highlight) {
                attroff(A_REVERSE);
            }
        }
        refresh();
        choice = getch();
        switch(choice) {
            case KEY_UP:
                if (highlight > 1) {
                    highlight--;
                }
                break;
            case KEY_DOWN:
                if (highlight < folderNames.size()) {
                    highlight++;
                }
                break;
            case '\n':
                clear();
                std::string selectedMod = folderNames[highlight-1];
                std::string infoFilePath = "game/mods/" + selectedMod + "/info.json";
                std::string modName = readJSON(infoFilePath);
                // idk 
                
                done = true;
                break;
            //case 'q':
            //    done = true;
            //    break;
            
          // default:
          //       break;
        }
    }

    endwin();
    return 0;
}


std::string readJSON(std::string filename) {
    std::ifstream f(filename, std::ifstream::binary);
    if (!f.good()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    Json::Value v;
    Json::CharReaderBuilder builder;
    builder["collectComments"] = false; // ignore comments in JSON file
    std::string errs;

    bool parsingSuccessful = Json::parseFromStream(builder, f, &v, &errs);
    if (!parsingSuccessful) {
        std::cerr << "Error: Failed to parse JSON file " << filename << std::endl;
        std::cerr << "Parsing errors: " << errs << std::endl;
        exit(EXIT_FAILURE);
    }

    return v["Name"].asString();
}