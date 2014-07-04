#ifndef __SHZ_MATH_KD_TREE_EXCEPTIONS__
#define __SHZ_MATH_KD_TREE_EXCEPTIONS__

#include <stdexcept> 

namespace shz{ namespace spatial{
	class kdtree_max_nodes_overflow_exception : public std::exception
	{
    private:
        std::string reason;
	public:
		kdtree_max_nodes_overflow_exception(const char *what) : reason(what){}
        
        virtual const char* what() const _NOEXCEPT { return reason.c_str(); }
        
        
	};
} }

#endif // __SHZ_MATH_KD_TREE_EXCEPTIONS__