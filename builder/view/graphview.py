import tkinter as tk


class GraphView:
    def __init__(self):
        self.width = 800
        self.height = 600

        window = tk.Tk()
        window.geometry(f"{self.width}x{self.height}")
        window.resizable(False, False)
        self.window = window

        canvas = tk.Canvas(window, width=self.width, height=self.height, borderwidth=0, highlightthickness=0,
                           bg="black")
        canvas.grid()
        self.canvas = canvas

        self.create_circle(100, 120, 50, fill="blue", outline="#DDD", width=4)
        # self.create_circle_arc(100, 120, 48, fill="green", outline="", start=45, end=140)
        # self.create_circle_arc(100, 120, 48, fill="green", outline="", start=275, end=305)
        # self.create_circle_arc(100, 120, 45, style="arc", outline="white", width=6, start=270 - 25, end=270 + 25)
        self.create_circle(150, 40, 20, fill="#BBB", outline="")

        window.wm_title("Graph")
        window.mainloop()

    def create_circle(self, x, y, r, **kwargs):
        self.canvas.create_oval(x - r, y - r, x + r, y + r, **kwargs)

    def create_circle_arc(self, x, y, r, **kwargs):
        if "start" in kwargs and "end" in kwargs:
            kwargs["extent"] = kwargs["end"] - kwargs["start"]
            del kwargs["end"]
        return self.canvas.create_arc(x - r, y - r, x + r, y + r, **kwargs)


if __name__ == '__main__':
    GraphView()
