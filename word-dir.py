#!/usr/bin/python3
# -*- coding: utf-8 -*-
import sys
brackets = "〈〉《》「」『』【】〔〕（）()"
Widgth = 16
wrev = ""
def isAlnum(word) :
    try:
        return word.encode(\'utf-8\').isalnum()
    except UnicodeEncodeError:
        return False
    
try:
    wnum = ""
    has_num = 0
    wstart = "←"
    wline = wstart
    nwords = 0
    def add_num(wsequence) :
        global has_num
        if has_num :
            global nwords
            nwords += has_num
            has_num = 0
            global wline
            wline = wsequence + wline

    while True :
        str = input("请输入：")
        # print("你输入的内容是: ", str, type(str))
        for word in str:
            i = brackets.find(word)
            if (i != -1):
                i ^= 1
                word = brackets[i:i+1]
            if isAlnum(word):
                wnum += word
                has_num = 1
                continue
            add_num(wnum)
            wnum = ""
            wline = word + wline
            nwords += 1

            if (nwords >= Widgth):
                wrev = wrev + wline + "\n"
                wline = wstart
                nwords = 0

except Exception as err:
    print(err)

if nwords or has_num :
    add_num(wnum)
    wrev += wline

print(wrev)
sys.exit(0)
