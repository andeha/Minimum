/*  after-nine.hpp | for .cpp-modelling. */

#ifdef __cplusplus

#define rt₋namespace namespace

rt₋namespace after9₋variables { extern int vector₋init₋error; };

template <typename E> struct vector { struct structa inner; 
  consteval unsigned bytes₋per₋tile() { return sizeof(E) <= 4096 ? 4096 : sizeof(E); }
  vector() { if (structa₋init(sizeof(E),bytes₋per₋tile(),&inner,Alloc)) { 
   Pult💡(after9₋variables::vector₋init₋error); } }
  ~vector() { deinit₋structa(&inner,Fallow); }
  E& operator[](__builtin_int_t idx) { return (E&)structa₋at(idx,inner); }
  int append(const E& elem) { return copy₋append₋items(1,elem,inner,Alloc); }
  __builtin_int_t count() { return structa₋count(&inner); }
};

typedef vector<char32̄_t> unicode₋string₁; /* ⬷ a․𝘬․a 'appendable unicode₋text'. */
typedef void ᶿ﹡ unicode₋string₂; /* ⬷ a․𝘬․a 'editable₋unicode₋text'. */

#endif
