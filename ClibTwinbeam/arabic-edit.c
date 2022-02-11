/*  arabic-edits.c | node stores 'characters to left' and in leaf text too. */

import ClibTwinbeam;

unicode₋shatter copy₋to₋shatter(struct Unicodes ucs)
{
   __builtin_int_t bytes = ucs.tetras*4;
   void * storage = Alloc(bytes);
   Copy8Memory(storage,(ByteAlignedRef)(ucs.unicodes),bytes);
   return (unicode₋shatter)storage;
}

void unalloc₋shatter(unicode₋shatter shatter)
{
   Fallow(shatter);
}

inexorable int is₋leaf₋node(void ᶿ﹡ opaque)
{
  struct node * node = (struct node *)opaque;
  return node->left == ΨΛΩ && node->right == ΨΛΩ;
}

void unalloc₋rope(void ᶿ﹡ opaque, struct two₋memory dynmem)
{
   if (opaque == ΨΛΩ) { return; }
   struct node * node = (struct node *)opaque;
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
   *branch = node;
   return 0;
}; /* ⬷ a․𝘬․a make₋branch₋alternatively₋two. */

int rope₋append₋text(void ᶿ﹡* opaque₋root, unicode₋shatter text, struct two₋memory 
 dynmem)
{ struct node *root₋node=(struct node *)*opaque₋root, 
    *branch₋node=(struct node *)ΨΛΩ, /* non-root and root branch. */
    *leaf₋node=(struct node *)ΨΛΩ;
   leaf₋node = (struct node *)dynmem.node₋alloc(sizeof(struct node));
   int32_t weight = dynmem.text₋bytesize(text);
   leaf₋node->payload.keyvalue.key = weight;
   /* ⬷ a․𝘬․a alloc₋node₋copy₋text₋and₋assign₋reference. */
   leaf₋node->payload.keyvalue.val = (__builtin_uint_t)text;
   if (*opaque₋root == ΨΛΩ) { *opaque₋root = leaf₋node; return 0; } /* ⬷ ground ends. */
   if (is₋leaf₋node(root₋node)) {
     if (rope₋wedge(root₋node,leaf₋node,&branch₋node,dynmem.node₋alloc)) {
       unalloc₋rope(leaf₋node,dynmem); return -2; }
     *opaque₋root = branch₋node;
   } else {
     if (root₋node->left == ΨΛΩ) {
       if (root₋node->right == ΨΛΩ) {
         root₋node->left = root₋node->right;
         root₋node->right = leaf₋node;
       }
       else {
         root₋node->left = leaf₋node;
         root₋node->right = ΨΛΩ;
       }
       root₋node->payload.keyvalue.val = root₋node->left->payload.keyvalue.val;
       return 0;
     }
     if (root₋node->right == ΨΛΩ) {
       root₋node->right = leaf₋node;
       root₋node->payload.keyvalue.val = root₋node->left->payload.keyvalue.val + 
        root₋node->right->payload.keyvalue.val;
       return 0;
     }
     if (rope₋wedge(root₋node,leaf₋node,&branch₋node,dynmem.node₋alloc)) {
       unalloc₋rope(leaf₋node,dynmem);
       return -3; }
     *opaque₋root = branch₋node;
   }
   return 0;
}

inexorable int rope₋append₋rope(void ᶿ﹡* opaque, void ᶿ﹡ rhs, 
 void * (*node₋alloc)(__builtin_int_t bytes))
{ struct node *branch₋root=ΨΛΩ, *root₋node=(struct node *)opaque, 
    *rhs₋node=(struct node *)rhs;
   if (rhs == ΨΛΩ) { return 0; }
   if (*opaque == ΨΛΩ) { return 0; }
   if (rope₋wedge(root₋node,rhs₋node,&branch₋root,node₋alloc)) {
    /* unalloc₋rope(leaf₋node); */ return -1; }
   if (branch₋root == ΨΛΩ) { return -2; }
   *opaque = branch₋root;
   rhs = ΨΛΩ;
   return 0;
}

inexorable __builtin_int_t fibonacci(__builtin_int_t n)
{
  __builtin_int_t coefficients[] = { 0,1,1,2,3,5,8,13,21,34,55,89,144,233, 
   377,610,987,1597,2584,4181,6765 };
  return n < 20 ? coefficients[n] : 6765;
}

inexorable void balance₋rope(void ᶿ﹡ opaque)
{
   
} /* length is string weight + number of nodes to root. */

inexorable void ground₋include(unicode₋shatter text, 
 struct node ** new₋root, struct two₋memory dynmem)
{
   int always₋zero = rope₋append₋text((void **)new₋root, 
    text, dynmem);
}

