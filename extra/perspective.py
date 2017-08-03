#!/usr/bin/python3
#
# DESCRIPTION
# Script that shows steps and calculations to create a perspective matrix.
# Created for learning purpose.
#
# WARNING
# All formula for Left-handed coordinates.
# Point x,y,z is put in homogeneous coordinates with W is set to 1

import sys
import math


# ------------------------------------------------------------------------------
# Default values
# ------------------------------------------------------------------------------
screen_width = 1000
screen_height = 500
near = 1
far = 10


# ------------------------------------------------------------------------------
# Remap assets
# ------------------------------------------------------------------------------
def get_x_remap_factor(fov, w, h):
    """ Returns the factor that multiplies X. """
    cotanFov = 1 / math.tan(fov/2)
    aspect = w / h
    return cotanFov / aspect

def get_y_remap_factor(fov, w, h):
    """ Returns the factor that multiplies Y. """
    return 1/math.tan(fov/2)

def z_divide(value, z):
    """ Divides the value by z. If z is 0, returns infinite. """
    if z == 0:
        return float('inf')
    return value / z;


# ------------------------------------------------------------------------------
# Full remap functions
# ------------------------------------------------------------------------------
def remapz(z, near, far):
    dz = far / (far - near)
    dw = -(far * near) / (far - near)
    return z * dz + dw


# ------------------------------------------------------------------------------
# Print remap values (With steps)
# ------------------------------------------------------------------------------
def print_x_remap(x, fov, w, h, z):
    print("----- Remap X -----")
    s_factor = get_x_remap_factor(fov, w, h)
    x_prim_1 = x * s_factor
    x_prim_2 = z_divide(x_prim_1, z)
    print(" Remap factor s = ", s_factor)
    print(" x'  = (x * s) = ", x_prim_1)
    print(" x'' = (x' / z) = ", x_prim_2)

def print_y_remap(y, fov, w, h, z):
    print("----- Remap Y -----")
    s_factor = get_y_remap_factor(fov, w, h)
    y_prim_1 = y * s_factor
    y_prim_2 = z_divide(y_prim_1, z)
    print(" Remap factor s = ", s_factor)
    print(" y'  = (y * s) = ", y_prim_1)
    print(" y'' = (y' / z) = ", y_prim_2)

def print_z_remap(z, fov, near, far):
    print("----- Remap Z -----")
    z_prim = remapz(z, near, far)
    print(" z' = ", z_prim)
    print(" z'' = (z' / z) = ", z_divide(z_prim, z))


# ------------------------------------------------------------------------------
# Assets functions
# ------------------------------------------------------------------------------
def is_atan_in_angle(expected, x, y):
    """ Returns true if arctan(x,y) is an angle smaller or equals to expected angle """
    angle = math.atan(y/x)
    return angle <= expected
def radians_to_degrees(angle):
    """ Returns the angle in degrees from the given radians angle.
        Result is an approximation. """
    return angle * 180 / math.pi
def degrees_to_radians(angle):
    """ Returns the angle in radian from the given degrees angle.
        Result is an approximation. """
    return angle / 180 * math.pi


# ------------------------------------------------------------------------------
# Main
# ------------------------------------------------------------------------------
def usage():
    print("[USAGE]")
    print(" ", __file__, "fov x y z")
    print(" ", __file__, "fov width height x y z")
    print(" ", __file__, "fov width height near far x y z")
    print("[DESCRIPTION]")
    print(" width is the screen width.")
    print(" height is the screen height.")
    print(" Process for left-handed coordinates")

def print_data(fov, w, h, near, far, x, y, z):
    """ Print row data about fov, point angle etc """
    print("----- Perspective Matrix data  -----")
    print("* Coordinates:")
    print("    x = ", x)
    print("    y = ", y)
    print("    z = ", z)
    print("* Angles in degrees:")
    print("    Fov = ", radians_to_degrees(fov))
    print("    Fov / 2 = ", radians_to_degrees(fov) / 2)
    print("    Point angle = ", radians_to_degrees(math.atan(y/z)))
    print("* Angles in radians:")
    print("    Fov = ", fov)
    print("    Fov / 2 = ", fov / 2)
    print("    Point angle = ", math.atan(y/z))
    print("* Is angle in Fov?")
    if (is_atan_in_angle(fov/2, z, y)):
        print("    Yes! Point should be displayed")
    else:
        print("    Noooo! Point shouldn't be displayed")
    print("* Other data")
    print("    Screen width = ", w)
    print("    Screen height = ", h)
    print("    Aspect w / h = ", w / h)
    print("    Aspect h / w = ", h / w)
    print("    Near clipping = ", near)
    print("    Far clipping = ", far)
    print("    tan(Fov / 2) = ", math.tan(fov/2))

def process_all(fov, w, h, near, far, x, y, z):
    """ Main execution process. """
    print()
    print_data(fov, w, h, near, far, x, y, z)
    print()
    print_x_remap(x, fov, w, h, z)
    print()
    print_y_remap(y, fov, w, h, z)
    print()
    print_z_remap(z, fov, near, far)

def main():
    """ The main (The famous). """
    global screen_width, screen_height, near, far
    nb_params = len(sys.argv) - 1 # Pos 0 is script name
    if (nb_params == 4):
        fov             = degrees_to_radians((int)(sys.argv[1]))
        x               = (int)(sys.argv[2])
        y               = (int)(sys.argv[3])
        z               = (int)(sys.argv[4])
    elif (nb_params == 6):
        fov             = degrees_to_radians((int)(sys.argv[1]))
        screen_width    = (int)(sys.argv[2])
        screen_height   = (int)(sys.argv[3])
        x               = (int)(sys.argv[4])
        y               = (int)(sys.argv[5])
        z               = (int)(sys.argv[6])
    elif (nb_params == 8):
        fov             = degrees_to_radians((int)(sys.argv[1]))
        screen_width    = (int)(sys.argv[2])
        screen_height   = (int)(sys.argv[3])
        near            = (int)(sys.argv[4])
        far             = (int)(sys.argv[5])
        x               = (int)(sys.argv[6])
        y               = (int)(sys.argv[7])
        z               = (int)(sys.argv[8])
    else:
        usage()
        return -1
    process_all(fov, screen_width, screen_height, near, far, x, y, z)

if __name__ == "__main__":
    main()
