/**
 * @authors miclewang@outlook.com
 * @date    2018-05-05
 */

var oBlogs = document.getElementById("blogs");
var uName = getCookie("uName");
var reqUrl='blogsBelongUser';
if(uName)
{
    reqUrl =reqUrl
        + "?uName="
        + uName;
}
$.ajax({
    url: reqUrl,
    success: function (data) {
        var result = JSON.parse(data);
        var html = "<table class=\"t1\">";
        html += "  <thead><th>Title</th><th>Upload</th><th>Update</th><th>Author</th><th>Operation</th></thead>";
        for (var i = 0; i < result.length; i++) {
            var oTr = (i%2==0) ? "<tr>":"<tr class='a1'>";
            var oTitle = "<td><a href = \"detail.html?id="+result[i][5]+"\">"+result[i][1]+"</a></td>";
            var oManage = "<td><a href=\"editor/index.html?id=" + result[i][5] + "\"> 修改</a><a href='#'> 删除 </a></td>";
            var oTime = "<td>" + timestamp2Time(result[i][2])
                + "</td><td>"+ timestamp2Time(result[i][3])
                + "</td><td>" + result[i][4] +"</td>";
            oTr = oTr + oTitle + oTime + oManage + "</tr>";
            html += oTr;
        }
        oBlogs.innerHTML = html + "</table>";
    },
    error: function () {
        console.log("fail");
    }
});