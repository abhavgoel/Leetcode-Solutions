//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends


class DSU
{
    vector<int>rank,parent,size;
    public:
    DSU(int n)
    {
        rank.resize(n+1,0);//n+1 , so it works for both 0 based and 1 based indexing
        size.resize(n+1,1);//every nide has size 1
        parent.resize(n+1);
        for(int i=0;i<=n;i++)
        parent[i]=i;
    }
    int findParent(int node)
    {
        if(node==parent[node])//node itself is the ultimate parent
        return node;

        return parent[node] = findParent(parent[node]);//recursively finding the ultimate parent
    }
    void unionByRank(int u,int v)
    {
        int ultParent_u = findParent(u);
        int ultParent_v = findParent(v);

        if(ultParent_u==ultParent_v)return;

        else if(rank[ultParent_u]<rank[ultParent_v])//rank of u is less, 
        {
            parent[ultParent_u]=ultParent_v;//attach u to v, parent of u is now v
        }
        else if(rank[ultParent_v]<rank[ultParent_u])//rank of v is less,
        {
            parent[ultParent_v]=ultParent_u;// attach v to u, parent of v is now u
        }
        else //both have same ranks, so attatch anyone to other
        {
            parent[ultParent_v]=ultParent_u;//attaching v to u, that means 2nd node to 1st node
            rank[ultParent_u]++;
        }

    }
    void unionBySize(int u,int v)
    {
        int ultParent_u = findParent(u);
        int ultParent_v = findParent(v);

        if(ultParent_u==ultParent_v)return;

        else if(size[ultParent_u]<size[ultParent_v])
        {
            parent[ultParent_u]=ultParent_v;
            size[ultParent_v]+=size[ultParent_u];
        }
        else if(size[ultParent_v]<size[ultParent_u])
        {
            parent[ultParent_v]=ultParent_u;
            size[ultParent_u]+=size[ultParent_v];
        }
        else 
        {
            parent[ultParent_v]=ultParent_u;
            size[ultParent_u]+=size[ultParent_v];
        }
    }

};

class Solution
{
    //kruskal's algo
	public:
	
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        DSU dsu(V);
        vector<pair<int,pair<int,int>>>edges;
        
        for(int i=0;i<V;i++)
        {
            for(auto it:adj[i])
            {
                int adjNode = it[0];
                int wt = it[1];
                
                int node = i;
                
                edges.push_back({wt,{node,adjNode}});
            }
        }
        
        sort(begin(edges),end(edges));
        
        int mstsum=0;
        
        for(auto i:edges)
        {
            int wt = i.first;
            int u = i.second.first;
            int v = i.second.second;
            
            if(dsu.findParent(u)!=dsu.findParent(v))
            {
                mstsum+=wt;
                dsu.unionByRank(u,v);
            }
        }
        return mstsum;
        
        
    }
    
};

//{ Driver Code Starts.


int main()
{
    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj[V];
        int i=0;
        while (i++<E) {
            int u, v, w;
            cin >> u >> v >> w;
            vector<int> t1,t2;
            t1.push_back(v);
            t1.push_back(w);
            adj[u].push_back(t1);
            t2.push_back(u);
            t2.push_back(w);
            adj[v].push_back(t2);
        }
        
        Solution obj;
    	cout << obj.spanningTree(V, adj) << "\n";
    }

    return 0;
}


// } Driver Code Ends