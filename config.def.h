/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx        = 0;        /* border pixel of windows */
static const unsigned int snap            = 32;       /* snap pixel */
static const int showbar                  = 1;        /* 0 means no bar */
static const int topbar                   = 1;        /* 0 means bottom bar */
static const char *fonts[]                = { "Fira Code:size=9" };
static const char dmenufont[]             = "Fira Code:size=9";

/* Battery settings. Sets up battery monitoring things. */
#define LOW_BATTERY_LEVEL 20

/* What do we call a window with no name? */
static const char broken[] = "This window has no name.";

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "+", "←" };

static const Rule rules[] =
  {
   /* xprop(1):
    *	WM_CLASS(STRING) = instance, class
    *	WM_NAME(STRING) = title
    */
   /* class      instance    title       tags mask     isfloating   monitor */
   { "Gimp",     NULL,       NULL,       0,            0,           -1 },
   { "Firefox",  NULL,       NULL,       0,            0,           -1 },
   { "keepassxc",NULL,       NULL,       1>>10,        1,           -1 },
  };

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

int hgap = 0;
int vgap = 0;

static const Layout layouts[] =
  {
   /* symbol     arrange function */
   { "M==",      grid },       /* Grid */
   { "MM=",      tile },       /* Stack/master tiling (default) */
   { "???",      NULL },       /* no layout function means floating behavior */
   { "[M]",      monocle },    /* One window at a time */
   { "=M=",      centeredmaster}, /* Like tiled, but master centered */
   { "===",      tricolumn },  /* Tri-column grid */
  };

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)                                                \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_grey1, "-nf", col_grey3, "-sb", col_green, "-sf", col_grey1, NULL };
static const char *termcmd[] = { "st", NULL };

static Key keys[] =
  {
   /* modifier                     key        function        argument */
   /* SPAWNS SECTION---------------------------------------------------*/
   { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
   /* WM ACTION SECTION------------------------------------------------*/
   { MODKEY,                       XK_q,      switchscheme,   {0} },
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
   { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
   { MODKEY,                       XK_z,      setlayout,      {.v = &layouts[5]} },
   { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
   { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
   { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[0]} },
   { MODKEY,                       XK_y,      setlayout,      {.v = &layouts[4]} },
   { MODKEY,                       XK_space,  setlayout,      {0} },
   { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
   { MODKEY,                       XK_a,      view,           {.ui = ~0 } },
   { MODKEY|ShiftMask,             XK_a,      tag,            {.ui = ~0 } },
   { MODKEY,                       XK_comma,  focusmon,       {.i = +1 } },
   { MODKEY,                       XK_period, focusmon,       {.i = -1 } },
   { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = +1 } },
   { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = -1 } },
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
   TAGKEYS(                        XK_minus,                  10)
   TAGKEYS(                        XK_equal,                  11)
   TAGKEYS(                        XK_BackSpace,              12)
   /* THE HOLY QUIT KEY-----------------------------------------------*/
   { MODKEY|ShiftMask,             XK_e,      quit,           {0} },
   { MODKEY|ShiftMask,             XK_r,      restart,        {0} },
  };

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] =
  {
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

