/**
 * @authors miclewang@outlook.com
 * @date    2018-03-03
 */

var oBlogs = document.getElementById("blogs");
var params = GetUrlParams();

window.onload = function () {
    var reqUrl='blogs';
    if(params.tagId)
    {
        reqUrl =reqUrl 
        + "?tagId="
        + params.tagId;
    }
    //给div添加文本元素
    $.ajax({
        url: reqUrl,
        success: function (data) {
            var result = JSON.parse(data);
            var html = "";
            for (var i = 0; i < result.length; i++) {
                var oDiv = "<div>";                
                var oTitle = "<a href = \"detail.html?id="+result[i][9]+"\"><h3>"+result[i][1]+"</h3></a> ";
                var oDesc = "<h4>" + result[i][2] + "</h4>";
                var oTime = "Upload: " + timestamp2Time(result[i][3]) + "  Updated: "+ timestamp2Time(result[i][4]) + "  Author: " + result[i][6];
                var oTag = "  Tags:  <a href=\"index.html?tagId=" +result[i][7] +"\">"+result[i][8] + "</a>";
                oDiv = oDiv + oTitle + oDesc + oTime + oTag + "</div>";
                html += oDiv;            
            }
            oBlogs.innerHTML = html;
        },
        error: function () {
            console.log("fail");
        }
    });
}