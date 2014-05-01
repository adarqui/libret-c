#ifndef RET_H
#define RET_H

/*
 * Some generic success/failure codes
 */

typedef enum {
	RET_NONE = 0x00,
	RET_STATUS_OK = 0x01,
	RET_STATUS_ERROR = 0x02,
	RET_STATUS_FATAL = 0x04
} RET_STATUS_t;

typedef enum {
	RET_VBITS_0 = 0x00,
	RET_VBITS_1 = 0x01,
	RET_VBITS_2 = 0x02,
	RET_VBITS_3 = 0x04
} RET_VBITS_t;

typedef void * RET_DATUM_t;
typedef unsigned char RET_BITSET_t;

typedef enum {
	RET_BOOL_FALSE = 0,
	RET_BOOL_TRUE = 1
} RET_BOOL_t;

/*
 * The ret {value, error} tuple data structure
 */

typedef struct ret {
	RET_DATUM_t v;
	RET_DATUM_t v2;
	RET_DATUM_t v3;
	RET_BITSET_t vbits;
	RET_STATUS_t e;
} ret_t;


/*
 * A variety of ret macros
 */

#define RET_INIT ret_t _r
#define ret_init ret_t _r

#define _RET_CLR(__r) { __r.v = NULL; __r.v2 = NULL; __r.v3 = NULL; __r.e = 0; }
#define _RET_V(__r) __r.v
#define _RET_V1 _RET_SET_V
#define _RET_V2(__r) __r.v2
#define _RET_V3(__r) __r.v3
#define _RET_E(__r) __r.e
#define _RET_SET_V(__r, __v) { __r.v = __v ; __r.vbits |= RET_VBITS_1; }
#define _RET_SET_V1 _RET_SET_V
#define _RET_SET_V2(__r, __v) { __r.v2 = __v ; __r.vbits |= RET_VBITS_2; }
#define _RET_SET_V3(__r, __v) { __r.v3 = __v ; __r.vbits |= RET_VBITS_3; }
#define _RET_UNSET_V(__r) { __r.v = NULL ; __r.vbits &= ~RET_VBITS_1; }
#define _RET_UNSET_V1 _RET_UNSET_V
#define _RET_UNSET_V2(__r) { __r.v2 = NULL ; __r.vbits &= ~RET_VBITS_2; }
#define _RET_UNSET_V3(__r) { __r.v3 = NULL ; __r.vbits &= ~RET_VBITS_3; }
#define _RET_SET_E(__r, __e) __r.e = __e

#define _RET_OK(__r, __v) { __r.v = __v; __r.e = RET_STATUS_OK; return __r; }
#define _RET_OK1 _RET_OK
#define _RET_OK2(__r, __v, __v2) { __r.v = __v; __r.v2 = __v2; __r.e = RET_STATUS_OK; return __r; }
#define _RET_OK3(__r, __v, __v2, __v3) { __r.v = __v; __r.v2 = __v3; __r.v3 = __v3; __r.e = RET_STATUS_OK; return __r; }
#define _RET_ERROR(__r, __v) { __r.v = __v; __r.e = RET_STATUS_ERROR; return __r; }
#define _RET_ERROR1 _RET_ERROR
#define _RET_ERROR2(__r, __v, __v2) { __r.v = __v; __r.v2 = __v2; __r.e = RET_STATUS_ERROR; return __r; }
#define _RET_ERROR3(__r, __v, __v2, __v3) { __r.v = __v; __r.v2 = __v3; __r.v3 = __v3; __r.e = RET_STATUS_ERROR; return __r; }
#define _RET_FATAL(__r, __v) { __r.v = __v; __r.e = RET_STATUS_ERROR | RET_STATUS_FATAL; return __r; }
#define _RET_FATAL1 _RET_FATAL_1
#define _RET_FATAL2(__r, __v, __v2) { __r.v = __v; __r.v2 = __v2; __r.e = RET_STATUS_ERROR | RET_STATUS_FATAL; return __r; }
#define _RET_FATAL3(__r, __v, __v2, __v3) { __r.v = __v; __r.v2 = __v3; __r.v3 = __v3; __r.e = RET_STATUS_ERROR | RET_STATUS_FATAL; return __r; }

