from Tkinter import *

master = Tk()

master.title("TIC TAC TOE")

w = master.geometry("312x400")

label1 = Label(text = "MODE :")
label1.grid(row = 1, column = 0)

two_player = Button(master, text = "Two Player")
two_player.grid(row = 1, column = 1, padx = 10, pady = 10)

computer = Button(master, text = "Computer")
computer.grid(row = 1, column = 2, padx = 10, pady = 20)

def CHECK(b1):
	print "Button Clicked!"

button1 = Button(master, text = " ", height = 4, width = 8, command = lambda: CHECK(button1))
button1.grid(row = 2, column = 0, sticky = N + S + E + W)

button2 = Button(master, text = " ", height = 4, width = 8, command = lambda: CHECK(button2))
button2.grid(row = 2, column = 1, sticky = N + S + E + W)

button3 = Button(master, text = " ", height = 4, width = 8, command = lambda: CHECK(button3))
button3.grid(row = 2, column = 2, sticky = N + S + E + W)

button4 = Button(master, text = " ", height = 4, width = 8, command = lambda: CHECK(button4))
button4.grid(row = 3, column = 0, sticky = N + S + E + W)

button5 = Button(master, text = " ", height = 4, width = 8, command = lambda: CHECK(button5))
button5.grid(row = 3, column = 1, sticky = N + S + E + W)

button6 = Button(master, text = " ", height = 4, width = 8, command = lambda: CHECK(button6))
button6.grid(row = 3, column = 2, sticky = N + S + E + W)

button7 = Button(master, text = " ", height = 4, width = 8, command = lambda: CHECK(button7))
button7.grid(row = 4, column = 0, sticky = N + S + E + W)

button8 = Button(master, text = " ", height = 4, width = 8, command = lambda: CHECK(button8))
button8.grid(row = 4, column = 1, sticky = N + S + E + W)

button9 = Button(master, text = " ", height = 4, width = 8, command = lambda: CHECK(button9))
button9.grid(row = 4, column = 2, sticky = N + S + E + W)

undo = Button(master, text = "Undo")
undo.grid(row = 5, column = 0, padx = 10, pady = 20)

redo = Button(master, text = "Redo")
redo.grid(row = 5, column = 1, padx = 10, pady = 20)

reset = Button(master, text = "Reset")
reset.grid(row = 5, column = 2, padx = 10, pady = 20)

mainloop()