/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Tom Gates <tom@thebithead.com>                               |
  +----------------------------------------------------------------------+
*/

/* $Id: php_pdo_nuodb_int.h 321634 2012-01-01 13:15:04Z felipe $ */

#ifndef PHP_PDO_NUODB_INT_H
#define PHP_PDO_NUODB_INT_H

#include <Connection.h>

#define PDO_NUODB_VERSION 1

#define PDO_NUODB_DEF_DATE_FMT "%Y-%m-%d"
#define PDO_NUODB_DEF_TIME_FMT "%H:%M:%S"
#define PDO_NUODB_DEF_TIMESTAMP_FMT PDO_FB_DEF_DATE_FMT " " PDO_FB_DEF_TIME_FMT

#define SHORT_MAX (1 << (8*sizeof(short)-1))

#if SIZEOF_LONG == 8
# define LL_MASK "l"
# define LL_LIT(lit) lit ## L
#else
# ifdef PHP_WIN32
#  define LL_MASK "I64"
#  define LL_LIT(lit) lit ## I64
# else
#  define LL_MASK "ll"
#  define LL_LIT(lit) lit ## LL
# endif
#endif

#define const_cast(s) ((char*)(s))

#ifdef PHP_WIN32
typedef void (__stdcall *info_func_t)(char*);
#else
typedef void (*info_func_t)(char*);
#endif

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif

typedef struct {
	/* the connection handle */
	Connection db;

	/* the transaction handle */
	int tr;

	/* the last error that didn't come from the API */
	char const *last_app_error;
	
	/* date and time format strings, can be set by the set_attribute method */
	char *date_format;
	char *time_format;
	char *timestamp_format;
	
	/* prepend table names on column names in fetch */
	unsigned fetch_table_names:1;
	
	unsigned _reserved:31;
	
} pdo_nuodb_db_handle;


typedef struct {
	
	/* the link that owns this statement */
	pdo_nuodb_db_handle *H;
	
	/* the statement handle */
	Statement stmt;
	
	/* the name of the cursor (if it has one) */
	char name[32];
	
	/* the type of statement that was issued */
	char statement_type:8;
	
	/* whether EOF was reached for this statement */
	unsigned exhausted:1;

	/* successful isc_dsql_execute opens a cursor */
	unsigned cursor_open:1;

	unsigned _reserved:22;

	/* the named params that were converted to ?'s by the driver */
	HashTable *named_params;
	
	/* allocated space to convert fields values to other types */
	char **fetch_buf;
	
	
} pdo_nuodb_stmt;

extern pdo_driver_t pdo_nuodb_driver;

extern struct pdo_stmt_methods nuodb_stmt_methods;

void _nuodb_error(pdo_dbh_t *dbh, pdo_stmt_t *stmt, char const *file, long line TSRMLS_DC);

enum {
	PDO_NUODB_ATTR_DATE_FORMAT = PDO_ATTR_DRIVER_SPECIFIC,
	PDO_NUODB_ATTR_TIME_FORMAT,
	PDO_NUODB_ATTR_TIMESTAMP_FORMAT,
};

#endif	/* PHP_PDO_NUODB_INT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
