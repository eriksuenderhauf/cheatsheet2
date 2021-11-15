//Problem D. Do use segment tree
//von PreFinals Moscow Workshops 2019, Day 1
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int UNUSED = -12345;
struct element
{
	ll ans,pre,suf,sum;
};
const element IDENTITY = {UNUSED,UNUSED,UNUSED,UNUSED};
void merge(element &r, element &a, element &b)
{
	if (a.ans==UNUSED)
		r=b;
	else if (b.ans==UNUSED)
		r=a;
	else
	{
		r.ans=max(max(a.ans,b.ans),a.suf+b.pre);
		r.pre=max(a.pre,a.sum+b.pre);
		r.suf=max(b.suf,b.sum+a.suf);
		r.sum=a.sum+b.sum;
	}
}

struct segtree
{
	int n;
	vector<element> tree;
	vector<int> lazy;
	void build(int i, int l, int r, vector<int> &a)
	{
		if (l==r)
		{
			tree[i].ans=tree[i].sum=
				tree[i].pre=tree[i].suf=a[l-1];
			return;
		}
		build(2*i,l,(l+r)/2,a);
		build(2*i+1,(l+r)/2+1,r,a);
		merge(tree[i],tree[2*i],tree[2*i+1]);
	}
	segtree(vector<int> &a)
	{
		n=a.size();
		tree.resize(4*(n+1));
		lazy.resize(tree.size(),UNUSED);
		build(1,1,n,a);	
	}
	void lazyupd(int i, int l, int r)
	{
		if (lazy[i]!=UNUSED)
		{
			tree[i].ans=max(lazy[i]*1LL,(r-l+1)*1LL*lazy[i]);
			tree[i].pre=tree[i].suf=tree[i].ans;
			tree[i].sum=(r-l+1)*1LL*lazy[i];
			if (l!=r)
			{
				lazy[2*i]=lazy[i];
				lazy[2*i+1]=lazy[i];
			}
			lazy[i]=UNUSED;
		}
	}
	void set(int i, int l, int r, int sl, int sr, int c)
	{
		lazyupd(i,l,r);
		if (l>sr||r<sl)
			return;
		if (l>=sl&&r<=sr)
		{
			lazy[i]=c;
			lazyupd(i,l,r);
			return;
		}
		set(2*i,l,(l+r)/2,sl,sr,c);
		set(2*i+1,(l+r)/2+1,r,sl,sr,c);
		merge(tree[i],tree[2*i],tree[2*i+1]);
	}
	void set(int l, int r, int c) { set(1,1,n,l,r,c); }
	element query(int i, int l, int r, int sl, int sr)
	{
		if (l>sr||r<sl)
			return IDENTITY;
		lazyupd(i,l,r);
		if (l>=sl&&r<=sr)
			return tree[i];
		element a=query(2*i,l,(l+r)/2,sl,sr),
				b=query(2*i+1,(l+r)/2+1,r,sl,sr);
		merge(a,a,b);
		return a;
	}
	element query(int l, int r) { return query(1,1,n,l,r); }
};

const int MAX_N = 200005;

int n,w[MAX_N],par[MAX_N],size[MAX_N],heavy[MAX_N],depth[MAX_N],path[MAX_N],head[MAX_N],tidx[MAX_N];
vector<int> adjl[MAX_N];
vector<segtree> trees;

int dfs(int i)
{
	size[i]=1;
	for (int c : adjl[i])
		if (c!=par[i])
		{
			par[c]=i;
			depth[c]=depth[i]+1;
			size[i]+=dfs(c);
			if (size[heavy[i]]<size[c])
				heavy[i]=c;
		}
	return size[i];
}

void hld()
{
	int num=0;
	for (int i=1; i<=n; i++)
		if (!par[i]||heavy[par[i]]!=i)
		{
			vector<int> ws;
			for (int j=i; j; j=heavy[j])
			{
				ws.push_back(w[j]);
				head[j]=i;
				tidx[j]=depth[j]-depth[i]+1;
				path[j]=num;
			}
			trees.push_back(segtree(ws));
			num++;
		}
}

int lca(int a, int b)
{
	while (path[a]!=path[b])
		if (depth[head[a]]<depth[head[b]])
			b=par[head[b]];
		else
			a=par[head[a]];
	return depth[a]<depth[b]?a:b;
}

void walk(int a, int p, int c) //p inklusive
{
	while (path[a]!=path[p])
	{
		trees[path[a]].set(1,tidx[a],c);
		a=par[head[a]];
	}
	trees[path[a]].set(tidx[p],tidx[a],c);
}

void change(int a, int b, int c)
{
	int l=lca(a,b);
	walk(a,l,c);
	walk(b,l,c);
}

element walk2(int a, int p) //p exklusive
{
	element res=IDENTITY;
	while (path[a]!=path[p])
	{
		element x=trees[path[a]].query(1,tidx[a]);
		merge(res,x,res);
		a=par[head[a]];
	}
	if (a!=p)
	{
		element x=trees[path[a]].query(tidx[p]+1,tidx[a]);
		merge(res,x,res);
	}
	return res;
}

ll query(int a, int b)
{
	int l=lca(a,b);
	if (l==a)
		swap(a,b);
	element e1=walk2(a,l);
	swap(e1.pre,e1.suf);
	element e2=walk2(b,l);
	element em=trees[path[l]].query(tidx[l],tidx[l]);
	merge(e1,e1,em);
	if (l!=b)
		merge(e1,e1,e2);
	return e1.ans;
}

int main()
{
	int q;
	scanf("%d %d",&n,&q);
	for (int i=1; i<=n; i++)
		scanf("%d",w+i);
	for (int i=1; i<n; i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		adjl[a].push_back(b);
		adjl[b].push_back(a);
	}
	depth[1]=1;
	dfs(1);
	hld();
	while (q--)
	{
		int t,a,b,c;
		scanf("%d %d %d %d",&t,&a,&b,&c);
		if (t==1)
			change(a,b,c);
		else
			printf("%lld\n",query(a,b));
	}
	return 0;
}
