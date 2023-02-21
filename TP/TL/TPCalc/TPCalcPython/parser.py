#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Generic functions for LL(1) parsing
"""

import lexer

# name of tokens in error message
def token_name():
    tn = list(lexer.TOKEN_PREFIX)
    tn[lexer.CALC] = 'CALC'
    tn[lexer.NAT]  = 'NAT'
    tn[lexer.END]  = 'END'
    return tn

TOKEN_NAME = token_name()

class Error(Exception):
    pass

_current_token = lexer.END
_value = None


def get_current():
    return _current_token


def init_parser(stream):
    global _current_token, _value
    lexer.reinit(stream)
    _current_token, _value = lexer.next_token()
    # print("@ init parser on",  repr(lexer.str_attr_token(_current, _value)))


def parse_token(token):
    global _current_token, _value
    if _current_token != token:
        raise Error('found token ' + repr(lexer.str_attr_token(_current_token, _value)) + ' but expected ' + repr(TOKEN_NAME[token]))
    if _current_token != lexer.END:
        old = _value
        _current_token, _value = lexer.next_token()
        return old
