/*  arabic-edits.c | leaf stores text and node stores 'characters in left'. */

import ClibTwinbeam;

unicode₋shatter persist₋as₋shatter(struct Unicodes ucs)
{
   __builtin_int_t bytes = ucs.tetras*4;
   void *storage = Heap₋alloc(bytes);
   Copy8Memory(storage,(ByteAlignedRef)(ucs.unicodes),bytes);
   return (unicode₋shatter)storage;
}

void unalloc₋shatter(unicode₋shatter text)
{
   Fallow(text);
}

inexorable int is₋leaf₋node(void ᶿ﹡ opaque)
{ struct node *node = (struct node *)opaque;
   return node->left == ΨΛΩ && node->right == ΨΛΩ;
}

inexorable __builtin_int_t depth₋rope(void ᶿ﹡ opaque)
{ struct node *node=(struct node *)opaque;
   /* if (opaque == ΨΛΩ) { return TriboolUnknown; } */
   return is₋leaf₋node(opaque) ? 0 : 
    1 + max(depth₋rope(node->left),depth₋rope(node->right));
}

inexorable __builtin_int_t length₋rope(void ᶿ﹡ opaque, struct two₋memory dynmem)
{ struct node *node=(struct node *)opaque;
   if (opaque == ΨΛΩ) { return 0LL; }
   else {
     __builtin_int_t left₋len=0,right₋len=0;
     if (is₋leaf₋node(node)) {
       unicode₋shatter text = (unicode₋shatter)node->payload.keyvalue.val;
       __builtin_int_t symbols = dynmem.text₋bytesize(text);
       return symbols;
     }
     if (node->left) { left₋len = length₋rope(node->left,dynmem); }
     if (node->right) { right₋len = length₋rope(node->right,dynmem); }
     return 1LL + left₋len + right₋len;
   }
} /* ⬷ length is string weight + number of nodes to root. */

void unalloc₋rope(void ᶿ﹡ opaque, struct two₋memory dynmem)
{ struct node *node = (struct node *)opaque;
   if (opaque == ΨΛΩ) { return; }
   if (is₋leaf₋node(opaque)) {
    unicode₋shatter text = (unicode₋shatter)(node->payload.keyvalue.val);
    dynmem.text₋dealloc(text);
    dynmem.node₋dealloc(opaque);
   }
   else {
     unalloc₋rope(node->left,dynmem);
     unalloc₋rope(node->right,dynmem);
     dynmem.node₋dealloc(opaque);
   }
}

void rope₋clear(void ᶿ﹡* opaque, struct two₋memory dynmem)
{
   unalloc₋rope(opaque,dynmem);
   *opaque=ΨΛΩ;
}

inexorable int rope₋wedge(struct node * root, struct node * leaf, 
 struct node ** branch, void * (*node₋alloc)(__builtin_int_t bytes)) {
   struct node * node = (struct node *)node₋alloc(sizeof(struct node));
   if (node == ΨΛΩ) { return -1; }
   if (root == ΨΛΩ) {
    node->left = leaf;
    node->right = ΨΛΩ;
    node->payload.bits = 0; /* ⬷ weight. */
    if (leaf != ΨΛΩ) { node->payload.keyvalue.key += 
     leaf->payload.keyvalue.key; }
   } else {
    node->left = root;
    node->right = leaf;
    node->payload.bits = 0; /* ⬷ weight. */
    if (root != ΨΛΩ) { node->payload.keyvalue.key += 
     root->payload.keyvalue.key; }
    if (leaf != ΨΛΩ) { node->payload.keyvalue.key += 
     leaf->payload.keyvalue.key; }
   }
   *branch = node; /* new node stores character count in 'left' and 'right'. */
   return 0;
}; /* ⬷ a․𝘬․a side-effect-free-band-branch. */