inexorable int rope₋split(void ᶿ﹡ opaque, __builtin_int_t idx, 
 void ᶿ﹡* lhs, void ᶿ﹡* rhs, struct two₋memory dynmem)
{ struct node *out₋lhs=(struct node *)ΨΛΩ, *out₋rhs=(struct node *)ΨΛΩ, 
    *root₋node=(struct node *)opaque;
   if (idx > rope₋length(opaque)) { return -1; }
   struct ¹stack node₋stack;
   if (init₋stack(&node₋stack, sizeof(struct node))) { return -2; }
   push(&node₋stack,(uint8_t *)&root₋node);
   __builtin_int_t current₋idx=0;
   while (!empty(&node₋stack)) {
     struct node * elem = (struct node *)pop(&node₋stack);
     if (is₋leaf₋node(elem)) {
       __builtin_int_t weight = elem->payload.keyvalue.key;
       unicode₋shatter heap₋text = (char32̄_t *)elem->payload.keyvalue.val;
       __builtin_int_t symbols = 1 + dynmem.text₋bytesize(heap₋text)/4;
       /* ⬷ and 'Heap₋object₋size' for length of text. */
       if (idx > current₋idx + weight) { ground₋include(heap₋text,&out₋lhs,dynmem); }
       else if (idx <= current₋idx) { ground₋include(heap₋text,&out₋rhs,dynmem); }
       else {
         __builtin_int_t tetra₋offset = idx - current₋idx, 
          lhs₋symbol₋tetras = tetra₋offset, 
          rhs₋symbol₋tetras = symbols - tetra₋offset, 
          lhs₋symbol₋bytes=4*lhs₋symbol₋tetras, rhs₋symbol₋bytes=4*rhs₋symbol₋tetras;
         void * leaf₁ = dynmem.text₋alloc(4 + lhs₋symbol₋bytes);
         void * leaf₂ = dynmem.text₋alloc(4 + rhs₋symbol₋bytes);
         Copy8Memory(((ByteAlignedRef)(4+(uint8_t *)leaf₁)), 
          (ByteAlignedRef)(uint8_t *)(1+heap₋text), lhs₋symbol₋bytes);
         Copy8Memory(((ByteAlignedRef)(4+(uint8_t *)leaf₂)), 
          (ByteAlignedRef)(uint8_t *)(1+heap₋text+tetra₋offset), rhs₋symbol₋bytes);
         ground₋include(leaf₁,&out₋lhs,dynmem);
         ground₋include(leaf₂,&out₋rhs,dynmem);
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
   return -1;
}

int rope₋insert(void ᶿ﹡* opaque, __builtin_int_t idx, void ᶿ﹡ wedge, 
 struct two₋memory dynmem)
{
   void *tmp₋lhs=ΨΛΩ, *tmp₋rhs=ΨΛΩ;
   if (rope₋split(*opaque,idx,&tmp₋lhs,&tmp₋lhs,dynmem)) { return -1; }
   if (rope₋append₋rope(&tmp₋lhs,wedge,dynmem.node₋alloc)) { return -2; }
   if (rope₋append₋rope(&tmp₋lhs,tmp₋rhs,dynmem.node₋alloc)) { return -3; }
   *opaque = tmp₋lhs;
   /* unalloc₋rope(tmp₋lhs,heap₋dealloc); */
   unalloc₋rope(tmp₋rhs,dynmem);
   return 0;
} /* insertion is propotional to the depth of the node to insert. */

int rope₋delete(void ᶿ﹡* opaque, __builtin_int_t idx, __builtin_int_t len, 
 struct two₋memory dynmem)
{
   void *tmp₋lhs=ΨΛΩ, *tmp₋rhs=ΨΛΩ;
   __builtin_int_t length = rope₋length(*opaque);
   if (length < idx || length < idx + len) { return -1; }
   if (rope₋split(*opaque,idx,&tmp₋lhs,&tmp₋rhs,dynmem)) { return -2; }
   unalloc₋rope(opaque,dynmem);
   if (rope₋append₋rope(*opaque,tmp₋lhs,dynmem.node₋alloc)) { return -3; }
   if (rope₋split(tmp₋rhs,len,&tmp₋lhs,&tmp₋rhs,dynmem)) { return -4; }
   if (rope₋append₋rope(opaque,tmp₋rhs,dynmem.node₋alloc)) { return -5; }
   unalloc₋rope(tmp₋lhs,dynmem);
   return 0;
}

__builtin_int_t rope₋length(void ᶿ﹡ opaque)
{
   if (opaque == ΨΛΩ) { return 0; }
   return (__builtin_int_t)(((struct node *)opaque)->payload.keyvalue.val);
}

char32̄_t rope₋index(void ᶿ﹡ opaque, __builtin_int_t idx)
{
   __builtin_int_t lhs₋weight=0;
   if (opaque == ΨΛΩ) { return U'\x0'; }
   else if (is₋leaf₋node(opaque)) {
     return *(idx + 1 + (char32̄_t *)(((struct node *)opaque)->payload.keyvalue.val));
   }
   else {
     struct node * root₋node = (struct node *)opaque;
     if (root₋node->left != ΨΛΩ) {
       lhs₋weight = root₋node->left->payload.keyvalue.key;
       if (lhs₋weight > idx) {
         return rope₋index(root₋node->left,idx);
       }
     }
     if (root₋node ->right == ΨΛΩ) { return U'\x0'; }
     if (idx < lhs₋weight + root₋node->payload.keyvalue.val) {
       return rope₋index(root₋node->right,idx - lhs₋weight);
     }
   }
   return U'\x0';
} /* ⬷ index execution time is propotional to depth of tree. */


