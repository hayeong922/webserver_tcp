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
#define DEFAULT 200

#define BAD_HTTP_METHOD 4001
#define BAD_HTTP_VERSION 4002

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


//extension
char glob_ext_html[FILESIZE];
char glob_ext_htm[FILESIZE];
char glob_ext_txt[FILESIZE];
char glob_ext_png[FILESIZE];
char glob_ext_gif[FILESIZE];
char glob_ext_jpg[FILESIZE];
char glob_ext_css[FILESIZE];
char glob_ext_icon[FILESIZE];
char glob_ext_js[FILESIZE];

//encodings
char glob_enc_html[FILESIZE];
char glob_enc_htm[FILESIZE];
char glob_enc_txt[FILESIZE];
char glob_enc_png[FILESIZE];
char glob_enc_gif[FILESIZE];
char glob_enc_jpg[FILESIZE];
char glob_enc_css[FILESIZE];
char glob_enc_icon[FILESIZE];
char glob_enc_js[FILESIZE];


struct HTTP_FORM{
	char *method;
	char *URL;
	char *http_version;
};

// set socket and bind for connection
int socket_bind(int port_num, int client_num){

  struct sockaddr_in server;
  int sock;

  server.sin_family = AF_INET;
  server.sin_port = htons(port_num);
  server.sin_addr.s_addr = INADDR_ANY;

  // make it zero the sockaddr_in struct for the right size
  memset(server.sin_zero, '\0', sizeof(server.sin_zero));

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	     perror("server socket: ");
	     exit(-1);
	   }
	 puts("socket created\n");

	if ((bind(sock, (struct sockaddr *)&server, sizeof(struct sockaddr_in))) < 0) {
	    perror("bind : ");
	    exit(-1);
	  }
	puts("bind done\n");

	// listen part, make it listen to number of clients, client_num : max number of cients
	if((listen(sock, client_num)) < 0){
		perror("listen failed\n");
		exit(-1);
	}

return sock;
}

void read_conf(){
	char *root_path;
	char *curr;
	char *read_param;
	char *test;
	char buff[MAXBUFFSIZE+1];
	char temp_path[MAXBUFFSIZE+1];
	char read[FILESIZE];
	int count = 1;
	int count_index =1;
	char *token;

	root_path = getcwd(buff,MAXBUFFSIZE);
	strcpy(temp_path,root_path);
	strcat(temp_path,"/ws.conf");

	//ws.conf file
	FILE *file;
	file = fopen(temp_path,"r");
	if(file == NULL){
		perror("cannot read file\n");
		exit(-1);
	}

	while(fgets(read,FILESIZE,file) != NULL)
	{
		switch(count){
			case PORT_NUM:
				curr = strtok_r(read, " ",&read_param);
				glob_port_num = atoi(read_param);
				break;
			case WEB_ROOT:
				curr = strtok_r(read, " ",&read_param);
				test = strtok(read_param,"\"");
				strcpy(glob_web_root,test);
				break;
			case DEFAULT:
				curr = strtok_r(read, " ",&read_param);
				char *token = strtok(read_param," ");
				while(token != NULL){
					if(count_index == 1){
						strcpy(glob_default,token);
					}
					if(count_index == 2){
						strcpy(glob_default_2,token);
					}
					if(count_index == 3){
						char *f = strtok(token,"\n"); // remove new line
						strcpy(glob_default_3,f);
					}
					token = strtok(NULL," ");
					count_index++;
				}
				break;
			case HTML:
				curr = strtok_r(read, " ",&read_param);
				strcpy(glob_ext_html,curr);
				test = strtok(read_param,"\n");
				strcpy(glob_enc_html,test);
				break;
			case HTM:
				curr = strtok_r(read, " ",&read_param);
				strcpy(glob_ext_htm,curr);
				test = strtok(read_param,"\n");
				strcpy(glob_enc_htm,test);
				break;
			case TXT:
				curr = strtok_r(read, " ",&read_param);
				strcpy(glob_ext_txt,curr);
				test = strtok(read_param,"\n");
				strcpy(glob_enc_txt,test);
				break;
			case PNG:
				curr = strtok_r(read, " ",&read_param);
				strcpy(glob_ext_png,curr);
				test = strtok(read_param,"\n");
				strcpy(glob_enc_png,test);
				break;
			case GIF:
				curr = strtok_r(read, " ",&read_param);
				strcpy(glob_ext_gif,curr);
				test = strtok(read_param,"\n");
				strcpy(glob_enc_gif,test);
				break;
			case JPG:
				curr = strtok_r(read, " ",&read_param);
				strcpy(glob_ext_jpg,curr);
				test = strtok(read_param,"\n");
				strcpy(glob_enc_jpg,test);
				break;
			case CSS:
				curr = strtok_r(read, " ",&read_param);
				strcpy(glob_ext_css,curr);
				test = strtok(read_param,"\n");
				strcpy(glob_enc_css,test);
				break;
			case JS:
				curr = strtok_r(read, " ",&read_param);
				strcpy(glob_ext_js,curr);
				test = strtok(read_param,"\n");
				strcpy(glob_enc_js,test);
				break;
			case ICON:
				curr = strtok_r(read, " ",&read_param);
				strcpy(glob_ext_icon,curr);
				test = strtok(read_param,"\n");
				strcpy(glob_enc_icon,test);
				break;
		}
		count++;
	}
	fclose(file);
}

