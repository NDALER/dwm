/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 12;       /* snap pixel */
static const unsigned int gappih    = 13;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 13;       /* vert inner gap between windows */
static const unsigned int gappoh    = 13;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 13;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int attachdirection    = 3;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"Firacode nerd font mono:pixelsize=13.5:antialias=true:autohint=true", "Noto Sans JP:size=12", };
static const char dmenufont[]       = "Firacode nerd font mono:pixelsize=13.5:antialias=true:autohint=true";
/* Colors */
static const char col_white[]       = "#ffffff";
static const char col_gray1[]       = "#444444";
static const char col_gray2[]       = "#222222";
static const char col_pink[]        = "#dd1991";
static const char col_pink2[]       = "#ba157a";
static const char col_blue[]        = "#157aba";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
   /*               fg         bg         border   */
   [SchemeNorm]  = { col_white, col_gray2, col_gray1 }, /* bar foreground, bar background, inactive window border */
   [SchemeSel]   = { col_pink, col_pink , col_pink  },  /* unused, unused, active window border */
   [SchemeTitle] = { col_white, col_gray2, col_gray2 }, /* title foreground, title background, unused */
};
static const unsigned int alphas[][3]      = {
   /*               fg      bg        border     */
   [SchemeNorm]  = { OPAQUE, baralpha, borderalpha },
   [SchemeSel]   = { OPAQUE, baralpha, borderalpha },
   [SchemeTitle] = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五" };

/*static const char *tagsel[][2] = {
   { "#ffffff", "#ba157a" },
   { "#ffffff", "#ba157a" },
   { "#ffffff", "#ba157a" },
   { "#ffffff", "#ba157a" },
   { "#ffffff", "#ba157a" },*/

static const char *tagsel[][2] = {
   /* fg            bg */
   { "#ffffff", "#ff5555" },
   { "#ffffff", "#ff79c6" },
   { "#282a36", "#50fa7b" },
   { "#282a36", "#f1fa8c" },
   { "#ffffff", "#2b3ef3" },
};

static const unsigned int tagalpha[] = { OPAQUE, baralpha };

static const Rule rules[] = {
    /* xprop(1):
    * WM_CLASS(STRING) = instance, class
    * WM_NAME(STRING) = title
        */
   /* class      instance    title       tags mask     isfloating  isterminal  noswallow monitor */
   { "Gimp",     NULL,       NULL,       1 << 3,       0,          0,           0,       -1 },
   { "firefox",  NULL,       NULL,       1 << 4,       0,          0,          -1,       -1 },
   { "inscape",  NULL,       NULL,       1 << 3,       0,          0,           0,       -1 },
   { "Anki",     NULL,       NULL,       1 << 3,       0,          0,           1,       -1 },
   { "st",       NULL,       NULL,       0,            0,          1,           0,       -1 },
   { "ncmpcpp",  NULL,       NULL,       0,            1,          1,           0,       -1 },
   { NULL,       NULL,   "Event Tester", 0,            0,          0,           1,       -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
   /* symbol     arrange function */
   { "[T]",      tile },    /* first entry is default */
   { "[F]",      NULL },    /* no layout function means floating behavior */
   { "|M|",      centeredmaster },
   { ">M>",      centeredfloatingmaster },
   { "[M]",      monocle },
   { "[@]",      spiral },
   { "[\\]",     dwindle },
   { "H[]",      deck },
   { "TTT",      bstack },
   { "===",      bstackhoriz },
   { "HHH",      grid },
   { "###",      nrowgrid },
   { "---",      horizgrid },
   { ":::",      gaplessgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
   { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
   { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
   { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
   { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/fish", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray2, "-nf", col_white, "-sb", col_pink, "-sf", col_white, NULL };
static const char *termcmd[]  = { "st", NULL };
#include "shift-tools.c"
//function keys, its on /usr/include/X11/XF86keysym.h
#include <X11/XF86keysym.h>

static Key keys[] = {
   /* modifier                     key        function        argument */
   { MODKEY,                       XK_x,      movecenter,     {0} },
   { MODKEY,                       XK_s,      togglesticky,   {0} },
   { MODKEY,	                    XK_i, shiftviewclients,    { .i = -1 } },
   { MODKEY,                       XK_o, shiftviewclients,    { .i = +1 } },
   { MODKEY,                       XK_bracketleft,      layoutscroll,   {.i = -1 } },
   { MODKEY,                       XK_bracketright,     layoutscroll,   {.i = +1 } },
   /* { MODKEY|ShiftMask,             XK_o,	shiftview,         { .i = +1 } }, */
   /* { MODKEY|ShiftMask,             XK_i,	shiftview,         { .i = -1 } }, */
   { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
   { MODKEY,	                    XK_Return, spawn,          {.v = termcmd } },
   { MODKEY,                       XK_b,      togglebar,      {0} },
   { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
   { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
   { MODKEY,                       XK_apostrophe, incnmaster, {.i = +1 } },
   { MODKEY,                       XK_semicolon, incnmaster,  {.i = -1 } },
   { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
   { MODKEY,	 		            XK_7,      shiftboth,      { .i = -1 }	},
   /* { MODKEY|ControlMask,		XK_h,      shiftswaptags,  { .i = -1 }	}, */
   /* { MODKEY|ControlMask,		XK_l,      shiftswaptags,  { .i = +1 }	}, */
   { MODKEY, 	                    XK_8,      shiftboth,      { .i = +1 }	},
   { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
   { MODKEY,                       XK_m,      setcfact,       {.f = +0.25} },
   { MODKEY,                       XK_comma,  setcfact,       {.f = -0.25} },
   { MODKEY,                       XK_slash,  setcfact,       {.f =  0.00} },
   { MODKEY,                       XK_z,      zoom,           {0} },
   { MODKEY,                       XK_equal,  incrgaps,       {.i = +1 } },
   { MODKEY,                       XK_minus,  incrgaps,       {.i = -1 } },
     /* { MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } }, */
     /* { MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } }, */
     /* { MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } }, */
     /* { MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } }, */
     /* { MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } }, */
     /* { MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } }, */
     /* { MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } }, */
     /* { MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } }, */
     /* { MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } }, */
     /* { MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } }, */
     /* { MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } }, */
     /* { MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } }, */
   { MODKEY|ShiftMask,             XK_equal,  togglegaps,     {0} },
   { MODKEY|ShiftMask,    	        XK_minus,  defaultgaps,    {0} },
   { MODKEY,                       XK_Tab,    view,           {0} },
   { MODKEY,                       XK_backslash, view,           {0} },
   { MODKEY,                       XK_Escape, killclient,     {0} },
   { MODKEY,                       XK_BackSpace, killclient,  {0} },
   { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
   /* { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, */
   /* { MODKEY,                       XK_n,      setlayout,      {.v = &layouts[2]} }, */
   { MODKEY,                       XK_space,  setlayout,      {0} },
   { MODKEY,                       XK_g,  togglefloating, {0} },
   { MODKEY,                       XK_f,      togglefullscr,  {0} },
   { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
   { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
   /* { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, */
   /* { MODKEY,                       XK_period, focusmon,       {.i = +1 } }, */
   /* { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, */
   { MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
   { MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
   { MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
   { MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
   { MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
   { MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
   { MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
   { MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
   { MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
   { MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
   { MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
   { MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
   { MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
   { MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
   { MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
   { MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
   { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
   TAGKEYS(                        XK_1,                      0)
   TAGKEYS(                        XK_2,                      1)
   TAGKEYS(                        XK_3,                      2)
   TAGKEYS(                        XK_4,                      3)
   TAGKEYS(                        XK_5,                      4)
   { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
   { 0, XF86XK_Explorer,		spawn,	   SHCMD("st -i -e nmtui") }, //fn + f1
   /* { 0, XF86XK_Search,		spawn,	   SHCMD("dunstify -r 1 (echo 'Brightness  = ' ( xbacklight -get | cut -c1-4))") },// fn + f2 */
   /* { 0, XF86XK_Calculator,		spawn,	   SHCMD("dunstify -r 1 (echo 'Brightness  = ' ( xbacklight -get | cut -c1-4))") },// fn + f3 */
   { 0, XF86XK_Tools,		    spawn,	   SHCMD("st -i -e ncmpcpp") },// fn + f4
   { 0, XF86XK_AudioPrev,		spawn,	   SHCMD("mpc prev"  ) }, //fn + f5
   { 0, XF86XK_AudioNext,		spawn,	   SHCMD("mpc next"  ) },// fn + f6
   { 0, XF86XK_AudioPlay, 		spawn,	   SHCMD("mpc toggle") },// fn + f7
   { 0, XF86XK_AudioStop,		spawn,	   SHCMD("mpc clear" ) },// fn + f8
   /* { 0, XF86XK_AudioMute,		spawn,	   SHCMD("dunstify -r 1 (echo 'Brightness  = ' ( xbacklight -get | cut -c1-4))") },// fn + f9 */
   /* { 0, XF86XK_AudioLowerVolume, spawn,       SHCMD("dunstify -r 1 (echo 'Brightness  = ' ( xbacklight -get | cut -c1-4))") },// fn + f10 */
   /* { 0, XF86XK_AudioRaiseVolume, spawn,       SHCMD("dunstify -r 1 (echo 'Brightness  = ' ( xbacklight -get | cut -c1-4))") },// fn + f11 */
   /* i think f12 can't be added because it would lock my keyboard */
   { MODKEY, 		 	XK_F1,     spawn,          SHCMD("dunstify -r 1 (echo 'Brightness  = ' ( xbacklight -get | cut -c1-4))")},
   { MODKEY, 		 	XK_F6,     spawn,          SHCMD("dunstify -r 1 (echo 'Brightness  = ' ( xbacklight -get | cut -c1-4))")},
   { MODKEY, 		 	XK_F7,     spawn,          SHCMD("fish -c /home/ndaler/SCRIPTS/Custom-scripts/brightnessdown.fish")},
   { MODKEY, 			XK_F8,     spawn,          SHCMD("fish -c /home/ndaler/SCRIPTS/Custom-scripts/brightnessup.fish")},
   { MODKEY, 			XK_F9,     spawn,          SHCMD("fish -c /home/ndaler/SCRIPTS/Custom-scripts/volumemuted.fish")},
   { MODKEY, 			XK_F10,    spawn,          SHCMD("fish -c /home/ndaler/SCRIPTS/Custom-scripts/volumedown.fish")},
   { MODKEY, 			XK_F11,    spawn,          SHCMD("fish -c /home/ndaler/SCRIPTS/Custom-scripts/volumeup.fish")},
   { 0, 		   		XK_Print,  spawn,          SHCMD("fish -c /home/ndaler/SCRIPTS/Custom-scripts/screenshot.fish")},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
   /* click          event mask button   function        argument */
   { ClkLtSymbol,    0,         Button1, setlayout,      {0} },
   { ClkLtSymbol,    0,         Button3, setlayout,      {.v = &layouts[2]} },
   { ClkWinTitle,    0,         Button2, zoom,           {0} },
   { ClkStatusText,  0,         Button2, spawn,          {.v = termcmd } },
   { ClkClientWin,   MODKEY,    Button1, movemouse,      {0} },
   { ClkClientWin,   MODKEY,    Button2, togglefloating, {0} },
   { ClkClientWin,   MODKEY,    Button3, resizemouse,    {0} },
  { ClkClientWin,   MODKEY|ShiftMask, Button3, killclient, {0} },
   { ClkTagBar,      0,         Button1, view,           {0} },
   { ClkTagBar,      0,         Button3, toggleview,     {0} },
   { ClkTagBar,      MODKEY,    Button1, tag,            {0} },
   { ClkTagBar,      MODKEY,    Button3, toggletag,      {0} },
   { ClkWinTitle,   0,          Button4, shiftviewclients, { .i = +1 } },
   { ClkWinTitle,   0,          Button5, shiftviewclients, { .i = -1 } },
};

