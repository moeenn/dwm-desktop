static int topbar = 1;
static int fuzzy = 1;
static int centered = 1;
static int min_width = 550;
static const char *fonts[] = {"Fira Sans:size=9"};
static const char *prompt = NULL;
static const char *colors[SchemeLast][2] = {
    /* fg       bg       */
    [SchemeNorm] = {"#eff8f8", "#2d2d2d"},
    [SchemeSel] = {"#eff8f8", "#15539e"},
    [SchemeOut] = {"#1b1b1b", "#1b1b1b"}, // border.
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines = 7;
/* -h option; minimum height of a menu line */
static unsigned int lineheight = 35;
static unsigned int min_lineheight = 10;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
static unsigned int border_width = 1;
