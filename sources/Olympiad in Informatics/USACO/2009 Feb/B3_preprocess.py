"""
# USA Computing Olympiad, USACO February 2009 Contest, Bronze 3. Coggle (modified)
# BOJ 1165 preprocess
#
# trie, backtracking
# Date: 2023.12.9
"""

import base64
import gzip

with open('dict.txt', 'r') as f:
    words = [line.strip() for line in f.readlines()]

prev_word = ''
trie = ''
for word in words:
    j = 0
    while j < len(prev_word) and j < len(word) and prev_word[j] == word[j]:
        j += 1
    trie += chr(97 + j)
    trie += word[j:]
    prev_word = word
print(f'len(trie) = {len(trie)}')

gzipped = gzip.compress(trie.encode())
print(f'len(gzipped) = {len(gzipped)}')
encoded = base64.b64encode(gzipped)
print(f'len(encoded) = {len(encoded)}')
decoded = encoded.decode()
print(f'len(decoded) = {len(decoded)}')

with open('dict_compressed.txt', 'w') as f:
    f.write(decoded)
