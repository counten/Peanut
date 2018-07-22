var URL = window.URL || window.webkitURL || window.mozURL || window.msURL;
navigator.saveBlob = navigator.saveBlob || navigator.msSaveBlob || navigator.mozSaveBlob || navigator.webkitSaveBlob;
window.saveAs = window.saveAs || window.webkitSaveAs || window.mozSaveAs || window.msSaveAs;

var detail_id = "";

// Because highlight.js is a bit awkward at times
var languageOverrides = {
    js: 'javascript',
    html: 'xml'
};

var livestyles;

emojify.setConfig({
    img_dir: 'emoji'
});

var md = markdownit({
    html: true,
    highlight: function (code, lang) {
        if (languageOverrides[lang]) lang = languageOverrides[lang];
        if (lang && hljs.getLanguage(lang)) {
            try {
                return hljs.highlight(lang, code).value;
            } catch (e) { }
        }
        return '';
    }
})
    .use(markdownitFootnote);

var hashto;

function update(e) {
    setOutput(e.getValue());

    //If a title is added to the document it will be the new document.title, otherwise use default
    var headerElements = document.querySelectorAll('h1');
    if (headerElements.length > 0 && headerElements[0].textContent.length > 0) {
        title = headerElements[0].textContent;
    } else {
        title = 'CodeYourLife | Editor'
    }

    //To avoid to much title changing we check if is not the same as before
    oldTitle = document.title;
    if (oldTitle != title) {
        oldTitle = title;
        document.title = title;
    }
    //clearTimeout(hashto);
    //hashto = setTimeout(updateHash, 1000);
}

function setOutput(val) {
    val = val.replace(/<equation>((.*?\n)*?.*?)<\/equation>/ig, function (a, b) {
        return '<img src="http://latex.codecogs.com/png.latex?' + encodeURIComponent(b) + '" />';
    });

    var out = document.getElementById('out');
    var old = out.cloneNode(true);
    out.innerHTML = md.render(val);
    emojify.run(out);

    var allold = old.getElementsByTagName("*");
    if (allold === undefined) return;

    var allnew = out.getElementsByTagName("*");
    if (allnew === undefined) return;

    for (var i = 0, max = Math.min(allold.length, allnew.length); i < max; i++) {
        if (!allold[i].isEqualNode(allnew[i])) {
            out.scrollTop = allnew[i].offsetTop;
            return;
        }
    }
}

CodeMirrorSpellChecker({
    codeMirrorInstance: CodeMirror,
});

var editor = CodeMirror.fromTextArea(document.getElementById('code'), {
    mode: "spell-checker",
    backdrop: "gfm",
    lineNumbers: false,
    matchBrackets: true,
    lineWrapping: true,
    theme: 'base16-light',
    extraKeys: {
        "Enter": "newlineAndIndentContinueMarkdownList"
    }
});

editor.on('change', update);

function selectionChanger(selection, operator, endoperator) {
    if (selection == "") {
        return operator;
    }
    if (!endoperator) {
        endoperator = operator
    }
    var isApplied = selection.slice(0, 2) === operator && seisAppliedection.slice(-2) === endoperator;
    var finaltext = isApplied ? selection.slice(2, -2) : operator + selection + endoperator;
    return finaltext;
}

editor.addKeyMap({
    // bold
    'Ctrl-B': function (cm) {
        cm.replaceSelection(selectionChanger(cm.getSelection(), '**'));
    },
    // italic
    'Ctrl-I': function (cm) {
        cm.replaceSelection(selectionChanger(cm.getSelection(), '_'));
    },
    // code
    'Ctrl-K': function (cm) {
        cm.replaceSelection(selectionChanger(cm.getSelection(), '`'));
    },
    // keyboard shortcut
    'Ctrl-L': function (cm) {
        cm.replaceSelection(selectionChanger(cm.getSelection(), '<kbd>', '</kbd>'));
    }
});

document.addEventListener('drop', function (e) {
    e.preventDefault();
    e.stopPropagation();

    var reader = new FileReader();
    reader.onload = function (e) {
        editor.setValue(e.target.result);
    };

    reader.readAsText(e.dataTransfer.files[0]);
}, false);