int rope₋append₋text(void ᶿ﹡* opaque₋root, unicode₋shatter text, struct 
 two₋memory dynmem)
{ struct node *root=(struct node *)*opaque₋root, 
   *leaf=(struct node *)dynmem.node₋alloc(sizeof(struct node)), 
   *branch=(struct node *)ΨΛΩ;
   int32_t weight = dynmem.text₋bytesize(text);
   leaf->payload.keyvalue.key = weight;
   leaf->payload.keyvalue.val = (__builtin_uint_t)text;
   /* ⬷ a․𝘬․a alloc₋node₋copy₋text₋and₋assign₋reference. */
   if (*opaque₋root == ΨΛΩ) { *opaque₋root=leaf; return 0; } /* ⬷ first ground case. */
   if (is₋leaf₋node(root)) {
     if (rope₋wedge(root,leaf,&branch,dynmem.node₋alloc)) {
       dynmem.node₋dealloc(leaf); return -2; }
     *opaque₋root = branch;
   } else {
     if (root->right == ΨΛΩ) {
       root->right = leaf;
       root->payload.keyvalue.val = root->left->payload.keyvalue.val + 
        root->right->payload.keyvalue.val;
       return 0;
     }
     if (rope₋wedge(root,leaf,&branch,dynmem.node₋alloc)) {
       dynmem.node₋dealloc(leaf); return -1; }
     *opaque₋root = branch;
   } /* ⬷ non-ground case - three nodes deep alternatively more. */
   return 0;
} /* returns '-1' when building too long and '-2' when adding too large. */

inexorable int rope₋append₋rope(void ᶿ﹡* opaque, void ᶿ﹡ rhs, 
 struct two₋memory dynmem)
{ struct node *branch=ΨΛΩ, *root=(struct node *)opaque, 
    *rhs₋node=(struct node *)rhs;
   if (rhs == ΨΛΩ) { return 0; }
   if (*opaque == ΨΛΩ) { return 0; }
   if (rope₋wedge(root,rhs₋node,&branch,dynmem.node₋alloc)) { return -1; }
   if (branch == ΨΛΩ) { return -2; }
   *opaque = branch;
   return 0;
} /* required by delete and insert. */

#define rope₋split iterative₋rope₋split

inexorable void * concat₋rope(void * left, void * right, struct two₋memory dynmem)
{ struct node *opaque=ΨΛΩ, *lhs=(struct node *)left, 
   *rhs=(struct node *)right;
   __builtin_int_t txtlen, depth;
  if (left == ΨΛΩ) { return right; }
  if (right == ΨΛΩ) { return left; }
  if (is₋leaf₋node(rhs)) {
    unicode₋shatter text = (unicode₋shatter)rhs->payload.keyvalue.val;
    int y = rope₋append₋text((void **)&opaque,text,dynmem);
    if (y) { return ΨΛΩ; }
  }
  opaque = dynmem.node₋alloc(sizeof(struct node));
  if (opaque == ΨΛΩ) { return ΨΛΩ; }
  opaque->payload.keyvalue.key = lhs->payload.keyvalue.key;
  opaque->left=lhs; opaque->right=rhs;
  return opaque;
}

struct forest { void * opaque; int length, min₋len; };
/*
  all trees in a forest is balanced trees.
  forest[i] has a depth at most i.
  the concatenation of a forest is equal to the tree that will be balanced.
  length(forest[i]) >= fibonacci(i+1)
  if length(leaf1) is in [Fn,Fn+1) then put x in slot n. this may done
   by concaternation alternatively directly.
  the concateration is is guaranteed to be balanced.
  concaternate in 2, ..., n-1 and concaternate x to the right of the result.
  0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765
 */

inexorable void * concat₋forest(struct forest * forest, 
 __builtin_int_t length, struct two₋memory dynmem)
{ void * opaque; __builtin_int_t sum=0;
   for (__builtin_int_t i=0; sum != length; i+=1) {
     if (forest[i].opaque) {
       opaque = concat₋rope(forest[i].opaque,opaque,dynmem);
       sum += forest[i].length;
     }
   }
   return opaque;
}

void balance₋rope(void ᶿ﹡* opaque, struct two₋memory dynmem)
{
  __builtin_int_t max₋len = length₋rope(opaque,dynmem), max₋depth=100;
  struct forest theforest[max₋depth];
  for (__builtin_int_t i=0; i<max₋depth; i+=1) {
    theforest[i].opaque = ΨΛΩ;
    if (i == 0) { theforest[i].min₋len = 1; }
    else if (i == 1) { theforest[i].min₋len = 2; }
    else {
      theforest[i].min₋len = theforest[i-1].min₋len + theforest[i-2].min₋len;
    }
    if (theforest[i].min₋len > max₋len) { break; }
  }
  *opaque = concat₋forest(theforest,max₋len,dynmem);
} /* ⬷ balancing reduces the depth of the tree. Traverse the rope
 from left to right and insert each leaf at the correct sequence 
 position. */

/* extern __builtin_int_t depth₋first₋with₋interval(noderef,__builtin_int_t,
 __builtin_int_t, void (^segment)(unicode₋shatter)); */

