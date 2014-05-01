#include "ret.h"
#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

int init_suite(void);
int clean_suite(void);
void libret_init(CU_pSuite);
void libret_test_clr(void);
void libret_test__clr(void);
void libret_test_v(void);
void libret_test__v(void);
void libret_test_e(void);
void libret_test__e(void);
void libret_test_ok(void);
void libret_test_error(void);
void libret_test_fatal(void);
void libret_test_ok_only(void);
void libret_test_error_only(void);
void libret_test_fatal_only(void);

ret_t libret_ok(void);
ret_t libret_error(void);
ret_t libret_fatal(void);

ret_t libret_ok_only(void);
ret_t libret_error_only(void);
ret_t libret_fatal_only(void);

int init_suite(void) {
	return 0;
}

int clean_suite(void) {
	return 0;
}

/*
 * specific cunit tests
 */

void libret_init(CU_pSuite p) {
	CU_add_test(p, "test RET_CLR", libret_test_clr);
	CU_add_test(p, "test _RET_CLR", libret_test__clr);
	CU_add_test(p, "test RET_V", libret_test_v);
	CU_add_test(p, "test _RET_V", libret_test__v);
	CU_add_test(p, "test RET_E", libret_test_e);
	CU_add_test(p, "test _RET_E", libret_test__e);
	CU_add_test(p, "test RET_OK", libret_test_ok);
	CU_add_test(p, "test RET_ERROR", libret_test_error);
	CU_add_test(p, "test RET_FATAL", libret_test_fatal);
	CU_add_test(p, "test RET_OK_ONLY", libret_test_ok_only);
	CU_add_test(p, "test RET_ERROR_ONLY", libret_test_error_only);
	CU_add_test(p, "test RET_FATAL_ONLY", libret_test_fatal_only);
	return;
}

void libret_test_clr(void) {
	RET_INIT;
	RET_CLR;
	CU_ASSERT(RET_V == NULL);
	CU_ASSERT(RET_E == RET_NONE);
	CU_ASSERT(ret_v == NULL);
	CU_ASSERT(ret_e == RET_NONE);
}

void libret_test__clr(void) {
	ret_t hi;
	_RET_CLR(hi);
	CU_ASSERT(_RET_V(hi) == NULL);
	CU_ASSERT(_RET_E(hi) == RET_NONE);
	CU_ASSERT(_ret_v(hi) == NULL);
	CU_ASSERT(_ret_e(hi) == RET_NONE);
}

void libret_test_v(void) {
	int i = 1;
	void * v = &i;
	RET_INIT;
	RET_SET_V(v);
	CU_ASSERT(RET_V == v);
	CU_ASSERT(RET_V == &i);
	ret_set_v(v);
	CU_ASSERT(ret_v == v);
	CU_ASSERT(ret_v == &i);
}

void libret_test__v(void) {
	char * s = "hi";
	ret_t hi;
	_RET_SET_V(hi, s);
	CU_ASSERT(_RET_V(hi) == s);
	_ret_set_v(hi, s);
	CU_ASSERT(_ret_v(hi) == s);
}

void libret_test_e(void) {
	int i = 100;
	RET_INIT;
	RET_SET_E(i);
	CU_ASSERT(RET_E == i);
	ret_set_e(i);
	CU_ASSERT(ret_e == i);
}

void libret_test__e(void) {
	int i = 100;
	ret_t hi;
	_RET_SET_E(hi, i);
	CU_ASSERT(_RET_E(hi) == i);
	_ret_set_e(hi, i);
	CU_ASSERT(_ret_e(hi) == i);
}

void libret_test_ok(void) {
	RET_INIT;
	_r = libret_ok();

	CU_ASSERT(RET_ISOK == RET_BOOL_TRUE);
	CU_ASSERT(RET_ISERROR == RET_BOOL_FALSE);
	CU_ASSERT(RET_ISFATAL == RET_BOOL_FALSE);

	CU_ASSERT(_RET_ISOK(_r) == RET_BOOL_TRUE);
	CU_ASSERT(_RET_ISERROR(_r) == RET_BOOL_FALSE);
	CU_ASSERT(_RET_ISFATAL(_r) == RET_BOOL_FALSE);

	CU_ASSERT(ret_isok == RET_BOOL_TRUE);
	CU_ASSERT(ret_iserror == RET_BOOL_FALSE);
	CU_ASSERT(ret_isfatal == RET_BOOL_FALSE);

	CU_ASSERT(_ret_isok(_r) == RET_BOOL_TRUE);
	CU_ASSERT(_ret_iserror(_r) == RET_BOOL_FALSE);
	CU_ASSERT(_ret_isfatal(_r) == RET_BOOL_FALSE);
}

void libret_test_error(void) {
	RET_INIT;
	_r = libret_error();

	CU_ASSERT(RET_ISOK == RET_BOOL_FALSE);
	CU_ASSERT(RET_ISERROR == RET_BOOL_TRUE);
	CU_ASSERT(RET_ISFATAL == RET_BOOL_FALSE);

	CU_ASSERT(_RET_ISOK(_r) == RET_BOOL_FALSE);
	CU_ASSERT(_RET_ISERROR(_r) == RET_BOOL_TRUE);
	CU_ASSERT(_RET_ISFATAL(_r) == RET_BOOL_FALSE);

	CU_ASSERT(ret_isok == RET_BOOL_FALSE);
	CU_ASSERT(ret_iserror == RET_BOOL_TRUE);
	CU_ASSERT(ret_isfatal == RET_BOOL_FALSE);

	CU_ASSERT(_ret_isok(_r) == RET_BOOL_FALSE);
	CU_ASSERT(_ret_iserror(_r) == RET_BOOL_TRUE);
	CU_ASSERT(_ret_isfatal(_r) == RET_BOOL_FALSE);
}

