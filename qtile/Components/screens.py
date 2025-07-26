from libqtile import widget


def power_line(foreground:str, background = None,
               fontsize = 40, padding = -2):
    
    return widget.TextBox(
        text = '',
        padding = -2,
        fontsize = 40,
        foreground = foreground,
        background = background,
    )


def network_widget(network_status):
  
    return widget.GenPollText(
            func = network_status,
            update_interval = 5,
            background = '#a6e3a1',
            foreground = '#24273a',
            padding = 6,
        )

def sink_widget(get_sink):

    return widget.GenPollText(
            func = get_sink,
            update_interval = 5,
            background = '#89b4fa',
            foreground = '#24273a',
            padding = 6,
        )

