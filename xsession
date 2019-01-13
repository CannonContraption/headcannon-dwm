#!/bin/zsh
#Status line command loop
#i3status | while read line; do
#  xsetroot -name "$line"
#done &
slstatus &

#Some autostarts...
st -e autoadd &
ibus-daemon &
lxpolkit &

#Start the WM itself
./dwm 2> .dwm_errors.log

