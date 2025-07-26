#!/bin/sh
# Setting by sigir

# Set monitor
xrandr --auto

# Active compositor
picom &

# Set wallpaper
feh --bg-fill ~/Pictures/Wallpapers/04.jpg

# Active notify daemon
dunst &

