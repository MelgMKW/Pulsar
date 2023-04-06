#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

def demangleNode(node):
    pointer = False
    ref = False
    const = False
    unsigned = False
    while True:
        if node[0] == 'P':
            pointer = True
        elif node[0] == 'R':
            ref = True
        elif node[0] == 'C':
            const = True
        elif node[0] == 'U':
            unsigned = True
        else:
            break
        node = node[1:]

    pre = str()
    post = str()
    if ref:
        post = '&'
    if pointer:
        post = '*'
    if const:
        pre = 'const '
    if unsigned:
        pre += 'unsigned '

    if node[0] == 'i':
        return pre + 'int' + post, node[1:]
    elif node[0] == 'b':
        return pre + 'bool' + post, node[1:]
    elif node[0] == 'c':
        return pre + 'char' + post, node[1:]
    elif node[0] == 's':
        return pre + 'short' + post, node[1:]
    elif node[0] == 'l':
        return pre + 'long' + post, node[1:]
    elif node[0] == 'f':
        return pre + 'float' + post, node[1:]
    elif node[0] == 'd':
        return pre + 'double' + post, node[1:]
    elif node[0] == 'w':
        return pre + 'wchar_t' + post, node[1:]
    elif node[0] == 'v':
        return pre + 'void' + post, node[1:]

    elif node[0] == 'F':
        return demangleFuncNode(node[1:])

    elif node[0] == 'Q':
        compCount = int(node[1])
        node = node[2:]
        accum = str()
        for idx in range(compCount):
            demangle, node = demangleNode(node)
            accum += demangle + "::"
        return pre + accum[:len(accum)-2] + post, node

    elif node[0].isdigit():
        counter = 1
        while node[counter].isdigit():
            counter += 1
        length = int(node[:counter])
        if node[counter] == '>' or node[counter] == ',':
            return '%d' % length, node[counter:]
        return pre + node[counter:counter+length] + post, node[counter+length:]

    return node, ''

def demangleFuncNode(node):
    args = str()
    while node[0] != '_':
        if len(args):
            args += ', '
        arg, node = demangleNode(node)
        args += arg
    node = node[1:]
    returnType, node = demangleNode(node)
    return '%s(%s)' % (returnType, args), node

def findSepIdx(name, idx):
    count = 0
    retval = 0
    for ch in name:
        if ch == '<' or ch == ',':
            if idx == count:
                return retval
            count += 1
        retval += 1
    return -1

def demangleTemplates(name):
    token = 0
    accum = name
    while True:
        tidx = findSepIdx(accum, token)
        token += 1
        if tidx < 0:
            return accum
        sidx = tidx + 1
        toDem = accum[sidx:]
        accum = accum[:sidx]
        dem, rem = demangleNode(toDem)
        accum += dem + rem

def demangle(sym):
    typeSplit = sym[1:].find('__')
    funcName = demangleTemplates(sym[:typeSplit+1])
    rem = sym[typeSplit+3:]
    funcType, rem = demangleNode(rem)
    funcType = demangleTemplates(funcType)
    objType = rem[0]
    post = str()
    if objType == 'C':
        post = ' const'
        objType = rem[1]
        rem = rem[1:]
    rem = rem[1:]
    funcArgs = str()
    while len(rem):
        if len(funcArgs):
            funcArgs += ', '
        arg, rem = demangleNode(rem)
        funcArgs += demangleTemplates(arg)
    return '%s::%s(%s)%s' % (funcType, funcName, funcArgs, post)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        raise RuntimeError("needs symbol argument")
    print(demangle(sys.argv[1]))