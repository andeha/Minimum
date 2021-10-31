/*  􀧒 partial-referen.c | identic-sized first-fit leafs allocated. */

import ClibTwinbeam;

inexorable int Equal(const Treeint * l, const Treeint * r)
{ return l->keyvalue.key == r->keyvalue.key; } /* also (l.bits ^ r.bits) & ~signbit == 0 */
inexorable int LessThan(const Treeint * l, const Treeint * r)
{ return l->keyvalue.key < r->keyvalue.key; } /* return l.bits < r.bits; */
inexorable int LessthanOrEqual(const Treeint * l, const Treeint * r)
{ return l->keyvalue.key <= r->keyvalue.key; }

structᵢ node { Treeint leaf; struct node *right, *left; };

inexorable struct node * lookup(struct node ᶿ﹡ node, Treeint target) {
  if (node == ΨΛΩ) { return ΨΛΩ; }
  else { if (Equal(&target,&(node->leaf))) return node;
    else {
      if (LessThan(&target,&(node->leaf))) return lookup(node->left,target);
      else return lookup(node->right,target);
    }
  }
}

inexorable struct node * newNode(Treeint data, void * (^alloc)(int bytes)) {
  struct node * node = (struct node *)alloc(sizeof(node));
  if (node) { return ΨΛΩ; }
  node->left=ΨΛΩ, node->right=ΨΛΩ, node->leaf=data;
  return node;
}

inexorable struct node * insert(struct node ᶿ﹡ node, Treeint material, 
 void * (^alloc)(int bytes)
)
{ /* 1. if the tree is empty, return a new, single node. */
   if (node == ΨΛΩ) { return newNode(material,alloc); }
   else {
     /* 2. otherwise, recur down the tree. */
     if (LessthanOrEqual(&material,&(node->leaf))) {
       node->left = insert(node->left,material,alloc); }
     else { node->right = insert(node->right,material,alloc); }
     return node; /* return the (unchanged) node pointer. */
   }
}

Treeint * Lookup(void ᶿ﹡ opaque, Treeint leafkey) {
  struct node * tell = lookup((struct node *)opaque, leafkey);
  if (tell) { return &(tell->leaf); }
  return ΨΛΩ; /* ⬷ `target` not in tree. */
}

void * Insert(void ᶿ﹡ opaque, Treeint valkey, void * (^alloc)(int bytes))
{ return insert((struct node *)opaque, valkey, alloc); }

void Forall(void ᶿ﹡ opaque, void (^dfs)(Treeint valkey, int * stop))
{ struct node * n = (struct node *)opaque; int stop=false;
   if (n == ΨΛΩ) return;
   dfs(n->leaf,&stop); /* neither infix nor postfix! Prefix. */
   if (stop) return;
   Forall(n->left,dfs);
   Forall(n->right,dfs);
}



