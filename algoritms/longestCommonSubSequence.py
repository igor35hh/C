
wordA = "hish"
wordB = "fish"

cell = [[0 for x in range(len(wordA))] for y in range(len(wordB))]
print(cell)

#for (i, j) in zip(range(len(wordA)), range(len(wordB))):
for i in range(len(wordA)):
    for j in range(len(wordB)):
        if wordA[i] == wordB[j]:
            if i > 0 and j > 0:
                cell[i][j] = cell[i-1][j-1]+1       
            else:
                cell[i][j] = 1
        else:
            if i > 0 and j > 0:
                cell[i][j] = max(cell[i-1][j], cell[i][j-1])
            else:
                cell[i][j] = 0
        
print(cell)