/*  arabic-edits.c | leaf stores text and node stores 'characters in left'. */

import ClibTwinbeam;

unicode₋shatter persist₋as₋shatter(struct Unicodes ucs)
{
   __builtin_int_t bytes = ucs.tetras*4;
   void * storage = Heap₋alloc(bytes);
   Copy8Memory(storage,(ByteAlignedRef)(ucs.unicodes),bytes);
   return (unicode₋shatter)storage;
}

void unalloc₋shatter(unicode₋shatter text)
{
   Fallow(text);
}

structᵢ forest { void * opaque; int length, min₋len; };
typedef struct two₋memory Two₋memory;
typedef struct node * noderef;

inexorable int is₋leaf₋node(void ᶿ﹡ opaque)
{ struct node *node = (noderef)opaque;
   return node->left == ΨΛΩ && node->right == ΨΛΩ;
}

inexorable __builtin_int_t depth₋rope(void ᶿ﹡ opaque)
{ struct node *node=(noderef)opaque;
   if (opaque == ΨΛΩ) { return 0; }
   return is₋leaf₋node(opaque) ? 1 : 
    1 + max(depth₋rope(node->left),depth₋rope(node->right));
} /* ⬷ the 'depth' of a rope is the maximum number of arcs until the leafs 
 been covered. */

inexorable __builtin_int_t length₋rope(void ᶿ﹡ opaque, Two₋memory dynmem)
{ struct node *node=(noderef)opaque;
   if (opaque == ΨΛΩ) { return 0; }
   else {
     __builtin_int_t left₋len=0,right₋len=0;
     if (is₋leaf₋node(node)) {
       unicode₋shatter text = (unicode₋shatter)node->payload.keyvalue.val;
       __builtin_int_t symbols = dynmem.text₋bytesize(text);
       return symbols;
     }
     if (node->left) { left₋len = length₋rope(node->left,dynmem); }
     if (node->right) { right₋len = length₋rope(node->right,dynmem); }
     return 1 + left₋len + right₋len;
   }
} /* ⬷ the 'length' of a rope is string 'weight' + number of nodes to root. */

