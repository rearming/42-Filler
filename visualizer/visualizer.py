import re
import sys
from tkinter import *
from tkinter import font
import random

def exit_esc(event):
    exit(21)


def get_players_names():
    _names = []
    for line in sys.stdin:
        raw_name = re.match(r"\$\$\$ exec p\d : \[.*?([a-zA-Z]+\.filler)\]", line)
        if raw_name:
            _names.append(raw_name.group(1))
        if len(_names) == 2:
            return _names


def get_map_size():
    for line in sys.stdin:
        map_size_str = re.match("Plateau ([0-9]+) ([0-9]+):", line)
        if map_size_str:
            return int(map_size_str.group(2)), int(map_size_str.group(1))


def get_all_maps(size_y):
    _maps = []
    _score = []
    while 21:
        _map = []
        for line in sys.stdin:
            match = re.match(r"[0-9]+ ([.oOxX]+)", line)
            if match:
                _map.append(match.group(1))
            raw_score = re.match(r"== [OX] fin: (\d+)", line)
            if raw_score:
                _score.append(raw_score.group(1))
            if len(_map) == size_y:
                break
        if _map:
            _maps.append(_map)
        if not _map:
            return _maps, _score


def get_square_size(size_x, size_y):
    window.update()
    print("canvas: ", canvas.winfo_width(), canvas.winfo_height())
    return min(canvas.winfo_width() / size_x, canvas.winfo_height() / size_y) / 1.5


def get_color(char):
    colors = {"O": "medium blue", "o": "royal blue", "X": "forest green", "x": "lime green", ".": "ghost white"}
    return colors[char]


def get_rand_color():
    colors = ["red", "blue"]
    return colors[random.randint(0, 1)]


def draw_player_names(names):
    print(names)
    players_font = font.Font(family="Times", size=30, weight="bold")
    vs_font = font.Font(family="Times", size=40)
    p1_label = Label(window, text=names[0], font=players_font)
    p2_label = Label(window, text=names[1], font=players_font)
    vs_label = Label(window, text="vs", font=vs_font)
    p1_label.grid(row=0, column=0, sticky=W)
    vs_label.grid(row=0, column=1)
    p2_label.grid(row=0, column=2, sticky=E)


def redraw_map(_map, squares):
    i = 0
    for y in range(len(_map)):
        for x in range(len(_map[y])):
            canvas.itemconfig(squares[i], fill=get_color(_map[y][x]))
            i += 1
    window.update()
    # window.after(200)


def make_map(size_x, size_y, square_size):
    squares = []
    for y in range(size_y):
        for x in range(size_x):
            x1 = x * square_size
            y1 = y * square_size
            x2 = (x + 1) * square_size
            y2 = (y + 1) * square_size
            squares.append(canvas.create_rectangle(x1, y1, x2, y2, fill="ghost white"))
    return squares


def visualize(_maps, size_x, size_y):
    squares = make_map(size_x, size_y, get_square_size(size_x, size_y))
    window.update()
    for _map in _maps:
        redraw_map(_map, squares)


def main():
    draw_player_names(get_players_names())
    size_x, size_y = get_map_size()

    _maps, score = get_all_maps(size_y)
    visualize(_maps, size_x, size_y)

    print(score)


window = Tk()
screen_width = window.winfo_screenwidth()
screen_height = window.winfo_screenheight()
window.geometry(str(screen_width) + "x" + str(screen_height))
canvas = Canvas(window, width=screen_width, height=screen_height)  # todo a little bit smaller canvas
canvas.grid(row=1, column=0)
window.bind("<Escape>", exit_esc)

main()

window.mainloop()