// Assumes ret.v was assigned somewhere else
#define _RET_OK_ONLY(__r) _RET_OK(__r, __r.v)
#define _RET_ERROR_ONLY(__r) _RET_ERROR(__r, __r.v)
#define _RET_FATAL_ONLY(__r) _RET_FATAL(__r, __r.v)

#define _RET_OK1_ONLY _RET_OK_ONLY
#define _RET_ERROR1_ONLY _RET_ERROR_ONLY
#define _RET_FATAL1_ONLY(__r) _RET_FATAL_ONLY

#define _RET_OK2_ONLY(__r) _RET_OK(__r, __r.v, __r.v2)
#define _RET_ERROR2_ONLY(__r) _RET_ERROR(__r, __r.v, __r.v2)
#define _RET_FATAL2_ONLY(__r) _RET_FATAL(__r, __r.v, __r.v2)

#define _RET_OK3_ONLY(__r) _RET_OK(__r, __r.v, __r.v2, __r.v3)
#define _RET_ERROR3_ONLY(__r) _RET_ERROR(__r, __r.v, __r.v2, __r.v3)
#define _RET_FATAL3_ONLY(__r) _RET_FATAL(__r, __r.v, __r.v2, __r.v3)

#define _RET_ISOK(__r) ((__r.e & RET_STATUS_OK) > 0)
#define _RET_ISERROR(__r) ((__r.e & RET_STATUS_ERROR) > 0)
#define _RET_ISFATAL(__r) ((__r.e & RET_STATUS_FATAL) > 0)


#define RET_CLR _RET_CLR(_r)
#define RET_V _RET_V(_r)
#define RET_V1 RET_V
#define RET_V2 _RET_V2(_r)
#define RET_V3 _RET_V3(_r)
#define RET_E _RET_E(_r)
#define RET_SET_V(_v) _RET_SET_V(_r, _v)
#define RET_SET_V1 RET_SET_V
#define RET_SET_V2(_v) _RET_SET_V2(_r, _v)
#define RET_SET_V3(_v) _RET_SET_V3(_r, _v)
#define RET_UNSET_V _RET_UNSET_V(_r)
#define RET_UNSET_V1 _RET_UNSET_V1(_r)
#define RET_UNSET_V2 _RET_UNSET_V2(_r)
#define RET_UNSET_V3 _RET_UNSET_V3(_r)
#define RET_SET_E(_e) _RET_SET_E(_r, _e)


#define RET_OK(_v) _RET_OK(_r, _v)
#define RET_ERROR(_v) _RET_ERROR(_r, _v)
#define RET_FATAL(_v) _RET_FATAL(_r, _v)

#define RET_OK1 RET_OK
#define RET_ERROR1 RET_ERROR
#define RET_FATAL1 RET_FATAL

#define RET_OK2(_v, _v2) _RET_OK2(_r, _v, _V2)
#define RET_ERROR2(_v, _v2) _RET_ERROR2(_r, _v, _v2)
#define RET_FATAL2(_v, _v2) _RET_FATAL2(_r, _v, _v2)

#define RET_OK3(_v, _v2, _v3) _RET_OK3(_r, _v, _v2, _v3)
#define RET_ERROR3(_v, _v2) _RET_ERROR2(_r, _v, _v2)
#define RET_FATAL3(_v, _v2) _RET_FATAL2(_r, _v, _v2)

// Assumes ret.v was assigned somewhere else
#define RET_OK_ONLY _RET_OK(_r, _r.v)
#define RET_ERROR_ONLY _RET_ERROR(_r, _r.v)
#define RET_FATAL_ONLY _RET_FATAL(_r, _r.v)

#define RET_OK1_ONLY RET_OK_ONLY
#define RET_ERROR1_ONLY RET_ERROR_ONLY
#define RET_FATAL1_ONLY RET_FATAL_ONLY

#define RET_OK2_ONLY _RET_OK(_r, _r.v, _r.v2)
#define RET_ERROR2_ONLY _RET_ERROR(_r, _r.v, _r.v2)
#define RET_FATAL2_ONLY _RET_FATAL(_r, _r.v, _r.v2)

#define RET_OK3_ONLY _RET_OK(_r, _r.v, _r.v2, _r.v3)
#define RET_ERROR3_ONLY _RET_ERROR(_r, _r.v, _r.v2, _r.v3)
#define RET_FATAL3_ONLY _RET_FATAL(_r, _r.v, _r.v2, _r.v3)

