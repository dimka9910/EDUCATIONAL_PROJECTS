<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Code</title>

    <link rel="stylesheet"
          href="//cdn.jsdelivr.net/gh/highlightjs/cdn-release@10.2.1/build/styles/default.min.css">
    <script src="//cdn.jsdelivr.net/gh/highlightjs/cdn-release@10.2.1/build/highlight.min.js"></script>
    <script>hljs.initHighlightingOnLoad();</script>
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
    <#if codeData.isTimeRestriction()>
        <span id="time_restriction"> ${codeData.time} </span>
    </#if>
    <#if codeData.isViewsRestriction()>
        <span id="views_restriction"> ${codeData.views} </span>
    </#if>
        <script></script>
    </#list>
</ul>
</body>
</html>