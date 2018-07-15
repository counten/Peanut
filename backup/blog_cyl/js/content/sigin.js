/**
 * @authors wbq813@foxmail.com
 * @date    2018-03-03
 */
var oLoginWapper = document.getElementById("login-wapper");
var oRegistWapper = document.getElementById("register-wapper");

var htmlLogin = "<div class=\"sin-box\">";
    htmlLogin += "<header class=\"sin-title\">";
        htmlLogin += "<div class=\"rot1\"></div>";
        htmlLogin += "<div class=\"rot2\"></div>";
        htmlLogin += "<i class=\"icon-dark\"></i>";
        htmlLogin += "<span class=\"css9de0fa404189f6\">Sin In</span>";
    htmlLogin += "</header>";
    htmlLogin += "<main>";
        htmlLogin += "<form>";
            htmlLogin += "<div class=\"in-box\">";
                htmlLogin += "<label>";
                    htmlLogin += "<span>Email</span>";
                    htmlLogin += "<input type=\"text\"  name=\"user_email\" id=\"user_email\" value = \"\">";
                htmlLogin += "</label>";
            htmlLogin += "</div>";
            htmlLogin += "<div class=\"in-box\">";
                htmlLogin += "<label>";
                    htmlLogin += "<span>Password</span>";
                    htmlLogin += "<input type=\"password\" name=\"user_password\" id=\"user_password\" value=\"\">";
                htmlLogin += "</label>";
            htmlLogin += "</div>";
            htmlLogin += "<div class=\"in-box\">";
                htmlLogin += "<button type=\"button\" id=\"login\">Sin In</button>";
            htmlLogin += "</div>";
        htmlLogin += "</form>";
    htmlLogin += "</main>";
    htmlLogin += "<footer class=\"oth-box\">";
        htmlLogin += "<em>";
            htmlLogin += "<a href=\"#\">Forget password?</a>";
        htmlLogin += "</em>";
        htmlLogin += "<span>";
            htmlLogin += "<a id=\"now_register\" href=\"javascript:;\">Sin Up</a>";
        htmlLogin += "</span>";
    htmlLogin += "</footer>";
    htmlLogin += "</div>";

    oLoginWapper.innerHTML = htmlLogin;


var htmlRegist = "<div class=\"sin-box\">";
htmlRegist += "<header class=\"sin-title\">";
    htmlRegist += "<div class=\"rot1\"></div>";
    htmlRegist += "<div class=\"rot2\"></div>";
    htmlRegist += "<i class=\"icon-dark\"></i>";
    htmlRegist += "<span class=\"css9de0fa404189f6\">Sin Up</span>";
htmlRegist += "</header>";
htmlRegist += "<main>";
    htmlRegist += "<form>";
        htmlRegist += "<div class=\"in-box\">";
            htmlRegist += "<label>";
                htmlRegist += "<span>Email</span>";
                htmlRegist += "<input type=\"text\" name=\"reg_email\" id=\"reg_email\">";
            htmlRegist += "</label>";
        htmlRegist += "</div>";
        htmlRegist += "<div class=\"in-box\">";
            htmlRegist += "<label>";
                htmlRegist += "<input type=\"text\" name=\"emailverify\" id=\"email_verify\" placeholder=\"Enter captcher in mailbox\">";
            htmlRegist += "</label>";
            htmlRegist += "<span id=\"email-captcher\">Captcher</span>";
        htmlRegist += "</div>";
        htmlRegist += "<div class=\"in-box\">";
            htmlRegist += "<label>";
                htmlRegist += "<span>Password</span>";
                htmlRegist += "<input type=\"password\" name=\"password\" id=\"password\">";
            htmlRegist += "</label>";
        htmlRegist += "</div>";
        htmlRegist += "<div class=\"in-box\">";
            htmlRegist += "<button type=\"button\" id=\"register\">Sin Up</button>";
        htmlRegist += "</div>";
    htmlRegist += "</form>";
htmlRegist += "</main>";
htmlRegist += "<footer class=\"oth-box\">";
    htmlRegist += "<em>";
        htmlRegist += "<a href=\"#\">Aready Have Account?</a>";
    htmlRegist += "</em>";
    htmlRegist += "<span>";
        htmlRegist += "<a id=\"now_login\" href=\"javascript:;\">Sin In</a>";
    htmlRegist += "</span>";
htmlRegist += "</footer>";
htmlRegist += "</div>";

oRegistWapper.innerHTML = htmlRegist;