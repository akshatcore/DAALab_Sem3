#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int u;
    int v;
    long long w;
} Edge;

int main()
{
    int V, E;

    scanf("%d", &V);
    scanf("%d", &E);

    Edge *edges = (Edge *)malloc(E * sizeof(Edge));

    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %lld",
              &edges[i].u,
              &edges[i].v,
              &edges[i].w);
    }

    int src;
    scanf("%d", &src);

    long long *dist = (long long *)malloc((V + 1) * sizeof(long long));
    int *parent = (int *)malloc((V + 1) * sizeof(int));

    /* Initialize */
    for (int i = 1; i <= V; i++)
    {
        dist[i] = LLONG_MAX;
        parent[i] = -1;
    }

    dist[src] = 0;

    /*
       Bellman-Ford:
       Relax all edges V-1 times
    */
    for (int i = 1; i <= V - 1; i++)
    {
        int changed = 0;

        for (int j = 0; j < E; j++)
        {
            int u = edges[j].u;
            int v = edges[j].v;
            long long w = edges[j].w;

            if (dist[u] != LLONG_MAX &&
                dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                changed = 1;
            }
        }

        /* No changes means shortest paths are finalized */
        if (!changed)
            break;
    }

    /*
       Check for negative weight cycle
       reachable from source
    */
    for (int i = 0; i < E; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;
        long long w = edges[i].w;

        if (dist[u] != LLONG_MAX &&
            dist[u] + w < dist[v])
        {
            printf("Negative cycle detected\n");

            free(edges);
            free(dist);
            free(parent);

            return 0;
        }
    }

    /*
       Print result for every vertex except source
    */
    for (int v = 1; v <= V; v++)
    {
        if (v == src)
            continue;

        /* Vertex is unreachable */
        if (dist[v] == LLONG_MAX)
        {
            printf("%d INF None\n", v);
        }
        else
        {
            /*
               Store path in reverse order
            */
            int *path = (int *)malloc((V + 1) * sizeof(int));
            int count = 0;

            int current = v;

            while (current != -1)
            {
                path[count++] = current;

                if (current == src)
                    break;

                current = parent[current];
            }

            printf("%d %lld ", v, dist[v]);

            /*
               Print path from source to destination
            */
            for (int i = count - 1; i >= 0; i--)
            {
                printf("%d", path[i]);

                if (i > 0)
                    printf("->");
            }

            printf("\n");

            free(path);
        }
    }

    free(edges);
    free(dist);
    free(parent);

    return 0;
}