void get_parameter(char *response, struct HTTP_FORM *format){
	char *tmp_ptr, *file_path;

	file_path = strtok_r(response, "\n",&tmp_ptr);

	file_path = strtok_r(file_path," ",&tmp_ptr);
	format->method = malloc(strlen(file_path)+1);
	strcpy(format->method, file_path);

	file_path = strtok_r(NULL," ",&tmp_ptr);
	format->URL = malloc(strlen(file_path)+1);
	strcpy(format->URL,file_path);

	format->http_version = malloc(strlen(tmp_ptr)+1);
	strcpy(format->http_version,tmp_ptr);

    printf("REQUEST HANDLER\n");
    printf("method: %s url: %s version: %s", format->method,format->URL,format->http_version);


}

/*
check if the http header params is valid or not,
and return valid or invalid output
*/
int validity_check(struct HTTP_FORM *format, int *error_request){

	if((strcmp(format->method,"GET")) != 0){
		printf("Invalid method");
		*error_request = BAD_HTTP_METHOD;
		return INVALID;
	}

	if(((strncmp(format->http_version,"HTTP/1.1",8))!= 0)&&((strcmp(format->http_version,"HTTP/1.0")) != 0)){
		printf("Invalid version");
		*error_request = BAD_HTTP_VERSION;
		return INVALID;
	}
	return VALID;
}

int check_file_format(char *user_file_path){
	if((strcmp(user_file_path,glob_ext_html))== 0)
		return TRUE;
	if((strcmp(user_file_path,glob_ext_htm))== 0)
		return TRUE;
	if((strcmp(user_file_path,glob_ext_txt))== 0)
		return TRUE;
	if((strcmp(user_file_path,glob_ext_png))== 0)
		return TRUE;
	if((strcmp(user_file_path,glob_ext_gif))== 0)
		return TRUE;
	if((strcmp(user_file_path,glob_ext_jpg))== 0)
		return TRUE;
	if((strcmp(user_file_path,glob_ext_css))== 0)
		return TRUE;
	if((strcmp(user_file_path,glob_ext_icon))== 0)
		return TRUE;
	if((strcmp(user_file_path,glob_ext_js))== 0)
		return TRUE;
}

int input_file_handler(char *path, char *body, int *status){
	int file_format, i;
	file_format = FALSE;
	char user_file_path[FILE_PATH_SIZE+1];
	char *input_extension;
	struct stat buffer;

	//concat input path and root document path, to make a absolute path to acces file
	strcpy(user_file_path,glob_web_root);
	strcat(user_file_path,path);
	// strrchr finds the last occurence of '.'
	input_extension = strrchr(user_file_path,'.');

	// default page, which is root page
	if(((strcmp(path,"/index")) == 0) || (strcmp(path,"/") == 0) || ((strcmp(path,"/index.html")) == 0)){
		if((strcmp(path,"/index")) == 0)
			strcat(user_file_path,".html");
		if((strcmp(path,"/")) == 0)
			strcat(user_file_path,"indext.html");
		*status = DEFAULT;
		strcpy(body,user_file_path);
		return 0;
	}

	if(!input_extension){
		*status = NOT_FOUND;
		strcpy(body, user_file_path);
		return 0;
	}

	/*check_file_format: checks if the file 
	format is supported in ws.cong*/
	file_format = check_file_format(user_file_path);
	
	if(!file_format){
		*status = NOT_IMPLEMENTED; // 501
		strcpy(body, user_file_path);
		return(0);
	}
	if((stat(user_file_path,&buffer) == 0)){
		*status = 200;
		strcpy(body, user_file_path);
		return 0;
	}else{
		*status = 404;
		strcpy(body, user_file_path);
		return 0;
	}
}

