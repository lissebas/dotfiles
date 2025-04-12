#!/bin/sh
# configuration setting for sigir's laptop

# Set monitor
xrandr --output HDMI-1 --mode 1920x1080 --left-of eDP-1

# Init audio interfaz
pactl set-default-sink alsa_output.pci-0000_04_00.1.hdmi-stereo

# Active compositor
picom &

# Set wallpaper
feh --bg-fill ~/Pictures/Wallpapers/semi\ circle.jpg

# Active notify daemon
dunst &

