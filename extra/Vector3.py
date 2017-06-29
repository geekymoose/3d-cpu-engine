from math import sqrt

class Vector3:
    """ Simple Vector3 class """

    # --------------------------------------------------------------------------
    # Constructors
    # --------------------------------------------------------------------------
    def __init__(self, x=0, y=0, z=0):
        self.x = x
        self.y = y
        self.z = z

    # --------------------------------------------------------------------------
    # General functions
    # --------------------------------------------------------------------------
    def length(self):
        """ Returns length of this vector. """
        return sqrt(self.squareLength())

    def squareLength(self):
        """ Returns square length of this vector. """
        return (self.x**2) + (self.y**2) + (self.z**2)

    def normalize(self):
        """ Returns a normalized version of this vector. """
        l = self.length()
        if (l==0): return Vector3(0,0,0)
        return Vector3(self.x/l, self.y/l, self.z/l)

    # --------------------------------------------------------------------------
    # Operator functions
    # --------------------------------------------------------------------------
    def multiply(self, s):
        """ Returns a new version of this vector multiplied by s. """
        return Vector3(self.x*s, self.y*s, self.z*s)

    def divide(self, s):
        """ Returns a new version of this vector divided by s.
        If s is 0, return null vector (All elements set to 0). 
        """
        if (s==0): return Vector3(0,0,0)
        return Vector3(self.x/s, self.y/s, self.z/s)

    def add(self, v):
        """ Returns a new version of this vector added with another vector v. """
        return Vector3(self.x+v.x, self.y+v.y, self.z+v.z)

    def sub(self, v):
        """ Returns a new version of this vector minus another vector v. """
        return Vector3(self.x-v.x, self.y-v.y, self.z-v.z)

    # --------------------------------------------------------------------------
    # Operations with other vectors
    # --------------------------------------------------------------------------
    def equals(self, v):
        """ Checks whether this vector components (x,y,z) are equal to v components. """
        return  self.x == v.x and self.y == v.y and self.z == v.z

    def dot(self, v):
        """ Returns the dot product of this vector. """
        return (self.x * v.x) + (self.y * v.y) + (self.z * v.z)

    def cross(self, v):
        """ Returns a new vector with is the CrossProduct of current vector and v. """
        newx = (self.y * v.z) - (self.z * v.y)
        newy = (self.z * v.x) - (self.x * v.z)
        newz = (self.x * v.y) - (self.y * v.x)
        return Vector3(newx, newy, newz)
