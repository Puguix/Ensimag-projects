#!/usr/bin/env python3

"""Decorator to debug python programs.

Decorate any function with @trace to display arguments
and results in terminology or to generate an image at
each call. You can also use "display_instance"
and "display_vars" directly in your code to
draw the instances and variables of your choice.
"""
from tempfile import NamedTemporaryFile
import os
import time
import collections
import typing
import inspect
import shutil

VARIABLE_BACKGROUND = "chartreuse"
INSTANCE_BACKGROUND = "gray"
NONE_BACKGROUND = "deeppink"
Variable = collections.namedtuple("Variable", "name value")

def _draw_none(none_inst, show_address: bool, dot_file):
    """Draw the None node"""
    dot_name = f'struct_{id(none_inst)}'
    print(f'  {dot_name} [label=<', file=dot_file)
    print(f'<TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0" BGCOLOR="{NONE_BACKGROUND}">',
          file=dot_file)
    if show_address:
        print(f'<TR><TD>0x{id(none_inst):x}</TD></TR>', file=dot_file)
    print(f'<TR><TD>None</TD></TR>', file=dot_file)
    print('</TABLE>>];', file=dot_file)
    return dot_name

def _draw_callable(callable_inst, show_address: bool, dot_file):
    """Draw the given callable"""
    dot_name = f'struct_{id(callable_inst)}'
    print(f'  {dot_name} [label=<', file=dot_file)
    print(f'<TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0" BGCOLOR="{INSTANCE_BACKGROUND}">',
          file=dot_file)
    if show_address:
        print(f'<TR><TD>0x{id(callable_inst):x}</TD></TR>', file=dot_file)
    print(f'<TR><TD><u>{type(callable_inst).__name__}</u></TD></TR>', file=dot_file)
    obj_str = f'{callable_inst.__name__}'
    print(f'<TR><TD>{obj_str}</TD></TR>', file=dot_file)
    print('</TABLE>>];', file=dot_file)
    return dot_name

def _is_primitive(inst):
    """Is the given instance 'primitive'?"""
    return isinstance(inst, (int, float, str)) or inst is None

def _draw_primitive(inst, show_address: bool, dot_file):
    """Draw a primitive instance"""
    dot_name = f'struct_{id(inst)}'
    print(f'  {dot_name} [label=<', file=dot_file)
    print(f'<TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0" BGCOLOR="{INSTANCE_BACKGROUND}">',
          file=dot_file)
    if show_address:
        print(f'<TR><TD>0x{id(inst):x}</TD></TR>', file=dot_file)
    print(f'<TR><TD><u>{type(inst).__name__}</u></TD></TR>', file=dot_file)
    inst_str = f'"{inst}"' if isinstance(inst, str) else f'{inst}'
    print(f'<TR><TD>{inst_str}</TD></TR>', file=dot_file)
    print('</TABLE>>];', file=dot_file)
    return dot_name

def _draw_sequence(seq_inst, dot_file, deeply, show_address, seen_insts):
    """Draw a list or tuple instance"""
    dot_name = f'struct_{id(seq_inst)}'
    seen_insts[id(seq_inst)] = dot_name
    print(f'  {dot_name} [label=<', file=dot_file)
    print(f'<TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0" BGCOLOR="{INSTANCE_BACKGROUND}">',
          file=dot_file)

    # Si la séquence n'est pas vide
    if seq_inst:
        if show_address:
            print(f'<TR><TD COLSPAN="{len(seq_inst)}">0x{id(seq_inst):x}</TD></TR>', file=dot_file)
        print(f'<TR><TD COLSPAN="{len(seq_inst)}"><u>{type(seq_inst).__name__}</u></TD></TR>',
              file=dot_file)
        print(f'<TR>', end='', file=dot_file)
        child_to_be_drawn = []
        child_count = 0
        for elem in seq_inst:
            if not deeply and _is_primitive(elem):
                elem_str = f'"{elem}"' if isinstance(elem, str) else f'{elem}'
                print(f'<TD>{elem_str}</TD>', end='', file=dot_file)
            else:
                if show_address:
                    print(f'<TD PORT="port_child{child_count}">0x{id(elem):x}</TD>',
                          file=dot_file)
                else:
                    print(f'<TD PORT="port_child{child_count}">⏺</TD>', end='', file=dot_file)
                child_to_be_drawn.append(elem)
                child_count += 1
        print(f'</TR>', file=dot_file)
        print('</TABLE>>];', file=dot_file)
        for i, child in enumerate(child_to_be_drawn):
            sub_dot_name = _draw_instance(deeply=deeply,
                                          inst=child,
                                          show_address=show_address,
                                          dot_file=dot_file, seen_insts=seen_insts)
            print(f'{dot_name}:port_child{i} -> {sub_dot_name};', file=dot_file)

    # Sinon elle est vide
    else:
        if show_address:
            print(f'<TR><TD>0x{id(seq_inst):x}</TD></TR>', file=dot_file)
        print(f'<TR><TD><u>{type(seq_inst).__name__}</u></TD></TR>', file=dot_file)
        print(f'<TR>', end='', file=dot_file)
        print(f'<TD>vide</TD>', end='', file=dot_file)
        print(f'</TR>', file=dot_file)
        print('</TABLE>>];', file=dot_file)

    return dot_name

