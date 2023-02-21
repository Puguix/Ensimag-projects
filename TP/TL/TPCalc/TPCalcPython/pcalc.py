#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Calculator in prefix syntax
"""

from locale import currency
from turtle import update
from webbrowser import get
import lexer
import sys

from parser import init_parser, parse_token, get_current, Error

###################
## the public function of the calculator

def parse(stream = sys.stdin):
    init_parser(stream)
    return parse_input([])

#########################
## parsing of input

def parse_input(l):
    # print("@ATTENTION: pcalc.parse_input à corriger !") # LIGNE A SUPPRIMER
    e = get_current()
    while e != lexer.END:
        if e == lexer.QUEST:
            n = parse_exp(l)
            l.append(n)
        lexer.update_current()
        e = get_current()
    return l


#########################
## parsing of expressions

def parse_exp(l):
    e = get_current()
    if e == lexer.PLUS:
        lexer.update_current()
        n1 = parse_exp(l)
        lexer.update_current()
        n2 = parse_exp(l)
        return n1+n2
    elif e == lexer.MOINS:
        lexer.update_current()
        n1 = parse_exp(l)
        lexer.update_current()
        n2 = parse_exp(l)
        return n1-n2
    elif e == lexer.MULT:
        lexer.update_current()
        n1 = parse_exp(l)
        lexer.update_current()
        n2 = parse_exp(l)
        return n1*n2
    elif e == lexer.DIV:
        lexer.update_current()
        n1 = parse_exp(l)
        lexer.update_current()
        n2 = parse_exp(l)
        return n1/n2
    elif e == lexer.CALC:
        return l[parse_token(lexer.NAT)-1]
    else:
        return parse_token(lexer.NAT)


#########################
## run on the command-line

if __name__ == "__main__":
    print("@ Testing the calculator in prefix syntax.")
    print("@ Type Ctrl-D to quit")
    l=parse()
    print("@ result = ", repr(l))
