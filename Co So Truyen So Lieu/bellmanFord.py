from operator import xor


def bellmanFord(graph,src):
    length = len(graph)
    type_ = type(graph)
    if type_ == list:
        nodes = [i for i in range(length)]
    distance_graph = []
    pi = []
    for i in range(length):
        distance_graph.append(999)
        pi.append(999)
    queue = []
    
    distance_graph[src] = 0
    queue.append(src)

    while len(queue) != 0:
        node = queue[0]
        queue.remove(node)
        for visit in nodes:
            if visit == pi[node]:
                continue
            if graph[node][visit] > 100:
                continue
            distance =  distance_graph[node] + graph[node][visit]
            print('node:', node, 'visit:', visit, 'distance:', distance, 'oldDistance:',distance_graph[visit]) 
            if distance < distance_graph[visit]:
                distance_graph[visit] = distance
                pi[visit] = node
                queue.append(visit)

    return distance_graph, pi


if __name__ == '__main__':
    graph_list = [  [0  , 5  , 9  , 2  , 999, 999, 999, 999],
                    [5  , 0  , 999, 999, 999, 999, 999, 11 ],
                    [9  , 1  , 0  , 999, 999, 4  , 3  , 999],
                    [2  , 1  , 999, 0  , 3  , 999, 999, 2  ],
                    [999, 999, 999, 999, 0  , 1  , 3  , 1  ],
                    [999, 999, 4  , 999, 1  , 0  , 999, 4  ],
                    [999, 999, 999, 999, 3  , 2  , 0  , 999],
                    [999, 11 , 999, 2  , 999, 4  , 999, 0  ]]
    distance, path = bellmanFord(graph_list, 0)
    print ('distance array: ', distance)
    for i in range(len(path)):
        print('pi:', i,':', path[i])