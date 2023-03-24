/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int barpadding					= 23;
static const char *fonts[]          = { "JetBrains Mono:size=10" };
static const char fg_dull[]       	= "#707880";
static const char bg_norm[]       	= "#232323";
static const char fg_norm[]       	= "#F7F7F7";
static const char accent[]       		= "#FDA53B";
static const char bg_sel[]        	= "#303030";
static const char *colors[][3]      = {
	/*               	fg         	bg         	border   */
	[SchemeNorm] 	= { fg_norm,	 	bg_norm, 		bg_norm },
	[SchemeSel]  	= { accent,		 	bg_sel,  		bg_norm },
	[SchemeDull]  = { fg_dull, 		bg_norm, 	 	bg_norm },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gcolor3",  NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "(M)",      monocle },
	{ "(=)",      tile },    /* first entry is default */
	{ "(~)",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod1Mask
#define WINKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "run", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *lockcmd[]  = { "i3lock", "-c", "000000", NULL };
static const char *filecmd[]  = { "thunar", NULL };
static const char *brightupcmd[]  = { "xbacklight", "-inc", "5", NULL };
static const char *brightdowncmd[]  = { "xbacklight", "-dec", "5", NULL };
static const char *killcmd[]  = { "xkill", NULL };
static const char *scrotcmd[]  = { "gnome-screenshot", "-i", NULL };

static const Key keys[] = {
	/* modifier                     key        									function        	argument */
	{ MODKEY,                       XK_p,      									spawn,          	{.v = dmenucmd } },
	{ WINKEY,             					XK_t,      									spawn,          	{.v = termcmd } },
	{ WINKEY,                       XK_e,      									spawn,          	{.v = filecmd } },
	{ WINKEY,                       XK_l,      									spawn,          	{.v = lockcmd } },
	{ 0,                       			XF86XK_MonBrightnessUp,     spawn,          	{.v = brightupcmd } },
	{ 0,                       			XF86XK_MonBrightnessDown,   spawn,          	{.v = brightdowncmd } },
	{ MODKEY|ShiftMask,        			XK_Delete,      						spawn,		      	{.v = killcmd } },
	{ 0,                            XK_Print,     							spawn,	        	{.v = scrotcmd } },
	{ MODKEY,                       XK_b,      									togglebar,      	{0} },
	{ MODKEY,                       XK_Tab,    									focusstack,     	{.i = +1 } },
	{ MODKEY,                       XK_equal,  									incnmaster,     	{.i = +1 } },
	{ MODKEY,                       XK_minus,  									incnmaster,     	{.i = -1 } },
	{ MODKEY,                       XK_h,      									setmfact,       	{.f = -0.03} },
	{ MODKEY,                       XK_l,      									setmfact,       	{.f = +0.03} },
	{ MODKEY,                       XK_Return, 									zoom,           	{0} },
	{ MODKEY,						            XK_F4,     									killclient,     	{0} },
	{ MODKEY|ShiftMask,             XK_m,      									setlayout,      	{.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      									setlayout,      	{.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_f,      									setlayout,      	{.v = &layouts[2]} },
	{ MODKEY,					              XK_space,  									togglefloating, 	{0} },
	{ MODKEY,                       XK_0,      									view,           	{.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      									tag,            	{.ui = ~0 } },
	{ MODKEY,                       XK_comma,  									focusmon,       	{.i = -1 } },
	{ MODKEY,                       XK_period, 									focusmon,       	{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  									tagmon,         	{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 									tagmon,         	{.i = +1 } },
	TAGKEYS(                        XK_1,                      	0)
	TAGKEYS(                        XK_2,                      	1)
	TAGKEYS(                        XK_3,                      	2)
	TAGKEYS(                        XK_4,                      	3)
	TAGKEYS(                        XK_5,                      	4)
	TAGKEYS(                        XK_6,                      	5)
	TAGKEYS(                        XK_7,                      	6)
	TAGKEYS(                        XK_8,                      	7)
	{ MODKEY|ShiftMask,             XK_q,      quit,           	{0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