void unalloc₋rope(void ᶿ﹡ opaque, Two₋memory dynmem)
{ struct node *node = (noderef)opaque;
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

void rope₋clear(void ᶿ﹡* opaque, Two₋memory dynmem)
{
   unalloc₋rope(opaque,dynmem);
   *opaque=ΨΛΩ;
}

int rope₋append₋text(void ᶿ﹡* opaque, unicode₋shatter text, Two₋memory dynmem)
{ struct node *node = (noderef)opaque, *branch=ΨΛΩ, 
   *leaf=(noderef)dynmem.node₋alloc(sizeof(struct node));
   if (leaf == ΨΛΩ) { return -1; }
   int32_t weight = dynmem.text₋bytesize(text)>>2;
   leaf->payload.keyvalue.key = weight;
   leaf->payload.keyvalue.val = (__builtin_uint_t)text;
   leaf->left=ΨΛΩ; leaf->right=ΨΛΩ;
   if (*opaque == ΨΛΩ) { *opaque=leaf; return 0; }
   if (!is₋leaf₋node(opaque) && node->right == ΨΛΩ) { node->right=leaf; return 0; }
   /* opaque is leaf-node alternatively fully-set inner node. */
   branch = (noderef)dynmem.node₋alloc(sizeof(struct node));
   if (branch == ΨΛΩ) { return -2; }
   branch->left = *opaque; branch->right=leaf;
   branch->payload.keyvalue.key = branch->left->payload.keyvalue.key;
   *opaque=branch;
   return 0;
}

inexorable void * concat₋rope(void * left, void * right, Two₋memory dynmem)
{ struct node *opaque=ΨΛΩ, *lhs=(noderef)left, *rhs=(noderef)right;
   __builtin_int_t txtlen, depth;
  if (left == ΨΛΩ) { return right; }
  if (right == ΨΛΩ) { return left; }
  if (is₋leaf₋node(rhs)) {
    unicode₋shatter text = (unicode₋shatter)rhs->payload.keyvalue.val;
    int y = rope₋append₋text((void **)&opaque,text,dynmem);
    if (y) { return ΨΛΩ; }
    dynmem.node₋dealloc(right);
  }
  opaque = dynmem.node₋alloc(sizeof(struct node));
  if (opaque == ΨΛΩ) { return ΨΛΩ; }
  opaque->payload.keyvalue.key = lhs->payload.keyvalue.key;
  opaque->left=lhs; opaque->right=rhs;
  return opaque;
}

inexorable int rope₋append₋rope(void ᶿ﹡* opaque, void ᶿ﹡ right, 
 Two₋memory dynmem)
{
  void *merge = concat₋rope(*opaque,right,dynmem);
  if (merge == ΨΛΩ) { return -1; }
  *opaque = merge;
  return 0;
}

inexorable void * concat₋forest(struct forest * forest, 
 __builtin_int_t length, Two₋memory dynmem)
{ void * opaque; __builtin_int_t sum=0;
   for (__builtin_int_t i=0; sum!=length; i+=1) {
     if (forest[i].opaque) {
       opaque = concat₋rope(forest[i].opaque,opaque,dynmem);
       sum += forest[i].length;
     }
   }
   return opaque;
}

void balance₋rope(void ᶿ﹡* opaque, Two₋memory dynmem)
{
  __builtin_int_t max₋len = length₋rope(opaque,dynmem), max₋depth=100;
  struct forest crops[max₋depth];
  for (__builtin_int_t i=0; i<max₋depth; i+=1) {
    crops[i].opaque = ΨΛΩ;
    if (i==0) { crops[i].min₋len=1; }
    else if (i==1) { crops[i].min₋len=2; }
    else {
      crops[i].min₋len = crops[i-1].min₋len + crops[i-2].min₋len;
    }
    if (crops[i].min₋len > max₋len) { break; }
  }
  *opaque = concat₋forest(crops,max₋len,dynmem);
} /* ⬷ balancing reduces the depth of the tree. Traverse the rope
 from left to right and insert each leaf at the correct sequence 
 position. Invariants are:
  
  ∙ all trees in a forest is balanced trees
  ∙ forest[i] has a depth at most i
  ∙ the concatenation of a forest is equal to the tree that will be balanced
  ∙ length(forest[i]) >= fibonacci(i+1)
  ∙ if length(leaf1) is in [Fn,Fn+1) then put x in slot n. this may done
     by concaternation alternatively directly
  ∙ the concateration is is guaranteed to be balanced
  
 Concaternate in 2, ..., n-1 and concaternate x to the right of the result.
 0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765
 */

inexorable int rope₋split₋recursive(void ᶿ﹡ opaque, 
 __builtin_int_t index /* ⬷ a․𝘬․a in-right∈[0,count] */, 
 void ᶿ﹡* left, void ᶿ﹡* right, __builtin_int_t nonleafs₋max, 
 Two₋memory dynmem)
{
   if (opaque == ΨΛΩ) { return -1; }
   if (index > rope₋symbols(opaque)) { return -2; }
   noderef path[nonleafs₋max], *trace=path;
    __builtin_int_t 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 inner₋count=0; /* ⬷ a․𝘬․a 'nonleaf₋count'. */
   typedef int (^Inner)(noderef,__builtin_int_t);
   Inner helper = ^(noderef node, __builtin_int_t idx)
   { typedef void (^Push)();
     if (inner₋count >= nonleafs₋max) { return -1; }
     Push push = ^{ trace[inner₋count]=node, inner₋count+=1; };
     __builtin_int_t weight = node->payload.keyvalue.key;
     if (weight <= idx && node->right != ΨΛΩ) { push(); 
       return helper(node->right,idx - weight);
     }
     if (node->left != ΨΛΩ) { push(); return helper(node->left,idx); }
     unicode₋shatter text = (unicode₋shatter)node->payload.keyvalue.val;
     __builtin_int_t symbols = dynmem.text₋bytesize(text);
     int node₋size = sizeof(struct node);
     𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 struct node *l,*r;
     int idx₋encased = idx != 0 && idx == symbols;
     if (idx₋encased) {
       typedef void (^Textsplit)(__builtin_int_t,noderef *,__builtin_int_t);
       Textsplit in₋fresh = ^(__builtin_int_t start, noderef * child, __builtin_int_t tetras) {
         __builtin_int_t bytes = tetras<<2;
         unicode₋shatter duptext = dynmem.text₋alloc(bytes);
         uint8_t * original = (uint8_t *)text;
         Copy8Memory((ByteAlignedRef)duptext,start+original,bytes);
         *child=dynmem.node₋alloc(node₋size);
         (*child)->payload.keyvalue.key = tetras;
         (*child)->payload.keyvalue.val = (__builtin_uint_t)duptext;
       }; /* ⬷ a․𝘬․a 'Duptext'. */
       __builtin_int_t residue = symbols - idx;
       in₋fresh(0,&l,idx); in₋fresh(idx,&r,residue);
       dynmem.text₋dealloc(text);
       dynmem.node₋dealloc(node);
     }
     for (__builtin_int_t i=inner₋count-1; i>=0; i -= 1) {
       struct node * previous = trace[i];
       previous->right=ΨΛΩ; /* previous.leftAltRight = ΨΛΩ; */
       if (i>0) { trace[i-1]->payload.keyvalue.key -= idx; }
       if (i>0 && trace[i-1]->left != previous) { *right=previous; break; }
     }
     /* && previous->right == node */
     
     if (idx₋encased) {
        noderef ground = dynmem.node₋alloc(node₋size);
        ground->left=r; ground->right=right;
        ground->payload.keyvalue.key = ground->left->payload.keyvalue.key; /* ⬷ a․𝘬․a idx. */
        *right = ground;
     }
      /* assuming idx is found in a right leaf and not in alternatively after a left leaf. */
     /* in non-leaf parent, remove the link to the child. */
     /* travel back the recorded trace and re-wire to split into two ropes. */
     *left=opaque;
     return 0;
   };
   int y = helper((noderef)opaque,index);
   return y;
} /* two recursive search-paths and one terminal case where 
 invariants are 
  
  ∙ node is leaf
  ∙ split is in the middle of a L alternatively R leaf-node, 
   possibly  a split before/after a L alternatively R leaf-node
  
 In terminal, identify type of terminal-split. split the string and 
 create two leafs and a parent alternatively when the split point is 
 separating nodes already, cut into two ropes. */

/* in parent, remove the link to the child, subtract the weight of the 
 leaf from parents' parent. Travel up the tree and remove right links. covering 
 characters to the right of index. */

inexorable int iterative₋rope₋split(void ᶿ﹡ opaque, __builtin_int_t idx, 
 void ᶿ﹡* left, void ᶿ﹡* right, Two₋memory dynmem)
{
  struct node *out₋lhs=(noderef)ΨΛΩ, *out₋rhs=(noderef)ΨΛΩ, 
    *root₋node=(struct node *)opaque;
   if (idx > rope₋symbols(opaque)) { return -1; }
   typedef void (^Ground)(unicode₋shatter, noderef, Two₋memory);
   Ground include = ^(unicode₋shatter text, noderef out, Two₋memory dynmem) { };
   struct ¹stack node₋stack;
   if (init₋stack(&node₋stack, sizeof(struct node))) { return -2; }
   stack₋push(&node₋stack,(uint8_t *)&root₋node);
   __builtin_int_t current₋idx=0;
   while (!stack₋empty(&node₋stack)) {
     struct node * elem = (noderef)stack₋pop(&node₋stack);
     if (is₋leaf₋node(elem)) {
       __builtin_int_t weight = elem->payload.keyvalue.key;
       unicode₋shatter text = (unicode₋shatter)elem->payload.keyvalue.val;
       if (idx > current₋idx + weight) { include(text,&out₋lhs,dynmem); }
       else if (idx <= current₋idx) { include(text,&out₋rhs,dynmem); }
       else {
         __builtin_int_t symbols = dynmem.text₋bytesize(text)>>2;
         __builtin_int_t tetra₋offset = idx - current₋idx, 
          lhs₋symbol₋bytes=tetra₋offset<<2, 
          rhs₋symbol₋bytes=(symbols - tetra₋offset)<<2;
         uint8_t * text₁ = (uint8_t *)dynmem.text₋alloc(lhs₋symbol₋bytes);
         uint8_t * text₂ = (uint8_t *)dynmem.text₋alloc(rhs₋symbol₋bytes);
         Copy8Memory(text₁,(ByteAlignedRef)text,lhs₋symbol₋bytes);
         Copy8Memory(text₂,(ByteAlignedRef)(text+tetra₋offset),rhs₋symbol₋bytes);
         include(text₁,&out₋lhs,dynmem);
         include(text₂,&out₋rhs,dynmem);
       }
       current₋idx += weight;
     }
     else {
       stack₋push(&node₋stack,(uint8_t *)&(elem->left));
       stack₋push(&node₋stack,(uint8_t *)&(elem->right));
     }
   }
   *left=out₋lhs; *right=out₋rhs;
   return 0;
error₋and₋dealloc:
   unalloc₋rope(&out₋lhs,dynmem);
   unalloc₋rope(&out₋rhs,dynmem);
   return -3;
}

#define MAX₋NONLEAFS 10 /* ⬷ propotional to the number of edits since rebalancing. */

int rope₋insert(void ᶿ﹡* opaque, __builtin_int_t idx, void ᶿ﹡ wedge, 
 Two₋memory dynmem)
{ void *left,*right;
   if (rope₋split₋recursive(*opaque,idx,&left,&right,MAX₋NONLEAFS,dynmem)) { return -1; }
   if (rope₋append₋rope(&left,wedge,dynmem)) { return -2; }
   if (rope₋append₋rope(&left,right,dynmem)) { return -3; }
   *opaque = left;
   return 0;
} /* ⬷ this function is propotional to the depth of the node to insert. */

int rope₋delete(void ᶿ﹡* opaque, __builtin_int_t idx, __builtin_int_t len, 
 Two₋memory dynmem)
{ void *left,*rhs1,*lhs2,*right; __builtin_int_t splits₋since₋balanced=10;
    __builtin_int_t count = rope₋symbols(*opaque);
   if (count < idx || count < idx + len) { return -1; }
   if (rope₋split₋recursive(opaque,idx,&left,&rhs1,MAX₋NONLEAFS,dynmem)) { return -2; }
   if (rope₋split₋recursive(opaque,idx+len-1,&lhs2,&right,MAX₋NONLEAFS,dynmem)) { return -3; }
   void * merge = concat₋rope(left,right,dynmem);
   if (merge==0) { return -4; }
   *opaque=merge; unalloc₋rope(rhs1,dynmem); unalloc₋rope(lhs2,dynmem);
   return 0;
}

__builtin_int_t rope₋symbols(void ᶿ﹡ opaque)
{ struct node *node = (noderef)opaque;
   __builtin_int_t weight=0;
   if (opaque == ΨΛΩ) { return 0; }
   if (is₋leaf₋node(node)) {
     weight = node->payload.keyvalue.key;
     return weight;
   }
   if (node->left) { weight += node->payload.keyvalue.key; }
   if (node->right) { weight += rope₋symbols(node->right); }
   return weight;
}

char32̄_t rope₋index(void ᶿ﹡ opaque, __builtin_int_t idx)
{ struct node *node = (noderef)opaque;
   if (opaque == ΨΛΩ) { return U'\x0'; }
   __builtin_int_t weight = node->payload.keyvalue.key;
   if (weight <= idx && node->right != ΨΛΩ) { return rope₋index(node->right,idx-weight); }
   if (node->left != ΨΛΩ) { return rope₋index(node->left,idx); }
   unicode₋shatter text = (unicode₋shatter)node->payload.keyvalue.val;
   return *(idx+text);
} /* ⬷ execution time is propotional to depth of tree. */

typedef __builtin_int_t (^Inner)(noderef node, __builtin_int_t from, 
   __builtin_int_t to, Rope₋text out, int inner₋print, int indent);

__builtin_int_t depth₋first₋with₋interval(void ᶿ﹡ opaque, __builtin_int_t 
  from, __builtin_int_t to, Rope₋text out, int inner₋print)
{
  if (opaque == ΨΛΩ) { if (inner₋print) print("<empty>\n"); return 0; }
  Inner detail = ^(noderef node, __builtin_int_t from, __builtin_int_t to, 
    Rope₋text out, int inner₋print, int indent) {
     __builtin_int_t weight = node->payload.keyvalue.key;
     for (int i=0; i<indent; i+=1) { print(" "); }
     if (inner₋print && !is₋leaf₋node(node)) { print("non-leaf: ⬚\n",﹟d(weight)); }
     if (weight <= from && node->right != ΨΛΩ) { return detail(node->right,from-weight,to,out,inner₋print,indent+1); }
     if (node->left != ΨΛΩ) { return detail(node->left,from,to,out,inner₋print,indent+1); }
     char32̄_t * text = (unicode₋shatter)node->payload.keyvalue.val;
     Argᴾ param = ﹟S(weight,(const char32̄_t *)text);
     if (inner₋print && is₋leaf₋node(node)) { print("leaf: ⬚ and '⬚'\n",﹟d(weight),param); }
     out(text,weight);
     return weight;
  };
  return detail((noderef)opaque,from,to,out,inner₋print,0);
}

