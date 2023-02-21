"""
graphical display system.
save objects as svg files and view them in terminology
"""
import os
import getpass
from itertools import cycle
from geo.quadrant import Quadrant


class Displayer:
    """
    displayer handles computations for displaying a set of objects
    """
    svg_dimensions = (800, 600)
    svg_colors = 'red green blue purple orange saddlebrown mediumseagreen\
                       darkolivegreen lightskyblue dimgray mediumpurple midnightblue\
                       olive chartreuse darkorchid hotpink darkred peru\
                       goldenrod mediumslateblue orangered darkmagenta\
                       darkgoldenrod mediumslateblue firebrick palegreen\
                       royalblue tan tomato springgreen pink orchid\
                       saddlebrown moccasin mistyrose cornflowerblue\
                       darkgrey'.split()
    file_count = 0

    def __init__(self, bounding_quadrant):
        """
        compute stroke size
        """
        coordinates = bounding_quadrant.get_arrays()
        self.min_coordinates, self.max_coordinates = coordinates

        self.dimensions = [
            a - b for a, b in zip(self.max_coordinates, self.min_coordinates)
        ]

        if any(d == 0.0 for d in self.dimensions):
            raise ValueError

        ratios = [a/b for a, b in zip(self.svg_dimensions, self.dimensions)]
        scale = min(ratios)
        if scale == 0.0:
            raise ValueError
        self.stroke_size = 3/scale

    def open_svg(self, filename):
        """
        open new svg file
        """
        svg_file = open(filename, 'w')
        svg_file.write('<svg width="{}" height="{}"'.format(*self.svg_dimensions))
        svg_file.write(' viewBox="{} {}'.format(*self.min_coordinates))
        svg_file.write(' {} {}"'.format(*self.dimensions))
        svg_file.write(' xmlns:xlink="http://www.w3.org/1999/xlink">\n')
        svg_file.write('<rect x="{}" y="{}"'.format(*self.min_coordinates))
        svg_file.write(' width="{}" height="{}" fill="white"/>\n'.format(*self.dimensions))
        svg_file.write('<defs><symbol id="c">\
        <circle r="{}"/></symbol></defs>\n'.format(2*self.stroke_size))
        svg_file.write('<g stroke-width="{}" opacity="0.7">\n'.format(self.stroke_size))
        return svg_file

    def close_svg(self, svg_file):
        """
        close svg file
        """
        # pylint: disable=no-self-use
        svg_file.write("</g>\n")
        svg_file.write("</svg>\n")
        svg_file.close()

def tycat(*things):
    """
    graphically displays all objects given.
    each argument will be displayed in a different color.
    requires :
        - the terminology terminal emulator
        - each object either implements
            * bounding_quadrant
            * svg_content
        or is an iterable on things implementing it.
    """
    print("[", Displayer.file_count, "]")

    # create different directories for each user
    user = getpass.getuser()
    directory = "/tmp/{}".format(user)
    if not os.path.exists(directory):
        os.makedirs(directory)

    filename = "{}/{}.svg".format(directory, str(Displayer.file_count).zfill(5))
    Displayer.file_count += 1

    size, svg_strings = compute_displays(things)
    try:
        display = Displayer(size)
    except ValueError:
        print("displaying image {} failed : it is flat".format(Displayer.file_count-1))
        return

    svg_file = display.open_svg(filename)
    for string in svg_strings:
        svg_file.write(string)
    display.close_svg(svg_file)
    os.system("tycat {}".format(filename))


def compute_displays(things):
    """
    compute bounding quadrant and svg strings for all things to display.
    """
    quadrant = Quadrant.empty_quadrant(2)
    strings = []
    for color, thing in zip(cycle(iter(Displayer.svg_colors)), things):
        strings.append('<g fill="{}" stroke="{}">\n'.format(color, color))
        inner_quadrant, inner_strings = compute_display(thing)
        quadrant.update(inner_quadrant)
        strings.extend(inner_strings)
        strings.append('</g>\n')

    return (quadrant, strings)

def compute_display(thing):
    """
    return bounding quadrant and svg strings for one thing (and all it's content)
    """
    quadrant = Quadrant.empty_quadrant(2)
    strings = []
    try:
        iterator = iter(thing)
        for subthing in iterator:
            inner_quadrant, inner_strings = compute_display(subthing)
            strings.extend(inner_strings)
            quadrant.update(inner_quadrant)

    except TypeError:
        # we cannot iterate on it
        strings.append(thing.svg_content())
        quadrant.update(thing.bounding_quadrant())

    return quadrant, strings
