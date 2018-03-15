from Tkinter import *
import tkMessageBox
import copy
from operator import itemgetter
from decimal import Decimal

winning_combination = []

class Tic_Tac_Toe:
	buttons = []

	def __init__(self, N):
		global winning_combination
		self.size = N
		k = 0
		for j in range(self.size):
			temp = []
			for i in range(self.size):
				temp.append(i + k)
			k += N
			winning_combination.append(temp)
		#print winning_combination

		p = [[0 for i in range(self.size)] for j in range(self.size)]
		for i in range(self.size):
			for j in range(self.size):
				p[i][j] = winning_combination[j][i]
		l = [[0 for i in range(self.size)] for j in range(2)]
		for i in range(self.size):
			for j in range(self.size):
				if i == j:
					l[0][j] = winning_combination[i][j]
		for i in range(self.size):
			for j in range(self.size):
				if (i + j) == self.size - 1:
					l[1][i] = winning_combination[i][j]
		winning_combination = winning_combination + p + l


		self.board = [" "] * self.size**2
		self.moves = [StringVar() for _ in xrange(self.size**2)]
		self.x_wins = 0
		self.o_wins = 0
		self.current_player = "X"
		self.move_number = 0
		self.winning_s = []
		self.game_over = False

		self.apply_to_each(lambda x: x.set(" "), self.moves)

	# make_move
	def make_move(self, move):
		computer_on.config(state = 'disabled')
		self.move_number += 1
		if self.current_player == "X":
			self.board[move] = "X"
			info_text.set("It is O's turn")
			self.current_player = "O"
		# If computer mode is ON, tell the computer to take it's turn
			if computer.get() and self.move_number < 9:
				self.computer_move()
		else:
			self.board[move] = "O"
			info_text.set("It is X's turn")
			self.current_player = "X"

		if self.game_over:
			return
		self.buttons[move].config(state = "disabled")

		#check for win
		winner = self.game_won(self.board)
		if winner is not None:
			self.who_won(winner)
			self.game_over = True
		elif self.move_number == self.size**2 and self.board_full(self.board):
			self.apply_to_each(lambda x: x.config(disabledforeground = "blue"), self.buttons)
			self.game_over = True
			tkMessageBox.showinfo("GAME TIE", "Ooh! seems like no-one lose!")

		self.update_board()

	def apply_to_each(self, func, _list):
		for i in _list:
			func(i)

	def any_return(self, it):
		for i in it:
			if i:
				return i
		return False

	def who_won(self, winner):
		if winner == "X":
			info_text.set("X wins!")
			tkMessageBox.showinfo("WINNER X", "Congratulations! X has won the game.")
			self.x_wins += 1
		else:
			info_text.set("O wins!")
			tkMessageBox.showinfo("WINNER O", "Congratulations! O has won the game.")
			self.o_wins += 1

		count.set("X: " + str(self.x_wins) + "\tO: " + str(self.o_wins))

		self.apply_to_each(lambda x: x.config(disabledforeground = "blue"), 
								[self.buttons[s] for s in self.winning_s])

		for b in self.buttons:
			b.config(state = "disabled")

	def reset(self):
		computer_on.config(state = 'normal')
		self.current_player = "X"
		self.move_number = 0
		self.game_over = False

		info_text.set("It is X's turn")

		self.board = [" " for _ in self.board]
		self.update_board()

		for b in self.buttons:
			b.config(state = "normal")
			b.config(disabledforeground = "black")

	def update_board(self):
		for i in xrange(self.size**2):
			self.moves[i].set(self.board[i])

	def game_won(self, gameboard):
		check = self.any_return([self.in_row(gameboard, c) for c in winning_combination])
		if check:
			return check
		else:
			return None

	def in_row(self, gameboard, s):
		
		_set = set()
		for i in range(self.size):
			_set.add(gameboard[s[i]])
		if len(_set) == 1 and _set.pop() != " ":
			self.winning_s = s
			return gameboard[s[0]]
		else:
			return None

	def get_opponent(self, current_player):
		if current_player == "X":
			return "O"
		else:
			return "X"

	def board_full(self, board):
		for i in board:
			if i == " ":
				return False
		return True

	def computer_move(self):
		player = "O"
		a = Decimal('-Infinity')
		b = Decimal('Infinity')

		board_copy = copy.deepcopy(self.board)
		best = -100
		best_move = None
		for i in xrange(self.size**2):
			# print board_copy
			if board_copy[i] == " ":
				board_copy[i] = player
				val = self.minmax(self.get_opponent(player), board_copy, a, b)
				board_copy[i] = " "
				if player == "O":
					if val > best:
						best = val
						best_move = i
				else:
					if val < best:
						best = val
						best_move = i;

		self.make_move(best_move)
	def minmax(self, player, board, a, b):
	
		board_copy = copy.deepcopy(board)
		# Check for a win
		# print board_copy
		winner = self.game_won(board_copy)
		if winner == "O":
			return 1
		elif winner == "X":
			return -1
		elif self.board_full(board_copy):
			return 0

		if player == "O":
			best_result = -100
		else:
			best_result = 100

		for i in xrange(self.size**2):
			if board_copy[i] == " ":
				board_copy[i] = player
				val = self.minmax(self.get_opponent(player), board_copy, a, b)
				board_copy[i] = " "
				if player == "O":
					best_result = max(best_result, val)
					a = min(a, best_result)
				else:
					best_result = min(best_result, val)
					b = max(b, best_result)

				if b <= a:
					return best_result

		return best_result

master = Tk()
master.title("TIC-TAC-TOE GAME")

N = input("Enter Size: ")

game = Tic_Tac_Toe(N)

# toshow the current scores

count = StringVar()
count.set("X : " + str(game.x_wins) + "\tO : " + str(game.o_wins))
l = Label(master, textvariable = count)
l.grid(row = 0, column = 1)

#create Button

for i in xrange(N**2):
	temp = Button(master, textvariable = game.moves[i], command = lambda s = i: game.make_move(s))
	temp.grid(row = (i / N) + N, column = (i % N), sticky = NSEW)
	game.buttons.append(temp)

#button for resetting the game

reset_button = StringVar()
reset_button.set("Reset")
reset = Button(master, textvariable = reset_button, command = game.reset)
reset.grid(row = 0, column = 0)

# Label used to give the user information
info_text = StringVar()
info_text.set("It is X's turn")
info = Label(master, textvariable = info_text)
info.grid(row = 2, column = 0, columnspan = 3)


#selecting modes

computer = IntVar()
computer_on = Checkbutton(master, text = "Computer", variable = computer)
computer_on.grid(row = 0, column = 2)

# Set the size of the rows and columns

for i in xrange(N**2):
	master.columnconfigure(i % N, minsize = 100)
	master.rowconfigure((i % N) + N, minsize = 100)

master.mainloop()
