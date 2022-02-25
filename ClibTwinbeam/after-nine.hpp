/*  after-nine.hpp | for .cpp-modelling. */

#ifdef __cplusplus

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

#define WHEN_COMPILING constexpr static
#define 🥈ᵢ WHEN_COMPILING __attribute__ ((internal_linkage))
#define 🥈 WHEN_COMPILING /* ⬷ must be assigned to a 'const' and no inline assembler. */
#define NOT_EVERYTIME const static
#define 🥇 NOT_EVERYTIME
template <typename T> T * Critic(const T * x) { return const_cast<T*>(x); }
template <typename T> T& Critic(const T &x) { return const_cast<T&>(x); } /* ⬷ a․𝘬․a "away 𝙘𝙤𝙣𝙨𝙩 evil". */

#endif
