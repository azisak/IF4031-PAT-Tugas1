#include <sys/types.h>
#include <sys/time.h>
#include <sys/queue.h>
#include <stdlib.h>
#include <err.h>
#include <event.h>
#include <evhttp.h>
#include <stdio.h>
#include <string>

using namespace std;

void generic_handler(struct evhttp_request *req, void *arg)
{
    printf("Server is listening on http://localhost:8890");

    struct evbuffer *buf;
    int fd = -1;
    int sz = 0;
    FILE * fp;

    buf = evbuffer_new();
    if (buf == NULL)
        err(1, "failed to create response buffer");
    
    string s_req(evhttp_request_uri(req));  

    if (s_req.compare("/500b.html") == 0) {
      fp = fopen ("./resource/500b.html", "r");
      fd = fileno(fp);
      fseek(fp, 0L, SEEK_END);
      sz = ftell(fp);
      evbuffer_add_file(buf, fd, 0, sz);
    } else if (s_req.compare("/20kb.html")==0){
      fp = fopen ("./resource/20kb.html", "r");
      fd = fileno(fp);
      fseek(fp, 0L, SEEK_END);
      sz = ftell(fp);
      evbuffer_add_file(buf, fd, 0, sz);
    } else {
      evbuffer_add_printf(buf, "<h1 style='text-align: center'> NOT FOUND </h1>");
    }
    evhttp_send_reply(req, HTTP_OK, "OK", buf);
}

int main(int argc, char **argv)
{
    
    struct evhttp *httpd;
    event_init();
    httpd = evhttp_start("0.0.0.0", 8890);

    printf("Server is listening on http://localhost:8890\n");
    printf("Try:\n");
    printf("- http://localhost:8890/500b.html\n");
    printf("- http://localhost:8890/20kb.html\n");
    
    /* Set a callback for requests to "/specific". */
    /* evhttp_set_cb(httpd, "/specific", another_handler, NULL); */

    /* Set a callback for all other requests. */
    evhttp_set_gencb(httpd, generic_handler, NULL);

    event_dispatch();    /* Not reached in this code as it is now. */
    evhttp_free(httpd);
    
    return 0;
}