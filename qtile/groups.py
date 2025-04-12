from libqtile.config import Group, Key
from libqtile.lazy import lazy

from keys import mod, keys

groups = [Group(i) for i in ['󰈹', '󰉋', '', '󰛸', '󰒋','󰓇']]

for i, group in enumerate(groups):
    
    actual_group = str(i + 1)
    
    keys.extend(
        [
            # mod1 + letter of group = switch to group
            Key([mod], actual_group, lazy.group[group.name].toscreen()),

            # mod1 + shift + letter of group = switch to & move focused window to group
            Key([mod, "shift"], actual_group, lazy.window.togroup(group.name, switch_group=True)),
            # Or, use below if you prefer not to switch to that group.
            # # mod1 + shift + letter of group = move focused window to group
            # Key([mod, "shift"], i.name, lazy.window.togroup(i.name),
            #     desc="move focused window to group {}".format(i.name)),
        ]
    )