void valid_file_response(char *file_path, int client){

	char *input_extension;
	char buffer[MAXBUFFSIZE];
	long file_size;
	FILE *input_file;
	size_t read_bytes, total_size;
	input_extension = strchr(file_path,'.');

	char png_response[] = "HTTP/1.1 200 OK:\r\n" "Content-Type: image/png; charset=UTF-8\r\n\r\n";
  	char gif_response[] = "HTTP/1.1 200 OK:\r\n" "Content-Type: image/gif; charset=UTF-8\r\n\r\n";
  	char html_response[] = "HTTP/1.1 200 OK:\r\n" "Content-Type: text/html; charset=UTF-8\r\n\r\n";
  	char text_response[] = "HTTP/1.1 200 OK:\r\n" "Content-Type: text/plain; charset=UTF-8\r\n\r\n";
  	char css_response[] = "HTTP/1.1 200 OK:\r\n" "Content-Type: text/css; charset=UTF-8\r\n\r\n";
  	char jpg_response[] = "HTTP/1.1 200 OK:\r\n" "Content-Type: image/jpeg; charset=UTF-8\r\n\r\n";
  	char htm_response[] = "HTTP/1.1 200 OK:\r\n" "Content-Type: text/html; charset=UTF-8\r\n\r\n";
  	char js_response[] = "HTTP/1.1 200 OK:\r\n" "Content-Type: text/javascript; charset=UTF-8\r\n\r\n";
  	char icon_response[] = "HTTP/1.1 200 OK:\r\n" "Content-Type: text/icon; charset=UTF-8\r\n\r\n";

  	input_file = fopen(file_path,"r");

  	fseek(input_file,0,SEEK_END);
  	file_size = ftell(input_file);
  	fseek(input_file,0,SEEK_SET);

  	if((strcmp(input_extension,".png")) == 0)
  		send(client, png_response,sizeof(png_response)-1,0);
  	if((strcmp(input_extension,".gif")) == 0)
  		send(client, gif_response,sizeof(gif_response)-1,0);
  	if((strcmp(input_extension,".html")) == 0)
  		send(client, html_response,sizeof(html_response)-1,0);
  	if((strcmp(input_extension,".jpg")) == 0)
  		send(client, jpg_response,sizeof(jpg_response)-1,0);
  	if((strcmp(input_extension,".text")) == 0)
  		send(client, text_response,sizeof(text_response)-1,0);
  	if((strcmp(input_extension,".css")) == 0)
  		send(client, css_response,sizeof(css_response)-1,0);
  	if((strcmp(input_extension,".htm")) == 0)
  		send(client, htm_response,sizeof(htm_response)-1,0);
  	if((strcmp(input_extension,".js")) == 0)
  		send(client, js_response,sizeof(js_response)-1,0);
  	if((strcmp(input_extension,".icon")) == 0)
  		send(client, icon_response,sizeof(icon_response)-1,0);

  	total_size = 0;
  	while(!feof(input_file)){
  		read_bytes = fread(buffer,1,MAXBUFFSIZE,input_file);
  		total_size += read_bytes;
  		send(client,buffer,read_bytes,0);
  	}
  	fclose(input_file);

}

