# board.msg
#Header header

# Information from each cell in the board
# Index of each cell in the array:
#            _ _ _ _ _ _
#           |_0_|_1_|_2_|
#           |_3_|_4_|_5_|
#           |_6_|_7_|_8_|
#
# Possible values:
#       0=empty cell
#       1=player1 token (X)
#       2=player2 token (O)
# Nine positions for the board [0-8]
uint8[9] data
