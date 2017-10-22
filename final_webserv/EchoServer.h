#include<limits.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<sys/stat.h>

#define FALSE 0
#define TRUE 1

#define INVALID 0
#define VALID 1

#define BAD_REQUEST 400
#define NOT_FOUND 404
#define NOT_IMPLEMENTED 501
#define INTERNET_SERVER_ERROR 500
#define VALID_REQUEST 200

#define BAD_HTTP_METHOD 4001
#define BAD_HTTP_VERSION 4002
#define BAD_HTTP_URL 4003


#define MAXBUFFSIZE 1024

#define THREAD_NUM 4
#define FILESIZE 200
#define FILE_PATH_SIZE 512
#define FILE_NUM 9

// this is for setting things for server
#define PORT_NUM 2
#define WEB_ROOT 4
#define DEFAULT 6
#define HTML 8
#define HTM 9
#define TXT 10
#define PNG 11
#define GIF 12
#define JPG 13
#define CSS 14
#define JS 15
#define ICON 16

int glob_port_num;
char glob_web_root[FILESIZE];
char glob_default[FILESIZE];
char glob_default_2[FILESIZE];
char glob_default_3[FILESIZE];

// file extension, glob variable 
char glob_ext_html[FILESIZE];
char glob_ext_htm[FILESIZE];
char glob_ext_txt[FILESIZE];
char glob_ext_png[FILESIZE];
char glob_ext_gif[FILESIZE];
char glob_ext_jpg[FILESIZE];
char glob_ext_css[FILESIZE];
char glob_ext_icon[FILESIZE];
char glob_ext_js[FILESIZE];

// file encodings, glob variable
char glob_enc_html[FILESIZE];
char glob_enc_htm[FILESIZE];
char glob_enc_txt[FILESIZE];
char glob_enc_png[FILESIZE];
char glob_enc_gif[FILESIZE];
char glob_enc_jpg[FILESIZE];
char glob_enc_css[FILESIZE];
char glob_enc_icon[FILESIZE];
char glob_enc_js[FILESIZE];

// HTTP request form or format
struct HTTP_FORM{
	char *method;
	char *URL;
	char *http_version;
};

// fuction declaration for string operation and HTTP Request
int socket_bind(int port_num, int client_num);
void read_conf(); // read ws.conf file 
void get_parameter(char *response, struct HTTP_FORM *format);
int validity_check(struct HTTP_FORM *format, int *error_request);
int client_file_format(char *user_file_path);
int input_file_handler(char *parth, char *body, int *status);
void valid_file_response(char *file_path, int client);
void HTTP_Response(int client, int status, struct HTTP_FORM *format, char *file_path);
void HTTP_Request(int client);












