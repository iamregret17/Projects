from tkinter import filedialog as fd
from tkinter.messagebox import showwarning, showerror
from pygame import mixer, error

SUPPORTED_FORMATS: set[str] = {"wav", "mp3", "ogg"}
audio_path: str = "sounds\\tuturu.mp3"


def set_sound_path(path: str) -> None:
    global audio_path
    audio_path = path


def get_sound_path() -> str:
    global audio_path
    return audio_path


def play_sound(sound_path: str) -> None:
    mixer.music.load(sound_path)
    mixer.music.play()


def play_sound_check(sound_path: str) -> None:
    try:
        mixer.music.load(sound_path)
        mixer.music.play()
        set_sound_path(sound_path)
    except Exception:
        sound_path = sound_path.split("/")
        error_message: str = (
            f"{sound_path[-1]} appears to be corrupted or partially unreadable.\nPlease verify the file's integrity and try again."
        )
        showerror("Unable to play audio file", message=error_message)


def select_file() -> None:
    filetypes = (("Audio files", "*.mp3 *.wav *.ogg"), ("All files", "*.*"))
    file_path: str = fd.askopenfilename(
        title="Open a file", initialdir="/", filetypes=filetypes
    )
    if file_path:  # Check if a file was selected
        audio_extension: str = file_path.split(".")[-1]
        if audio_extension not in SUPPORTED_FORMATS:
            showwarning(
                title="Unsupported Format",
                message="Supported extensions are wav, mp3 and ogg.",
            )
        else:
            play_sound_check(file_path)
