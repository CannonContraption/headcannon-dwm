# HeadCannon-DWM
A fork of DWM with a number of little quality-of-life patches such as built-in
battery monitoring and light/dark mode runtime switch.

# Requirements
In order to build this version of DWM, you don't need anything special when
compared to vanilla DWM. Just use the standard Xlib headers.

# Installation
Firstly, make sure that /usr/local/bin is in your $PATH. If you can't do that,
edit config.mk just like any other DWM install.

Then just run the standard make commands:

    make
    sudo make install

# Launching HeadCannon-DWM
First of all, you need a display manager that can use .xsession or similar. DWM
has no autostarts support in this configuration, and that means that in order
to get things like a status bar, you will need some helper commands. Examples
can be found in my dotfiles repo.

The basics to get it running can be summed up in one line:

    exec dwm

Assuming your install is configured right, that will get you a *minimal*
desktop. Do note in order to do anything with it, you will need a copy of
dmenu. Stock will work fine, including most distro packages.

Furthermore, I personally recommend using something like sxhkd (Simple X HotKey
Daemon) for binding keyboard shortcuts. You can add those to the config.h in
DWM itself, but using a separate hotkey program means more portable, and
frankly easier to configure hotkey support.

In order to spawn DWM on a specific display, simply set the DISPLAY environment
variable to match your preferences. For example, if you use display :1 rather
than :0 (multiseat environment, etc) you could just run

    DISPLAY=:1 exec dwm

and dwm will start on that display.

# Configuration

Modify config.h and rebuild. Simple as that.

# Changes from upstream DWM
## Colors
First and foremost, the colors have been changed to more closely match the
'Wombat' Emacs theme. That's my personal preference for theme, but if you don't
like it feel free to change it in your own config.h.

On the note of colors, headcannon-dwm also has support for switching between
a light mode and a dark mode. My preference for light themes (again in Emacs)
is the Leuven theme, and thus that's what I used to model the light theme of
headcannon-dwm. To toggle between light and dark mode, use super+q.

## Battery Status
This ties in nicely with the previous point. While not perfect, this copy of
dwm has a rudimentary battery checker, which uses files in /sys/class in order
to change the color of the window manager to match certain battery states.
Here is the pattern it follows:

Charged or desktop? Uses a green color.

Discharging but good battery? Uses a blue color.

Discharging but low battery? Uses a red color.

Charging? Uses a yellow color.

These are all approximations of the actual colors, they vary depending on
whether you're in light or dark mode, but that's the general idea.

## Extra Layouts
This copy of dwm includes the centeredmaster and gaplessgrid patches from the
dwm website.

## Standard Shortcuts
I moved to dwm from i3. Personally speaking, I liked many of i3's keyboard
shortcuts better ($mod+Shift+q to close a window, for instance) so many of the
standard i3 shortcuts make an appearance here rather than DWM shortcuts. See
config.h for now for a full list, though I may document them here in time.

## Extra tags
This version of dwm has eleven tags. Mainly so all the numbers are used.
super+Backspace is used in my workflow for sticky things that apply to any
project I have open at that point in time.

