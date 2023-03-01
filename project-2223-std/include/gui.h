#ifndef GUI_H
#define GUI_H

/**
 * @brief Close the GUI window.
 *
 */
void GUI_close();

/**
 * @brief Initialize the GUI windows.
 *
 * The width and height of the window are specified in number of cells.
 * `ICON_SIZE` is a constant determining the size in pixel of an icon.
 *
 * @param title  a string representing the title of the window
 *
 * @param width  the width of the window (number of cells)
 *
 * @param height the height of the window (number of cells)
 */
void GUI_init(char *title, int width, int height);

/**
 * @brief Display a Sokoban level.
 *
 * @param width  the number of columns in the game
 *
 * @param height the number of rows in the game
 *
 * @param level  a "matrix" of `char` representing the level.
 *               Each `char` represents a symbol as defined in
 *               the `symbols` array
 */
void GUI_show(int width, int height, char level[height][width]);

/**
 * @brief Get the key pressed by the user
 *
 * @return a char representing the key pressed by the user
 */
int GUI_get_key();

/**
 * @brief Wait for a mouse click on the window
 *
 */
void GUI_wait_click();

/**
 * @brief Wait for time ms.
 *
 * @param time the time to wait (in ms)
 *
 */
void GUI_pause(int time);

#endif
