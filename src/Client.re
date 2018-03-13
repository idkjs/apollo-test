open ApolloLinks;

open ApolloInMemoryCache;

/* Define type for InMemoryCache's dataIdFromObject option  */
type dataObject = {
  .
  "__typename": string,
  "id": string,
  "key": string,
};

let logout = () => ();

/* Create an HTTP Link */
let httpLink =
  createHttpLink(
    ~uri="https://api.graph.cool/simple/v1/cjdgba1jw4ggk0185ig4bhpsn",
    (),
  );

/* Create a Link that puts an Authorization header in context */
let contextHandler = () => {
  let token = "123";
  let headers = {
    "headers": {
      "authorization": {j|Bearer $token|j},
    },
  };
  headers;
};

let authLink = createContextLink(contextHandler);

/* Create a Link that handles 401 error responses */
let errorHandler = errorResponse =>
  switch (errorResponse##networkError) {
  | Some(error) =>
    if (error##statusCode == 401) {
      logout();
    } else {
      ();
    }
  | None => ()
  };

let errorLink = createErrorLink(errorHandler);

let inMemoryCache =
  createInMemoryCache(
    ~dataIdFromObject=
      (obj: dataObject) =>
        if (obj##__typename === "Organization") {
          obj##key;
        } else {
          obj##id;
        },
    (),
  );

/*
   Default in memory cache
   let inMemoryCache = createInMemoryCache(());
 */
/* Create the ApolloClient */
module Instance =
  ReasonApollo.CreateClient(
    {
      let apolloClient =
        ReasonApollo.createApolloClient(
          ~cache=inMemoryCache,
          ~link=from([|authLink, errorLink, httpLink|]),
          (),
        );
    },
  );
/* open ApolloLinks;

   open ApolloInMemoryCache;

   /* type dataObject = {
        .
        "__typename": string,
        "id": string,
        "key": string,
      }; */
   type dataObject = {
     .
     "__typename": string,
     "id": string,
     "key": string,
   };

   /* Create an InMemoryCache */
   let inMemoryCache =
     createInMemoryCache(~dataIdFromObject=(obj: dataObject) => obj##id, ());

   /* Create an HTTP Link */
   /* let httpLink = ApolloLinks.createHttpLink(~uri="http://swapi.apis.guru/", ()); */
   let httpLink =
     createHttpLink(
       ~uri=
         Printf.sprintf(
           "https://api.graph.cool/simple/v1/cjdgba1jw4ggk0185ig4bhpsn",
         ),
       /* ~credentials="include", */
       (),
     );

   let logout = () => ();

   /* Create a Link that handles 401 error responses */
   let errorHandler = errorResponse =>
     switch (errorResponse##networkError) {
     | Some(error) =>
       if (error##statusCode == 401) {
         logout();
       } else {
         ();
       }
     | None => ()
     };

   let errorLink = createErrorLink(errorHandler);

   module Instance =
     ReasonApollo.CreateClient(
       {
         let apolloClient =
           ReasonApollo.createApolloClient(
             ~cache=inMemoryCache /* restore method can be piped e.g. inMemoryCache |> restore(window.__APOLLO__) */,
             ~link=from([|errorLink, httpLink|]),
             (),
           );
       },
     ); */