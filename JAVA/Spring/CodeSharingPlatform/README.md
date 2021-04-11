Description
-----------

Programming is full of little secrets. Sometimes, even within the same company, there is some secret code that should be hidden from most of the colleagues. This piece of code should only be available to certain people, and it may be deleted in the future to hide the traces.

In this stage, let's make such functionality possible. You will need to add two limitations on the code snippet's visibility:

1.  **A limit on the number of views** will allow viewing the snippet only a certain number of times, after which the snippet is deleted from the database.
2.  **A limit on the viewing time** will allow viewing a code snippet for a certain period of time, and after its expiration, the code snippet is deleted from the database.

If both restrictions are applied to a certain code snippet, it has to be deleted when at least one of these limits is reached.

Obviously, the hidden pieces of code should not be shown on the `GET /code/latest` page or available by the `GET /api/code/latest` request. They should only be available through a link. So, remember that **the latest snippets should not contain any restrictions**.

If you are a true spy, you might object: if all the links have numeric identifiers, can't we find the secret snippets just by looking through the different numbers? Indeed, it is quite easy to access secret links this way. To avoid this, let's generate links not with consecutive numbers but with UUID's (Universally Unique IDentifiers). To implement this, see a [tutorial on generating the UUID](https://kodejava.org/how-do-i-generate-uuid-guid-in-java/). Now, no snippets can be obtained without a direct link!

Objectives
----------

In this stage, your program should support the same endpoints as in the previous stage. Here is what's going to be different:

*   Code snippets should be accessible via UUID links. `POST /api/code/new` should return a UUID of the snippet instead of a number.  
    
*   `POST /api/code/new` should take a JSON object with a field `code` and two other fields:  
    1\. `time` field contains the time (in seconds) during which the snippet is accessible.  
    2\. `views` field contains a number of views allowed for this snippet.  
    Remember, that 0 and negative values should correspond to the absence of the restriction.  
    
*   `GET /code/new` should contain two elements on top of the others:  
    1\. `<input id="time_restriction" type="text"/>` should contain the time restriction.  
    2\. `<input id="views_restriction" type="text"/>` should contain the views restriction  
      
    Remember that POST request should contain numbers, not strings.  
    
*   `GET /api/code/latest` and `GET /code/latest` should not return any restricted snippets.  
    
*   `GET /api/code/UUID` should not be accessible if one of the restrictions is triggered. Return `404 Not Found` in this case and all the cases when no snippet with such a UUID was found.  
    
*   `GET /api/code/UUID` should show what restrictions apply to the code piece. Use the keys `time` and `views` for that. A zero value (0) should correspond to the absence of the restriction.  
    1\. `time` field contains the time (in seconds) during which the snippet is accessible.  
    2\. `views` field shows how many additional views are allowed for this snippet (excluding the current one).  
    
*   `GET /code/UUID` should contain the following elements:  
    1.`<span id="time_restriction"> ... </span>` in case the time restriction is applied.  
    2\. `<span id="views_restriction"> ... </span>` in case the views restriction is applied.  
      
    Note: if only one of the restrictions is applied, you should show only one of the above elements.
