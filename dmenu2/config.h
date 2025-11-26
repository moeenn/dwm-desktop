static int topbar = 1;
static int fuzzy = 1;
static int centered = 1;
static int min_width = 550;
static const char* fonts[] = { "Roboto Medium:size=9" };
static const char* prompt = NULL;
static const char* colors[SchemeLast][2] = {
    /* fg       bg       */
    [SchemeNorm] = { "#d8d8d8", "#181818" },
    [SchemeSel] = { "#d8d8d8", "#777777" },
    [SchemeOut] = { "#d8d8d8", "#777777" }, // border.
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
