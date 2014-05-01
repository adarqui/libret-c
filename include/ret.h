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

typedef void * RET_DATUM_t;

typedef enum {
	RET_BOOL_FALSE = 0,
	RET_BOOL_TRUE = 1
} RET_BOOL_t;


/*
 * A variety of ret macros
 */

#define _RET_CLR(__r) { __r.v = NULL;__r.e = 0; }
#define _RET_V(__r) __r.v
#define _RET_E(__r) __r.e
#define _RET_SET_V(__r, __v) __r.v = __v
#define _RET_SET_E(__r, __e) __r.e = __e

#define _RET_OK(__r, __v) { __r.v = __v; __r.e = RET_STATUS_OK; return __r; }
#define _RET_ERROR(__r, __v) { __r.v = __v; __r.e = RET_STATUS_ERROR; return __r; }
#define _RET_FATAL(__r, __v) { __r.v = __v; __r.e = RET_STATUS_ERROR | RET_STATUS_FATAL; return __r; }

// Assumes ret.v was assigned somewhere else
#define _RET_OK_ONLY(__r) _RET_OK(__r, __r.v)
#define _RET_ERROR_ONLY(__r) _RET_ERROR(__r, __r.v)
#define _RET_FATAL_ONLY(__r) _RET_FATAL(__r, __r.v)

#define _RET_ISOK(__r) ((__r.e & RET_STATUS_OK) > 0)
#define _RET_ISERROR(__r) ((__r.e & RET_STATUS_ERROR) > 0)
#define _RET_ISFATAL(__r) ((__r.e & RET_STATUS_FATAL) > 0)


#define RET_CLR _RET_CLR(_r)
#define RET_V _RET_V(_r)
#define RET_E _RET_E(_r)
#define RET_SET_V(_v) _RET_SET_V(_r, _v)
#define RET_SET_E(_e) _RET_SET_E(_r, _e)

#define RET_OK(_v) _RET_OK(_r, _v)
#define RET_ERROR(_v) _RET_ERROR(_r, _v)
#define RET_FATAL(_v) _RET_FATAL(_r, _v)

// Assumes ret.v was assigned somewhere else
#define RET_OK_ONLY _RET_OK(_r, _r.v)
#define RET_ERROR_ONLY _RET_ERROR(_r, _r.v)
#define RET_FATAL_ONLY _RET_FATAL(_r, _r.v)

#define RET_ISOK _RET_ISOK(_r)
#define RET_ISERROR _RET_ISERROR(_r)
#define RET_ISFATAL _RET_ISFATAL(_r)



/*
 * Lowercase aliases
 */

#define _ret_clr _RET_CLR
#define _ret_v _RET_V
#define _ret_e _RET_E
#define _ret_set_v _RET_SET_V
#define _ret_set_e _RET_SET_E

#define _ret_ok _RET_OK
#define _ret_error _RET_ERROR
#define _ret_fatal _RET_FATAL

#define _ret_ok_only _RET_OK_ONLY
#define _ret_error_only _RET_ERROR_ONLY
#define _ret_fatal_only _RET_FATAL_ONLY

#define _ret_isok _RET_ISOK
#define _ret_iserror _RET_ISERROR
#define _ret_isfatal _RET_ISFATAL


#define ret_clr RET_CLR
#define ret_v RET_V
#define ret_e RET_E
#define ret_set_v RET_SET_V
#define ret_set_e RET_SET_E

#define ret_ok RET_OK
#define ret_error RET_ERROR
#define ret_fatal RET_FATAL

#define ret_ok_only RET_OK_ONLY
#define ret_error_only RET_ERROR_ONLY
#define ret_fatal_only RET_FATAL_ONLY

#define ret_isok RET_ISOK
#define ret_iserror RET_ISERROR
#define ret_isfatal RET_ISFATAL


/*
 * The ret {value, error} tuple data structure
 */

typedef struct ret {
	RET_DATUM_t v;
	RET_STATUS_t e;
} ret_t;

#define RET_INIT ret_t _r
#define ret_init ret_t _r

#endif
