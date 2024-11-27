import tkinter as tk
import ttkbootstrap as ttk

MIN_VALUE: int = 5
MAX_VALUE: int = 60
INCREMENT: int = 5


def configure_combobox(
    combobox: ttk.Combobox, values: list[str], var: tk.StringVar
) -> None:
    combobox.configure(
        width=9,
        state="readonly",
        style="TCombobox",
        values=values,
        textvariable=var,
    )


def configure_spinbox(
    spinbox: ttk.Spinbox, style: ttk.Style, var: tk.StringVar
) -> None:
    spinbox.configure(
        from_=MIN_VALUE,
        to=MAX_VALUE,
        increment=INCREMENT,
        width=4,
        wrap=True,
        state="readonly",
        style="TSpinbox",
        textvariable=var,
    )
