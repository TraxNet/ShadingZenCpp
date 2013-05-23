#ifndef __SHZ_MATH_KD_TREE__
#define __SHZ_MATH_KD_TREE__

#include <array>
#include <stdexcept> 
#include <shz/math/math.hpp>

namespace shz{ namespace spatial{

    template <typename KeyType> struct kd_tree_trais {
        
        
    };

    template <typename Key, typename Value> struct kd_tree {
        typedef kd_tree_trais<Key> traits;
        typedef Key key_type;
        typedef Value value_type;
        typedef size_t size_type;
        typedef value_type* pointer;
        typedef value_type& reference;
        typedef const value_type* const_pointer;
        typedef const value_type& const_reference;
        
    private:
        size_type numNodes;
        
    public:
        
        
        kd_tree() : numNodes(size_type()) { }
        
        kd_tree& operator = (const kd_tree<Key, Value>& other) { }
        
        size_type size() const { return numNodes; }
        size_type max_size() const { return size_type(-1); }
        bool empty() const { return size() == size_type(); }
    };
} }

#endif // __SHZ_MATH_KD_TREE__