def _draw_dict(dict_inst, dot_file, deeply, show_address, seen_insts):
    """Draw a dict instance"""
    dot_name = f'struct_{id(dict_inst)}'
    seen_insts[id(dict_inst)] = dot_name
    print(f'  {dot_name} [label=<', file=dot_file)
    print(f'<TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0" BGCOLOR="{INSTANCE_BACKGROUND}">',
          file=dot_file)
    if show_address:
        print(f'<TR><TD>0x{id(dict_inst):x}</TD></TR>', file=dot_file)
    print(f'<TR><TD COLSPAN="{len(dict_inst)*2}"><u>{type(dict_inst).__name__}</u></TD></TR>',
          file=dot_file)
    child_to_be_drawn = []
    child_count = 0
    print(f'<TR>', file=dot_file)
    for i in range(1, len(dict_inst) + 1):
        print(f'<TD COLSPAN="2">item{i}</TD>', file=dot_file)
    print(f'</TR>', file=dot_file)
    print(f'<TR>', end='', file=dot_file)
    for key, value in dict_inst.items():
        for elem, elem_name in ((key, "key"), (value, "value")):
            if not deeply and isinstance(elem, (int, float, str)):
                elem_str = f'"{elem}"' if isinstance(elem, str) else f'{elem}'
                print(f'<TD>{elem_name} {elem_str}</TD>',
                      end='', file=dot_file)
            else:
                if show_address:
                    print(f'<TD PORT="port_child{child_count}">0x{id(elem):x}</TD>',
                          file=dot_file)
                else:
                    print(f'<TD PORT="port_child{child_count}">{elem_name} ⏺</TD>',
                          end='', file=dot_file)
                child_to_be_drawn.append(elem)
                child_count += 1
    print(f'</TR>', file=dot_file)
    print('</TABLE>>];', file=dot_file)
    for i, child in enumerate(child_to_be_drawn):
        sub_dot_name = _draw_instance(deeply=deeply, inst=child, show_address=show_address,
                                      dot_file=dot_file, seen_insts=seen_insts)
        print(f'{dot_name}:port_child{i} -> {sub_dot_name};', file=dot_file)
    return dot_name

def _draw_other(inst, dot_file, deeply, show_address, seen_insts):
    """Draw an instance using its attributes"""
    dot_name = f'struct_{id(inst)}'
    seen_insts[id(inst)] = dot_name
    print(f'  {dot_name} [label=<', file=dot_file)
    print(f'<TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0" BGCOLOR="{INSTANCE_BACKGROUND}">',
          file=dot_file)
    if show_address:
        print(f'<TR><TD>0x{id(inst):x}</TD></TR>', file=dot_file)
    print(f'<TR><TD COLSPAN="{len(vars(inst))}"><u>{type(inst).__name__}</u></TD></TR>',
          file=dot_file)
    child_to_be_drawn = []
    child_count = 0
    print(f'<TR>', file=dot_file)
    for field_name in vars(inst):
        print(f'<TD>{field_name}</TD>', file=dot_file)
    print(f'</TR>', file=dot_file)
    print(f'<TR>', end='', file=dot_file)
    for field_name in vars(inst):
        field_obj = getattr(inst, field_name)
        if not deeply and _is_primitive(field_obj):
            elem_str = f'"{field_obj}"' if isinstance(field_obj, str) else f'{field_obj}'
            print(f'<TD>{elem_str}</TD>', end='', file=dot_file)
        else:
            if show_address:
                print(f'<TD PORT="port_child{child_count}">0x{id(field_obj):x}</TD>',
                      file=dot_file)
            else:
                print(f'<TD PORT="port_child{child_count}">⏺</TD>', end='', file=dot_file)
            child_to_be_drawn.append(field_obj)
            child_count += 1

    print(f'</TR>', file=dot_file)
    print('</TABLE>>];', file=dot_file)
    for i, child in enumerate(child_to_be_drawn):
        sub_dot_name = _draw_instance(deeply=deeply, show_address=show_address, inst=child,
                                      dot_file=dot_file, seen_insts=seen_insts)
        print(f'{dot_name}:port_child{i} -> {sub_dot_name};', file=dot_file)
    return dot_name

