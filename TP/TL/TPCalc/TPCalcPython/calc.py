#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Calculator in infix syntax
"""

from email.errors import MissingHeaderBodySeparatorDefect

from isort import place_module_with_reason
import lexer
import sys

from parser import init_parser, parse_token, get_current, token_name

###################
## the public function of the calculator

def parse(stream = sys.stdin):
    init_parser(stream)
    l = parse_input()
    parse_token(lexer.END)
    return l


#########################
## parsing of input

def parse_input():
    #print("@ATTENTION: calc.parse_input à corriger !") # LIGNE A SUPPRIMER
    return parse_inputX([])

def parse_inputX(l0):
    if get_current() == lexer.END:
        return l0
    n = exp2(l0)
    parse_token(lexer.QUEST)
    return parse_inputX(l0+[n])

def exp2(l):
    n1 = exp1(l)
    return exp2X(l,n1)

def exp2X(l,n1):
    l_exp2X = [lexer.QUEST, lexer.CPAR]
    if get_current() in l_exp2X:
        return n1
    elif get_current() == lexer.PLUS:
        parse_token(lexer.PLUS)
        n2 = exp1(l)
        return exp2X(l, n1+n2)
    parse_token(lexer.MINUS)
    n2 = exp1(l)
    return exp2X(l, n1-n2)

def exp1(l):
    n1 = exp0(l)
    return exp1X(l, n1)

def exp1X(l, n1):
    l_exp1X = [lexer.PLUS, lexer.MINUS, lexer.QUEST, lexer.CPAR]
    if get_current() in l_exp1X :
        return n1
    elif get_current() == lexer.MULT:
        parse_token(lexer.MULT)
        n2 = exp0(l)
        return exp1X(l, n1*n2)
    parse_token(lexer.DIV)
    n2 = exp0(l)
    return exp1X(l, n1//n2)

def exp0(l):
    if get_current() == lexer.NAT:
        return parse_token(lexer.NAT)
    elif get_current() == lexer.CALC:
        return l[parse_token(lexer.CALC) - 1]
    elif get_current() == lexer.MINUS:
        parse_token(lexer.MINUS)
        return -exp0(l)
    parse_token(lexer.OPAR)
    n = exp2(l)
    parse_token(lexer.CPAR)
    return n



#########################
## run on the command-line

if __name__ == "__main__":
    print("@ Testing the calculator in infix syntax.")
    print("@ Type Ctrl-D to quit")
    l=parse()
    print("@ result = ", repr(l))
