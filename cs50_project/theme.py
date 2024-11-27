import tkinter as tk
from tkinter import ttk


def remove_highlights(box: ttk.Spinbox | ttk.Combobox, style: ttk.Style) -> None:
    style_id = box.cget("style")
    text_color = style.lookup(style_id, "foreground")
    style.configure(style_id, selectbackground="", selectforeground=text_color)


def change_theme(style: ttk.Style, theme_name_var: tk.StringVar) -> None:
    selected_theme = theme_name_var.get()
    style.theme_use(selected_theme)