void libret_test_fatal(void) {
	RET_INIT;
	_r = libret_fatal();

	CU_ASSERT(RET_ISOK == RET_BOOL_FALSE);
	CU_ASSERT(RET_ISERROR == RET_BOOL_TRUE);
	CU_ASSERT(RET_ISFATAL == RET_BOOL_TRUE);

	CU_ASSERT(_RET_ISOK(_r) == RET_BOOL_FALSE);
	CU_ASSERT(_RET_ISERROR(_r) == RET_BOOL_TRUE);
	CU_ASSERT(_RET_ISFATAL(_r) == RET_BOOL_TRUE);

	CU_ASSERT(ret_isok == RET_BOOL_FALSE);
	CU_ASSERT(ret_iserror == RET_BOOL_TRUE);
	CU_ASSERT(ret_isfatal == RET_BOOL_TRUE);

	CU_ASSERT(_ret_isok(_r) == RET_BOOL_FALSE);
	CU_ASSERT(_ret_iserror(_r) == RET_BOOL_TRUE);
	CU_ASSERT(_ret_isfatal(_r) == RET_BOOL_TRUE);
}

void libret_test_ok_only(void) {
	RET_INIT;
	_r = libret_ok_only();

	CU_ASSERT(RET_ISOK == RET_BOOL_TRUE);
	CU_ASSERT(RET_ISERROR == RET_BOOL_FALSE);
	CU_ASSERT(RET_ISFATAL == RET_BOOL_FALSE);

	CU_ASSERT(_RET_ISOK(_r) == RET_BOOL_TRUE);
	CU_ASSERT(_RET_ISERROR(_r) == RET_BOOL_FALSE);
	CU_ASSERT(_RET_ISFATAL(_r) == RET_BOOL_FALSE);

	CU_ASSERT(ret_isok == RET_BOOL_TRUE);
	CU_ASSERT(ret_iserror == RET_BOOL_FALSE);
	CU_ASSERT(ret_isfatal == RET_BOOL_FALSE);

	CU_ASSERT(_ret_isok(_r) == RET_BOOL_TRUE);
	CU_ASSERT(_ret_iserror(_r) == RET_BOOL_FALSE);
	CU_ASSERT(_ret_isfatal(_r) == RET_BOOL_FALSE);
}

void libret_test_error_only(void) {
	RET_INIT;
	_r = libret_error_only();

	CU_ASSERT(RET_ISOK == RET_BOOL_FALSE);
	CU_ASSERT(RET_ISERROR == RET_BOOL_TRUE);
	CU_ASSERT(RET_ISFATAL == RET_BOOL_FALSE);

	CU_ASSERT(_RET_ISOK(_r) == RET_BOOL_FALSE);
	CU_ASSERT(_RET_ISERROR(_r) == RET_BOOL_TRUE);
	CU_ASSERT(_RET_ISFATAL(_r) == RET_BOOL_FALSE);

	CU_ASSERT(ret_isok == RET_BOOL_FALSE);
	CU_ASSERT(ret_iserror == RET_BOOL_TRUE);
	CU_ASSERT(ret_isfatal == RET_BOOL_FALSE);

	CU_ASSERT(_ret_isok(_r) == RET_BOOL_FALSE);
	CU_ASSERT(_ret_iserror(_r) == RET_BOOL_TRUE);
	CU_ASSERT(_ret_isfatal(_r) == RET_BOOL_FALSE);
}

void libret_test_fatal_only(void) {
	RET_INIT;
	_r = libret_fatal_only();

	CU_ASSERT(RET_ISOK == RET_BOOL_FALSE);
	CU_ASSERT(RET_ISERROR == RET_BOOL_TRUE);
	CU_ASSERT(RET_ISFATAL == RET_BOOL_TRUE);

	CU_ASSERT(_RET_ISOK(_r) == RET_BOOL_FALSE);
	CU_ASSERT(_RET_ISERROR(_r) == RET_BOOL_TRUE);
	CU_ASSERT(_RET_ISFATAL(_r) == RET_BOOL_TRUE);

	CU_ASSERT(ret_isok == RET_BOOL_FALSE);
	CU_ASSERT(ret_iserror == RET_BOOL_TRUE);
	CU_ASSERT(ret_isfatal == RET_BOOL_TRUE);

	CU_ASSERT(_ret_isok(_r) == RET_BOOL_FALSE);
	CU_ASSERT(_ret_iserror(_r) == RET_BOOL_TRUE);
	CU_ASSERT(_ret_isfatal(_r) == RET_BOOL_TRUE);
}

ret_t libret_ok(void) {
	RET_INIT;
	RET_OK("hi");
}

ret_t libret_error(void) {
	ret_init;
	ret_error("hi");
}

ret_t libret_fatal(void) {
	ret_t hi;
	_RET_FATAL(hi, "hi");
	return hi;
}

ret_t libret_ok_only(void) {
	RET_INIT;
	RET_SET_V("hi");
	RET_OK_ONLY;
}

ret_t libret_error_only(void) {
	ret_init;
	ret_set_v("hi");
	ret_error_only;
}

ret_t libret_fatal_only(void) {
	ret_t hi;
	_RET_FATAL(hi, "hi");
	return hi;
}

int main(int argc, char *argv[]) {
	CU_pSuite p = NULL;
	if(CU_initialize_registry() != CUE_SUCCESS) {
		errx(1, "CU_initialize_registry: Failed: %i\n", CU_get_error());
	}

	p = CU_add_suite("libret-c tests", init_suite, clean_suite);
	if(p == NULL) {
		CU_cleanup_registry();
		errx(1, "CU_add_suite: Failed: %i\n", CU_get_error());
	}

	libret_init(p);
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
