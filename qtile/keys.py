from libqtile.config import Key
from libqtile.lazy import lazy
from libqtile.utils import guess_terminal


mod = "mod4"

keys = [

    # Windows hotkeys (basic qtile config)
    Key([mod], "l", lazy.layout.right(), desc="Move focus to right"),
    Key([mod], "h", lazy.layout.left(), desc="Move focus to left"),
    Key([mod], "j", lazy.layout.down(), desc="Move focus down"),
    Key([mod], "k", lazy.layout.up(), desc="Move focus up"),

    Key([mod, "shift"], "l", lazy.layout.shuffle_right(), desc="Move window to the right"),
    Key([mod, "shift"], "h", lazy.layout.shuffle_left(), desc="Move window to the left"),
    Key([mod, "shift"], "j", lazy.layout.shuffle_down(), desc="Move window down"),
    Key([mod, "shift"], "k", lazy.layout.shuffle_up(), desc="Move window up"),
    
    Key([mod, "control"], "l", lazy.layout.grow_right(), desc="Grow window to the right"),
    Key([mod, "control"], "h", lazy.layout.grow_left(), desc="Grow window to the left"),
    Key([mod, "control"], "j", lazy.layout.grow_down(), desc="Grow window down"),
    Key([mod, "control"], "k", lazy.layout.grow_up(), desc="Grow window up"),
    
    Key([mod], "n", lazy.layout.normalize(), desc="Reset all window sizes"),
    Key([mod, 'shift'], 'f', lazy.window.toggle_fullscreen()),
    
    
    # Toggle between different layouts as defined below
    Key([mod, "control"], "r", lazy.reload_config(), desc="Reload the config"),
    Key([mod], "Tab", lazy.next_layout(), desc="Toggle between layouts"),
    Key([mod], "q", lazy.window.kill(), desc="Kill focused window"),
    
    
    # Keys applications hotkeys
    Key([mod], "Return", lazy.spawn('kitty'), desc="Launch terminal"),
    Key([mod], 'b', lazy.spawn('firefox'), desc="Launch Browser"),
    Key([mod], 'r', lazy.spawn('rofi -show drun')),
    Key([mod], 'l', lazy.spawn('betterlockscreen -l')),
    
    # Background apps
    Key([mod, 'shift'], 's', lazy.spawn('flameshot gui')),

    # Scripts
    Key([mod], 'p', lazy.spawn('bash -c "/home/sebastian/.config/scripts/external_media"')),


    # Keys system hotkeys
    # Brightness
    Key([], 'XF86MonBrightnessDown', lazy.spawn('brightnessctl s 2%-')),
    Key([], 'XF86MonBrightnessUp', lazy.spawn('brightnessctl s 2%+')),
    
    # Audio
    Key([], 'XF86AudioRaiseVolume', lazy.spawn('amixer -D pulse sset Master 2%+')),
    Key([], 'XF86AudioLowerVolume', lazy.spawn('amixer -D pulse sset Master 2%-')),
    Key([], 'XF86AudioMute', lazy.spawn('amixer -D pulse sset Master toggle')),    
]
