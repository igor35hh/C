
graph = {
        'a': {'b': -1, 'c':4},
        'b': {'c':  3, 'd':  2, 'e':  2},
        'c': {},
        'd': {'b':  1, 'c':  5},
        'e': {'d': -3}
    }

destination = {node: float('Inf') for node in graph}
destination['a'] = 0
predecessor = {node: None for node in graph}

def find_cost(node, neighbour, graph, destination, predecessor):
    if destination[node] != float('Inf') and destination[neighbour] > destination[node] + graph[node][neighbour]:
        destination[neighbour] = destination[node] + graph[node][neighbour]
        predecessor[neighbour] = node
        
for item in range(len(graph)-1):
    for node in graph:
        for neighbour in graph[node]:
            find_cost(node, neighbour, graph, destination, predecessor)
            
for node in graph:
    for neighbour in graph[node]:
        assert destination[neighbour] <= destination[node] + graph[node][neighbour]


print('destination', destination)
print('predecessor', predecessor)
