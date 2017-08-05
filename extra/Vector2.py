from math import sqrt

class Vector2:
    """ Simple Vector2 class. """

    # --------------------------------------------------------------------------
    # Constructors
    # --------------------------------------------------------------------------
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    # --------------------------------------------------------------------------
    # General functions
    # --------------------------------------------------------------------------
    def length(self):
        """ Returns length of this vector. """
        return sqrt(self.squareLength())

    def squareLength(self):
        """ Returns square length of this vector. """
        return (self.x**2) + (self.y**2)

    def normalize(self):
        """ Returns a normalized version of this vector.
            If length is 0, null vector returned. (All elements set to 0). """
        l = self.length()
        if (l==0): return Vector2(0,0)
        return Vector2(self.x/l, self.y/l)

    # --------------------------------------------------------------------------
    # Operator functions
    # --------------------------------------------------------------------------
    def multiply(self, s):
        """ Returns a new version of this vector multiplied by s. """
        return Vector2(self.x*s, self.y*s)

    def divide(self, s):
        """ Returns a new version of this vector divided by s.
            If s is 0, return null vector (All elements set to 0).  """
        if (s==0): return Vector2(0,0)
        return Vector2(self.x/s, self.y/s)

    def add(self, v):
        """ Returns a new version of this vector added with another vector v. """
        return Vector2(self.x+v.x, self.y+v.y)

    def sub(self, v):
        """ Returns a new version of this vector minus another vector v. """
        return Vector2(self.x-v.x, self.y-v.y)

    # --------------------------------------------------------------------------
    # Operations with other vectors
    # --------------------------------------------------------------------------
    def equals(self, v):
        """ Checks whether this vector components are equal to v components. """
        return  self.x == v.x and self.y == v.y

    def dot(self, v):
        """ Returns the dot product of this vector. """
        return (self.x * v.x) + (self.y * v.y)
