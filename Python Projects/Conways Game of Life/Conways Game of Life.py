# File:        proj1.py
# Author:      Chris Jimenez
# Date:        11/8/15
# Section:     20
# Email:       fp42134@umbc.edu
# Description: This program asks the user for dimensions of a game board, cells of the board to
#              turn on, and produces new versions of the board based on the previous board.

def makeNewBoard(newBoard, rows, columns):

    for i in range(0, rows):
        rowList = []
        for j in range(0, columns):
            rowList.append(".")
        newBoard.append(rowList)
    return newBoard

def isAlive(boardList, rows, columns, row, column):

    counter = 0

    if boardList[row - 1][column - 1] == "A":
        counter += 1

    if boardList[row - 1][column] == "A":
        counter += 1

    if(column + 1) < columns:
        if boardList[row - 1][column + 1] == "A":
            counter += 1

    if boardList[row][column - 1] == "A":
        counter += 1

    if(column + 1) < columns:
        if boardList[row][column + 1] == "A":
            counter += 1

    if(row + 1) < rows:
        if boardList[row + 1][column - 1] == "A":
            counter += 1
    
    if(row + 1) < rows:
        if boardList[row + 1][column] == "A":
            counter += 1

    if(row + 1) < rows and (column + 1) < columns:
        if boardList[row + 1][column + 1] == "A":
            counter += 1

    return counter

def iterateBoardList(boardList, rows, columns, newBoard):

    # any live cell with fewer than two neighbors dies
    # any live cell two or three live neighbors lives to the next generation
    # any live cell with more than three live neighbors dies
    # any dead cell with exactly three live neighbors becomes a live cell

    makeNewBoard(newBoard, rows, columns)

    for row in range(0, len(boardList)):

        for column in range(0, len(boardList[row])):

            if boardList[row][column] == ".":

                if isAlive(boardList, rows, columns, row, column) == 3:
                    newBoard[row][column] = "A"

            elif boardList[row][column] == "A":

                if (isAlive(boardList, rows, columns, row, column) == 2) or (isAlive(boardList, rows, columns, row, column) == 3):
                    newBoard[row][column] = "A"

                elif isAlive(boardList, rows, columns, row, column) < 2 or isAlive(boardList, rows, columns, row, column) > 3:
                    newBoard[row][column] = "."

    boardList = newBoard[:]
    return(newBoard)
                
def printBoard(boardList):

    for i in boardList:
        for j in i:
            print(j, end = "")
        print()
    print("\n")

def main():

    rows = int(input("Please enter number of rows:\t"))
    while rows < 1:
        rows = int(input("\tThat is not a valid value; please enter a number\n\tgreater than or equal to 1\nPlease enter number of rows:\t"))

    columns = int(input("Please enter number of columns:\t"))
    while columns < 1:
        columns = int(input("\tThat is not a valid value; please enter a number\n\tgreater than or equal to 1\nPlease enter number of rows:\t"))

    boardList = []

    for i in range(0, rows):
        rowList = []
        for j in range(0, columns):
            rowList.append(".")
        boardList.append(rowList)

    getRow = ""
    while getRow != "q":
        getRow = input("\nPlease enter the row of a cell to turn on (or q to exit): ")

        if getRow == "q":
            break
        if getRow != "q":
            getRow = int(getRow)

        while (getRow < 0) or (getRow > (rows - 1)):
            getRow = input("\tThat is not a valid value; please enter a number\n\tbetween 0 and {} inclusive...\nPlease enter the row of a cell to turn on (or q to exit): ".format(rows - 1))
            if getRow != "q":
                getRow = int(getRow)

        if getRow != "q":
            getColumn = int(input("Please enter a column for that cell: "))
            while (getColumn < 0) or (getColumn > (columns - 1)):
                getColumn = int(input("\tThat is not a valid value; please enter a number\n\tbetween 0 and {} inclusive...\nPlease enter the column of a cell to turn on (or q to exit): ".format(columns - 1)))
                
        boardList[getRow][getColumn] = "A"

    iterations = int(input("\nHow many iterations should I run? "))
    while iterations < 0:
        iterations = int(input("\tThat is not a valid value; please enter a number\n\tgreater than or equal to 0\n\nHow many iterations should I run? "))

    print("Starting board:\n")
    printBoard(boardList)

    for iteration in range(1, iterations + 1):
        newBoard = []
        boardList = iterateBoardList(boardList, rows, columns, newBoard)
        print("Iteration {}:\n".format(iteration))
        printBoard(boardList)

main()
