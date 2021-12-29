/*  after-9.h | 'expressive timeserie' and 'bleeding on trees'. */

/* #define EXPERIMENT₋BRIEFED */

/* rt₋namespace after9₋variables { int structa₋init₋error; }; */

template <typename E> struct vector { struct structa inner; 
  consteval unsigned bytes₋per₋tile() { return sizeof(E) <= 4096 ? 4096 : sizeof(E); }
  vector() { if (structa₋init(sizeof(E),bytes₋per₋tile(),&inner)) { 
   /* Pult💡(after9-variables::structa₋init₋error); */ } }
  ~vector() { structa₋uninit(&inner); }
  E& operator[](__builtin_int_t idx) { return (E&)inner.structa₋at(idx,inner); }
  int append(const E& elem) { return inner.copy₋append₋items(1,elem,inner); }
  __builtin_int_t count() { return 1 + (inner.structa₋bytes() - 1)/sizeof(E); }
};


