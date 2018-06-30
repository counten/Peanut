(function ($) {
    $.extend({
        dialog: function (options) {
            //默认值
            var defaults = {
                title: '',//标题，当为空或者长度为0时，将不显示标题
                message: '',//message文本，支持html(传入htmlid),你可以在这里定义你的小图标
                message_type: 'text', //text 文本消息，html，message 是外部html的id; 
                mask: true,//是否显示遮罩。默认为有遮罩
                maxWidth: '',//最大宽度,为空时自适应宽
                maxHeight: '',//最大高度，为空时自适应高
                okText: '',//确定按钮文字，当为空时将不显示此按钮
                cancelText: '',//取消按钮文字，为空时将不显示此按钮
                okEvent: null,//确定按钮事件，为空时不执行任何事件
                cancelEvent: null, //取消按钮事件,为空时不执行任何事件
                autoTime: '-1',//自动关闭时间,当时间小于0时，没有自动关闭
                autoEvent: null, //自动关闭后的事件，为空时不执行任何事件
                append: '',//父容器id，是否把弹窗定位于某一容器中
                showClose: true//是否显示关闭按钮，默认显示
            };

            var options = $.extend(defaults, options);
            var id = _generateMixed(5);
            var _boxId = _creat(options, id);
            $("#btnok" + id).unbind().bind("click", function () {
                if (options.okEvent) {
                    options.okEvent();
                }
                _close(id);
            });
            $("#btncancel" + id).unbind(_creat).bind("click", function () {
                if (options.cancelEvent) {
                    options.cancelEvent();
                }
                _close(id);
            });
            _drag(_boxId, 1);
            return _boxId;
        },
        close: function (boxid) {
            var i_creatd = boxid.replace("box", "");
            var bg = "bg" + id, box = "box" + id;
            $("#" + bg).remove();
            $("#" + box).remove();
            clearTimeout(t);
        }
    });
    function _creat(options, id) {
        var _bgId = "bg" + id, _boxId = "box" + id, _borderId = "border" + id, _titleId = 'titleId' + id, _btnokid = "btnok" + id, _btncancelId = "btncancel" + id, _closeid = 'btnclose' + id;
        
        // If need title;
        var title = '';
        if (options.title.length > 0)
            title = '<div id="' + _titleId + '" class="title"  style="cursor: move;">' +options.title + '</div>';
        title += ((options.showClose == true) ? '<a id="' + _closeid + '" class="close" href="javascript:void(0)" onclick="_close(\'' + id + '\')"> X </a>' : "");
        
        // if need button;
        var _buttonOk = "", _buttonCancel = "";
        if (options.okText.length > 0)
            _buttonOk = '<A id="' + _btnokid + '" class="btnok"  href="javascript:void(0)">' + options.okText + '</A>&nbsp;';
        if (options.cancelText.length > 0)
            _buttonCancel = '<A id="' + _btncancelId + '"class="btncancel" href="javascript:void(0)" >' + options.cancelText + '</A>';
        if (options.okText.length > 0 || options.cancelText.length > 0)
            button = '<div id="btnArea">' +_buttonCancel+_buttonOk+ "</div>";
        else
            button = "";

        // If need message;
        var  message = '';
        if(options.message.length > 0){
            if(options.message_type == 'text'){
                message = ' <P id="message-text">' + options.message + '</P>';                
            }
            else{
                message = options.message;
            }
        }

        // If need Mask;
        if (options.mask == true)
            $("BODY").append('<div id="' + _bgId + '" class="ug_bg"></div>');
        
        // Show box;
        var _boxWi = "";
        if (!isNaN(options.maxWidth))
            _boxWi = "width:" + options.maxWidth + "px" + ";";
        var _boxHe = "";
        if (!isNaN(options.maxHeight))
            _boxHe = "height:" + options.maxHeight + "px" + ";";
        var box = ''
            + '<DIV id="' + _boxId + '" class="ug_layer drag" style="' + _boxWi + _boxHe + '" >'
            + title
            + '<DIV class="mainmessage">' 
            + message
            + '</DIV>'
            + button
            + '</DIV>'
            + '';
        $("BODY").append(box);
        //浏览器可视窗口的高度和宽度，中间显示
        var w = $("#" + _boxId).css("width").toUpperCase().replace("PX", "");
        var h = $("#" + _boxId).css("height").toUpperCase().replace("PX", "");
        var _tar_left = ($(window).width() - w) / 2;
        var _tar_top = ($(window).height() - h) / 2;
        $("#" + _boxId).css({
            "left": _tar_left,
            "top": _tar_top
        });

        // Need autoclose;
        if (!isNaN(options.autoTime) && options.autoTime > 1) {
            _countDown(options.autoTime, id, options.autoEvent);
        };

        //如果有目标容器
        if (options.append.length > 0) {
            var area_top = $("#" + options.append).offset().top;
            var area_left = $("#" + options.append).offset().left;
            var area_w = $("#" + options.append).css("width").toUpperCase().replace("PX", "");
            var area_h = $("#" + options.append).css("height").toUpperCase().replace("PX", "");

            var w = $("#" + _boxId).css("width").toUpperCase().replace("PX", "");
            var h = $("#" + _boxId).css("height").toUpperCase().replace("PX", "");
            var _tar_left = area_left + (area_w - w) / 2;
            var _tar_top = area_top + (area_h - 150) / 2;
            $("#" + _bgId).css({
                "width": area_w + "px",
                "height": area_h + "px",
                "top": area_top,
                "left": area_left,
                "position": "absolute"
            });
            $("#" + _boxId).css({
                "position": "absolute",
                "left": _tar_left,
                "top": _tar_top
            });
        }
        return _boxId;
    };
    _generateMixed = function (n) {
        var chars = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'];
        var res = "";
        for (var i = 0; i < n; i++) {
            var id = Math.ceil(Math.random() * 35);
            res += chars[id];
        }
        return res;
    };
    _drag = function (boxId, s) {
        //整个dia的宽高
        var dia_width = $("#" + boxId).css("width").toUpperCase().replace("PX", "");
        var dia_height = $("#" + boxId).css("height").toUpperCase().replace("PX", "");
        var new_x = ""; //目标位置
        var new_y = "";
        var orig_x = ""; //单击时的源位置
        var orig_y = "";
        var setLeft = ""; //单击时离元素最左上角的位置
        var offsetTop = "";
        if (typeof boxId == "string") boxId = document.getElementById(boxId);
        boxId.orig_index = boxId.style.zIndex;
        $(".drag").on('mousedown', function (a) {
            //移动时加个遮照，可不要
            // boxId.style.zIndex = 10000;
            // document.getElementById("aclolse").style.zIndex = 999999;
            if (!a) a = window.event;
            setLeft = a.clientX + document.body.scrollLeft - boxId.offsetLeft;
            setTop = a.clientY + document.body.scrollTop - boxId.offsetTop;
            document.ondragstart =  false;
            document.onselectstart =  false;
            document.onselect = "document.selection.empty();";
            if (boxId.setCapture)
                boxId.setCapture();
            else if (window.captureEvents)
                window.captureEvents(Event.MOUSEMOVE | Event.MOUSEUP);
            document.onmousemove = function (a) {
                if (!a) a = window.event;
                new_x = _mousePosition(a).clientX - setLeft;
                new_y = a.clientY + document.body.scrollTop - setTop;
                //控制边界
                if (new_x < 0) new_x = 8;
                if (new_x > $(window).width() - dia_width) new_x = $(window).width() - dia_width;
                if (new_y > $(window).height() - dia_height) new_y = $(window).height() - dia_height;
                if (new_y < 0) new_y = 10;
                boxId.style.left = new_x.toString() + "px";;
                boxId.style.top = new_y.toString() + "px";
                //保存最后位置
                boxId.orig_x = parseInt(boxId.style.left) - _mousePosition(a).scrollLeft;
                boxId.orig_y = parseInt(boxId.style.top) - _mousePosition(a).scrollTop;
            }
            document.onmouseup = function () {
                if (boxId.releaseCapture)
                    boxId.releaseCapture();
                else if (window.captureEvents)
                    window.captureEvents(Event.MOUSEMOVE | Event.MOUSEUP);
                document.onmousemove = null;
                document.onmouseup = null;
                document.ondragstart = null;
                document.onselectstart = null;
                document.onselect = null;
                boxId.style.zIndex = boxId.orig_index;
            }
        });
        window.onresize = function () {
            boxId.style.left = ($(window).width() - dia_width) / 2 + "px";
            boxId.style.top = ($(window).height() - dia_height) / 2 + "px";
        }
    };
    _mousePosition = function (ev) {
        var obj = { bodyX: '', bodyY: '', screenX: '', screenY: '', clientX: '', clientY: '', scrollLeft: '', scrollTop: '' };
        obj.screenX = ev.screenX; //相对于屏幕
        obj.screenY = ev.screenY;
        obj.clientX = ev.clientX; //相对浏览器窗口
        obj.clientY = ev.clientY;
        obj.scrollLeft = document.body.scrollLeft;
        obj.scrollTop = document.body.scrollTop;
        //相对于文档body
        obj.bodyX = ev.pageX || (ev.clientX + (document.documentElement.srcollLeft || document.body.scrollLeft));
        obj.bodyY = ev.pageY || (ev.clientY + (document.documentElement.scrollTop || document.body.scrollTop));
        return obj;
    };
    _countDown = function (autoTime, id, autoEvent) {
        clearTimeout(t);
        var jumpTo = $("#box" + id + " .mainmessage");
        //jumpTo.html(txt + "(<font>" + secs + '</font> ' + secsWord + ')');
        jumpTo.html(jumpTo.html().replace(autoTime + 1, '').replace("{s}", autoTime + "{s}"));
        if (--autoTime > 0) {
            t = window.setTimeout("_countDown(" + autoTime + ",'" + id + "'," + autoEvent + ")", 1000);
        }
        else {
            _close(id);
            if (autoEvent)
                autoEvent();
        }
    };
    //关闭事件
    _close = function (id) {
        var bg = "bg" + id, box = "box" + id;
        $("#" + bg).remove();
        $("#" + box).remove();
        clearTimeout(t);
    };
    var t;
})(jQuery);