#define RET_ISOK _RET_ISOK(_r)
#define RET_ISERROR _RET_ISERROR(_r)
#define RET_ISFATAL _RET_ISFATAL(_r)



/*
 * Lowercase aliases
 */

#define _ret_clr _RET_CLR
#define _ret_v _RET_V
#define _ret_v1 _RET_V
#define _ret_v2 _RET_V2
#define _ret_v3 _RET_V3
#define _ret_e _RET_E
#define _ret_set_v _RET_SET_V
#define _ret_set_v1 _RET_SET_V
#define _ret_set_v2 _RET_SET_V2
#define _ret_set_v3 _RET_SET_V3
#define _ret_unset_v _RET_UNSET_V
#define _ret_unset_v1 _RET_UNSET_V
#define _ret_unset_v2 _RET_UNSET_V2
#define _ret_unset_v3 _RET_UNSET_V3
#define _ret_set_e _RET_SET_E

#define _ret_ok _RET_OK
#define _ret_ok1 _RET_OK
#define _ret_ok2 _RET_OK2
#define _ret_ok3 _RET_OK3
#define _ret_error _RET_ERROR
#define _ret_error1 _RET_ERROR
#define _ret_error2 _RET_ERROR2
#define _ret_error3 _RET_ERROR3
#define _ret_fatal _RET_FATAL
#define _ret_fatal1 _RET_FATAL
#define _ret_fatal2 _RET_FATAL2
#define _ret_fatal3 _RET_FATAL3

#define _ret_ok_only _RET_OK_ONLY
#define _ret_ok1_only _RET_OK_ONLY
#define _ret_ok2_only _RET_OK2_ONLY
#define _ret_ok3_only _RET_OK3_ONLY
#define _ret_error_only _RET_ERROR_ONLY
#define _ret_error1_only _RET_ERROR_ONLY
#define _ret_error2_only _RET_ERROR_ONLY2
#define _ret_error3_only _RET_ERROR_ONLY3
#define _ret_fatal_only _RET_FATAL_ONLY
#define _ret_fatal1_only _RET_FATAL_ONLY
#define _ret_fatal2_only _RET_FATAL_ONLY2
#define _ret_fatal3_only _RET_FATAL_ONLY3

#define _ret_isok _RET_ISOK
#define _ret_iserror _RET_ISERROR
#define _ret_isfatal _RET_ISFATAL



#define ret_clr RET_CLR
#define ret_v RET_V
#define ret_v1 RET_V
#define ret_v2 RET_V2
#define ret_v3 RET_V3
#define ret_e RET_E
#define ret_set_v RET_SET_V
#define ret_set_v1 RET_SET_V
#define ret_set_v2 RET_SET_V2
#define ret_set_v3 RET_SET_V3
#define ret_unset_v RET_UNSET_V
#define ret_unset_v1 RET_UNSET_V
#define ret_unset_v2 RET_UNSET_V2
#define ret_unset_v3 RET_UNSET_V3
#define ret_set_e RET_SET_E

#define ret_ok RET_OK
#define ret_ok1 RET_OK
#define ret_ok2 RET_OK2
#define ret_ok3 RET_OK3
#define ret_error RET_ERROR
#define ret_error1 RET_ERROR
#define ret_error2 RET_ERROR2
#define ret_error3 RET_ERROR3
#define ret_fatal RET_FATAL
#define ret_fatal1 RET_FATAL
#define ret_fatal2 RET_FATAL2
#define ret_fatal3 RET_FATAL3

#define ret_ok_only RET_OK_ONLY
#define ret_ok1_only RET_OK_ONLY
#define ret_ok2_only RET_OK2_ONLY
#define ret_ok3_only RET_OK3_ONLY
#define ret_error_only RET_ERROR_ONLY
#define ret_error1_only RET_ERROR_ONLY
#define ret_error2_only RET_ERROR_ONLY2
#define ret_error3_only RET_ERROR_ONLY3
#define ret_fatal_only RET_FATAL_ONLY
#define ret_fatal1_only RET_FATAL_ONLY
#define ret_fatal2_only RET_FATAL_ONLY2
#define ret_fatal3_only RET_FATAL_ONLY3

#define ret_isok RET_ISOK
#define ret_iserror RET_ISERROR
#define ret_isfatal RET_ISFATAL


#endif
