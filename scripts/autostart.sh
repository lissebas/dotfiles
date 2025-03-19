#!/bin/sh
# configuration setting for sigir's laptop

# Set monitor
 xrandr --auto
#xrandr --output eDP-1 --mode 1366x768 --output HDMI-1 --mode 1440x900 --same-as eDP-1


# Active compositor
picom &

# Set wallpaper
feh --bg-fill ~/Pictures/Wallpapers/05.png

# Active notify daemon
dunst &

