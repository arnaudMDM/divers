#!/bin/env python
# -*- coding: utf-8 -*-

import easygui as eg

msg     = "What exercise do you want to do?"
title   = "Menu"
choices = ["Hiragana-katana word", "Kanji word", "Kanji alone"]
choic   = eg.choicebox(msg, title, choices)

if choic == choices[0]:
    title       = "Hiragana-katana word"
    fieldNames  = ["Answer"]
    fieldValues = []  # we start with blanks for the values
    msg = ""
    while True:
        msg += "Question:  さ"
        fieldValues = eg.multenterbox(msg,title, fieldNames)

        if fieldValues == None: 
            break

        if fieldValues[0] == "a":
            msg = "GOOD !\n"
        else:
            msg = "WRONG. Answer: \n"
            
        print ("Reply was:", fieldValues)