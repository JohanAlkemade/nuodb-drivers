dnl $Id$
dnl config.m4 for extension pdo_nuodb

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(pdo_nuodb, for pdo_nuodb support,
dnl Make sure that the comment is aligned:
dnl [  --with-pdo_nuodb             Include pdo_nuodb support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(pdo_nuodb, whether to enable pdo_nuodb support,
dnl Make sure that the comment is aligned:
dnl [  --enable-pdo_nuodb           Enable pdo_nuodb support])

if test "$PHP_PDO_NUODB" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-pdo_nuodb -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/pdo_nuodb.h"  # you most likely want to change this
  dnl if test -r $PHP_PDO_NUODB/$SEARCH_FOR; then # path given as parameter
  dnl   PDO_NUODB_DIR=$PHP_PDO_NUODB
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for pdo_nuodb files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PDO_NUODB_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PDO_NUODB_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the pdo_nuodb distribution])
  dnl fi

  dnl # --with-pdo_nuodb -> add include path
  dnl PHP_ADD_INCLUDE($PDO_NUODB_DIR/include)

  dnl # --with-pdo_nuodb -> check for lib and symbol presence
  dnl LIBNAME=pdo_nuodb # you may want to change this
  dnl LIBSYMBOL=pdo_nuodb # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PDO_NUODB_DIR/lib, PDO_NUODB_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PDO_NUODBLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong pdo_nuodb lib version or lib not found])
  dnl ],[
  dnl   -L$PDO_NUODB_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PDO_NUODB_SHARED_LIBADD)

  PHP_NEW_EXTENSION(pdo_nuodb, pdo_nuodb.c, $ext_shared)
fi
