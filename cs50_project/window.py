import tkinter as tk
import ttkbootstrap as ttk
from ttkbootstrap.tooltip import ToolTip
from file import play_sound

COLUMNS = 3
ANIMATION: dict[int, str] = {
    1000: "🫢💤",
    2000: "🤭💤",
    3000: "🥰💞",
    8000: "🥱💤",
    9000: "😪💤",
    10000: "😴💤",
}


def popup_window(
    window: ttk.Window,
    sound_path: str,
    popup_interval: tk.IntVar,
    popup_duration: tk.IntVar,
) -> None:
    popup: ttk.Toplevel = ttk.Toplevel()
    popup.bind("<Control-s>", lambda e: show_main_window(window, popup))
    popup.title("Eye Break Reminder")
    position_window(popup, 350, 100)
    popup.iconbitmap("images/eye.ico")
    play_sound(sound_path)

    # Configure the grid
    popup.columnconfigure((0, 1, 2), weight=1)
    popup.rowconfigure((0, 1, 2, 3), weight=1)

    # variables
    popup_duration_ms: int = popup_duration.get() * 1000
    emoticon_text_var: tk.StringVar = tk.StringVar(value="😴💤")
    animation_done: tk.BooleanVar = tk.BooleanVar(value=False)

    # labels
    emoticon_label: ttk.Label = ttk.Label(
        popup, textvariable=emoticon_text_var, font=("rougant", 20)
    )
    reminder_label: ttk.Label = ttk.Label(
        popup,
        text="LOOK AT SOMETHING 20FT AWAY",
        font=("Arial Rounded MT Bold", 10, "bold"),
    )
    timer_bar: ttk.Progressbar = ttk.Progressbar(
        popup,
        orient="horizontal",
        length=350,
        mode="determinate",
        maximum=popup_duration_ms,
    )

    emoticon_label.grid(row=0, column=0, columnspan=3, sticky="s")
    reminder_label.grid(row=1, column=0, columnspan=3, sticky="s")
    timer_bar.grid(row=3, column=0, sticky="s")

    # tooltip
    tooltip_label: ttk.Label = ttk.Label(popup, text="🛈", font=("Calibri, 15"))
    tooltip_label.grid(row=0, column=0, sticky="nw", padx=10)
    ToolTip(
        tooltip_label,
        bootstyle="selectfg-inverse",
        text="Press Ctrl+S\nfor Settings",
    )

    # emote binding
    emoticon_label.bind(
        "<Button-1>",
        lambda e: start_animation(emoticon_label, emoticon_text_var, animation_done),
    )

    # start timer
    timer_bar.start(1)

    # withdraw the popup window
    popup.after(
        popup_duration_ms + 50,
        lambda: end_popup_window(
            window,
            popup,
            timer_bar,
            sound_path,
            popup_interval,
            popup_duration,
        ),
    )

    popup.mainloop()


def position_window(window: ttk.Window, width: int, height: int):
    screen_width = window.winfo_screenwidth()
    screen_height = window.winfo_screenheight()
    x = screen_width - width - 30
    y = screen_height - height - 100
    window.geometry(f"{width}x{height}+{x}+{y}")


def change_window(
    window: ttk.Window,
    sound_path: str,
    popup_interval: tk.IntVar,
    popup_duration: tk.IntVar,
) -> None:
    window.withdraw()
    window.after(
        popup_interval.get() * 60000,
        lambda: popup_window(window, sound_path, popup_interval, popup_duration),
    )


def reset_popup_window(
    window: ttk.Window,
    popup: ttk.Toplevel,
    sound_path: str,
    popup_interval: tk.IntVar,
    popup_duration: tk.IntVar,
) -> None:
    popup.destroy()
    change_window(window, sound_path, popup_interval, popup_duration)


def end_popup_window(
    window: ttk.Window,
    popup: ttk.Toplevel,
    timer_bar: ttk.Progressbar,
    sound_path: str,
    popup_interval: tk.IntVar,
    popup_duration: tk.IntVar,
) -> None:
    timer_bar.stop()
    timer_bar["value"] = popup_duration.get() * 1000
    play_sound(sound_path)
    popup.after(
        1000,
        lambda: reset_popup_window(
            window, popup, sound_path, popup_interval, popup_duration
        ),
    )


def show_main_window(window: ttk.Window, popup: ttk.Toplevel) -> None:
    window.deiconify()
    popup.destroy()


def start_animation(
    label: ttk.Label, var: tk.StringVar, animation_done: tk.BooleanVar
) -> None:
    if animation_done.get():
        return

    animation_done.set(True)
    var.set("🥱💤")
    for item in ANIMATION:
        label.after(item, lambda i=item: var.set(ANIMATION[i]))

    label.after(10000, lambda: animation_done.set(False))
