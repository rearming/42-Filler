import random
import re
import sys
from tkinter import *
from tkinter import font


class GameParser:
    __game_str = ""

    __board_size = {}
    __piece_size = {}

    __boards = []
    __pieces = []
    __players_names = []
    __total_scores = {}

    def __init__(self):
        for line in sys.stdin:
            self.__game_str += line
        self.__parse_names()
        self.__parse_board_size()
        self.__parse_boards()
        self.__parse_pieces()
        self.__parse_scores()
    
    def __parse_names(self):
        self.__players_names = re.findall(r"\$\$\$ exec p\d : \[.*?([a-zA-Z]+\.filler)\]", self.__game_str)

    def __parse_board_size(self):
        _groups = re.search(r"Plateau ([0-9]+) ([0-9]+):", self.__game_str).groups()
        self.__board_size["x"] = int(_groups[1])
        self.__board_size["y"] = int(_groups[0])

    def __parse_boards(self):
        raw_boards = re.findall(r"\d+ ([\.xXoO]+)\n", self.__game_str)
        _board = []
        for line_i in range(len(raw_boards)):
            _board.append(raw_boards[line_i])
            if (line_i + 1) % self.__board_size["y"] == 0:
                self.__boards.append(_board.copy())
                _board.clear()

    def __parse_pieces(self):
        raw_pieces = re.findall(r"Piece (\d+) (\d+):((?:\.|\*|\n)+)", self.__game_str)
        get_shape_func = lambda lines : list(filter(None, lines.split("\n")))
        self.__pieces = list(map(lambda piece:  {"x": int(piece[1]), "y": int(piece[0]), "shape": get_shape_func(piece[2])}, raw_pieces))
        self.__piece_size["x"] = max(self.__pieces, key=lambda piece: piece["x"])["x"]
        self.__piece_size["y"] = max(self.__pieces, key=lambda piece: piece["y"])["y"]

    def __parse_scores(self):
        raw_scores = re.findall(r"== (X|O) fin: (\d+)", self.__game_str)
        self.__total_scores = list(map(lambda fin: {"player": fin[0], "score": fin[1]}, raw_scores))

    def get_board_size(self):
        return self.__board_size
    
    def get_boards(self):
        return self.__boards

    def get_pieces(self):
        return self.__pieces

    def get_players_names(self):
        return self.__players_names

    def get_total_scores(self):
        return self.__total_scores

    def get_piece_size(self):
        return self.__piece_size


class BoardRenderer:
    __canvas = Canvas
    __board_size = {}
    __rect_size = 0
    __board_rects = []

    def __init__(self, board_size, canv: Canvas):
        self.__board_size = board_size
        self.__canvas = canv

        self.__get_rect_size()
        self.__create_rects()

    def __get_rect_size(self):
        self.__canvas.update()
        print("canvas width:", self.__canvas.winfo_width(), "height:", self.__canvas.winfo_height())
        self.__rect_size = self.__canvas.winfo_height() / self.__board_size["y"]

    def __create_rects(self):
        for y in range(self.__board_size["y"]):
            for x in range(self.__board_size["x"]):
                x1 = x * self.__rect_size
                y1 = y * self.__rect_size
                x2 = (x + 1) * self.__rect_size
                y2 = (y + 1) * self.__rect_size
                self.__board_rects.append(self.__canvas.create_rectangle(x1, y1, x2, y2, fill="ghost white"))

    def redraw(self, _board):
        i = 0
        for y in range(len(_board)):
            for x in range(len(_board[y])): # todo тут все факапится на фигурках, потому что у них размеры с размером поля не совпадают
                self.__canvas.itemconfig(self.__board_rects[i], fill=get_color(_board[y][x]))
                i += 1
        

class PiecesRenderer:
    pass


class Gui:
    __header = []
    __header_size = {}

    __board_canvas = Canvas
    __pieces_canvas = Canvas
    __canvas_frame = Frame

    def __init__(self):
        self.__construct_header()
        self.__header.update()
        self.__header_size = {"height": self.__header.winfo_height(), "width": self.__header.winfo_width()}
        self.__canvas_frame = Frame(window)
        self.__construct_board_canvas()
        self.__construct_pieces_canvas()
        self.__canvas_frame.grid(row=1, column=0, columnspan=2)
        
    def __construct_board_canvas(self):
        board_ratio = parser.get_board_size()["x"] / parser.get_board_size()["y"]
        canvas_height = screen_height - screen_height / 8
        canvas_width = int(canvas_height * board_ratio)
        self.__board_canvas = Canvas(self.__canvas_frame, width=canvas_width, height=canvas_height, \
            highlightbackground="black", highlightthickness=4)
        self.__board_canvas.grid(row=0, column=0, padx=5)

    def __construct_pieces_canvas(self):
        print(parser.get_piece_size())
        board_ratio = parser.get_piece_size()["x"] / parser.get_piece_size()["y"]
        canvas_height = screen_height - screen_height / 8
        canvas_width = int(canvas_height * board_ratio)
        self.__pieces_canvas = Canvas(self.__canvas_frame, width=canvas_width, height=canvas_height, \
            highlightbackground="black", highlightthickness=4)
        self.__pieces_canvas.grid(row=0, column=1, padx=5)

    def __construct_header(self):
        self.__header = Frame(window)

        names = parser.get_players_names()

        players_font = font.Font(family="Times", size=30, weight="bold")
        vs_font = font.Font(family="Times", size=30, weight="bold")

        p1_label = Label(self.__header, text=names[0], font=players_font)
        vs_label = Label(self.__header, text="vs", font=vs_font)
        p2_label = Label(self.__header, text=names[1], font=players_font)

        p1_label.grid(row=0, column=0)
        vs_label.grid(row=0, column=1, padx=int(screen_width / 7))
        p2_label.grid(row=0, column=2)

        self.__header.grid(row=0, column=0, columnspan=3)

    def get_board_canvas(self):
        return self.__board_canvas

    def get_pieces_canvas(self):
        return self.__pieces_canvas


def exit_esc(event):
    exit(21)
    

def get_color(char):
    colors = {"O": "medium blue", "o": "royal blue", "X": "forest green", "x": "lime green", ".": "ghost white", "*": "DeepPink3"}
    return colors[char]


def main():
    gui = Gui()

    board_renderer = BoardRenderer(parser.get_board_size(), gui.get_board_canvas())
    pieces_renderer = BoardRenderer(parser.get_piece_size(), gui.get_pieces_canvas())

    _boards = parser.get_boards()
    _pieces = parser.get_pieces()

    for i in range(len(_boards)):
        board_renderer.redraw(_boards[i])
        print(_boards[i])
        print(_pieces[i]["shape"])
        pieces_renderer.redraw(_pieces[i]["shape"])
        window.update()
        window.after(int(2000))


window = Tk()
screen_width = window.winfo_screenwidth() / 2
screen_height = window.winfo_screenheight() / 2
window.geometry(str(int(screen_width)) + "x" + str(int(screen_height)))
window.bind("<Escape>", exit_esc)

parser = GameParser()
main()

window.mainloop()
