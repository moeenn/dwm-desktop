// appearance
static const char font[]					= "Monospace 8";
static const char normbordercolor[]			= "#444444";
static const char normbgcolor[]				= "#222222";
static const char normfgcolor[]				= "#bbbbbb";
static const char dullfgcolor[]             = "#505050";
static const char selbordercolor[]			= "#005577";
static const char selbgcolor[]				= "#005577";
static const char selfgcolor[]				= "#eeeeee";
static const unsigned int borderpx			= 1;		// border pixel of windows
static const unsigned int snap				= 5;		// snap pixel
static const unsigned int iconmargin		= 7;		// systray icon spacing
static const unsigned int systrayspacing	= 1;		// systray spacing
static const Bool showsystray				= True;		// False means no systray
static const Bool showbar					= True;		// False means no bar
static const Bool topbar					= False;	// False means bottom bar
static const Bool statusmarkup				= True;		// True means use pango markup in status message
static const unsigned int barpadding		= 15;

// tags
static const char *tags[] = { " 01 ", " 02 ", " 03 ", " 04 " };

static const Rule rules[] = {
	// class 		instance 	title 	tags mask 	isfloating	monitor
	{ "Gimp",		NULL,		NULL,	0,			True,		-1 },
	{ "Firefox",	NULL,		NULL,	1 << 8,		False,		-1 },
};

// layouts
static const float mfact		= 0.55;		// factor of master area size [0.05..0.95]
static const int nmaster		= 1;		// number of clients in master area
static const Bool resizehints	= False;	// True means respect size hints in tiled resizals

static const Layout layouts[] = {
	// symbol		arrange function
	{ "[|]",		monocle },	// first entry is default
	{ "[=]",		tile },		// time layout
	{ "[~]",		NULL },		// no layout function means floating behavior
};

// key definitions (Octal values are keysyms. Find using xev)
#define MODKEY Mod1Mask
#define WINKEY Mod4Mask
#define XF86AudioRaiseVolume    0x1008ff13
#define XF86AudioLowerVolume    0x1008ff11
#define XF86AudioMute           0x1008ff12

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,						KEY,	view,			{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,			KEY,	toggleview,		{.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,				KEY,	tag,			{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask,	KEY,	toggletag,		{.ui = 1 << TAG} },

// shell spawn helper
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

// commands
static const char *dmenucmd[]   = { "dmenu_run", "-i", "-fn", "Monospace Bold-8", "-h", "30", "-w", "400", "-l", "6", "-x", "468", "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]    = { "st", NULL };
static const char *filecmd[]    = { "thunar", NULL };
static const char *lock[]       = { "i3lock", "-c", "000000", NULL };
static const char *startmenu[]  = { "dmenu_startmenu", NULL };
static const char *volup[]      = { "dzvol", "-i", "5", "-b", normbgcolor, "-f", selbgcolor, "-z", dullfgcolor, "-m", normfgcolor, NULL };
static const char *voldown[]    = { "dzvol", "-d", "5", "-b", normbgcolor, "-f", selbgcolor, "-z", dullfgcolor, "-m", normfgcolor, NULL };
static const char *voltoggle[]  = { "dzvol", "-t", "toggle", "-b", normbgcolor, "-f", selbgcolor, "-z", dullfgcolor, "-m", normfgcolor, NULL };

static Key keys[] = {
	// modifier						key			function		argument
	{ MODKEY,						XK_p,		spawn,			{.v = dmenucmd } },
	{ WINKEY,						XK_t,		spawn,			{.v = termcmd } },
	{ WINKEY,						XK_e,		spawn,			{.v = filecmd } },
    { WINKEY,						XK_l,		spawn,			{.v = lock } },
    { 0,	    					XK_F1,		spawn,			{.v = startmenu } },
    { 0,						    XF86AudioRaiseVolume,		spawn,			{.v = volup } },
    { 0,						    XF86AudioLowerVolume,		spawn,			{.v = voldown } }, 
    { 0,						    XF86AudioMute,		spawn,			{.v = voltoggle } },   
	{ MODKEY,						XK_b,		togglebar,		{0} },
	{ MODKEY,						XK_Tab,		focusstack,		{.i = +1 } },
	{ MODKEY,						XK_equal,	incnmaster,		{.i = +1 } },
	{ MODKEY,						XK_minus,	incnmaster,		{.i = -1 } },
	{ MODKEY,						XK_h,		setmfact,		{.f = -0.01} },
	{ MODKEY,						XK_l,		setmfact,		{.f = +0.01} },
	{ MODKEY,						XK_Return,	zoom,			{0} },
	{ MODKEY,						XK_F4,		killclient,		{0} },
	{ MODKEY,       				XK_m,		setlayout,		{.v = &layouts[0]} },
	{ MODKEY,       				XK_t,		setlayout,		{.v = &layouts[1]} },
	{ MODKEY,       				XK_f,		setlayout,		{.v = &layouts[2]} },
	{ MODKEY,						XK_space,	setlayout,		{0} },
	{ MODKEY,       				XK_space,	togglefloating,	{0} },
	{ MODKEY,						XK_0,		view,			{.ui = ~0 } },
	{ MODKEY|ShiftMask,				XK_0,		tag,			{.ui = ~0 } },
	{ MODKEY,						XK_comma,	focusmon,		{.i = -1 } },
	{ MODKEY,						XK_period,	focusmon,		{.i = +1 } },
	{ MODKEY|ShiftMask,				XK_comma,	tagmon,			{.i = -1 } },
	{ MODKEY|ShiftMask,				XK_period,	tagmon,			{.i = +1 } },
	TAGKEYS(						XK_1,						0)
	TAGKEYS(						XK_2,						1)
	TAGKEYS(						XK_3,						2)
	TAGKEYS(						XK_4,						3)
	{ MODKEY|ShiftMask,				XK_q,		quit,			{0} },
};

// button definitions
// click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin
static Button buttons[] = {
	// click				event mask		button			function		argument
	{ ClkLtSymbol,			0,				Button1,		setlayout,		{0} },
	{ ClkLtSymbol,			0,				Button3,		setlayout,		{.v = &layouts[2]} },
	{ ClkWinTitle,			0,				Button2,		zoom,			{0} },
	{ ClkStatusText,		0,				Button2,		spawn,			{.v = termcmd } },
	{ ClkClientWin,			MODKEY,			Button1,		movemouse,		{0} },
	{ ClkClientWin,			MODKEY,			Button2,		togglefloating,	{0} },
	{ ClkClientWin,			MODKEY,			Button3,		resizemouse,	{0} },
	{ ClkTagBar,			0,				Button1,		view,			{0} },
	{ ClkTagBar,			0,				Button3,		toggleview,		{0} },
	{ ClkTagBar,			MODKEY,			Button1,		tag,			{0} },
	{ ClkTagBar,			MODKEY,			Button3,		toggletag,		{0} },
};
