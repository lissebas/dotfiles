# !/bin/bash


# Arbitrary but unique message tag
msgTag="myvolume"
appName="SoundManager"

# Query amixer for the current volume and whether or not the speaker is muted
volume="$(amixer get Master | tail -1 | awk '{print $5}' | sed 's/[^0-9]*//g')"
mute="$(amixer get Master | tail -1 | awk '{print $6}' | sed 's/[^a-z]*//g')"

if [[ $volume == 0 || "$mute" == "off" ]]; then
    # Show the sound muted notification
    dunstify -a $appName -u low -i audio-volume-muted -h string:x-dunst-stack-tag:$msgTag "Volume muted" 
else
    # Show the volume notification
    dunstify -a "$appName" -u low -i audio-speakers \
      -h string:x-dunst-stack-tag:$msgTag \
      -h int:value:"$volume" \
      "${volume}%"


fi
