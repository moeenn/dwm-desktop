// appearance
static const char *fonts[]					= { "Cascadia Code:size=9" };
static const char dmenufont[]				= "Cascadia Code:size=9";
static const unsigned int borderpx			= 1;
static const char col_gray1[]				= "#0c0f13";
static const char col_gray2[]				= "#16181b";
static const char col_gray3[]				= "#b8b8b0";
static const char col_gray4[]				= "#dddddd";
static const char col_cyan[]				= "#006c98";
static const char *colors[][3]				= {
	//				fg				bg				border
	[SchemeNorm] = { col_gray3, 	col_gray1, 		col_gray2 },
	[SchemeSel]  = { col_gray4, 	col_cyan,  		col_cyan },
};

// system tray
static const int showsystray				= 1;				// 0 means no systray
static const unsigned int systraypinning	= 0;				// 0: sloppy systray follows selected monitor
static const unsigned int systrayspacing	= 2;				// systray spacing
static const int systraypinningfailfirst	= 1;				// 1: if pinning fails, display systray on the first monitor

// window buttons i.e. tab bar
//  Display modes of the tab bar: never shown, always shown, shown only in
//  monocle mode in the presence of several windows.
//  Modes after showtab_nmodes are disabled.
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab					= showtab_always;
static const int toptab						= False;
static const unsigned int tabpadding 		= 10;

// other settings
static const unsigned int snap				= 5;				// snap to screen edge pixels
static const int showbar					= 1;				// 0 means no bar
static const int barpadding					= 12;				// bar vertical padding
static const int topbar						= 1;				// 0 means bottom bar

// tags
static const char *tags[] = { " 01 ", " 02 ", " 03 ", " 04 ", " 05 ", " 06 ", " 07 ", " 08 " };

static const Rule rules[] = {
	// class 		instance	title		tags mask	isfloating	monitor
	{ "Gimp",		NULL,		NULL,		0,			1,			-1 },
	{ "Firefox",	NULL,		NULL,		1 << 8,		0,			-1 },
};

// layouts
static const float mfact		= 0.55;			// master area width
static const int nmaster		= 1;			// number of clients in master area
static const int resizehints	= 0;			// 1 means respect size proportion in resizals

static const Layout layouts[] = {
	// symbol		layout function
	{ "[|]",		monocle },		// default
	{ "[=]",		tile },			// tiling mode
	{ "[~]",		NULL },			// null means floating mode
};

// key definitions (Octal values are keysyms. Find using xev)
#define MODKEY 			Mod1Mask
#define WINKEY 			Mod4Mask
// #define RaiseVolume		0x1008ff13
// #define LowerVolume		0x1008ff11
// #define AudioMute		0x1008ff12
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,						KEY,	view,			{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,			KEY,	toggleview,		{.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,				KEY,	tag,			{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask,	KEY,	toggletag,		{.ui = 1 << TAG} },

// helper for spawning shell commands in the pre dwm-5.0 fashion
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

// commands
static char dmenumon[2] 		= "0";
static const char *dmenucmd[]	= { "dmenu_run", "-fn", dmenufont, "-h", "27",
									"-nb", col_gray1, "-nf", col_gray3,
									"-sb", col_cyan, "-sf", col_gray4, NULL };

static const char *termcmd[]	= { "st", NULL };
static const char *filecmd[] 	= { "thunar", NULL };
static const char *lock[]		= { "i3lock", "-c", "000000", NULL };
// static const char *startmenu[]	= { "dmenu_startmenu", NULL };

// volume commands
// static const char *volup[]		= { "dzvol", "-i", "5", "-b", col_gray1,
// 									"-f", col_cyan, "-z", col_gray4, "-m",
// 									col_gray4, NULL };

// static const char *voldown[]	= { "dzvol", "-d", "5", "-b", col_gray1,
// 									"-f", col_cyan, "-z", col_gray4, "-m",
// 									col_gray4, NULL };

// static const char *voltoggle[]	= { "dzvol", "-t", "toggle", "-b", col_gray1,
// 									"-f", col_cyan, "-z", col_gray4, "-m",
// 									col_gray4, NULL };

static Key keys[] = {
	// modifier				key				function		argument
	{ MODKEY,				XK_p,			spawn,			{.v = dmenucmd } },
	{ WINKEY,				XK_t,			spawn,			{.v = termcmd } },
	{ WINKEY,				XK_e,			spawn,			{.v = filecmd } },
	{ WINKEY,				XK_l,			spawn,			{.v = lock } },
	// { 0,					XK_F1,			spawn,			{.v = startmenu } },
	// { 0,					RaiseVolume,	spawn,			{.v = volup } },
	// { 0,					LowerVolume,	spawn,			{.v = voldown } },
	// { 0,					AudioMute,		spawn,			{.v = voltoggle } },
	{ MODKEY,				XK_b,			togglebar,		{0} },
//	{ MODKEY,				XK_w,			tabmode,		{-1} },
	{ MODKEY,				XK_Tab,			focusstack,		{.i = +1 } },
//	{ MODKEY|ShiftMask,		XK_Tab,			focusstack,		{.i = -1 } },
	{ MODKEY,				XK_equal,		incnmaster,		{.i = +1 } },
	{ MODKEY,				XK_minus,		incnmaster,		{.i = -1 } },
	{ MODKEY,				XK_h,			setmfact,		{.f = -0.01} },
	{ MODKEY,				XK_l,			setmfact,		{.f = +0.01} },
	{ MODKEY,				XK_Return,		zoom,			{0} },
//	{ MODKEY,				XK_Tab,			view,			{0} },
	{ MODKEY,				XK_F4,			killclient,		{0} },
	{ MODKEY,				XK_m,			setlayout,		{.v = &layouts[0]} },
	{ MODKEY,				XK_t,			setlayout,		{.v = &layouts[1]} },
	{ MODKEY,				XK_f,			setlayout,		{.v = &layouts[2]} },
//	{ MODKEY,				XK_space,		setlayout,		{0} },
	{ MODKEY,				XK_space,		togglefloating,	{0} },
//	{ MODKEY,				XK_0,			view,			{.ui = ~0 } },
//	{ MODKEY|ShiftMask,		XK_0,			tag,			{.ui = ~0 } },
//	{ MODKEY,				XK_comma,		focusmon,		{.i = -1 } },
//	{ MODKEY,				XK_period,		focusmon,		{.i = +1 } },
//	{ MODKEY|ShiftMask,		XK_comma,		tagmon,			{.i = -1 } },
//	{ MODKEY|ShiftMask,		XK_period,		tagmon,			{.i = +1 } },
	{ MODKEY|ControlMask,	XK_Left,   		viewtoleft,     {0} },
	{ MODKEY|ControlMask,	XK_Right,  		viewtoright,    {0} },
	{ MODKEY|ShiftMask,     XK_Left,   		tagtoleft,      {0} },
	{ MODKEY|ShiftMask,     XK_Right,  		tagtoright,     {0} },
	TAGKEYS(				XK_1,			0)
	TAGKEYS(				XK_2,			1)
	TAGKEYS(				XK_3,			2)
	TAGKEYS(				XK_4,			3)
	TAGKEYS(				XK_5,			4)
	TAGKEYS(				XK_6,			5)
	TAGKEYS(				XK_7,			6)
	TAGKEYS(				XK_8,			7)
	{ MODKEY|ShiftMask,		XK_q,			quit,			{0} },
};

// button definitions
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
	{ ClkTabBar,			0,				Button1,		focuswin,		{0} },
};