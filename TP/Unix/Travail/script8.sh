#!/bin/bash

last|cut -f 1 -d ' '|sort|uniq -c|sort -n 