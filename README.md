# Error

## Typename in Client.re is set to Organization

* you get same error if set to 'Person' as set on the server for Person.

* test [query](https://graphqlbin.com/xkKDfL)

* test with curl:

```
curl 'https://api.graph.cool/simple/v1/cjdgba1jw4ggk0185ig4bhpsn' -H 'Accept-Encoding: gzip, deflate, br' -H 'Content-Type: application/json' -H 'Accept: */*' -H 'Connection: keep-alive' -H 'DNT: 1' -H 'Origin: https://api.graph.cool' --data-binary '{"query":"query getAllPersons {\n        people:allPersons {\n          id\n          age\n          name\n          __typename\n          \n        }\n      }","operationName":"getAllPersons"}' --compressed
```
