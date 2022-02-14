from operator import xor


def dijkstra(graph,src):
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
    next = src
    
    while len(nodes) != 0:
        nodes.remove(next)
        Min = 999
        minValue = 999
        print(queue)
        for visit in nodes:
            if graph[next][visit] > 100:
                continue
            distance =  distance_graph[next] + graph[next][visit]
            print('node:', next, 'visit:', visit, 'distance:', distance, 'oldDistance:',distance_graph[visit]) 
            if distance < distance_graph[visit]:
                distance_graph[visit] = distance
                pi[visit] = next

        temp = []
        for i in range(0, length):
            if i in queue:
                continue
            temp.append(distance_graph[i])
        if len(temp) != 0:
            next = distance_graph.index(min(temp))
        else:
            break
        # print('Min:', Min)
        queue.append(next)
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
    distance, path = dijkstra(graph_list, 0)
    print ('distance array: ', distance)
    for i in range(len(path)):
        print('pi:', i,':', path[i])