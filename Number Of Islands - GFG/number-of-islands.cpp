//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++
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
class Solution {
  public:
  vector<int>dx={1,-1,0,0};
vector<int>dy={0,0,1,-1};
    vector<int> numOfIslands(int n, int m, vector<vector<int>> &operators) {
        //firstly lets treat grid indexes as nodes
        //there would be total of n*m nodes , so lets create a DSU with n*m nodes
        
        DSU dsu(n*m);
        
        //n = row
        //m = col 
        //every index can be converted to node by i*m + col;
        vector<vector<int>>vis(n,vector<int>(m,0));//basically a grid and vis array
        vector<int>ans;
        int count = 0;
        
        //the idea is to add 1 to the island counter everytime there is an operations,
        //and subtract count by 1 everytime an adjacent cell is 1(land)
        for(auto i:operators)
        {
            int row = i[0];
            int col = i[1];
            if(vis[row][col]==1)///if same cell visited the count of isalnds would be same,as no new operation is performed
            {
                ans.push_back(count);
                continue;
            }
            
            vis[row][col]=1;
            count++;//increasing everytime but will decrease is islands found nearby afterwards
            
            for(int k=0;k<4;k++)
            {
                int newrow = row+dx[k];
                int newcol = col+dy[k];
                
                if(newrow>=0 && newcol>=0 && newrow<n && newcol<m && vis[newrow][newcol]==1)
                {
                    int parentNode = row*m + col;
                    int node = newrow*m+newcol;
                    if(dsu.findParent(parentNode)!=dsu.findParent(node))
                    {
                        count--;
                        dsu.unionByRank(node,parentNode);
                    }
                }
                
                
            }
            
            
            
            ans.push_back(count);
        }
        return ans;
        
        
    }
};


//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n,m,k; cin>>n>>m>>k;
        vector<vector<int>> a;
        
        for(int i=0; i<k; i++){
            vector<int> temp;
            for(int j=0; j<2; j++){
                int x; cin>>x;
                temp.push_back(x);
            }
            a.push_back(temp);
        }
    
        Solution obj;
        vector<int> res = obj.numOfIslands(n,m,a);
        
        for(auto x : res)cout<<x<<" ";
        cout<<"\n";
    }
}

// } Driver Code Ends