#pragma once

#include <string>
#include <sstream>
#include <xmmintrin.h>

using namespace std;

class Utils{
public:
	template<class T>
	static T parseString(string s){
		T temp;
		stringstream ss;

		ss << s;
		ss >> temp;

		return temp;
	}

    static __declspec(noinline) float MyFSel(float mask, float a, float b)
    {
        _mm_store_ss(&a, _mm_or_ps(_mm_and_ps(_mm_set_ss(a), _mm_set_ss(mask)), _mm_andnot_ps(_mm_set_ss(mask), _mm_set_ss(b))));
        return a;
        //float fArray[2] = { a, b };
        //return fArray[*((uint32_t*)(&mask)) >> 31];
    }

    static float minss(float a, float b)
    {
        // Branchless SSE min.
        _mm_store_ss(&a, _mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));
        return a;
    }

    static float maxss(float a, float b)
    {
        // Branchless SSE max.
        _mm_store_ss(&a, _mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
        return a;
    }

    static float clamp(float val, float minval, float maxval)
    {
        // Branchless SSE clamp.
        // return minss( maxss(val,minval), maxval );

        _mm_store_ss(&val, _mm_min_ss(_mm_max_ss(_mm_set_ss(val), _mm_set_ss(minval)), _mm_set_ss(maxval)));
        return val;
    }
};