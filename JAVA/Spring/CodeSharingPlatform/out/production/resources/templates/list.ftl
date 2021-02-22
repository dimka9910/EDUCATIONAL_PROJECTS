<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Latest</title>
</head>
<body>
<ul>
    <#list codeDatas as codeData>
        <span id="load_date"> ${codeData.date} </span>
            <pre id="code_snippet">
                <code>
                    ${codeData.code}
                </code>
            </pre>
    </#list>
</ul>
</body>
</html>