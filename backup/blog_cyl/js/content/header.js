/**
 * @authors wbq813@foxmail.com
 * @date    2018-03-03
 */

var oHeader = document.getElementById("header");

var html = "<nav class=\"navbar navbar-default\">";
html += "<div class=\"container-fluid\">";
html += "<!-- Brand and toggle get grouped for better mobile display -->";
html += "<div class=\"navbar-header\">";
html += "<button type=\"button\" class=\"navbar-toggle collapsed\" data-toggle=\"collapse\" data-target=\"#bs-example-navbar-collapse-1\"";
html += "aria-expanded=\"false\">";
html += "<span class=\"sr-only\">Toggle navigation</span>";
html += "<span class=\"icon-bar\"></span>";
html += "<span class=\"icon-bar\"></span>";
html += "<span class=\"icon-bar\"></span>";
html += "</button>";
html += "<a class=\"navbar-brand\" href=\"index.html\"> CodeYourLife </a>";
html += "</div>";

html += "<!-- Collect the nav links, forms, and other content for toggling -->";
html += "<div class=\"collapse navbar-collapse\" id=\"bs-example-navbar-collapse-1\">";
html += "<ul class=\"nav navbar-nav navbar-right\">";
html += "<li id='index0'>";
html += "<a href=\"index.html\"> Blog";
html += "</a>";
html += "</li>";
html += "<li id='index1'>";
html += "<a href=\"archives.html\"> Archives";
html += "</a>";
html += "</li>";
html += "<li id='index2'>";
html += "<a href=\"tags.html\"> Tags";
html += "</a>";
html += "</li>";
html += "<li id='index3'>";
html += "<a href=\"author.html\"> Author";
html += "</a>";
html += "</li>";
html += "<li id='index4'>";
html += "<a href=\"product.html\"> Products";
html += "</a>";
html += "</li>";
html += "<li id='index5'>";
html += "<a href=\"favorite.html\"> Favorite";
html += "</a>";
html += "</li>";

html += "<li class=\"\" id = \"user_area\">";
html += "<a id=\"login_btn\" href=\"javascript:;\">Sin in|up</a>";


html += "<ul id = \"drop_down_list\" class=\"sub-menu\">";
html += "<li><a href=\"editor/index.html\">Create Blog</a></li>";
html += "<li><a href=\"manage.html\">Manage</a></li>";
html += "<li><a id=\"logout_btn\" href=\"javascript:;\">Sin Out</a></li>";
html += "</ul>";


html += "</li>";

html += "</ul>";
html += "</div>";
html += "</div>";
html += "</nav>";

oHeader.innerHTML = html;
$(document).ready(function() {
	var title = document.title;
	var activeIn ;
	switch (title){
        case "CodeYourLife | Archives":
            activeIn = "index1"
            break
        case "CodeYourLife | Tags":
            activeIn = "index2"
            break
        case "CodeYourLife | Author":
            activeIn = "index3"
            break
        case "CodeYourLife | Product":
            activeIn = "index4"
            break
        case "CodeYourLife | Favorite":
            activeIn = "index5"
            break
        default:
            activeIn = "index0";
	}
	document.getElementById(activeIn).setAttribute("class","active");
});
