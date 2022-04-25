#ifndef CONSOLE_H
#define CONSOLE_H

#include <windows.h>

namespace game {
   // clear screen, move a cursor to (0,0)
   void Clear(void);

   // change cursor's position
   void GotoXY(int _x, int _y);

   // set title to a console 
   void SetTitle(const char* _szConsoleName);

   // set colors of background and text
   void SetColor(unsigned char _BgColor, unsigned char _TextColor);

   // make a cursor visible or not
   void SetCursor(BOOL _bShow);

   // set console size
   void SetConsoleSize(int _col, int _lines);
}


#endif // !CONSOLE_H