inexorable int rope₋split₋recursive(void ᶿ﹡ opaque, __builtin_int_t index, 
 void ᶿ﹡* left, void ᶿ﹡* right, struct two₋memory dynmem)
{ typedef struct node * noderef; *right=ΨΛΩ;
   if (opaque == ΨΛΩ) { return -1; }
   if (index > rope₋symbols(opaque)) { return -2; }
   __builtin_int_t max₋nonleafs=10 /* rope₋nonleafs(opaque) */;
   noderef path[max₋nonleafs], *trace=path; 
    __builtin_int_t 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 nonleaf₋count=0;
   typedef int (^Inner)(noderef,__builtin_int_t);
   Inner helper = ^(noderef node, __builtin_int_t idx)
   { typedef void (^Push)();
     Push push = ^{ trace[nonleaf₋count]=node; nonleaf₋count += 1; };
     __builtin_int_t weight = node->payload.keyvalue.key;
     if (weight <= idx && node->right != ΨΛΩ) { push(); 
       return helper(node->right,idx - weight);
     }
     if (node->left != ΨΛΩ) { push(); return helper(node->left,idx); }
     /* is-leaf: four cases split in the middle of a L alt. R leaf-node and 
      split after  a L alt. R node. */
  /* split the string and create two leafs and a parent alternatively
    when the split point is separating nodes already, cut into two ropes. */
     unicode₋shatter text = (unicode₋shatter)node->payload.keyvalue.val;
     __builtin_int_t symbols = dynmem.text₋bytesize(text);
     int node₋size = sizeof(struct node);
     𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 struct node *l,*r;
     if (idx != symbols) {
       typedef void (^Textsplit)(__builtin_int_t,noderef *,__builtin_int_t);
       Textsplit in₋fresh = ^(__builtin_int_t start, noderef * child, __builtin_int_t count) {
         unicode₋shatter duptext = dynmem.text₋alloc(count);
         uint8_t * original = (uint8_t *)text;
         Copy8Memory((ByteAlignedRef)duptext,start+original,count);
         *child=dynmem.node₋alloc(node₋size);
         (*child)->payload.keyvalue.key = count;
         (*child)->payload.keyvalue.val = (__builtin_uint_t)duptext;
         __builtin_int_t residue = symbols - idx;
         in₋fresh(0,&l,idx); in₋fresh(idx,&r,residue);
         dynmem.text₋dealloc(text);
         dynmem.node₋dealloc(node);
       }; /* ⬷ a․𝘬․a 'Duptext'. */
     }
     for (__builtin_int_t i=nonleaf₋count-1; i>=0; i -= 1) {
       struct node * previous = trace[i];
       previous->right=ΨΛΩ; /* previous.leftAltRight = ΨΛΩ; */
       if (i>0) { trace[i-1]->payload.keyvalue.key -= idx; }
       if (i>0 && trace[i-1]->left != previous) { *right=previous; break; }
     }
     /* && previous->right == node */
     
     if (idx == symbols) {
        noderef ground = dynmem.node₋alloc(node₋size);
        ground->left=r; ground->right=r;
        ground->payload.keyvalue.key = l->payload.keyvalue.key; /* ⬷ a․𝘬․a idx. */
     }
      /* assuming idx is found in a right leaf and not in alternatively after a left leaf. */
     /* in non-leaf parent, remove the link to the child. */
     /* travel back the recorded trace and re-wire to split into two ropes. */
     *left=opaque;
     return 0;
   };
   return helper((noderef)opaque,index);
} /* in parent, remove the link to the child, subtract the weight of the 
 leaf from parents' parent. Travel up the tree and remove right links. covering 
 characters to the right of index. */

