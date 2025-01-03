#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>   // For the key events to move about the window
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

/* Defining the color palette of Catppuccin Mocha theme
   I only used three principal colors about this program */
#define TEXT 0xcdd6f4               // Text
#define BACKGROUND 0x1e1e1e         // Base
#define BACKGROUND_HL 0xcba6f7      // Mauve

/* Main option selector used by the main container option
   the window generated after press the Win + P keybing */
#define FONT_FAMILY "fixed"
#define CONTAINER_WIDTH 1000        // Total width container
#define CONTAINER_HEIGHT 200        // Total height container
#define MAIN_OPTIONS 2              // To set the length array

int menu_option = 0;                // Counter to select the option
const char *modes[MAIN_OPTIONS] = {"Screens", "Audio"}; // Options to config

/* Screen mode selector options used by the screen mode selector
   define your xrandr monitors and the dimensions about this window */
#define PRIMARY_MONITOR "eDP"       // My laptop monitor output
#define SECOND_MONITOR "HDMI-A-0"   // My HDMI name output
#define SCREEN_WIDTH 1002           // Width of the window (sum 3 for a complete area)
#define SCREEN_OPTIONS 3            // In this case we configure left, mirror or right position

int screen_option = 0;              // Counter
const char *screen_modes[SCREEN_OPTIONS] = {"Left", "Mirror", "Right"};


/* Audio media output, see your output names with the command
   pactl list sinks short*/
#define LAPTOP_AUDIO "alsa_output.pci-0000_04_00.6.analog-stereo"
#define HDMI_AUDIO "alsa_output.pci-0000_04_00.1.hdmi-stereo"
#define AUDIO_WIDTH 1000           // Width of the window
#define AUDIO_OPTIONS 2            // In this case we configure laptop and hdmi output

int audio_option = 0;              // Counter
const char *audio_modes[AUDIO_OPTIONS] = {"LAPTOP", "HDMI"};


// Draw menu options select -> define function
void draw_menu(Display *display, Window window, GC gc, XFontStruct *font,
               int window_width, int options_length, const char *mode[], int selected_option) {

  XClearWindow(display, window);

  int section_width = window_width / options_length;    // Equal width for each section

  for (int i = 0; i < options_length; i++) {            // Iterate over each option

    int rect_x = i * section_width;                     // Start x-coordinate

    // Highlight the selected option
    if (i == selected_option) {
      XSetForeground(display, gc, BACKGROUND_HL);     // Background color
      XFillRectangle(display, window, gc,
          rect_x, 0,                                  // Begin <x,y> coords
          section_width, CONTAINER_HEIGHT);           // Setting <x,y> dims
      XSetForeground(display, gc, BACKGROUND);        // Text color of background
    
    } else {
      XSetForeground(display, gc, TEXT);
      XDrawRectangle(display, window, gc,
          rect_x, 0,                                     // Begin <x,y> coords
          section_width, CONTAINER_HEIGHT);              // Setting <x,y> dims
    }

    // Draw text centered inside the rectangle
    int text_width = XTextWidth(font, mode[i], strlen(mode[i]));
    int text_x = rect_x + (section_width - text_width) / 2;
    int text_y = 0 + (CONTAINER_HEIGHT + font->ascent) / 2;

    XDrawString(display, window, gc,        
        text_x, text_y,                             // Setting <x,y> coords
        mode[i], strlen(mode[i]));                  // Setting text to draw
  }
}


char* get_resolution() {
    FILE *fp;
    static char resolution[50]; // Static so it persists after returning

    // Execute the command and open a pipe to read its output
    fp = popen("xrandr --query | grep -A1 \"^HDMI-A-0 \" | tail -n1 | awk '{print $1}'", "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(EXIT_FAILURE);
    }

    // Read the command output into the buffer
    if (fgets(resolution, sizeof(resolution), fp) == NULL) {
        perror("Failed to read resolution");
        pclose(fp);
        exit(EXIT_FAILURE);
    }

    // Close the pipe
    pclose(fp);

    // Remove the newline character if present
    resolution[strcspn(resolution, "\n")] = '\0';

    return resolution;
}

