from libqtile import bar, layout, widget
from libqtile.config import Click, Drag, Match, Screen

screens = [

    Screen(

        top=bar.Bar(

            [
                widget.GroupBox(
                    fontsize=12,
                    borderwidth=3,
                    highlight_method='block',

                    # Text color
                    active = '#ed8796',                     # Red color: when an app is open
                    inactive = '#cad3f5',                   # Text color: when a window is empty
                    block_highlight_text_color = '#a6da95', # Green color: when stay into a window
                    this_current_screen_border='#24273a',   # Base color: when stay into a window

                    rounded=False,
                    disable_drag=False,
                ),

                widget.Spacer(),

                # Time & Date (Flat Nerd Font Style - unified color)
                widget.Clock(
                    format="%H:%M | %d %b",  # adds AM/PM for clarity
                    foreground='#fab387',
                    padding=4
                ),


                # NB Systray is incompatible with Wayland, consider using StatusNotifier instead
                # widget.StatusNotifier(),
                widget.Spacer(),

                # network
                widget.TextBox(" ", fontsize=14, padding=0, foreground='#a6e3a1'),
                widget.Wlan(
                    foreground='#a6e3a1',
                    padding=6,
                    interface='wlan0',
                    format='{essid}'
                ),

                # battery
                widget.TextBox("", fontsize=12, padding=6, foreground='#91d7e3'),
                widget.Battery(
                    foreground='#91d7e3',
                    low_percentage=0.2,
                    low_foreground='DF2E38',
                    format='{percent:2.0%}',
                    padding=6,
                    full_char='Charged',
                ),

                # volume
                widget.TextBox("󰕾", fontsize=12, padding=4, foreground='#89b4fa'),
                widget.Volume(
                    foreground='#89b4fa',
                    padding=2,
                    mute_format = 'Muted',
                ),

            widget.TextBox(
                text='󰃠',  # ícono de brillo (también: 󰛨 o 󰖨)
                fontsize=12,
                padding=4,
                foreground='#f9e2af'
            ),
            widget.Backlight(
                backlight_name='amdgpu_bl1',  # puede variar según tu hardware
                format='{percent:2.0%}',
                foreground='#f9e2af',
                padding=4
            ),

            widget.TextBox(
                text='',  # ícono de memoria RAM (también puedes usar: 󰘚 o 󰾆)
                fontsize=12,
                padding=4,
                foreground='#cba6f7'  # color que combine con tu paleta
            ),
            widget.Memory(
                foreground='#cba6f7',
                format='{MemUsed:.1f}GB',  # muestra memoria usada en GB
                padding=4,
                measure_mem='G'  # garantiza consistencia en GIGAS
            ),

            widget.TextBox(
                text='󰍛',  # ícono de CPU (alternativas: 󰘚 o )
                fontsize=12,
                padding=4,
                foreground='#cba6f7'
            ),
            widget.CPU(
                format='{load_percent}%',
                foreground='#cba6f7',
                padding=4
            ),



            ],
            26,
            margin = [4,4,0,4],
            # border_width=[2, 0, 2, 0],  # Draw top and bottom borders
            # border_color=["ff00ff", "000000", "ff00ff", "000000"]  # Borders are magenta
            background='#24273a',
        ),
    ),
]


