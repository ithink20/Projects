

"""
	0 | 1 | 2
	3 | 4 | 5
	6 | 7 | 8

"""

board = [" ", " ", " ", " ", " ", " ", " ", " ", " ",]

def printBoard():
	print "    |    |    "
	print " " + board[0] + "  | " + board[1] + "  | " + board[2] + " "
	print "    |    |    "
	print "----|----|----"
	print "    |    |    "
	print " " + board[3] + "  | " + board[4] + "  | " + board[5] + " "
	print "    |    |    "
	print "----|----|----"
	print "    |    |    "
	print " " + board[6] + "  | " + board[7] + "  | " + board[8] + " "
	print "    |    |    "

def main():
	printBoard()
	while True:
		#Player X turn:
		c = int(input("Player X turn : "))
		if board[c] == " ":
			board[c] = "X"
			printBoard()
		else:
			print "False"
			continue

		#check for X wins
		if (board[0] == "X" and board[1] == "X" and board[2] == "X") or\
			(board[3] == "X" and board[4] == "X" and board[5] == "X") or\
			(board[6] == "X" and board[7] == "X" and board[8] == "X") or\
			(board[0] == "X" and board[3] == "X" and board[6] == "X") or\
			(board[1] == "X" and board[4] == "X" and board[7] == "X") or\
			(board[2] == "X" and board[5] == "X" and board[8] == "X") or\
			(board[0] == "X" and board[4] == "X" and board[8] == "X") or\
			(board[2] == "X" and board[4] == "X" and board[6] == "X"):
			print "X wins! "
			break

		#check of tie:
		isFull = True
		if " " in board:
			isFull = False
		if isFull == True:
			print "Tie!"
			break	

		#Player 0 turn:
		c = int(input("Player 0 turn : "))
		if board[c] == " ":
			board[c] = "0"
			printBoard()
		else:
			print "False"
			continue

		#check for 0 wins
		if (board[0] == "0" and board[1] == "0" and board[2] == "0") or\
			(board[3] == "0" and board[4] == "0" and board[5] == "0") or\
			(board[6] == "0" and board[7] == "0" and board[8] == "0") or\
			(board[0] == "0" and board[3] == "0" and board[6] == "0") or\
			(board[1] == "0" and board[4] == "0" and board[7] == "0") or\
			(board[2] == "0" and board[5] == "0" and board[8] == "0") or\
			(board[0] == "0" and board[4] == "0" and board[8] == "0") or\
			(board[2] == "0" and board[4] == "0" and board[6] == "0"):
			print "0 wins! "
			break

		#check of tie:
		isFull = True
		if " " in board:
			isFull = False
		if isFull == True:
			print "Tie!"
			break	
	
	
if __name__ == '__main__':
	main()
