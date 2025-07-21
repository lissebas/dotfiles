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
                    active='#CAA9E0',
                    block_highlight_text_color="#91B1F0",
                    highlight_color='#4B427E',
                    inactive='#282738',
                    foreground='#4B427E',
                    background='#353446',
                    this_current_screen_border='#353446',
                    this_screen_border='#353446',
                    other_current_screen_border='#353446',
                    other_screen_border='#353446',
                    urgent_border='#353446',
                    rounded=True,
                    disable_drag=True,
                ),

                widget.Spacer(),
                
                # time
                widget.Clock(format="%I:%M - %d %b", foreground='#fab387',padding=6),

                # NB Systray is incompatible with Wayland, consider using StatusNotifier instead
                # widget.StatusNotifier(),
                widget.Spacer(),


                # network
                widget.TextBox("", fontsize=14, padding=6, foreground='#a6e3a1'),
                widget.Wlan(
                    foreground='#a6e3a1',
                    padding=6,
                    interface='wlan0',
                    format='{essid}'
                ),

                # battery
                widget.TextBox("󱘖", fontsize=14, padding=6, foreground='#89dceb'),
                widget.Battery(
                    foreground= '#89dceb',
                    low_percentage= 0.2,
                    low_foreground= 'DF2E38',
                    format= '{percent:2.0%}',
                    padding= 6,
                    full_char= 'Charged',


                ),

                # volume 
                
                widget.TextBox("󰕾", fontsize=12, padding=4, foreground='#89b4fa'),
                widget.Volume(foreground='#89b4fa',
                              padding=2,
                ),



            ],
            26,
            margin = [4,4,0,4],
            # border_width=[2, 0, 2, 0],  # Draw top and bottom borders
            # border_color=["ff00ff", "000000", "ff00ff", "000000"]  # Borders are magenta
            background='#2E3440',
        ),
    ),
]


