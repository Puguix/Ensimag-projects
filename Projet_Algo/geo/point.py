"""
points (any dimension).
"""
from math import sqrt
from geo.quadrant import Quadrant


class Point:
    """
    a point is defined as a vector of any given dimension.

    for example:

    - create a point at x=2, y=5:

    my_point = Point([2, 5])

    - find distance between two points:

    distance = point1.distance_to(point2)
    """
    def __init__(self, coordinates):
        """
        build new point using an array of coordinates.
        """
        self.coordinates = coordinates

    def copy(self):
        """
        return copy of given point.
        """
        return Point(list(self.coordinates))

    def distance_to(self, other):
        """
        euclidean distance between two points.
        """
        if self < other:
            return other.distance_to(self)  # we are now a symmetric function

        total = 0
        for c_1, c_2 in zip(self.coordinates, other.coordinates):
            diff = c_1 - c_2
            total += diff * diff

        return sqrt(total)

    def bounding_quadrant(self):
        """
        return min quadrant containing point.
        this method is defined on any displayable object.
        """
        return Quadrant(self.coordinates, self.coordinates)

    def svg_content(self):
        """
        svg display for tycat.
        """
        return '<use xlink:href="#c" x="{}" y="{}"/>\n'.format(*self.coordinates)

    def cross_product(self, other):
        """
        cross product between 2 2d vectors.
        """
        x_1, y_1 = self.coordinates
        x_2, y_2 = other.coordinates
        return -y_1*x_2 + x_1*y_2

    def __add__(self, other):
        """
        addition operator. (useful for translations)
        """
        return Point([i + j for i, j in zip(self.coordinates, other.coordinates)])

    def __sub__(self, other):
        """
        substraction operator. (useful for translations)
        """
        return Point([i - j for i, j in zip(self.coordinates, other.coordinates)])

    def __mul__(self, factor):
        """
        multiplication by scalar operator. (useful for scaling)
        """
        return Point([c*factor for c in self.coordinates])

    def __truediv__(self, factor):
        """
        division by scalar operator. (useful for scaling)
        """
        return Point([c/factor for c in self.coordinates])

    def __str__(self):
        """
        print code generating the point.
        """
        return ', '.join(str(c) for c in self.coordinates)

    def __repr__(self):
        return "Point([" + ', '.join(str(c) for c in self.coordinates) + "])"

    def __lt__(self, other):
        """
        lexicographical comparison
        """
        return self.coordinates < other.coordinates
