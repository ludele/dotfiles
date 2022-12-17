/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int snap           = 31;  /* snap pixel */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 0;   /* 0 means bottom bar */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False display systray on other*/
static const int showsystray             = 1;   /* 0 means no systray */

static const char *fonts[]          = { "mononoki:size=12.3:antialias=true:autohint=true", "Noto sans CJK JP:size 18:antialias=true:autohint=true", "JoyPixels:pixelsize=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "Code New Roman:size=13";

/* tagging */
	static const char *tags[] = { "$", "二", "三", "四", "五", "六"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
        { "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
        { "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
        { "st",      NULL,     NULL,           0,         0,          1,           0,        -1 },
        { NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]",       tile },    /* first entry is default */
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

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const char norm_fg[] = "#b4b9d8";
static const char norm_bg[] = "#090a0d";
static const char norm_border[] = "#000000";

static const char sel_fg[] = "#ffc0cb";
static const char sel_bg[] = "#000000";
static const char sel_border[] = "#ffffff";

static const char *colors[][3]   = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
};


/* commands */
//static const char *[]            = {""};
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]  = { "dmenu_run" };
static const char *termcmd[]   = { "st", NULL  };
//static const char *emacs[]     = { "/home/lu/.local/bin/emacsclient.sh" };
//static const char *btc[]       = { "btc" };
//static const char *swm[]       = { "swm" };
//static const char *red[]       = { "/home/lu/.local/bin/redshift_inc.sh"  };

static Key keys[] = {
	/* modifier             key        function           argument */
	{ MODKEY,               XK_d,      spawn,             {.v = dmenucmd } },
	{ MODKEY|ShiftMask,     XK_Return, spawn,             {.v = termcmd } },
	{ MODKEY|ShiftMask,     XK_e,      spawn,             {.v = (const char *[]){"/home/lu/.local/bin/emacsclient.sh" } } },
	{ MODKEY,      		XK_b,      spawn,             {.v = (const char *[]){"btc"} } },
	{ MODKEY,      		XK_v,      spawn,             {.v = (const char *[]){"swm" } } },
	{ MODKEY,      		XK_F1,     spawn,             {.v = (const char *[]){"/home/lu/.local/bin/redshift_inc.sh" } } },
	{ MODKEY,      		XK_e,      spawn,             SHCMD("pactl set-sink-volume '@DEFAULT_SINK@' +500") },
	{ MODKEY,      		XK_w,      spawn,             SHCMD("pactl set-sink-volume '@DEFAULT_SINK@' -500") },
        { MODKEY,               XK_F3,     spawn,             SHCMD("notify-send Volume: $(pamixer --get-volume-human)") },
	{ MODKEY,      		XK_F2,     spawn,             {.v = (const char *[]){"/home/lu/.local/bin/pactl_sink" } } },
	{ MODKEY,      		XK_r,      spawn,             SHCMD("st -e pulsemixer") },
	{ MODKEY,	        XK_p,      togglebar,         {0} },
	{ MODKEY,               XK_Down,   focusstack,        {.i = +1 } },
	{ MODKEY,               XK_Up,     focusstack,        {.i = -1 } },	
	{ MODKEY|ShiftMask,     XK_Down,   focusstack,        {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_Up,     focusstack,        {.i = -1 } },
	{ MODKEY,               XK_o,      incnmaster,        {.i = +1 } },
	{ MODKEY,               XK_l,      incnmaster,        {.i = -1 } },
	{ MODKEY,       	XK_j,      aspectresize,      {.i = +24} },
	{ MODKEY, 	        XK_k,      aspectresize,      {.i = -24} },
	{ MODKEY|ShiftMask,     XK_Left,   setmfact,          {.f = -0.05} },
	{ MODKEY|ShiftMask,     XK_Right,  setmfact,          {.f = +0.05} },
        { MODKEY,               XK_Left,   setmfact,          {.f = -0.05} },
	{ MODKEY,               XK_Right,  setmfact,          {.f = +0.05} },
	{ MODKEY,               XK_Return, zoom,              {0} },
	{ MODKEY,               XK_Tab,    view,              {0} },
	{ MODKEY|ShiftMask,     XK_q,      killclient,        {0} },
	{ MODKEY,               XK_a,      setlayout,         {.v = &layouts[0]} },
	{ MODKEY,               XK_f,      setlayout,         {.v = &layouts[1]} },
	{ MODKEY,               XK_s,      setlayout,         {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,     XK_space,  setlayout,         {0} },
	{ MODKEY,               XK_space,  togglefloating,    {0} },
	{ MODKEY|ShiftMask,     XK_f,      togglefullscr,     {0} },
	{ MODKEY,               XK_0,      view,              {.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,      tag,               {.ui = ~0 } },
	{ MODKEY,               XK_z,      focusmon,          {.i = -1 } },
	{ MODKEY,               XK_x,      focusmon,          {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_z,      tagmon,            {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_x,      tagmon,            {.i = +1 } },
	TAGKEYS(                XK_1,                         0)
	TAGKEYS(                XK_2,                         1)
	TAGKEYS(                XK_3,                         2)
	TAGKEYS(                XK_4,                         3)
	TAGKEYS(                XK_5,                         4)
	TAGKEYS(                XK_6,                         5)
//	{ MODKEY|ShiftMask,     XK_r,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};