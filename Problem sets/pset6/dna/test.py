import dna

se = "AAGGTAAGTTTAGAATATAAAAGGTGAGTTAAATAGAATAGGTTAAAATTAAAGGAGATCAGATCAGATCAGATCTATCTATCTATCTATCTATCAGAAAAGAGTAAATAGTTAAAGAGTAAGATATTGAATTAATGGAAAATATTGTTGGGGAAAGGAGGGATAGAAGG"
sub = "AGATC"
#print(dna.longest_match(se, sub))

#s = dna.read_sequence("CS50X/pset/pset6/dna/sequences/1.txt")
#print(s)


database = dna.read_database("/workspaces/113283050/CS50X/pset/pset6/dna/databases/small.csv")
print(database)