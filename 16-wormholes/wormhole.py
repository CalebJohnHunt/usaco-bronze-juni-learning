
def generateCombos(w):
    if len(w) == 2:
        return [[(w[0], w[1])]]
    lst = []
    for i in range(len(w)-1):
        lst.append([(w[0], w[i+1])])
        lst += generateCombos(w[1:i] + w[i+1:])
    return lst

print(generateCombos([1,2]))
