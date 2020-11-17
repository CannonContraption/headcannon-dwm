#!/bin/sh

# reset the localplatform.h file
rm -v localplatform.h
touch localplatform.h

# Discover the battery and AC adapter files
battery=$(ls /sys/class/power_supply | grep BAT)
adapter=$(ls /sys/class/power_supply | grep AC)

# mklaptopconfig function
#
# Adds in the laptop configuration defines for use by the battery checking code.
# This allows the build step to determine this stuff rather than constantly
# checking.
mklaptopconfig()
{
    echo '#define LAPTOPMODE' >> localplatform.h
    echo '#define BATTERYID "'$battery'"' >> localplatform.h
    echo '#define ACADAPTERID "'$adapter'"' >> localplatform.h
}

# mkdesktopconfig function
#
# Adds placeholder defines for desktops so we can still build
mkdesktopconfig()
{
    echo '#define BATTERYID "null"' >> localplatform.h
    echo '#define ACADAPTERID "null"' >> localplatform.h
}

# Terminal detection
#
# Detects alacritty, else falls back to st
detectterm()
{
    which alacritty && {
        echo '#define DEFAULTTERM "alacritty"' >> localplatform.h
        return 0
    }
    echo '#define DEFAULTTERM "st"' >> localplatform.h
}

detectterm

# Apply the battery settings
if [ -n "$battery" ]; then
    mklaptopconfig
else
    mkdesktopconfig
fi