def _draw_instance(deeply: bool, show_address: bool, inst: object,
                   dot_file: typing.TextIO, seen_insts: dict):
    """Draw the given instance in the dot file.

    And all other instances accessible from it.
    Return the dot name of the instance.
    """

    # Return if obj already seen
    if id(inst) in seen_insts:
        return seen_insts[id(inst)]

    # None is sooooo special
    if inst is None:
        dot_name = _draw_none(inst, show_address, dot_file)
        seen_insts[id(inst)] = dot_name

    # Handle primitive type in a special way
    elif _is_primitive(inst):
        dot_name = _draw_primitive(inst, show_address, dot_file)
        seen_insts[id(inst)] = dot_name

    # Handle list and tuples in the same special way.
    # Drawing here depends on deeply
    elif isinstance(inst, (list, tuple)):
        dot_name = _draw_sequence(inst, dot_file, deeply, show_address, seen_insts)

    # Handle dict in a special way
    # Drawing of dict depends on deeply
    elif isinstance(inst, dict):
        dot_name = _draw_dict(inst, dot_file, deeply, show_address, seen_insts)

    # Handle callable (such as a function) in a special way
    elif callable(inst):
        dot_name = _draw_callable(inst, show_address, dot_file)
        seen_insts[id(inst)] = dot_name

    # Handle any other instance in a generic way
    else:
        dot_name = _draw_other(inst, dot_file, deeply, show_address, seen_insts)

    return dot_name

def _draw_variable(deeply: bool, show_address: bool, variable: Variable, dot_file: typing.TextIO,
                   seen_insts: dict):
    """Draw the given variable in the dot file.

    And all instances accessible from it.
    """

    # Draw the variable itself
    print(f'  struct_{variable.name} [label=<', file=dot_file)
    print(f'<TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0" BGCOLOR="{VARIABLE_BACKGROUND}">',
          file=dot_file)
    print(f'<TR><TD>{variable.name}</TD></TR>', file=dot_file)
    if show_address:
        print(f'<TR><TD PORT="port_{variable.name}">0x{id(variable.value):x}</TD></TR>',
              file=dot_file)
    else:
        print(f'<TR><TD PORT="port_{variable.name}">⏺</TD></TR>', file=dot_file)
    print('</TABLE>>];', file=dot_file)

    # Draw the instance referenced by variable and all accessible instances
    # from it. And the link between variable and the instance it references.
    inst_dot_name = _draw_instance(deeply=deeply, show_address=show_address, inst=variable.value,
                                   dot_file=dot_file, seen_insts=seen_insts)
    print(f'struct_{variable.name}:port_{variable.name} -> {inst_dot_name};', file=dot_file)

def display_vars(*args: typing.Sequence[Variable],
                 deeply: bool = True,
                 show_address: bool = False,
                 visualize: bool = True,
                 image_name: str = None):
    """Display graph of instances starting from given variables.

    Drawing is done by generating an SVG image with graphviz/dot.

    :param typing.Sequence[Variable] args: The sequence of variables
           to start the drawing from
    :param bool deeply: If True, str, int and float instances are drawn
           as in the reality, that is as instances. Else, they are
           embedded in the enclosing instance if such instance exists.
    :param bool visualize: If True, the generated image is opened in
           the terminal. For that, the program MUST run inside termi-
           nology. Else, the SVG file is copied into the current
           directory and its name is printed on stdout.
    :param str image_name: If visualize is False, this parameter
           allows specifying the name of the generated SVG image.
    """

    # Create the dot file as a temporary file (thanks to Python standard lib!)
    dot_f = NamedTemporaryFile(mode="w", delete=False, suffix=".dot")
    print('digraph structs {', file=dot_f)
    print('  node [shape=plaintext]', file=dot_f)

    # Draw variables one by one
    seen = {}
    for var in args:
        _draw_variable(deeply=deeply, show_address=show_address,
                       variable=var, dot_file=dot_f, seen_insts=seen)

    # Convert to image
    print("}", file=dot_f)
    dot_f.close()
    dot_name = dot_f.name
    img_name = dot_name + ".svg"
    os.system("dot -Tsvg {} -o {}".format(dot_name, img_name))

    # Open image using tycat
    if visualize:
        os.system("tycat {}".format(img_name))
        time.sleep(1)

    # Or copy the image to the current directory
    else:
        if image_name:
            target_file = f"./{image_name}.svg"
        else:
            target_file = f"./{os.path.basename(img_name)}"
        print(f"image generated as {target_file}")
        shutil.copyfile(img_name, target_file)

