/*
 * See LICENSE file for copyright and license details.
 *
 * Color scheme settings. Define and set up colors here.
 * The default should stay at the top, even if you intend to set a new one.
 */

/*
 * How color themes work:
 *
 * Color themes in HCDWM are tightly integrated with the battery monitoring
 * system, and as such your theme should provide a different "mode" for each
 * battery state. These are the modes:
 * - norm - Normal, unselected screen. When the mouse is on another screen.
 * - sel  - For whatever's selected. Battery is discharging, but good.
 * - bat  - For whatever's selected, when the battery is low.
 * - chr  - For whatever's selected, when the battery is charging.
 * - full - For whatever's selected, when the battery is full.
 *
 * Each of these, in turn, has three different colors to specify. One for
 * foreground, one for background, and one for the border color. These are
 * specified in order in a char* array. See below for examples.
 *
 * Happy theming!
 */


/* ================== Theme definition section ============================== */
/*
 *  _      __           __        __
 * | | /| / /__  __ _  / /  ___ _/ /_
 * | |/ |/ / _ \/  ' \/ _ \/ _ `/ __/
 * |__/|__/\___/_/_/_/_.__/\_,_/\__/
 *
 * The Default Headcannon-DWM theme
 * credit to the Emacs team
 */
static       char col_grey1[]             = "#242424";
static       char col_grey2[]             = "#444444";
static       char col_grey3[]             = "#bbbbbb";
/* static       char col_grey4[]             = "#eeeeee"; Unused. */
static       char col_green[]             = "#92A65E";
static       char col_red[]               = "#E5786D";
static       char col_yellow[]            = "#F0DFAF";
static       char col_blue[]              = "#9AB8D7";

static colortheme color_wombat =
  {
   /* scheme       foregrnd,  backgrnd,  border */
   .schemenorm = { col_grey3, col_grey1, col_grey2 },
   .schemesel  = { col_grey1, col_blue,  col_blue  },
   .schemebat  = { col_grey1, col_red,   col_red   },
   .schemechr  = { col_grey1, col_yellow,col_yellow},
   .schemefull = { col_grey1, col_green, col_green },
  };

/*
 *    __
 *   / /  ___ __ ___  _____ ___
 *  / /__/ -_) // / |/ / -_) _ \
 * /____/\__/\_,_/|___/\__/_//_/
 *
 * The Default Light theme in Headcannon-DWM
 * Credit to the Emacs team, again
 */
static       char col_grey1leuven[]       = "#d3d3d3";
static       char col_grey2leuven[]       = "#bebebe";
static       char col_grey3leuven[]       = "#020202";
static       char col_grey4leuven[]       = "#595959";
static       char col_greenleuven[]       = "#008000";
static       char col_redleuven[]         = "#ff0b0b";
static       char col_yellowleuven[]      = "#ff8c00";
static       char col_blueleuven[]        = "#335ea8";

static colortheme color_leuven =
  {
   .schemenorm = { col_grey4leuven, col_grey1leuven, col_grey2leuven },
   .schemesel  = { col_grey1leuven, col_blueleuven,  col_blueleuven  },
   .schemebat  = { col_grey1leuven, col_redleuven,   col_redleuven   },
   .schemechr  = { col_grey3leuven, col_yellowleuven,col_yellowleuven},
   .schemefull = { col_grey1leuven, col_greenleuven, col_greenleuven },
  };

/*
 _____________  _     __
/_  __/ __/ _ \(_)__ / /
 / / _\ \/ // / (_-</ _ \
/_/ /___/____/_/___/_//_/
TSDH light -ish color theme
 */
static       char col_grey1tsdish[]       = "#fafafa";
static       char col_grey2tsdish[]       = "#bebebe";
static       char col_grey3tsdish[]       = "#020202";
static       char col_grey4tsdish[]       = "#383a42";
static       char col_greentsdish[]       = "#50a14f";
static       char col_redtsdish[]         = "#e44649";
static       char col_yellowtsdish[]      = "#ffec8b";
static       char col_bluetsdish[]        = "#94BFF3";

static colortheme color_tsdish =
  {
   /* scheme       foregrnd,  backgrnd,  border */
   .schemenorm = { col_grey4tsdish, col_grey1tsdish, col_grey2tsdish },
   .schemesel  = { col_grey4tsdish, col_bluetsdish,  col_bluetsdish  },
   .schemebat  = { col_grey1tsdish, col_redtsdish,   col_redtsdish   },
   .schemechr  = { col_grey3tsdish, col_yellowtsdish,col_yellowtsdish},
   .schemefull = { col_grey1tsdish, col_greentsdish, col_greentsdish },
  };

/* ====================== Color settings section ============================ */
/* Default color scheme */
int csch = 0;

/* Number of configured color schemes */
static int no_color_themes = 3;

/* List of finished configurations */
static colortheme * colors[3] =
  {
   &color_wombat,
   &color_leuven,
   &color_tsdish,
  };
