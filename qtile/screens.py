from libqtile import bar, layout, widget
from libqtile.config import Click, Drag, Match, Screen

from Components.screens import power_line, network_widget#, sink_widget
from Components.utils import get_connection_interface#, get_sound_interface

widgets = [

    widget.GroupBox(
        fontsize=12,
        borderwidth=3,
        highlight_method='block',

        # Text color
        active = '#ed8796',                     # Red color: when an app is open
        inactive = '#cad3f5',                   # Text color: when a window is empty
        block_highlight_text_color = '#a6da95', # Green color: when stay into a window
        this_current_screen_border='#24273a',   # Base color: when stay into a window
    ),

    widget.Spacer(),

    # ----- power line separation -----
    power_line(foreground = '#a6e3a1', background = None),

    # network
    network_widget(get_connection_interface),


    # SEPARATOR

    power_line(foreground = '#cba6f7', background = '#a6e3a1'),

    widget.TextBox(
        text='',  # ícono de memoria RAM (también puedes usar: 󰘚 o 󰾆)
        fontsize=12,
        padding=4,
        background='#cba6f7',  # color que combine con tu paleta
        foreground='#24273a',
    ),

    widget.Memory(
        background='#cba6f7',
        foreground='#24273a',
        format='{MemUsed:.1f}GB',  # muestra memoria usada en GB
        padding=4,
        measure_mem='G'  # garantiza consistencia en GIGAS
    ),

    widget.TextBox(
        text='󰍛',  # ícono de CPU (alternativas: 󰘚 o )
        fontsize=12,
        padding=4,
        background='#cba6f7',
        foreground='#24273a',
    ),
    widget.CPU(
        format='{load_percent}%',
        background='#cba6f7',
        foreground='#24273a',
        padding=4
    ),

    # SEPARATOR

    power_line(foreground = '#89b4fa', background = '#cba6f7'),

    # battery
    widget.TextBox(
    "", fontsize=12, padding=6, background='#89b4fa',
    foreground='#24273a'),
 
    widget.Battery(
        background='#89b4fa',
        foreground='#24273a',
        low_percentage=0.2,
        low_foreground='DF2E38',
        format='{percent:2.0%}',
        padding=6,
        full_char='Charged',
    ),

    # volume
#    sink_widget(get_sound_interface),
  
    widget.Volume(
        background='#89b4fa',
        foreground='#24273a',
        padding=2,
        mute_format = 'Muted',
    ),

    widget.TextBox(
        text=' 󰃠',  # ícono de brillo (también: 󰛨 o 󰖨)
        fontsize=12,
        padding=4,
        background='#89b4fa',
        foreground='#24273a',
    ),
    
    widget.Backlight(
        backlight_name='amdgpu_bl1',  # puede variar según tu hardware
        format='{percent:2.0%}',
        background='#89b4fa',
        foreground='#24273a',
        padding=4
    ),



    # SEPARATOR

    power_line(foreground = '#fab387', background = '#89b4fa'),

    widget.TextBox(
        text='󰃭 ', 
        fontsize=12,
        padding=0,
        background='#fab387',
        foreground = '#24273a'
    ),

    # Time & Date (Flat Nerd Font Style - unified color)
    widget.Clock(
        format="%d %b - %H:%M", 
        background='#fab387',
        foreground = '#24273a',
        padding=4
    ),


]


screens = [
    Screen(
        top = bar.Bar(widgets, size = 20, margin = [4,4,0,4], background = '#24273a')
    )
]
