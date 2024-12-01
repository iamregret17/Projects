import tkinter as tk
from tkinter import ttk
from theme import change_theme, remove_highlights


def handle_spinbox_event(spnbox: ttk.Spinbox, callback_function):
    spnbox.bind("<<Increment>>", callback_function)
    spnbox.bind("<<Decrement>>", callback_function)


def handle_combobox_event(cmbbox: ttk.Combobox, callback_function):
    cmbbox.bind("<<ComboboxSelected>>", callback_function)


def theme_combobox_callback(
    combobox: ttk.Combobox, style: ttk.Style, theme_name_var: tk.StringVar
) -> None:
    change_theme(style, theme_name_var)
    remove_highlights(combobox, style)
