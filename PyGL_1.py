def buildTristrips(triangles):
    count = 0
    stripless = triangles   #create temp for triangles that holds every triangle not on a strip

    while len(stripless) > 0:   #as long as not empty
        triangle = stripless[0]
        count += 1 #increment counter of strips
        stripless = list(set(stripless) - set(pseudoStrip(triangle))) #make list of triangles not in strips
        stripless = sorted(stripless, key = checkAdjs) #order the list based on how many adjacents the triangle has so we use the triangles with the least amount first

        print('Generated %d tristrips' % count)

def findAdjacent(triangle):
    adjacents = []  #array for adjacent triangles

    for tri in triangle.adjTris:

        if (tri.nextTri == None and tri.prevTri == None):   #only count it as adjacent if it also hasn't been used
            adjacents.append(tri)

    if not adjacents:  #has no adjacents
        return False
    else:
        ret = sorted(adjacents, key = checkAdjs)
        return ret[0]

def checkAdjs(triangle):
    temp = 0

    for tri in triangle.adjTris:

        if tri.nextTri == None and tri.prevTri == None:
            temp += 1

    return temp

def pseudoStrip(triangle):
    triStrip = [triangle]
    freeAdjs = findAdjacent(triangle) #unused adjacents

    while freeAdjs:
        triangle.nextTri = freeAdjs  #the triangles next triangle should be an unused adjacent triangle which has the least number of adjacents as well
        freeAdjs.prevTri = triangle #Make the previous triangle the triangle just used
        triStrip.append(freeAdjs)
        triangle = freeAdjs #the next triangle becomes the current triangle
        freeAdjs = findAdjacent(triangle)

    return triStrip
