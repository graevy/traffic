import numpy as np


class DiamondSquareAlgorithm:
    def __init__(self, side, maxHeight=255):
        """runs the recursion

        Args:
            side (int): length that becomes (2**side-1 -> self.side) an array side
            maxHeight (int, optional): [description]. Defaults to 255.
        """
        self.side = 2**side + 1
        self.max = self.side - 1
        self.maxHeight = maxHeight
        self.terrain = np.zeros((self.side, self.side))

        # initialize array corners to random values
        self.terrain[0,0] =                     np.random.randint(0,maxHeight)
        self.terrain[0,self.max] =              np.random.randint(0,maxHeight)
        self.terrain[self.max,0] =              np.random.randint(0,maxHeight)
        self.terrain[self.max,self.max] =       np.random.randint(0,maxHeight)

        # runs the algorithm
        self.divide(self.max)

    def show(self):
        # suppresses printing in scientific notation with numpy
        np.set_printoptions(suppress=True)
        print(self.terrain)

    def attemptAccess(self, x, y):
        """attempts to get a 2darray element.

        Args:
            x (int): row index
            y (int): column index

        Returns:
            float or int: the element, or 0 on a failed access
        """
        # try/catch is faster than if statements for large arrays, and is most of the runtime. EAFP
        try:
            return self.terrain[x,y]
        except IndexError:
            self.validNeighbors -= 1
            return 0

    def square(self, x, y, size):
        """populates 2darray elements in a square specificed by:

        Args:
            x (int): x coordinate of center of square
            y (int): y coordinate of center of square
            size (int): half of a side of that square
        """
        self.validNeighbors = 4
        top_left = self.attemptAccess(x - size, y - size)
        top_right = self.attemptAccess(x + size, y - size)
        bottom_left = self.attemptAccess(x + size, y + size)
        bottom_right = self.attemptAccess(x - size, y + size)

        average = ((top_left + top_right + bottom_left + bottom_right) // self.validNeighbors)
        self.terrain[x, y] = average

    def diamond(self, x, y, size):
        """populates 2d array elements in a diamond specified by:

        Args:
            x (int): x coordinate of center of diamond
            y (int): y coordinate of center of diamond
            size (int): half the length of the diamond
        """
        """
                T

            L   X   R

                B
        """

        right = self.attemptAccess(x + size, y)
        top = self.attemptAccess(x, y - size)
        left = self.attemptAccess(x - size, y)
        bottom = self.attemptAccess(x, y + size)

        average = ((top + right + bottom + left) // 4)
        self.terrain[x, y] = average

    def divide(self, size):
        """recursive function to call square and diamond steps and fully populate a square 2darray section

        Args:
            size (int): side length of that square section
        """

        x = size // 2
        y = size // 2
        half = size // 2

        if half < 1:
            return

        # Square
        for y in range(half, self.max, size):
            for x in range(half, self.max, size):
                self.square(x, y, half)

        # Diamond
        for y in range(0, self.max + 1, half):
            for x in range((y + half) % size, self.max + 1, size):
                self.diamond(x, y, half)

        self.divide(size // 2) 

if __name__ == "__main__":
    a = DiamondSquareAlgorithm(3, 65535)
    a.show()
