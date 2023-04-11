/*
** EPITECH PROJECT, 2023
** reply_codes
** File description:
** In this file is a description of the reply codes
*/

#pragma once

#include <stdio.h>

enum Category {
    INFORMATION,
    SUCCESS,
    ERROR
};

struct reply_codes_s {
    int code;
    enum Category category;
    const char *message;
};

static const struct reply_codes_s reply_codes[] = {
    {110, INFORMATION, "to complete"},
    {150, INFORMATION, "to complete"},
    {200, SUCCESS, "to complete"},
    {214, SUCCESS, "to complete"},
    {220, SUCCESS, "to complete"},
    {221, SUCCESS, "to complete"},
    {230, SUCCESS, "to complete"},
    {350, SUCCESS, "to complete"},
    {430, ERROR, "to complete"},
    {431, ERROR, "to complete"},
    {500, ERROR, "to complete"},
    {501, ERROR, "to complete"},
    {502, ERROR, "to complete"},
    {530, ERROR, "to complete"},
    {550, ERROR, "to complete"}
};