void set_screen(int select_option) {
    const char* resolution = get_resolution();
    char command[500];
 
    printf("Monitor option %i\n", select_option);
    switch (select_option) {
        // Setting the external monitor like a mirror of principal monitor
        case 1:
            snprintf(command, sizeof(command),
                     "xrandr --output %s --off & xrandr --output %s --mode %s --scale-from 1366x768 --same-as %s",
                     SECOND_MONITOR, SECOND_MONITOR, resolution, PRIMARY_MONITOR);
            system(command);
            system("notify-send SCREEN " SECOND_MONITOR " mirror shared");
            break;

        // Setting the principal monitor at left of other monitor
        case 0:
            snprintf(command, sizeof(command),
                     "xrandr --output %s --off & xrandr --output %s --mode %s --left-of %s",
                    SECOND_MONITOR, SECOND_MONITOR, resolution, PRIMARY_MONITOR);
            system(command);
            break;

        // Setting the principal monitor at right of other monitor
        case 2:
            snprintf(command, sizeof(command),
                     "xrandr --output %s --off & xrandr  --output %s --mode %s --right-of %s",
                     SECOND_MONITOR, SECOND_MONITOR, resolution, PRIMARY_MONITOR);
            system(command);
            break;

        default:
            printf("Invalid option selected screen\n");
            break;
    }
}

void set_audio(int select_option) {
    char command[500];
 
    printf("Monitor option %i\n", select_option);
    switch (select_option) {
        // Setting the external monitor like a mirror of principal monitor
        case 0:
            snprintf(command, sizeof(command),
                     "pactl set-default-sink %s",
                     LAPTOP_AUDIO);
            system(command);
            break;

        // Setting the external monitor like a mirror of principal monitor
        case 1:
            snprintf(command, sizeof(command),
                     "pactl set-default-sink %s",
                     HDMI_AUDIO);
            system(command);
            break;

        default:
            printf("Invalid option selected screen\n");
            break;
    }
}


