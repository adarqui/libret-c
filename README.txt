Simple set of macros for creating a "tuple" error type: {value, error}. This gives us a return behavior similar to go:

v, err := someFunction(...);

Instead, we return a ret_t struct which declares a value (v) and an error (e). For example:

...
RET_INIT;

_r = someFunction();
if(RET_ISERROR == RET_BOOL_TRUE) {
	errx(1, ...)
}

printf("%s\n", RET_V);



--------
TODO:

	Perhaps we will want the ability to return multiple values. For example: RET_OK3(v1, v2, v3) ... RET_V, RET_V2, RET_V3); (MOST LIKELY WILL IMPLEMENT)

		RET_Vn
		RET_OKn
		RET_ERRORn
		RET_FATALn
		RET_SET_Vn(...)

		etc.. I like it.

		v1, v2, v3, err := someFunction(..)

		_r = someFunction(..)
		v1 = RET_V1
		v2 = RET_V2
		v3 = RET_V3

	We might want to know for sure if the callee set a value. Perhaps we will set a bit in a flag to tell us whether or not 1, 2, 3, or N values were set. (MOST LIKELY WILL IMPLEMENT)

	The only issue with both of the above 'features' will be some of the size of the ret_t struct.


--------------

Installation:

	make test
	make install


How to use ret.h:

	Check the test.c file for further usage.



-- adarqui