void HTTP_Response(int client, int status, struct HTTP_FORM *format,char *file_path){
	char invalid_version[] = "HTTP/1.1 400 Bad Request: Invalid Version: %s\r\n";
	char invalid_url[] = "HTTP/1.1 400 Bad Request: Invalid URI: %s\r\n";
	char invalid_method[] = "HTTP/1.1 400 Bad Request: Invalid Method: %s\r\n";

	// html display
	char not_found[] = "HTTP/1.1 404 Not Found:%s\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n\r\n"
    "<!DOCTYPE html><html><head><title>404 Not Found</title>"
    "<body><h1>404 Not Found:%s</h1></body></html>\r\n";

    char server_error[] = "HTTP/1.1 500 Internal Server Error:\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n\r\n"
    "<!DOCTYPE html><html><head><title>500 Internal Server Error</title>"
    "<body><h1>cannot allocate memory</h1></body></html>\r\n";

  	char not_implemented[] = "HTTP/1.1 501 Not Implemented: %s\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n\r\n"
    "<!DOCTYPE html><html><head><title>501 Not Implemented</title>"
    "<body><h1>501 Not Implemented: %s</h1></body></html>\r\n";

    char http_response[MAXBUFFSIZE];
    memset(&http_response, 0, sizeof(http_response));     // initialize

    switch(status){
    	case NOT_IMPLEMENTED:
    			// print formatted data to buffer
    			snprintf(http_response, sizeof(http_response),not_implemented,format->URL,format->URL);
    			write(client, http_response,sizeof(http_response));
    			break;
    	case NOT_FOUND:
    			snprintf(http_response, sizeof(http_response),not_found,format->URL,format->URL);
    			write(client, http_response,sizeof(http_response));
    			break;
    	case BAD_REQUEST:
    			break;
    	case INTERNET_SERVER_ERROR:
    			snprintf(http_response, sizeof(http_response),server_error);
    			write(client, http_response,sizeof(http_response));
    			break;
    	case DEFAULT: // 200
    			// contruct_file_respinse(full_path, client);
    			valid_file_response(file_path,client);
    			break; 
    	case BAD_HTTP_VERSION:
    			snprintf(http_response, sizeof(http_response),invalid_version,format->URL,format->URL);
    			write(client, http_response,sizeof(http_response));
    			break;
    	case BAD_HTTP_METHOD:
    			snprintf(http_response, ( sizeof(invalid_method) + ( (sizeof(format->method))*2)), invalid_method, format->method, format->method);
      			write(client,http_response, ( sizeof(invalid_method) + ( (sizeof(format->method))*2)));
    			break;
    	case 4003:
		      printf("This is a bad http uri\n");
		      snprintf(http_response, sizeof(http_response), invalid_url, format->method);
		      write(client,http_response, sizeof(http_response));
		      break;
    }


}

void HTTP_Request(int client){
	struct HTTP_FORM format;
	int content_len, content_type;
	char content[MAXBUFFSIZE], file_path[FILE_PATH_SIZE];

	if(content_len = recv(client, content, MAXBUFFSIZE, 0) < 0){
		perror("Recv error: ");
		exit(-1);
	}

	if(content_len){
		// get parameter
		get_parameter((char *)&content,&format);
		printf("HTTP METHOD: %s URL: %s VERSION: %s\n",format.method,format.URL,format.http_version);

		// check request header if valid send response
		// else still send response?
		if(validity_check((char *)&content, &format)==INVALID){
			HTTP_Response(client, content_type,&format,(char*)&file_path);
		}else{ 
			// this case VALID header
			// so check if it supports such file format and check file path
			input_file_handler((format.URL),(char *)&file_path,&content_type);
			HTTP_Response(client, content_type,&format,(char*)&file_path);
		}

	}
	free(format.method);
	free(format.URL);
	free(format.http_version);
}

int main(int argc, char ** argv){
	int socket_desc, client_sock, c, read_size;
	int thread_id;
	struct sockaddr_in client;
	unsigned int sockaddr_len = sizeof(struct sockaddr_in);

	// read and set variable by reading information from ws.conf
	read_conf();

	printf("read ws.conf file\n");

	printf("\nport number:%d\n",glob_port_num);

	// set socket
	socket_desc = socket_bind(glob_port_num,THREAD_NUM);
	printf("socket_desc:%d\n",socket_desc);

	while(1){
		
		// accpet and listen
		if((client_sock = accept(socket_desc,(struct sockaddr*)&client,&sockaddr_len)) < 0)
		{
			perror("accept failed\n");
			exit(1);
		}

		thread_id = fork();
		if(thread_id < 0 ){
			perror("fork failed\n");
			exit(1);
		}

		/*child thread will do the task, so can close the initial socket*/
		if(thread_id == 0){
			close(socket_desc);
			// request part implementation
			//client handler(client) part needs to be added, below is func
			printf("http request fuc call\n");
			HTTP_Request(client_sock);

			exit(0);
		}

		/* parent thread will wait and accept new client, 
		don't need active socket for all*/
		if(thread_id > 0){
			printf("thread_id bigger than 0\n");
			close(client_sock);
	        waitpid(0, NULL, WNOHANG);
		}


	}// end of while
}