int audio_modes_draw() {

  Display *display;
  Window window;
  int screen;
  GC gc;
  XEvent event;
  XFontStruct *font;

  // Open connection to X server
  display = XOpenDisplay(NULL);
  if (!display) {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  screen = DefaultScreen(display);

  // Create a simple window
  window = XCreateSimpleWindow(
      display, RootWindow(display, screen),
      (DisplayWidth(display, screen) - CONTAINER_WIDTH) / 2,
      (DisplayHeight(display, screen) - CONTAINER_HEIGHT) / 2,
      CONTAINER_WIDTH, CONTAINER_HEIGHT, 0,
      BACKGROUND,
      BACKGROUND
      );

  // Set window properties
  Atom wm_type = XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
  Atom wm_dialog = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
  Atom atom_type = XInternAtom(display, "ATOM", False);

  XChangeProperty(display, window, wm_type, atom_type, 32, PropModeReplace, (unsigned char *)&wm_dialog, 1);

  Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
  Atom wm_state_above = XInternAtom(display, "_NET_WM_STATE_ABOVE", False);
  XChangeProperty(display, window, wm_state, atom_type, 32, PropModeReplace, (unsigned char *)&wm_state_above, 1);

  XSizeHints *size_hints = XAllocSizeHints();
  size_hints->flags = PMinSize | PMaxSize;
  size_hints->min_width = CONTAINER_WIDTH;
  size_hints->min_height = CONTAINER_HEIGHT;
  size_hints->max_width = CONTAINER_WIDTH;
  size_hints->max_height = CONTAINER_HEIGHT;
  XSetWMNormalHints(display, window, size_hints);
  XFree(size_hints);

  XSelectInput(display, window, ExposureMask | KeyPressMask);

  XMapWindow(display, window);

  // Create Graphics Context
  gc = XCreateGC(display, window, 0, NULL);
  XSetForeground(display, gc, BlackPixel(display, screen));

  font = XLoadQueryFont(display, FONT_FAMILY);
  if (!font) {
    fprintf(stderr, "Failed to load font.\n");
    exit(1);
  }
  XSetFont(display, gc, font->fid);

    // Event loop
  while (1) {
    XNextEvent(display, &event);

    if (event.type == Expose) {
      draw_menu(display, window, gc, font, AUDIO_WIDTH, AUDIO_OPTIONS, audio_modes, audio_option);
    }

    if (event.type == KeyPress) {
      KeySym key = XLookupKeysym(&event.xkey, 0);

      switch (key) {
        case XK_Left:
          if (audio_option > 0) {
            audio_option--;
            draw_menu(display, window, gc, font, AUDIO_WIDTH, AUDIO_OPTIONS, audio_modes, audio_option);
          }
          break;

        case XK_Right:
          if (audio_option < AUDIO_OPTIONS - 1) {
            audio_option++;
            draw_menu(display, window, gc, font, AUDIO_WIDTH, AUDIO_OPTIONS, audio_modes, audio_option);
          }
          break;

        case XK_Return:
          set_audio(audio_option);
          break;

        case XK_Escape:
          goto cleanup;
    }
  }

  }

cleanup:
    XFreeFont(display, font);
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}



int screen_modes_draw() {

  Display *display;
  Window window;
  int screen;
  GC gc;
  XEvent event;
  XFontStruct *font;

  // Open connection to X server
  display = XOpenDisplay(NULL);
  if (!display) {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  screen = DefaultScreen(display);

  // Create a simple window
  window = XCreateSimpleWindow(
      display, RootWindow(display, screen),
      (DisplayWidth(display, screen) - CONTAINER_WIDTH) / 2,
      (DisplayHeight(display, screen) - CONTAINER_HEIGHT) / 2,
      CONTAINER_WIDTH, CONTAINER_HEIGHT, 0,
      BACKGROUND,
      BACKGROUND
      );

  // Set window properties
  Atom wm_type = XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
  Atom wm_dialog = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
  Atom atom_type = XInternAtom(display, "ATOM", False);

  XChangeProperty(display, window, wm_type, atom_type, 32, PropModeReplace, (unsigned char *)&wm_dialog, 1);

  Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
  Atom wm_state_above = XInternAtom(display, "_NET_WM_STATE_ABOVE", False);
  XChangeProperty(display, window, wm_state, atom_type, 32, PropModeReplace, (unsigned char *)&wm_state_above, 1);

  XSizeHints *size_hints = XAllocSizeHints();
  size_hints->flags = PMinSize | PMaxSize;
  size_hints->min_width = CONTAINER_WIDTH;
  size_hints->min_height = CONTAINER_HEIGHT;
  size_hints->max_width = CONTAINER_WIDTH;
  size_hints->max_height = CONTAINER_HEIGHT;
  XSetWMNormalHints(display, window, size_hints);
  XFree(size_hints);

  XSelectInput(display, window, ExposureMask | KeyPressMask);

  XMapWindow(display, window);

  // Create Graphics Context
  gc = XCreateGC(display, window, 0, NULL);
  XSetForeground(display, gc, BlackPixel(display, screen));

  font = XLoadQueryFont(display, FONT_FAMILY);
  if (!font) {
    fprintf(stderr, "Failed to load font.\n");
    exit(1);
  }
  XSetFont(display, gc, font->fid);

    // Event loop
  while (1) {
    XNextEvent(display, &event);

    if (event.type == Expose) {
      draw_menu(display, window, gc, font, SCREEN_WIDTH, SCREEN_OPTIONS, screen_modes, screen_option);
    }

    if (event.type == KeyPress) {
      KeySym key = XLookupKeysym(&event.xkey, 0);

      switch (key) {
        case XK_Left:
          if (screen_option > 0) {
            screen_option--;
            draw_menu(display, window, gc, font, SCREEN_WIDTH, SCREEN_OPTIONS, screen_modes, screen_option);
          }
          break;

        case XK_Right:
          if (screen_option < SCREEN_OPTIONS - 1) {
            screen_option++;
            draw_menu(display, window, gc, font, SCREEN_WIDTH, SCREEN_OPTIONS, screen_modes, screen_option);
          }
          break;

        case XK_Return:
          set_screen(screen_option);
          break;

        case XK_Escape:
          goto cleanup;
    }
  }

  }

cleanup:
    XFreeFont(display, font);
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}










// Main function initializer
int main() {
  Display *display;
  Window window;
  int screen;
  GC gc;
  XEvent event;
  XFontStruct *font;

  // Open connection to X server
  display = XOpenDisplay(NULL);
  if (!display) {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  screen = DefaultScreen(display);

  // Create a simple window
  window = XCreateSimpleWindow(
      display, RootWindow(display, screen),
      (DisplayWidth(display, screen) - CONTAINER_WIDTH) / 2,
      (DisplayHeight(display, screen) - CONTAINER_HEIGHT) / 2,
      CONTAINER_WIDTH, CONTAINER_HEIGHT, 0,
      BACKGROUND,
      BACKGROUND
      );

  // Set window properties
  Atom wm_type = XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
  Atom wm_dialog = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
  Atom atom_type = XInternAtom(display, "ATOM", False);

  XChangeProperty(display, window, wm_type, atom_type, 32, PropModeReplace, (unsigned char *)&wm_dialog, 1);

  Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
  Atom wm_state_above = XInternAtom(display, "_NET_WM_STATE_ABOVE", False);
  XChangeProperty(display, window, wm_state, atom_type, 32, PropModeReplace, (unsigned char *)&wm_state_above, 1);

  XSizeHints *size_hints = XAllocSizeHints();
  size_hints->flags = PMinSize | PMaxSize;
  size_hints->min_width = CONTAINER_WIDTH;
  size_hints->min_height = CONTAINER_HEIGHT;
  size_hints->max_width = CONTAINER_WIDTH;
  size_hints->max_height = CONTAINER_HEIGHT;
  XSetWMNormalHints(display, window, size_hints);
  XFree(size_hints);

  XSelectInput(display, window, ExposureMask | KeyPressMask);

  XMapWindow(display, window);

  // Create Graphics Context
  gc = XCreateGC(display, window, 0, NULL);
  XSetForeground(display, gc, BlackPixel(display, screen));

  font = XLoadQueryFont(display, FONT_FAMILY);
  if (!font) {
    fprintf(stderr, "Failed to load font.\n");
    exit(1);
  }
  XSetFont(display, gc, font->fid);

  // Event loop
  while (1) {
    XNextEvent(display, &event);

    if (event.type == Expose) {
      draw_menu(display, window, gc, font, CONTAINER_WIDTH, MAIN_OPTIONS, modes, menu_option);
    }
    
    // When the user presses a key
    if (event.type == KeyPress) {

      KeySym key = XLookupKeysym(&event.xkey, 0); // Capture the key code pressed

      switch (key) {
        case XK_Left:
          if (menu_option > 0) {
            menu_option--;
            draw_menu(display, window, gc, font, CONTAINER_WIDTH, MAIN_OPTIONS, modes, menu_option);
          }
          break;

        case XK_Right:
          if (menu_option < MAIN_OPTIONS - 1) {
            menu_option++;
            draw_menu(display, window, gc, font, CONTAINER_WIDTH, MAIN_OPTIONS, modes, menu_option);
          }
          break;

        case XK_Return:
          if (strcmp(modes[menu_option], "Screens") == 0) {
            screen_modes_draw();
          } 
          else if (strcmp(modes[menu_option], "Audio") == 0) {
            audio_modes_draw();
          }
          break;

        case XK_Escape:
          goto cleanup;
      }
    }
  }

cleanup:
    XFreeFont(display, font);
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}

