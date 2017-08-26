import math

mentions = dict()

mentions['alex'] = dict()
mentions['alex'][1] = 5.0
mentions['alex'][2] = 3.0
mentions['alex'][5] = 4.0

mentions['rob'] = dict()
mentions['rob'][1] = 4.0
mentions['rob'][6] = 1.0
mentions['rob'][8] = 2.0
mentions['rob'][9] = 3.0

mentions['bob'] = dict()
mentions['bob'][2] = 5.0
mentions['bob'][3] = 5.0

mentions['david'] = dict()
mentions['david'][3] = 4.0
mentions['david'][4] = 3.0
mentions['david'][6] = 2.0
mentions['david'][7] = 1.0

print(mentions)

def distCosine(vecA, vecB):
    print(vecA, vecB)
    def dotProduct(vecA, vecB):
        d = 0.0
        for dim in vecA:
            if dim in vecB:
                #print(dim, vecB)
                d += vecA[dim]*vecB[dim]
        return d
    return dotProduct(vecA,vecB) / math.sqrt(dotProduct(vecA,vecA)) / math.sqrt(dotProduct(vecB,vecB))

def makeRecommendation(userID, userRates, nBestUsers, nBestProducts):
    matches = [(u, distCosine(userRates[userID], userRates[u])) for u in userRates if u != userID]
    print(matches)
    bestMatches = sorted(matches, key=lambda x: (x[1], x[0]), reverse=True)[:nBestUsers]
    print("Most suitable for '%s' users:" % userID)
    for line in bestMatches:
        print("  UserID: %6s  coeff: %6.4f" % (line[0], line[1])) 
          
    sim = dict()
    sim_all = sum([x[1] for x in bestMatches])
    print(sim_all)
    bestMatches = dict([x for x in bestMatches if x[1] > 0.0])
           
    for relatedUser in bestMatches:
        for product in userRates[relatedUser]:
            if not product in userRates[userID]:
                if not product in sim:
                    sim[product] = 0.0
                sim[product] += userRates[relatedUser][product] * bestMatches[relatedUser]
                
    for product in sim:
        sim[product] /= sim_all
        
    bestProducts = sorted(sim.items(), key=lambda x: (x[1], x[0]), reverse=True)[:nBestProducts]
    print("Most suitable products:")
    for prodInfo in bestProducts:
        print("  ProductID: %6s  suitable coeff: %6.4f" % (prodInfo[0], prodInfo[1]))   
    return [(x[0], x[1]) for x in bestProducts]

rec = makeRecommendation('rob', mentions, 5, 5)



