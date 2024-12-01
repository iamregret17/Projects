import tkinter as tk
import ttkbootstrap as ttk
from ttkbootstrap.tooltip import ToolTip
from pathlib import Path
import queue
from events import handle_spinbox_event, handle_combobox_event, theme_combobox_callback
from configure import configure_combobox, configure_spinbox
from theme import remove_highlights
from sound import sound_init, sound_combobox_callback
from window import change_window, position_window
from file import select_file
from file import get_sound_path

# constants
WINDOW_WIDTH: int = 350
WINDOW_HEIGHT: int = 250


def main():
    window: ttk.Window = ttk.Window()
    window.title("Eye Break Reminder")
    window.bind("<Control-w>", lambda e: window.destroy())
    window.resizable(0, 0)  # window unresizable

    # Initial window position
    position_window(window, WINDOW_WIDTH, WINDOW_HEIGHT)
    window.iconbitmap("images/eye.ico")

    # Configure the grid
    window.columnconfigure((0, 1, 2), weight=1)

    # list the sound files with path
    supported_sounds: list[str] = list(Path("sounds/").glob("*.*"))
    if not supported_sounds:
        supported_sounds.append(Path("."))

    # variables
    style: ttk.Style = ttk.Style()
    sound_queue: queue.Queue = queue.Queue()
    theme_names: list[str] = style.theme_names()

    # tk variables
    theme_name_var: tk.StringVar = tk.StringVar(value=theme_names[0])
    popup_sound_var: tk.StringVar = tk.StringVar(value=supported_sounds[0].stem)
    popup_interval_var: tk.IntVar = tk.IntVar(value=20)
    popup_duration_var: tk.IntVar = tk.IntVar(value=20)

    # sounds
    sound_init(sound_queue)

    # header
    app_label: ttk.Label = ttk.Label(
        window, text="Configure Settings", font=("Georgia", 12)
    )
    app_label.grid(row=0, columnspan=3, pady=10)

    # tooltip
    tooltip_label: ttk.Label = ttk.Label(window, text="🛈", font=("Calibri, 15"))
    tooltip_label.grid(row=0, column=0, sticky="w", padx=15)
    ToolTip(
        tooltip_label,
        bootstyle="selectfg-inverse",
        text="Supported extensions\nare wav, mp3 and ogg",
    )

    # frame 1 -------------------------------------------------------------------->
    theme_label: ttk.Label = ttk.Label(window, text="Theme")
    theme_combobox = ttk.Combobox(window)
    configure_combobox(theme_combobox, theme_names, var=theme_name_var)

    theme_label.grid(row=1, column=0, pady=2, sticky="e")
    theme_combobox.grid(row=1, column=1, padx=10, pady=2, sticky="w")
    handle_combobox_event(
        theme_combobox,
        lambda e: theme_combobox_callback(theme_combobox, style, theme_name_var),
    )

    # frame 2 -------------------------------------------------------------------->
    sound_label: ttk.Label = ttk.Label(window, text="Popup Sound")
    import_sound_button: ttk.Button = ttk.Button(window, text="+", command=select_file)
    sound_combobox: ttk.Combobox = ttk.Combobox(window)
    configure_combobox(
        sound_combobox, [file.stem for file in supported_sounds], popup_sound_var
    )

    sound_label.grid(row=2, column=0, pady=2, sticky="e")
    import_sound_button.grid(row=2, column=1, pady=2, padx=11, sticky="e")
    sound_combobox.grid(row=2, column=1, padx=10, pady=2, sticky="w")
    handle_combobox_event(
        sound_combobox,
        lambda e: sound_combobox_callback(
            sound_queue, sound_combobox, style, popup_sound_var
        ),
    )

    # frame 3 -------------------------------------------------------------------->
    interval_label: ttk.Label = ttk.Label(window, text="Popup Interval")
    interval_unit_label: ttk.Label = ttk.Label(window, text="minutes")
    interval_spinbox: ttk.Spinbox = ttk.Spinbox(window)
    configure_spinbox(interval_spinbox, style, popup_interval_var)

    interval_label.grid(row=3, column=0, pady=2, sticky="e")
    interval_spinbox.grid(row=3, column=1, padx=10, pady=2, sticky="w")
    interval_unit_label.grid(row=3, column=1, pady=2, padx=15, sticky="se")
    handle_spinbox_event(
        interval_spinbox, lambda e: remove_highlights(interval_spinbox, style)
    )

    # frame 4 -------------------------------------------------------------------->
    duration_label: ttk.Label = ttk.Label(window, text="Popup Duration")
    duration_unit_label: ttk.Label = ttk.Label(window, text="seconds")
    duration_spinbox: ttk.Spinbox = ttk.Spinbox(window)
    configure_spinbox(duration_spinbox, style, popup_duration_var)

    duration_label.grid(row=4, column=0, pady=2, sticky="e")
    duration_spinbox.grid(row=4, column=1, padx=10, pady=2, sticky="w")
    duration_unit_label.grid(row=4, column=1, pady=2, padx=15, sticky="se")
    handle_spinbox_event(
        duration_spinbox, lambda e: remove_highlights(duration_spinbox, style)
    )

    # button -------------------------------------------------------------------->
    start_button: ttk.Button = ttk.Button(
        window,
        text="start",
        command=lambda: change_window(
            window, get_sound_path(), popup_interval_var, popup_duration_var
        ),
    )
    start_button.grid(row=5, columnspan=3, pady=7)

    window.mainloop()


if __name__ == "__main__":
    main()
