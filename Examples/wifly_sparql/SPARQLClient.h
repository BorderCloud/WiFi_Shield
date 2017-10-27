

#ifndef __SPARQL_CLIENT_H__
#define __SPARQL_CLIENT_H__

#define SPARQL_CLIENT_DEFAULT_TIMEOUT         30000  // 3s

#define SPARQL_MAX_HOST_LEN                   20
#define SPARQL_MAX_PATH_LEN                   64
#define SPARQL_MAX_BUF_LEN                    100

#define SPARQL_DEFAULT_PORT                   80

#include <Arduino.h>
#include <WiFly.h>

class SPARQLClient {
  public:
    SPARQLClient();
    
    int query(const char *url, int timeout = SPARQL_CLIENT_DEFAULT_TIMEOUT);
    int get(const char *url, const char *header, int timeout = SPARQL_CLIENT_DEFAULT_TIMEOUT);
    int post(const char *url, const char *data, int timeout = SPARQL_CLIENT_DEFAULT_TIMEOUT);
    int post(const char *url, const char *headers, const char *data, int timeout = SPARQL_CLIENT_DEFAULT_TIMEOUT);
    
  private:
    int parseURL(const char *url, char *host, int max_host_len, uint16_t *port, char *path, int max_path_len);
    int connect(const char *url, const char *method, const char *data, int timeout = SPARQL_CLIENT_DEFAULT_TIMEOUT);
    int connect(const char *url, const char *method, const char *header, const char *data, int timeout = SPARQL_CLIENT_DEFAULT_TIMEOUT);
 
 
 
 // $endpoint = "https://example.com/sparql-auth";
// $sc = new SparqlClient();
// $sc->setEndpointRead($endpoint);
////$sc->setEndpointWrite($endpoint);
// $sc->setLogin("login");
// $sc->setPassword("password");

// $q = "select *  where {?x ?y ?z.} LIMIT 5";
// $rows = $sp_ReadAndWrite->query($q, 'rows');
// $err = $sp_ReadAndWrite->getErrors();
// if ($err) {
    // print_r($err);
    // throw new Exception(print_r($err, true));
// }

// foreach ($rows["result"]["variables"] as $variable) {
    // printf("%-20.20s", $variable);
    // echo '|';
// }
// echo "\n";
 
 
 
    WiFly* wifly;
};

#endif // __SPARQL_CLIENT_H__

