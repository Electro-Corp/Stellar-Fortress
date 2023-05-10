#include <iostream>
#include <menu.h>
#include <ncurses.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choices[] = {
  "Play Stellar Fortress",
  "Mod Menu",
  "Achievements",
  "Settings"
};

char *game_options[] = {
  "New Game",
  "Load Game",
  "Save Game",
  "Quit Game"
};

char *mod_options[] = {
  "Install Mod", // Does it open mod folder or a dif menu?
  "Uninstall Mod",
  "Back"
};

char *settings_options[] = {
  "Help", // idk placeholder or smthn
  "Back"
};

int settings_menu() {
    int set_choices = sizeof(mod_options) / sizeof(char*);
  int s_highlight = 1;
  int c;
  
  // Mod Menu
          clear();
          
          mvprintw(2, 2, "Use arrow keys to navigate, press Enter to select:");
          for (int i = 0; i < set_choices; i++) {
            if (i == s_highlight - 1) {
              attron(A_REVERSE);
            }
            mvprintw(4 + i, 2, "%s", set_options[i]);
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
                  
                } else if(m_highlight == 2) {
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
            mvprintw(4 + i, 2, "%s", set_options[i]);
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
                  
                } else if(m_highlight == 2) {
                  
                } else if(m_highlight == 3) {
                  // Break out to Main menu again ig
                  // might have to make this its own method I think it would be easier
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
        
        if (highlight == 1) {
          // Stellar Fortress
          // probably creates a new game class or smhtn idk
        } else if (highlight == 2) {
          // Mod Menu
          mod_menu();
        } else if (highlight == 3) {
          // Settings
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

  return 0;
}

