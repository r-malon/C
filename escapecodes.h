/*
ANSI escape codes wrapped in macros
The most useful are the CSI sequences
Original: https://github.com/fabriciopashaj/c-ansi-sequences
*/
#ifndef ESCAPECODES_H
#define ESCAPECODES_H

#include "control_codes.h"

/* Select Graphic Rendition */
#define SGR_SEQ(s) CSI s "m"
#define SGR_RESET CSI "0m"

#define BUF_MAIN	CSI "?1049l"
#define BUF_ALT		CSI "?1049h"	/* Switch to a new screen buffer */

/* Only '0' and 'B' work in Windows */
#define CHRSET(s)		ESC "(" #s	/* '0' is DEC Line Drawing mode */
#define CHRSET_DEFAULT	ESC "(B"	/* 'B' is US-ASCII */

/* Cursor */
#define CUR_HOME         CSI "H"
#define CUR_SET(n, m)    CSI #n ";" #m "H"
#define DYN_CUR_SET      CUR_SET(%d, %d)
#define CUR_UP(n)        CSI #n "A"
#define DYN_CUR_UP       CUR_UP(%d)
#define CUR_DOWN(n)      CSI #n "B"
#define DYN_CUR_DOWN     CUR_DOWN(%d)
#define CUR_RIGHT(n)     CSI #n "C"
#define DYN_CUR_RIGHT    CUR_RIGHT(%d)
#define CUR_LEFT(n)      CSI #n "D"
#define DYN_CUR_LEFT     CUR_LEFT(%d)
#define CUR_UP_BEG(n)    CSI #n "E"
#define DYN_CUR_UP_BEG   CUR_UP_BEG(%d)
#define CUR_DOWN_BEG(n)  CSI #n "F"
#define DYN_CUR_DOWN_BEG CUR_DOWN_BEG(%d)
#define CUR_SET_COL(n)   CSI #n "G"
#define DYN_CUR_SET_COL  CUR_SET_COL(%d)
#define CUR_REQ_POS      CSI "6n"
#define CUR_MOVE_1UP     ESC "M"
#define CUR_SAVE_DEC     ESC "7"
#define CUR_RESTORE_DEC  ESC "8"
#define CUR_SAVE_SCO     CSI "s"
#define CUR_RESTORE_SCO  CSI "u"
#define CUR_INVIS    CSI "?25l"
#define CUR_VIS      CSI "?25h"
#define CUR_NOBLK    CSI "?12l"
#define CUR_BLK      CSI "?12h"


/* Text colors */
#define FG_BLACK    ";30"
#define FG_RED      ";31"
#define FG_GREEN    ";32"
#define FG_YELLOW   ";33"
#define FG_BLUE     ";34"
#define FG_MAGENTA  ";35"
#define FG_CYAN     ";36"
#define FG_WHITE    ";37"

#define SETFG_BLACK   CSI FG_BLACK   "m"
#define SETFG_RED     CSI FG_RED     "m"
#define SETFG_GREEN   CSI FG_GREEN   "m"
#define SETFG_YELLOW  CSI FG_YELLOW  "m"
#define SETFG_BLUE    CSI FG_BLUE    "m"
#define SETFG_MAGENTA CSI FG_MAGENTA "m"
#define SETFG_CYAN    CSI FG_CYAN    "m"
#define SETFG_WHITE   CSI FG_WHITE   "m"

#define BRIGHT_FG(c)     FG_ ## c ";1"
#define FG256(n)         ";38;5;" #n
#define SETBRIGHT_FG(c)  CSI BRIGHT_FG(c) "m"
#define SETFG256(n)      CSI FG256(n) "m"
#define DYN_BRIGHT_FG    BRIGHT_FG(%d)
#define DYN_FG256        FG256(%d)
#define DYN_SETBRIGHT_FG SETBRIGHT_FG(%d)
#define DYN_SETFG256     SETFG256(%d)

