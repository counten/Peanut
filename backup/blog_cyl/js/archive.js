/**
 * @authors wbq813@foxmail.com
 * @date    2018-03-03
 */

var oArchive = document.getElementById("archive");

window.onload = function () {
    //给div添加文本元素
    $.ajax({
        url: "archive",
        success: function (data) {
            var result = JSON.parse(data);
            var html = "";
            var year_month = "";
            for (var i = 0; i < result.length; i++) {
                var oDiv = "";
                if(year_month != timestamp2Ym(result[i][1]))
                {
                    if(i != 0)
                    {
                        oDiv += "</ul></div>";
                    }
                    year_month = timestamp2Ym(result[i][1]);                    
                    oDiv += "<div class = \"item\"><h3>" + year_month +":</h3><ul class=\"list\">";
                }             
                oDiv = oDiv +"<li><time>Day: " +timestamp2Date(result[i][1]) +" </time>";
                oDiv = oDiv + "<a href = \"detail.html?id="+result[i][2]+"\"> " + result[i][0] +" </a>";
                oDiv = oDiv +"<span class=\"text-muted\"> connemt(0)</span></li>";
                html += oDiv ;            
            }
            oArchive.innerHTML = html + "</ul></div>";
        },
        error: function () {
            console.log("fail");
        }
    });
}