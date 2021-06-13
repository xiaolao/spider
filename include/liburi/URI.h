/* Author: Mo McRoberts <mo.mcroberts@bbc.co.uk>
 * 
 * Copyright 2014-2017 BBC
 */

/*
 * Copyright 2012 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef URI_H_
# define URI_H_                        1

# include <inttypes.h>
# include <sys/types.h>
# include <wchar.h>

# ifndef URI_TYPE_DEFINED
#  define URI_TYPE_DEFINED
typedef struct uri_struct URI;
# endif

typedef struct uri_info_struct URI_INFO;

/* Note that excepting the 'internal' member, URI_INFO can be safely
 * modified by the calling application if it's convenient to do so.
 */
struct uri_info_struct
{
	void *reserved;
	char *scheme;
	char *auth;
	char *host;
	int port;
	char *path;
	char *query;
	char *fragment;
	char *user;
	char *pass;
	char **params;
#ifdef P_LIBURI_H_
	struct uri_info_internal_data_struct internal;
#endif
};

# if (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L) && !defined(restrict)
#  define restrict
# endif

# undef BEGIN_DECLS_
# undef END_DECLS_
# if defined(__cplusplus)
#  define BEGIN_DECLS_                 extern "C" {
#  define END_DECLS_                   }
# else
#  define BEGIN_DECLS_                 /* */
#  define END_DECLS_                   /* */
#endif

BEGIN_DECLS_;

/* Create a URI from a 7-bit ASCII string (the presence of non-ASCII characters
 * will cause parsing to fail)
 */
URI *uri_create_ascii(const char *restrict uristr, const URI *restrict uri);

/* Create a URI from a UTF-8 string (regardless of locale) and optional base URI */
URI *uri_create_ustr(const unsigned char *restrict uristr, const URI *restrict uri);

/* Create a URI from a wide-character Unicode string and optional base URI */
URI *uri_create_wstr(const wchar_t *restrict uristr, const URI *restrict uri);

/* Create a URI from a string and optional base URI */
URI *uri_create_str(const char *restrict uristr, const URI *restrict uri);

/* Create a URI from an existing URI and optional base URI */
URI *uri_create_uri(const URI *restrict source, const URI *restrict base);

/* Create a file: URI from the current working directory */
URI *uri_create_cwd(void);

/* Rebase a relative URI against a base URI */
int uri_rebase(URI *restrict rel, const URI *restrict base);

/* Destroy a URI, freeing the resources it uses */
int uri_destroy(URI *uri);

/* Return 1 if the URI specified is absolute, 0 if it is relative */
int uri_absolute(const URI *uri);

/* Return 1 if the path in the URI specified is absolute, 0 if it is
 * relative
 */
int uri_absolute_path(const URI *uri);
	
/* Get or set the URI's scheme */
size_t uri_scheme(const URI *restrict uri, char *restrict buf, size_t buflen);
const char *uri_scheme_str(const URI *uri);
char *uri_scheme_stralloc(const URI *uri);
int uri_set_scheme(URI *restrict uri, const char *restrict newscheme);

/* Get or set the URI's authentication information (typically 'user' or
 * 'user:pass')
 */
size_t uri_auth(const URI *restrict uri, char *restrict buf, size_t buflen);
const char *uri_auth_str(const URI *uri);
char *uri_auth_stralloc(const URI *uri);
int uri_set_auth(URI *restrict uri, const char *restrict newauth);

/* Get or set the URI's hostname */
size_t uri_host(const URI *restrict uri, char *restrict buf, size_t buflen);
const char *uri_host_str(const URI *uri);
char *uri_host_stralloc(const URI *uri);
int uri_set_host(URI *restrict uri, const char *restrict newhost);

/* Copy the URI's port into the buffer provided */
size_t uri_port(const URI *restrict uri, char *restrict buf, size_t buflen);
const char *uri_port_str(const URI *uri);
char *uri_port_stralloc(const URI *uri);
int uri_portnum(const URI *uri);
int uri_set_port(URI *restrict uri, int newport);

/* Copy the URI's path into the buffer provided */
size_t uri_path(const URI *restrict uri, char *restrict buf, size_t buflen);

/* Copy the URI's query string into the buffer provided */
size_t uri_query(const URI *restrict uri, char *restrict buf, size_t buflen);
const char *uri_query_str(const URI *uri);
char *uri_query_stralloc(const URI *uri);
int uri_set_query(URI *restrict uri, const char *newquery);

/* Copy the URI's fragment into the buffer provided */
size_t uri_fragment(const URI *restrict uri, char *restrict buf, size_t buflen);
const char *uri_fragment_str(const URI *uri);
char *uri_fragment_stralloc(const URI *uri);
int uri_set_fragment(URI *restrict uri, const char *newquery);

/* Copy the whole URI, as a string, into the buffer provided */
size_t uri_str(const URI *restrict uri, char *restrict buf, size_t buflen);

/* Allocate a new string using malloc() and copy the URI into it */
char *uri_stralloc(const URI *restrict uri);

/* Copy the various parts of the URI to a URI_INFO structure */
URI_INFO *uri_info(const URI *uri);
	
/* Free a URI_INFO structure */
int uri_info_destroy(URI_INFO *info);
	
/* Obtain query-string parameters from a URI_INFO structure */
const char *uri_info_get(URI_INFO *info, const char *key, const char *defval);
intmax_t uri_info_get_int(URI_INFO *info, const char *key, intmax_t defval);

/* Compare two URIs and test for equality */
int uri_equal(const URI *a, const URI *b);
	
END_DECLS_

#endif /*!URI_H_*/
