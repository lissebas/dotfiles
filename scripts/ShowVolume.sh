# !/bin/bash


# Arbitrary but unique message tag
msgTag="myvolume"
appName="SoundManager"


getVolume() {
  amixer get Master | tail -1 | awk -F'[][]' '{ print $2 }' | sed 's/%//'
}

getStatus() {
  amixer get Master | tail -1 | awk -F'[][]' '{ print $4 }'
}

volume=$(getVolume)
mute=$(getStatus)

if [[ $volume == 0 || "$mute" == "off" ]]; then
    # Show the sound muted notification
    dunstify -a $appName -u low -h string:x-dunst-stack-tag:$msgTag "  Volume muted" 
else
    # Show the volume notification
    dunstify -a "$appName" -u low \
      -h string:x-dunst-stack-tag:$msgTag \
      -h int:value:"$volume" \
      "  ${volume}%"
fi
