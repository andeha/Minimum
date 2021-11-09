/* 􀓩 ruin-edit.c a․𝘬․a shatter-edit.c | non-interval-node is weight alt․ text. */

import ClibTwinbeam;

structᵢ internal₋rope₋heap {
  void (^text₋dealloc)(void *);
  void (^heap₋dealloc)(void *);
  void * (^heap₋alloc)(__builtin_int_t bytes);
  void * (^text₋alloc)(__builtin_int_t bytes);
};

inexorable int is₋leaf₋node(void ᶿ﹡ opaque)
{
  struct node * node = (struct node *)opaque;
  return node->left == ΨΛΩ && node->right == ΨΛΩ;
}

void unalloc₋rope(void ᶿ﹡ opaque, void (^heap₋dealloc)(void *), 
 void (^text₋dealloc)(void *))
{
   if (opaque == ΨΛΩ) { return; }
   struct node * node = (struct node *)opaque;
   if (is₋leaf₋node(opaque)) {
    union Tetra𝘖rUnicode * text = (union Tetra𝘖rUnicode *)(node->payload.keyvalue.val);
    text₋dealloc(text);
    heap₋dealloc(opaque);
   }
   else {
     unalloc₋rope(node->left,heap₋dealloc,text₋dealloc);
     unalloc₋rope(node->right,heap₋dealloc,text₋dealloc);
     heap₋dealloc(opaque);
   }
}

inexorable int rope₋wedge(struct node * root, struct node * leaf, 
 struct node ** branch, void * (^node₋alloc)(__builtin_int_t bytes)) {
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

int rope₋append₋text(void ᶿ﹡* opaque₋root, union Tetra𝘖rUnicode * 
 length₋prefixed₋text, void (^text₋dealloc)(void *), 
 void (^heap₋dealloc)(void *), void * (^heap₋alloc)(__builtin_int_t bytes))
{ struct node *root₋node=(struct node *)*opaque₋root, 
    *branch₋node=(struct node *)ΨΛΩ, /* non-root and root branch. */
    *leaf₋node=(struct node *)ΨΛΩ;
   leaf₋node = (struct node *)heap₋alloc(sizeof(struct node));
   int32_t weight = length₋prefixed₋text[0].count;
   leaf₋node->payload.keyvalue.key = weight;
   /* ⬷ a․𝘬․a alloc₋node₋copy₋text₋and₋assign₋reference. */
   leaf₋node->payload.keyvalue.val = 
    (__builtin_uint_t)&(length₋prefixed₋text[1].uc);
   if (*opaque₋root == ΨΛΩ) { *opaque₋root = leaf₋node; return 0; } /* ⬷ ground ends. */
   if (is₋leaf₋node(root₋node)) {
     if (rope₋wedge(root₋node,leaf₋node,&branch₋node,heap₋alloc)) {
       unalloc₋rope(leaf₋node,heap₋dealloc,text₋dealloc); return -2; }
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
     if (rope₋wedge(root₋node,leaf₋node,&branch₋node,heap₋alloc)) {
       unalloc₋rope(leaf₋node,heap₋dealloc,text₋dealloc);
       return -3; }
     *opaque₋root = branch₋node;
   }
   return 0;
}

inexorable int rope₋append₋rope(void ᶿ﹡* opaque, void ᶿ﹡ rhs, 
 void * (^node₋alloc)(__builtin_int_t bytes))
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
  __builtin_int_t coefficients[] = {0,1,1,2,3,5,8,13,21,34,55,89,144,233,
   377,610,987,1597,2584,4181,6765};
  return n < 20 ? coefficients[n] : 6765;
}

inexorable void balance₋rope(void ᶿ﹡ opaque)
{
   
} /* length is string weight + number of nodes to root. */

inexorable void ground₋include(union Tetra𝘖rUnicode * length₋prefixed₋text, 
 struct node ** new₋root, struct internal₋rope₋heap * coalesced₋ops)
{
   int always₋zero = rope₋append₋text((void **)new₋root, 
    length₋prefixed₋text, coalesced₋ops->text₋dealloc, 
    coalesced₋ops->heap₋dealloc, coalesced₋ops->heap₋alloc);
}

