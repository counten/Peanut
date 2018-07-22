$(function () {

	// aready login
	let uname = getCookie("uName");
	let uemail = getCookie("uEmail");
	if(uname != null && uemail != null){
		loginSuccess(uname, uemail);
	}
	
	// ***************弹出登录注册***************
	function popUp(id) {
		if (id == "#login_btn") {
			$(id).on("click", function (event) {
				$(".mask")
					.slideDown(1000);
				$("#login-wapper")
					.delay(500)
					.slideDown(1000);
				event.stopPropagation();
			});
		} else if (id == "#register_btn") {
			$(id).on("click", function (event) {
				$(".mask")
					.slideDown(1000);
				$("#register-wapper")
					.delay(500)
					.fadeIn(1000);
				event.stopPropagation();
			});
		}

	}
	popUp("#login_btn");
	popUp("#register_btn");

	// ***************立即注册***************
	$("#now_register").on("click", function (event) {
		event.stopPropagation();
		$("#login-wapper").slideUp(1000);
		$("#register-wapper").delay(1000).fadeIn(500);
	});

	// ***************立即登录***************
	$("#now_login").on("click", function (event) {
		event.stopPropagation();
		$("#register-wapper").fadeOut(1000);
		$("#login-wapper").delay(1000).slideDown(500);
	});


	// ***************点击空白处隐藏***************
	function hidden_popUp(popup) {
		$(document.body).on("click", function (event) {
			var target = $(event.target);
			if (event.target != target && target.closest(popup).length == 0) {
				closeMask(popup);
			}
			event.stopPropagation();
		});
	}
	hidden_popUp("#login-wapper");
	hidden_popUp("#register-wapper");

	// ***************点击输入框隐藏文字和边框动画***************
	function hidden_txt(id) {
		$(id).on("focus blur", function (event) {
			event.stopPropagation();
			var $this = $(this);
			if (event.type == "focus") {
				$this.siblings("span").css("color", "#666");
				// 添加边框动画
				$("#login-wapper").css("animation", "colors 20s ease infinite");
			} else if (event.type == "blur") {
				$this.siblings("span").css("color", "#fff");
				$("#login-wapper").css("animation", "none");
			}
		});
		// 隐藏输入框里面span的文字
		$(id).on("input", function (event) {
			if ($(this).val() != "") {
				$(this).siblings("span").fadeOut();
			} else {
				$(this).siblings("span").fadeIn();
			}
			event.stopPropagation()
		});
	}

	hidden_txt("#user_email");
	hidden_txt("#user_password");

	// ***************用户ajax实现用户登录***************
	$("#login").on("click", function () {
		var $user_email = $("#user_email").val();
		var $user_password = $("#user_password").val();
		if ($user_email != "" && $user_password != "") {
			console.log("send" + $user_email);
			$.ajax({
				type: "POST",
				url: "login",
				dataType: "JSON",
				data: {
					"user_email": $user_email,
					"user_password": $user_password
				},
				success: function (data) {
					console.log(data);
					if(data[0][1] == $user_email)
					{  
						closeMask("#login-wapper");
						loginSuccess(data[0][0], data[0][1]);
					}
					else
					{
						loginRegTip(loginRegisterTip.userPassword_wrong);
					}
				}
			});
		} else {
			loginRegTip(loginRegisterTip.phoneOrPassowrd_blank);
		}
	});


	// ***************用户ajax实现用户注册***************
	$('#register').click(function () {
		// 获取用户手机号码
		var $userphone = $('#user_phone').val();
		// 获取注册密码
		var $regpassword = $("#reg_password").val();
		// 获取手机验证码  
		var $code = $("#phone_verify").val();
		// 判断手机号码和密码是否为空，验证码的长度是否为4
		if ($userphone != "" && $regpassword != "") {
			if ($code.length == 4) {
				$.ajax({
					type: "POST",
					url: "php/addUser.php",
					dataType: "JSON",
					data: {
						"userphone": $userphone,
						"regpassword": $regpassword,
						"code": $code
					},
					success: function (data) {
						switch (data) {
							case 1:
								//用户已存在  
								loginRegTip(loginRegisterTip.userPhone_exist);
								break;
							case 2:
								//注册成功  
								alert("注册成功！");
								//$.cookie("user",user_email);  
								//$.cookie("limit",0);  
								window.location.href = "index.php";
								break;
							case 0:
								//验证码错误  
								loginRegTip(loginRegisterTip.phoneVerify_wrong);
								break;
						}
					}
				})
			} else {
				loginRegTip(loginRegisterTip.phoneVerify_length);
			}
		} else {
			loginRegTip(loginRegisterTip.phoneOrPassowrd_blank);
		}
	});
});

// log success
function loginSuccess(uName, uEmail)
{
	setCookie("uName",uName);
	setCookie("uEmail",uEmail);
	$("#login_btn").text(uName);
	$("#login_btn").attr("href","#");
	$("#login_btn").unbind("click");
	$("#drop_down_list").css("display","block");
}

// close mask
function closeMask(popup)
{
	if ($(popup).css("display") == "block") {
		$(".mask")
			.delay(500)
			.fadeOut(1000);
		$(popup)
			.fadeOut(1000);
	}
}

// Sin out
var oLogOutBtn = document.getElementById("logout_btn");
var oUserArea = document.getElementById("user_area");
oLogOutBtn.onclick = function(){
	delCookie("uName");
	delCookie("uEmail");
	window.location.href = "index.html";
}