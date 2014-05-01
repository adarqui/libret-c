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



--------------
TODO:
	Add tests for the multi-variable macros (V1-V3) etc.
--------------


Installation:

	make test
	make install


How to use ret.h:

	Check the test.c file for further usage.



-- adarqui
