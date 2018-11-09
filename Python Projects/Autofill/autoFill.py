# File:        proj2.py
# Author:      Chris Jimenez
# Date:        12/3/15
# Section:     20
# Email:       fp42134@umbc.edu
# Description: This program uses a recursive autofill function to fill in blanks on grid.
#
#			   Grade recieved: 100/100

def blankGrid(gridFile):

    gridList = []
    gridFileRead = open(gridFile, 'r')

    for row in gridFileRead:
        rowList = []
        for cell in row:
            rowList.append(cell)
        gridList.append(rowList)
    return gridList

def printGrid(gridList):

    for row in gridList:
        for cell in row:
            print(cell, end = "")
    print()

def getCoords(rowLength, columnLength):

    # Get coordinates to start filling
    fillCoord = input("Please enter the coordinates you would like to start\nfilling at in the form 'row,col', or Q to quit: ")
    if fillCoord == "Q":
        print("Thank you for using the autofill program!")
        import sys
        sys.exit()

    # Split the user's coordinates into a list and cast to integers
    coordList = fillCoord.split(",")
    row = int(coordList[0])
    column = int(coordList[1])

    # While either coordinate is out of range
    while (not 0 <= row < columnLength) or (not 0 <= column < rowLength - 1):
        
        if not 0 <= row < columnLength:
            # Print this if row is wrong
            print("\t{} is not a valid row value; please enter a number\n\tbetween 0 and".format(row), (columnLength - 1), "inclusive.")

        if not 0 <= column < rowLength:
            # Print this if column is wrong
            print("\t{} is not a valid column value; please enter a number\n\tbetween 0 and".format(column), (rowLength - 1), "inclusive.")
        # Or print both statements if both are wrong

        # Retry fillCoord
        fillCoord = input("Please enter the coordinates you would like to fill at\n\tin the form 'row,col': ")
        if fillCoord == "Q":
            print("Thank you for using the autofill program!")
            import sys
            sys.exit()
        coordList = fillCoord.split(",")
        row = int(coordList[0])
        column = int(coordList[1])

    return row, column

def fillGrid(gridList, row, column, fillSymbol, showSteps):

    if gridList[row][column] == " ":
        gridList[row][column] = fillSymbol
        if showSteps == "yes":
            print()
            printGrid(gridList)

        # Top
        if gridList[row - 1][column] == " ":
            fillGrid(gridList, row - 1, column, fillSymbol, showSteps)

        # Right
        if gridList[row][column + 1] == " ":
            fillGrid(gridList, row, column + 1, fillSymbol, showSteps)

        # Bottom
        if gridList[row + 1][column] == " ":
            fillGrid(gridList, row + 1, column, fillSymbol, showSteps)

        # Left
        if gridList[row][column - 1] == " ":
            fillGrid(gridList, row, column - 1, fillSymbol, showSteps)

        return gridList

def main():

    gridFile = input("Please enter a file for input: ")
    while (gridFile[-4:] != ".txt") and (gridFile[-4:] != ".dat"):
        gridFile = input("That is not a valid filemane -- please enter a filename\n\tthat ends in '.dat' or '.txt': ")

    # Make 2D list of blank grid from input file
    gridList = blankGrid(gridFile)

    # Print the blank grid
    printGrid(gridList)

    rowLength = len(gridList[-1])
    columnLength = len(gridList)

    # Loops until the user enters "Q" to quit, couldn't find anywhere in the prompt that said to stop the program once the board is full
    while 1 == 1:

        # Ask for coordinates to start filling from
        fillCoord = getCoords(rowLength, columnLength)
        row = fillCoord[0]
        column = fillCoord[1]

        # Ask for symbol
        fillSymbol = input("Please enter a symbol to fill with: ")
        while len(fillSymbol) != 1:
            print("\tThe symbol '{}' is not a single character.".format(fillSymbol))
            fillSymbol = input("Please enter a symbol to fill with: ")

        # Ask if want to see steps
        showSteps = input("Would you like to show each step of the recursion?\nEnter 'yes' or 'no': ")
        while (showSteps != "yes") and (showSteps != "no"):
            print("The choice '{}' is not valid.".format(showSteps))
            showSteps = input("Would you like to show each step of the recursion?\nEnter 'yes' or 'no': ")

        # If the user's coordinates are on a border, do nothing and print the grid as it is
        if gridList[row][column] != " ":
            print("\n============================================\n")
            printGrid(gridList)
            print()
        else:
            # Fill the grid starting from the coordinates
            fillGrid(gridList, row, column, fillSymbol, showSteps)
            print("\n============================================\n")
            printGrid(gridList)
            print()

main()
