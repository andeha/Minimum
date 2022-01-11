/*  after-nine.h | 'expressive timeserie' and 'bleeding on trees'. */

/* #define EXPERIMENT₋BRIEFED */

/* rt₋namespace after9₋variables { int structa₋init₋error; }; */

template <typename E> struct vector { struct structa inner; 
  consteval unsigned bytes₋per₋tile() { return sizeof(E) <= 4096 ? 4096 : sizeof(E); }
  vector() { if (structa₋init(sizeof(E),bytes₋per₋tile(),&inner,Alloc)) { 
   /* Pult💡(after9-variables::structa₋init₋error); */ } }
  ~vector() { deinit₋structa(&inner,Fallow); }
  E& operator[](__builtin_int_t idx) { return (E&)structa₋at(idx,inner); }
  int append(const E& elem) { return copy₋append₋items(1,elem,inner,Alloc); }
  __builtin_int_t count() { return structa₋count(&inner); }
};

typedef vector<char32̄_t> unicode₋string;


