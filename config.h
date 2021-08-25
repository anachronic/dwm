/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "NotoSansDisplay Nerd Font:style=Semibold:pixelsize=24;1", "NotoColorEmoji:fontformat=truetype:pixelsize:24:antialias=false;" };
static const char dmenufont[]       = "monospace:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1: nav", "2: term", "3:dev", "4: discord", "5", "6", "7", "8: prod", "9: spot" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class    ,  instance ,  title                ,  tags mask ,  isfloating ,  monitor */
	{ "Gimp"    ,  NULL     ,  NULL                 ,  0         ,  1          ,  -1 },
	{ "Firefox" ,  NULL     ,  NULL                 ,  1 << 8    ,  0          ,  -1 },
	{ NULL      ,  NULL     ,  "Picture in picture" ,  ~0        ,  1          ,  -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
// static const char *termcmd[]  = { "kitty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

    // Sorting by keyboard order, commented if shortcut is defined elsewhere

    // Tags
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

    // Super+tab: Cycle between tags
	{ MODKEY,                       XK_Tab,    view,           {0} },

    // super+q: close window
	{ MODKEY,                       XK_q,      killclient,     {0} },
    // super+shift+q: Not defined yet
	// { MODKEY|ShiftMask,             XK_q,      killclient,     {0} },

    // super+w: taken by udevmon 
    // super+shift+w: Not defined yet
	// { MODKEY|ShiftMask,             XK_w,      killclient,     {0} },

    // super+e: Not defined yet
	// { MODKEY                        XK_e,      killclient,     {0} },
    // super+shift+e: Exit x session. Bound in sxhkd
	// { MODKEY|ShiftMask,             XK_e,      spawn,          {.v = exitcmd} },

    // super+r: Not defined yet
	// { MODKEY                        XK_r,      killclient,     {0} },
    // super+shift+r: Not defined yet
	// { MODKEY|ShiftMask,             XK_r,      spawn,          {.v = exitcmd} },

    // super+t: Taken by udevmon
    // super+shift+t: Taken by udevmon

    // super+y: Not defined yet
	// { MODKEY                        XK_y,      killclient,     {0} },
    // super+shift+y: Not defined yet
	// { MODKEY|ShiftMask,             XK_y,      spawn,          {.v = exitcmd} },

    // super+u: Not defined yet
	// { MODKEY                        XK_u,      killclient,     {0} },
    // super+shift+u: Not defined yet
	// { MODKEY|ShiftMask,             XK_u,      spawn,          {.v = exitcmd} },

    // super+i: increment windows in primary area
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    // super+shift+i: Not defined yet
	// { MODKEY|ShiftMask,             XK_i,      spawn,          {.v = exitcmd} },

    // super+o: Not defined yet
 	// { MODKEY,                       XK_o,      setlayout,      {.v = &layouts[3]} },
    // super+shift+o: Set centered master layout (not my word choice!!!)
 	{ MODKEY|ShiftMask,             XK_o,      setlayout,      {.v = &layouts[3]} },

    // super+p: Not defined yet
	// { MODKEY                        XK_p,      killclient,     {0} },
    // super+shift+p: Not defined yet
	// { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = exitcmd} },

    // super+a: Not defined yet
	// { MODKEY                        XK_a,      killclient,     {0} },
    // super+shift+a: Not defined yet
	// { MODKEY|ShiftMask,             XK_a,      spawn,          {.v = exitcmd} },

    // super+s: Not defined yet
	// { MODKEY                        XK_s,      killclient,     {0} },
    // super+shift+s: Not defined yet
	// { MODKEY|ShiftMask,             XK_s,      spawn,          {.v = exitcmd} },

    // super+d: Decrement windows in primary area
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    // super+shift+d: Not defined yet
	// { MODKEY|ShiftMask,             XK_d,      spawn,          {.v = exitcmd} },

    // super+f: Taken by udevmon and bound to ctrl+f
    // super+shift+f: Change to floating layout
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },

    // super+g: Taken by udevmon and bound to ctrl+g
    // super+shift+g: Not defined yet
	// { MODKEY|ShiftMask,             XK_g,      spawn,          {.v = exitcmd} },

    // super+h: Not defined yet
	// { MODKEY                        XK_h,      killclient,     {0} },
    // super+shift+h: Decrease primary area size
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },

    // super+j: Go down the stack (I think, not sure)
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    // super+shift+j: Not defined yet
	// { MODKEY|ShiftMask,             XK_j,      spawn,          {.v = exitcmd} },

    // super+k: Go up the stack (I think, not sure)
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    // super+shift+k: Not defined yet
	// { MODKEY|ShiftMask,             XK_k,      spawn,          {.v = exitcmd} },

    // super+l: Not defined yet
	// { MODKEY                        XK_l,      killclient,     {0} },
    // super+shift+l: Increase primary area size
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },

    // super+return: Spawn a shell (bound in sxhkd)
	// { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    // super+shift+return: push current window to primary area
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },

    // super+z: Not defined yet
	// { MODKEY                        XK_z,      killclient,     {0} },
    // super+shift+z: Not defined yet
	// { MODKEY|ShiftMask,             XK_z,      spawn,          {.v = exitcmd} },

    // super+x: Not defined yet
	// { MODKEY                        XK_x,      killclient,     {0} },
    // super+shift+x: Not defined yet
	// { MODKEY|ShiftMask,             XK_x,      spawn,          {.v = exitcmd} },

    // super+c: Not defined yet
	// { MODKEY                        XK_c,      killclient,     {0} },
    // super+shift+c: Not defined yet
	// { MODKEY|ShiftMask,             XK_c,      spawn,          {.v = exitcmd} },

    // super+v: Paste (even in terminal). Bound in sxhkd
	// { MODKEY,                       XK_v,      spawn,          SHCMD("/home/nsalas/dotfiles/scripts/superv.sh") },
    // super+shift+v: Not defined yet
	// { MODKEY|ShiftMask,             XK_v,      spawn,          {.v = exitcmd} },

    // super+b: Toggle status bar visibility
	{ MODKEY,                       XK_b,      togglebar,      {0} },
    // super+shift+b: Not defined yet
	// { MODKEY|ShiftMask,             XK_b,      spawn,          {.v = exitcmd} },

    // super+n: Not defined yet
	// { MODKEY                        XK_n,      killclient,     {0} },
    // super+shift+n: Not defined yet
	// { MODKEY|ShiftMask,             XK_n,      spawn,          {.v = exitcmd} },

    // super+m: Change to tiling layout
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[0]} },
    // super+shift+m: Change to monocle layout
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },

    // super+,: Move focus to other (previous?) monitor
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    // super+shift+,: Move current window to other (previous?) monitor
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },

    // super+.: Move focus to other (next?) monitor
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    // super+shift+.: Move current window to other (next?) monitor
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    // super+space: Launch dmenu, Bound in sxhkd
	// { MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
    // super+shift+space: Toggle floating, Note that it doesn't seem to work all that well
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

