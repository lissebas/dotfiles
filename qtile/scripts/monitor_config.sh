#!/bin/sh
# configuration setting for sigir's laptop

# Init audio interfaz
pactl set-default-sink alsa_output.pci-0000_04_00.6.analog-stereo

# Set monitor
xrandr --output HDMI-1 --mode 1440x900 --left-of eDP-1

# Active compositor
picom &

# Set wallpaper
feh --bg-fill ~/Pictures/Wallpapers/purple\ square.jpg

# Active notify daemon
dunst &