//Print the document named as the document title encoded to avoid strange chars and spaces
function saveAsMarkdown() {
    save(editor.getValue(), document.title.replace(/[`~!@#$%^&*()_|+\-=?;:'",.<>\{\}\[\]\\\/\s]/gi, '') + ".md");
}

//Print the document named as the document title encoded to avoid strange chars and spaces
function saveAsHtml() {
    save(document.getElementById('out').innerHTML, document.title.replace(/[`~!@#$%^&*()_|+\-=?;:'",.<>\{\}\[\]\\\/\s]/gi, '') + ".html");
}

function save(code, name) {
    var blob = new Blob([code], {
        type: 'text/plain'
    });
    if (window.saveAs) {
        window.saveAs(blob, name);
    } else if (navigator.saveBlob) {
        navigator.saveBlob(blob, name);
    } else {
        url = URL.createObjectURL(blob);
        var link = document.createElement("a");
        link.setAttribute("href", url);
        link.setAttribute("download", name);
        var event = document.createEvent('MouseEvents');
        event.initMouseEvent('click', true, true, window, 1, 0, 0, 0, 0, false, false, false, false, 0, null);
        link.dispatchEvent(event);
    }
}

function openFile(evt) {
    if (window.File && window.FileReader && window.FileList && window.Blob) {
        var files = evt.target.files;
        console.log(files);
        var reader = new FileReader();
        reader.onload = function (file) {
            console.log(file.target.result);
            editor.setValue(file.target.result);
            return true;
        };
        reader.readAsText(files[0]);

    } else {
        alert('The File APIs are not fully supported in this browser.');
    }
}

document.addEventListener('keydown', function (e) {
    if (e.keyCode == 83 && (e.ctrlKey || e.metaKey)) {
        e.shiftKey ? showMenu() : saveInBrowser();

        e.preventDefault();
        return false;
    }

    if (e.keyCode === 27 && menuVisible) {
        hideMenu();

        e.preventDefault();
        return false;
    }
});

function clearEditor() {
    editor.setValue("");
}

function saveInBrowser() {
    var text = editor.getValue();
    if (localStorage.getItem('content')) {
        jQuery.dialog({
            title: 'Existing Data Detected',
            message: 'You will overwrite the data previously saved!',
            okText: 'Overwrite!',
            cancelText: 'Cancel',
            showClose: false,
            okEvent: function () {
                localStorage.setItem('content', text);
                jQuery.dialog({
                    title: 'Saved',
                    message: 'Your Document has been saved.',
                    okText: 'OK',
                    showClose: false
                });
            }
        });
    } else {
        localStorage.setItem('content', text);
        jQuery.dialog({
            title: 'Saved',
            message: 'Your Document has been saved.',
            okText: 'OK',
            showClose: false
        });
    }
}

function toggleNightMode(button) {
    button.classList.toggle('selected');
    document.getElementById('toplevel').classList.toggle('nightmode');
}

function toggleReadMode(button) {
    button.classList.toggle('selected');
    document.getElementById('out').classList.toggle('focused');
    document.getElementById('in').classList.toggle('hidden');
}

function updateHash() {
    window.location.hash = btoa( // base64 so url-safe
        RawDeflate.deflate( // gzip
            unescape(encodeURIComponent( // convert to utf8
                editor.getValue()
            ))
        )
    );
}

function start() {
    // update blog
    var params = GetUrlParams();
    if(params.id){
        detail_id = params.id;
        $.ajax({
            url: "../detail?id=" + detail_id,
            success: function (data) {
                IsUpdate = true;
                var result = JSON.parse(data);
                editor.setValue(result[0][1]);
            },
            error: function () {
                console.log("fail");
            }
        });
    }
    else if (window.location.hash) {
        var h = window.location.hash.replace(/^#/, '');
        if (h.slice(0, 5) == 'view:') {
            setOutput(decodeURIComponent(escape(RawDeflate.inflate(atob(h.slice(5))))));
            document.body.className = 'view';
        } else {
            editor.setValue(
                decodeURIComponent(escape(
                    RawDeflate.inflate(
                        atob(
                            h
                        )
                    )
                ))
            );
        }
        var readbutton = document.getElementById('readbutton');
        readbutton.click();
    } else if (localStorage.getItem('content')) {
        editor.setValue(localStorage.getItem('content'));
    }
    update(editor);
    editor.focus();
    document.getElementById('fileInput').addEventListener('change', openFile, false);
}

// before release
function beforeRelease() {
    jQuery.dialog({
        title: 'Release To Server',
        message_type: 'html',
        message: '<div><label>Desc:</label><textarea id=desc></textarea></div><div><label>Tags:</label><input type=text list=tagList id=tags><datalist id=tagList></datalist></div>',
        maxWidth: 400,
        maxHeight: 300,
        okText: 'Release',
        cancelText: 'Cancel',
        showClose: false,
        okEvent: function () {
            release();
        }
    });
    // Get Desc from server
    if(detail_id != ""){
        $.ajax({
            url: "/blogs?detail_id=" + GetUrlParams().id,
            success: function (data) {
                var result = JSON.parse(data);
                document.getElementById("desc").value = result[0][2];
                document.getElementById("tags").value =result[0][8];
            }
        });
    }
    // get tags from server;
    oTags = document.getElementById("tagList");
    var tagsHtml = "";
    $.ajax({
        url: "/tags",
        success: function (data) {
            var result = JSON.parse(data);
            for (var i = 0; i < result.length; i++) {
                tagsHtml = tagsHtml + "<option>" + result[i][1] + "</option>";
            }
            oTags.innerHTML = tagsHtml;
        }
    });
}

// Release to server
function release() {
    var uEmail = getCookie("uEmail");
    var title = document.title;
    var desc = document.getElementById('desc').value;
    var tags = document.getElementById('tags').value;
    var content = editor.getValue();

    // console.log("tags: "+tags);
    if(detail_id != ""){
        console.log("update: " + title + "--" + desc +"--"+tags+"--"+detail_id+"--"+content);
        $.ajax({
            type: "POST",
            url: "/updateBlog",
            dataType: "JSON",
            data: {
                "title": title,
                "desc": desc,
                "tags": tags,
                "detail_id": detail_id,
                "content": content
            },
            success: function (data) {
                console.log(data);
                jQuery.dialog({
                    title: 'Release successed!',
                    message: 'Your Blog has been released to server.',
                    okText: 'OK',
                    showClose: false
                });
            }
        });
    }else {
        console.log("newBlog: " + title + "--" + desc +"--"+tags+"--"+detail_id+"--"+content);
        $.ajax({
            type: "POST",
            url: "/newBlog",
            dataType: "JSON",
            data: {
                "user_email": uEmail,
                "title": title,
                "desc": desc,
                "tags": tags,
                "content": content
            },
            success: function (data) {
                console.log(data);
                jQuery.dialog({
                    title: 'Release successed!',
                    message: 'Your Blog has been released to server.',
                    okText: 'OK',
                    showClose: false
                });
            }
        });
    }

}

start();