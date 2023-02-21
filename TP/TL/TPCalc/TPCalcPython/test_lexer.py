#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
test the lexer
"""

import io
import lexer

TEST_LEXICAL_ERRORS = True
TEST_EXT1 = False

def verify_seps(seps):
    for c in seps:
        assert c in lexer.SEP, ("irrelevant test:" + repr(sep) + " should contain only spaces and not " + repr(c))


def verify_without_seps(lexeme):
     for c in lexeme:
        assert not (c in lexer.SEP), ("irrelevant test:" + repr(lexeme) + " should not contain spaces" + repr(c))


def is_equal(e1, e2):
    return type(e1) is type(e2) and e1.args == e2.args

def test_lexer(sep_lexemes=(), final_sep='', error=None):
    """ run a test on the lexer
    - 'sep_lexemes' a list of string pairs (seps, lexeme)
    - 'final_sep' a string of seps
    - 'error' either None or (n, exc) where 'n' is the number of token read 
              and 'exc' is the excepted exception"""
    # build the input of the test
    stream = io.StringIO()
    for sep, lexeme in sep_lexemes:
        stream.write(sep)
        verify_without_seps(lexeme)
        stream.write(lexeme)
    verify_seps(final_sep)
    stream.write(final_sep)
    stream.seek(0)
    if error is None:
        num_tokens, exc = len(sep_lexemes), None
    else:
        num_tokens, exc = error
        assert num_tokens >= 0
        assert num_tokens <= len(sep_lexemes)
    # run the test
    print("@ testing lexer on input:", repr(stream.getvalue()))
    print("@ error expected:", repr(error))
    i = 0
    try:
        lexer.reinit(stream)
        while True:
            token, value = lexer.next_token()
            if token == lexer.END:
                assert exc is None, ("exception " + repr(exc) + " expected")
                assert i == num_tokens, ("only read " + repr(i) + " tokens instead of " + repr(num_tokens))
                break
            atok = lexer.str_attr_token(token, value)
            assert i < num_tokens, ("read lexeme " + repr(atok) + " whereas none was expected")
            sep, lexeme = sep_lexemes[i]
            assert atok == lexeme, ("token num " + repr(i) + " found " + atok + " instead of " + lexeme)
            i += 1
    except lexer.Error as e:
        assert is_equal(e, exc), ("found exception " + repr(e) + " instead of " + repr(exc))
        assert i == num_tokens, ("error token num " + repr(i) + " instead of "+ repr(num_tokens))
        stream.close()
    except Exception as e:
        stream.close()
        raise e
    print("@ => OK")
    print()

def single(lexeme, seps=""):
    return ((seps, lexeme),)


test_lexer()
test_lexer(single("7"))
test_lexer(single("12345678900","  000"))
test_lexer(single("0","  000"))
test_lexer(((" "*3, "+"), ("\n"*3, '-'), (" \n  ", '*'), ("",'/'), ("","123"), (" ", "406"), ("", "#789"), ("", "#0"), (" ","0"), ("","?")), "  \n ")
if TEST_EXT1:
    test_lexer(((" "*3, ":"), ("",'p'), (" \n  ", 'g')))
    test_lexer(((" "*3, "+"), ("\n"*3, '-'), (" \n  ", '*'), ("",'/'), ("","123"), (" ", "406"), ("", "#"), (" ", "#0"), (" ","0"), ("","?")))
    test_lexer(((" "*3, "+"), ("\n"*3, '-'), (" \n  ", '*'), ("",'/'), ("","123"), (" ", "406"), ("", "#"), ("", "#0"), (" ","0"), ("","?")))


if TEST_LEXICAL_ERRORS:
    exc1 = lexer.unknown_token_error('$')
    test_lexer(single("$"), error=(0, exc1))
    test_lexer(((" "*3, "+"), ("\n"*3, '-'), (" \n  ", '$'), ("",'/'), ("","123"), (" ", "406"), ("","?")), "  \n ", error=(2, exc1))
    test_lexer(((" "*3, "+"), ("\n"*3, '-'), (" \n  ", '*'), ("",'/'), ("","123"), ("", "$406"), ("","?")), "  \n ", error=(5, exc1))
    if not TEST_EXT1:
        test_lexer(((" "*3, "+"), ("\n"*3, '-'), (" \n  ", '*'), ("",'/'), ("","123"), (" ", "406"), ("", "#"), (" ", "#0"), (" ","0"), ("","?")), error=(6, lexer.expected_digit_error(" ")))
        test_lexer(((" "*3, "+"), ("\n"*3, '-'), (" \n  ", '*'), ("",'/'), ("","123"), (" ", "406"), ("", "#"), ("", "#0"), (" ","0"), ("","?")), error=(6, lexer.expected_digit_error("#")))
        test_lexer(((" "*3, "+"), ("\n"*3, '-'), (" \n  ", '*'), ("",'/'), ("","123"), (" ", "406"), ("", "#"), ("", "$"), (" ","0"), ("","?")), error=(6, lexer.expected_digit_error("$")))

print()
print("@ all tests on lexer OK !")