#define FG_RGB(r, g, b)    ";38;2;" #r ";" #g ";" #b
#define SETFG_RGB(r, g, b) CSI FG_RGB(r, g, b) "m"
#define DYN_FG_RGB         FG_RGB(%d, %d, %d)
#define DYN_SETFG_RGB      SETFG_RGB(%d, %d, %d)

#define FG_DEFAULT CSI "39m" /* Reset foreground color only */

/* Background colors */
#define BG_BLACK    ";40"
#define BG_RED      ";41"
#define BG_GREEN    ";42"
#define BG_YELLOW   ";43"
#define BG_BLUE     ";44"
#define BG_MAGENTA  ";45"
#define BG_CYAN     ";46"
#define BG_WHITE    ";47"

#define SETBG_BLACK   CSI BG_BLACK   "m"
#define SETBG_RED     CSI BG_RED     "m"
#define SETBG_GREEN   CSI BG_GREEN   "m"
#define SETBG_YELLOW  CSI BG_YELLOW  "m"
#define SETBG_BLUE    CSI BG_BLUE    "m"
#define SETBG_MAGENTA CSI BG_MAGENTA "m"
#define SETBG_CYAN    CSI BG_CYAN    "m"
#define SETBG_WHITE   CSI BG_WHITE   "m"

#define BRIGHT_BG(c)     BG_ ## c ";1"
#define BG256(n)         ";48;5;" #n
#define SETBRIGHT_BG(c)  CSI BRIGHT_BG(c) "m"
#define SETBG256(n)      CSI BG256(n) "m"
#define DYN_BRIGHT_BG    BRIGHT_BG(%d)
#define DYN_BG256        BG256(%d)
#define DYN_SETBRIGHT_BG SETBRIGHT_BG(%d)
#define DYN_SETBG256     SETBG256(%d)

#define BG_RGB(r, g, b)    ";48;2;" #r ";" #g ";" #b
#define SETBG_RGB(r, g, b) CSI BG_RGB(r, g, b) "m"
#define DYN_BG_RGB         BG_RGB(%d, %d, %d)
#define DYN_SETBG_RGB      SETBG_RGB(%d, %d, %d)

#define BG_DEFAULT CSI "49m" /* Reset background color only */


/* Text styles */
#define TXT_BLD ";1" /* bold */
#define TXT_DIM ";2" /* dim/faint */
#define TXT_ITL ";3" /* italic */
#define TXT_UNL ";4" /* underline */
#define TXT_BLK ";5" /* blinking mode */
#define TXT_REV ";7" /* reversed */
#define TXT_HID ";8" /* hidden/invisible */
#define TXT_STK ";9" /* strikethrough */

#define SETTXT_BLD CSI TXT_BLD "m"
#define SETTXT_DIM CSI TXT_DIM "m"
#define SETTXT_ITL CSI TXT_ITL "m"
#define SETTXT_UNL CSI TXT_UNL "m"
#define SETTXT_BLK CSI TXT_BLK "m"
#define SETTXT_REV CSI TXT_REV "m"
#define SETTXT_HID CSI TXT_HID "m"
#define SETTXT_STK CSI TXT_STK "m"


/* Screen */
#define SCR_CLR2END  CSI "0J" /* Clear to end of screen */
#define SCR_CLR2BEG  CSI "1J" /* Clear to beginning of screen */
#define SCR_CLR_ALL  CSI "2J" /* Clear entire screen */
#define SCR_CLR_SAV  CSI "3J" /* Clear saved lines */
#define SCR_CLR2LEND CSI "0K" /* Clear to end of line */
#define SCR_CLR2LBEG CSI "1K" /* Clear to beginning of line */
#define SCR_CLR_LINE CSI "2K" /* Clear entire line */
#define SCR_RESTORE  CSI "?47l"
#define SCR_SAVE     CSI "?47h"

#endif /* ESCAPECODES_H */