inexorable int iterative₋rope₋split(void ᶿ﹡ opaque, __builtin_int_t idx, 
 void ᶿ﹡* lhs, void ᶿ﹡* rhs, struct two₋memory dynmem)
{
  struct node *out₋lhs=(struct node *)ΨΛΩ, *out₋rhs=(struct node *)ΨΛΩ, 
    *root₋node=(struct node *)opaque;
   if (idx > rope₋symbols(opaque)) { return -1; }
   typedef void (^Ground)(unicode₋shatter, struct node *, struct two₋memory);
   Ground include = ^(unicode₋shatter text, struct node *out, struct two₋memory dynmem) {};
   struct ¹stack node₋stack;
   if (init₋stack(&node₋stack, sizeof(struct node))) { return -2; }
   push(&node₋stack,(uint8_t *)&root₋node);
   __builtin_int_t current₋idx=0;
   while (!empty(&node₋stack)) {
     struct node * elem = (struct node *)pop(&node₋stack);
     if (is₋leaf₋node(elem)) {
       __builtin_int_t weight = elem->payload.keyvalue.key;
       unicode₋shatter text = (char32̄_t *)elem->payload.keyvalue.val;
       __builtin_int_t symbols = 1 + (dynmem.text₋bytesize(text)>>2);
       if (idx > current₋idx + weight) { include(text,&out₋lhs,dynmem); }
       else if (idx <= current₋idx) { include(text,&out₋rhs,dynmem); }
       else {
         __builtin_int_t tetra₋offset = idx - current₋idx, 
          lhs₋symbol₋bytes=tetra₋offset<<2, 
          rhs₋symbol₋bytes=(symbols - tetra₋offset)<<2;
         void * text₁ = dynmem.text₋alloc(4 + lhs₋symbol₋bytes);
         void * text₂ = dynmem.text₋alloc(4 + rhs₋symbol₋bytes);
         Copy8Memory(((ByteAlignedRef)(4+(uint8_t *)text₁)), 
          (ByteAlignedRef)(uint8_t *)(1+text), lhs₋symbol₋bytes);
         Copy8Memory(((ByteAlignedRef)(4+(uint8_t *)text₂)), 
          (ByteAlignedRef)(uint8_t *)(1+text+tetra₋offset), rhs₋symbol₋bytes);
         include(text₁,&out₋lhs,dynmem);
         include(text₂,&out₋rhs,dynmem);
       }
       current₋idx += weight;
     }
     else {
       push(&node₋stack,(uint8_t *)&(elem->left));
       push(&node₋stack,(uint8_t *)&(elem->right));
     }
   }
   *lhs=out₋lhs; *rhs=out₋rhs;
   return 0;
error₋and₋dealloc:
   unalloc₋rope(&out₋lhs,dynmem);
   unalloc₋rope(&out₋rhs,dynmem);
   return -3;
}

int rope₋insert(void ᶿ﹡* opaque, __builtin_int_t idx, void ᶿ﹡ wedge, 
 struct two₋memory dynmem)
{ void *left,*right;
   if (rope₋split(*opaque,idx,&left,&right,dynmem)) { return -1; }
   if (rope₋append₋rope(&left,wedge,dynmem)) { return -2; }
   if (rope₋append₋rope(&left,right,dynmem)) { return -3; }
   *opaque = left;
   return 0;
} /* this function is propotional to the depth of the node to insert. */

int rope₋delete(void ᶿ﹡* opaque, __builtin_int_t idx, __builtin_int_t len, 
 struct two₋memory dynmem)
{ void *left,*rhs1,*lhs2,*right;
    __builtin_int_t count = rope₋symbols(*opaque);
   if (count < idx || count < idx + len) { return -1; }
   if (rope₋split(opaque,idx,&left,&rhs1,dynmem)) { return -2; }
   if (rope₋split(opaque,idx+len-1,&lhs2,&right,dynmem)) { return -3; }
   void * merge = concat₋rope(left,right,dynmem);
   if (merge == 0) { return -4; } /* unalloc-rope(opaque); */
   *opaque=merge; unalloc₋rope(rhs1,dynmem); unalloc₋rope(lhs2,dynmem);
   return 0;
}

__builtin_int_t rope₋symbols(void ᶿ﹡ opaque)
{ struct node *node = (struct node *)opaque;
   __builtin_int_t weight=0;
   if (opaque == ΨΛΩ) { return 0; }
   if (is₋leaf₋node(node)) {
     weight = node->payload.keyvalue.key;
     return weight;
   }
   if (node->left) { weight += node->left->payload.keyvalue.key; }
   if (node->right) { weight += node->right->payload.keyvalue.key; }
   return weight;
}

char32̄_t rope₋index(void ᶿ﹡ opaque, __builtin_int_t idx)
{ struct node *node = (struct node *)opaque;
   if (opaque == ΨΛΩ) { return U'\x0'; }
   __builtin_int_t weight = node->payload.keyvalue.val;
   if (weight <= idx && node->right != ΨΛΩ) { return rope₋index(node->right,idx-weight); }
   if (node->left != ΨΛΩ) { return rope₋index(node->left,idx); }
   unicode₋shatter text = (unicode₋shatter)node->payload.keyvalue.val;
   return *(idx+text);
} /* ⬷ execution time is propotional to depth of tree. */


