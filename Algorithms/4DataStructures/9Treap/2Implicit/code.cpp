struct treap {
	struct node {
		int size,prio,val;
		node *l=0,*r=0;
	} *root=0;
	int get(node *n) { return n?n->size:0; }
	void upd(node *n) {
		if (n)
			n->size=1+get(n->l)+get(n->r);
	}
	void split(node *n, node *&l, node *&r, int key, int add=0) {
		if (!n)
			return void(l=r=0);
		int nkey=add+get(n->l)+1;
		if (nkey<key)
			split(n->r,n->r,r,key,nkey),l=n;
		else
			split(n->l,l,n->l,key,add),r=n;
		upd(n);
	}
	void merge(node *l, node *r, node *&n) {
		if (!l||!r)
			n=l?l:r;
		else if (l->prio>r->prio)
			merge(l->r,r,l->r),n=l;
		else
			merge(l,r->l,r->l),n=r;
		upd(n);
	}
	void insert(int pos, int val) {
		node *n=new node();
		n->prio=rand(),n->val=val;
		node *l,*r;
		split(root,l,r,pos);
		merge(l,n,l);
		merge(l,r,root);
	}
	void remove(int pos) {
		node *l,*n,*r;
		split(root,l,r,pos);
		split(r,n,r,2);
		merge(l,r,root);
	}
	int get(int pos) {
		node *l,*n,*r;
		split(root,l,r,pos);
		split(r,n,r,2);
		int res=n?n->val:0;
		merge(l,n,l);
		merge(l,r,root);
		return res;
	}
};
