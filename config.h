/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Fira Mono:size=10" };
static const char dmenufont[]       = "Fira Mono:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_green[]        = "#95E454";
static const char col_red[]         = "#E5786D";
static const char col_yellow[]      = "#F0DFAF";
static const char col_blue[]        = "#9AB8D7";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray1, col_blue,  col_blue  },
	[SchemeBat]  = { col_gray1, col_red,   col_red   },
	[SchemeChr]  = { col_gray1, col_yellow,col_yellow},
	[SchemeFull] = { col_gray1, col_green, col_green },
};

/* Battery settings. Sets up battery monitoring things. */
#define LOW_BATTERY_LEVEL 20

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "s" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define XF86AudioRaiseVolume  0x1008ff13
#define XF86AudioLowerVolume  0x1008ff11
#define XF86AudioMute         0x1008ff12
#define XF86AudioPlay         0x1008ff14
#define XF86AudioStop         0x1008ff15
#define XF86AudioPrev         0x1008ff16
#define XF86AudioNext         0x1008ff17
#define XF86MonBrightnessUp   0x1008ff02
#define XF86MonBrightnessDown 0x1008ff03

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_green, "-sf", col_gray1, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *surfcmd[]  = { "surf", "ddg.gg", NULL };
static const char *ffxcmd[]   = { "firefox", NULL };
static const char *emacscmd[] = { "emacsclient", "-c", NULL };
static const char *randrcmd[] = { "arandr", NULL };

/* WM tools spawn arrays */
static const char *brightup[] = { "xbacklight", "+5", NULL };
static const char *brightdn[] = { "xbacklight", "-5", NULL };

static const char *volup[]    = { "amixer", "sset", "Master", "5%+", NULL };
static const char *voldn[]    = { "amixer", "sset", "Master", "5%-", NULL };
static const char *voloff[]   = { "amixer", "set", "Master", "toggle", NULL };

static const char *lockscrn[] = { "screenlock.sh", "-n", NULL };

static const char *mediafwd[] = { "mpc", "next", NULL};
static const char *mediabk[]  = { "mpc", "prev", NULL};
static const char *mediatgl[] = { "mpc", "toggle", NULL};
static const char *mediastp[] = { "mpc", "stop", NULL};

static const char *setwallp[] = { "feh", "--randomize", "--bg-fill", "/usr/share/backgrounds/custom", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	/* SPAWNS SECTION---------------------------------------------------*/
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = ffxcmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = surfcmd } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = emacscmd } },
	/* WM TOOL SECTION--------------------------------------------------*/
	{ 0,                 XF86AudioRaiseVolume, spawn,          {.v = volup} },
	{ 0,                 XF86AudioLowerVolume, spawn,          {.v = voldn} },
	{ 0,                 XF86AudioMute,        spawn,          {.v = voloff} },
	{ 0,                 XF86AudioPrev,        spawn,          {.v = mediabk} },
	{ 0,                 XF86AudioNext,        spawn,          {.v = mediafwd} },
	{ 0,                 XF86AudioPlay,        spawn,          {.v = mediatgl} },
	{ 0,                 XF86AudioStop,        spawn,          {.v = mediastp} },
	{ 0,                 XF86MonBrightnessUp,  spawn,          {.v = brightup} },
	{ 0,                 XF86MonBrightnessDown,spawn,          {.v = brightdn} },
	/*{ 0,                 XF86Display,          spawn,          {.v = randrcmd} },*/
	{ MODKEY,                       XK_p,      spawn,          {.v = randrcmd} },
	{ MODKEY|ShiftMask,             XK_i,      spawn,          {.v = lockscrn} },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = setwallp} },
	/* WM ACTION SECTION------------------------------------------------*/
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	/* TAG KEYS SECTION-------------------------------------------------*/
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	TAGKEYS(                        XK_BackSpace,              10)
	/* THE HOLY QUIT KEY-----------------------------------------------*/
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

