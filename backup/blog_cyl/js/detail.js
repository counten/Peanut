/**
 * @authors miclewang@outlook.com
 * @date    2018-03-03
 */
var oDetail = document.getElementById("detail");
var params = GetUrlParams();

// Because highlight.js is a bit awkward at times
var languageOverrides = {
    js: 'javascript',
    html: 'xml'
};

var md = markdownit({
    html: true,
    highlight: function(code, lang) {
        if (languageOverrides[lang]) lang = languageOverrides[lang];
        if (lang && hljs.getLanguage(lang)) {
            try {
                return hljs.highlight(lang, code).value;
            } catch (e) {}
        }
        return '';
    }
})
.use(markdownitFootnote);

window.onload = function(){
    //给div添加文本元素
    $.ajax({
        url: "detail?id=" + params.id,
        success: function (data) {
            var result = JSON.parse(data);
            var htm = md.render(result[0][1]);
            oDetail.innerHTML = htm;
        },
        error: function () {
            console.log("fail");
        }
    });
}