def display_instance(instance: object,
                     deeply: bool = True,
                     show_address: bool = False,
                     visualize: bool = True,
                     image_name: str = None):
    """Display graph of instances starting from the given instance.

    Drawing is done by generating an SVG image with graphviz/dot.

    :param object instance: The instance to start the drawing from
    :param bool deeply: If True, str, int and float instances are drawn
           as in the reality, that is as instances. Else, they are
           embedded in the enclosing instance if such instance exists.
    :param bool visualize: If True, the generated image is opened in
           the terminal. For that, the program MUST run inside termi-
           nology. Else, the SVG file is copied into the current
           directory and its name is printed on stdout.
    :param str image_name: If visualize is False, this parameter
           allows specifying the name of the generated SVG image.
    """

    # Create the dot file as a temporary file (thanks to Python standard lib!)
    dot_f = NamedTemporaryFile(mode="w", delete=False, suffix=".dot")
    print('digraph structs {', file=dot_f)
    print('  node [shape=plaintext]', file=dot_f)

    # Draw the instance
    _draw_instance(deeply=deeply, show_address=show_address,
                   inst=instance, dot_file=dot_f, seen_insts={})

    # Convert to image
    print("}", file=dot_f)
    dot_f.close()
    dot_name = dot_f.name
    img_name = f"{dot_name}.svg"
    os.system("dot -Tsvg {} -o {}".format(dot_name, img_name))

    # Open image using tycat
    if visualize:
        os.system("tycat {}".format(img_name))
        time.sleep(1)

    # Or copy the image to the current directory
    else:
        if image_name:
            target_file = f"./{image_name}.svg"
        else:
            target_file = f"./{os.path.basename(img_name)}"
        print(f"image generated as {target_file}")
        shutil.copyfile(img_name, target_file)

def trace(deeply: bool = True,
          show_address: bool = False,
          visualize: bool = True,
          image_name: str = None):
    """Decorator to trace a function deeply or not.

    trace is called on the first time the definition of a function decorated
    with @traceur.trace(X, Y, Z) is encountered for a given X, Y, Z triplet

    :param bool deeply: If True, str, int and float instances are drawn
           as in the reality, that is as instances. Else, they are
           embedded in the enclosing instance if such instance exists.
    :param bool visualize: If True, the generated image is opened in
           the terminal. For that, the program MUST run inside termi-
           nology. Else, the SVG file is copied into the current
           directory and its name is printed on stdout.
    :param str image_name: If visualize is False, this parameter
           allows specifying the name of the generated SVG image.
    """
    def parametrized_tracer(function):
        """Activate terminal display (tycat) of function arguments and results.

        For a given X, Y, Z triplet, parametrized_tracer is called every time the
        definition of a function decorated with @traceur.trace(X, Y, Z) is encountered
        """
        def tracer(*args, **kwargs):
            """Trace and call original function.

            For a given X, Y, Z triplet, tracer is called every time a function
            decorated with @traceur.trace(X, Y, Z) is called.
            """

            # Print function call as text on stdout
            print("-----------------------------------")
            arguments = []
            # Positional arguments
            posargs = inspect.getfullargspec(function).args
            for arg_name, arg_val in zip(posargs, args):
                arguments.append(Variable(arg_name, arg_val))
            posargs_str = ", ".join([f"{arg.name}={arg.value}" for arg in arguments])
            # Varargs tuple
            first_vararg_index = len(posargs)
            varargs_str = ""
            if args[first_vararg_index:]:
                arguments.append(Variable(inspect.getfullargspec(function).varargs,
                                          args[first_vararg_index:]))
                varargs_str = f"args={args[first_vararg_index:]}"
            # Kwargs dictionnary
            kwargs_str = ""
            if kwargs:
                arguments.append(Variable("kwargs", kwargs))
                kwargs_str = f"kwargs={kwargs}"
            allargs_str = ", ".join(filter(None, (posargs_str, varargs_str, kwargs_str)))
            print(f"function call : {function.__name__}({allargs_str})")

            # Print function arguments as image (on stdout or in file)
            display_vars(*arguments, deeply=deeply, show_address=show_address,
                         visualize=visualize, image_name=image_name)

            # Call the function
            result = function(*args, **kwargs)

            # Print function return value as text on stdout
            print(f"return value ----> {result}")

            # Print function return value as image (on stdout or in file)
            display_instance(result, deeply=deeply, show_address=show_address,
                             visualize=visualize, image_name=image_name)

            return result
        return tracer
    return parametrized_tracer