inexorable int rope₋split(void ᶿ﹡ opaque, __builtin_int_t idx, 
 void ᶿ﹡* lhs, void ᶿ﹡* rhs, struct internal₋rope₋heap * coalesced)
{ struct node *out₋lhs=(struct node *)ΨΛΩ, *out₋rhs=(struct node *)ΨΛΩ, 
    *root₋node=(struct node *)opaque;
   if (idx > rope₋length(opaque)) { return -1; }
   struct ¹stack node₋stack;
   if (init₋stack(&node₋stack, sizeof(struct node))) { return -2; }
   push(&node₋stack,(uint8_t *)root₋node);
   __builtin_int_t current₋idx=0;
   while (!empty(&node₋stack)) {
     struct node * elem = (struct node *)pop(&node₋stack);
     if (is₋leaf₋node(elem)) {
       __builtin_int_t weight = elem->payload.keyvalue.key;
       union Tetra𝘖rUnicode * text = (union Tetra𝘖rUnicode *)(elem->payload.keyvalue.val);
       if (idx > current₋idx + weight) { ground₋include(text,&out₋lhs,coalesced); }
       else if (idx <= current₋idx) { ground₋include(text,&out₋rhs,coalesced); }
       else {
         int32_t symbols = text->count;
         __builtin_int_t tetra₋offset = idx - current₋idx, 
          lhs₋symbol₋tetras = tetra₋offset, 
          rhs₋symbol₋tetras = symbols - tetra₋offset, 
          lhs₋symbol₋bytes=4*lhs₋symbol₋tetras, rhs₋symbol₋bytes=4*rhs₋symbol₋tetras;
         void * leaf₁ = coalesced->text₋alloc(4 + lhs₋symbol₋bytes);
         void * leaf₂ = coalesced->text₋alloc(4 + rhs₋symbol₋bytes);
         ((union Tetra𝘖rUnicode *)leaf₁)->count = lhs₋symbol₋tetras;
         ((union Tetra𝘖rUnicode *)leaf₂)->count = rhs₋symbol₋tetras;
         Copy8Memory(((ByteAlignedRef)(4+(uint8_t *)leaf₁)), (ByteAlignedRef)(uint8_t *)(1+text), lhs₋symbol₋bytes);
         Copy8Memory(((ByteAlignedRef)(4+(uint8_t *)leaf₂)), (ByteAlignedRef)(uint8_t *)(1+text+tetra₋offset), rhs₋symbol₋bytes);
         ground₋include(leaf₁,&out₋lhs,coalesced);
         ground₋include(leaf₂,&out₋rhs,coalesced);
       }
       current₋idx += weight;
     }
     else {
       push(&node₋stack,(uint8_t *)(elem->left));
       push(&node₋stack,(uint8_t *)(elem->right));
     }
   }
   *lhs=out₋lhs; *rhs=out₋rhs;
   return 0;
error₋and₋dealloc:
   unalloc₋rope(&out₋lhs,coalesced->heap₋dealloc,coalesced->text₋dealloc);
   unalloc₋rope(&out₋rhs,coalesced->heap₋dealloc,coalesced->text₋dealloc);
   return -1;
}

int rope₋insert(void ᶿ﹡* opaque, __builtin_int_t idx, void ᶿ﹡ wedge, 
 void (^text₋dealloc)(void *), void (^heap₋dealloc)(void *), 
 void * (^node₋alloc)(__builtin_int_t bytes), 
 void * (^text₋alloc)(__builtin_int_t bytes))
{
   void *tmp₋lhs=ΨΛΩ, *tmp₋rhs=ΨΛΩ;
   struct internal₋rope₋heap coalesced₋ops = { text₋dealloc, heap₋dealloc, 
    node₋alloc, text₋alloc };
   if (rope₋split(*opaque,idx,&tmp₋lhs,&tmp₋lhs,&coalesced₋ops)) { return -1; }
   if (rope₋append₋rope(&tmp₋lhs,wedge,node₋alloc)) { return -2; }
   if (rope₋append₋rope(&tmp₋lhs,tmp₋rhs,node₋alloc)) { return -3; }
   *opaque = tmp₋lhs;
   /* unalloc₋rope(tmp₋lhs,heap₋dealloc); */
   unalloc₋rope(tmp₋rhs,heap₋dealloc,text₋dealloc);
   return 0;
} /* insertion is propotional to the depth of the node to insert. */

int rope₋delete(void ᶿ﹡* opaque, __builtin_int_t idx, __builtin_int_t len, 
 void (^text₋dealloc)(void *), void (^heap₋dealloc)(void *), 
 void * (^node₋alloc)(__builtin_int_t bytes), 
 void * (^text₋alloc)(__builtin_int_t bytes))
{
   void *tmp₋lhs=ΨΛΩ, *tmp₋rhs=ΨΛΩ;
   __builtin_int_t length = rope₋length(*opaque);
   if (length < idx || length < idx + len) { return -1; }
   struct internal₋rope₋heap coalesced₋ops = { text₋dealloc, heap₋dealloc, 
    node₋alloc, text₋alloc };
   if (rope₋split(*opaque,idx,&tmp₋lhs,&tmp₋rhs,&coalesced₋ops)) { return -2; }
   unalloc₋rope(opaque,heap₋dealloc,text₋dealloc);
   if (rope₋append₋rope(*opaque,tmp₋lhs,node₋alloc)) { return -3; }
   if (rope₋split(tmp₋rhs,len,&tmp₋lhs,&tmp₋rhs,&coalesced₋ops)) { return -4; }
   if (rope₋append₋rope(opaque,tmp₋rhs,node₋alloc)) { return -5; }
   unalloc₋rope(tmp₋lhs,heap₋dealloc,text₋dealloc);
   return 0;
}

__builtin_int_t rope₋length(void ᶿ﹡ opaque)
{
   if (opaque == ΨΛΩ) { return 0; }
   return (__builtin_int_t)(((struct node *)opaque)->payload.keyvalue.val);
}

char32_t rope₋index(void ᶿ﹡ opaque, __builtin_int_t idx)
{
   __builtin_int_t lhs₋weight=0;
   if (opaque == ΨΛΩ) { return U'\x0'; }
   else if (is₋leaf₋node(opaque)) {
     return *(idx + 1 + (char32_t *)(((struct node *)opaque)->payload.keyvalue.val));
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
} /* index execution time is propotional to depth of tree. */


