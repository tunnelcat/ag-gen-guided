#!/usr/bin/env python2

from sys import argv, exit

if len(argv) != 3:
    print "Usage: %s [input file] [output file]" % argv[0]
    exit(1)

with open(argv[1], 'r') as inf:
    lines = inf.readlines()

def find_first_arrow():
    global lines
    for i in xrange(len(lines)):
        if '->' in lines[i]:
            return i
    return -1;

def get_hash_map(fai):
    global lines
    hash_map = {}
    current_id = 0
    for i in xrange(1, fai):
        h = lines[i][:-3]
        if h not in hash_map:
            hash_map[h] = current_id
            current_id += 1
        lines[i] = lines[i].replace(h, str(hash_map[h]))
    return hash_map

def perform_replacements(fai, hash_map):
    global lines

    for i in xrange(fai, len(lines) - 1):
        hashes = lines[i][:-4].split(' -> ')
        lines[i] = lines[i].replace(hashes[0], str(hash_map[hashes[0]]))
        lines[i] = lines[i].replace(hashes[1], str(hash_map[hashes[1]]))


first_arrow_index = find_first_arrow();
if (first_arrow_index == -1):
    print "Error: file is improper graph"
    exit(2);

hash_map = get_hash_map(first_arrow_index)

perform_replacements(first_arrow_index, hash_map)

with open(argv[2], 'w') as outf:
    for line in lines:
        outf.write(line)
