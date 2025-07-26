# !/bin/bash
msgTag="mybrightness"
appName="VideoManager"

brightness=$(brightnessctl -d amdgpu_bl1 | grep "Current brightness" | awk '{print $4}' | sed 's/[^0-9]*//g')

# Show the brightness notification
dunstify -a "$appName" -u low -i computer \
  -h string:x-dunst-stack-tag:$msgTag \
  -h int:value:"$brightness" \
  "${brightness}%"
