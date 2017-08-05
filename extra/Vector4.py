from math import sqrt

class Vector4:
    """ Simple Vector4 class. """

    # --------------------------------------------------------------------------
    # Constructors
    # --------------------------------------------------------------------------
    def __init__(self, x, y, z, w):
        self.x = x
        self.y = y
        self.z = z
        self.w = w

    # --------------------------------------------------------------------------
    # General functions
    # --------------------------------------------------------------------------
    def length(self):
        """ Returns length of this vector. """
        return sqrt(self.squareLength())

    def length3(self):
        """ Returns length of this vector using only x, y, z. """
        return sqrt(self.squareLength3())

    def squareLength(self):
        """ Returns square length of this vector. """
        return (self.x**2) + (self.y**2) + (self.z**2) + (self.w**2)

    def squareLength3(self):
        """ Return square length of this vector using only x, y, z. """
        return (self.x**2) + (self.y**2) + (self.z**2)

    def normalize(self):
        """ Returns a normalized version of this vector. """
        l = self.length()
        if (l==0): return Vector4(0,0,0,0)
        return Vector4(self.x/l, self.y/l, self.z/l, self.w/l)

    def normalize3(self):
        """ Returns a normalized version of this vector using only x, y, z. """
        l = self.length3()
        if (l==0): return Vector4(0,0,0,0)
        return Vector4(self.x/l, self.y/l, self.z/l, 0)

    # --------------------------------------------------------------------------
    # Operator functions
    # --------------------------------------------------------------------------
    def multiply(self, s):
        """ Returns a new version of this vector multiplied by s. """
        return Vector4(self.x*s, self.y*s, self.z*s, self.w*s)

    def divide(self, s):
        """ Returns a new version of this vector divided by s.
            If s is 0, return null vector (All elements set to 0).  """
        if (s==0): return Vector4(0,0,0,0)
        return Vector4(self.x/s, self.y/s, self.z/s, self.w/s)

    def add(self, v):
        """ Returns a new version of this vector added with another vector v. """
        return Vector4(self.x+v.x, self.y+v.y, self.z+v.z, self.w+v.w)

    def sub(self, v):
        """ Returns a new version of this vector minus another vector v. """
        return Vector4(self.x-v.x, self.y-v.y, self.z-v.z, self.w-v.w)

    # --------------------------------------------------------------------------
    # Operations with other vectors
    # --------------------------------------------------------------------------
    def equals(self, v):
        """ Checks whether this vector components (x,y,z,w) are equal to v components. """
        return  self.x == v.x and self.y == v.y and self.z == v.z and self.w == v.w

    def dot(self, v):
        """ Returns the dot product of this vector. """
        return (self.x * v.x) + (self.y * v.y) + (self.z * v.z) + (self.w * v.w)

    def dot3(self, v):
        """ Returns the dot product of this vector using only x, y, z. """
        return (self.x * v.x) + (self.y * v.y) + (self.z * v.z)

    def cross3(self, v):
        """ Returns a new vector with is the CrossProduct of current vector and v. """
        newx = (self.y * v.z) - (self.z * v.y)
        newy = (self.z * v.x) - (self.x * v.z)
        newz = (self.x * v.y) - (self.y * v.x)
        return Vector4(newx, newy, newz, 0)
