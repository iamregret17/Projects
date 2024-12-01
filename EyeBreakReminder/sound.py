import os

os.environ["PYGAME_HIDE_SUPPORT_PROMPT"] = "hide"
from pygame import mixer
from tkinter import ttk
import tkinter as tk
import threading
import queue
from theme import remove_highlights
from file import set_sound_path


def sound_init(sound_queue: queue.Queue[str]) -> None:
    # Initialize mixer
    mixer.init(frequency=44100, size=-16, channels=2, buffer=512)
    worker_thread = threading.Thread(
        target=lambda: play_sound_worker(sound_queue), daemon=True
    )
    worker_thread.start()


def sound_combobox_callback(
    sound_queue: queue.Queue[str],
    combobox: ttk.Combobox,
    style: ttk.Style,
    popup_sound_var: tk.StringVar,
) -> None:
    remove_highlights(combobox, style)
    soundpath = f"sounds/{popup_sound_var.get()}.mp3"
    sound_queue.put(soundpath)
    set_sound_path(soundpath)


def play_sound_worker(sound_queue: queue.Queue[str]) -> None:
    while True:
        soundpath = sound_queue.get()
        if soundpath is None:
            break
        mixer.music.load(str(soundpath))
        mixer.music.play()
        sound_queue.task_done()
